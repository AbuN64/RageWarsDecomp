#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const char k_GAnimationsindextextEncodedBytes[33] =
    "\077\200\000\000>\000\000\000=\031\231\232\077\200\000\000animations index\000";
#endif

#if defined(VERSION_US_REV1)
const float k_GAnimationsindextextEncodedWords[4] = {
    1.0f, 0.125f, 0.0375f, 1.0f,
};

const char g_animationsIndexText[17] =
    "animations index";
#endif
