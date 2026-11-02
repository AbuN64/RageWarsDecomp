#include "ENGINE/CONTPAD.H"
#if defined(VERSION_US)

/* Bytes the original holds up to the next 16-byte object boundary; no instruction reads them. */
unsigned int k_contpadStaleWords[3] = {
    0x0000000F, 0x000A0004, 0x0000001A,
};
#endif
