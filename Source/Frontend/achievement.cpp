#include "types.h"
#include "Common/resident_event_handler.h"
#include "Common/frontend_clock_state.h"
#include "Common/menulistscreen.h"
#include "Common/selectionscreenstate.h"
#include "Common/shared_gameslot.h"
#include "Common/menu_options_and_results.h"
#include "Achieve/achieve_match_setup.h"
#include "Common/playerprofiles.h"
#include "Defs/defs.h"
#include "Frontend/frontend_address_symbols.h"

/* unit ACHIEVEMENT.CPP */
/* Awards earned end-of-match unlocks and lists the first two new rewards. */
void Frontend_AwardMatchAchievements(s32 player, s32 *awarded) {
    SlotSelectionPlayerConfig *status;
    Shared_Game *globals;
    CGameStatus *rules;

    f32 elapsed;

    u32 ok;
    s32 score;
    s32 count;
    s32 i;

    count = 0;
    awarded[0] = -1;
    awarded[1] = -1;
    if (Achieve_MatchQualifies() == 0) {
        return;
    }
    status = &g_playerSettings[player];
    if (status->active != 1) {
        return;
    }
    if (status->out != 0) {
        return;
    }
    for (i = 0; i < 36; i++) {
        if (Defs_TestBit(g_localPlayerProfiles[player].achievementFlags, i) == 0 && g_localPlayerProfiles[player].plays[i] >= 2) {
            Defs_SetBitValue(g_localPlayerProfiles[player].achievementFlags, i, 1);
            if (count < 2) {
                awarded[count++] = i;
            }
        }
    }
    if (Defs_TestBit(g_localPlayerProfiles[player].achievementFlags, 36) == 0) {
        ok = 0;
        if (((u8)g_matchAchievementQualificationFlagA - 1U < 5 && status->kills >= 15) ||
            ((rules = &g_gameSettings.counters)->timeLimit >= 0.0f && status->kills >= 15 &&
             (elapsed = rules->timeLimit * (1.0f / 15.0f),
              elapsed = (f32) (s32) (elapsed * (1.0f / 60.0f)),
              (f32) g_gameSettings.laps - elapsed) <= 5.0f)) {
            ok = 1;
        }
        if (ok == 1) {
            Defs_SetBitValue(g_localPlayerProfiles[player].achievementFlags, 36, 1);
            if (count < 2) {
                awarded[count++] = 36;
            }
        }
    }
    if (Defs_TestBit(g_localPlayerProfiles[player].achievementFlags, 37) == 0) {
        ok = 0;
        if (((u8)g_matchAchievementQualificationFlagA - 1U < 10 && status->kills >= 25) ||
            ((rules = &g_gameSettings.counters)->timeLimit >= 0.0f && status->kills >= 25 &&
             (elapsed = rules->timeLimit * (1.0f / 15.0f),
              elapsed = (f32) (s32) (elapsed * (1.0f / 60.0f)),
              (f32) g_gameSettings.laps - elapsed) <= 10.0f)) {
            ok = 1;
        }
        if (ok == 1) {
            Defs_SetBitValue(g_localPlayerProfiles[player].achievementFlags, 37, 1);
            if (count < 2) {
                awarded[count++] = 37;
            }
        }
    }
    if (Defs_TestBit(g_localPlayerProfiles[player].achievementFlags, 38) == 0 && status->kills == 0 &&
        (globals = &g_gameSettings)->laps >= 10 && globals->players >= 20) {
        Defs_SetBitValue(g_localPlayerProfiles[player].achievementFlags, 38, 1);
        if (count < 2) {
            awarded[count++] = 38;
        }
    }
    if (Defs_TestBit(g_localPlayerProfiles[player].achievementFlags, 39) == 0 && status->total >= 5) {
        Defs_SetBitValue(g_localPlayerProfiles[player].achievementFlags, 39, 1);
        if (count < 2) {
            awarded[count++] = 39;
        }
    }
    if (Defs_TestBit(g_localPlayerProfiles[player].achievementFlags, 40) == 0 && (globals = &g_gameSettings)->players >= 20) {
        score = status->kills;
        ok = 1;
        for (i = 0; i < 4; i++) {
            if (ok != 1) {
                break;
            }
            if (player != i && (globals->playerSettings[i].enabled != 1 || globals->playerSettings[i].locked != 0 ||
                                globals->playerSettings[i].score - score < 10)) {
                ok = 0;
            }
        }
        if (ok == 1) {
            Defs_SetBitValue(g_localPlayerProfiles[player].achievementFlags, 40, 1);
            if (count < 2) {
                awarded[count++] = 40;
            }
        }
    }
    if (Defs_TestBit(g_localPlayerProfiles[player].achievementFlags, 41) == 0 && g_localPlayerProfiles[player].statistics.wins > 1000) {
        Defs_SetBitValue(g_localPlayerProfiles[player].achievementFlags, 41, 1);
        if (count < 2) {
            awarded[count++] = 41;
        }
    }
    if (Defs_TestBit(g_localPlayerProfiles[player].achievementFlags, 42) == 0 && g_localPlayerProfiles[player].statistics.deaths > 1000) {
        Defs_SetBitValue(g_localPlayerProfiles[player].achievementFlags, 42, 1);
        if (count < 2) {
            awarded[count++] = 42;
        }
    }
    if (Defs_TestBit(g_localPlayerProfiles[player].achievementFlags, 43) == 0 && status->rewardStatistic >= 10 &&
        (globals = &g_gameSettings)->laps >= 10 && globals->players >= 20) {
        Defs_SetBitValue(g_localPlayerProfiles[player].achievementFlags, 43, 1);
        if (count < 2) {
            awarded[count++] = 43;
        }
    }
    if (Defs_TestBit(g_localPlayerProfiles[player].achievementFlags, 44) == 0 && status->score == 0 &&
        (globals = &g_gameSettings)->laps >= 10 && globals->players >= 20) {
        Defs_SetBitValue(g_localPlayerProfiles[player].achievementFlags, 44, 1);
        if (count < 2) {
            awarded[count] = 44;
        }
    }
}
