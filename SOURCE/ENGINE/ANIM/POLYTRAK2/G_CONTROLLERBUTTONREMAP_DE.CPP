#include "ENGINE/CONTPAD.H"
#if defined(VERSION_DE)

/* Alignment fill to the next 16-byte object boundary. */
unsigned int k_ContpadEncodedWordsBlock1AlignmentPad[3] = {
    0x00008000, 0x00004000, 0x00004000,
};
#endif
