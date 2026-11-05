#if defined(VERSION_EU_X)

#include "types.h"


#include "include_asm.h"


#include "Common/format.h"


#include "Data/Overlays/Menu/resources_addresses.h"


#include "Common/resident_event_handler.h"


#include "data_overlay_layouts.h"


#include "Data/Gfxdata/event_handler_code_targets.h"


#include "Data/Pixel_format/g_pixelformatdescriptors.h"


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
#endif
