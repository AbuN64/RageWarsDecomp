#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const char s_mempakWriteTempDataText[23] =
    "Mempak write temp data\000";
#endif

#if defined(VERSION_US)
unsigned char k_GPakwritescratchnotenameEncodedBytes[1] = {
    0x53,
};
#endif

#if defined(VERSION_EU_X)
unsigned char k_GPakwritescratchnotenameEncodedBytesBlock3[1] = {
    0x7C,
};
#endif

#if defined(VERSION_DE)
unsigned char k_GPakwritescratchnotenameEncodedBytesBlock1[1] = {
    0x70,
};
#endif

#if defined(VERSION_US_REV1)
const char g_pakWriteScratchNoteName[23] =
    "Mempak write temp data";
#endif

#if defined(VERSION_US_REV1)
unsigned char k_GPakwritescratchnotenameEncodedBytesBlock2[1] = {
    0x6C,
};
#endif
