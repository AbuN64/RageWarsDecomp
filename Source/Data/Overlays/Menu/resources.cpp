#include "types.h"
#include "include_asm.h"
#include "Common/format.h"
#include "Data/Overlays/Menu/resources_addresses.h"
#include "Common/resident_event_handler.h"
#include "data_overlay_layouts.h"
#include "Data/Gfxdata/event_handler_code_targets.h"
#include "Data/Pixel_format/g_pixelformatdescriptors.h"

/* FRONTEND_UPDATESCREENMODE_DATA.CPP */
#if defined(VERSION_DE)
int g_frontendUpdateScreenModeData = -1;
#endif
#if defined(VERSION_EU)
int g_frontendUpdateScreenModeData = -1;
#endif
#if defined(VERSION_EU_X)
int g_frontendUpdateScreenModeData = -1;
#endif
#if defined(VERSION_US)
int g_frontendUpdateScreenModeData = -1;
#endif
#if defined(VERSION_US_REV1)
int g_frontendUpdateScreenModeData = -1;
#endif

/* FRONTEND_ADVANCEVIDEOMODE_DATA.CPP */
#if defined(VERSION_DE)
int g_frontendAdvanceVideoModeData[2] = {
    3, 3
};
#endif
#if defined(VERSION_EU)
int g_frontendAdvanceVideoModeData[2] = {
    3, 3
};
#endif
#if defined(VERSION_EU_X)
int g_frontendAdvanceVideoModeData[2] = {
    3, 3
};
#endif
#if defined(VERSION_US)
int g_frontendAdvanceVideoModeData[2] = {
    3, 3
};
#endif
#if defined(VERSION_US_REV1)
int g_frontendAdvanceVideoModeData[2] = {
    3, 3
};
#endif

#if defined(VERSION_US)
struct {
    s32 regionModes[35];
    s32 defaultModes[35];
    s32 renderConfigs[15];
    u32 modeIds[24];
    s32 modeCount;
} g_frontendAdvanceVideoModeWordsUs __attribute__((aligned(4))) = {
    { 284, 222, 97, 62, -127, -89, 1, 480, 360, 29, 18, -41, -32, 0, 480, 240, 27, 14, -45, -30, 0, 380, 200, 60, 30,
    -85, -50, 1, 0, 0, 0, 0, 0, 0, 0 },
    { 284, 222, 97, 62, -127, -89, 1, 480, 360, 25, 55, -47, -60, 0, 480, 240, 26, 30, -45, -50, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0x0, 0x1, 0x2, 0x3, 0x8, 0x9, 0xa, 0xb, 0xe, 0xf, 0x10, 0x11, 0x16, 0x17, 0x18, 0x19, 0x1c, 0x1d, 0x1e, 0x1f,
    0x24, 0x25, 0x26, 0x27 },
    983050
};
typedef char g_frontendAdvanceVideoModeWordsUsSizeCheck[(sizeof(g_frontendAdvanceVideoModeWordsUs) == 440) ? 1 : -1];
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
    { 284, 222, 97, 62, -127, -89, 1, 480, 360, 29, 18, -41, -32, 0, 480, 240, 27, 14, -45, -30, 0, 380, 200, 60, 30,
    -85, -50, 1, 0, 0, 0, 0, 0, 0, 0 },
    { 284, 222, 97, 62, -127, -89, 1, 480, 360, 25, 55, -47, -60, 0, 480, 240, 26, 30, -45, -50, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0x0, 0x1, 0x2, 0x3, 0x8, 0x9, 0xa, 0xb, 0xe, 0xf, 0x10, 0x11, 0x16, 0x17, 0x18, 0x19, 0x1c, 0x1d, 0x1e, 0x1f,
    0x24, 0x25, 0x26, 0x27 },
    0
};
typedef char g_frontendAdvanceVideoModeWordsEuSizeCheck[(sizeof(g_frontendAdvanceVideoModeWordsEu) == 440) ? 1 : -1];
#endif
#if defined(VERSION_EU_X)
extern struct {
    s32 regionModes[35];
    s32 defaultModes[35];
    s32 renderConfigs[15];
    u32 modeIds[24];
    s32 modeCount;
} g_frontendAdvanceVideoModeWordsEu __attribute__((aligned(4)));
typedef char g_frontendAdvanceVideoModeWordsEuSizeCheck[(sizeof(g_frontendAdvanceVideoModeWordsEu) == 440) ? 1 : -1];
#endif
#endif

