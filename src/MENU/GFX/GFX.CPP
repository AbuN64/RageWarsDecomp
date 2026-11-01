#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "COMMON/SITYPE.H"

/* 804143B0.CPP */
#if !(defined(VERSION_EU_X) || defined(VERSION_US_REV1))
/* Ratio of the cycle counter osGetTime returns to the counter rate g_systemClockFrequency, each converted to a double. */
extern u64 osGetTime(void);
extern double Libc_SignedLongLongToDouble(s64 value);
f64 Gfx_GetNormalizedCounter(void) {
    return Libc_SignedLongLongToDouble(osGetTime()) / Libc_SignedLongLongToDouble(g_systemClockFrequency);
}
#endif

/* 804143B0_2.CPP */
#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
f64 Gfx_GetConvertedCounterRatio(void) {
    return Libc_SignedLongLongToDoubleUsRev1(osGetTime()) / Libc_SignedLongLongToDoubleUsRev1(g_systemClockFrequency);
}
#endif
