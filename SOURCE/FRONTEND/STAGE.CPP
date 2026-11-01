#include "COMMON/GAMEPLAY_SETTINGS.H"
#include "RSP/RANDOM_DIRECTION_AND_AFFINE_MATH.H"
#include "include_asm.h"
#include "COMMON/LEVEL_GOAL.H"
#include "COMMON/ACTIVE.H"
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "FRONTEND/STAGE_PLACESTAGEOPPONENTS.H"
#include "SYSTEM/SOUND_CONTEXT_MUSIC_AND_VOICE_CONTROL.H"
#include "ACHIEVE/ACHIEVE.H"
#include "FRONTEND/SCREEN.H"

/* STAGE.CPP */
/* Prepares a match: stops the current screen, starts screen 2, resets the eight player status
   records (clearing bytes 0x94 and 0x95 and, for human slots, the team byte 0x92) while counting
   active humans, clears the match counters, and outside mode 0 looks up the stage default for the
   first active player through Achieve_CopyPreset and resets the round state. It then runs the setup of
   the current rule set g_currentResultMode, copies each active human's name and the five profile bytes at 0x189
   of their player record into status bytes 0x7B, 0x7D, 0x79, 0x7A and 0x82, sets the game mode (team mode 2 falls back to 1 with fewer than two
   humans) and, when SoundElement_GetMusicPlaybackEnabled allows, picks a random arena 0x38 to 0x3B. */

extern struct PlayerNameProfileRecord g_localPlayerProfiles[];
/* The stage entry of the current match: seven opponent records from +5. */
struct Stage {
    char pad0[5];
    u8 opponents[7][4];
};
extern struct Stage *g_currentStagePreset;
extern s32 g_selectedLevelId;

extern void MarkMenuEventHandled(void);
extern void SmXlate_SwitchScreen(s32);
extern void Tsmos_RequestFrontendShutdown(void);

extern u8 *XPlus_CopyString(u8 *destination, u8 *source);

void Stage_StartConfiguredMatch(void) {
    u8 *settings;
    u8 *config;
    struct MatchPlayerStatus *status;
    s32 humans;
    s32 i;
    s32 first;
    CGameStatus *match;

    MarkMenuEventHandled();
    SmXlate_SwitchScreen(2);
    Tsmos_RequestFrontendShutdown();
    humans = 0;
    settings = (u8 *)&g_gameSettings;
    for (i = 0; i < 8; i++) {
        status = (struct MatchPlayerStatus *)((u8 *)&((Shared_Game *)settings)->playerSettings[i]);
        status->lives = 0;
        status->score = 0;
        if (status->computer == 0) {
            status->team = 0xFF;
        }
        if (status->computer == 0 && status->joined == 1) {
            humans++;
        }
    }
    match = &g_gameSettings.counters;
    match->enabled = 0;
    match->m_bPhoenixRoomActive = 0;
    g_currentStagePreset = 0;
    if (settings[13] != 0) {
        first = 0;
        while (((struct MatchPlayerStatus *)((u8 *)&((Shared_Game *)settings)->playerSettings[first]))->joined == 0) {
            first++;
        }
        status = (struct MatchPlayerStatus *)((u8 *)&((Shared_Game *)settings)->playerSettings[first]);
        switch (settings[13]) {
        case 1:
            g_currentStagePreset = Achieve_CopyPreset(g_selectedLevelId, 0, status->kind);
            break;
        case 2:
            g_currentStagePreset = Achieve_CopyPreset(g_selectedLevelId, 1, 0);
            break;
        case 3:
            g_currentStagePreset = Achieve_CopyPreset(g_selectedLevelId, 3, 0);
            break;
        case 4:
            g_currentStagePreset = Achieve_CopyPreset(g_selectedLevelId, 2, 0);
            break;
        }
        g_gameSettings.counters.humanWon = 0;
        Stage_PlaceStageOpponents();
    }
    switch (g_currentResultMode.kind) {
    case 0:
        Random_StartCaptureTheFlagMatch();
        break;
    case 1:
        Random_StartFragTagMatch();
        break;
    case 2:
        Random_StartIndividualMatch();
        break;
    case 3:
        Random_StartTeamMatch();
        break;
    }
    for (i = 0; i < 4; i++) {
        status = (struct MatchPlayerStatus *)((u8 *)&((Shared_Game *)settings)->playerSettings[i]);
        if (status->joined == 1 && status->computer == 0) {
            XPlus_CopyString(status->name, g_localPlayerProfiles[i].name);
            if (settings[13] != 0) {
                status->team = 0;
            } else {
                status->team = 0xFF;
            }
            status->profileFirst = g_localPlayerProfiles[i].profile[0];
            status->profileSecond = g_localPlayerProfiles[i].profile[1];
            status->profileThird = g_localPlayerProfiles[i].profile[2];
            status->profileFourth = g_localPlayerProfiles[i].profile[3];
            status->profileFifth = g_localPlayerProfiles[i].profile[4];
        }
    }
    config = (u8 *)&g_gameSettings;
    if (config[1408] == 2 && humans >= 2) {
        Frontend_RequestScreenMode(1);
    } else {
        Frontend_RequestScreenMode(config[1408]);
    }
    if (SoundElement_GetMusicPlaybackEnabled() != 0) {
        SoundElement_SetMusicPlaybackEnabled(Graphu64_NextRandom() % 4 + 56);
    }
}

