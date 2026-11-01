#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const float k_CcollisionIntegrategravityanddragEncodedWords[11] = {
    0.06666667f, 15.0f, 1.0f, 0.5f, 1.0f, 10.24f,
    30.72f, 0.2048f, 1.0f, 4.096f, 1.0485761f,
};
#endif

#if defined(VERSION_US_REV1)
const float k_CcollisionIntegrategravityanddragEncodedWordsBlock1[4] = {
    0.06666667f, 15.0f, 1.0f, 0.5f,
};

/* ROM-grounded data: src/ccollisionIntegrategravityanddragOneWordsUsRev1.c */
const float k_CcollisionIntegrategravityanddragOneWords[1] = {
    1.0f,
};

const float k_CcollisionIntegrategravityanddragEncodedWordsBlock2[6] = {
    10.24f, 30.72f, 0.2048f, 1.0f, 4.096f, 1.0485761f,
};
#endif
