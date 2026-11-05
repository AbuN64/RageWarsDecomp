#ifndef ACHIEVE_WEAPON_UNLOCK_RECORDS_H
#define ACHIEVE_WEAPON_UNLOCK_RECORDS_H
#include "types.h"

struct InventorySlot {
    u8 available;
    u8 slot;
};

typedef struct InventorySlot InventorySlot;

struct WeaponUnlockModelView {
    char pad0[0x4C];
    int reservedWord;
};

typedef struct WeaponUnlockModelView WeaponUnlockModelView;

#endif
