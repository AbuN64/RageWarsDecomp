#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/PLAYERRECAT64E.H"
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RENDERCOUNTERS.H"
#include "MULTI/MULTI_COMPLETEGAMEOVERDELAY.H"
#include "COMMON/GAME_SESSION.H"
#include "include_asm.h"

/* 8043E9A8_6.CPP */
/* When the timer m_GameOverTimer has run out, calls Match_ResetMatchControllerState on g_gameSession and returns one;
   otherwise returns zero. */
extern void Match_ResetMatchControllerState(void *);

s32 Multi_CompleteGameOverDelay(void) {
    if (g_gameSettings.counters.m_GameOverTimer <= 0.0f) {
        Match_ResetMatchControllerState(&g_gameSession);
        return 1;
    }
    return 0;
}

/* Counts the timer at offset 0x10 of g_matchRoundCounters down by g_frameElapsedTime, stopping at zero, and returns
   zero. */

s32 Multi_DecreaseGameOverTimer(void) {
    CGameStatus *state = &g_gameSettings.counters;
    f32 timer = state->m_GameOverTimer - g_frameElapsedTime;

    state->m_GameOverTimer = timer;
    if (timer < 0.0f) {
        state->m_GameOverTimer = 0.0f;
    }
    return 0;
}

/* 8042FBEC_16.CPP */
