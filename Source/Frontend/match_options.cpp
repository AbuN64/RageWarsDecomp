#include "Common/menu_options_and_results.h"
#include "Common/aiprofile.h"
#include "Common/runtime_declarations.h"
#include "Common/player_join_requests.h"
#include "options.h"
#include "types.h"
#include "Common/selectionscreenstate.h"
#include "Common/screen.h"
#include "Common/menulistscreen.h"
#include "Frontend/join_getjoinrequestrank.h"
#include "Frontend/join_randomizejoinrequestentries.h"
#include "Frontend/frontend_activatematchoptionaction.h"
#include "Scene/cache_freememory.h"
#include "Common/shared_gameslot.h"
#include "Join/join_cyclejoinrequestrank.h"
#include "Ui/Tsmos/Smp/smp_button.h"
#include "Common/shared_menureply.h"
#include "Smp/smp_button.h"
#include "N64eng/n64eng.h"
#include "Frontend/frontend_address_symbols.h"
#include "include_asm.h"
#include "Common/frontend_resource_load_state.h"
#include "Common/resident_event_handler.h"
#include "Common/menu_overlay.h"
#include "Common/format.h"
#include "data_overlay_layouts.h"
#include "Match_options/frontend_creatematchoptions.h"
#include "Common/level_goal.h"
#include "Frontend/menuimage.h"
#include "Frontend/node_findwidgetbyresourceid.h"
#include "Widget/widget_findwidgetatpoint.h"

/* unit FRONTEND_ACTIVATEMATCHOPTIONACTION.CPP */
/* Refreshes the option block g_gameSettings from the widgets of the menu g_matchOptionsScreen points to: the four option bytes
   from the values N64Eng_GetNumericWidgetValue reports for its numeric widgets, and the selection byte from the
   selection SmpButton_GetListSelection reports for its list widget. */
void Frontend_StoreMatchOptionWidgets(void) {
    Shared_Game *options;
    s32 value;

    value = N64Eng_GetNumericWidgetValue(g_matchOptionsScreen->widget28);
    options = &g_gameSettings;
    options->laps = value;
    options->players = N64Eng_GetNumericWidgetValue(g_matchOptionsScreen->widget24);
    options->trialOther = N64Eng_GetNumericWidgetValue(g_matchOptionsScreen->widget2C);
    options->trialScore = N64Eng_GetNumericWidgetValue(g_matchOptionsScreen->widget30);
    options->multiplayerRuleBytes[0] = SmpButton_GetListSelection(g_matchOptionsScreen->selectWidget);
}

/* Synchronizes screen g_matchOptionsScreen's option widgets and player-count widget with the stored option
 * block g_gameSettings and the live player count: pushes the four stored option bytes back into their
 * checkbox widgets, sets the player-count widget to the lesser of the screen's cap and the live
 * player count (or the screen's default when that count is zero), and sets the selection and
 * cursor widgets from the stored selection byte and the current cursor value. */
void Frontend_LoadMatchOptionWidgets(void) {
    Shared_Game *opts;
    s32 count;
    s32 cap;

    opts = &g_gameSettings;
    N64Eng_SetNumericWidgetValue(g_matchOptionsScreen->widget24, opts->players);
    N64Eng_SetNumericWidgetValue(g_matchOptionsScreen->widget28, opts->laps);
    N64Eng_SetNumericWidgetValue(g_matchOptionsScreen->widget2C, opts->trialOther);
    N64Eng_SetNumericWidgetValue(g_matchOptionsScreen->widget30, opts->trialScore);
    count = Join_CountUsedSlots();
    cap = g_matchOptionsScreen->countCap;
    if (cap < count) {
        count = cap;
    }
    if (count == 0) {
        count = g_matchOptionsScreen->countDefault;
    }
    N64Eng_SetNumericWidgetValue(g_matchOptionsScreen->widget34, count);
    SmpButton_SelectListEntry(g_matchOptionsScreen->selectWidget, opts->multiplayerRuleBytes[0]);
    SmpButton_SelectListEntry(g_matchOptionsScreen->cursorWidget, Join_GetJoinRequestRank());
}

