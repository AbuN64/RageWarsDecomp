#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const char g_printfLowercaseHexDigits[17] =
    "0123456789abcdef\000";
#endif

#if defined(VERSION_US_REV1)
const char g_printfLowercaseHexDigitsRev1[17] =
    "0123456789abcdef";
#endif
