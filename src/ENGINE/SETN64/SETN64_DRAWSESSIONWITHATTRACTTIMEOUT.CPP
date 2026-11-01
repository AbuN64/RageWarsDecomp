#include "COMMON/SHARED_GAMESLOT.H"
#include "include_asm.h"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/PAKQUEUESTATE.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/ROUND_STATE_VARIANTS.H"
#include "SCENE/SCENE_UPDATEANDDRAWWORLD.H"

/* Requests a switch of the session into mode 0x14: when the pending 0x1000 flag is set outside modes 0xB and 0xC and a target is given it records that target with phase 2 and clears the flags; otherwise, once Cinema_IsSequenceIdle accepts the flags, it saves the current mode, enters mode 0x14 with the given argument at phase 1, and sets the timer when Control_IsSnapshotActive_Camera allows. */



extern s32 Cinema_IsSequenceIdle(s32 *flags);

void SetN64_HandleSessionTransitionInput(GameSession *session, s32 cancelTarget, s32 target) {
    s32 pending;
    s32 *flags;

    flags = (s32 *)&g_combinedControllerProfile.pressedButtons;
    pending = *flags & 0x1000;
    if ((unsigned)(session->mode - 11) < 2) {
        pending = 0;
    }
    if (pending != 0 && target != -1) {
        session->phase = 2;
        session->target = target;
        *flags = 0;
        return;
    }
    if (Cinema_IsSequenceIdle(flags) != 0) {
        s32 mode = session->mode;

        session->phase = 1;
        session->timer = 0;
        session->mode = 20;
        session->target = cancelTarget;
        session->previousMode = mode;
        if (Control_IsSnapshotActive() != 0) {
            session->timer = (1.0f);
        }
    }
}

/* Calls cleanup functions on a game state and optionally transitions control state when conditions change. */




extern void SmXlate_SwitchScreen(s32 index);
extern void SetN64_BeginModeTransition(GameSession *session, s32 targetMode);
extern void Gsky_DrawPlayerListNoOp(void *unusedSession);
extern void SetN64_DrawSessionFade(struct GameSession *session);





void SetN64_DrawSessionWithAttractTimeout(void *session) {
    GameSession *state;
    f32 value;

    state = session;
    if (g_attractTimeoutEnabled == 1) {
        value = state->transitionTime;
        if (g_attractTimeoutBegin < value) {
            if (g_attractTimeoutFinish < value) {
                g_attractTimeoutEnabled = 0;

#if defined(VERSION_EU)
Tsmos_InitializeEuropeanFrontend
#else
InitFrontendMenus
#endif
();
                SmXlate_SwitchScreen(2);
                Frontend_RequestScreenMode(0);
                SetN64_BeginModeTransition(state, 1);
                state->transitionTime = 0;
            } else if (g_combinedControllerProfile.buttons != 0) {
                g_attractTimeoutEnabled = 0;

#if defined(VERSION_EU)
Tsmos_InitializeEuropeanFrontend
#else
InitFrontendMenus
#endif
();
                SmXlate_SwitchScreen(2);
                SetN64_BeginModeTransition(state, 8);
                state->transitionTime = 0;
            }
        }
    }
    Scene_UpdateAndDrawWorld(&state->world);
    Gsky_DrawPlayerListNoOp(state->players);
    OnScreen_DrawStatusBars(&state->hud);
    /* Only us-rev1 makes this call: us, eu, eu-x and de go straight on to SetN64_DrawSessionFade, two
       instructions shorter, as each cartridge's own bytes show. */
#ifdef VERSION_US_REV1
    Tengine_UpdateArtsendTexturePreview();
#endif
    SetN64_DrawSessionFade(state);
}

#include "COMMON/SESSIONHANDLERROW.H"








void SetN64_AdvanceGameClock(GameSession *world) {
    f32 t1;
    f32 t2;
    f32 t3;

    if (world->clockPaused == 0) {
        t1 = g_gameSettings.counters.m_GameTimeFifteenth + g_frameElapsedTime;
        g_gameSettings.counters.m_GameTimeFifteenth = t1;
        if (g_gameClockTicksPerSecond <= t1) {
            t2 = g_gameSettings.counters.m_GameTimeSeconds + g_gameClockUnitIncrement;
            g_gameSettings.counters.m_GameTimeFifteenth = t1 - g_gameClockTicksPerSecond;
            g_gameSettings.counters.m_GameTimeSeconds = t2;
            if (g_gameClockSecondsPerMinute <= t2) {
                t3 = g_gameSettings.counters.m_GameTimeMinutes + g_gameClockUnitIncrement;
                g_gameSettings.counters.m_GameTimeSeconds = t2 - g_gameClockSecondsPerMinute;
                g_gameSettings.counters.m_GameTimeMinutes = t3;
                if (g_gameClockSecondsPerMinute <= t3) {
                    g_gameSettings.counters.m_GameTimeMinutes = t3 - g_gameClockSecondsPerMinute;
                    g_gameSettings.counters.m_GameTimeHours = g_gameSettings.counters.m_GameTimeHours + g_gameClockUnitIncrement;
                }
            }
        }
    }
}

#include "COMMON/SESSIONHANDLERROW.H"
extern f32 g_roundTimeoutBegin, g_roundTimeoutFinish;
extern void Gsky_DrawPlayerListNoOp(void *);
extern void SmXlate_SwitchScreen(s32);
extern void SetN64_BeginModeTransition(GameSession *, s32);
extern void SetN64_DrawSessionFade(GameSession *);

void SetN64_DrawSessionWithRoundTimeout(GameSession *session) {
    CGameStatus *counters = &g_gameSettings.counters;
    f32 time;
    if (counters->transitionActive == 1) {
        time = session->transitionTime;
        if (g_roundTimeoutBegin < time) {
            if (g_roundTimeoutFinish < time) {
                counters->transitionActive = 0;
                stopRoundPlatform();
                SmXlate_SwitchScreen(2);
                Frontend_RequestScreenMode(0);
                SetN64_BeginModeTransition(session, 1);
                session->transitionTime = 0;
            } else if (g_combinedControllerProfile.buttons != 0) {
                counters->transitionActive = 0;
                stopRoundPlatform();
                SmXlate_SwitchScreen(2);
                SetN64_BeginModeTransition(session, 8);
                session->transitionTime = 0;
            }
        }
    }
    Scene_UpdateAndDrawWorld(&session->world);
    Gsky_DrawPlayerListNoOp(session->players);
    OnScreen_DrawStatusBars(&session->hud);
#ifdef VERSION_US_REV1
    Tengine_UpdateArtsendTexturePreview();
#endif
    SetN64_DrawSessionFade(session);
}