#if defined(VERSION_DE)
struct {
    s32 regionModes[35];
    s32 defaultModes[35];
    s32 renderConfigs[15];
    u32 modeIds[24];
    s32 modeCount;
} g_frontendAdvanceVideoModeWordsDe __attribute__((aligned(4))) = {
    { 284, 222, 97, 62, -127, -89, 1, 480, 360, 29, 18, -41, -32, 0, 480, 240, 27, 14, -45, -30, 0, 380, 200, 60, 30,
    -85, -50, 1, 0, 0, 0, 0, 0, 0, 0 },
    { 284, 222, 97, 62, -127, -89, 1, 480, 360, 25, 55, -47, -60, 0, 480, 240, 26, 30, -45, -50, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 },
    { 0x0, 0x1, 0x2, 0x3, 0x8, 0x9, 0xa, 0xb, 0xe, 0xf, 0x10, 0x11, 0x16, 0x17, 0x18, 0x19, 0x1c, 0x1d, 0x1e, 0x1f,
    0x24, 0x25, 0x26, 0x27 },
    -1
};
typedef char g_frontendAdvanceVideoModeWordsDeSizeCheck[(sizeof(g_frontendAdvanceVideoModeWordsDe) == 440) ? 1 : -1];
#endif

/* NODE_SETDISPLAYCLIPBOUNDS_DATA.CPP */
#ifdef VERSION_DE
struct {
    s32 g_frontendViewportWidth;
    s32 g_frontendViewportHeight;
    s32 g_frontendRenderStateInitialized;
    s32 g_widgetTextBatchMode;
    s32 g_frontendWidgetStateChanged;
    s32 g_frontendArchiveResident;
    u8 retainedHandlerWords[8];
} g_frontendRenderState __attribute__((aligned(4))) = {
    1,
    1,
    0,
    -1,
    0,
    0,
    { 0x0, 0x41, 0x2b, 0x78, 0x0, 0x0, 0x0, 0x6 }
};
typedef char g_frontendRenderStateSizeCheck[
    (sizeof(g_frontendRenderState) == 32) ? 1 : -1];
#endif
#ifdef VERSION_EU
struct {
    s32 g_frontendViewportWidth;
    s32 g_frontendViewportHeight;
    s32 g_frontendRenderStateInitialized;
    s32 g_widgetTextBatchMode;
    s32 g_frontendWidgetStateChanged;
    s32 g_frontendArchiveResident;
    u8 zeroHandlerTail[8];
} g_frontendRenderState __attribute__((aligned(4))) = {
    1,
    1,
    0,
    -1,
    0,
    0,
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }
};
typedef char g_frontendRenderStateSizeCheck[
    (sizeof(g_frontendRenderState) == 32) ? 1 : -1];
#endif
#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
#if defined(VERSION_EU_X)
extern struct {
    s32 g_frontendViewportWidth;
    s32 g_frontendViewportHeight;
    s32 g_frontendRenderStateInitialized;
    s32 g_widgetTextBatchMode;
    s32 g_frontendWidgetStateChanged;
    s32 g_frontendArchiveResident;
    u8 retainedHandlerWords[8];
} g_frontendRenderState __attribute__((aligned(4)));
typedef char g_frontendRenderStateSizeCheck[
    (sizeof(g_frontendRenderState) == 32) ? 1 : -1];
#endif
#if defined(VERSION_US_REV1)
struct {
    s32 g_frontendViewportWidth;
    s32 g_frontendViewportHeight;
    s32 g_frontendRenderStateInitialized;
    s32 g_widgetTextBatchMode;
    s32 g_frontendWidgetStateChanged;
    s32 g_frontendArchiveResident;
    u8 retainedHandlerWords[8];
} g_frontendRenderState __attribute__((aligned(4))) = {
    1,
    1,
    0,
    -1,
    0,
    0,
    { 0x0, 0x0, 0x0, 0x16, 0x3d, 0xe1, 0x47, 0xae }
};
typedef char g_frontendRenderStateSizeCheck[
    (sizeof(g_frontendRenderState) == 32) ? 1 : -1];
