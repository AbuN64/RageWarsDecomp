#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"
#include "TYPES.H"
#include "include_asm.h"
#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)

/* 800D0D78.CPP */
unsigned short k_GAudiopitchratiocurveEncodedHalfwords[12] = {
    0x800C, 0xBB20, 0x800C, 0xBB30, 0x8010, 0x8060, 0x403F, 0x0000, 0x3442, 0x0010, 0x8C42, 0x0000,
};
#endif
#if defined(VERSION_EU)
unsigned short k_GAudiopitchratiocurveEncodedHalfwords[12] = {
    0x800C, 0xC700, 0x800C, 0xC710, 0x8011, 0x8060, 0x403F, 0x0000, 0x2054, 0x5520, 0x4D45, 0x204D,
};
#endif
#if defined(VERSION_EU_X)
unsigned short k_GAudiopitchratiocurveEncodedHalfwords[12] = {
    0x800C, 0xD0D0, 0x800C, 0xD0E0, 0x8011, 0x2060, 0x403F, 0x0000, 0x3F8B, 0x4141, 0x3F8B, 0x1D14,
};
#endif
#if defined(VERSION_US)
unsigned short k_GAudiopitchratiocurveEncodedHalfwords[12] = {
    0x800C, 0xBA30, 0x800C, 0xBA40, 0x8010, 0x6060, 0x403F, 0x0000, 0x4252, 0x414C, 0x5F42, 0x4F52,
};
#endif
#endif
#if defined(VERSION_US_REV1)

/* ROM-grounded exact candidate, normalized from prior lane proof. */
unsigned int g_GAudiopitchratiocurveWords3[6] = {
    0x800D0D60, 0x800D0D70, 0x8010C060, 0x403F0000, 0x3F8BD1C1, 0x3F8BADA9,
};
#endif
