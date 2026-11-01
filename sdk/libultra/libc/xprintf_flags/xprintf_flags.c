#include "include_asm.h"
#include "../../../include/libgultra.h"

/* 800CCD40.CPP */
#if !(defined(VERSION_US_REV1))
const char g_printfFlagCharactersText[8] =
    " +-#0\000\000\000";
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_printfFlagCharactersText_StorageWords_XprintfData0.c */
const unsigned short g_printfFlagCharactersText_StorageWords[3] = {
    0x202B, 0x2D23, 0x3000,
};
#endif

/* 800CD394_7.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CCD46 */
unsigned short g_XprintfData0EncodedHalfwords[1] = {
    0x0000,
};
#endif

/* 800CD394_8.CPP */
#if defined(VERSION_US_REV1)
unsigned int g_printfFlagBits[6] = {
    0x00000001, 0x00000002, 0x00000004, 0x00000008, 0x00000010, 0x00000000,
};
#endif
