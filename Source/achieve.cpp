#include "../sdk/include/LIBC.H"
#include "include_asm.h"
#include "types.h"
#include "Common/resident_event_handler.h"
#include "Common/frontend_clock_state.h"
#include "Common/menulistscreen.h"
#include "Common/runtime_declarations.h"
#include "Common/shared_gameslot.h"
#include "Common/world.h"
#include "Common/menu_options_and_results.h"
#include "Common/weapon_unlock_presets.h"
#include "Achieve/preset_and_weapon_unlock_views.h"
#include <platform_sdk.h>
#include "Achieve/achieve.h"
#include "Common/playerprofiles.h"
#include "World/playerprofile.h"
#include "Engine/defs.h"
#include "Engine/scene_findtrackedactors.h"
#include "Menu/event.h"
#include "Achieve/achieve_address_symbols.h"
#include "Common/gameplay_settings.h"

/* Upgrades the thirteen weapon levels of player record g_localPlayerProfiles[index] from the number of its 50
   achievement flags Defs_TestBit reports set: every two achievements from 2 raise one more weapon
   to level 2 and, from 28, one more of twelve to level 3, in a fixed weapon order. */
static inline s32 Achieve_CountPlayerAchievements(s32 index) {
    s32 count;
    s32 i;

    count = 0;
    i = 0;
    do {
        if (Defs_TestBit(g_localPlayerProfiles[index].achievementFlags, i) == 1) {
            count++;
        }
        i++;
    } while (i < 50);
    return count;
}


/* Counts the enabled entries in a fifty-entry player table. */

/* Marks available inventory entries with their slot indices. */
/* Awards player p the character completion unlock (flag 0x31): when the player's record in g_playerSettings_Achieve is
   active and not locked, and the player's profile in g_localPlayerProfiles lacks that flag while its milestone set
   holds bits 0 to 3, it sets the flag through Defs_SetBitValue and stores 0x31 through the second argument. */
s32 Achieve_AwardCharacterCompletionUnlock(s32 p) {
    Profile *record;
    Shared_Game *settings;
    s32 given;

    record = &g_localPlayerProfiles[p];
    settings = &g_gameSettings;
    given = -1;
    if (settings->controllerMode == 1 && settings->humanWon == 1 && g_selectedLevelId >= 35) {
        switch (settings->slots[p].kind) {
        case 0:
            if (Player_TestAchievementFlag7(record, 17) == 0) {
                Player_SetAchievementFlag7(record, 17);
                given = 17;
            }
            break;
        case 1:
            if (Player_TestAchievementFlag7(record, 6) == 0) {
                Player_SetAchievementFlag7(record, 6);
                given = 6;
            }
            break;
        case 2:
            if (Player_TestAchievementFlag7(record, 3) == 0) {
                Player_SetAchievementFlag7(record, 3);
                given = 3;
            }
            break;
        case 3:
            if (Player_TestAchievementFlag7(record, 4) == 0) {
                Player_SetAchievementFlag7(record, 4);
                given = 4;
            }
            break;
        case 4:
            if (Player_TestAchievementFlag7(record, 14) == 0) {
                Player_SetAchievementFlag7(record, 14);
            }
            break;
        case 5:
            if (Player_TestAchievementFlag7(record, 1) == 0) {
                Player_SetAchievementFlag7(record, 1);
                given = 1;
            }
            break;
        case 6:
            if (Player_TestAchievementFlag7(record, 18) == 0) {
                Player_SetAchievementFlag7(record, 18);
                given = 18;
            }
            break;
        case 7:
            if (Player_TestAchievementFlag7(record, 8) == 0) {
                Player_SetAchievementFlag7(record, 8);
                given = 8;
            }
            break;
        case 8:
            if (Player_TestAchievementFlag7(record, 9) == 0) {
                Player_SetAchievementFlag7(record, 9);
                given = 9;
            }
            break;
        case 9:
            if (Player_TestAchievementFlag7(record, 10) == 0) {
                Player_SetAchievementFlag7(record, 10);
                given = 10;
            }
            break;
        case 17:
            if (Player_TestAchievementFlag7(record, 2) == 0) {
                Player_SetAchievementFlag7(record, 2);
                given = 2;
            }
            break;
        case 18:
            break;
        }
        if (Player_TestAchievementFlag7(record, 17) == 1 && Player_TestAchievementFlag7(record, 1) == 1 &&
            Player_TestAchievementFlag7(record, 8) == 1 && Player_TestAchievementFlag7(record, 11) == 0) {
            Player_SetAchievementFlag7(record, 11);
        }
        if (Player_TestAchievementFlag7(record, 2) == 1 && Player_TestAchievementFlag7(record, 6) == 1 &&
            Player_TestAchievementFlag7(record, 9) == 1 && Player_TestAchievementFlag7(record, 12) == 0) {
            Player_SetAchievementFlag7(record, 12);
        }
        if (Player_TestAchievementFlag7(record, 3) == 1 && Player_TestAchievementFlag7(record, 18) == 1 &&
            Player_TestAchievementFlag7(record, 10) == 1 && Player_TestAchievementFlag7(record, 13) == 0) {
            Player_SetAchievementFlag7(record, 13);
        }
    }
    return given;
}

