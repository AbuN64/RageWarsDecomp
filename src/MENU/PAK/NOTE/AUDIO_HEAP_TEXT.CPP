#include "include_asm.h"

/* ROM-grounded data: src/g_audioHeapText_AudioHeapText.c */
const char g_audioHeapText[11] = "audio heap";

#if defined(VERSION_EU_X)
unsigned char k_AudioHeapTextEncodedBytesBlock2[1] = {
    0x38,
};
#endif

#if defined(VERSION_DE)
unsigned char k_AudioHeapTextEncodedBytes[1] = {
    0x63,
};
#endif

#if defined(VERSION_US_REV1)
unsigned char k_AudioHeapTextEncodedBytesBlock1[1] = {
    0x40,
};
#endif
