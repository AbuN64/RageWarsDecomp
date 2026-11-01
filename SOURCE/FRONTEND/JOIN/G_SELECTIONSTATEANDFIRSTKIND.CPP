#include "TYPES.H"
#if defined(VERSION_EU)
struct {
    void * screen;
    s32 firstKind;
} g_selectionStateAndFirstKind __attribute__((aligned(4))) = {
    0,
    146
};
typedef char g_selectionStateAndFirstKindSizeCheck[(sizeof(g_selectionStateAndFirstKind) == 8) ? 1 : -1];
#endif
#if defined(VERSION_EU_X)
struct {
    void * screen;
    s32 firstKind;
} g_selectionStateAndFirstKind __attribute__((aligned(4))) = {
    0,
    150
};
typedef char g_selectionStateAndFirstKindSizeCheck[(sizeof(g_selectionStateAndFirstKind) == 8) ? 1 : -1];
#endif
#if defined(VERSION_US)
struct {
    void * screen;
    s32 firstKind;
} g_selectionStateAndFirstKind __attribute__((aligned(4))) = {
    0,
    146
};
typedef char g_selectionStateAndFirstKindSizeCheck[(sizeof(g_selectionStateAndFirstKind) == 8) ? 1 : -1];
#endif
