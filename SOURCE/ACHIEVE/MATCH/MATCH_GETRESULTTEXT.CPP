#include "include_asm.h"
#include "COMMON/LONE/g_currentStagePreset.H"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "COMMON/MENULISTSCREEN.H"
#include "TYPES.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "COMMON/STATERECAT91.H"
#include "ACHIEVE/MATCH_GETRESULTTEXT.H"
#include "COMMON/PLAYERPROFILES.H"
#include "WORLD/PLAYERPROFILE.H"
#include "ENGINE/DEFS.H"

/* Applies event *g_currentStagePreset to player record g_localPlayerProfiles[index] once per g_selectedLevelId: when that bit
   of the record's current slot flags is already set it returns -1; otherwise it sets the bit and,
   for an event code below 58, dispatches through k_matchRewardEffectJumpTable to the effect for that code and
   returns the code plus 5000 (5001 when the second effect's test clears bit 0), or -1 for a code
   the table marks unknown. The dispatch and return sit in a one-pass loop; that weighting gives
   the result its saved register ahead of the key pointer, as the cartridge has it. */


















/* Returns the message text for an event result from Match_ApplyLevelCompletionReward: for results 5001 to 5057 the
   text pointer k_matchResultTextJumpTable selects for the result, where result 5002 picks between two texts by
   bit 0 of Player_GetLevelProgress_MatchGetresulttext for the first player's current slot; zero for any other result. The
   dispatch and return sit in a one-pass loop, whose weighting gives the text its register as the
   cartridge has it. */




#if defined(VERSION_EU)
#elif defined(VERSION_EU_X)
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#endif

s32 Match_ApplyLevelCompletionReward(s32 index) {
    s32 result = -1;
    Profile *player = &g_localPlayerProfiles[index];
    s32 *key = &g_selectedLevelId;
    u32 code;

    if (Defs_TestBit(&player->achievementFlags[219 + player->slot * 5], *key) != 0) {
        goto done;
    }
    Defs_SetBitValue(&player->achievementFlags[219 + player->slot * 5], *key, 1);
    code = *g_currentStagePreset;
    result = code + 5000;
    do {
        if (code >= 58) {
            goto unknown;
        }
        switch (code) {
        case 0: goto unknown;
        case 1: goto effect_0;
        case 2: goto effect_1;
        case 3: goto effect_2;
        case 4: goto effect_3;
        case 5: goto effect_4;
        case 6: goto effect_5;
        case 7: goto effect_6;
        case 8: goto effect_7;
        case 9: goto effect_8;
        case 10: goto effect_9;
        case 11: goto effect_10;
        case 12: goto effect_11;
        case 13: goto effect_12;
        case 14: goto effect_13;
        case 15: goto effect_14;
        case 16: goto effect_15;
        case 17: goto effect_16;
        case 18: goto effect_17;
        case 19: goto effect_18;
        case 20: goto effect_19;
        case 21: goto effect_20;
        case 22: goto effect_21;
        case 23: goto effect_22;
        case 24: goto effect_23;
        case 25: goto effect_24;
        case 26: goto effect_25;
        case 27: goto effect_26;
        case 28: goto effect_27;
        case 29: goto effect_28;
        case 30: goto effect_29;
        case 31: goto effect_30;
        case 32: goto unknown;
        case 33: goto effect_31;
        case 34: goto effect_32;
        case 35: goto unknown;
        case 36: goto unknown;
        case 37: goto effect_33;
        case 38: goto unknown;
        case 39: goto unknown;
        case 40: goto unknown;
        case 41: goto unknown;
        case 42: goto unknown;
        case 43: goto unknown;
        case 44: goto unknown;
        case 45: goto unknown;
        case 46: goto unknown;
        case 47: goto unknown;
        case 48: goto unknown;
        case 49: goto unknown;
        case 50: goto unknown;
        case 51: goto unknown;
        case 52: goto done;
        case 53: goto effect_34;
        case 54: goto unknown;
        case 55: goto unknown;
        case 56: goto unknown;
        case 57: goto effect_35;
        }
    effect_0:
        Player_IncrementLevelProgress(player, player->slot);
        Player_IncrementLevelProgress(player, player->slot);
        goto done;
    effect_1:
        Player_IncrementLevelProgress(player, player->slot);
        if ((Player_GetLevelProgress(player, player->slot) & 1) == 0) {
            result = 5001;
        }
        goto done;
    effect_2:
        Player_SetAchievementFlag2F(player, 4);
        goto done;
    effect_3:
        Player_SetAchievementFlagByIndex(player, 2);
        goto done;
    effect_4:
        Player_SetAchievementFlag2F(player, 14);
        goto done;
    effect_5:
        Player_SetAchievementFlagByIndex(player, 6);
        goto done;
    effect_6:
        Player_SetAchievementFlag2F(player, 7);
        goto done;
    effect_7:
        Player_SetAchievementFlagByIndex(player, 16);
        goto done;
    effect_8:
        Player_SetAchievementFlagByIndex(player, 5);
        goto done;
    effect_9:
        Player_SetAchievementFlagByIndex(player, 17);
        goto done;
    effect_10:
        Player_SetAchievementFlag2F(player, 6);
        goto done;
    effect_11:
        Player_SetAchievementFlagByIndex(player, 14);
        goto done;
    effect_12:
        Player_SetAchievementFlagByIndex(player, 4);
        goto done;
    effect_13:
        Player_SetAchievementFlag2F(player, 12);
        goto done;
    effect_14:
        Player_SetAchievementFlag2F(player, 10);
        goto done;
    effect_15:
        Player_AddTenToProfileValue14(player);
        goto done;
    effect_16:
        Player_SetAchievementFlagByIndex(player, 8);
        goto done;
    effect_17:
        Player_SetAchievementFlag2F(player, 8);
        goto done;
    effect_18:
        Player_SetAchievementFlag2F(player, 15);
        goto done;
    effect_19:
        Player_SetAchievementFlagByIndex(player, 11);
        goto done;
    effect_20:
        Player_SetAchievementFlagByIndex(player, 10);
        goto done;
    effect_21:
        Player_SetAchievementFlagByIndex(player, 3);
        goto done;
    effect_22:
        Player_AddFiftyToProfileValue16(player);
        goto done;
    effect_23:
        Player_AddFiftyToProfileValue15(player);
        goto done;
    effect_24:
        Player_SetAchievementFlag2F(player, 13);
        goto done;
    effect_25:
        Player_SetAchievementFlag2F(player, 9);
        goto done;
    effect_26:
        Player_SetAchievementFlagByIndex(player, 1);
        goto done;
    effect_27:
        Player_SetAchievementFlagByIndex(player, 9);
        goto done;
    effect_28:
        Player_SetAchievementFlagByIndex(player, 7);
        goto done;
    effect_29:
        Player_SetAchievementFlagByIndex(player, 13);
        goto done;
    effect_30:
        Player_SetAchievementFlag2F(player, 5);
        goto done;
    effect_31:
        Player_SetAchievementFlag2F(player, 1);
        goto done;
    effect_32:
        Player_SetAchievementFlagByIndex(player, 0);
        goto done;
    effect_33:
        Player_SetAchievementFlag2F(player, 11);
        goto done;
    effect_34:
        player->count++;
        goto done;
    effect_35:
        Player_AdvanceProfileProgress(player);
        goto done;
    unknown:
        result = -1;
    done:
        return result;
    } while (0);
}

