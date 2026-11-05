#include "include_asm.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/selectionscreenstate.h"
#include "Ui/Tsmos/Smp/smp_fade.h"
#include "Engine/defs.h"
#include "Data/g_unlockgatedlistscreen.h"
#include "Frontend/widget_findwidgetatpoint.h"
#include "Common/animation.h"
#include "Menu/Unlocklist/menu_createunlockgatedlistscreen_symbols.h"
#include "Common/sharedplayer.h"
#include "Common/menulistscreen.h"
#include "Common/menu_overlay.h"
#include "Scene/cache_freememory.h"
#include "Playercount/frontend_updateplayercountscreen.h"
#include "Common/screen.h"
#include "Common/shared_menureply.h"
#include "Common/playerprofiles.h"
#include "Menu/menu_advancefademeter.h"
#include "Menu/Unlocklist/menu_updatescrollingchoicescreen_symbols.h"
#include "Common/aiprofile.h"
#include "Common/cheatcode.h"
#include "Menu/menu_dispatchsettingscolumnevent.h"
#include "Common/menuselectionmessage.h"
#include "Frontend/node_findwidgetbyresourceid.h"
#include "Data/g_titlebuttonscreen.h"
#include "Common/triple.h"
#if ((defined(VERSION_EU_X)))
#include "Common/resident_event_handler.h"
#include "Frontend/frontend.h"
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1) || defined(VERSION_EU_X) || defined(VERSION_EU) || defined(VERSION_DE)

/* Resource ids of this screen are numbered per version (relative to us): eu-x 4, de -2. */
static inline s32 unlockRes_menuCreateunlockgatedlistscreen(s32 id) {
#if defined(VERSION_EU_X)
    return id + 4;
#elif defined(VERSION_DE)
    return id - 2;
#else
    return id;
#endif
}

s32 Menu_CreateUnlockGatedListScreen(void *window) {
    void *obj;

    g_unlockGatedListScreen = (Shared_MenuWidgetState *)Cache_AllocateMemory(24);
    ((struct StateMenuUpdateScrollingChoiceScreen *)g_unlockGatedListScreen)->list = SmpFade_CreateFadeWidget(unlockRes_menuCreateunlockgatedlistscreen(310), unlockRes_menuCreateunlockgatedlistscreen(311));
    g_unlockGatedListScreen->seen = 0;

    if (Defs_TestBit(g_profileModePlayedLevels[0], 0) == 0) {
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(window, unlockRes_menuCreateunlockgatedlistscreen(314)), 1);
    }

    g_unlockGatedListScreen->resourceWidget = SmpFlicker_CreateFlickerWidget(unlockRes_menuCreateunlockgatedlistscreen(313), 110);

    obj = Node_FindWidgetByResourceId(window, unlockRes_menuCreateunlockgatedlistscreen(312));
    g_unlockGatedListScreen->item = obj;
    ((ListScreenItem *)obj)->alpha = 15;

    g_unlockGatedListScreen->scrollDelay = 3;
    g_unlockGatedListScreen->nextScreen = -1;
    return 0;
}
#endif

#if defined(VERSION_DE)
enum { MENU_RESOURCE = 313 };
#elif defined(VERSION_EU)
enum { MENU_RESOURCE = 315 };
#elif defined(VERSION_EU_X)
enum { MENU_RESOURCE = 319 };
#elif defined(VERSION_US_REV1) || defined(VERSION_US)
enum { MENU_RESOURCE = 315 };
#endif

/* Releases the object g_unlockGatedListScreen holds through Cache_FreeMemory, clears g_unlockGatedListScreen and returns zero. */
/* Handles menu selection and updates the active menu state. */

 void MarkMenuEventHandled(void);

 

s32 Menu_FreeScrollingChoiceScreen(void) {
    Cache_FreeMemory(g_unlockGatedListScreen);
    g_unlockGatedListScreen = 0;
    return 0;
}

/* Calls SmpButton_WrapButtonWidget with 0x13B, 0x13A and 0x13C in turn and returns zero. */
s32 Menu_WrapScrollingChoiceNodes(void) {
#if defined(VERSION_DE)
    SmpButton_WrapButtonWidget(313);
    SmpButton_WrapButtonWidget(312);
    SmpButton_WrapButtonWidget(314);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    SmpButton_WrapButtonWidget(315);
    SmpButton_WrapButtonWidget(314);
    SmpButton_WrapButtonWidget(316);
#elif defined(VERSION_EU_X)
    SmpButton_WrapButtonWidget(319);
    SmpButton_WrapButtonWidget(318);
    SmpButton_WrapButtonWidget(320);
#endif
    return 0;
}

