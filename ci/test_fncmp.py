import struct
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import fncmp  # noqa: E402

LINES = ['Same = 0x80000000; // type:func rom:0x10',
         'Other = 0x80000008; // type:func rom:0x18',
         'g_data = 0x80000018; // rom:0x28',
         'End = 0x80000020; // type:func rom:0x30']
ROM = bytes(16) + bytes.fromhex('0c000010 00000000' '24020001 03e00008 00000000 00000000') + bytes(8)


class FncmpTest(unittest.TestCase):
    def test_rom_functions_sizes(self):
        self.assertEqual(fncmp.rom_functions(LINES), {'Same': (0x10, 8), 'Other': (0x18, 16)})

    def test_matching_function_masks_relocated_jal(self):
        text = bytes.fromhex('0c000000 00000000')
        row = next(fncmp.rows([('Same', 0, 8)], text, {0: fncmp.RELOC_MASK['R_MIPS_26']},
                              ROM, fncmp.rom_functions(LINES)))
        self.assertEqual(row, ('Same', 8, 8, 0, 0))

    def test_differing_function_reports_size_and_words(self):
        table = fncmp.rom_functions(LINES)
        row = next(fncmp.rows([('Other', 0, 12)], bytes.fromhex('24020002 03e00008 00000000'), {}, ROM, table))
        self.assertEqual(row, ('Other', 12, 12, 0, 1))
        text = bytes.fromhex('24020001 00000000 03e00008 00000000')
        row = next(fncmp.rows([('Other', 0, 16)], text, {}, ROM, table))
        self.assertEqual(row[3], 4)

    def test_rom_alignment_padding_is_not_a_delta(self):
        row = next(fncmp.rows([('Other', 0, 12)], bytes.fromhex('24020001 03e00008 00000000'), {},
                              ROM, fncmp.rom_functions(LINES)))
        self.assertEqual(row, ('Other', 12, 12, 0, 0))

    def test_one_instruction_overflow_into_trailing_nop_is_a_delta(self):
        text = bytes.fromhex('24020001 24030002 03e00008 00000000')
        row = next(fncmp.rows([('Other', 0, 16)], text, {}, ROM, fncmp.rom_functions(LINES)))
        self.assertEqual(row[1:4], (16, 12, 4))

    def test_non_zero_words_after_last_return_are_code(self):
        tail = bytes.fromhex('03e00008 00000000 8c820020 8fa30010')
        self.assertEqual(fncmp.code_size(tail), 16)
        self.assertEqual(fncmp.code_size(tail + bytes(8)), 16)

    def test_missing_trailing_rom_words_are_a_delta(self):
        text = bytes.fromhex('03e00008 00000000 00000000 00000000')
        rom = bytes.fromhex('03e00008 00000000 8c820020 8fa30010') + bytes(16)
        lines = ['Other = 0x80000000; // type:func rom:0x0',
                 'End = 0x80000010; // type:func rom:0x10']
        row = next(fncmp.rows([('Other', 0, 16)], text, {}, rom, fncmp.rom_functions(lines)))
        self.assertEqual(row[1:4], (8, 16, -8))

    def test_delay_slot_detection(self):
        for word in (0x03E00008, 0x45000003, 0x10400002, 0x0C000000, 0x50400001):
            self.assertTrue(fncmp.has_delay_slot(word), hex(word))
        for word in (0x24020001, 0x00000000, 0x8FBF0014):
            self.assertFalse(fncmp.has_delay_slot(word), hex(word))

    def test_call_sites_collect_arguments_including_delay_slot(self):
        code = bytes.fromhex('24040001 0c000000 24050002 8fa60010 0c000000 00000000')
        self.assertEqual([args for _, args in fncmp.call_sites(code)], [['a0', 'a1'], ['a2']])

    def test_call_rows_report_dropped_argument(self):
        rom = bytes(16) + bytes.fromhex('24040001 3c060000 0c000004 24050002 03e00008 00000000')
        table = {'Hook': (0x10, 24)}
        text = bytes.fromhex('24040001 0c000000 24050002 03e00008 00000000')
        rows = list(fncmp.call_rows([('Hook', 0, 20)], text, rom, table, {0x80000010: 'Callee'}))
        self.assertEqual(rows, [('Hook', 0, 'Callee', ['a0', 'a1'], ['a0', 'a1', 'a2'])])
        self.assertEqual(list(fncmp.call_rows([('Hook', 0, 20)], text, bytes(16) + text, {'Hook': (0x10, 20)}, {})), [])


class FndisTest(unittest.TestCase):
    def test_mnemonics_mask_immediates(self):
        import fndis
        text = '   0:\t27bdffe8 \taddiu\tsp,sp,-24\n   4:\t3c040000 \tlui\ta0,0x0\n'
        self.assertEqual(fndis.mnemonics(text), ['addiu sp,sp,-24', 'lui a0,N'])


def tiny_object():
    """ELF32 BE with one function in its own .text.Same section and one R_MIPS_26."""
    code = bytes.fromhex('0c000000 00000000')
    strtab = b'\0Same\0'
    symtab = bytes(16) + struct.pack('>IIIBBH', 1, 0, 8, 0x12, 0, 1)
    rel = struct.pack('>II', 0, (1 << 8) | 4)
    blobs = [code, symtab, strtab, rel]
    offsets, at = [], 0x34
    for b in blobs:
        offsets.append(at)
        at += len(b)
    headers = [bytes(40),
               struct.pack('>10I', 0, 1, 6, 0, offsets[0], 8, 0, 0, 4, 0),
               struct.pack('>10I', 0, 2, 0, 0, offsets[1], 32, 3, 1, 4, 16),
               struct.pack('>10I', 0, 3, 0, 0, offsets[2], len(strtab), 0, 0, 1, 0),
               struct.pack('>10I', 0, 9, 0, 0, offsets[3], 8, 2, 1, 4, 8)]
    header = bytearray(0x34)
    header[0x20:0x24] = at.to_bytes(4, 'big')
    header[0x2E:0x30] = (40).to_bytes(2, 'big')
    header[0x30:0x32] = len(headers).to_bytes(2, 'big')
    return bytes(header) + b''.join(blobs) + b''.join(headers)


class ReadObjectTest(unittest.TestCase):
    def test_per_function_section_and_relocation(self):
        functions, code, relocs = fncmp.read_object(tiny_object())
        self.assertEqual(functions, [('Same', 0, 8)])
        self.assertEqual(code, bytes.fromhex('0c000000 00000000'))
        self.assertEqual(relocs, {0: fncmp.RELOC_MASK['R_MIPS_26']})
        row = next(fncmp.rows(functions, code, relocs, ROM, fncmp.rom_functions(LINES)))
        self.assertEqual(row, ('Same', 8, 8, 0, 0))


if __name__ == '__main__':
    unittest.main()
