#include "include_asm.h"

/* 800C721C.CPP */

/* 800C6E84_3.CPP */
#if defined(VERSION_DE) || defined(VERSION_EU_X)
#if defined(VERSION_DE)
unsigned int k_ActorZeroWordsVariant1[1] = {
    0x00000000,
};
#endif
#if defined(VERSION_EU_X)
extern char g_Playerai_ApplyLinkedProjectileStatusAddressEuX[];
void *k_ActorZeroWordsVariant1[1] = {
    (void *)(g_Playerai_ApplyLinkedProjectileStatusAddressEuX + 2276),
};
#endif
#endif
