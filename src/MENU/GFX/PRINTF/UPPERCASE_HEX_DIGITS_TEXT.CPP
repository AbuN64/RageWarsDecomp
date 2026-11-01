#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const char s_gfxUppercaseHexDigits[20] =
    "0123456789ABCDEF\000\000\000\000";
#endif

#if defined(VERSION_US_REV1)
const char g_uppercaseHexDigitsUsRev1[17] =
    "0123456789ABCDEF";
#endif
