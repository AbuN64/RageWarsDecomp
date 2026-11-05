#include "include_asm.h"

#if defined(VERSION_DE)
float k_PutEncodedWords[1] = {
    2147483648.0f,
};
#endif

#if defined(VERSION_EU)
const unsigned int k_PutEncodedWordEu[1] = {
    0x08000042,
};
#endif

#if defined(VERSION_US_REV1)
const unsigned int k_PutEncodedWordUsRevision[1] = {
    0x0043EA78,
};
#endif
