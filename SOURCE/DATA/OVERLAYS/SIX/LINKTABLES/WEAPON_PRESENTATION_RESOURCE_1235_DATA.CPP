#include "TYPES.H"

#include "include_asm.h"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/ragewars_weapon_presentation_D094C_us_rev1.c */
struct {
    unsigned int w0;
    unsigned short h1[2];
} g_weaponPresentationResource1235 = { 0x800D70F0, { 0x04D3, 0xFFFF } };
#endif

#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
struct {
    s16 resource;
    s16 sentinel;
} g_weaponPresentationResource1235Record __attribute__((aligned(2))) = {
    0,
    -1
};
typedef char g_weaponPresentationResource1235RecordSizeCheck[(sizeof(g_weaponPresentationResource1235Record) == 4) ? 1 : -1];
#endif
#endif