/* Places the computer opponents of the stage entry g_currentStagePreset: first frees the player settings
   records still marked joined and locked, then for each of the entry's seven opponent records with a
   nonzero kind places it through Random_AddStageOpponent and, by kind, sets the returned slot's controlMode
   and the match counters: kind 12 sets 2 with enabled, timer 100 and cooldown -1; 13 sets 1 with
   enabled; 16 sets 2; 14 sets 1 with enabled for the first such opponent and 0 afterwards; 15 sets 1
   with enabled and clears m_nTalsetLives; any other kind sets 0 and, once a kind 15 opponent was placed,
   marks the slot active. */
extern s32 Random_AddStageOpponent(u8 *);
void Stage_PlaceStageOpponents(void) {
    CGameStatus *match;
    Shared_PlayerSettingsRecord *player;
    s32 boss;
    s32 escorted;
    s32 i;
    s32 slot;
    s32 on;
    Shared_Game *game;

    boss = 0;
    escorted = 0;
    match = &g_gameSettings.counters;
    for (i = 0; i < 8; i++) {
        player = &g_gameSettings.playerSettings[i];
        if (player->enabled == 1 && player->locked == player->enabled) {
            player->enabled = 0;
            player->locked = 0;
        }
    }
    for (i = 0; i < 7; i++) {
        on = 1;
        game = &g_gameSettings;
        if (g_currentStagePreset->opponents[i][0] == 0) {
            continue;
        }
        switch (g_currentStagePreset->opponents[i][0]) {
        case 12:
            match->enabled = on;
            slot = Random_AddStageOpponent(g_currentStagePreset->opponents[i]);
            (game->playerSettings + slot)->controlMode = 2;
            match->m_nBastilleShield = 100;
            match->m_nBastilleTimer = -1;
            break;
        case 13:
            match->enabled = on;
            slot = Random_AddStageOpponent(g_currentStagePreset->opponents[i]);
            (game->playerSettings + slot)->controlMode = on;
            break;
        case 16:
            slot = Random_AddStageOpponent(g_currentStagePreset->opponents[i]);
            (game->playerSettings + slot)->controlMode = 2;
            break;
        case 14:
            slot = Random_AddStageOpponent(g_currentStagePreset->opponents[i]);
            if (boss == 0) {
                boss = 1;
                match->enabled = on;
                (game->playerSettings + slot)->controlMode = on;
            } else {
                (game->playerSettings + slot)->controlMode = 0;
            }
            break;
        case 15:
            escorted = 1;
            match->enabled = on;
            match->m_nTalsetLives = 0;
            slot = Random_AddStageOpponent(g_currentStagePreset->opponents[i]);
            (game->playerSettings + slot)->controlMode = on;
            break;
        default:
            slot = Random_AddStageOpponent(g_currentStagePreset->opponents[i]);
            game->playerSettings[slot].controlMode = 0;
            if (escorted) {
                game->playerSettings[slot].active = on;
            }
            break;
        }
    }
}
