#include "RENDER/TIMED_SESSION_TRANSITIONS.H"
#include "include_asm.h"
#include "COMMON/OBJRECAT26DD8.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/WORLD.H"
#include "COMMON/DESCRIPTORRECAT29.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "TYPES.H"
#include "ENGINE/SETN64.H"
#include "RENDER/CONTROL_CYCLEACTORSNAPSHOTMODE.H"
#include "COMMON/ROUND_STATE_VARIANTS.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/GAME_SESSION.H"

extern void SetN64_HandleSessionTransitionInput(s32 session, s32 cancelTarget, s32 target);


/* Resets the menu viewport and selects the row identified by the owner's current index. */


extern void SetN64_CommitSessionInputs(void *unused);

extern void CCollision_Initialize(void);


extern void Scene_SetSelection(void *state, s32 selection, s32 mode);


extern s32 g_gameLoopFrameCount;

extern void SetN64_ResetSessionPlayerPools(void *session, s32 count, s32 force_active);

void SetN64_HandleMode11Input(s32 session) {
    SetN64_HandleSessionTransitionInput(session, 12, 12);
}

void SetN64_DrawMode11Session(void *session) { SetN64_DrawSessionWithAttractTimeout(session); }

void SetN64_ResetMode10Items(s32 sessionAddress) {
    Scene_ResetTransitionViewport();
    ((s32 (*)(s32, s32))SetN64_ResetPlayerItems)(sessionAddress, 111);
}

void SetN64_HandleMode10Input(s32 session) {
    SetN64_HandleSessionTransitionInput(session, 13, 8);
}

void SetN64_DrawMode10Session(void *session) { SetN64_DrawSessionWithAttractTimeout(session); }

void SetN64_ResetMode12Items(int sessionAddress) {
    Scene_ResetTransitionViewport();
    SetN64_ResetPlayerItems(sessionAddress, ((RoundSessionItemStateView *)sessionAddress)->selectionKeyBase + 601);
}

void SetN64_HandleMode12Input(s32 session) {
    SetN64_HandleSessionTransitionInput(session, 13, 13);
}

void SetN64_DrawMode12Session(void *session) { SetN64_DrawSessionWithAttractTimeout(session); }

void SetN64_ResumeSelectedSession(GameSession *unused) {
    void *dst;
    s32 field;
    f32 f;

    g_gameSettings.counters.first = 0;
    g_gameLoopFrameCount = 0;
    SetN64_CommitSessionInputs(unused);
    CCollision_Initialize();
#if defined(VERSION_US_REV1)
    TextLoad_ResetArtsendTextureState();
#endif
    dst = &g_world;
#if defined(VERSION_US_REV1)
    f = (1.0f);
#else
    f = (1.0f);
#endif
    field = unused->selector;
#if defined(VERSION_US_REV1)
    g_roundExtraStateUsRev1 = 0;
#endif
    g_skyRotorSpinScale = f;
    g_roundTimerStep = f;
    g_particleSimulationTimeScale = f;
    Scene_SetSelection(dst, field, 0);
    unused->mode = 13;
    g_initialMatchStartPending = 0;
}

/* Prepares a session for a new round: clears the round flag, resets the round state, records the round seed when Control_IsSnapshotActive_Camera allows, resets the scoreboard and player slot, restarts the arena with the session's arena setting, resets the camera timers and reloads the session's sound bank and music. */
void SetN64_StartRound(GameSession *session) {
    CGameStatus *counters;
    Shared_Game *game;

    g_gameLoopFrameCount = 0;
    SetN64_CommitSessionInputs(session);
    if (Control_IsSnapshotActive() != 0) {
        session->selector = Control_GetSnapshotActorId();
    }
    counters = &g_gameSettings.counters;
    counters->state = 0;
    counters->m_FragTagSelectionType = 3;
    game = &g_gameSettings;
    game->local = 1;
    game->mode1E = 8;
    SetN64_ResetSessionPlayerPools(session, session->arena, 0);
    if (Control_IsSnapshotActive() != 0) {
        Control_RestoreActorSnapshot();
    }
    CCollision_Initialize();
    resetRoundExtra();
    clearRoundExtra();
    g_skyRotorSpinScale = roundTimerConstant();
    g_roundTimerStep = roundTimerConstant();
    g_particleSimulationTimeScale = roundTimerConstant();
    Scene_InitPreview(&g_world, session->resource);
    Scene_SetSelection(&g_world, session->selector, 0);
}

#if !(defined(VERSION_US_REV1))
const float g_Setn64StartroundWords1[1] = {
    1.0f,
};
#endif
