#include "Common/weapon_screen_message_operations.h"
#include "Common/player_item_inventory.h"
#include "types.h"
#include "Common/shared_gameslot.h"
#include "Common/rendercounters.h"
#include "Multi/multi_completegameoverdelay.h"
#include "Common/game_session.h"
#include "include_asm.h"
#include "Ovlgame/match.h"

/* When the timer m_GameOverTimer has run out, calls Match_ResetMatchControllerState on g_gameSession and returns one;
   otherwise returns zero. */
s32 Multi_CompleteGameOverDelay(void) {
    if (g_gameSettings.counters.m_GameOverTimer <= 0.0f) {
        Match_ResetMatchControllerState(&g_gameSession);
        return 1;
    }
    return 0;
}

/* Counts the game-over timer down by g_frameElapsedTime, stopping at zero, and returns zero. */
s32 Multi_DecreaseGameOverTimer(void) {
    CGameStatus *state = &g_gameSettings.counters;
    f32 timer = state->m_GameOverTimer - g_frameElapsedTime;

    state->m_GameOverTimer = timer;
    if (timer < 0.0f) {
        state->m_GameOverTimer = 0.0f;
    }
    return 0;
}
