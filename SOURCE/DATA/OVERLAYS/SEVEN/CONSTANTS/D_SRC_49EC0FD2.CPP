#include "TYPES.H"

#include "include_asm.h"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/ragewars_weapon_presentation_D10CC_us_rev1.c */
struct {
    unsigned int w0;
    unsigned short h1[2];
} g_weaponPresentationDescriptor3Rev1 = { 0x800D7144, { 0x04D9, 0x0BCC } };
#endif

#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
struct {
    s16 resource;
    s16 sentinel;
} g_weaponPresentationDescriptor3Rev1Terminator __attribute__((aligned(2))) = {
    0,
    -1
};
typedef char g_weaponPresentationDescriptor3Rev1TerminatorSizeCheck[(sizeof(g_weaponPresentationDescriptor3Rev1Terminator) == 4) ? 1 : -1];
#endif
#endif
