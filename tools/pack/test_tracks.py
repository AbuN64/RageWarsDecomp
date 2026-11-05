import os
import struct
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import tracks


def row(key, name):
    body = struct.pack('>iiii', 0, 7, key, 8) + b'\0' * 8 + name.encode() + b'\0'
    return body + b'\0' * (tracks.ENTRY - len(body))


class TracksTest(unittest.TestCase):
    def test_lists_rows_of_the_record_block(self):
        block = struct.pack('>II', tracks.ENTRY, 2) + row(601, 'Map01_MH-BL-2PL-EASY') + row(637, 'cinema')
        rom = b'\xff' * 16 + block + b'\xff' * 8
        self.assertEqual(list(tracks.find_tables(rom)), [(16, [(601, 'Map01_MH-BL-2PL-EASY'), (637, 'cinema')])])

    def test_refuses_a_row_without_a_printable_name(self):
        block = struct.pack('>II', tracks.ENTRY, 1) + struct.pack('>iiii', 0, 0, 1, 0) + b'\x01' * (tracks.ENTRY - 16)
        self.assertIsNone(tracks.rows_at(block, 0))


if __name__ == '__main__':
    unittest.main()
