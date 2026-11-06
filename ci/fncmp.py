"""Compare each function of one compiled object against its bytes in a base ROM.

Usage: python3 ci/fncmp.py <version> <object.o> [--all | --calls]
Prints one row per function: name, ours size, ROM size, size delta, and
the count of differing instruction words after masking relocated fields.
Sizes are real code sizes: only trailing zero words are alignment, except a
nop that fills the delay slot of the function's last jump or branch; non-zero
words after the last return are ROM code our build must also hold.
--calls prints, per jal site whose a0-a3 setup differs from the ROM's,
the function, site ordinal, ROM callee and both argument register sets.
"""
import re
import struct
import sys
from pathlib import Path

SYMBOL = re.compile(r'\s*(\w+)\s*=\s*0x[0-9A-Fa-f]+;(.*)rom:0x([0-9A-Fa-f]+)')
# Relocation type -> mask of the instruction bits the linker writes.
RELOC_MASK = {'R_MIPS_26': 0x03FFFFFF, 'R_MIPS_HI16': 0xFFFF, 'R_MIPS_LO16': 0xFFFF,
              'R_MIPS_GPREL16': 0xFFFF, 'R_MIPS_32': 0xFFFFFFFF}


def rom_functions(symbol_lines):
    """Map function name -> (rom offset, size to the next ROM symbol) from symbol_addrs lines."""
    rows = sorted((int(m.group(3), 16), m.group(1), 'type:func' in m.group(2))
                  for m in map(SYMBOL.match, symbol_lines) if m)
    return {name: (offset, rows[i + 1][0] - offset)
            for i, (offset, name, func) in enumerate(rows[:-1]) if func}


