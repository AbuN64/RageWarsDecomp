#include "include_asm.h"
#include "Common/Lone/g_languageindex.h"
#include "Common/sharedplayer.h"
#include "Common/playerprofiles.h"
#include "types.h"
#include "Common/shared_gameslot.h"
#include "Engine/defs.h"
#include "Common/runtime_declarations.h"
#include "Common/effectrender.h"
#include "Achieve/achieve_address_symbols.h"
#include "Common/gameplay_settings.h"
#include "Common/stagepreset.h"
#include "Common/resident_event_handler.h"
#include "Common/frontend_clock_state.h"
#include "Common/menulistscreen.h"
#include "Common/vector4f.h"
#include "Common/menu_options_and_results.h"
#include "Common/weapon_unlock_presets.h"
#include "Achieve/match_getresulttext.h"
#include "World/playerprofile.h"

/* Increment the capped player match count and eligible level count. */
void Match_UpdateMatchCounters(s32 playerIndex, s32 counterIndex) {
    s32 count;
    s32 i;
    s32 eligible;
    s32 value;
    s32 result;
    Shared_PlayerSettingsRecord *rec;
    Shared_Game *cfg;
    if (g_profileAchievementProgressRows[playerIndex][0] == 1) {
        return;
    }
    value = g_profileAchievementCountRows[playerIndex][0] + 1;
    if (value > 99999) {
        g_profileAchievementCountRows[playerIndex][0] = 99999;
    } else {
        g_profileAchievementCountRows[playerIndex][0] = value;
    }
    if (g_matchAchievementQualificationFlagA <= 0 && g_matchAchievementQualificationFlagB <= 0) {
        result = 0;
    } else {
        eligible = 1;
        count = 0;
        for (i = 0; i < 8; i++) {
            rec = &g_playerSettings[i];
            if (rec->enabled == 1) {
                if (rec->locked != rec->enabled) {
                    if (g_playerCountedShots[i] >= 76) {
                        count++;
                    }
                }
            }
        }
        if (count < 2) {
            eligible = 0;
        }
        result = eligible;
    }
    if (result == 1) {
        cfg = &g_gameSettings;
        if (cfg->laps >= 10 || cfg->players >= 10) {
            value = g_profileAchievementCounters[counterIndex + playerIndex * 400] + 1;
            if (value >= 6) {
                g_profileAchievementCounters[counterIndex + playerIndex * 400] = 5;
            } else {
                g_profileAchievementCounters[counterIndex + playerIndex * 400] = value;
            }
        }
    }
}

