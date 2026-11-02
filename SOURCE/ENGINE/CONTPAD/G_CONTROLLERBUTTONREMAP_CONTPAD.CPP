#include "ENGINE/CONTPAD.H"
#if defined(VERSION_US_REV1)

ButtonRemap g_controllerButtonRemap[19] = {
    { 0x8000, 0x8000 },
    { 0x4000, 0x4000 },
    { 0x20, 0x10 },
    { 0x10, 0x20 },
    { 0x2000, 0x2000 },
    { 0x1000, 0x1000 },
    { 0x800, 0x8 },
    { 0x200, 0x2 },
    { 0x100, 0x1 },
    { 0x400, 0x4 },
    { 0x8, 0x800 },
    { 0x2, 0x200 },
    { 0x1, 0x100 },
    { 0x4, 0x400 },
    { 0x10000, 0x10000 },
    { 0x20000, 0x20000 },
    { 0x40000, 0x40000 },
    { 0x80000, 0x80000 },
    { 0, 0 },
};
#endif
#if defined(VERSION_US_REV1)

/* 800D0E48.CPP */
/* ROM-grounded data: rodata/unresolved/800D0DA4_unclaimed_D1A48 */
/* Bytes the original holds up to the next 16-byte object boundary; no instruction reads them. */
unsigned int g_controllerButtonRemapStaleFloats[2] = {
    0x3F84F47C, 0x3F84CF4E,
};
#endif
