#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"
#include "TYPES.H"

#include "include_asm.h"

/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
#if defined(VERSION_DE)
s32 g_createDataZeroWords = 0;
#endif
#if defined(VERSION_EU)
s32 g_createDataZeroWords = 0;
#endif
#if defined(VERSION_EU_X)
s32 g_createDataZeroWords = 0;
#endif
#if defined(VERSION_US)
s32 g_createDataZeroWords = 0;
#endif
#if defined(VERSION_US_REV1)
s32 g_createDataZeroWords = 0;
#endif

#if defined(VERSION_US)
char g_createDataTextFragment_us[28] =
    "REBORN_PLANT\000\000\000\000LAGequR\000\000\365\024\000";
#endif

#if defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
struct {
    u8 alignmentFill0[12];
    s32 g_serialInterfaceAccessQueueInitialized;
    u8 alignmentFill16[12];
} g_createDataOffsetTable_eu_x __attribute__((aligned(2))) = {
    { 0x80, 0x0, 0x0, 0x0, 0x0, 0x4, 0x0, 0x8, 0x0, 0xc, 0x0, 0x12 },
    0,
    { 0x0, 0x2c, 0x0, 0x35, 0x0, 0x3f, 0x0, 0x4b, 0x0, 0x59, 0x0, 0x69 }
};
typedef char g_createDataOffsetTable_eu_xSizeCheck[(sizeof(g_createDataOffsetTable_eu_x) == 28) ? 1 : -1];
#endif
#endif
#endif

#if defined(VERSION_EU)
char g_createDataTextFragment_eu[28] =
    "mantids\000warp\000\000\000\000rimagen's li";
#endif

#if defined(VERSION_DE)
float g_createDataUnitRangeWords_de[7] = {
    0.999999f, -0.999999f, 1.0f, 0.0f, 0.0f, 0.0f,
    0.0f,
};
#endif
