#include "TYPES.H"

#include "include_asm.h"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/ragewars_weapon_presentation_D0ACC_us_rev1.c */
struct {
    unsigned int w0;
    unsigned short h1[2];
} g_weaponSlot4PresentationUsRev1 = { 0x800D7100, { 0x04C6, 0x0BBB } };
#endif

#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
struct {
    s16 resource;
    s16 sentinel;
} g_weaponSlot4PresentationRecord __attribute__((aligned(2))) = {
    0,
    -1
};
typedef char g_weaponSlot4PresentationRecordSizeCheck[(sizeof(g_weaponSlot4PresentationRecord) == 4) ? 1 : -1];
#endif
#endif
