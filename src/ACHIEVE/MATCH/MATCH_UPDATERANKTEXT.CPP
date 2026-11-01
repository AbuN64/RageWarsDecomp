#include "include_asm.h"
#include "COMMON/LONE/G_LANGUAGEINDEX.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/PLAYERPROFILES.H"


#include "TYPES.H"
typedef struct AchieveRecord { u8 pad0[0x78]; u8 active; u8 pad79[0x18]; u8 team; u8 pad92[4]; } AchieveRecord;
extern u8 g_profileAchievementProgressRows[][0x96];
extern s32 g_profileAchievementCountRows[][100];
extern u8 g_profileAchievementCounters[];
extern s8 g_matchAchievementQualificationFlagA;
extern s8 g_matchAchievementQualificationFlagB;
extern AchieveRecord g_playerSettings[];
extern s32 g_playerCountedShots[];
typedef struct { s8 pad[0x24]; s8 a; s8 b; } Settings;
extern Settings g_gameSettings;
/* Increment the capped player match count and eligible level count. */
void Match_UpdateMatchCounters(s32 playerIndex, s32 counterIndex) {
    s32 count;
    s32 i;
    s32 eligible;
    s32 value;
    s32 result;
    AchieveRecord *rec;
    Settings *cfg;
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
            if (rec->active == 1) {
                if (rec->team != rec->active) {
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
        if (cfg->a >= 10 || cfg->b >= 10) {
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

extern s32 Defs_TestBit(void *bitArray, s32 index);

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
extern char *g_profileRankTitles[];
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
extern char *g_profileRank0LocalizedTitles[];
extern char *g_profileRank1LocalizedTitles[];
extern char *g_profileRank2LocalizedTitles[];
extern char *g_profileRank3LocalizedTitles[];
extern char *g_profileRank4LocalizedTitles[];
extern char *g_profileRank5LocalizedTitles[];
extern char *g_profileRank6LocalizedTitles[];
extern char *g_profileRank7LocalizedTitles[];
extern char *g_profileRank8LocalizedTitles[];
extern char *g_profileRank9LocalizedTitles[];
extern char *g_profileRank10LocalizedTitles[];
extern char *g_profileRank11LocalizedTitles[];
extern char *g_profileRank12LocalizedTitles[];
extern char *g_profileRank13LocalizedTitles[];
extern char *g_profileRank14LocalizedTitles[];
extern char *g_profileRank15LocalizedTitles[];
extern char *g_profileRank16LocalizedTitles[];
extern char *g_profileRank17LocalizedTitles[];
extern char *g_profileRank18LocalizedTitles[];
extern char *g_profileRank19LocalizedTitles[];
#endif

char *Match_UpdateRankText(s32 index) {
    s32 count;
    s32 i;
    char *text;
    s32 rank;
    if (index >= 4) {
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        return (g_profileRankTitles[0]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        return ((g_profileRank0LocalizedTitles)[g_languageIndex]);
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
        text = ((g_profileRank0LocalizedTitles)[g_languageIndex]);
#endif
        break;
    case 2:
    case 3:
        rank = 1;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[1]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = ((g_profileRank1LocalizedTitles)[g_languageIndex]);
#endif
        break;
    case 4:
    case 5:
        rank = 2;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[2]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = ((g_profileRank2LocalizedTitles)[g_languageIndex]);
#endif
        break;
    case 6:
    case 7:
        rank = 3;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[3]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = ((g_profileRank3LocalizedTitles)[g_languageIndex]);
#endif
        break;
    case 8:
    case 9:
        rank = 4;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[4]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = ((g_profileRank4LocalizedTitles)[g_languageIndex]);
#endif
        break;
    case 10:
    case 11:
        rank = 5;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[5]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = ((g_profileRank5LocalizedTitles)[g_languageIndex]);
#endif
        break;
    case 12:
    case 13:
        rank = 6;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[6]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = ((g_profileRank6LocalizedTitles)[g_languageIndex]);
#endif
        break;
    case 14:
    case 15:
        rank = 7;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[7]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = ((g_profileRank7LocalizedTitles)[g_languageIndex]);
#endif
        break;
    case 16:
    case 17:
        rank = 8;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[8]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = ((g_profileRank8LocalizedTitles)[g_languageIndex]);
#endif
        break;
    case 18:
    case 19:
        rank = 9;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[9]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = ((g_profileRank9LocalizedTitles)[g_languageIndex]);
#endif
        break;
    case 20:
    case 21:
        rank = 10;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[10]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = ((g_profileRank10LocalizedTitles)[g_languageIndex]);
#endif
        break;
    case 22:
    case 23:
    case 24:
        rank = 11;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[11]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = ((g_profileRank11LocalizedTitles)[g_languageIndex]);
#endif
        break;
    case 25:
    case 26:
    case 27:
        rank = 12;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[12]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = ((g_profileRank12LocalizedTitles)[g_languageIndex]);
#endif
        break;
    case 28:
    case 29:
    case 30:
        rank = 13;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[13]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = ((g_profileRank13LocalizedTitles)[g_languageIndex]);
#endif
        break;
    case 31:
    case 32:
    case 33:
        rank = 14;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[14]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = ((g_profileRank14LocalizedTitles)[g_languageIndex]);
#endif
        break;
    case 34:
    case 35:
    case 36:
        rank = 15;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[15]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = ((g_profileRank15LocalizedTitles)[g_languageIndex]);
#endif
        break;
    case 37:
    case 38:
    case 39:
        rank = 16;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[16]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = ((g_profileRank16LocalizedTitles)[g_languageIndex]);
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
        text = ((g_profileRank17LocalizedTitles)[g_languageIndex]);
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
        text = ((g_profileRank18LocalizedTitles)[g_languageIndex]);
#endif
        break;
    default:
        rank = 19;
#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
        text = (g_profileRankTitles[19]);
#elif defined(VERSION_EU) || defined(VERSION_EU_X)
        text = ((g_profileRank19LocalizedTitles)[g_languageIndex]);
#endif
        break;
    }
    g_localPlayerProfiles[index].rank = rank;
    return text;
}
