#include "include_asm.h"
#include "COMMON/ALFXPARAM.H"

/* 800CC694_6.CPP */
const unsigned int g_sequenceTicksToSecondsUnsignedBias_StorageWords[3] = {
    0x41F00000, 0x00000000, 0x49742400,
};

/* 800CC694_7.CPP */
const unsigned int k_SeqData1EncodedWords[4] = {
    0x49742400, 0x41F00000, 0x00000000, 0x4F000000,
};

#if defined(VERSION_US)
unsigned int k_SeqData1EncodedWordsBlock1[3] = {
    0x0000D055, 0x02000800, 0x08000812,
};
#endif

#if defined(VERSION_EU_X)
unsigned int k_SeqData1EncodedWordsBlock3[3] = {
    0x00000000, 0x420A3D70, 0x3FDD2F1C,
};
#endif

#if defined(VERSION_EU)
extern char g_Playerai_ApplyLinkedProjectileStatusAddressEu[];
void *k_SeqData1EncodedWordsBlock2[3] = {
    (void *)(g_Playerai_ApplyLinkedProjectileStatusAddressEu + 2276), (void *)(g_Playerai_ApplyLinkedProjectileStatusAddressEu + 2276), (void *)(g_Playerai_ApplyLinkedProjectileStatusAddressEu + 2276),
};
#endif
