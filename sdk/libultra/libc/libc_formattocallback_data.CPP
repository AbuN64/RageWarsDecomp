#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const char g_libcZeroPaddingText[33] =
    "00000000000000000000000000000000\000";
#endif

#if defined(VERSION_US)
char k_LibcFormattocallbackDataEncodedBytes[11] =
    "NICT\000\000\004\000\000\000f";
#endif

#if defined(VERSION_US)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_EU_X)
unsigned char k_LibcFormattocallbackDataEncodedBytesBlock1[11] = {
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
#endif

#if defined(VERSION_EU_X)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_EU)
unsigned char k_LibcFormattocallbackDataEncodedBytesBlock2[11] = {
    0x0C, 0x6B, 0x38, 0x80, 0x0C, 0x6B, 0x28, 0x80, 0x0C, 0x6B, 0x1C,
};
#endif

#if defined(VERSION_EU)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_DE)
char s_LibcFormattocallbackDataAbcdefText[11] =
    "56789abcdef";
#endif

#if defined(VERSION_DE)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
const unsigned char g_libcZeroPaddingText_StorageWords[] = {
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x00,
#if defined(VERSION_US_REV1)
    0x20, 0x00, 0x00,
#endif
};
#endif