/* Refreshes the entry list of screen g_matchOptionsScreen: reads the selection of its cursor widget through
   SmpButton_GetListSelection and the entry count of its entry-list widget through N64Eng_GetNumericWidgetValue. With no entries it
   clears the list through Join_ResetJoinRequestEntries; otherwise, when the count differs from what
   Join_CountUsedSlots_FrontendActivatematchoptionaction shows or force is 1, it clears the list and rebuilds it for the count and
   selection through Join_RandomizeJoinRequestEntries. */
void Frontend_SyncMatchJoinSlots(s32 force) {
    s32 selection;
    s32 count;

    selection = SmpButton_GetListSelection(g_matchOptionsScreen->cursorWidget);
    count = N64Eng_GetNumericWidgetValue(g_matchOptionsScreen->widget34);
    if (count <= 0) {
        Join_ResetJoinRequestEntries();
        return;
    }
    if (count != Join_CountUsedSlots() || force == 1) {
        Join_ResetJoinRequestEntries();
        Join_RandomizeJoinRequestEntries(count, selection);
    }
}

/* Releases the object g_matchOptionsScreen holds through Cache_FreeMemory, clears g_matchOptionsScreen and returns zero. */
s32 Frontend_DestroyMatchOptions(void) {
    Cache_FreeMemory(g_matchOptionsScreen);
    g_matchOptionsScreen = 0;
    return 0;
}

/* Event handler placeholder: ignores the event and returns zero. */
s32 Frontend_ReturnMatchOptionsEventZero(void) {
    return 0;
}

s32 Frontend_ResetMatchOptionOnEvent(s32 element, s32 eventId, u32 eventData, s32 eventValue) {
    u32 kind;
    void *widget;
    s32 value;

    kind = eventData >> 16;
    if ((kind == 3) && (eventValue == 2)) {
        MarkMenuEventHandled();
        switch (Menu_GetFocusedElementId()) {
#if defined(VERSION_DE)
        case 863:
#elif defined(VERSION_EU_X)
        case 871:
#else
        case 867:
#endif
            widget = g_matchOptionsScreen->widget24;
            value = 0;
            N64Eng_SetNumericWidgetValue(widget, value);
            break;
#if defined(VERSION_DE)
        case 861:
#elif defined(VERSION_EU_X)
        case 869:
#else
        case 865:
#endif
            widget = g_matchOptionsScreen->widget28;
            value = 0;
            N64Eng_SetNumericWidgetValue(widget, value);
            break;
#if defined(VERSION_DE)
        case 859:
#elif defined(VERSION_EU_X)
        case 867:
#else
        case 863:
#endif
            widget = g_matchOptionsScreen->widget2C;
            value = 0;
            N64Eng_SetNumericWidgetValue(widget, value);
            break;
#if defined(VERSION_DE)
        case 865:
#elif defined(VERSION_EU_X)
        case 873:
#else
        case 869:
#endif
            widget = g_matchOptionsScreen->widget30;
            value = 0;
            N64Eng_SetNumericWidgetValue(widget, value);
            break;
#if defined(VERSION_DE)
        case 872:
#elif defined(VERSION_EU_X)
        case 880:
#else
        case 876:
#endif
            widget = g_matchOptionsScreen->widget34;
            value = g_matchOptionsScreen->countDefault;
            N64Eng_SetNumericWidgetValue(widget, value);
            break;
        }
    }
    return 0;
}

/* Handles the menu message Menu_GetFocusedElementId reports after MarkMenuEventHandled unless Frontend_GetMenuImageState reports
   screen g_matchOptionsScreen busy: 0x36B closes the menu through Frontend_StoreMatchOptionWidgets, sends code -1 to
   Random_SetMenuChoiceResult and calls Menu_ReturnToPreviousScreen; 0x369 does the same with page reset Frontend_SyncMatchJoinSlots(0)
   and code 0x17 when N64Eng_GetNumericWidgetValue reports the screen's entry-list widget non-empty; 0x36A always does
   it with Join_SeatJoinRequests and code 0x19, then calls Tsmos_DeactivateControllerState. Returns zero. */
