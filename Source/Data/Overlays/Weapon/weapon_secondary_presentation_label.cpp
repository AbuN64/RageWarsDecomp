#if defined(VERSION_US_REV1)

#include "Gfxdata/audio_decodeframe_data.h"


#include "types.h"


#include "include_asm.h"


#include "Data/Gfxdata/audio_decodeframe_data.h"


#include "Weapon_state_tables/weapon_state_tables.h"


#include "Data/Ovl1_g/weapon_spin_feedback_callback_address.h"


struct {
    unsigned int textLine;
    unsigned short resourceIds[2];
} g_weaponSecondaryPresentationLabel = { (unsigned int)&g_backdropTextLines[132], { 0x04C3, 0x0BB8 } };

struct {
    s16 resource;
    s16 sentinel;
} g_weaponSecondaryPresentationLabelRecord __attribute__((aligned(2))) = {
    0,
    -1
};

struct {
    unsigned short h0[4];
    unsigned int w1;
} g_weaponAmmoEmptyLinkRecord = { { 0xFFFF, 0xFFFF, 0xFFFF, 0x0000 }, 0x00000003 };
#endif
