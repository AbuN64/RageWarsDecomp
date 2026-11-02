#include "ENGINE/CONTPAD.H"
#if defined(VERSION_US)

/* Alignment fill to the next 16-byte object boundary. */
unsigned int k_ContpadEncodedWordsAlignmentPad[3] = {
    0x0000000F, 0x000A0004, 0x0000001A,
};
#endif
