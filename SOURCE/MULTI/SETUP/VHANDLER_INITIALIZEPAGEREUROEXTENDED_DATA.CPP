#include "include_asm.h"
#include "TYPES.H"
#if defined(VERSION_DE)
u32 k_VhandlerInitializepagereuroextendedEncodedBlockDe[30] = {
    0x3DD1A331, 0x0FE1150F, 0x3161E6A1, 0x6F6137EF, 0x2612912E, 0xA1F34005,
    0x0228B2E2, 0x13A1B410, 0xF0F15124, 0x0E2FA16C, 0x29CD8A02, 0x34ED5CB3,
    0xC2E2200F, 0x20EEE1A2, 0xB3BFE01D, 0x22FEE3EF, 0x10B12F30, 0xF01F0F5F,
    0x1106B110, 0x32317C11, 0x11331FB1, 0x312D3200, 0x060E4321, 0xB115B031,
    0x0223FE40, 0xFFB10D0D, 0x19E1FEFF, 0x2EE0C1F0, 0xB0FFF1FF, 0x0EFD1EB3,
};
#if defined(VERSION_DE)
struct {
    u8 alignmentFill[8];
} k_VhandlerInitializepagereuroextendedEncodedWords __attribute__((aligned(4))) = {
    { 0xB2, 0xE0, 0x1E, 0xF1, 0xE1, 0xCD, 0xFF, 0xF3 }
};
#endif
#endif
#if defined(VERSION_DE) || defined(VERSION_US)
#if defined(VERSION_DE)
unsigned int k_VhandlerInitializepagereuroextendedEncodedWordFirst[1] = {
    0xB1B31D31,
};
#endif
#endif
#if defined(VERSION_DE)
/* bytes live in the preceding array */
unsigned int k_VhandlerInitializepagereuroextendedEncodedTailDe[1] = {
    0xFFDEDA0B,
};
#endif
#if defined(VERSION_DE) || defined(VERSION_US)
#if defined(VERSION_DE)
unsigned int k_VhandlerInitializepagereuroextendedEncodedWordSecond[1] = {
    0x2EA1EC3D,
};
#endif
#endif
