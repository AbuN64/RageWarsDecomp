#include "include_asm.h"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/ragewars_weapon_presentation_D0E2C_us_rev1.c */
struct {
    unsigned int w0;
    unsigned short h1[2];
} g_weaponPresentation4_us_rev1 = { 0x800D7124, { 0x04CF, 0x0BC4 } };
#endif

#if defined(VERSION_US_REV1)
unsigned short g_weaponPresentation4Halfwords[2] = {
    0x0000, 0xFFFF,
};
#endif
