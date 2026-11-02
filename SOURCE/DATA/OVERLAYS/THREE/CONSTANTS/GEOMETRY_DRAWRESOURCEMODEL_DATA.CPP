#include "include_asm.h"
#include "TYPES.H"

#if defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
struct {
    u32 renderModesAndFlags[12];
    s32 fillEnabled;
    f32 fillRed;
    f32 fillGreen;
    f32 fillBlue;
    f32 fillAlpha;
    f32 fillTargetAlpha;
    u8 primitiveOverride[6];
    u8 alignmentFill[2];
} g_geometryDrawResourceModelWritableWords_eu_x __attribute__((aligned(4))) = {
    { 0xffffffff, 0xffffffff, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x10000, 0xc4000000, 0xc8000000 },
    0,
    255.0f,
    255.0f,
    255.0f,
    255.0f,
    255.0f,
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
    { 0x0, 0x0 }
};
typedef char g_geometryDrawResourceModelWritableWords_eu_xSizeCheck[(sizeof(g_geometryDrawResourceModelWritableWords_eu_x) == 80) ? 1 : -1];
#endif
#endif

#if defined(VERSION_EU_X)
#if defined(VERSION_EU_X)
unsigned short k_GeometryDrawresourcemodelEncodedHalfwordsBlock1[8] = {
    0xA000, 0x0000, 0xA000, 0x0000, 0x00FF, 0x0000, 0x00FF, 0x0000,
};
#endif
#endif
