#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"
#include "TYPES.H"
#include "include_asm.h"
#ifdef VERSION_DE
#if defined(VERSION_DE)

/* 800D0D78_2.CPP */
/* ROM-grounded data: rodata/writable/800D0D90 */
struct {
    s32 g_musicRequestedTrack;
    s32 g_musicStartupFrameCount;
    u8 retainedInstructionWords[8];
} g_GAudiopitchratiocurveWords4 __attribute__((aligned(4))) = {
    0,
    0,
    { 0x3c, 0x3, 0xa4, 0x60, 0x34, 0x63, 0x0, 0x10 }
};
typedef char g_GAudiopitchratiocurveWords4SizeCheck[(sizeof(g_GAudiopitchratiocurveWords4) == 16) ? 1 : -1];
#endif
#endif
#ifdef VERSION_EU
#if defined(VERSION_EU)
char g_GAudiopitchratiocurveWords4[16] __attribute__((aligned(4))) = "\000\000\000\000\000\000\000\000DR. DON ";
#endif
#endif
#ifdef VERSION_EU_X
#if defined(VERSION_EU_X)
struct {
    s32 g_musicRequestedTrack;
    s32 g_musicStartupFrameCount;
    u8 retainedPitchRatioWords[8];
} g_GAudiopitchratiocurveWords4 __attribute__((aligned(4))) = {
    0,
    0,
    { 0x3f, 0x8a, 0xb0, 0x6c, 0x3f, 0x8a, 0x8c, 0x29 }
};
typedef char g_GAudiopitchratiocurveWords4SizeCheck[(sizeof(g_GAudiopitchratiocurveWords4) == 16) ? 1 : -1];
#endif
#endif
#ifdef VERSION_US
#if defined(VERSION_US)
struct {
    s32 g_musicRequestedTrack;
    s32 g_musicStartupFrameCount;
    u8 retainedEosTagWords[8];
} g_GAudiopitchratiocurveWords4 __attribute__((aligned(4))) = {
    0,
    0,
    { 0x65, 0x71, 0x75, 0x4, 0x2e, 0x65, 0x6f, 0x73 }
};
typedef char g_GAudiopitchratiocurveWords4SizeCheck[(sizeof(g_GAudiopitchratiocurveWords4) == 16) ? 1 : -1];
#endif
#endif
#ifdef VERSION_US_REV1
#if defined(VERSION_US_REV1)
struct {
    s32 g_musicRequestedTrack;
    s32 g_musicStartupFrameCount;
    u8 retainedPitchRatioWords[8];
} g_GAudiopitchratiocurveWords4 __attribute__((aligned(4))) = {
    0,
    0,
    { 0x3f, 0x8b, 0x41, 0x41, 0x3f, 0x8b, 0x1d, 0x14 }
};
typedef char g_GAudiopitchratiocurveWords4SizeCheck[(sizeof(g_GAudiopitchratiocurveWords4) == 16) ? 1 : -1];
#endif
#endif
