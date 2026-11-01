#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"
#include "TYPES.H"


/* ROM-grounded data: rodata/writable/800E2AB0 */
#ifdef VERSION_DE
extern char g_node_SelectPreviousGridRowEntry[];
#if defined(VERSION_DE)
struct {
    s32 g_frontendViewportWidth;
    s32 g_frontendViewportHeight;
    s32 g_frontendRenderStateInitialized;
    s32 g_widgetTextBatchMode;
    s32 g_frontendWidgetStateChanged;
    s32 g_frontendArchiveResident;
    u8 alignmentFill24[8];
} g_NodeSetdisplayclipboundsPointerWords1 __attribute__((aligned(4))) = {
    1,
    1,
    0,
    -1,
    0,
    0,
    { 0x0, 0x41, 0x2b, 0x78, 0x0, 0x0, 0x0, 0x6 }
};
typedef char g_NodeSetdisplayclipboundsPointerWords1SizeCheck[(sizeof(g_NodeSetdisplayclipboundsPointerWords1) == 32) ? 1 : -1];
#endif
#endif
#ifdef VERSION_EU
#if defined(VERSION_EU)
struct {
    s32 g_frontendViewportWidth;
    s32 g_frontendViewportHeight;
    s32 g_frontendRenderStateInitialized;
    s32 g_widgetTextBatchMode;
    s32 g_frontendWidgetStateChanged;
    s32 g_frontendArchiveResident;
    u8 alignmentFill24[8];
} g_NodeSetdisplayclipboundsPointerWords1 __attribute__((aligned(4))) = {
    1,
    1,
    0,
    -1,
    0,
    0,
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }
};
typedef char g_NodeSetdisplayclipboundsPointerWords1SizeCheck[(sizeof(g_NodeSetdisplayclipboundsPointerWords1) == 32) ? 1 : -1];
#endif
#endif
#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
#if defined(VERSION_EU_X)
struct {
    s32 g_frontendViewportWidth;
    s32 g_frontendViewportHeight;
    s32 g_frontendRenderStateInitialized;
    s32 g_widgetTextBatchMode;
    s32 g_frontendWidgetStateChanged;
    s32 g_frontendArchiveResident;
    u8 alignmentFill24[8];
} g_NodeSetdisplayclipboundsPointerWords1 __attribute__((aligned(4))) = {
    1,
    1,
    0,
    -1,
    0,
    0,
    { 0x0, 0x0, 0x0, 0x16, 0x3d, 0xe1, 0x47, 0xae }
};
typedef char g_NodeSetdisplayclipboundsPointerWords1SizeCheck[(sizeof(g_NodeSetdisplayclipboundsPointerWords1) == 32) ? 1 : -1];
#endif
#if defined(VERSION_US_REV1)
struct {
    s32 g_frontendViewportWidth;
    s32 g_frontendViewportHeight;
    s32 g_frontendRenderStateInitialized;
    s32 g_widgetTextBatchMode;
    s32 g_frontendWidgetStateChanged;
    s32 g_frontendArchiveResident;
    u8 alignmentFill24[8];
} g_NodeSetdisplayclipboundsPointerWords1 __attribute__((aligned(4))) = {
    1,
    1,
    0,
    -1,
    0,
    0,
    { 0x0, 0x0, 0x0, 0x16, 0x3d, 0xe1, 0x47, 0xae }
};
typedef char g_NodeSetdisplayclipboundsPointerWords1SizeCheck[(sizeof(g_NodeSetdisplayclipboundsPointerWords1) == 32) ? 1 : -1];
#endif
#endif
#ifdef VERSION_US
#if defined(VERSION_US)
struct {
    s32 g_frontendViewportWidth;
    s32 g_frontendViewportHeight;
    s32 g_frontendRenderStateInitialized;
    s32 g_widgetTextBatchMode;
    s32 g_frontendWidgetStateChanged;
    s32 g_frontendArchiveResident;
    u8 alignmentFill24[8];
} g_NodeSetdisplayclipboundsPointerWords1 __attribute__((aligned(4))) = {
    1,
    1,
    0,
    -1,
    0,
    0,
    { 0x4e, 0x54, 0x5f, 0x53, 0x4d, 0x41, 0x4c, 0x4c }
};
typedef char g_NodeSetdisplayclipboundsPointerWords1SizeCheck[(sizeof(g_NodeSetdisplayclipboundsPointerWords1) == 32) ? 1 : -1];
#endif
#endif
