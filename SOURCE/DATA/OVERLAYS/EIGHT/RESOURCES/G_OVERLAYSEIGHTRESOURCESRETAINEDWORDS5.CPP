#include "TYPES.H"


#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
struct {
    s32 previousReservedWord;
    s32 modeParameters[7];
    s32 lastModeParameters[7];
} g_OverlaysEightResourcesRetainedWords5 __attribute__((aligned(4))) = {
    0,
    { 380, 200, 60, 30, -85, -50, 1 },
    { 0, 0, 0, 0, 0, 0, 0 }
};
typedef char g_OverlaysEightResourcesRetainedWords5SizeCheck[(sizeof(g_OverlaysEightResourcesRetainedWords5) == 60) ? 1 : -1];
#endif
#endif
