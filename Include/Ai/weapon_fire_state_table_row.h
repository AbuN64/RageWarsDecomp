#ifndef AI_WEAPON_FIRE_STATE_TABLE_ROW_H
#define AI_WEAPON_FIRE_STATE_TABLE_ROW_H
#include "types.h"

/* One fire state of a weapon: the state id, its enter and update callbacks, the sound it plays
 * and its scale and mode. The first row of a table holds the callback table pointer in place
 * of a state id; the last row has state id -1. */
typedef struct WeaponFireStateTableRow {
    u32 state;
    void *enter;
    void *update;
    s32 reserved0;
    s32 soundId;
    f32 scale;
    s32 mode;
    s32 reserved1;
} WeaponFireStateTableRow;

extern WeaponFireStateTableRow k_weaponFireStateTable[5];

#endif
