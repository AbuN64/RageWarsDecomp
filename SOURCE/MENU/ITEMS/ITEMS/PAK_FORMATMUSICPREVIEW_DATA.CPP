#include "include_asm.h"

#if defined(VERSION_EU) || defined(VERSION_EU_X)
const char k_pakFormatmusicpreviewDataConstantWords[4] =
    "%2d";
#endif

#if defined(VERSION_EU_X)
unsigned int k_PakFormatmusicpreviewEncodedWordsBlock1[3] = {
    0x0000004B, 0x00000014, 0x00000028,
};
#endif

#if defined(VERSION_EU)
unsigned int k_PakFormatmusicpreviewEncodedWordsBlock2[3] = {
    0x4A0D4A67, 0x4A178744, 0xC8250F0F,
};
#endif
