#include "include_asm.h"
#include "Sirawread/sirawread.h"

/* SIRAWREAD.CPP */
#if !(defined(VERSION_US_REV1))
const char g_sirawreadText[15] =
    "io/sirawread.c\000";
#endif

#if defined(VERSION_US)
unsigned char k_SirawreadEncodedBytes[13] = {
    0x00, 0x10, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x53, 0x4D, 0x48,
};
#endif

#if defined(VERSION_EU_X)
unsigned char k_sirawreadInstructionBytes[13] = {
    0x00, 0x00, 0x21, 0x02, 0x50, 0x00, 0x20, 0xF6, 0xE0, 0x00, 0x20, 0xFA, 0x30,
};
#endif

#if defined(VERSION_EU)
unsigned char k_sirawreadPaddingBytes[13] = {
    0x00, 0x40, 0x00, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00,
};
#endif

#if defined(VERSION_DE)
char s_SirawreadIoSirawwritText[13] =
    "\000io/sirawwrit";
#endif

#if defined(VERSION_US_REV1)
const char s_sirawreadText[15] =
    "io/sirawread.c";
#endif

#if defined(VERSION_US_REV1)
unsigned char k_sirawreadTailByte[1] = {
    0xE0,
};
#endif