s32 Frontend_ActivateMatchOptionAction(void) {
    MarkMenuEventHandled();
    if (Frontend_GetMenuImageState(g_matchOptionsScreen) == 1) {
        return 0;
    }
    switch (Menu_GetFocusedElementId()) {
#if defined(VERSION_DE)
    case 871:
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    case 875:
#elif defined(VERSION_EU_X)
    case 879:
#endif
        Frontend_StoreMatchOptionWidgets();
        Random_SetMenuChoiceResult(-1);
        Menu_ReturnToPreviousScreen();
        break;
#if defined(VERSION_DE)
    case 869:
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    case 873:
#elif defined(VERSION_EU_X)
    case 877:
#endif
        if (N64Eng_GetNumericWidgetValue(g_matchOptionsScreen->widget34) > 0) {
            Frontend_StoreMatchOptionWidgets();
            Frontend_SyncMatchJoinSlots(0);
            Random_SetMenuChoiceResult(23);
            Menu_ReturnToPreviousScreen();
        }
        break;
#if defined(VERSION_DE)
    case 870:
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    case 874:
#elif defined(VERSION_EU_X)
    case 878:
#endif
        Frontend_StoreMatchOptionWidgets();
        Frontend_SyncMatchJoinSlots(0);
        Join_SeatJoinRequests();
        Random_SetMenuChoiceResult(25);
        Menu_ReturnToPreviousScreen();
        Tsmos_DeactivateControllerState();
        break;
    }
    return 0;
}

/* Calls MarkMenuEventHandled and, unless Frontend_GetMenuImageState reports one for the object g_matchOptionsScreen holds, calls
   Frontend_StoreMatchOptionWidgets, Random_SetMenuChoiceResult with -1 and Menu_ReturnToPreviousScreen. Returns zero. */
s32 Frontend_ExitMatchOptions(void) {
    MarkMenuEventHandled();
    if (Frontend_GetMenuImageState(g_matchOptionsScreen) == 1) {
        return 0;
    }
    Frontend_StoreMatchOptionWidgets();
    Random_SetMenuChoiceResult(-1);
    Menu_ReturnToPreviousScreen();
    return 0;
}

s32 Frontend_RefreshMatchSlotsOnZeroEvent(void *first, void *second, void *third, s32 fourth) {
    if (fourth == 0) {
        Frontend_SyncMatchJoinSlots(1);
        return 0;
    }
    return 0;
}

s32 Frontend_RefreshMatchSlotsOnZeroEventAlt(void *first, void *second, void *third, s32 fourth) {
    if (fourth == 0) {
        Frontend_SyncMatchJoinSlots(1);
        return 0;
    }
    return 0;
}

