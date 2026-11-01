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
unsigned char k_XprintfDataEncodedBytesBlock1[11] = {
    0x0C, 0x6A, 0x98, 0x80, 0x0C, 0x65, 0xA0, 0x80, 0x0C, 0x6A, 0x8C,
};
#endif

#if defined(VERSION_EU)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_DE)
unsigned char k_XprintfDataEncodedBytes[11] = {
    0x00, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00,
};
#endif

#if defined(VERSION_DE)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
const char g_printfUppercaseDigitsUsRev1[17] = "0123456789ABCDEF";
#endif