def compare(ours, rom, masks):
    """Return the count of 4-byte words that differ outside the relocated bits."""
    differ = 0
    for word in range(0, min(len(ours), len(rom)) // 4 * 4, 4):
        mask = ~masks.get(word, 0) & 0xFFFFFFFF
        a = int.from_bytes(ours[word:word + 4], 'big') & mask
        b = int.from_bytes(rom[word:word + 4], 'big') & mask
        differ += a != b
    return differ


def has_delay_slot(word):
    """True when the MIPS instruction word is a jump or branch with a delay slot."""
    op = word >> 26
    if op == 0:
        return word & 0x3F in (8, 9)  # jr, jalr
    if op == 0x11:
        return (word >> 21) & 0x1F == 8  # bc1f/bc1t and likely forms
    return op in (1, 2, 3, 4, 5, 6, 7, 0x14, 0x15, 0x16, 0x17)


def branch_target(word, at):
    """Return the byte offset a conditional branch at `at` targets, or None."""
    op = word >> 26
    if op in (1, 4, 5, 6, 7, 0x14, 0x15, 0x16, 0x17) or (op == 0x11 and (word >> 21) & 0x1F == 8):
        offset = word & 0xFFFF
        return at + 4 + ((offset - 0x10000 if offset & 0x8000 else offset) << 2)
    return None


def code_size(code):
    """Return the real code bytes.

    Only trailing zero words are alignment, and a zero word that is the delay
    slot of the last jump or branch stays code. Non-zero words after the last
    `jr ra` are real instructions (dead code or an unnamed stub): they count,
    so a build that lacks them shows as a size delta, never as fill.
    """
    full = len(code) // 4 * 4
    end = full
    while end >= 4 and code[end - 4:end] == b'\0\0\0\0':
        end -= 4
    if end < full and end >= 4 and has_delay_slot(int.from_bytes(code[end - 4:end], 'big')):
        end += 4
    return end


def rows(functions, text, relocs, rom_image, table):
    """Yield (name, ours, rom, delta, differing words) per object function."""
    for name, start, size in functions:
        if name not in table:
            yield name, size, None, None, None
            continue
        offset, rom_size = table[name]
        code = text[start:start + code_size(text[start:start + size])]
        masks = {r - start: m for r, m in relocs.items() if start <= r < start + size}
        rom = rom_image[offset:offset + code_size(rom_image[offset:offset + rom_size])]
        yield (name, len(code), len(rom), len(code) - len(rom), compare(code, rom, masks))


ARGUMENTS = ('a0', 'a1', 'a2', 'a3')


def written_register(word):
    """Return the general register an instruction word writes, or None."""
    op = word >> 26
    if op == 0:
        return None if word & 0x3F in (8, 0x18, 0x19, 0x1A, 0x1B) else (word >> 11) & 0x1F
    if op in (8, 9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF) or 0x20 <= op <= 0x27:
        return (word >> 16) & 0x1F
    if op == 0x11 and (word >> 21) & 0x1F in (0, 2):  # mfc1, cfc1
        return (word >> 16) & 0x1F
    return None


def call_sites(code):
    """Return [(call word, sorted a0-a3 names written since the previous call, delay slot included)]."""
    words = [int.from_bytes(code[k:k + 4], 'big') for k in range(0, len(code) // 4 * 4, 4)]
    sites, written, k = [], set(), 0
    while k < len(words):
        word = words[k]
        written.add(written_register(word))
        if word >> 26 == 3 or (word >> 26 == 0 and word & 0x3F == 9):  # jal, jalr
            written.discard(written_register(word))
            if k + 1 < len(words):
                written.add(written_register(words[k + 1]))
            sites.append((word, sorted(ARGUMENTS[r - 4] for r in written if r is not None and 4 <= r <= 7)))
            written, k = set(), k + 2
            continue
        k += 1
    return sites


def call_rows(functions, text, rom_image, table, names):
    """Yield (function, site ordinal, ROM callee, ours args, ROM args) per differing call site."""
    for name, start, size in functions:
        if name not in table:
            continue
        offset, rom_size = table[name]
        ours = call_sites(text[start:start + code_size(text[start:start + size])])
        rom = call_sites(rom_image[offset:offset + code_size(rom_image[offset:offset + rom_size])])
        for k in range(max(len(ours), len(rom))):
            a = ours[k][1] if k < len(ours) else None
            b = rom[k][1] if k < len(rom) else None
            if a != b:
                callee = names.get((rom[k][0] & 0x3FFFFFF) << 2 | 0x80000000, '?') if k < len(rom) else '-'
                yield name, k, callee, a, b


VADDR = re.compile(r'\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+);')


def vaddr_names(symbol_lines):
    """Map virtual address -> symbol name."""
    return {int(m.group(2), 16): m.group(1) for m in map(VADDR.match, symbol_lines) if m}


RELOC_TYPE = {2: 'R_MIPS_32', 4: 'R_MIPS_26', 5: 'R_MIPS_HI16', 6: 'R_MIPS_LO16', 7: 'R_MIPS_GPREL16'}


def read_object(data):
    """Parse a big-endian ELF32 relocatable.

    Return (functions [(name, start, size)], code bytes, {start-relative offset: mask})
    with every executable section laid end to end, so per-function sections work.
    """
    u16 = lambda o: int.from_bytes(data[o:o + 2], 'big')
    u32 = lambda o: int.from_bytes(data[o:o + 4], 'big')
    shoff, shsize, shnum = u32(0x20), u16(0x2E), u16(0x30)
    sections = [struct.unpack_from('>10I', data, shoff + k * shsize) for k in range(shnum)]
    base, code = {}, bytearray()
    for k, (_, kind, flags, _, offset, size, *_rest) in enumerate(sections):
        if kind == 1 and flags & 4:  # PROGBITS, SHF_EXECINSTR
            base[k] = len(code)
            code += data[offset:offset + size]
            code += bytes(-len(code) % 4)
    functions, relocs = [], {}
    for k, (_, kind, _, _, offset, size, link, info, _, entsize) in enumerate(sections):
        if kind == 2:  # SYMTAB
            strtab = sections[link][4]
            for e in range(offset, offset + size, 16):
                name, value, sym_size, sym_info, _, shndx = struct.unpack_from('>IIIBBH', data, e)
                if sym_info & 0xF == 2 and shndx in base:
                    end = data.index(b'\0', strtab + name)
                    functions.append((data[strtab + name:end].decode(), base[shndx] + value, sym_size))
        elif kind in (9, 4) and info in base:  # REL / RELA on code
            for e in range(offset, offset + size, entsize):
                r_offset, r_info = struct.unpack_from('>II', data, e)
                kind_name = RELOC_TYPE.get(r_info & 0xFF)
                if kind_name:
                    relocs[base[info] + r_offset] = RELOC_MASK[kind_name]
    functions.sort(key=lambda f: f[1])
    return functions, bytes(code), relocs


def main(argv):
    version, obj = argv[1], argv[2]
    lines = Path(f'versions/{version}/symbol_addrs.txt').read_text().splitlines()
    table = rom_functions(lines)
    rom_image = Path(f'roms/baserom.{version}.z64').read_bytes()
    functions, text, relocs = read_object(Path(obj).read_bytes())
    if '--calls' in argv:
        names, bad = vaddr_names(lines), 0
        for name, site, callee, ours, rom in call_rows(functions, text, rom_image, table, names):
            bad += 1
            print(f'{name}\tsite={site}\tcallee={callee}\tours={ours}\trom={rom}')
        print(f'call_sites_differing={bad}')
        return 1 if bad else 0
    bad = 0
    for name, ours, rom, delta, differ in rows(functions, text, relocs, rom_image, table):
        ok = delta == 0 and differ == 0
        bad += not ok
        if not ok or '--all' in argv:
            print(f'{name}\tours={ours}\trom={rom}\tdelta={delta}\tdiffer={differ}')
    print(f'functions={len(functions)} differing={bad}')
    return 1 if bad else 0


if __name__ == '__main__':
    sys.exit(main(sys.argv))
