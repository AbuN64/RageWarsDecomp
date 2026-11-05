#ifndef ACHIEVE_PRESET_AND_WEAPON_UNLOCK_VIEWS_H
#define ACHIEVE_PRESET_AND_WEAPON_UNLOCK_VIEWS_H
#include "types.h"
#include "Common/weapon_unlock_presets.h"
#include "Achieve/weapon_unlock_records.h"
struct WeaponUnlockModelView;
struct PresetTable {
    char pad0[0x16];
    PresetRow rows[1];
};
struct WeaponUnlockPlayerView {
    char p[24];
    struct WeaponUnlockModelView *model;
    char p2[1468];
    struct WeaponUnlockProfileView *profile;
    char p3[38];
    InventorySlot slots[8];
};
#endif
