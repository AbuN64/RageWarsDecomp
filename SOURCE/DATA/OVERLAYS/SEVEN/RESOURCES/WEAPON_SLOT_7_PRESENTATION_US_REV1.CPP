#include "TYPES.H"

#include "include_asm.h"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/ragewars_weapon_presentation_D0BEC_us_rev1.c */
struct {
    unsigned int w0;
    unsigned short h1[2];
} g_weaponSlot7PresentationUsRev1 = { 0x800D710C, { 0x04C9, 0x0BBE } };
#endif

#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
struct {
    s16 resource;
    s16 sentinel;
} g_weaponSlot7PresentationRecord __attribute__((aligned(2))) = {
    0,
    -1
};
typedef char g_weaponSlot7PresentationRecordSizeCheck[(sizeof(g_weaponSlot7PresentationRecord) == 4) ? 1 : -1];
#endif
#endif
