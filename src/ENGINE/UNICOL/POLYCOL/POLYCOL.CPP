#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const char k_PolycolEncodedBytes[8] =
    "\077333\077333";
#endif




#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/k_PolycolEncodedWords_Polycol.c */
const float k_PolycolEncodedWords[2] = {
    0.7f, 0.7f,
};
#endif
