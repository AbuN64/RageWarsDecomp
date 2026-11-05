#include "Gfxdata/audio_decodeframe_data.h"
#include "types.h"
#include "include_asm.h"
#include "Data/Gfxdata/audio_decodeframe_data.h"
#include "Weapon_state_tables/weapon_state_tables.h"
#include "Data/Ovl1_g/weapon_spin_feedback_callback_address.h"

/* WEAPON_SECONDARY_PRESENTATION_LABEL_DATA.CPP */
#if defined(VERSION_US_REV1)
extern struct {
    unsigned int textLine;
    unsigned short resourceIds[2];
} g_weaponSecondaryPresentationLabel;

extern struct {
    s16 resource;
    s16 sentinel;
} g_weaponSecondaryPresentationLabelRecord __attribute__((aligned(2)));
typedef char g_weaponSecondaryPresentationLabelRecordSizeCheck[
    (sizeof(g_weaponSecondaryPresentationLabelRecord) == 4) ? 1 : -1];
#endif

/* WEAPON_AMMO_EMPTY_LINK_RECORD.CPP */
#if defined(VERSION_US_REV1)
extern struct {
    unsigned short h0[4];
    unsigned int w1;
} g_weaponAmmoEmptyLinkRecord;
#endif

/* K_WEAPONEASESPINACTIONSTATERECORD.CPP */
#if defined(VERSION_US_REV1)
struct {
    void * reserved0;
    void * reserved1;
    f32 scale;
    f32 speed;
    void * states;
    void * enter;
    void * update;
} k_weaponEaseSpinActionStateRecord __attribute__((aligned(4))) = {
    0,
    0,
    1.0f,
    1.0f,
    &g_weaponStateScripts.alternateTriggerFireState[7],
    0,
    (void *)&g_weapon_EaseSpinAndUpdateFeedbackEntry
};
typedef char k_weaponEaseSpinActionStateRecordSizeCheck[(sizeof(k_weaponEaseSpinActionStateRecord) == 28) ? 1 : -1];
#endif

/* WEAPON_PRIMARY_PRESENTATION_LABEL_DATA.CPP */
#if defined(VERSION_US_REV1)
struct {
    unsigned int textLine;
    unsigned short resourceIds[2];
} g_weaponPrimaryPresentationLabel = { (unsigned int)&g_backdropTextLines[136], { 0x04D3, 0xFFFF } };

struct {
    s16 resource;
    s16 sentinel;
} g_weaponPrimaryPresentationLabelRecord __attribute__((aligned(2))) = {
    0,
    -1
};
typedef char g_weaponPrimaryPresentationLabelRecordSizeCheck[
    (sizeof(g_weaponPrimaryPresentationLabelRecord) == 4) ? 1 : -1];
#endif

/* WEAPON_AMMO_PAIRED_LINK_RECORD.CPP */
#if defined(VERSION_US_REV1)
struct {
    unsigned short h0[4];
    unsigned int w1;
} g_weaponAmmoPairedLinkRecord = { { 0xFFFF, 0x02DA, 0x02DA, 0x0000 }, 0x00000003 };
#endif
