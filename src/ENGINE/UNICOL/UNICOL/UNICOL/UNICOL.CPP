#include "include_asm.h"

/* 800C37E4.CPP */
#if defined(VERSION_DE)
float g_UnicolEncodedWordsBlock1[3] = {
    3.0f, 1.0f, 0.008726647f,
};
#endif

/* 800C8710_15.CPP */
#if !(defined(VERSION_US_REV1))
const float k_UnicolEncodedWords[9] = {
    0.5f, 0.5f, 1.0f, 0.35f, 1.0f, 47.5f,
    1.0f, 10.24f, 0.06666667f,
};
#endif


#if defined(VERSION_EU_X)
float k_UnicolEncodedWordsBlock11[3] = {
    1.0f, 1.0f, 1.0f,
};
#endif


#if defined(VERSION_US_REV1)
const float k_UnicolEncodedWordsBlock2[4] = {
    0.5f, 0.5f, 1.0f, 0.35f,
};

/* ROM-grounded data: src/k_UnicolOneWords_Unicol.c */
const float k_UnicolOneWords[1] = {
    1.0f,
};

/* ROM-grounded data: src/k_UnicolEncodedWordsBlock5_Unicol.c */
const float k_UnicolEncodedWordsBlock5[2] = {
    47.5f, 1.0f,
};

/* ROM-grounded data: src/k_UnicolEncodedWordsBlock3_Unicol.c */
const float k_UnicolEncodedWordsBlock3[1] = {
    10.24f,
};

/* ROM-grounded data: src/k_UnicolEncodedWordsBlock4_Unicol.c */
const float k_UnicolEncodedWordsBlock4[1] = {
    0.06666667f,
};
#endif

/* 800C88D4.CPP */
#if defined(VERSION_US_REV1)
float g_UnicolEncodedWordsBlock2[3] = {
    1.0f, 1.0f, 1.0f,
};
#endif
