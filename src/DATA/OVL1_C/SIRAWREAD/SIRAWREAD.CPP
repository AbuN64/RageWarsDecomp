#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const char g_sirawreadText[15] =
    "io/sirawread.c\000";
#endif

#if defined(VERSION_US)
unsigned char k_SirawreadEncodedBytes[13] = {
    0x00, 0x10, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x53, 0x4D, 0x48,
};
#endif

#if defined(VERSION_US)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_EU_X)
unsigned char k_SirawreadEncodedBytesBlock2[13] = {
    0x00, 0x00, 0x21, 0x02, 0x50, 0x00, 0x20, 0xF6, 0xE0, 0x00, 0x20, 0xFA, 0x30,
};
#endif

#if defined(VERSION_EU_X)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_EU)
unsigned char k_SirawreadEncodedBytesBlock1[13] = {
    0x00, 0x40, 0x00, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00,
};
#endif

#if defined(VERSION_EU)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_DE)
char s_SirawreadIoSirawwritText[13] =
    "\000io/sirawwrit";
#endif

#if defined(VERSION_DE)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/s_sirawreadText_Sirawread.c */
const char s_sirawreadText[15] =
    "io/sirawread.c";
#endif

#if defined(VERSION_US_REV1)
unsigned char k_SirawreadEncodedBytesBlock3[1] = {
    0xE0,
};
#endif