#endif
#endif
#ifdef VERSION_US
struct {
    s32 g_frontendViewportWidth;
    s32 g_frontendViewportHeight;
    s32 g_frontendRenderStateInitialized;
    s32 g_widgetTextBatchMode;
    s32 g_frontendWidgetStateChanged;
    s32 g_frontendArchiveResident;
    u8 retainedFontSmallText[8];
} g_frontendRenderState __attribute__((aligned(4))) = {
    1,
    1,
    0,
    -1,
    0,
    0,
    { 0x4e, 0x54, 0x5f, 0x53, 0x4d, 0x41, 0x4c, 0x4c }
};
typedef char g_frontendRenderStateSizeCheck[
    (sizeof(g_frontendRenderState) == 32) ? 1 : -1];
#endif

/* NODE_DISPATCHTYPEDWIDGETEVENT_DATA.CPP */
#if defined(VERSION_DE)
struct {
    ResidentEventHandlerEntry eventHandlers0[6];
    u8 retainedRecordWords[8];
    struct Format pixelFormats[36];
    char text1952[16];
} g_nodeDispatchTypedWidgetEventTable_de __attribute__((aligned(4))) = {
    { { 5, 30000, (ResidentEventHandler)(void *)&g_node_SelectPreviousGridRowEntry }, { 6, 30000,
    (ResidentEventHandler)(void *)&g_node_SelectNextGridRowEntry }, { 7, 30000,
    (ResidentEventHandler)(void *)&g_node_SelectPreviousGridColumnEntry }, { 8, 30000,
    (ResidentEventHandler)(void *)&g_node_SelectNextGridColumnEntry }, { 3587, 30000,
    (ResidentEventHandler)(void *)&g_node_DestroyGridListEntry }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
    { { 0, 0, 0, 0, 0, { 0x0, 0x0, 0x0, 0x0 }, { -8, -8, -8, -8 } }, { 1, 0, 16, 16, 16, { 0xf800, 0x7e0, 0x1f, 0x0 },
    { 8, 3, -3, -8 } }, { 2, 0, 16, 16, 16, { 0xf00, 0xf0, 0xf, 0xf000 }, { 4, 0, -4, 8 } }, { 3, 0, 16, 16, 16,
    { 0xf000, 0xf00, 0xf0, 0xf }, { 8, 4, 0, -4 } }, { 4, 0, 16, 16, 16, { 0x7c00, 0x3e0, 0x1f, 0x8000 }, { 7, 2, -3,
    8 } }, { 5, 0, 16, 16, 16, { 0xf800, 0x7c0, 0x3e, 0x1 }, { 8, 3, -2, -7 } }, { 6, 0, 16, 16, 15, { 0x7c00, 0x3e0,
    0x1f, 0x0 }, { 7, 2, -3, 7 } }, { 7, 0, 16, 16, 15, { 0xf800, 0x7c0, 0x3e, 0x0 }, { 8, 3, -2, -8 } }, { 8, 0, 24,
    24, 24, { 0xff0000, 0xff00, 0xff, 0x0 }, { 16, 8, 0, -8 } }, { 9, 0, 24, 24, 24, { 0xf800, 0x7e0, 0x1f, 0xff0000 },
    { 8, 3, -3, 16 } }, { 10, 0, 32, 32, 24, { 0xff000000, 0xff0000, 0xff00, 0x0 }, { 24, 16, 8, -8 } }, { 11, 0, 32,
    32, 24, { 0xff0000, 0xff00, 0xff, 0x0 }, { 16, 8, 0, 16 } }, { 12, 0, 32, 32, 32, { 0xff0000, 0xff00, 0xff,
    0xff000000 }, { 16, 8, 0, 24 } }, { 13, 0, 32, 32, 32, { 0xff000000, 0xff0000, 0xff00, 0xff }, { 24, 16, 8, 0 } },
    { 14, 1, 4, 16, 16, { 0xf800, 0x7e0, 0x1f, 0x0 }, { 8, 3, -3, -8 } }, { 15, 1, 4, 24, 24, { 0xff0000, 0xff00, 0xff,
    0x0 }, { 16, 8, 0, -8 } }, { 16, 1, 4, 32, 24, { 0xff0000, 0xff00, 0xff, 0x0 }, { 16, 8, 0, 16 } }, { 17, 1, 4, 32,
    24, { 0xff000000, 0xff0000, 0xff00, 0x0 }, { 24, 16, 8, -8 } }, { 18, 1, 4, 32, 32, { 0xff0000, 0xff00, 0xff,
    0xff000000 }, { 16, 8, 0, 24 } }, { 19, 1, 4, 32, 32, { 0xff000000, 0xff0000, 0xff00, 0xff }, { 24, 16, 8, 0 } },
    { 20, 1, 4, 16, 16, { 0xf800, 0x7c0, 0x3e, 0x1 }, { 8, 3, -2, -7 } }, { 21, 1, 4, 16, 16, { 0x7c00, 0x3e0, 0x1f,
    0x8000 }, { 7, 2, -3, 8 } }, { 22, 1, 4, 16, 15, { 0xf800, 0x7c0, 0x3e, 0x0 }, { 8, 3, -2, -8 } }, { 23, 1, 4, 16,
    15, { 0x7c00, 0x3e0, 0x1f, 0x0 }, { 7, 2, -3, 7 } }, { 24, 1, 8, 16, 16, { 0xf800, 0x7e0, 0x1f, 0x0 }, { 8, 3, -3,
    -8 } }, { 25, 1, 8, 24, 24, { 0xff0000, 0xff00, 0xff, 0x0 }, { 16, 8, 0, -8 } }, { 26, 1, 8, 32, 24, { 0xff0000,
    0xff00, 0xff, 0x0 }, { 16, 8, 0, 16 } }, { 27, 1, 8, 32, 24, { 0xff000000, 0xff0000, 0xff00, 0x0 }, { 24, 16, 8,
    -8 } }, { 28, 1, 8, 32, 32, { 0xff0000, 0xff00, 0xff, 0xff000000 }, { 16, 8, 0, 24 } }, { 29, 1, 8, 32, 32,
    { 0xff000000, 0xff0000, 0xff00, 0xff }, { 24, 16, 8, 0 } }, { 30, 1, 8, 16, 16, { 0xf800, 0x7c0, 0x3e, 0x1 }, { 8,
    3, -2, -7 } }, { 31, 1, 8, 16, 16, { 0x7c00, 0x3e0, 0x1f, 0x8000 }, { 7, 2, -3, 8 } }, { 32, 1, 8, 16, 15, { 0xf800,
    0x7c0, 0x3e, 0x0 }, { 8, 3, -2, -8 } }, { 33, 1, 8, 16, 15, { 0x7c00, 0x3e0, 0x1f, 0x0 }, { 7, 2, -3, 7 } }, { 34,
    0, 4, 4, 4, { 0xf, 0x0, 0x0, 0x0 }, { -4, -8, -8, -8 } }, { 35, 0, 8, 8, 8, { 0xff, 0x0, 0x0, 0x0 }, { 0, -8, -8,
    -8 } } },
    "\000A\\ \000\000\000\000        "
};
typedef char g_nodeDispatchTypedWidgetEventTable_deSizeCheck[
    (sizeof(g_nodeDispatchTypedWidgetEventTable_de) == 1968) ? 1 : -1];
#endif

/* GFX_FORMATARGUMENTLIST_DATA.CPP */
#if defined(VERSION_DE)
char g_GfxFormatargumentlistBytes[36] __attribute__((aligned(1))) = "                0000000000000000\000\000\000\000";
#endif
#if defined(VERSION_EU)
char g_GfxFormatargumentlistBytes[36] __attribute__((aligned(1))) = "                0000000000000000\000\000\000\000";
#endif
#if defined(VERSION_EU_X)
char g_GfxFormatargumentlistBytes[36] __attribute__((aligned(1))) = "                0000000000000000\000\000\000\000";
#endif
#if defined(VERSION_US)
char g_GfxFormatargumentlistBytes[36] __attribute__((aligned(1))) = "                0000000000000000\000\000\000\000";
#endif
#if defined(VERSION_US_REV1)
char g_GfxFormatargumentlistBytes[36] __attribute__((aligned(1))) = "                0000000000000000\000";
#endif

/* MENU_MEASUREMENUTEXT_DATA.CPP */
#if defined(VERSION_US_REV1)
extern s32 g_hudReferenceViewportWidth;

extern s32 g_hudReferenceViewportHeight;

extern s32 g_frontendCurrentVideoModeIndex;
#endif

#if defined(VERSION_EU)
struct {
    ResidentEventHandlerEntry eventHandlers0[6];
    u8 zeroHandlerTail[8];
    struct Format pixelFormats[36];
    void * videoCallbacks[2];
    u8 retainedCallbackWords[8];
} g_gridListEventHandlerRows __attribute__((aligned(4))) = {
    { { 5, 30000, (ResidentEventHandler)(void *)&addrLow_Node_SelectPreviousGridRow }, { 6, 30000,
    (ResidentEventHandler)(void *)&addrLow_Node_SelectNextGridRow }, { 7, 30000,
    (ResidentEventHandler)(void *)&addrLow_Node_SelectPreviousGridColumn }, { 8, 30000,
    (ResidentEventHandler)(void *)&addrLow_Node_SelectNextGridColumn }, { 3587, 30000,
    (ResidentEventHandler)(void *)&addrLow_Node_DestroyGridList }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
    { { 0, 0, 0, 0, 0, { 0x0, 0x0, 0x0, 0x0 }, { -8, -8, -8, -8 } }, { 1, 0, 16, 16, 16, { 0xf800, 0x7e0, 0x1f, 0x0 },
    { 8, 3, -3, -8 } }, { 2, 0, 16, 16, 16, { 0xf00, 0xf0, 0xf, 0xf000 }, { 4, 0, -4, 8 } }, { 3, 0, 16, 16, 16,
    { 0xf000, 0xf00, 0xf0, 0xf }, { 8, 4, 0, -4 } }, { 4, 0, 16, 16, 16, { 0x7c00, 0x3e0, 0x1f, 0x8000 }, { 7, 2, -3,
    8 } }, { 5, 0, 16, 16, 16, { 0xf800, 0x7c0, 0x3e, 0x1 }, { 8, 3, -2, -7 } }, { 6, 0, 16, 16, 15, { 0x7c00, 0x3e0,
    0x1f, 0x0 }, { 7, 2, -3, 7 } }, { 7, 0, 16, 16, 15, { 0xf800, 0x7c0, 0x3e, 0x0 }, { 8, 3, -2, -8 } }, { 8, 0, 24,
    24, 24, { 0xff0000, 0xff00, 0xff, 0x0 }, { 16, 8, 0, -8 } }, { 9, 0, 24, 24, 24, { 0xf800, 0x7e0, 0x1f, 0xff0000 },
    { 8, 3, -3, 16 } }, { 10, 0, 32, 32, 24, { 0xff000000, 0xff0000, 0xff00, 0x0 }, { 24, 16, 8, -8 } }, { 11, 0, 32,
    32, 24, { 0xff0000, 0xff00, 0xff, 0x0 }, { 16, 8, 0, 16 } }, { 12, 0, 32, 32, 32, { 0xff0000, 0xff00, 0xff,
    0xff000000 }, { 16, 8, 0, 24 } }, { 13, 0, 32, 32, 32, { 0xff000000, 0xff0000, 0xff00, 0xff }, { 24, 16, 8, 0 } },
    { 14, 1, 4, 16, 16, { 0xf800, 0x7e0, 0x1f, 0x0 }, { 8, 3, -3, -8 } }, { 15, 1, 4, 24, 24, { 0xff0000, 0xff00, 0xff,
    0x0 }, { 16, 8, 0, -8 } }, { 16, 1, 4, 32, 24, { 0xff0000, 0xff00, 0xff, 0x0 }, { 16, 8, 0, 16 } }, { 17, 1, 4, 32,
    24, { 0xff000000, 0xff0000, 0xff00, 0x0 }, { 24, 16, 8, -8 } }, { 18, 1, 4, 32, 32, { 0xff0000, 0xff00, 0xff,
    0xff000000 }, { 16, 8, 0, 24 } }, { 19, 1, 4, 32, 32, { 0xff000000, 0xff0000, 0xff00, 0xff }, { 24, 16, 8, 0 } },
    { 20, 1, 4, 16, 16, { 0xf800, 0x7c0, 0x3e, 0x1 }, { 8, 3, -2, -7 } }, { 21, 1, 4, 16, 16, { 0x7c00, 0x3e0, 0x1f,
    0x8000 }, { 7, 2, -3, 8 } }, { 22, 1, 4, 16, 15, { 0xf800, 0x7c0, 0x3e, 0x0 }, { 8, 3, -2, -8 } }, { 23, 1, 4, 16,
    15, { 0x7c00, 0x3e0, 0x1f, 0x0 }, { 7, 2, -3, 7 } }, { 24, 1, 8, 16, 16, { 0xf800, 0x7e0, 0x1f, 0x0 }, { 8, 3, -3,
    -8 } }, { 25, 1, 8, 24, 24, { 0xff0000, 0xff00, 0xff, 0x0 }, { 16, 8, 0, -8 } }, { 26, 1, 8, 32, 24, { 0xff0000,
    0xff00, 0xff, 0x0 }, { 16, 8, 0, 16 } }, { 27, 1, 8, 32, 24, { 0xff000000, 0xff0000, 0xff00, 0x0 }, { 24, 16, 8,
    -8 } }, { 28, 1, 8, 32, 32, { 0xff0000, 0xff00, 0xff, 0xff000000 }, { 16, 8, 0, 24 } }, { 29, 1, 8, 32, 32,
    { 0xff000000, 0xff0000, 0xff00, 0xff }, { 24, 16, 8, 0 } }, { 30, 1, 8, 16, 16, { 0xf800, 0x7c0, 0x3e, 0x1 }, { 8,
    3, -2, -7 } }, { 31, 1, 8, 16, 16, { 0x7c00, 0x3e0, 0x1f, 0x8000 }, { 7, 2, -3, 8 } }, { 32, 1, 8, 16, 15, { 0xf800,
    0x7c0, 0x3e, 0x0 }, { 8, 3, -2, -8 } }, { 33, 1, 8, 16, 15, { 0x7c00, 0x3e0, 0x1f, 0x0 }, { 7, 2, -3, 7 } }, { 34,
    0, 4, 4, 4, { 0xf, 0x0, 0x0, 0x0 }, { -4, -8, -8, -8 } }, { 35, 0, 8, 8, 8, { 0xff, 0x0, 0x0, 0x0 }, { 0, -8, -8,
    -8 } } },
    { (void *)&addrLow_Gfx_BlinkVideoUnlessBypassed, 0 },
    { 0x31, 0x6b, 0x0, 0x3c, 0x8d, 0x6b, 0x0, 0xf8 }
};
typedef char g_gridListEventHandlerRowsSizeCheck[(sizeof(g_gridListEventHandlerRows) == 1968) ? 1 : -1];
#endif

/* G_PIXELFORMATDESCRIPTORS.CPP */
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_gridNavigationEventHandlers[6] = {
    { 5, 30000, (ResidentEventHandler)(void *)&g_selectPreviousGridRowHandlerAddress }, { 6, 30000,
    (ResidentEventHandler)(void *)&g_selectNextGridRowHandlerAddress }, { 7, 30000,
    (ResidentEventHandler)(void *)&g_selectPreviousGridColumnHandlerAddress }, { 8, 30000,
    (ResidentEventHandler)(void *)&g_selectNextGridColumnHandlerAddress }, { 3587, 30000,
    (ResidentEventHandler)(void *)&g_eventHandlerCodeTargetIdE03 }, { 0, 0, (ResidentEventHandler)0 }
};

struct {
    u8 retainedRecordWords[8];
} g_GPixelformatdescriptorsWords __attribute__((aligned(4))) = {
    { 0xC2, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
};
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
Format g_pixelFormatDescriptors[36] = {
    { 0, 0, 0, 0, 0, { 0x0, 0x0, 0x0, 0x0 }, { -8, -8, -8, -8 } },
    { 1, 0, 16, 16, 16, { 0xF800, 0x7E0, 0x1F, 0x0 }, { 8, 3, -3, -8 } },
    { 2, 0, 16, 16, 16, { 0xF00, 0xF0, 0xF, 0xF000 }, { 4, 0, -4, 8 } },
    { 3, 0, 16, 16, 16, { 0xF000, 0xF00, 0xF0, 0xF }, { 8, 4, 0, -4 } },
    { 4, 0, 16, 16, 16, { 0x7C00, 0x3E0, 0x1F, 0x8000 }, { 7, 2, -3, 8 } },
    { 5, 0, 16, 16, 16, { 0xF800, 0x7C0, 0x3E, 0x1 }, { 8, 3, -2, -7 } },
    { 6, 0, 16, 16, 15, { 0x7C00, 0x3E0, 0x1F, 0x0 }, { 7, 2, -3, 7 } },
    { 7, 0, 16, 16, 15, { 0xF800, 0x7C0, 0x3E, 0x0 }, { 8, 3, -2, -8 } },
    { 8, 0, 24, 24, 24, { 0xFF0000, 0xFF00, 0xFF, 0x0 }, { 16, 8, 0, -8 } },
    { 9, 0, 24, 24, 24, { 0xF800, 0x7E0, 0x1F, 0xFF0000 }, { 8, 3, -3, 16 } },
    { 10, 0, 32, 32, 24, { 0xFF000000, 0xFF0000, 0xFF00, 0x0 }, { 24, 16, 8, -8 } },
    { 11, 0, 32, 32, 24, { 0xFF0000, 0xFF00, 0xFF, 0x0 }, { 16, 8, 0, 16 } },
    { 12, 0, 32, 32, 32, { 0xFF0000, 0xFF00, 0xFF, 0xFF000000 }, { 16, 8, 0, 24 } },
    { 13, 0, 32, 32, 32, { 0xFF000000, 0xFF0000, 0xFF00, 0xFF }, { 24, 16, 8, 0 } },
    { 14, 1, 4, 16, 16, { 0xF800, 0x7E0, 0x1F, 0x0 }, { 8, 3, -3, -8 } },
    { 15, 1, 4, 24, 24, { 0xFF0000, 0xFF00, 0xFF, 0x0 }, { 16, 8, 0, -8 } },
    { 16, 1, 4, 32, 24, { 0xFF0000, 0xFF00, 0xFF, 0x0 }, { 16, 8, 0, 16 } },
    { 17, 1, 4, 32, 24, { 0xFF000000, 0xFF0000, 0xFF00, 0x0 }, { 24, 16, 8, -8 } },
    { 18, 1, 4, 32, 32, { 0xFF0000, 0xFF00, 0xFF, 0xFF000000 }, { 16, 8, 0, 24 } },
    { 19, 1, 4, 32, 32, { 0xFF000000, 0xFF0000, 0xFF00, 0xFF }, { 24, 16, 8, 0 } },
    { 20, 1, 4, 16, 16, { 0xF800, 0x7C0, 0x3E, 0x1 }, { 8, 3, -2, -7 } },
    { 21, 1, 4, 16, 16, { 0x7C00, 0x3E0, 0x1F, 0x8000 }, { 7, 2, -3, 8 } },
    { 22, 1, 4, 16, 15, { 0xF800, 0x7C0, 0x3E, 0x0 }, { 8, 3, -2, -8 } },
    { 23, 1, 4, 16, 15, { 0x7C00, 0x3E0, 0x1F, 0x0 }, { 7, 2, -3, 7 } },
    { 24, 1, 8, 16, 16, { 0xF800, 0x7E0, 0x1F, 0x0 }, { 8, 3, -3, -8 } },
    { 25, 1, 8, 24, 24, { 0xFF0000, 0xFF00, 0xFF, 0x0 }, { 16, 8, 0, -8 } },
    { 26, 1, 8, 32, 24, { 0xFF0000, 0xFF00, 0xFF, 0x0 }, { 16, 8, 0, 16 } },
    { 27, 1, 8, 32, 24, { 0xFF000000, 0xFF0000, 0xFF00, 0x0 }, { 24, 16, 8, -8 } },
    { 28, 1, 8, 32, 32, { 0xFF0000, 0xFF00, 0xFF, 0xFF000000 }, { 16, 8, 0, 24 } },
    { 29, 1, 8, 32, 32, { 0xFF000000, 0xFF0000, 0xFF00, 0xFF }, { 24, 16, 8, 0 } },
    { 30, 1, 8, 16, 16, { 0xF800, 0x7C0, 0x3E, 0x1 }, { 8, 3, -2, -7 } },
    { 31, 1, 8, 16, 16, { 0x7C00, 0x3E0, 0x1F, 0x8000 }, { 7, 2, -3, 8 } },
    { 32, 1, 8, 16, 15, { 0xF800, 0x7C0, 0x3E, 0x0 }, { 8, 3, -2, -8 } },
    { 33, 1, 8, 16, 15, { 0x7C00, 0x3E0, 0x1F, 0x0 }, { 7, 2, -3, 7 } },
    { 34, 0, 4, 4, 4, { 0xF, 0x0, 0x0, 0x0 }, { -4, -8, -8, -8 } },
    { 35, 0, 8, 8, 8, { 0xFF, 0x0, 0x0, 0x0 }, { 0, -8, -8, -8 } },
};
#endif

#if defined(VERSION_US)
char s_GPixelformatdescriptorsALBOWTText[16] =
    "\000A\\\240\000\000\000\000L_BOWT\000\000";
#endif

#if defined(VERSION_US_REV1)
unsigned int g_pixelFormatDescriptorPointers[4] = {
    (unsigned int)g_pixelFormatPointerWordsCodeTarget, 0x00000000, 0x00000089, 0x0000008A,
};
#endif

/* SCREEN_DATA.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 width;
    s32 viewportHeight;
    s32 offsetX;
    s32 offsetY;
    s32 borderX;
    s32 borderY;
} g_videoArgumentsR0M0 __attribute__((aligned(4))) = {
    284,
    222,
    97,
    62,
    -127,
    -89
};
#endif

/* VIDEO_ARGUMENTS_R0M1_RECORD.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 reservedWord;
} g_videoArgumentsR0M1ReservedWord __attribute__((aligned(4))) = {
    1
};
typedef char g_videoArgumentsR0M1ReservedWordSizeCheck[
    (sizeof(g_videoArgumentsR0M1ReservedWord) == 4) ? 1 : -1];

struct {
    s32 width;
    s32 viewportHeight;
    s32 offsetX;
    s32 offsetY;
    s32 borderX;
    s32 borderY;
} g_videoArgumentsR0M1 __attribute__((aligned(4))) = {
    480,
    360,
    29,
    18,
    -41,
    -32
};
#endif

/* VIDEO_ARGUMENTS_R0M2_RECORD.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 reservedWord;
} g_videoArgumentsR0M2ReservedWord __attribute__((aligned(4))) = {
    0
};
typedef char g_videoArgumentsR0M2ReservedWordSizeCheck[
    (sizeof(g_videoArgumentsR0M2ReservedWord) == 4) ? 1 : -1];

struct {
    s32 width;
    s32 viewportHeight;
    s32 offsetX;
    s32 offsetY;
    s32 borderX;
    s32 borderY;
} g_videoArgumentsR0M2 __attribute__((aligned(4))) = {
    480,
    240,
    27,
    14,
    -45,
    -30
};
#endif

/* G_VIDEOMODEPARAMETERRECORD.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 previousReservedWord;
    s32 modeParameters[7];
    s32 lastModeParameters[7];
} g_videoModeParameterRecord __attribute__((aligned(4))) = {
    0,
    { 380, 200, 60, 30, -85, -50, 1 },
    { 0, 0, 0, 0, 0, 0, 0 }
};
typedef char g_videoModeParameterRecordSizeCheck[
    (sizeof(g_videoModeParameterRecord) == 60) ? 1 : -1];
#endif

/* VIDEO_ARGUMENTS_R1M0_RECORD.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 width;
    s32 viewportHeight;
    s32 offsetX;
    s32 offsetY;
    s32 borderX;
    s32 borderY;
} g_videoArgumentsR1M0 __attribute__((aligned(4))) = {
    284,
    222,
    97,
    62,
    -127,
    -89
};
#endif

/* VIDEO_ARGUMENTS_R1M1_RECORD.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 reservedWord;
} g_videoArgumentsR1M1ReservedWord __attribute__((aligned(4))) = {
    1
};
typedef char g_videoArgumentsR1M1ReservedWordSizeCheck[
    (sizeof(g_videoArgumentsR1M1ReservedWord) == 4) ? 1 : -1];

struct {
    s32 width;
    s32 viewportHeight;
    s32 offsetX;
    s32 offsetY;
    s32 borderX;
    s32 borderY;
} g_videoArgumentsR1M1 __attribute__((aligned(4))) = {
    480,
    360,
    25,
    55,
    -47,
    -60
};
#endif

/* VIDEO_ARGUMENTS_R1M2_RECORD.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 reservedWord;
} g_videoArgumentsR1M2ReservedWord __attribute__((aligned(4))) = {
    0
};
typedef char g_videoArgumentsR1M2ReservedWordSizeCheck[
    (sizeof(g_videoArgumentsR1M2ReservedWord) == 4) ? 1 : -1];

struct {
    s32 width;
    s32 viewportHeight;
    s32 offsetX;
    s32 offsetY;
    s32 borderX;
    s32 borderY;
} g_videoArgumentsR1M2 __attribute__((aligned(4))) = {
    480,
    240,
    26,
    30,
    -45,
    -50
};
#endif

/* FRONTEND_APPLYVIDEOMODE_DATA.CPP */
#if defined(VERSION_US_REV1)
struct {
    s32 renderConfig[15];
} g_videoConfigurations __attribute__((aligned(4))) = {
    { 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 }
};
/* Video mode id per TV region (rows) and viewport flags (columns). */
unsigned int VideoModeIds[3][8] = {
    { 0x00, 0x01, 0x02, 0x03, 0x08, 0x09, 0x0A, 0x0B },
    { 0x0E, 0x0F, 0x10, 0x11, 0x16, 0x17, 0x18, 0x19 },
    { 0x1C, 0x1D, 0x1E, 0x1F, 0x24, 0x25, 0x26, 0x27 },
};
#endif
