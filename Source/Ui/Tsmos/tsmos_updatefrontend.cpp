#include "Common/menu_screen_elements.h"
#include "Common/shared_gameslot.h"
#include "Common/record.h"
#include "Common/statepair.h"
#include "Ui/Tsmos/TSMOS.h"
#include "Common/archive_chunk_images.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/weapon_screen_message_operations.h"
#include "Frontend/node_getimagetexture.h"
#include "Frontend/random_setuprandomteams.h"
#include "Resmgr/tsmos_updatefrontend.h"
#include "Resmgr/tsmos_setidletimer.h"
#include "Ui/Quag/N64_Eng.h"
#include "Resmgr/frame_heap_marks.h"
#include "menu.h"
#include "Ui/g_frontendshutdownstate.h"
#include "Ui/ui_address_symbols.h"

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
        if (g_frontendShutdownState.x == 1) {
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