/* Calls the handler registered for event (tables g_matchOptionsEventCodes, g_matchOptionsActorKinds, g_matchOptionsEventCallbacks). A row matches when its event equals event and its kind equals the actor's kind or is the any-kind wildcard 0x7530. Returns the handler's result, or zero when no row matches. */
s32 Frontend_DispatchMatchOptionsEvent(void *object, s32 event, s32 eventData, s32 eventValue, s32 eventContext) {
    MatchOptionsEventCallback *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuWidget *actor;

    if (g_matchOptionsEventCallbacks != 0) {
        wildcard = 30000;
        entry = &g_matchOptionsEventCallbacks;
        index = 0;
        do {
            if (g_matchOptionsEventCodes[index].value == event) {
                actor = object;
                actor_kind = actor->resource;
                table_kind = g_matchOptionsActorKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(object, event, eventData, eventValue, eventContext);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}

/* unit FRONTEND.CPP */
#if defined(VERSION_DE)
extern float k_frontendFragment[2];
#endif

#if defined(VERSION_EU_X)

int Frontend_ClearEuxLoadingHints(void) { SmpButton_WrapButtonWidget(477); SmpButton_WrapButtonWidget(478); return 0; }
#endif

#if defined(VERSION_EU)
/* Marks two loading-screen hint slots (0x1D9 and 0x1DA) blank. */
#include "types.h"
#include "Common/menu_overlay.h"
#include "Frontend/frontend.h"
#include "Smp/smp_button.h"

s32 Frontend_ClearEuLoadingHints(void) {
    SmpButton_WrapButtonWidget(473);
    SmpButton_WrapButtonWidget(474);
    return 0;
}
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* Marks two loading-screen hint slots (0x1D9 and 0x1DA) blank. */
s32 Frontend_ClearLoadingHints(void) {
    SmpButton_WrapButtonWidget(473);
    SmpButton_WrapButtonWidget(474);
    return 0;
}
#endif

#if defined(VERSION_US)
extern unsigned int k_frontendFragment[9];
#endif

#if defined(VERSION_EU_X)
extern unsigned int k_frontendFragment[2];
#endif

#if defined(VERSION_US_REV1)
extern unsigned int g_frontendSmallWordPair[2];
#endif

#if defined(VERSION_EU)
extern unsigned int k_frontendFragment[2];
#endif

/* unit FRONTEND_CREATEMATCHOPTIONS_DATA.CPP */
#if defined(VERSION_DE)
struct {
    void * g_matchOptionsScreen;
} g_FrontendCreatematchoptionsWords __attribute__((aligned(4))) = {
    0
};
typedef char g_FrontendCreatematchoptionsWordsSizeCheck[(sizeof(g_FrontendCreatematchoptionsWords) == 4) ? 1 : -1];
#endif
#if defined(VERSION_EU)
struct {
    void * g_matchOptionsScreen;
} g_FrontendCreatematchoptionsWords __attribute__((aligned(4))) = {
    0
};
typedef char g_FrontendCreatematchoptionsWordsSizeCheck[(sizeof(g_FrontendCreatematchoptionsWords) == 4) ? 1 : -1];
#endif
#if defined(VERSION_EU_X)
struct {
    void * g_matchOptionsScreen;
} g_FrontendCreatematchoptionsWords __attribute__((aligned(4))) = {
    0
};
typedef char g_FrontendCreatematchoptionsWordsSizeCheck[(sizeof(g_FrontendCreatematchoptionsWords) == 4) ? 1 : -1];
#endif
#if defined(VERSION_US)
struct {
    void * g_matchOptionsScreen;
} g_FrontendCreatematchoptionsWords __attribute__((aligned(4))) = {
    0
};
typedef char g_FrontendCreatematchoptionsWordsSizeCheck[(sizeof(g_FrontendCreatematchoptionsWords) == 4) ? 1 : -1];
#endif
#if defined(VERSION_US_REV1)
struct {
    void * g_matchOptionsScreen;
} g_FrontendCreatematchoptionsWords __attribute__((aligned(4))) = {
    0
};
typedef char g_FrontendCreatematchoptionsWordsSizeCheck[(sizeof(g_FrontendCreatematchoptionsWords) == 4) ? 1 : -1];
#endif
#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)
struct {
    ResidentEventHandlerEntry eventHandlers0[7];
    u8 retainedRecordWords[8];
} g_frontendCreateMatchOptionsRecord __attribute__((aligned(4))) = {
    { { 3590, 21, RESIDENT_HANDLER_ADDRESS(Frontend_CreateMatchOptions) }, { 3587, 21, RESIDENT_HANDLER_ADDRESS(Frontend_DestroyMatchOptions) }, { 3594, 21, RESIDENT_HANDLER_ADDRESS(Frontend_ReturnMatchOptionsEventZero) }, { 2, 21, RESIDENT_HANDLER_ADDRESS(Frontend_ExitMatchOptions) }, { 1, 21, RESIDENT_HANDLER_ADDRESS(Frontend_ActivateMatchOptionAction) }, { 10, 21, RESIDENT_HANDLER_ADDRESS(Frontend_ResetMatchOptionOnEvent) }, { 8, 874, RESIDENT_HANDLER_ADDRESS(Frontend_RefreshMatchSlotsOnZeroEventAlt) } },
    { 0x0, 0x0, 0x0, 0x7, 0x0, 0x0, 0x3, 0x6a }
};
typedef char g_frontendCreateMatchOptionsRecordSizeCheck[(sizeof(g_frontendCreateMatchOptionsRecord) == 92) ? 1 : -1];
#endif
#if defined(VERSION_EU)
ResidentEventHandlerEntry g_frontendCreateMatchOptionsRecord[9] = {
    { 3590, 21, (ResidentEventHandler)(void *)&addrLow_Frontend_CreateMatchOptions }, { 3587, 21, (ResidentEventHandler)(void *)&addrLow_Frontend_MatchOptionsEvent0E03ScenarioSetupEvent0E08Handler }, { 3594, 21, (ResidentEventHandler)(void *)&addrLow_Frontend_ReturnMatchOptionsEventZero }, { 2, 21, (ResidentEventHandler)(void *)&addrLow_Frontend_ExitMatchOptions }, { 1, 21, (ResidentEventHandler)(void *)&addrLow_Frontend_ActivateMatchOptionAction }, { 10, 21, (ResidentEventHandler)(void *)&addrLow_Frontend_ResetMatchOptionOnEvent }, { 8, 878, (ResidentEventHandler)(void *)&addrLow_Frontend_RefreshMatchSlotsOnZeroEventAlt }, { 7, 878, (ResidentEventHandler)(void *)&addrLow_Frontend_RefreshMatchSlotsOnZeroEvent },
    { 0, 0, (ResidentEventHandler)0 }
};
#endif
#if defined(VERSION_EU_X)
ResidentEventHandlerEntry g_frontendCreateMatchOptionsRecord[9] = {
    { 3590, 21, RESIDENT_HANDLER_ADDRESS(Frontend_CreateMatchOptions) }, { 3587, 21, RESIDENT_HANDLER_ADDRESS(Frontend_DestroyMatchOptions) }, { 3594, 21, RESIDENT_HANDLER_ADDRESS(Frontend_ReturnMatchOptionsEventZero) }, { 2, 21, RESIDENT_HANDLER_ADDRESS(Frontend_ExitMatchOptions) }, { 1, 21, RESIDENT_HANDLER_ADDRESS(Frontend_ActivateMatchOptionAction) }, { 10, 21, RESIDENT_HANDLER_ADDRESS(Frontend_ResetMatchOptionOnEvent) }, { 8, 882, RESIDENT_HANDLER_ADDRESS(Frontend_RefreshMatchSlotsOnZeroEventAlt) }, { 7, 882, RESIDENT_HANDLER_ADDRESS(Frontend_RefreshMatchSlotsOnZeroEvent) },
    { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif
#if defined(VERSION_US) || defined(VERSION_US_REV1)
#if defined(VERSION_US)
ResidentEventHandlerEntry g_FrontendCreatematchoptionsPointerWords[9] = {
    { 3590, 21, (ResidentEventHandler)(void *)&addrLow_Frontend_CreateMatchOptions2 }, { 3587, 21, (ResidentEventHandler)(void *)&addrLow_Frontend_DestroyMatchOptions }, { 3594, 21, (ResidentEventHandler)(void *)&addrLow_Frontend_ReturnMatchOptionsEventZero2 }, { 2, 21, (ResidentEventHandler)(void *)&addrLow_Frontend_ExitMatchOptions2 }, { 1, 21, (ResidentEventHandler)(void *)&addrLow_Frontend_ActivateMatchOptionAction2 }, { 10, 21, (ResidentEventHandler)(void *)&addrLow_Frontend_ResetMatchOptionOnEvent2 }, { 8, 878, (ResidentEventHandler)(void *)&addrLow_Frontend_RefreshMatchSlotsOnZeroEventAlt2 }, { 7, 878, (ResidentEventHandler)(void *)&addrLow_Frontend_RefreshMatchSlotsOnZeroEvent2 },
    { 0, 0, (ResidentEventHandler)0 }
};
#endif
#if defined(VERSION_US_REV1)
ResidentEventHandlerEntry g_FrontendCreatematchoptionsPointerWords[9] = {
    { 3590, 21, (ResidentEventHandler)(void *)&addrLow_Frontend_CreateMatchOptions2 }, { 3587, 21, (ResidentEventHandler)(void *)&addrLow_Frontend_DestroyMatchOptions }, { 3594, 21, (ResidentEventHandler)(void *)&addrLow_Frontend_ReturnMatchOptionsEventZero2 }, { 2, 21, (ResidentEventHandler)(void *)&addrLow_Frontend_ExitMatchOptions2 }, { 1, 21, (ResidentEventHandler)(void *)&addrLow_Frontend_ActivateMatchOptionAction2 }, { 10, 21, (ResidentEventHandler)(void *)&addrLow_Frontend_ResetMatchOptionOnEvent2 }, { 8, 878, (ResidentEventHandler)(void *)&addrLow_Frontend_RefreshMatchSlotsOnZeroEventAlt2 }, { 7, 878, (ResidentEventHandler)(void *)&addrLow_Frontend_RefreshMatchSlotsOnZeroEvent2 },
    { 0, 0, (ResidentEventHandler)0 }
};
#endif
#endif

/* unit FRONTEND_CREATEMATCHOPTIONS.CPP */
#if defined(VERSION_EU) || defined(VERSION_EU_X)
#define MO_TEXT(i) (g_matchOptionsListLabelsByLanguage[i][settings->language])
#else
#define MO_TEXT(i) (g_matchOptionsListLabels[i])
#endif

#if defined(VERSION_DE)
enum { OPTIONS_TEXT = 859 };
#else
#if defined(VERSION_EU_X)
enum { OPTIONS_TEXT = 867 };
#else
enum { OPTIONS_TEXT = 863 };
#endif
#endif

s32 Frontend_CreateMatchOptions(void *root) {
    struct MatchOptionsScreen *screen;
    Shared_Game *settings;
    void *selectList;
    void *cursorList;

    screen = Cache_AllocateMemory(64);
    g_matchOptionsScreen = screen;
    Frontend_InitMenuImage(screen->transition, 103, 0, 0, 0);
    g_matchOptionsScreen->countCap = Join_CountOpenPlayerSlots();
    switch (g_currentResultMode.kind) {
    case 1:
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(root, OPTIONS_TEXT + 0), 1);
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(root, OPTIONS_TEXT + 4), 1);
        break;
    case 0:
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(root, OPTIONS_TEXT + 6), 1);
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(root, OPTIONS_TEXT + 4), 1);
        break;
    case 2:
    case 3:
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(root, OPTIONS_TEXT + 0), 1);
        Widget_SetWidgetFlag100(Node_FindWidgetByResourceId(root, OPTIONS_TEXT + 6), 1);
        break;
    }
    g_matchOptionsScreen->widget24 = N64Eng_CreateNumericWidget(OPTIONS_TEXT + 4, OPTIONS_TEXT + 5, 0, 100, 1);
    g_matchOptionsScreen->widget28 = N64Eng_CreateNumericWidget(OPTIONS_TEXT + 2, OPTIONS_TEXT + 3, 0, 100, 1);
    g_matchOptionsScreen->widget2C = N64Eng_CreateNumericWidget(OPTIONS_TEXT + 0, OPTIONS_TEXT + 1, 0, 100, 1);
    g_matchOptionsScreen->widget30 = N64Eng_CreateNumericWidget(OPTIONS_TEXT + 6, OPTIONS_TEXT + 7, 0, 100, 1);
    g_matchOptionsScreen->countDefault = 0;
    if (g_matchOptionsScreen->countCap == 3) {
        g_matchOptionsScreen->countDefault = 1;
    }
    g_matchOptionsScreen->widget34 = N64Eng_CreateNumericWidget(OPTIONS_TEXT + 13, OPTIONS_TEXT + 14, g_matchOptionsScreen->countDefault,
                                            g_matchOptionsScreen->countCap, 1);
    selectList = SmpButton_CreateListWidget(OPTIONS_TEXT + 8, OPTIONS_TEXT + 9);
    {void **slot = &g_matchOptionsScreen->selectWidget; *slot = selectList;}
    settings = &g_gameSettings;
    SmpButton_AppendListText(selectList, MO_TEXT(0));
    SmpButton_AppendListText(g_matchOptionsScreen->selectWidget, MO_TEXT(1));
    cursorList = SmpButton_CreateListWidget(OPTIONS_TEXT + 15, OPTIONS_TEXT + 16);
    {void **slot = &g_matchOptionsScreen->cursorWidget; *slot = cursorList;}
    SmpButton_AppendListText(cursorList, MO_TEXT(2));
    SmpButton_AppendListText(g_matchOptionsScreen->cursorWidget, MO_TEXT(3));
    SmpButton_AppendListText(g_matchOptionsScreen->cursorWidget, MO_TEXT(4));
    SmpButton_AppendListText(g_matchOptionsScreen->cursorWidget, MO_TEXT(5));
    SmpButton_AppendListText(g_matchOptionsScreen->cursorWidget, MO_TEXT(6));
    SmpButton_WrapButtonWidget(OPTIONS_TEXT + 10);
    SmpButton_WrapButtonWidget(OPTIONS_TEXT + 11);
    SmpButton_WrapButtonWidget(OPTIONS_TEXT + 12);
    Frontend_LoadMatchOptionWidgets();
    Frontend_SyncMatchJoinSlots(0);
    Frontend_LoadMatchOptionWidgets();
    return 0;
}
