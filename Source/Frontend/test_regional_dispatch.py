"""Compile the regional dispatchers with mocked table and actor seams."""
import pathlib
import subprocess
import sys
import tempfile

root = pathlib.Path(__file__).resolve().parents[2]
functions = []
for path, name in [("Source/Frontend/match.cpp", "Frontend_DispatchMatchMenuEvent"),
                   ("Source/Frontend/match.cpp", "Match_DispatchEuxMatchMenuEvent"),
                   ("Source/Menu/extraoptions.cpp", "Menu_DispatchExtraOptionsEvent")]:
    text = (root / path).read_text()
    start = text.index("s32 " + name + "(")
    end = text.index("\n}\n", start) + 3
    functions.append(text[start:end])
harness = r'''
#include <assert.h>
typedef int s32;
typedef struct { int resource; } MenuWidget;
typedef int (*Handler)(void *, int, int, int, int);
typedef struct { int event, actorKind; Handler handler; } ResidentEventHandlerEntry;
#define ANY_ACTOR_KIND 30000
ResidentEventHandlerEntry g_matchMenuEventIds[4], g_extraOptionsEventCodes[4];
static int calls;
static int handle(void *actor, int event, int a, int b, int c) {
    assert(((MenuWidget *)actor)->resource == 7);
    assert(event == 42 && a == 3 && b == 4 && c == 5);
    ++calls;
    return 91;
}
'''
harness += "\n".join(functions)
harness += r'''
int main(void) {
    MenuWidget actor = {7};
    Handler dispatchers[] = {Frontend_DispatchMatchMenuEvent,
        Match_DispatchEuxMatchMenuEvent, Menu_DispatchExtraOptionsEvent};
    int i;
    for (i = 0; i < 3; ++i) {
        ResidentEventHandlerEntry *rows = i == 2 ? g_extraOptionsEventCodes : g_matchMenuEventIds;
        rows[0] = (ResidentEventHandlerEntry){0, 0, 0};
        assert(dispatchers[i](&actor,42,3,4,5) == 0);
        rows[0] = (ResidentEventHandlerEntry){41, 7, handle};
        rows[1] = (ResidentEventHandlerEntry){42, 8, handle};
        rows[2] = (ResidentEventHandlerEntry){42, ANY_ACTOR_KIND, handle};
        rows[3] = (ResidentEventHandlerEntry){0, 0, 0};
        calls = 0;
        assert(dispatchers[i](&actor,42,3,4,5) == 91 && calls == 1);
        rows[1].actorKind = 7;
        calls = 0;
        assert(dispatchers[i](&actor,42,3,4,5) == 91 && calls == 1);
        rows[1].event = rows[2].event = 0;
        assert(dispatchers[i](&actor,42,3,4,5) == 0);
    }
}
'''
with tempfile.TemporaryDirectory(dir=sys.argv[1]) as directory:
    binary = pathlib.Path(directory) / "dispatch-test"
    subprocess.run(["cc", "-std=c99", "-Wall", "-Werror", "-x", "c", "-", "-o", str(binary)], input=harness, text=True, check=True)
    subprocess.run([str(binary)], check=True)
print("PASS regional dispatch: empty, mismatch, wildcard, first match, argument forwarding")
