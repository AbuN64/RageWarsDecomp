#include "include_asm.h"
#include "COMMON/EFFECTRENDER.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "COMMON/MENULISTSCREEN.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include <ultra64.h>
#include "COMMON/WORLD.H"
#include "COMMON/STATERECAT91.H"
#include "TYPES.H"
#include "ACHIEVE/achieve_match_setup.H"

/* Copies a player's enabled options into its option list: unless the player's info (at 0x5D8) is
   locked (byte 0x91 is 1) or absent (byte 0x78 is 0), each of the 22 option flags at 0x4C that is 1
   is recorded as the pair (1, value from 0x62) at 0x602 plus twice its index. */




void Achieve_ApplyPlayerOptionOverrides(PlayerLoadoutSelectionView *p) {
    int i;

    if (p->info->locked != 1 && p->info->present != 0) {
        for (i = 0; i < 22; i++) {
            if (p->info->enabled[i] == 1) {
                p->options[i].flag = p->info->enabled[i];
                p->options[i].value = p->info->values[i];
            }
        }
    }
}

extern void *Scene_GetBlLevelData(void *, s32);

void Achieve_EnableLevelWeapons(WeaponPlayer *player) {
    WeaponStatus *status = player->status;
    s32 i;
    u16 *entries;
    s32 id;
    s32 active;

    if (status->out != 1 && status->active != 0) {
        void *table = Scene_GetBlLevelData(&g_world, g_selectedLevelId);
        i = 0;
        active = 1;
        entries = table;
        do {
            id = entries[3];
            if (id >= 1219) {
                id -= 1219;
                player->weapons[id][0] = active;
                player->weapons[id][1] = i;
            }
            i++;
            entries++;
        } while (i < 8);
    }
}

#include "COMMON/CHARACTERSELECTIONROOT.H"
extern MatchMenuApplySlotValueGfx g_gameSettings;

s32 Achieve_MatchQualifies(void) {
    MatchMenuApplySlotValueGfx *match;
    s32 i;
    s32 count;
    s32 result;
    RosterSlot *slot;

    match = &g_gameSettings;
    if (match->matchQualifierFirst <= 0 && match->matchQualifierSecond <= 0) {
        return 0;
    }
    result = 1;
    count = 0;
    for (i = 0; i < 8; i++) {
        slot = &g_gameSettings.slots[i];
        if (slot->active == 1 && slot->m_IsBot != slot->active && g_playerCountedShots[i] >= 76) {
            count++;
        }
    }
    if (count < 2) {
        result = 0;
    }
    return result;
}


