#include "ENGINE/CONTPAD.H"

#if defined(VERSION_DE)
/* Alignment fill to the next 16-byte object boundary. */
unsigned int k_ContpadEncodedWordsBlock1AlignmentPad[3] = {
    0x00008000, 0x00004000, 0x00004000,
};
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
/* Alignment fill to the next 16-byte object boundary. */
unsigned int k_ContpadEncodedWordsBlock2AlignmentPad[2] = {
    0x00000000, 0xFFFFFFFF,
};
#endif
