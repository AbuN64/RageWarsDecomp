#include "include_asm.h"

/* 800C6E24.CPP */
/* ROM-grounded data: src/Portal_GetEngagementDistanceConstantWords.c */
const float g_Portal_GetEngagementDistanceConstantWords[2] = {
    1.0f, 0.52359885f,
};

#if defined(VERSION_US)
unsigned int k_PortalEngagementAndSearchLiteralEncodedWords[1] = {
    0x5F446973,
};
#endif

#if defined(VERSION_EU_X)
unsigned int k_PortalEngagementAndSearchLiteralEncodedWordsBlock2[1] = {
    0xC2480000,
};
#endif

#if defined(VERSION_EU)
unsigned int k_PortalEngagementAndSearchLiteralEncodedWordsBlock1[1] = {
    0x3C04800E,
};
#endif

#if defined(VERSION_DE)
unsigned int k_PortalEngagementAndSearchLiteralNegativeOneWords[1] = {
    0xBF800000,
};
#endif

/* 800C6E2C.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800C6E2C */
unsigned int g_PortalEngagementAndSearchLiteralEncodedWords[1] = {
    0x3FC00000,
};
#endif
