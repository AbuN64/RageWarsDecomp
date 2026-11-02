#include "ENGINE/CONTPAD.H"
#if defined(VERSION_DE)

/* Bytes the original holds up to the next 16-byte object boundary; no instruction reads them. */
unsigned int k_contpadStaleWordsBlock1[3] = {
    0x00008000, 0x00004000, 0x00004000,
};
#endif