s32 Menu_UpdateScrollingChoiceScreen(void) {
    s32 result;
    s32 target;

    switch (result = SmpSlider_GetTransitionMode(((struct StateMenuUpdateScrollingChoiceScreen *)g_unlockGatedListScreen)->menu)) {
    case 1:
        if (g_unlockGatedListScreen->seen != 0) {
            return 0;
        }
        g_unlockGatedListScreen->seen = result;
        if (Defs_TestBit(((Profile *)g_localPlayerProfiles)->levelFlags[0], 0) != 0) {
            return 0;
        }
        Menu_SetFocusedElement(MENU_RESOURCE);
        return 0;
    case 3:
        if (--((struct StateMenuUpdateScrollingChoiceScreen *)g_unlockGatedListScreen)->delay <= 0) {
            ((struct StateMenuUpdateScrollingChoiceScreen *)g_unlockGatedListScreen)->list->y--;
            if (((struct StateMenuUpdateScrollingChoiceScreen *)g_unlockGatedListScreen)->list->y + ((struct StateMenuUpdateScrollingChoiceScreen *)g_unlockGatedListScreen)->list->height < 0) {
                ((struct StateMenuUpdateScrollingChoiceScreen *)g_unlockGatedListScreen)->list->y = ((struct StateMenuUpdateScrollingChoiceScreen *)g_unlockGatedListScreen)->menu->list->height;
            }
            ((struct StateMenuUpdateScrollingChoiceScreen *)g_unlockGatedListScreen)->delay = result;
        }
        break;
    case 4:
        MarkMenuEventHandled();
        target = ((struct StateMenuUpdateScrollingChoiceScreen *)g_unlockGatedListScreen)->target;
        if (target == -1) {
            target = 3;
        }
        SmXlate_SwitchScreen(target);
        break;
    default:
        return 0;
    }
    return 0;
}

s32 Menu_CancelScrollingChoiceScreen(void) {
    struct StateMenuUpdateScrollingChoiceScreen *state;

    MarkMenuEventHandled();
    state = g_unlockGatedListScreen;
    state->target = -1;
    SmpSlider_SetTransitionMode(state->menu, 2);
    return 0;
}

s32 Menu_HandleScrollingChoice(void) {
    s32 focusedElementIdResult;
    s32 unusedInteger1;
    MarkMenuEventHandled();
    focusedElementIdResult = Menu_GetFocusedElementId();
    switch (focusedElementIdResult) { /* irregular */
#if defined(VERSION_DE)
    case 312 + 2:
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    case 314 + 2:
#elif defined(VERSION_EU_X)
    case 318 + 2:
#endif
        ((struct StateMenuUpdateScrollingChoiceScreen *)g_unlockGatedListScreen)->target = -1;
        break;
#if defined(VERSION_DE)
    case 312 + 1:
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    case 314 + 1:
#elif defined(VERSION_EU_X)
    case 318 + 1:
#endif
        if (Defs_TestBit(g_profileModePlayedLevels[0], 0) == 0) {
            ((struct StateMenuUpdateScrollingChoiceScreen *)g_unlockGatedListScreen)->target = 7;
        } else {
            ((struct StateMenuUpdateScrollingChoiceScreen *)g_unlockGatedListScreen)->target = 30;
        }
        break;
#if defined(VERSION_DE)
    case 312:
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    case 314:
#elif defined(VERSION_EU_X)
    case 318:
#endif
        g_activeProfileCharacterSelections = g_profileCharacterSelections;
        ((struct StateMenuUpdateScrollingChoiceScreen *)g_unlockGatedListScreen)->target = 10;
        break;
    }
    SmpSlider_SetTransitionMode(((struct StateMenuUpdateScrollingChoiceScreen *)g_unlockGatedListScreen)->menu, 2);
    return 0;
}

