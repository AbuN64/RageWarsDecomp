#include "ENGINE/CONTPAD.H"
#if defined(VERSION_US_REV1)

/* 800D0DA4.CPP */
/* Bytes the original holds up to the next 16-byte object boundary; no instruction reads them. */
unsigned int g_controllerButtonRemapStaleFloatsBlock1[3] = {
    0x3F8AD4AA, 0x3F8AB06C, 0x3F8A8C29,
};
#endif
