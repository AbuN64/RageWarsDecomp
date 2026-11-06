"""Exercise stage-resource selection with unsigned level flags and mocked world lookup."""
import pathlib
import subprocess
import sys
import tempfile

source = pathlib.Path(__file__).with_name("random.cpp").read_text()
start = source.index("s32 Random_GetStageTransitionResource(void)")
end = source.index("\n}\n", start) + 3
harness = r'''
#include <assert.h>
#include <stdint.h>
typedef int32_t s32;
typedef uint16_t u16;
struct { int controllerMode; } g_gameSettings;
int g_world, g_selectedLevelId, calls;
u16 level[2];
void *Scene_GetBlLevelData(void *world, s32 selected) {
    assert(world == &g_world && selected == g_selectedLevelId);
    ++calls;
    return level;
}
'''
harness += source[start:end]
harness += r'''
int main(void) {
    g_selectedLevelId = 7;
    g_gameSettings.controllerMode = 0;
    assert(Random_GetStageTransitionResource() == 3080 && calls == 0);
    g_gameSettings.controllerMode = 1;
    level[1] = 0;
    assert(Random_GetStageTransitionResource() == 3010);
    level[1] = 0x8000;
    assert(Random_GetStageTransitionResource() == 330690);
    level[1] = 0xffff;
    assert(Random_GetStageTransitionResource() == 658360);
    assert(calls == 3);
}
'''
with tempfile.TemporaryDirectory(dir=sys.argv[1]) as directory:
    binary = pathlib.Path(directory) / "stage-transition-test"
    subprocess.run(["cc", "-std=c99", "-Wall", "-Werror", "-x", "c", "-", "-o", str(binary)], input=harness, text=True, check=True)
    subprocess.run([str(binary)], check=True)
print("PASS stage transition: direct stage, zero flag, high-bit flag, maximum flag, world lookup")
