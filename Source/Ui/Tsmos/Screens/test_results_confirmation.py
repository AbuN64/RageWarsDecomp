"""Exercise the results prompt's shared reply through mocked menu actions."""
import pathlib
import subprocess
import sys
import tempfile

source = pathlib.Path(__file__).with_name("match_reason.cpp").read_text()
start = source.index("s32 Frontend_HandleResultsConfirmation(s32 context)")
end = source.index("\n}\n", start) + 3
harness = r'''
#include <assert.h>
typedef int s32;
struct { int value, ready; } g_selectionMessageReply;
struct Screen { int phase, buttonAddress, dirty; } screen;
struct Screen *g_matchResultBadgeScreen = &screen;
int g_selectionMessageStage, enabled, switched, handled, focused;
enum { CONFIRM_MESSAGE = 10, FALLBACK_MESSAGE = 20 };
int Node_FindWidgetByResourceId(int context, int key) { assert(context == 7); return key; }
int Widget_ListHasFlag100(int widget) { return 0; }
void Menu_SetFocusedElement(int message) { focused = message; }
void Tsmos_ActivateControllerState(void) {}
void Widget_SetWidgetFlag08(int button, int flag) { assert(button == 9); enabled = flag; }
void MarkMenuEventHandled(void) { ++handled; }
void SmXlate_SwitchScreen(int next) { switched = next; }
'''
harness += source[start:end]
harness += r'''
int main(void) {
    screen.buttonAddress = 9;
    screen.phase = 1;
    g_selectionMessageReply.value = 42;
    g_selectionMessageReply.ready = 0;
    Frontend_HandleResultsConfirmation(7);
    assert(switched == 0 && handled == 0);
    g_selectionMessageReply.ready = 1;
    g_selectionMessageStage = 1;
    Frontend_HandleResultsConfirmation(7);
    assert(g_selectionMessageReply.ready == 1 && switched == 0);
    g_selectionMessageStage = 0;
    Frontend_HandleResultsConfirmation(7);
    assert(g_selectionMessageReply.ready == 0 && switched == 42 && handled == 1 && enabled == 0);
    g_selectionMessageReply.value = -1;
    g_selectionMessageReply.ready = 1;
    Frontend_HandleResultsConfirmation(7);
    assert(g_selectionMessageReply.ready == 0 && enabled == 1 && screen.dirty == 1);
    assert(switched == 42 && handled == 1);
    screen.phase = 0;
    Frontend_HandleResultsConfirmation(7);
    assert(screen.phase == 1 && focused == CONFIRM_MESSAGE);
}
'''
with tempfile.TemporaryDirectory(dir=sys.argv[1]) as directory:
    binary = pathlib.Path(directory) / "results-confirmation-test"
    subprocess.run(["cc", "-std=c99", "-Wall", "-Werror", "-x", "c", "-", "-o", str(binary)], input=harness, text=True, check=True)
    subprocess.run([str(binary)], check=True)
print("PASS results confirmation: no reply, inactive stage, selected screen, cancelled choice, prompt initialization")
