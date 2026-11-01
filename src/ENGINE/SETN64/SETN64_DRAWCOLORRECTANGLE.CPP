#include "COMMON/LEVEL_TRACK.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "COMMON/ITEMRECAT20V1.H"
#include <PR/gbi.h>
#include <ultra64.h>
#include "COMMON/WORLD.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "COMMON/PAKQUEUESTATE.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "TYPES.H"


void Pools_ResetActorPools(struct DraftOwnerA370 *owner, s32 actorCount);

void Player_InitializePlayerPool(struct CPlayerPool_t *pool, s32 count, s32 force_active);

void SetN64_DrawColorRectangle(void *unused, u8 *color, s32 left, s32 top, s32 right, s32 bottom) {
    if (color[3] != 0) {
        gDPPipeSync(g_displayListCursor++);
        gDPSetCycleType(g_displayListCursor++, G_CYC_1CYCLE);
        Geometry_SetModePreset(19);
        Geometry_SetCombineMode(25);
        gDPSetPrimColor(g_displayListCursor++, 255, 255, color[0], color[1], color[2], color[3]);
        {
            Gfx *cmd = g_displayListCursor++;
            s32 x, y, x0, y0;
            u32 high, low, high0;
            x = right;
            if (x < 0) x = 0;
            y = bottom;
            high = _SHIFTL(x,14,10);
            if (y < 0) y = 0;
            low = _SHIFTL(y,2,10) | _SHIFTL(G_FILLRECT,24,8);
            cmd->words.w0 = high | low;
            x0 = left;
            if (x0 < 0) x0 = 0;
            y0 = top;
            high0 = _SHIFTL(x0,14,10);
            if (y0 < 0) y0 = 0;
            cmd->words.w1 = high0 | _SHIFTL(y0,2,10);
        }
    }
}

/** Thin wrapper around Control_CommitControllerInputs. */
void SetN64_CommitSessionInputs(void *unused) {
    Control_CommitControllerInputs();
}

void SetN64_SelectSpawnAndStartSession(GameSession *gameSession, s32 target) {
    Shared_Placed spawn;
    s32 selectionValues;

    selectionValues = target;
    if (Scene_FindPlacedObjectsByKey(&g_world, -1, selectionValues, &spawn, 1) == 0) {
        selectionValues = 0;
    }
    g_gameSettings.counters.m_GameTimeFifteenth = 0;
    g_gameSettings.counters.m_GameTimeSeconds = 0;
    g_gameSettings.counters.m_GameTimeMinutes = 0;
    g_gameSettings.counters.m_GameTimeHours = 0;
    g_gameSettings.counters.first = 0;
    gameSession->phase = 2;
    gameSession->selector = selectionValues;
    gameSession->selectionActive = 1;
    gameSession->target = 13;
}

void SetN64_ResetSessionPlayerPools(void *owner, s32 count, s32 force_active) {
    GameSession *session = owner;
    Pools_ResetActorPools(session->players, count);
    Player_InitializePlayerPool(session->menu, count, force_active);
}
