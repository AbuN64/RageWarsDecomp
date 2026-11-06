"""Mnemonic diff of one compiled function against its bytes in a base ROM.

Usage: python3 ci/fndis.py <version> <object.o> <function> [context]
Disassembles both with mips-linux-gnu-objdump, replaces immediates with N
and prints a unified diff (ours vs rom), MAXL lines at most (default 80).
"""
import difflib
import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import fncmp  # noqa: E402

LINE = re.compile(r'\s*[0-9a-f]+:\s+[0-9a-f]{8}\s+(\S+)\s*(.*)')


def mnemonics(objdump_text):
    """Return 'mnemonic operands' per instruction with hex immediates replaced by N."""
    return [f"{m.group(1)} {re.sub(r'0x[0-9a-f]+', 'N', m.group(2))}".rstrip()
            for m in map(LINE.match, objdump_text.splitlines()) if m]


def disassemble(code):
    """Disassemble raw big-endian MIPS bytes into mnemonic lines."""
    with tempfile.NamedTemporaryFile(delete=False) as f:
        f.write(code)
    try:
        out = subprocess.run(['mips-linux-gnu-objdump', '-D', '-b', 'binary', '-m', 'mips:4300', '-EB', f.name],
                             capture_output=True, text=True, check=True).stdout
    finally:
        os.unlink(f.name)
    return mnemonics(out)


def function_bytes(version, obj, name):
    """Return (ours, rom) real code bytes of one function."""
    table = fncmp.rom_functions(Path(f'versions/{version}/symbol_addrs.txt').read_text().splitlines())
    rom = Path(f'roms/baserom.{version}.z64').read_bytes()
    functions, text, _ = fncmp.read_object(Path(obj).read_bytes())
    start, size = next((s, z) for n, s, z in functions if n == name)
    offset, rom_size = table[name]
    ours = text[start:start + size]
    theirs = rom[offset:offset + rom_size]
    return ours[:fncmp.code_size(ours)], theirs[:fncmp.code_size(theirs)]


def main(argv):
    version, obj, name = argv[1:4]
    context = int(argv[4]) if len(argv) > 4 else 2
    ours, rom = (disassemble(b) for b in function_bytes(version, obj, name))
    print(f'{name} ours={len(ours)} rom={len(rom)}')
    limit = int(os.environ.get('MAXL', '80'))
    for k, line in enumerate(difflib.unified_diff(ours, rom, 'ours', 'rom', n=context, lineterm='')):
        if k >= limit:
            break
        print(line)
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv))
