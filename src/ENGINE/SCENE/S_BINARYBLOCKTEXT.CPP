#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const char s_binaryBlockText[13] =
    "binary block\000";
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/k_SBinaryblocktextEncodedBytesSource.c */
const char k_SBinaryblocktextEncodedBytes[13] =
    "binary block";
#endif