void Achieve_UpdateUnlockTiers(s32 index) {
    Profile *record;
    s32 count;

    record = &g_localPlayerProfiles[index];
    count = Achieve_CountPlayerAchievements(index);
    if (count >= 2) {
        record->achievementFlags[13] = 2;
    }
    if (count >= 4) {
        record->achievementFlags[18] = 2;
    }
    if (count >= 6) {
        record->achievementFlags[14] = 2;
    }
    if (count >= 8) {
        record->achievementFlags[22] = 2;
    }
    if (count >= 10) {
        record->achievementFlags[15] = 2;
    }
    if (count >= 12) {
        record->achievementFlags[16] = 2;
    }
    if (count >= 14) {
        record->achievementFlags[23] = 2;
    }
    if (count >= 16) {
        record->achievementFlags[19] = 2;
    }
    if (count >= 18) {
        record->achievementFlags[30] = 2;
    }
    if (count >= 20) {
        record->achievementFlags[20] = 2;
    }
    if (count >= 22) {
        record->achievementFlags[17] = 2;
    }
    if (count >= 24) {
        record->achievementFlags[21] = 2;
    }
    if (count >= 26) {
        record->achievementFlags[31] = 2;
    }
    if (count >= 28) {
        record->achievementFlags[13] = 3;
    }
    if (count >= 30) {
        record->achievementFlags[18] = 3;
    }
    if (count >= 32) {
        record->achievementFlags[14] = 3;
    }
    if (count >= 34) {
        record->achievementFlags[22] = 3;
    }
    if (count >= 36) {
        record->achievementFlags[15] = 3;
    }
    if (count >= 38) {
        record->achievementFlags[16] = 3;
    }
    if (count >= 40) {
        record->achievementFlags[23] = 3;
    }
    if (count >= 42) {
        record->achievementFlags[30] = 3;
    }
    if (count >= 44) {
        record->achievementFlags[20] = 3;
    }
    if (count >= 46) {
        record->achievementFlags[17] = 3;
    }
    if (count >= 48) {
        record->achievementFlags[21] = 3;
    }
    if (count >= 50) {
        record->achievementFlags[31] = 3;
    }
}

Preset *Achieve_CopyPreset(s32 key, s32 row, s32 column) {
    PresetTable *table;

    table = (PresetTable *)Scene_GetBlLevelData(&g_world, key);
    if (table == 0) {
        return 0;
    }
    Libc_CopyBytes(&g_achievementPresetCopy, &table->rows[row].presets[column], sizeof(Preset));
    return &g_achievementPresetCopy;
}

/* Announces the current arena's entry for a slot: selects one of four five-byte name tables from the
   mode byte g_gameControllerMode, indexes it by the argument times 400 and hands that entry to Defs_SetBitValue
   together with the current handle g_selectedLevelId and flag 1; an unrecognised mode does nothing. */
