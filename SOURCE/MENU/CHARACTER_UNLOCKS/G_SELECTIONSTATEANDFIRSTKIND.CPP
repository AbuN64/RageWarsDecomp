#include "TYPES.H"
#if defined(VERSION_US_REV1)
struct {
    void * screen;
    s32 firstKind;
} g_selectionStateAndFirstKind __attribute__((aligned(4))) = {
    0,
    146
};
typedef char g_selectionStateAndFirstKindSizeCheck[(sizeof(g_selectionStateAndFirstKind) == 8) ? 1 : -1];
#endif