/* Count achievements, store the rank, and select its version-specific title. */
char *Match_UpdateRankText(s32 index) {
    s32 count;
    s32 i;
    char *text;
    s32 rank;
    if (index >= 4) {
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        return (g_profileRankTitles[0]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        return (g_profileRankLocalizedTitles[0][g_languageIndex]);
#endif
    }
    count = 0;
    i = 0;
    do {
        if (Defs_TestBit((s32)g_localPlayerProfiles[index].achievementFlags, i) == 1) {
            count++;
        }
        i++;
    } while (i < 50);
    switch (count) {
    case 0:
    case 1:
        rank = 0;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[0]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = (g_profileRankLocalizedTitles[0][g_languageIndex]);
#endif
        break;
    case 2:
    case 3:
        rank = 1;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[1]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = (g_profileRankLocalizedTitles[1][g_languageIndex]);
#endif
        break;
    case 4:
    case 5:
        rank = 2;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[2]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = (g_profileRankLocalizedTitles[2][g_languageIndex]);
#endif
        break;
    case 6:
    case 7:
        rank = 3;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[3]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = (g_profileRankLocalizedTitles[3][g_languageIndex]);
#endif
        break;
    case 8:
    case 9:
        rank = 4;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[4]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = (g_profileRankLocalizedTitles[4][g_languageIndex]);
#endif
        break;
    case 10:
    case 11:
        rank = 5;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[5]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = (g_profileRankLocalizedTitles[5][g_languageIndex]);
#endif
        break;
    case 12:
    case 13:
        rank = 6;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[6]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = (g_profileRankLocalizedTitles[6][g_languageIndex]);
#endif
        break;
    case 14:
    case 15:
        rank = 7;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[7]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = (g_profileRankLocalizedTitles[7][g_languageIndex]);
#endif
        break;
    case 16:
    case 17:
        rank = 8;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[8]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = (g_profileRankLocalizedTitles[8][g_languageIndex]);
#endif
        break;
    case 18:
    case 19:
        rank = 9;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[9]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = (g_profileRankLocalizedTitles[9][g_languageIndex]);
#endif
        break;
    case 20:
    case 21:
        rank = 10;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[10]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = (g_profileRankLocalizedTitles[10][g_languageIndex]);
#endif
        break;
    case 22:
    case 23:
    case 24:
        rank = 11;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[11]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = (g_profileRankLocalizedTitles[11][g_languageIndex]);
#endif
        break;
    case 25:
    case 26:
    case 27:
        rank = 12;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[12]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = (g_profileRankLocalizedTitles[12][g_languageIndex]);
#endif
        break;
    case 28:
    case 29:
    case 30:
        rank = 13;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[13]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = (g_profileRankLocalizedTitles[13][g_languageIndex]);
#endif
        break;
    case 31:
    case 32:
    case 33:
        rank = 14;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[14]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = (g_profileRankLocalizedTitles[14][g_languageIndex]);
#endif
        break;
    case 34:
    case 35:
    case 36:
        rank = 15;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[15]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = (g_profileRankLocalizedTitles[15][g_languageIndex]);
#endif
        break;
    case 37:
    case 38:
    case 39:
        rank = 16;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[16]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = (g_profileRankLocalizedTitles[16][g_languageIndex]);
#endif
        break;
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:
        rank = 17;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[17]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = (g_profileRankLocalizedTitles[17][g_languageIndex]);
#endif
        break;
    case 45:
    case 46:
    case 47:
    case 48:
    case 49:
        rank = 18;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[18]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = (g_profileRankLocalizedTitles[18][g_languageIndex]);
#endif
        break;
    default:
        rank = 19;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[19]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = (g_profileRankLocalizedTitles[19][g_languageIndex]);
#endif
        break;
    }
    g_localPlayerProfiles[index].rank = rank;
    return text;
}

/* Applies event g_currentStagePreset->recorded to player record g_localPlayerProfiles[index] once per g_selectedLevelId: when that bit
   of the record's current slot flags is already set it returns -1; otherwise it sets the bit and,
   for an event code below 58, dispatches through k_matchRewardEffectJumpTable to the effect for that code and
   returns the code plus 5000 (5001 when the second effect's test clears bit 0), or -1 for a code
   the table marks unknown. The dispatch and return sit in a one-pass loop; that weighting gives
   the result its saved register ahead of the key pointer, as the cartridge has it. */

/* Applies the reward for the first completion of the selected level by the player at index: the stage preset picks
   which level-progress counter or achievement flag is advanced. Returns 5000 plus the stage preset as the result code
   (5001 for stage preset 2 when its progress counter is even after the update), or -1 when the level was already rewarded or the stage has no reward. */
s32 Match_ApplyLevelCompletionReward(s32 index) {
    s32 result = -1;
    Profile *player = &g_localPlayerProfiles[index];
    s32 *key = &g_selectedLevelId;
    u32 code;

    if (Defs_TestBit(&player->achievementFlags[219 + player->slot * 5], *key) != 0) {
        return result;
    }
    Defs_SetBitValue(&player->achievementFlags[219 + player->slot * 5], *key, 1);
    code = g_currentStagePreset->recorded;
    result = code + 5000;
    switch (code) {
    case 1:
        Player_IncrementLevelProgress(player, player->slot);
        Player_IncrementLevelProgress(player, player->slot);
        return result;
    case 2:
        Player_IncrementLevelProgress(player, player->slot);
        if ((Player_GetLevelProgress(player, player->slot) & 1) == 0) {
            result = 5001;
        }
        return result;
    case 3:
        Player_SetAchievementFlag2F(player, 4);
        return result;
    case 4:
        Player_SetAchievementFlagByIndex(player, 2);
        return result;
    case 5:
        Player_SetAchievementFlag2F(player, 14);
        return result;
    case 6:
        Player_SetAchievementFlagByIndex(player, 6);
        return result;
    case 7:
        Player_SetAchievementFlag2F(player, 7);
        return result;
    case 8:
        Player_SetAchievementFlagByIndex(player, 16);
        return result;
    case 9:
        Player_SetAchievementFlagByIndex(player, 5);
        return result;
    case 10:
        Player_SetAchievementFlagByIndex(player, 17);
        return result;
    case 11:
        Player_SetAchievementFlag2F(player, 6);
        return result;
    case 12:
        Player_SetAchievementFlagByIndex(player, 14);
        return result;
    case 13:
        Player_SetAchievementFlagByIndex(player, 4);
        return result;
    case 14:
        Player_SetAchievementFlag2F(player, 12);
        return result;
    case 15:
        Player_SetAchievementFlag2F(player, 10);
        return result;
    case 16:
        Player_AddTenToProfileValue14(player);
        return result;
    case 17:
        Player_SetAchievementFlagByIndex(player, 8);
        return result;
    case 18:
        Player_SetAchievementFlag2F(player, 8);
        return result;
    case 19:
        Player_SetAchievementFlag2F(player, 15);
        return result;
    case 20:
        Player_SetAchievementFlagByIndex(player, 11);
        return result;
    case 21:
        Player_SetAchievementFlagByIndex(player, 10);
        return result;
    case 22:
        Player_SetAchievementFlagByIndex(player, 3);
        return result;
    case 23:
        Player_AddFiftyToProfileValue16(player);
        return result;
    case 24:
        Player_AddFiftyToProfileValue15(player);
        return result;
    case 25:
        Player_SetAchievementFlag2F(player, 13);
        return result;
    case 26:
        Player_SetAchievementFlag2F(player, 9);
        return result;
    case 27:
        Player_SetAchievementFlagByIndex(player, 1);
        return result;
    case 28:
        Player_SetAchievementFlagByIndex(player, 9);
        return result;
    case 29:
        Player_SetAchievementFlagByIndex(player, 7);
        return result;
    case 30:
        Player_SetAchievementFlagByIndex(player, 13);
        return result;
    case 31:
        Player_SetAchievementFlag2F(player, 5);
        return result;
    case 33:
        Player_SetAchievementFlag2F(player, 1);
        return result;
    case 34:
        Player_SetAchievementFlagByIndex(player, 0);
        return result;
    case 37:
        Player_SetAchievementFlag2F(player, 11);
        return result;
    case 53:
        player->count++;
        return result;
    case 57:
        Player_AdvanceProfileProgress(player);
        return result;
    default:
        result = -1;
        return result;
    }
}

char *Match_GetResultText(s32 result) {
    Profile *player = g_localPlayerProfiles;
    char *text = 0;

    if (result < 0) {
        return text;
    }
    switch (result) {
    case 5001:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_EAGLE_TALISMAN], g_acquiredItemTextsEu[ACQUIRED_TEXT_EAGLE_TALISMAN], g_acquiredItemTextsEuX[ACQUIRED_TEXT_EAGLE_TALISMAN], g_languageIndex);
        break;
    case 5002:
        if ((Player_GetLevelProgress(player, player->slot) & 1) == 0) {
            text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_OTHER_EAGLE_TALISMAN], g_acquiredItemTextsEu[ACQUIRED_TEXT_OTHER_EAGLE_TALISMAN], g_acquiredItemTextsEuX[ACQUIRED_TEXT_OTHER_EAGLE_TALISMAN], g_languageIndex);
        } else {
            text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_HALF_EAGLE_TALISMAN], g_acquiredItemTextsEu[ACQUIRED_TEXT_HALF_EAGLE_TALISMAN], g_acquiredItemTextsEuX[ACQUIRED_TEXT_HALF_EAGLE_TALISMAN], g_languageIndex);
        }
        break;
    case 5004:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_CROSSBOW_SNIPER_SCOPE], g_acquiredItemTextsEu[ACQUIRED_TEXT_CROSSBOW_SNIPER_SCOPE], g_acquiredItemTextsEuX[ACQUIRED_TEXT_CROSSBOW_SNIPER_SCOPE], g_languageIndex);
        break;
    case 5005:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_INFLATOR], g_acquiredItemTextsEu[ACQUIRED_TEXT_INFLATOR], g_acquiredItemTextsEuX[ACQUIRED_TEXT_INFLATOR], g_languageIndex);
        break;
    case 5006:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_MINIGUN_PERSONAL_SHIELD], g_acquiredItemTextsEu[ACQUIRED_TEXT_MINIGUN_PERSONAL_SHIELD], g_acquiredItemTextsEuX[ACQUIRED_TEXT_MINIGUN_PERSONAL_SHIELD], g_languageIndex);
        break;
    case 5007:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_PLASMA_RIFLE], g_acquiredItemTextsEu[ACQUIRED_TEXT_PLASMA_RIFLE], g_acquiredItemTextsEuX[ACQUIRED_TEXT_PLASMA_RIFLE], g_languageIndex);
        break;
    case 5008:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_JUMP_CLAW_ATTACK], g_acquiredItemTextsEu[ACQUIRED_TEXT_JUMP_CLAW_ATTACK], g_acquiredItemTextsEuX[ACQUIRED_TEXT_JUMP_CLAW_ATTACK], g_languageIndex);
        break;
    case 5009:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_ASSAULT_RIFLE_RAPID_FIRE], g_acquiredItemTextsEu[ACQUIRED_TEXT_ASSAULT_RIFLE_RAPID_FIRE], g_acquiredItemTextsEuX[ACQUIRED_TEXT_ASSAULT_RIFLE_RAPID_FIRE], g_languageIndex);
        break;
    case 5010:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_ACID_SPIT_ATTACK], g_acquiredItemTextsEu[ACQUIRED_TEXT_ACID_SPIT_ATTACK], g_acquiredItemTextsEuX[ACQUIRED_TEXT_ACID_SPIT_ATTACK], g_languageIndex);
        break;
    case 5011:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_MINIGUN], g_acquiredItemTextsEu[ACQUIRED_TEXT_MINIGUN], g_acquiredItemTextsEuX[ACQUIRED_TEXT_MINIGUN], g_languageIndex);
        break;
    case 5012:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_INFLATOR_UPGRADE], g_acquiredItemTextsEu[ACQUIRED_TEXT_INFLATOR_UPGRADE], g_acquiredItemTextsEuX[ACQUIRED_TEXT_INFLATOR_UPGRADE], g_languageIndex);
        break;
    case 5013:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_SHOTGUN_STREETSWEEPER], g_acquiredItemTextsEu[ACQUIRED_TEXT_SHOTGUN_STREETSWEEPER], g_acquiredItemTextsEuX[ACQUIRED_TEXT_SHOTGUN_STREETSWEEPER], g_languageIndex);
        break;
    case 5014:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_NAPALM_GEL], g_acquiredItemTextsEu[ACQUIRED_TEXT_NAPALM_GEL], g_acquiredItemTextsEuX[ACQUIRED_TEXT_NAPALM_GEL], g_languageIndex);
        break;
    case 5015:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_GRENADE_LAUNCHER], g_acquiredItemTextsEu[ACQUIRED_TEXT_GRENADE_LAUNCHER], g_acquiredItemTextsEuX[ACQUIRED_TEXT_GRENADE_LAUNCHER], g_languageIndex);
        break;
    case 5016:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_BEAR_TALISMAN], g_acquiredItemTextsEu[ACQUIRED_TEXT_BEAR_TALISMAN], g_acquiredItemTextsEuX[ACQUIRED_TEXT_BEAR_TALISMAN], g_languageIndex);
        break;
    case 5017:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_FREEZE_GUN_UPGRADE], g_acquiredItemTextsEu[ACQUIRED_TEXT_FREEZE_GUN_UPGRADE], g_acquiredItemTextsEuX[ACQUIRED_TEXT_FREEZE_GUN_UPGRADE], g_languageIndex);
        break;
    case 5018:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_FREEZE_GUN], g_acquiredItemTextsEu[ACQUIRED_TEXT_FREEZE_GUN], g_acquiredItemTextsEuX[ACQUIRED_TEXT_FREEZE_GUN], g_languageIndex);
        break;
    case 5019:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_CHESTBURSTER], g_acquiredItemTextsEu[ACQUIRED_TEXT_CHESTBURSTER], g_acquiredItemTextsEuX[ACQUIRED_TEXT_CHESTBURSTER], g_languageIndex);
        break;
    case 5020:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_SCORPION_LAUNCHER_MAGNET], g_acquiredItemTextsEu[ACQUIRED_TEXT_SCORPION_LAUNCHER_MAGNET], g_acquiredItemTextsEuX[ACQUIRED_TEXT_SCORPION_LAUNCHER_MAGNET], g_languageIndex);
        break;
    case 5021:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_GRENADE_LAUNCHER_UPGRADE], g_acquiredItemTextsEu[ACQUIRED_TEXT_GRENADE_LAUNCHER_UPGRADE], g_acquiredItemTextsEuX[ACQUIRED_TEXT_GRENADE_LAUNCHER_UPGRADE], g_languageIndex);
        break;
    case 5022:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_MAG_LASER_SIGHT], g_acquiredItemTextsEu[ACQUIRED_TEXT_MAG_LASER_SIGHT], g_acquiredItemTextsEuX[ACQUIRED_TEXT_MAG_LASER_SIGHT], g_languageIndex);
        break;
    case 5023:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_COUGAR_TALISMAN], g_acquiredItemTextsEu[ACQUIRED_TEXT_COUGAR_TALISMAN], g_acquiredItemTextsEuX[ACQUIRED_TEXT_COUGAR_TALISMAN], g_languageIndex);
        break;
    case 5024:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_COYOTE_TALISMAN], g_acquiredItemTextsEu[ACQUIRED_TEXT_COYOTE_TALISMAN], g_acquiredItemTextsEuX[ACQUIRED_TEXT_COYOTE_TALISMAN], g_languageIndex);
        break;
    case 5025:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_EMACIATOR], g_acquiredItemTextsEu[ACQUIRED_TEXT_EMACIATOR], g_acquiredItemTextsEuX[ACQUIRED_TEXT_EMACIATOR], g_languageIndex);
        break;
    case 5026:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_FLARE_GUN], g_acquiredItemTextsEu[ACQUIRED_TEXT_FLARE_GUN], g_acquiredItemTextsEuX[ACQUIRED_TEXT_FLARE_GUN], g_languageIndex);
        break;
    case 5027:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_BOOMERANG_UPGRADE], g_acquiredItemTextsEu[ACQUIRED_TEXT_BOOMERANG_UPGRADE], g_acquiredItemTextsEuX[ACQUIRED_TEXT_BOOMERANG_UPGRADE], g_languageIndex);
        break;
    case 5028:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_FLARE_GUN_UPGRADE], g_acquiredItemTextsEu[ACQUIRED_TEXT_FLARE_GUN_UPGRADE], g_acquiredItemTextsEuX[ACQUIRED_TEXT_FLARE_GUN_UPGRADE], g_languageIndex);
        break;
    case 5029:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_PLASMA_RIFLE_SCOPE], g_acquiredItemTextsEu[ACQUIRED_TEXT_PLASMA_RIFLE_SCOPE], g_acquiredItemTextsEuX[ACQUIRED_TEXT_PLASMA_RIFLE_SCOPE], g_languageIndex);
        break;
    case 5030:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_EMACIATOR_UPGRADE], g_acquiredItemTextsEu[ACQUIRED_TEXT_EMACIATOR_UPGRADE], g_acquiredItemTextsEuX[ACQUIRED_TEXT_EMACIATOR_UPGRADE], g_languageIndex);
        break;
    case 5031:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_ASSAULT_RIFLE], g_acquiredItemTextsEu[ACQUIRED_TEXT_ASSAULT_RIFLE], g_acquiredItemTextsEuX[ACQUIRED_TEXT_ASSAULT_RIFLE], g_languageIndex);
        break;
    case 5033:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_BOOMERANG], g_acquiredItemTextsEu[ACQUIRED_TEXT_BOOMERANG], g_acquiredItemTextsEuX[ACQUIRED_TEXT_BOOMERANG], g_languageIndex);
        break;
    case 5034:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_WARHAMMER_ROCKET_UPGRADE], g_acquiredItemTextsEu[ACQUIRED_TEXT_WARHAMMER_ROCKET_UPGRADE], g_acquiredItemTextsEuX[ACQUIRED_TEXT_WARHAMMER_ROCKET_UPGRADE], g_languageIndex);
        break;
    case 5037:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_SCORPION_LAUNCHER], g_acquiredItemTextsEu[ACQUIRED_TEXT_SCORPION_LAUNCHER], g_acquiredItemTextsEuX[ACQUIRED_TEXT_SCORPION_LAUNCHER], g_languageIndex);
        break;
    case 5057:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_VIPER_TALISMAN], g_acquiredItemTextsEu[ACQUIRED_TEXT_VIPER_TALISMAN], g_acquiredItemTextsEuX[ACQUIRED_TEXT_VIPER_TALISMAN], g_languageIndex);
        break;
    case 5052:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_COOPERATIVE_TALISMAN], g_acquiredItemTextsEu[ACQUIRED_TEXT_COOPERATIVE_TALISMAN], g_acquiredItemTextsEuX[ACQUIRED_TEXT_COOPERATIVE_TALISMAN], g_languageIndex);
        break;
    case 5053:
        text = RW_LOCALIZED_TEXT(g_acquiredItemTexts[ACQUIRED_TEXT_MINIGAME_ICON], g_acquiredItemTextsEu[ACQUIRED_TEXT_MINIGAME_ICON], g_acquiredItemTextsEuX[ACQUIRED_TEXT_MINIGAME_ICON], g_languageIndex);
        break;
    default:
        break;
    }
    return text;
}
