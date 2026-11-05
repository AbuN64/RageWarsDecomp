#ifndef PAKINTERFACESCREEN_OVL1_J_H
#define PAKINTERFACESCREEN_OVL1_J_H
#include "types.h"
/* One loadout weapon row: its resource, icon, weapon index and locked-notice label. */
struct LoadoutWeaponItem {
    s32 resource;
    s32 icon;
    s32 weapon;
    void *label;
};
extern struct LoadoutWeaponItem g_loadoutWeaponItems[];
#endif
