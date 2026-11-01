#include "TYPES.H"

#include "include_asm.h"

/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
#if defined(VERSION_DE)
int g_FrontendAdvancevideomodeWords1[2] = {
    3, 3
};
#endif
#if defined(VERSION_EU)
int g_FrontendAdvancevideomodeWords1[2] = {
    3, 3
};
#endif
#if defined(VERSION_EU_X)
int g_FrontendAdvancevideomodeWords1[2] = {
    3, 3
};
#endif
#if defined(VERSION_US)
int g_FrontendAdvancevideomodeWords1[2] = {
    3, 3
};
#endif
#if defined(VERSION_US_REV1)
int g_FrontendAdvancevideomodeWords1[2] = {
    3, 3
};
#endif

#if defined(VERSION_US)
#if defined(VERSION_US)
struct {
    s32 regionModes[35];
    s32 defaultModes[35];
    s32 renderConfigs[15];
    u32 modeIds[24];
    s32 modeCount;
} g_frontendAdvanceVideoModeWordsUs __attribute__((aligned(4))) = {
    { 284, 222, 97, 62, -127, -89, 1, 480, 360, 29, 18, -41, -32, 0, 480, 240, 27, 14, -45, -30, 0, 380, 200, 60, 30, -85, -50, 1, 0, 0, 0, 0, 0, 0, 0 },
    { 284, 222, 97, 62, -127, -89, 1, 480, 360, 25, 55, -47, -60, 0, 480, 240, 26, 30, -45, -50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0x0, 0x1, 0x2, 0x3, 0x8, 0x9, 0xa, 0xb, 0xe, 0xf, 0x10, 0x11, 0x16, 0x17, 0x18, 0x19, 0x1c, 0x1d, 0x1e, 0x1f, 0x24, 0x25, 0x26, 0x27 },
    983050
};
typedef char g_frontendAdvanceVideoModeWordsUsSizeCheck[(sizeof(g_frontendAdvanceVideoModeWordsUs) == 440) ? 1 : -1];
#endif
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU)
struct {
    s32 regionModes[35];
    s32 defaultModes[35];
    s32 renderConfigs[15];
    u32 modeIds[24];
    s32 modeCount;
} g_frontendAdvanceVideoModeWordsEu __attribute__((aligned(4))) = {
    { 284, 222, 97, 62, -127, -89, 1, 480, 360, 29, 18, -41, -32, 0, 480, 240, 27, 14, -45, -30, 0, 380, 200, 60, 30, -85, -50, 1, 0, 0, 0, 0, 0, 0, 0 },
    { 284, 222, 97, 62, -127, -89, 1, 480, 360, 25, 55, -47, -60, 0, 480, 240, 26, 30, -45, -50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0x0, 0x1, 0x2, 0x3, 0x8, 0x9, 0xa, 0xb, 0xe, 0xf, 0x10, 0x11, 0x16, 0x17, 0x18, 0x19, 0x1c, 0x1d, 0x1e, 0x1f, 0x24, 0x25, 0x26, 0x27 },
    0
};
typedef char g_frontendAdvanceVideoModeWordsEuSizeCheck[(sizeof(g_frontendAdvanceVideoModeWordsEu) == 440) ? 1 : -1];
#endif
#if defined(VERSION_EU_X)
struct {
    s32 regionModes[35];
    s32 defaultModes[35];
    s32 renderConfigs[15];
    u32 modeIds[24];
    s32 modeCount;
} g_frontendAdvanceVideoModeWordsEu __attribute__((aligned(4))) = {
    { 284, 222, 97, 62, -127, -89, 1, 480, 360, 29, 18, -41, -32, 0, 480, 240, 27, 14, -45, -30, 0, 380, 200, 60, 30, -85, -50, 1, 0, 0, 0, 0, 0, 0, 0 },
    { 284, 222, 97, 62, -127, -89, 1, 480, 360, 25, 55, -47, -60, 0, 480, 240, 26, 30, -45, -50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0x0, 0x1, 0x2, 0x3, 0x8, 0x9, 0xa, 0xb, 0xe, 0xf, 0x10, 0x11, 0x16, 0x17, 0x18, 0x19, 0x1c, 0x1d, 0x1e, 0x1f, 0x24, 0x25, 0x26, 0x27 },
    0
};
typedef char g_frontendAdvanceVideoModeWordsEuSizeCheck[(sizeof(g_frontendAdvanceVideoModeWordsEu) == 440) ? 1 : -1];
#endif
#endif

#if defined(VERSION_DE)
#if defined(VERSION_DE)
struct {
    s32 regionModes[35];
    s32 defaultModes[35];
    s32 renderConfigs[15];
    u32 modeIds[24];
    s32 modeCount;
} g_frontendAdvanceVideoModeWordsDe __attribute__((aligned(4))) = {
    { 284, 222, 97, 62, -127, -89, 1, 480, 360, 29, 18, -41, -32, 0, 480, 240, 27, 14, -45, -30, 0, 380, 200, 60, 30, -85, -50, 1, 0, 0, 0, 0, 0, 0, 0 },
    { 284, 222, 97, 62, -127, -89, 1, 480, 360, 25, 55, -47, -60, 0, 480, 240, 26, 30, -45, -50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0x0, 0x1, 0x2, 0x3, 0x8, 0x9, 0xa, 0xb, 0xe, 0xf, 0x10, 0x11, 0x16, 0x17, 0x18, 0x19, 0x1c, 0x1d, 0x1e, 0x1f, 0x24, 0x25, 0x26, 0x27 },
    -1
};
typedef char g_frontendAdvanceVideoModeWordsDeSizeCheck[(sizeof(g_frontendAdvanceVideoModeWordsDe) == 440) ? 1 : -1];
#endif
#endif
