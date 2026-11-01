#include "include_asm.h"
#if !(defined(VERSION_US))
#if !(defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US))
/* ROM-grounded data: src/k_initialDataFloatConstantWords_InitialData.c */
const float k_initialDataFloatConstantWords[1] = {
    120.0f,
};
#endif
#endif
#if defined(VERSION_EU_X)
unsigned int k_InitialEncodedWordsBlock1[3] = {
    0x00007530, 0x0041AEC0, 0x00000E03,
};
#endif
#if defined(VERSION_EU)
unsigned int k_InitialEncodedWordsBlock2[3] = {
    0x484A0800, 0x4A05174D, 0xE9171C7C,
};
#endif
#if defined(VERSION_DE) || defined(VERSION_US)
#if defined(VERSION_US)
const unsigned int k_InitialZeroWords[1] = {
    0x00000000,
};
#endif
#endif
