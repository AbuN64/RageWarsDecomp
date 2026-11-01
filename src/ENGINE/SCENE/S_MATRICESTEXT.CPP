#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const char g_matricesText[9] =
    "Matrices\000";
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/s_matricesTextSource.c */
const unsigned char s_matricesText[9] =
    "Matrices";
#endif
