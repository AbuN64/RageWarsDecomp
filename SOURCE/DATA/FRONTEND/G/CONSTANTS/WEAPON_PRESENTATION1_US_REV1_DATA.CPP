#include "include_asm.h"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/ragewars_weapon_presentation_D0D0C_us_rev1.c */
struct {
    unsigned int w0;
    unsigned short h1[2];
} g_weaponPresentation1_us_rev1 = { 0x800D7118, { 0x04CC, 0x0BC1 } };
#endif

#if defined(VERSION_US_REV1)
unsigned short g_weaponPresentation1Halfwords[2] = {
    0x0000, 0xFFFF,
};
#endif