char *Match_GetResultText(s32 result) {
    Profile *player = g_localPlayerProfiles;
    char *text = 0;

    if (result < 0) {
        return text;
    }
    switch (result) {
    case 5001:
        text = RW_LOCALIZED_TEXT(g_matchResult5001TextDe, g_matchResult5001TextEu, g_matchResult5001TextEu, g_languageIndex);
        break;
    case 5002:
        if ((Player_GetLevelProgress(player, player->slot) & 1) == 0) {
            text = RW_LOCALIZED_TEXT(g_matchResult5002UnplayedTextDe, g_matchResult5002UnplayedTextEu, g_matchResult5002UnplayedTextEu, g_languageIndex);
        } else {
            text = RW_LOCALIZED_TEXT(g_matchResult5002PlayedTextDe, g_matchResult5002PlayedTextEu, g_matchResult5002PlayedTextEu, g_languageIndex);
        }
        break;
    case 5004:
        text = RW_LOCALIZED_TEXT(g_matchResult5004TextDe, g_matchResult5004TextEu, g_matchResult5004TextEu, g_languageIndex);
        break;
    case 5005:
        text = RW_LOCALIZED_TEXT(g_matchResult5005TextDe, g_matchResult5005TextEu, g_matchResult5005TextEuX, g_languageIndex);
        break;
    case 5006:
        text = RW_LOCALIZED_TEXT(g_matchResult5006TextDe, g_matchResult5006TextEu, g_matchResult5006TextEu, g_languageIndex);
        break;
    case 5007:
        text = RW_LOCALIZED_TEXT(g_matchResult5007TextDe, g_matchResult5007TextEu, g_matchResult5007TextEu, g_languageIndex);
        break;
    case 5008:
        text = RW_LOCALIZED_TEXT(g_matchResult5008TextDe, g_matchResult5008TextEu, g_matchResult5008TextEu, g_languageIndex);
        break;
    case 5009:
        text = RW_LOCALIZED_TEXT(g_matchResult5009TextDe, g_matchResult5009TextEu, g_matchResult5009TextEu, g_languageIndex);
        break;
    case 5010:
        text = RW_LOCALIZED_TEXT(g_matchResult5010TextDe, g_matchResult5010TextEu, g_matchResult5010TextEuX, g_languageIndex);
        break;
    case 5011:
        text = RW_LOCALIZED_TEXT(g_matchResult5011TextDe, g_matchResult5011TextEu, g_matchResult5011TextEuX, g_languageIndex);
        break;
    case 5012:
        text = RW_LOCALIZED_TEXT(g_matchResult5012TextDe, g_matchResult5012TextEu, g_matchResult5012TextEu, g_languageIndex);
        break;
    case 5013:
        text = RW_LOCALIZED_TEXT(g_matchResult5013TextDe, g_matchResult5013TextEu, g_matchResult5013TextEu, g_languageIndex);
        break;
    case 5014:
        text = RW_LOCALIZED_TEXT(g_matchResult5014TextDe, g_matchResult5014TextEu, g_matchResult5014TextEu, g_languageIndex);
        break;
    case 5015:
        text = RW_LOCALIZED_TEXT(g_matchResult5015TextDe, g_matchResult5015TextEu, g_matchResult5015TextEu, g_languageIndex);
        break;
    case 5016:
        text = RW_LOCALIZED_TEXT(g_matchResult5016TextDe, g_matchResult5016TextEu, g_matchResult5016TextEu, g_languageIndex);
        break;
    case 5017:
        text = RW_LOCALIZED_TEXT(g_matchResult5017TextDe, g_matchResult5017TextEu, g_matchResult5017TextEu, g_languageIndex);
        break;
    case 5018:
        text = RW_LOCALIZED_TEXT(g_matchResult5018TextDe, g_matchResult5018TextEu, g_matchResult5018TextEu, g_languageIndex);
        break;
    case 5019:
        text = RW_LOCALIZED_TEXT(g_matchResult5019TextDe, g_matchResult5019TextEu, g_matchResult5019TextEu, g_languageIndex);
        break;
    case 5020:
        text = RW_LOCALIZED_TEXT(g_matchResult5020TextDe, g_matchResult5020TextEu, g_matchResult5020TextEu, g_languageIndex);
        break;
    case 5021:
        text = RW_LOCALIZED_TEXT(g_matchResult5021TextDe, g_matchResult5021TextEu, g_matchResult5021TextEu, g_languageIndex);
        break;
    case 5022:
        text = RW_LOCALIZED_TEXT(g_matchResult5022TextDe, g_matchResult5022TextEu, g_matchResult5022TextEu, g_languageIndex);
        break;
    case 5023:
        text = RW_LOCALIZED_TEXT(g_matchResult5023TextDe, g_matchResult5023TextEu, g_matchResult5023TextEu, g_languageIndex);
        break;
    case 5024:
        text = RW_LOCALIZED_TEXT(g_matchResult5024TextDe, g_matchResult5024TextEu, g_matchResult5024TextEu, g_languageIndex);
        break;
    case 5025:
        text = RW_LOCALIZED_TEXT(g_matchResult5025TextDe, g_matchResult5025TextEu, g_matchResult5025TextEuX, g_languageIndex);
        break;
    case 5026:
        text = RW_LOCALIZED_TEXT(g_matchResult5026TextDe, g_matchResult5026TextEu, g_matchResult5026TextEuX, g_languageIndex);
        break;
    case 5027:
        text = RW_LOCALIZED_TEXT(g_matchResult5027TextDe, g_matchResult5027TextEu, g_matchResult5027TextEuX, g_languageIndex);
        break;
    case 5028:
        text = RW_LOCALIZED_TEXT(g_matchResult5028TextDe, g_matchResult5028TextEu, g_matchResult5028TextEu, g_languageIndex);
        break;
    case 5029:
        text = RW_LOCALIZED_TEXT(g_matchResult5029TextDe, g_matchResult5029TextEu, g_matchResult5029TextEu, g_languageIndex);
        break;
    case 5030:
        text = RW_LOCALIZED_TEXT(g_matchResult5030TextDe, g_matchResult5030TextEu, g_matchResult5030TextEu, g_languageIndex);
        break;
    case 5031:
        text = RW_LOCALIZED_TEXT(g_matchResult5031TextDe, g_matchResult5031TextEu, g_matchResult5031TextEu, g_languageIndex);
        break;
    case 5033:
        text = RW_LOCALIZED_TEXT(g_matchResult5033TextDe, g_matchResult5033TextEu, g_matchResult5033TextEu, g_languageIndex);
        break;
    case 5034:
        text = RW_LOCALIZED_TEXT(g_matchResult5034TextDe, g_matchResult5034TextEu, g_matchResult5034TextEuX, g_languageIndex);
        break;
    case 5037:
        text = RW_LOCALIZED_TEXT(g_matchResult5037TextDe, g_matchResult5037TextEu, g_matchResult5037TextEu, g_languageIndex);
        break;
    case 5057:
        text = RW_LOCALIZED_TEXT(g_matchResult5057TextDe, g_matchResult5057TextEu, g_matchResult5057TextEu, g_languageIndex);
        break;
    case 5052:
        text = RW_LOCALIZED_TEXT(g_matchResult5052TextDe, g_matchResult5052TextEu, g_matchResult5052TextEu, g_languageIndex);
        break;
    case 5053:
        text = RW_LOCALIZED_TEXT(g_matchResult5053TextDe, g_matchResult5053TextEu, g_matchResult5053TextEu, g_languageIndex);
        break;
    default:
        break;
    }
    return text;
}
