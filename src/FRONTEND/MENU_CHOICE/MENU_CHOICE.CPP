#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SHARED_MENUREPLY.H"

/* Runs the screen g_playModeMenuState each frame: past stage 1 of g_selectionMessageStage it only calls Tsmos_DeactivateControllerState;
   otherwise it calls Tsmos_ActivateControllerState and, while the opening delay at 0xC runs, counts it down and
   calls SmpSlider_EnableTransition on its menu when it expires; after that, while the menu reports 3, it counts
   the scroll delay at 0x14 down and on expiry scrolls the list at 0x8 back one row, wrapping to
   the menu's own row count, and restarts the delay at 3, and when the menu reports 4 it calls
   MarkMenuEventHandled and leaves through SmXlate_SwitchScreen with the target at 0x18. Returns zero. Adapted
   from Frontend_UpdatePlayerCountScreen with the opening delay added, the scroll delay and target moved and the -1
   target test removed. */







extern struct StateFrontendUpdatePlayModeMenu *g_playModeMenuState;
extern void Tsmos_DeactivateControllerState(void);
extern s32 SmpSlider_GetTransitionMode(s32 *record);
extern void SmpSlider_EnableTransition(struct Access_s32_5C *object);

s32 Frontend_UpdatePlayModeMenu(void) {
    s32 result;

    if (g_selectionMessageStage >= 2) {
        Tsmos_DeactivateControllerState();
        return 0;
    }
    Tsmos_ActivateControllerState();
    if (g_playModeMenuState->opening > 0) {
        if (--g_playModeMenuState->opening == 0) {
            SmpSlider_EnableTransition(g_playModeMenuState->menu);
            return 0;
        }
        return 0;
    }
    switch (result = SmpSlider_GetTransitionMode(g_playModeMenuState->menu)) {
    case 3:
        if (--g_playModeMenuState->delay <= 0) {
            g_playModeMenuState->list->transitionTimer--;
            if (g_playModeMenuState->list->transitionTimer + g_playModeMenuState->list->transitionDuration < 0) {
                g_playModeMenuState->list->transitionTimer = g_playModeMenuState->menu->list->transitionDuration;
            }
            g_playModeMenuState->delay = result;
        }
        break;
    case 4:
        MarkMenuEventHandled();
        SmXlate_SwitchScreen(g_playModeMenuState->target);
        break;
    default:
        return 0;
    }
    return 0;
}
