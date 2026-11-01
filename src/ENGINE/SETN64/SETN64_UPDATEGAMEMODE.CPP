#include "COMMON/INTEGERSTATEB0.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/PAKQUEUESTATE.H"
#include "COMMON/ACTORRECAT5E0.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "ENGINE/SETN64.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/TRIPLE.H"
extern f32 g_snapshotModeTransitionTimer;

void SetN64_BeginModeTransition(GameSession *session, s32 targetMode) {
    s32 saved;

    saved = session->mode;
    session->phase = 1;
    session->timer = 0;
    session->mode = 20;
    session->target = targetMode;
    session->previousMode = saved;
    if (Control_IsSnapshotActive() != 0) {
        session->timer = g_snapshotModeTransitionTimer;
    }
}

/** Set the state byte and linked value in a large object. */
void SetN64_SetTransitionTarget(GameSession *object, int value) {
    object->phase = 2;
    object->target = value;
}

typedef void (*SessionUpdateHandler)(void *);


extern void SetN64_UpdateFrameTiming(void *world);






void SetN64_UpdateGameMode(void *session) {
    s32 field;
    SessionUpdateHandler fn;

    if (g_sessionUpdateResetFlag != 0) {
        g_sessionUpdateResetFlag = 0;
    }
    Control_TickSnapshotCountdown();
    field = ((GameSession *)session)->mode;
    fn = ((SessionHandlerRow *)g_sessionUpdateHandlers)[field].update;
    if (fn != 0) {
        fn(session);
        field = ((GameSession *)session)->mode;
    }
    if (field != 20 && g_gameModeTransitionFrames != 0) {
        g_gameModeTransitionFrames -= 1;
        SetN64_UpdateFrameTiming(session);
    }
    g_sessionUpdateCount += 1;
}

s32 SetN64_CheckTimedSessionTransition(TimedSessionTransitionView *session, f32 duration, s32 eight, s32 inputTargetMode) {
    s32 *flag = (s32 *)&g_combinedControllerProfile.pressedButtons;

    if ((*flag != 0) && (inputTargetMode != -1)) {
        session->transitionPhase = 2;
        session->transitionTarget = inputTargetMode;
        *flag = 0;
        return 1;
    }
    if ((duration * g_timedTransitionDurationScale) < session->transitionTimer) {
        session->transitionPhase = 2;
        session->transitionTarget = eight;
        return 1;
    }
    return 0;
}
