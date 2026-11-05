#include "Frontend/frontend_dispatchplayercountevent.h"
#include "include_asm.h"
#include "Common/runtime_declarations.h"
#include "Playercount/frontend_createplayercountscreende.h"
#include "Ui/Tsmos/Smp/smp_fade.h"
#include "Common/selectionscreenstate.h"
#include "Common/shared_menureply.h"
#include "Frontend/node_findwidgetbyresourceid.h"
#include "Ui/X_files/x_stdio.h"
#include "Smp/smp_slider.h"
#include "Smp/smp_button.h"
#include "Smp/smp_flicker.h"
#include "Frontend/frontend_address_symbols.h"
#include "Common/menu_options_and_results.h"
#include "Common/aiprofile.h"
#include "Common/match_settings.h"
#include "types.h"
#include "Common/pakqueuestate.h"
#include "Common/menu_screen_elements.h"
#include "Frontend/frontend_dispatchplayercountevent.h"
#include "Render/soundelement_playflatsound.h"
#include "Scene/cache_freememory.h"
#include "Playercount/frontend_updateplayercountscreen.h"
#include "Common/screen.h"
#include "Common/gameplay_settings.h"

/* unit FRONTEND_INCREASEPLAYERCOUNT_DATA.CPP */
const unsigned char s_playerCountFormatStorage[] = {
    0x25, 0x64, 0x00,
#if defined(VERSION_EU_X)
    /* Retained suffix at 800E9373; total storage ends at 800E9380. */
    0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x0F, 0x00,
#endif
#if defined(VERSION_DE)
    /* Retained suffix at 800DDB33; total storage ends at 800DDB40. */
    0x7C, 0x00, 0x42, 0xE2, 0xC0, 0x00, 0x42, 0xE3, 0x1C, 0x00, 0x42, 0xE3, 0x74,
#endif
#if defined(VERSION_EU)
    0xD3,
#endif
#if defined(VERSION_US)
    0x00,
#endif
#if defined(VERSION_US_REV1)
    0x10,
#endif
};

/* unit FRONTEND_CREATEPLAYERCOUNTSCREENDE.CPP */
#if defined(VERSION_DE)

/* Builds the 0x24-byte state g_playerCountScreen from the resources 0x392 to 0x397, hooks its list at 0x14 into the part Node_FindWidgetByResourceId returns for 0x397 and registers it with XStdio_FormatBuffer; returns zero. */
s32 Frontend_CreatePlayerCountScreenDe(s32 root) {
    MenuWidget *part;
    g_playerCountScreen = (struct PlayerCountScreenState *)Cache_AllocateMemory(36);
    Tsmos_ActivateControllerState();
    g_playerCountScreen->menu = SmpFade_CreateFadeWidget(914, 915);
    SmpSlider_EnableTransition(g_playerCountScreen->menu);
    SmpButton_WrapButtonWidget(918);
    part = (MenuWidget *)Node_FindWidgetByResourceId(root, 916);
    g_playerCountScreen->window = part;
    part->alpha = 0xF;
    g_playerCountScreen->button = SmpFlicker_CreateFlickerWidget(917, 110);
    g_playerCountScreen->delay = 3;
    part = (MenuWidget *)Node_FindWidgetByResourceId(root, 919);
    part->text = g_playerCountScreen->text;
    g_playerCountScreen->value = 1;
    XStdio_FormatBuffer(g_playerCountScreen->text, s_playerCountFormat, 1);
    return 0;
}
#endif

/* unit FRONTEND_UPDATEPLAYERCOUNTSCREEN.CPP */
/* Releases the object g_playerCountScreen holds through Cache_FreeMemory, clears g_playerCountScreen and returns zero. */
s32 Frontend_DestroyPlayerCountScreen(void) {
    Cache_FreeMemory(g_playerCountScreen);
    g_playerCountScreen = 0;
    return 0;
}

/* Runs the screen g_playerCountScreen each frame: past stage 1 of g_selectionMessageStage it only calls Tsmos_DeactivateControllerState;
   otherwise it calls Tsmos_ActivateControllerState and, while its menu reports 3, counts the delay at 0xC down and
   on expiry scrolls the list at 0x8 back one row, wrapping to the menu's own row count, and
   restarts the delay at 3; when the menu reports 4 it calls MarkMenuEventHandled and leaves through
   SmXlate_SwitchScreen with the stored target or Menu_ReturnToPreviousScreen when that is -1. Returns zero. Written
   from the assembly as a switch on the menu result, matching on the first trial. */
