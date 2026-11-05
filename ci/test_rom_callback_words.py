"""Exercise stored callback words and the real navigation reader with mocked handlers.

Run: python3 ci/test_rom_callback_words.py --scratch <private-directory>
"""
import argparse
import pathlib
import re
import struct
import subprocess
import unittest

ROOT = pathlib.Path(__file__).resolve().parents[1]


class CallbackWords(unittest.TestCase):
    def test_production_table_words(self):
        """Compile the actual five definitions with only SDK scalar types mocked."""
        (SCRATCH / 'types.h').write_text(
            '#ifndef TYPES_H\n#define TYPES_H\n'
            'typedef unsigned char u8; typedef signed char s8; '
            'typedef unsigned short u16; typedef short s16; '
            'typedef unsigned int u32; typedef int s32; '
            'typedef unsigned long long u64; typedef long long s64; '
            'typedef float f32; typedef double f64;\n#endif\n')
        (SCRATCH / 'include_asm.h').write_text(
            '#define INCLUDE_ASM(...)\n#define INCLUDE_RODATA(...)\n')
        cases = [
            ('de', 'Source/Data/constants_data_block2.cpp', 'g_weaponSwitchStateWordsDe',
             748, {144: 0x0022FF04, 148: 0x00232B64}),
            ('us', 'Source/Data/Ai/weapon_switch_state_words_us.cpp',
             'g_weaponSwitchStateWordsUs', 744, {140: 0x0022FEE4, 144: 0x00232B44}),
            ('eu', 'Source/Data/Ai/playerai_initializeplayerhealth_data.cpp',
             'k_PlayeraiInitializeplayerhealthData', 744,
             {140: 0x00232B44, 144: 0x00232B74}),
            ('us', 'Source/Ai/Nav/scaled.cpp',
             'k_playerNavDirectionAndHandlerTable', 1888,
             {112: 0x00210230, 116: 0x0020F6C0, 120: 0x00210E88, 124: 0x0020DDE0}),
            ('eu-x', 'Source/Ai/Nav/wheel.cpp',
             'k_navResetwheelprobestateFragment', 8,
             {0: 0x00232790, 4: 0x00232790}),
        ]
        for version, source, symbol, size, captured in cases:
            with self.subTest(version=version, symbol=symbol):
                obj = SCRATCH / (symbol + '.o')
                # Extract the actual definition; mock unrelated SDK declarations.
                production = (ROOT / source).read_text()
                finish = production.index('\n};', production.index('} '+symbol) if 'Words' in symbol or 'Initialize' in symbol else production.index(symbol+' = {') if symbol == 'k_playerNavDirectionAndHandlerTable' else production.index(symbol+'[2] = {')) + 3
                if symbol == 'k_playerNavDirectionAndHandlerTable':
                    begin = production.index('Ovldat2ConstantWordsLayout '+symbol+' = {')
                    layout = (ROOT / 'Include/Data/rest_source_records.h').read_text()
                    first = layout.index('typedef struct Ovldat2ConstantWordsLayout')
                    layout = layout[first:layout.index('} Ovldat2ConstantWordsLayout;', first)+len('} Ovldat2ConstantWordsLayout;')]
                elif symbol == 'k_navResetwheelprobestateFragment':
                    begin = production.index('const RomCallbackWord '+symbol+'[2] = {')
                    layout = ''
                else:
                    begin = production.rfind('struct {', 0, production.index('} '+symbol))
                    layout = ''
                snippet = SCRATCH / (symbol+'.c')
                snippet.write_text('#include "types.h"\n#include "Data/rom_callback_word.h"\nextern char g_weaponFireStateCallbackTable[];\n'+layout+'\n'+production[begin:finish])
                subprocess.run(['cc', '-m32', '-fno-pic', '-fno-pie', '-x', 'c', '-c',
                                '-DVERSION_' + version.upper().replace('-', '_'),
                                '-I' + str(SCRATCH), '-I' + str(ROOT / 'Include'),
                                str(snippet), '-o', str(obj)], check=True)
                b = obj.read_bytes()
                self.assertEqual(b[4:6], bytes([1, 1]))  # ELF32 little-endian test seam.
                h = struct.unpack_from('<HHIIIIIHHHHHH', b, 16)
                sections = [struct.unpack_from('<IIIIIIIIII', b, h[5] + i*h[10])
                            for i in range(h[11])]
                found = None
                for sh in sections:
                    if sh[1] != 2:
                        continue
                    strings = sections[sh[6]]
                    names = b[strings[4]:strings[4]+strings[5]]
                    for off in range(sh[4], sh[4]+sh[5], sh[9]):
                        name, value, length, _, _, index = struct.unpack_from('<IIIBBH', b, off)
                        if names[name:names.index(b'\0', name)].decode() == symbol:
                            found = value, length, index
                self.assertIsNotNone(found)
                value, length, index = found
                self.assertEqual(length, size)
                section = sections[index]
                data = b[section[4]+value:section[4]+value+length]
                for offset, expected in captured.items():
                    self.assertEqual(struct.unpack_from('<I', data, offset)[0], expected)
                for rel in sections:
                    if rel[1] == 9 and rel[7] == index:
                        for off in range(rel[4], rel[4]+rel[5], 8):
                            where, _ = struct.unpack_from('<II', b, off)
                            self.assertNotIn(where-value, captured,
                                             'callback must be a stored word, not a pointer relocation')

    def test_captured_words_layout_and_reader(self):
        source = (ROOT / 'Source/Ai/Nav/behaviour.cpp').read_text()
        start = source.index('void Nav_RunBehaviorHandler(')
        end = source.index('\n/*', start)
        reader = source[start:end]
        declarations = (ROOT / 'Include/Common/ai_behaviour_types.h').read_text()
        first = declarations.index('struct Behaviour {')
        behaviour = declarations[first:declarations.index('};', first)+2]
        entry = re.search(r'typedef struct AiBehaviourEntry \{[^}]+\} AiBehaviourEntry;', declarations).group(0)
        (SCRATCH / 'types.h').write_text('typedef unsigned char u8; typedef unsigned int u32; typedef int s32;\n')
        harness = r'''
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include "Data/rom_callback_word.h"
typedef struct { s32 state, handlerIndex; } AiController;
typedef s32 (*Handler)(void *);
#if defined(VERSION_US)
static struct { RomCallbackWord *behaviorRows[14]; } k_playerNavDirectionAndHandlerTable;
#define g_aiCharacterBehaviorTables k_playerNavDirectionAndHandlerTable.behaviorRows
#else
RomCallbackWord *g_aiCharacterBehaviorTables[14];
#endif
'''+behaviour+'\n'+entry+'\n'+reader+r'''
static int calls;
static s32 advance(void *p) { ++calls; return 1; }
static s32 change(void *p) { ((AiController *)p)->state = 1; return 1; }
struct StateRow { s32 id; RomCallbackWord enter, update; u32 rest[5]; };
int main(void) {
    /* Captured US navigation +112/+116/+120/+124 and EU-X two-word span. */
    RomCallbackWord captured[] = {{0x00210230}, {0x0020F6C0},
                                  {0x00210E88}, {0x0020DDE0}, {0},
                                  {0x00232790}, {0x00232790}};
    RomCallbackWord row[20] = {{0}};
    AiController c = {0, 1};
    struct Behaviour behaviour = {{0}, {0x00232B44}};
    assert(sizeof(behaviour) == 12);
    assert(offsetof(struct Behaviour, update) == 8);
    assert(behaviour.update.address == 0x00232B44);
    assert(sizeof(RomCallbackWord) == 4);
    assert(_Alignof(RomCallbackWord) == 4);
    assert(offsetof(struct StateRow, enter) == 4);
    assert(offsetof(struct StateRow, update) == 8);
    assert(sizeof(struct StateRow) == 32);
    assert(sizeof(row) == 80);
    AiBehaviourEntry actual = {0};
    actual.enter.address = captured[0].address;
    actual.update.address = captured[1].address;
    assert(sizeof(actual) == 32 && offsetof(AiBehaviourEntry, update) == 8);
    assert(captured[0].address == 0x00210230);
    assert(captured[0].address != 0x80210230); /* Original full-pointer defect. */
    assert((uintptr_t)(Handler)(uintptr_t)captured[0].address == 0x00210230);
    assert(captured[4].address == 0);
    assert(captured[5].address == captured[6].address);
    assert((uintptr_t)advance <= UINT32_MAX);
    row[0].address = (u32)(uintptr_t)advance;
    g_aiCharacterBehaviorTables[0] = row;
    Nav_RunBehaviorHandler(&c); /* Null selected slot restarts at slot zero. */
    assert(calls == 1 && c.handlerIndex == 1);
    row[1].address = (u32)(uintptr_t)change;
    Nav_RunBehaviorHandler(&c);
    assert(c.state == 1 && c.handlerIndex == 0);
    Nav_RunBehaviorHandler(&c); /* Missing table is a no-op. */
    assert(calls == 1);
    c.state = 99; c.handlerIndex = 0;
    Nav_RunBehaviorHandler(&c);
    assert(c.state == 0 && c.handlerIndex == 0 && calls == 2);
    row[0].address = 0;
    Nav_RunBehaviorHandler(&c); /* Null first handler is a no-op. */
    assert(calls == 2);
    return 0;
}
'''
        cfile = SCRATCH / 'callbacks.c'
        binary = SCRATCH / 'callbacks'
        cfile.write_text(harness)
        for flags in [[], ['-DVERSION_US']]:
            subprocess.run(['cc', '-std=c11', '-no-pie', '-Wno-int-to-pointer-cast',
                            '-I'+str(SCRATCH), '-I'+str(ROOT / 'Include'),
                            *flags, str(cfile), '-o', str(binary)], check=True)
            subprocess.run([str(binary)], check=True)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--scratch', type=pathlib.Path, required=True)
    args, rest = parser.parse_known_args()
    SCRATCH = args.scratch.resolve()
    SCRATCH.mkdir(parents=True, exist_ok=True)
    unittest.main(argv=[__file__]+rest)
