#include "include_asm.h"

/* ROM-grounded data: rodata/shared/800E1B60 */
const unsigned char s_playerCountFormatStorage[] = {
    0x25, 0x64, 0x00,
#if defined(VERSION_EU)
    0xD3,
#endif
#if defined(VERSION_US)
    0x00,
#endif
#if defined(VERSION_US_REV1)
    0x10,
#endif
};

#if defined(VERSION_EU_X)
unsigned char k_FrontendIncreaseplayercountEncodedBytesBlock1[13] = {
    0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x0F, 0x00,
};
#endif

#if defined(VERSION_EU_X)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_DE)
unsigned char k_FrontendIncreaseplayercountEncodedBytes[13] = {
    0x7C, 0x00, 0x42, 0xE2, 0xC0, 0x00, 0x42, 0xE3, 0x1C, 0x00, 0x42, 0xE3, 0x74,
};
#endif

#if defined(VERSION_DE)
/* bytes live in the preceding array */
#endif
