#include "include_asm.h"
#include "../include/libgultra.h"

#if defined(VERSION_DE) || defined(VERSION_EU)
const float k_LongarithDataEncodedWordsBlock2[6] = {
    30.0f, 0.0f, 7.5f, 0.0f,
    30.0f, 0.0f,
};
#endif

#if defined(VERSION_EU)
unsigned int k_LongarithDataEncodedWordsBlock1[2] = {
    0x3DCCCCCD, 0x3F000000,
};
#endif

#if defined(VERSION_DE)
unsigned int k_LongarithDataEncodedWords[2] = {
    0x40F00000, 0x00000000,
};
#endif

#if defined(VERSION_EU_X) || defined(VERSION_US_REV1)
/* ROM-grounded exact candidate, normalized from prior lane proof. */
unsigned int g_longLongHighWordUnsignedBias_StorageWords[8] = {
    0x41F00000, 0x00000000, 0x40F00000, 0x00000000, 0x41F00000, 0x00000000, 0x00040000, 0x000C0000,
};
#endif
