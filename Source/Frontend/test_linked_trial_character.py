"""Check signed character selection at the linked-trial dispatcher boundary."""
import pathlib
import subprocess
import sys
import tempfile

root = pathlib.Path(__file__).resolve().parents[2]
text = (root / "Source/Frontend/results.cpp").read_text()
start = text.index("void Results_MarkLinkedTrialsAvailable(void *trialBits) {")
end = text.index("\n}\n", start) + 3
harness = r'''
#include <assert.h>
#include <stdint.h>
typedef int s32;
typedef signed char s8;
typedef unsigned char u8;
struct GameSettingsModeStatusView { int mode; struct { int kind; } status[4]; } g_gameSettingsView;
struct TableFrontendMarkLinkedTrialsAvailable { int first; int items[3]; } preset;
struct Screen { int player; u8 *owned; u8 *pending; } screen, *g_trialCatalogueScreen = &screen;
u8 g_activeProfileCharacterSelections;
static int selectedKind;
static struct TableFrontendMarkLinkedTrialsAvailable *Achieve_CopyPreset(void *bits, int category, int kind) {
    assert(bits == 0 && category == 0);
    selectedKind = kind;
    return &preset;
}
static int Defs_TestBit(void *bits, int index) { assert(0); return 0; }
static void Defs_SetBitValue(void *bits, int index, int value) { assert(0); }
'''
harness += text[start:end]
harness += r'''
int main(void) {
    g_activeProfileCharacterSelections = 0xff;
    Results_MarkLinkedTrialsAvailable(0);
    assert(selectedKind == -1);
    g_activeProfileCharacterSelections = 7;
    Results_MarkLinkedTrialsAvailable(0);
    assert(selectedKind == 7);
}
'''
# The production address carrier is 32-bit; use native pointer width in the host harness.
harness = harness.replace("unsigned int category;", "uintptr_t category;")
with tempfile.TemporaryDirectory(dir=sys.argv[1]) as directory:
    binary = pathlib.Path(directory) / "linked-trial-character"
    subprocess.run(["cc", "-std=c99", "-Wall", "-Werror", "-x", "c", "-", "-o", str(binary)], input=harness, text=True, check=True)
    subprocess.run([str(binary)], check=True)
print("PASS linked-trial character: 0xff is -1; ordinary character 7 is preserved")
