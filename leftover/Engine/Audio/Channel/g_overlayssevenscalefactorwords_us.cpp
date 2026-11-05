#include "Common/format.h"
#include "Common/resident_event_handler.h"
#include "data_overlay_layouts.h"
#include "types.h"
#include "include_asm.h"
#include "Channel/lookuppanvalue.h"

#if defined(VERSION_DE)
float g_overlaysSevenScaleFactorWords_de_de_CC3EC[63] = {
    0.85f, 1.0f, 0.85f, 1.0f, 0.85f, 1.0f,
    0.85f, 1.0f, 0.9f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 0.9f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
};
#endif

#if defined(VERSION_EU)
float g_overlaysSevenScaleFactorWords_eu_eu_CCFCC[63] = {
    816277.25f, 1.0f, 0.85f, 1.0f, 0.85f, 1.0f,
    0.85f, 1.0f, 0.9f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 0.9f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
};
#endif

#if defined(VERSION_EU_X)
float g_overlaysSevenScaleFactorWords_eu_x_eux_CD99C[63] = {
    1.313823f, 1.0f, 0.85f, 1.0f, 0.85f, 1.0f,
    0.85f, 1.0f, 0.9f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 0.9f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
};
#endif

#if defined(VERSION_US)
struct {
    u8 retainedUnreText[4];
    u32 g_soundVolumeScales[62];
} g_overlaysSevenScaleFactorWords_us __attribute__((aligned(4))) = {
    { 0x55, 0x4e, 0x52, 0x45 },
    { 0x3f800000, 0x3f59999a, 0x3f800000, 0x3f59999a, 0x3f800000, 0x3f59999a, 0x3f800000, 0x3f666666, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f666666, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000 }
};
typedef char g_overlaysSevenScaleFactorWords_usSizeCheck[(sizeof(g_overlaysSevenScaleFactorWords_us) == 252) ? 1 : -1];
#endif
