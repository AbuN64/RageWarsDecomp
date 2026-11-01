#include "COMMON/INTEGERSTATEB0.H"
#include "COMMON/EFFECTCONTRIBUTION.H"
#include "COMMON/LEVEL.H"
#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RENDERCOUNTERS.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "OVLGAME/MATCH_INITPARTICLEQUAD.H"
#include "COMMON/LEVEL_TRACK.H"
#include "include_asm.h"
#include "COMMON/SESSIONHANDLERROW.H"
#include "COMMON/WORLD.H"
#include "COMMON/ITEMRECAT20V1.H"

/* MATCH.CPP */
s32 Match_InitParticleQuad(void) {
    Vtx *vertices = (Vtx *)&g_particleQuadVertices;
    s32 i = 0;
    s32 more;

    vertices[0].v.ob[0] = -1;
    vertices[0].v.ob[2] = 1;
    vertices[0].v.tc[0] = 0;
    vertices[0].v.tc[1] = 0;
    vertices[1].v.ob[0] = 1;
    vertices[1].v.ob[2] = 1;
    vertices[1].v.tc[0] = 1024;
    vertices[1].v.tc[1] = 0;
    vertices[2].v.ob[0] = 1;
    vertices[2].v.ob[2] = -1;
    vertices[2].v.tc[0] = 1024;
    vertices[2].v.tc[1] = 1024;
    vertices[3].v.ob[0] = -1;
    vertices[3].v.ob[2] = -1;
    vertices[3].v.tc[0] = 0;
    vertices[3].v.tc[1] = 1024;
    do {
        vertices[i].v.ob[1] = 0;
        vertices[i].v.flag = 0;
        vertices[i].v.cn[0] = 255;
        vertices[i].v.cn[1] = 255;
        vertices[i].v.cn[2] = 255;
        vertices[i].v.cn[3] = 255;
        i++;
        more = i < 4;
    } while (more);
    return more;
}

/* Resets a match: calls Control_SetControllerMode_Optiontransition with zero, Rumble_FreeAllPoolNodes_Match on g_controllerRumblePool and Playerai_ResetPlayerControllers_Match on
   g_playerViewRenderContext, clears five state words of g_matchRoundCounters, and sets the byte at offset 0x26DC1 of the
   match block to 2 and its word at 0x26DBC to one. */

extern char g_controllerRumblePool[];
extern char g_playerViewRenderContext[];

extern void Rumble_FreeAllPoolNodes(void *);
struct Context;
extern void Playerai_ResetPlayerControllers(struct Context *);

void Match_ResetMatchControllerState(char *match) {
    CGameStatus *state;

    Control_SetControllerMode(0);
    Rumble_FreeAllPoolNodes(g_controllerRumblePool);
    Playerai_ResetPlayerControllers(g_playerViewRenderContext);
    state = &g_gameSettings.counters;
    state->teams = 0;
    state->m_bFragTagOn = 0;
    state->m_bCTFOn = 0;
    state->first = 0;
    state->transitionActive = 0;
    ((GameSession *)match)->phase = 2;
    ((GameSession *)match)->target = 1;
}

/* Asks Scene_FindPlacedObjectsByKey_Match about g_world_AchieveUpdateresultsscreen with a minus-one selector, clears the words of g_matchRoundCounters and puts the object at gameSession into state 0xC with byte 0x26DC1 set to two and the selector, or zero when the lookup failed, stored at 0x26DD8. Adapted from SetN64_SelectSpawnAndStartSession with the selector fixed at minus one, the word at 0x26DDC cleared before the last word of g_matchRoundCounters instead of set after the selector, and the state 0xC instead of 0xD changed. */

void Match_ResetGameClockAndSelectSpawn(GameSession *gameSession) {
    Shared_Placed spawn;
    s32 spawnSelector;

    spawnSelector = -1;
    if (Scene_FindPlacedObjectsByKey(&g_world, spawnSelector, spawnSelector, &spawn, 1) == 0) {
        spawnSelector = 0;
    }
    g_gameSettings.counters.m_GameTimeFifteenth = 0;
    g_gameSettings.counters.m_GameTimeSeconds = 0;
    g_gameSettings.counters.m_GameTimeMinutes = 0;
    g_gameSettings.counters.m_GameTimeHours = 0;
    gameSession->selectionActive = 0;
    g_gameSettings.counters.first = 0;
    gameSession->phase = 2;
    gameSession->selector = spawnSelector;
    gameSession->target = 12;
}

/* Starts the fade out of the session into the match: keeps key as the session selector when
   Scene_FindPlacedObjectsByKey finds a placed object for it (else 0), restarts the game clock and targets mode 13
   when the local player has a transition pending, otherwise mode 12. */
void Match_StartMatchTransition(GameSession *session, s32 key) {
    Shared_Placed spawn;
    if (Scene_FindPlacedObjectsByKey(&g_world, -1, key, &spawn, 1) == 0) {
        key = 0;
    }
    g_gameSettings.counters.m_GameTimeFifteenth = 0;
    g_gameSettings.counters.m_GameTimeSeconds = 0;
    g_gameSettings.counters.m_GameTimeMinutes = 0;
    g_gameSettings.counters.m_GameTimeHours = 0;
    g_gameSettings.counters.first = 0;
    session->selectionActive = 0;
    session->selector = key;
    if (session->local != 0) {
        if (g_gameSettings.counters.transitionActive != 0) {
            session->phase = 2;
            session->target = 13;
        } else {
            session->phase = 2;
            session->target = 12;
        }
    } else {
        session->phase = 2;
        session->target = 12;
    }
}
