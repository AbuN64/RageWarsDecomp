#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"
#include "TYPES.H"

#include "include_asm.h"

#if defined(VERSION_DE)
struct {
    s32 sectionCount;
    s32 delayLength;
    s32 sections[48];
} g_OverlaysSevenConstantsRetainedWords19 __attribute__((aligned(4))) = {
    6,
    4800,
    { 160, 944, 9830, -9830, 2815, 0, 0, 16383, 416, 768, 13107, -13107, 0, 0, 0, 0, 784, 912, 19660, -19660, 0, 0, 0, 0, 1664, 2864, 13107, -13107, 2719, 0, 0, 16383, 1984, 2496, 14107, -14107, 0, 0, 0, 0, 64, 4592, 19384, 0, 20479, 0, 0, 21759 }
};
typedef char g_OverlaysSevenConstantsRetainedWords19SizeCheck[(sizeof(g_OverlaysSevenConstantsRetainedWords19) == 200) ? 1 : -1];
#endif
#if defined(VERSION_EU)
struct {
    s32 sectionCount;
    s32 delayLength;
    s32 sections[48];
} g_OverlaysSevenConstantsRetainedWords19 __attribute__((aligned(4))) = {
    6,
    4800,
    { 160, 944, 9830, -9830, 2815, 0, 0, 16383, 416, 768, 13107, -13107, 0, 0, 0, 0, 784, 912, 19660, -19660, 0, 0, 0, 0, 1664, 2864, 13107, -13107, 2719, 0, 0, 16383, 1984, 2496, 14107, -14107, 0, 0, 0, 0, 64, 4592, 19384, 0, 20479, 0, 0, 21759 }
};
typedef char g_OverlaysSevenConstantsRetainedWords19SizeCheck[(sizeof(g_OverlaysSevenConstantsRetainedWords19) == 200) ? 1 : -1];
#endif
#if defined(VERSION_EU_X)
struct {
    s32 sectionCount;
    s32 delayLength;
    s32 sections[48];
} g_OverlaysSevenConstantsRetainedWords19 __attribute__((aligned(4))) = {
    6,
    4800,
    { 160, 944, 9830, -9830, 2815, 0, 0, 16383, 416, 768, 13107, -13107, 0, 0, 0, 0, 784, 912, 19660, -19660, 0, 0, 0, 0, 1664, 2864, 13107, -13107, 2719, 0, 0, 16383, 1984, 2496, 14107, -14107, 0, 0, 0, 0, 64, 4592, 19384, 0, 20479, 0, 0, 21759 }
};
typedef char g_OverlaysSevenConstantsRetainedWords19SizeCheck[(sizeof(g_OverlaysSevenConstantsRetainedWords19) == 200) ? 1 : -1];
#endif
#if defined(VERSION_US)
struct {
    s32 sectionCount;
    s32 delayLength;
    s32 sections[48];
} g_OverlaysSevenConstantsRetainedWords19 __attribute__((aligned(4))) = {
    6,
    4800,
    { 160, 944, 9830, -9830, 2815, 0, 0, 16383, 416, 768, 13107, -13107, 0, 0, 0, 0, 784, 912, 19660, -19660, 0, 0, 0, 0, 1664, 2864, 13107, -13107, 2719, 0, 0, 16383, 1984, 2496, 14107, -14107, 0, 0, 0, 0, 64, 4592, 19384, 0, 20479, 0, 0, 21759 }
};
typedef char g_OverlaysSevenConstantsRetainedWords19SizeCheck[(sizeof(g_OverlaysSevenConstantsRetainedWords19) == 200) ? 1 : -1];
#endif
#if defined(VERSION_US_REV1)
struct {
    s32 sectionCount;
    s32 delayLength;
    s32 sections[48];
} g_OverlaysSevenConstantsRetainedWords19 __attribute__((aligned(4))) = {
    6,
    4800,
    { 160, 944, 9830, -9830, 2815, 0, 0, 16383, 416, 768, 13107, -13107, 0, 0, 0, 0, 784, 912, 19660, -19660, 0, 0, 0, 0, 1664, 2864, 13107, -13107, 2719, 0, 0, 16383, 1984, 2496, 14107, -14107, 0, 0, 0, 0, 64, 4592, 19384, 0, 20479, 0, 0, 21759 }
};
typedef char g_OverlaysSevenConstantsRetainedWords19SizeCheck[(sizeof(g_OverlaysSevenConstantsRetainedWords19) == 200) ? 1 : -1];
#endif

#if defined(VERSION_US)
#if defined(VERSION_US)
struct {
    u8 alignmentFill0[4];
    u32 g_soundVolumeScales[62];
} g_overlaysSevenScaleFactorWords_us __attribute__((aligned(4))) = {
    { 0x55, 0x4e, 0x52, 0x45 },
    { 0x3f800000, 0x3f59999a, 0x3f800000, 0x3f59999a, 0x3f800000, 0x3f59999a, 0x3f800000, 0x3f666666, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f666666, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000 }
};
typedef char g_overlaysSevenScaleFactorWords_usSizeCheck[(sizeof(g_overlaysSevenScaleFactorWords_us) == 252) ? 1 : -1];
#endif
#endif

#if defined(VERSION_EU_X)
float g_overlaysSevenScaleFactorWords_eu_x[63] = {
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

#if defined(VERSION_EU)
float g_overlaysSevenScaleFactorWords_eu[63] = {
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

#if defined(VERSION_DE)
float g_overlaysSevenScaleFactorWords_de[63] = {
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
