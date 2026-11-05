#include "include_asm.h"
#include "Common/effectrender.h"
#include "types.h"
#include "Common/resident_event_handler.h"
#include "Common/frontend_clock_state.h"
#include "Common/menulistscreen.h"
#include "Common/runtime_declarations.h"
#include <platform_sdk.h>
#include "Common/world.h"
#include "Common/weapon_unlock_presets.h"
#include "Achieve/achieve_match_setup.h"
#include "Common/shared_gameslot.h"
#include "Engine/scene_findtrackedactors.h"

#define g_gameSettingsView (*(MatchMenuApplySlotValueGfx *)&g_gameSettings)

/* Copies a player's enabled options into its option list: unless the player's info is
   locked or absent, each of the 22 enabled option flags that is 1 is recorded in the player's option list
   as the pair (flag, matching value). */
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

#include "Common/characterselectionroot.h"

s32 Achieve_MatchQualifies(void) {
    MatchMenuApplySlotValueGfx *match;
    s32 i;
    s32 count;
    s32 result;
    RosterSlot *slot;

    match = &g_gameSettingsView;
    if (match->matchQualifierFirst <= 0 && match->matchQualifierSecond <= 0) {
        return 0;
    }
    result = 1;
    count = 0;
    for (i = 0; i < 8; i++) {
        slot = &g_gameSettingsView.slots[i];
        if (slot->active == 1 && slot->m_IsBot != slot->active && g_playerCountedShots[i] >= 76) {
            count++;
        }
    }
    if (count < 2) {
        result = 0;
    }
    return result;
}
