#!/usr/bin/env python3
"""Exercise the folded dispatcher bodies with mocked widget/table seams.

Run: python3 Source/Ui/Tsmos/Smp/test_dispatch.py --build-dir <scratch directory>
"""
import argparse
import pathlib
import re
import subprocess

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--build-dir', required=True, type=pathlib.Path)
args = parser.parse_args()
args.build_dir.mkdir(parents=True, exist_ok=True)
source = '''#include <assert.h>
typedef int s32;
#define ANY_ACTOR_KIND 30000
struct MenuWidget { short resource; };
typedef s32 (*ResidentEventHandler)(void *, s32, s32, s32, s32);
typedef struct { s32 event, actorKind; ResidentEventHandler handler; } ResidentEventHandlerEntry;
static int first(void *w, int e, int a, int b, int c) {
    assert(((struct MenuWidget *)w)->resource == 42);
    assert(e == 10 && a == 11 && b == 12 && c == 13);
    return 101;
}
static int second(void *w, int e, int a, int b, int c) { return 202; }
'''
cases = []
for path in sorted(pathlib.Path(__file__).parent.glob('smp_*.cpp')):
    for match in re.finditer(r's32 (Smp\w+_Dispatch\w+)\([^\n]+\) \{\n.*?\n\}', path.read_text(), re.S):
        body = match.group(0)
        table = re.search(r'handlerEntry = \(ResidentEventHandlerEntry \*\)&(\w+);', body)
        if table is None:
            continue
        table = table.group(1)
        source += f'ResidentEventHandlerEntry {table}[4];\n' + body + '\n'
        call = f'{match.group(1)}(&widget, 10, 11, 12, 13)'
        cases.append(f'''
    {table}[0] = (ResidentEventHandlerEntry){{9, 42, second}};
    {table}[1] = (ResidentEventHandlerEntry){{10, 41, second}};
    {table}[2] = (ResidentEventHandlerEntry){{10, 42, first}};
    assert({call} == 101);
    {table}[2].actorKind = ANY_ACTOR_KIND;
    assert({call} == 101);
    {table}[1].actorKind = 42;
    assert({call} == 202);
    {table}[1].actorKind = 41;
    {table}[2].actorKind = 43;
    assert({call} == 0);
    {table}[0].handler = 0;
    {table}[2].actorKind = 42;
    assert({call} == 0);
''')
assert len(cases) == 8, f'Expected eight folded dispatchers, selected {len(cases)}'
source += 'int main(void) { struct MenuWidget widget = {42};\n' + ''.join(cases) + 'return 0; }\n'
cfile = args.build_dir / 'dispatch.c'
binary = args.build_dir / 'dispatch'
cfile.write_text(source)
subprocess.run(['cc', '-std=c99', '-Wall', '-Werror', str(cfile), '-o', str(binary)], check=True)
subprocess.run([str(binary.resolve())], check=True)
print(f'PASS: {len(cases)} dispatchers; 40 exact-kind, wildcard, first-match, no-match and sentinel assertions')
