#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X)
const char g_printfUppercaseDigitsLegacy[17] =
    "0123456789ABCDEF\000";
#endif
#if defined(VERSION_US)
const char g_printfUppercaseDigitsLegacy[20] =
    "0123456789ABCDEF\000_PA";
#endif
#endif

#if defined(VERSION_EU_X)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_EU)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_DE)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
const char g_printfUppercaseDigits[17] = "0123456789ABCDEF";
#endif
