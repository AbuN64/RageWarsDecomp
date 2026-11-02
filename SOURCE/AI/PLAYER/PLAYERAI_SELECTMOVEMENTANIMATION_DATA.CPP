#include "include_asm.h"

/* ROM-grounded data: src/k_selectMovementAnimationPoolBiasPair_us_rev1.c */
const float k_PlayeraiSelectmovementanimationEncodedWords[2] = {
    1.024f, -1.024f,
};

#if defined(VERSION_EU_X)
char s_PlayeraiSelectmovementanimationElsIndeText[8] =
    "els inde";
#endif

#if defined(VERSION_EU)
unsigned int k_PlayeraiSelectmovementanimationEncodedWordsBlock1[2] = {
    0x2694FFFF, 0x8EA20024,
};
#endif
