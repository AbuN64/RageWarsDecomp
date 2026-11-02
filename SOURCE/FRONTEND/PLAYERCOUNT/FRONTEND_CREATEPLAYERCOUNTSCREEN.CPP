#include "COMMON/SETTINGSRECAT24.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "TYPES.H"
#include "COMMON/SHARED_MENUREPLY.H"

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* Builds screen state g_playerCountScreen: allocates 0x24 bytes, sets up the handle for resources
   0x398/0x399, loads resource 0x39C, wires up windows 0x39A and 0x39D, the 0x39B button and
   the delay, and formats s_playerCountFormat into the state's text buffer through XStdio_FormatBuffer. */

#include "TYPES.H"
#include "FRONTEND/FRONTEND_DISPATCHPLAYERCOUNTEVENT.H"
#define PLAYERCOUNT_VIEW_US ((struct PlayerCountScreenState *)g_playerCountScreen)

extern s32 SmpFade_CreateFadeWidget(s32, s32);
extern void SmpSlider_EnableTransition(struct Access_s32_5C *object);
extern s32 XStdio_FormatBuffer(void *goal, s32 fmt0, ...);

s32 Frontend_CreatePlayerCountScreen(s32 screenData) {
    struct PlayerCountScreenState *state;
    s32 handle;
    struct MenuWidget *node;
    void *text;

    /* the hub's allocation helper returns its SelectionScreenState view; this unit keeps its own state type */
    g_playerCountScreen = (SettingsScreenState *)Cache_AllocateMemory(36);
    Tsmos_ActivateControllerState();
    handle = SmpFade_CreateFadeWidget(920, 921);
    state = PLAYERCOUNT_VIEW_US;
    state->menu = handle;
    SmpSlider_EnableTransition(handle);
    SmpButton_WrapButtonWidget(924);
    /* the MenuWidget view names the alpha byte at +0x10 and the text pointer at +0x34 that the hub's Item omits */
    node = (struct MenuWidget *) Node_FindWidgetByResourceId((void *) screenData, 922);
    state = PLAYERCOUNT_VIEW_US;
    state->window = node;
    node->alpha = 15;
    handle = SmpFlicker_CreateFlickerWidget(923, 110);
    state = PLAYERCOUNT_VIEW_US;
    state->button = handle;
    state->delay = 3;
    node = (struct MenuWidget *) Node_FindWidgetByResourceId((void *) screenData, 925);
    state = PLAYERCOUNT_VIEW_US;
    text = &state->text;
    node->text = text;
    state->value = 1;
    XStdio_FormatBuffer(text, s_playerCountFormat, 1);
    return 0;
}
#endif
