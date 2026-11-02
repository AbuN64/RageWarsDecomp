#include "TYPES.H"

#include "include_asm.h"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/ragewars_weapon_presentation_D100C_us_rev1.c */
struct {
    unsigned int w0;
    unsigned short h1[2];
} g_weaponPresentationDescriptor1Rev1 = { 0x800D7138, { 0x04D6, 0x0BC9 } };
#endif

#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
struct {
    s16 resource;
    s16 sentinel;
} D_src_5ef0e8ff __attribute__((aligned(2))) = {
    0,
    -1
};
typedef char D_src_5ef0e8ffSizeCheck[(sizeof(D_src_5ef0e8ff) == 4) ? 1 : -1];
#endif
#endif