#if defined(VERSION_DE)
/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_settingsColumnEventIds, an actor kind at g_settingsColumnEventKinds and a handler at g_settingsColumnEventHandlers: the first row whose event equals eventId and whose kind equals the actor's input kind, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. */
s32 Menu_DispatchSettingsColumnEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra) {
    MenuChoiceEventHandler *entry;
    MenuWidget *actor;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    s32 actorKind;
    s32 tableKind;

    if (g_settingsColumnEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_settingsColumnEventHandlers;
        index = 0;
        do {
            if (g_settingsColumnEventIds[index].value == eventId) {
                actor = eventObject;
                actor_kind = actor->resource;
                table_kind = g_settingsColumnEventKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(eventObject, eventId, eventPayload, eventValue, eventExtra);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}
#endif

/* Releases the object g_titleButtonScreen holds through Cache_FreeMemory, clears g_titleButtonScreen and returns zero. */
s32 Menu_CreateTitleButtonScreen(void *list) {
    struct ResourceSmpFlickerCreateFlickerWidget *item;
    g_titleButtonScreen = Cache_AllocateMemory(20);
#if defined(VERSION_DE)
    ((struct MenuMenuCreateTitleButtonScreen *)g_titleButtonScreen)->title = SmpFade_CreateFadeWidget(966, 966 + 1);
    ((struct MenuMenuCreateTitleButtonScreen *)g_titleButtonScreen)->button = SmpFlicker_CreateFlickerWidget(966 + 3, 110);
    item = Node_FindWidgetByResourceId(list, 966 + 2);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    ((struct MenuMenuCreateTitleButtonScreen *)g_titleButtonScreen)->title = SmpFade_CreateFadeWidget(972, 972 + 1);
    ((struct MenuMenuCreateTitleButtonScreen *)g_titleButtonScreen)->button = SmpFlicker_CreateFlickerWidget(972 + 3, 110);
    item = Node_FindWidgetByResourceId(list, 972 + 2);
#elif defined(VERSION_EU_X)
    ((struct MenuMenuCreateTitleButtonScreen *)g_titleButtonScreen)->title = SmpFade_CreateFadeWidget(976, 976 + 1);
    ((struct MenuMenuCreateTitleButtonScreen *)g_titleButtonScreen)->button = SmpFlicker_CreateFlickerWidget(976 + 3, 110);
    item = Node_FindWidgetByResourceId(list, 976 + 2);
#endif
    ((struct MenuMenuCreateTitleButtonScreen *)g_titleButtonScreen)->item = item;
    item->value = 15;
    ((struct MenuMenuCreateTitleButtonScreen *)g_titleButtonScreen)->count = 3;
    ((struct MenuMenuCreateTitleButtonScreen *)g_titleButtonScreen)->selection = -1;
    return 0;
}

s32 Menu_FreeTitleButtonScreen(void) {
    Cache_FreeMemory(g_titleButtonScreen);
    g_titleButtonScreen = 0;
    return 0;
}

#if !(defined(VERSION_DE) || defined(VERSION_EU_X))
/* Calls SmpButton_WrapButtonWidget with 0x3D0 and then 0x3D1, and returns zero. */
s32 Menu_WrapTitleButtonScreenNodes(void) {
    SmpButton_WrapButtonWidget(976);
    SmpButton_WrapButtonWidget(977);
    return 0;
}
#endif

#if defined(VERSION_DE)
/* Calls SmpButton_WrapButtonWidget with 0x3D0 and then 0x3D1, and returns zero. */
s32 Menu_WrapSettingsNodePair(void) {
#if defined(VERSION_DE)
    SmpButton_WrapButtonWidget(970);
    SmpButton_WrapButtonWidget(971);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    SmpButton_WrapButtonWidget(976);
    SmpButton_WrapButtonWidget(977);
#elif defined(VERSION_EU_X)
    SmpButton_WrapButtonWidget(980);
    SmpButton_WrapButtonWidget(981);
#endif
    return 0;
}
#endif

#if !(defined(VERSION_DE) || defined(VERSION_EU_X))
/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_scrollingChoiceEventIds, an actor kind at g_scrollingChoiceEventKinds and a handler at g_scrollingChoiceEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */








s32 Menu_DispatchScrollingChoiceEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra) {
    MenuChoiceEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuWidget *actor;

    if (g_scrollingChoiceEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_scrollingChoiceEventHandlers;
        index = 0;
        do {
            if (g_scrollingChoiceEventIds[index].event == eventId) {
                actor = eventObject;
                actor_kind = actor->resource;
                table_kind = g_scrollingChoiceEventKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(eventObject, eventId, eventPayload, eventValue, eventExtra);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}
#endif

#if defined(VERSION_EU_X)

s32 Menu_DispatchSettingsTableEvent(MenuWidget *pThis, s32 event, s32 eventPayload, s32 eventValue, s32 eventExtra) {
    s32 i;
    for (i = 0; g_scrollingChoiceEventIds[i].handler != 0; i++) {
        if (g_scrollingChoiceEventIds[i].event == event &&
            (g_scrollingChoiceEventIds[i].actorKind == pThis->resource || g_scrollingChoiceEventIds[i].actorKind == 30000)) {
            return g_scrollingChoiceEventIds[i].handler(pThis, event, eventPayload, eventValue, eventExtra);
        }
    }
    return 0;
}
#endif
