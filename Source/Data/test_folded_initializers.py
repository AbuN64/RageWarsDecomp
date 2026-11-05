"""Regression checks for folded data whose C initializer previously lost words."""
import pathlib
import re
import unittest
import struct

ROOT = pathlib.Path(__file__).resolve().parents[2]


class FoldedInitializers(unittest.TestCase):
    def test_weapon_record_preserves_complete_rom_span(self):
        source = (ROOT / 'Source/Camera/playerai_initializeplayerhealth_data.cpp').read_text()
        payload = source.split('WeaponStateRecordsUs k_weaponStateRecordsUs = {', 1)[1]
        words = payload.split('{', 1)[1].split('}', 1)[0]
        entries = [entry.strip() for entry in words.split(',') if entry.strip()]
        self.assertEqual(len(entries), 1021)
        text_words = re.search(r'\{ (0x585F5348), (0x4F544755), (0x4E5F5041) \}', payload)
        self.assertIsNotNone(text_words)
        text = b''.join(int(word, 16).to_bytes(4, 'big') for word in text_words.groups())
        self.assertEqual(text, b'X_SHOTGUN_PA')
        self.assertEqual(1021 * 4 + len(text) + 2 * 4, 0xCBE98 - 0xCAE90)

    def test_weapon_state_fold_closes_every_conditional(self):
        source = (ROOT / 'Source/Data/weapon_state_tables.cpp').read_text()
        depth = 0
        for line in source.splitlines():
            if re.match(r'^\s*#\s*(if|ifdef|ifndef)\b', line):
                depth += 1
            elif re.match(r'^\s*#\s*endif\b', line):
                depth -= 1
                self.assertGreaterEqual(depth, 0)
        self.assertEqual(depth, 0)

    def test_player_action_records_keep_six_words_per_state(self):
        # Each ROM state is 24 bytes: three addresses, mask, action, flags.
        for file, symbol in [
            ('Source/Data/player_action_state_table.cpp', 'g_playerActionStateTableWordsUs'),
            ('Source/Data/Frontend/B/constants.cpp', 'g_sceneEffectTuningUsRevision'),
        ]:
            with self.subTest(symbol=symbol):
                source = (ROOT / file).read_text().split(symbol + ' = {', 1)[1]
                rows = re.findall(r'^        \{ (.*) \},?$', source, re.MULTILINE)
                self.assertEqual(len(rows), 94)
                for row in rows:
                    self.assertEqual(len(row.split(',')), 6)
                # First and final state numeric words read from both ROM tables.
                self.assertEqual([v.strip() for v in rows[0].split(',')][-3:],
                                 ['0', '1', '131072'])
                self.assertEqual([v.strip() for v in rows[-1].split(',')][-3:],
                                 ['0', '23301', '131072'])

    def test_decode_table_headers_preserve_serialized_bytes(self):
        source = (ROOT / 'Source/Engine/Audio/decoder.cpp').read_text()
        rows = source.split('DecodeTable g_audioDecodeTables[4] = {', 1)[1].split('};', 1)[0]
        expected = [
            'ffffff810000007f000000ff00000010000001010000010000000001',
            'ffffff810000007f000000ff00000010000001050000010000000005',
            'ffffff810000007f000000ff00000010000001090000010000000009',
            'ffffffc000000040ffffffff00000010ffffffff0000008100000000',
        ]
        headers = re.findall(r'\{ ([^{}]+)', rows)
        self.assertEqual(len(headers), 4)
        for row, fixture in zip(headers, expected):
            values = [int(value.strip()) for value in row.split(',')[:8]]
            self.assertEqual(struct.pack('>iiiHHiii', *values).hex(), fixture)

    def test_weapon_callback_tail_uses_entry_address(self):
        # The preserved tail pointer is byte offset 0x120: 0x20 header + 8 * 0x20.
        source = (ROOT / 'Source/Data/Overlays/Credits/linktables.cpp').read_text()
        self.assertIn('(unsigned int)&g_weaponFireStateCallbackTable.entries[8]', source)
        self.assertNotRegex(source, r'(?<!&)g_weaponFireStateCallbackTable \+ 0x120')
        self.assertNotRegex(source, r'g_weaponLockedNoticeTextEuX\+0x[0-9A-Fa-f]+\[')

    def test_character_table_tail_retains_rom_offset(self):
        source = (ROOT / 'Source/fx.cpp').read_text()
        # The ROM self-reference targets +0xF24: 891 words and 39 eight-byte entries.
        self.assertEqual(891 * 4 + 39 * 8, 0xF24)
        self.assertIn('&g_pakAdjustownernotificationoptionDataConstantWords.references2[0]', source)
        self.assertNotIn('&g_pakAdjustownernotificationoptionDataConstantWords.references2[1]', source)



if __name__ == '__main__':
    unittest.main()
