#include "COMMON/INTEGERSTATE530.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RECORD.H"
#include "COMMON/STATEPAIR.H"
#include "UI/TSMOS/TSMOS.H"
#include "COMMON/SLOTRECATCV1.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "FRONTEND/NODE_GETIMAGETEXTURE.H"
#include "FRONTEND/RANDOM_SETUPRANDOMTEAMS.H"
#include "RESMGR/TSMOS_UPDATEFRONTEND.H"
#include "RESMGR/TSMOS_SETIDLETIMER.H"
#include "UI/QUAG/N64_ENG.H"
#include "RESMGR/FRAME_HEAP_MARKS.H"
#include "MENU.H"

extern s32 g_frontendShutdownState;
extern u8 g_controllerPakFrontendState;
void Tsmos_UpdateFrontend(void) {
    s32 mode;
    s32 value;
    s32 active;
    s32 state;
    if (g_frontendActiveState == 1) {
        ESmem_SwapFrameHeap();
        mode = GetMenuScreenOwner();
        Menu_RouteElementEvent(mode, 3592, 0, 0, 0);
        Menu_DrawScreenStack();
        Node_EvictExpiredImages();
        N64Eng_AdvanceFrameCounter();
        mode = GetMenuScreenOwner();
        active = 1;
        value = 0;
        if (mode == 3) {
            goto mode_three;
        }
        if (mode != 24) {
            goto mode_inactive;
        }
        value = 20;
        goto mode_done;
mode_three:
        value = 300;
        goto mode_done;
mode_inactive:
        active = 0;
mode_done:
        if ((g_gameSettings.counters.transitionActive == 0) && (active == 1) && ((f32)(value * 15) < g_frontendTimerState.value)) {
            Random_SetupRandomTeams();
            Stage_StartConfiguredMatch();
            Tsmos_SetIdleTimer(0.0f);
        }
        g_frontendTimerState.value += g_frameElapsedTime;
        state = g_frontendTimerState.state;
        if (state == 1) {
            g_frontendTransitionCountdown--;
            if (g_frontendTransitionCountdown <= 0) {
                g_frontendTransitionCountdown = 60;
                g_controllerPakFrontendState = state;
            }
        }
        if (g_frontendShutdownState == 1) {
            Tsmos_ShutdownFrontend();
        }
    }
}
#if defined(VERSION_EU)
void Tsmos_InitializeEuropeanFrontend(void);
#else
void InitFrontendMenus(void);
#endif
void Join_ResetJoinRequestEntries(void);
void Tsmos_InitFrontendOnce(void) {
    if (g_frontendActiveState == 0) {
        Join_ResetJoinRequestEntries();
#if defined(VERSION_EU)
        Tsmos_InitializeEuropeanFrontend();
#else
        InitFrontendMenus();
#endif
    }
}