void Achieve_MarkLevelPlayed(s32 slot) {
    switch (g_gameSettings.controllerMode) {
    case 1:
        Defs_SetBitValue(&g_profileModePlayedLevels[0][slot * 400], g_selectedLevelId, 1);
        return;
    case 2:
        Defs_SetBitValue(&g_profileModePlayedLevels[1][slot * 400], g_selectedLevelId, 1);
        return;
    case 3:
        Defs_SetBitValue(&g_profileModePlayedLevels[2][slot * 400], g_selectedLevelId, 1);
        return;
    case 4:
        Defs_SetBitValue(&g_profileModePlayedLevels[3][slot * 400], g_selectedLevelId, 1);
        return;
    }
}

/* Starts the ambient track for the current stage g_selectedLevelId (stage 4, 9, 22 and 35 select tracks
   0 to 3): returns -1 when the stage has no track or when Defs_TestBit reports the slot busy,
   otherwise starts it on profileIndex's 400-byte slot of g_profileMilestoneCompletionBits through Defs_SetBitValue and returns
   0x13BC. */
s32 Achieve_AwardMilestoneCompletion(s32 profileIndex) {
    s32 result;
    s32 track;
    u8 *slot;

    result = -1;
    switch (g_selectedLevelId) {
    case 4:
        track = 0;
        break;
    case 9:
        track = 1;
        break;
    case 22:
        track = 2;
        break;
    case 35:
        track = 3;
        break;
    default:
        track = -1;
        break;
    }
    if (track != -1) {
        slot = &g_profileMilestoneCompletionBits[profileIndex * 400];
        if (Defs_TestBit(slot, track) == 0) {
            result = 5052;
            Defs_SetBitValue(slot, track, 1);
        }
    }
    return result;
}

void Achieve_AwardAllMilestoneAchievement(s32 player, s32 *award) {
    Shared_PlayerSettingsRecord *record;
    s32 all;
    s32 i;

    record = &g_playerSettings[player];
    all = 1;
    if (record->enabled == 1 && record->locked == 0) {
        if (Defs_TestBit(g_localPlayerProfiles[player].achievementFlags, 49) == 0) {
            for (i = 0; i < 4; i++) {
                if (all != 1) {
                    return;
                }
                if (Defs_TestBit(&g_localPlayerProfiles[player].trackFlags, i) == 0) {
                    all = 0;
                }
            }
            if (all == 1) {
                Defs_SetBitValue(g_localPlayerProfiles[player].achievementFlags, 49, 1);
                *award = 49;
            }
        }
    }
}

s32 Achieve_CountEarnedAchievements(s32 index) {
    s32 slot;
    s32 count;
    count = 0;
    slot = 0;
    do {
        if (Defs_TestBit(&g_profileUnlockFlagBase[index], slot) == 1) {
            count += 1;
        }
        slot += 1;
    } while (slot < 50);
    return count;
}

void Achieve_ApplyProfileWeaponUnlocks(WeaponUnlockPlayerView *player) {
    s32 item;
    s32 unlockAvailable;
    s32 i;
    WeaponUnlockProfileView *profile;
    struct Model *model;
    s32 profileByteOffset;
    profile = player->profile;
    if (profile->locked != 1) {
        i = 0;
        if (profile->present != 0) {
            model = (struct Model *)player->model;
            profileByteOffset = profile->profileIndex * 400;
                        do {
                item = model->slots[i];
                if (item >= 1219) {
                    item = item - 1219;
                    unlockAvailable = Player_HasProfileUnlockFlag(profileByteOffset + g_localPlayerProfiles->name, item);
                    if (unlockAvailable == 1) {
                        player->slots[item].available = unlockAvailable;
                        player->slots[item].slot = i;
                    }
                }
                i += 1;
            } while (i < 8);
        }
    }
}

#if defined(VERSION_EU)
unsigned int k_achieveFragment[1] = {
    0x00600061,
};
#endif

#if defined(VERSION_DE)
void *k_achieveFragment[1] = {
    (void *)(g_Frontend_DispatchPlayModeEventAddress + 10088),
};
#endif
