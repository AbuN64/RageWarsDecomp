"""Run the real status routine against scripted Controller Pak responses.

Usage: python3 Source/Menu/Pak/test_note_status.py <scratch-directory>
"""
from pathlib import Path
import subprocess
import sys
import tempfile

source = Path(__file__).with_name("note.cpp").read_text()
start = source.index("s32 Note_UpdateStatus(")
end = source.index("\n}", start) + 2
routine = source[start:end]
harness = r'''
#include <assert.h>
#include <stdio.h>
typedef int s32;
typedef struct { int channel; } OSPfs;
static OSPfs files[4];
static unsigned char g_controllerReadStatusBytes[16];
static int g_controllerPakChannelStatuses[4], g_controllerPakChannelStates[4];
static void *g_controllerSiMessageQueue;
static int responses[4], calls, refreshCalls, refreshResult;
static void *pak27_noteCreateandwritenote(int ch) { return &files[ch]; }
static int osPfsInitPak(void *queue, void *file, int ch) {
    assert(queue == g_controllerSiMessageQueue && file == &files[ch]);
    assert(calls < 4);
    return responses[calls++];
}
static int Note_RefreshNotes(int ch) { assert(ch >= 0 && ch < 4); refreshCalls++; return refreshResult; }
'''
checks = r'''
int main(void) {
    const int codes[] = {0, 1, 2, 4, 10, 11, 99};
    const int mapped[] = {-5, -2, -5, -3, -4, -3, 17};
    int sequence, ch, disconnected, badRefresh, tests = 0;
    for (sequence = 0; sequence < 2401; sequence++)
    for (ch = 0; ch < 4; ch++)
    for (disconnected = 0; disconnected < 2; disconnected++)
    for (badRefresh = 0; badRefresh < 2; badRefresh++) {
        int n = sequence, i, expected = 17, attempts = 0, ready = 0;
        for (i = 0; i < 4; i++) { responses[i] = codes[n % 7]; n /= 7; }
        for (i = 0; i < 4; i++) { g_controllerPakChannelStatuses[i] = 17; g_controllerPakChannelStates[i] = 9; g_controllerReadStatusBytes[i * 4] = 0; }
        g_controllerReadStatusBytes[ch * 4] = disconnected;
        calls = refreshCalls = 0; refreshResult = badRefresh;
        if (disconnected) expected = -2;
        else {
            n = sequence;
            for (i = 0; i < 4; i++) {
                int code = n % 7; n /= 7; attempts++;
                if (code != 6) expected = mapped[code];
                if (expected == -5) { ready = 1; expected = badRefresh ? -4 : 0; break; }
                if (expected == -2) break;
            }
        }
        assert(Note_UpdateStatus(ch) == (expected == 0 || expected == -4));
        assert(g_controllerPakChannelStatuses[ch] == expected);
        assert(calls == attempts && refreshCalls == ready);
        assert(g_controllerPakChannelStates[ch] == (ready ? 3 : 9));
        for (i = 0; i < 4; i++) if (i != ch) { assert(g_controllerPakChannelStatuses[i] == 17); assert(g_controllerPakChannelStates[i] == 9); }
        tests++;
    }
    printf("note status passed %d scripted retry, disconnect and refresh scenarios\n", tests);
    return 0;
}
'''
with tempfile.TemporaryDirectory(dir=sys.argv[1]) as scratch:
    path = Path(scratch)
    (path / "status.c").write_text(harness + routine + checks)
    subprocess.run(["cc", "-O2", str(path / "status.c"), "-o", str(path / "status")], check=True)
    subprocess.run([str(path / "status")], check=True)