s32 Frontend_UpdatePlayerCountScreen(void) {
    s32 result;

    if (g_selectionMessageStage >= 2) {
        Tsmos_DeactivateControllerState();
        return 0;
    }
    Tsmos_ActivateControllerState();
    switch (result = SmpSlider_GetTransitionMode(((SettingsScreenState *)g_playerCountScreen)->head.menu)) {
    case 3:
        if (--((SettingsScreenState *)g_playerCountScreen)->head.delay <= 0) {
            ((SettingsScreenState *)g_playerCountScreen)->head.list->y--;
            if (((SettingsScreenState *)g_playerCountScreen)->head.list->y + ((SettingsScreenState *)g_playerCountScreen)->head.list->height < 0) {
                ((SettingsScreenState *)g_playerCountScreen)->head.list->y = ((SettingsScreenState *)g_playerCountScreen)->head.menu->list->height;
            }
            ((SettingsScreenState *)g_playerCountScreen)->head.delay = result;
        }
        break;
    case 4:
        MarkMenuEventHandled();
        if (((SettingsScreenState *)g_playerCountScreen)->head.target != -1) {
            SmXlate_SwitchScreen(((SettingsScreenState *)g_playerCountScreen)->head.target);
            return 0;
        }
        Menu_ReturnToPreviousScreen();
        break;
    default:
        return 0;
    }
    return 0;
}

/* Activates the requested player slots and creates any missing players when entering the screen. */
int Frontend_ConfirmPlayerCount(void) {
    int i;
    Shared_PlayerSettingsRecord *slot;

    MarkMenuEventHandled();
    ((SettingsScreenState *)g_playerCountScreen)->head.target = 7;
    SmpSlider_SetTransitionMode(((SettingsScreenState *)g_playerCountScreen)->head.menu, 2);
    for (i = 0; i < ((SettingsScreenState *)g_playerCountScreen)->count; i++) {
        slot = &g_playerSettings[i];
        slot->enabled = 1;
        slot->slot = i;
        if (g_profileSlotIndices[i][0] < 0) {
            Player_InitializeProfileSlot(i);
        }
    }
    return 0;
}

/* Marks the event handled, flags the screen as cancelled and starts its exit transition. Returns zero. */
s32 Frontend_CancelPlayerCount(void) {
    SettingsScreenState *state;

    MarkMenuEventHandled();
    state = g_playerCountScreen;
    state->head.target = -1;
    SmpSlider_SetTransitionMode(state->head.menu, 2);
    return 0;
}

/* Slider-up handler: when pressed, marks the event handled, raises the player count while the next controller is connected and below the connected total, shows the count with s_playerCountFormat and plays the click sound. Returns zero. */
s32 Frontend_IncreasePlayerCount(void *menuObject, void *unusedEvent, void *unusedContext, s32 press) {
    SettingsScreenState *object;

    if (press != 1) {
        return 0;
    }
    MarkMenuEventHandled();
    if (Control_IsControllerConnected(((SettingsScreenState *)g_playerCountScreen)->count) == press) {
        object = g_playerCountScreen;
        if (object->count < Control_CountConnectedControllers()) {
            ((SettingsScreenState *)g_playerCountScreen)->count++;
        }
    }
    XStdio_FormatBuffer(g_playerCountScreen->text, s_playerCountFormat, ((SettingsScreenState *)g_playerCountScreen)->count);
    SoundElement_PlayFlatSound(3713);
    return 0;
}

/* Slider-down handler: when pressed, marks the event handled, lowers the player count by one while it is at least 2, shows the count with s_playerCountFormat and plays the click sound. Returns zero. */
s32 Frontend_DecreasePlayerCount(void *first, void *second, void *third, s32 fourth) {
    s32 value;

    if (fourth != 1) {
        return 0;
    }
    MarkMenuEventHandled();
    value = ((SettingsScreenState *)g_playerCountScreen)->count;
    if (value >= 2) {
        ((SettingsScreenState *)g_playerCountScreen)->count = value - 1;
    }
    XStdio_FormatBuffer(g_playerCountScreen->text, s_playerCountFormat, ((SettingsScreenState *)g_playerCountScreen)->count);
    SoundElement_PlayFlatSound(3713);
    return 0;
}

