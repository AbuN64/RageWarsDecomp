#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const float k_CbarrelUpdatetrackeraimEncodedWords[4] = {
    51.199997f, 51.199997f, 3.1415927f, 3.4028235e+38f,
};
#endif

#if defined(VERSION_US_REV1)
const float k_CbarrelUpdatetrackeraimEncodedWordsBlock1[3] = {
    51.199997f, 51.199997f, 3.1415927f,
};

/* ROM-grounded data: src/k_CbarrelUpdatetrackeraimMaxFiniteFloatWords_CbarrelUpdatetrackeraimData.c */
const float k_CbarrelUpdatetrackeraimMaxFiniteFloatWords[1] = {
    3.4028235e+38f,
};
#endif
