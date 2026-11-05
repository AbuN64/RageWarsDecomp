#include "include_asm.h"

/* gfx_getconvertedcounterratio_data.CPP */
#if defined(VERSION_EU_X)
#include "types.h"
#include "Common/effectrender.h"
/* Signed 64-bit integer to double: the high word scaled by 2^32 plus the low word, each word read
   as signed and corrected by 2^32 when negative. */

double Libc_SignedLongLongToDoubleUsRev1(s64 value) {
    double high, low;
    s32 negate = 0;
    if (value < 0) {
        value = -value;
        negate = 1;
    }
    high = (s32)(value >> 32);
    if ((s32)(value >> 32) < 0)
        high += g_longLongHighWordUnsignedBias;
    high *= g_longLongHighWordHalfwordScale;
    high *= g_longLongHighWordHalfwordScale;
    low = (s32)value;
    if ((s32)value < 0)
        low += g_longLongLowWordUnsignedBias;
    high += low;
    return negate ? -high : high;
}
#endif