/* Calls the handler registered for eventId (tables g_playerCountEventIds, g_playerCountEventActorKinds, g_playerCountEventHandlers). A row matches when its event equals eventId and its kind equals the actor's kind or is the any-kind wildcard 0x7530. Returns the handler's result, or zero when no row matches. */
s32 Frontend_DispatchPlayerCountEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    PlayerCountEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuWidget *actor;

    if (g_playerCountEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_playerCountEventHandlers;
        index = 0;
        do {
            if (g_playerCountEventIds[index].value == eventId) {
                actor = widget;
                actor_kind = actor->resource;
                table_kind = g_playerCountEventActorKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(widget, eventId, eventData0, eventData1, eventData2);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}

/* unit FRONTEND_CREATEPLAYERCOUNTSCREENEU.CPP */
#if defined(VERSION_EU)
#include "types.h"
#include "Ui/Tsmos/Smp/smp_fade.h"
#include "Smp/smp_slider.h"
#include "Smp/smp_button.h"
#include "Smp/smp_flicker.h"
#include "Frontend/frontend_address_symbols.h"

/* Builds a three-row slider popup in its 0x24-byte state g_playerCountScreen: title/list from the ids at 0x398, the numeric
   readout item at 0x39D showing the text at +0x14 formatted with s_playerCountFormat. Returns 0. */
s32 Frontend_CreatePlayerCountScreenEu(void *window) {
    MenuWidget *item;
    void *title;

    g_playerCountScreen = Cache_AllocateMemory(36);
    Tsmos_ActivateControllerState();
    title = SmpFade_CreateFadeWidget(920, 921);
    g_playerCountScreen->menu = title;
    SmpSlider_EnableTransition(title);
    SmpButton_WrapButtonWidget(924);
    item = Node_FindWidgetByResourceId(window, 922);
    g_playerCountScreen->window = item;
    item->alpha = 15;
    g_playerCountScreen->button = SmpFlicker_CreateFlickerWidget(923, 110);
    g_playerCountScreen->delay = 3;
    item = Node_FindWidgetByResourceId(window, 925);
    item->text = g_playerCountScreen->text;
    g_playerCountScreen->value = 1;
    XStdio_FormatBuffer(g_playerCountScreen->text, s_playerCountFormat, 1);
    return 0;
}
#endif

/* unit FRONTEND_CREATECOURSEOPTIONSMENU.CPP */
#if defined(VERSION_US_REV1)
#include "Common/selectionscreenstate.h"
#include "Common/player_join_requests.h"
#include "types.h"
#include "Common/shared_menureply.h"
#endif
#if defined(VERSION_EU_X)
#include "types.h"
#include "Playercount/frontend_createcourseoptionsmenu.h"
#include "Ui/Tsmos/Smp/smp_fade.h"
#include "Smp/smp_slider.h"
#include "Smp/smp_button.h"
#include "Smp/smp_flicker.h"
#include "Frontend/frontend_address_symbols.h"

/* Builds a three-row slider popup in its 0x24-byte state g_playerCountScreen: title/list from the ids at 0x39C, the numeric
   readout item at 0x39D showing the text at +0x14 formatted with s_playerCountFormat. Returns 0. */
s32 Frontend_CreatePlayerCountScreenEux(void *window) {
    MenuWidget *item;
    void *title;

    g_playerCountScreen = Cache_AllocateMemory(36);
    Tsmos_ActivateControllerState();
    title = SmpFade_CreateFadeWidget(924, 925);
    g_playerCountScreen->menu = title;
    SmpSlider_EnableTransition(title);
    SmpButton_WrapButtonWidget(928);
    item = Node_FindWidgetByResourceId(window, 926);
    g_playerCountScreen->window = item;
    item->alpha = 15;
    g_playerCountScreen->button = SmpFlicker_CreateFlickerWidget(927, 110);
    g_playerCountScreen->delay = 3;
    item = Node_FindWidgetByResourceId(window, 929);
    item->text = g_playerCountScreen->text;
    g_playerCountScreen->value = 1;
    XStdio_FormatBuffer(g_playerCountScreen->text, s_playerCountFormat, 1);
    return 0;
}
#endif

/* unit FRONTEND_CREATEPLAYERCOUNTSCREEN.CPP */
#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* Builds screen state g_playerCountScreen: allocates 0x24 bytes, sets up the handle for resources
   0x398/0x399, loads resource 0x39C, wires up windows 0x39A and 0x39D, the 0x39B button and
   the delay, and formats s_playerCountFormat into the state's text buffer through XStdio_FormatBuffer. */

#include "types.h"
#include "Frontend/frontend_dispatchplayercountevent.h"
#include "Ui/Tsmos/Smp/smp_fade.h"
#include "Smp/smp_slider.h"
#include "Frontend/frontend.h"
#define PLAYERCOUNT_VIEW_US ((struct PlayerCountScreenState *)g_playerCountScreen)

s32 Frontend_CreatePlayerCountScreen(s32 screenData) {
    struct PlayerCountScreenState *state;
    s32 handle;
    struct MenuWidget *node;
    void *text;

    g_playerCountScreen = (SettingsScreenState *)Cache_AllocateMemory(36);
    Tsmos_ActivateControllerState();
    handle = SmpFade_CreateFadeWidget(920, 921);
    state = PLAYERCOUNT_VIEW_US;
    state->menu = handle;
    SmpSlider_EnableTransition(handle);
    SmpButton_WrapButtonWidget(924);
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
