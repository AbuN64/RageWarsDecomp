#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/REQUESTRECAT10.H"
#include "OPTIONS.H"
#include "TYPES.H"
#include "COMMON/SELECTIONSCREENSTATE.H"
#include "COMMON/SCREEN.H"
#include "COMMON/MENULISTSCREEN.H"
#include "FRONTEND/JOIN_GETJOINREQUESTRANK.H"
#include "FRONTEND/JOIN_RANDOMIZEJOINREQUESTENTRIES.H"
#include "FRONTEND/FRONTEND_ACTIVATEMATCHOPTIONACTION.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "COMMON/SHARED_GAMESLOT.H"
extern struct MatchOptionsScreen *g_matchOptionsScreen;
extern s32 SmpButton_GetListSelection(s32 *record);
extern s32 N64Eng_GetNumericWidgetValue(void *);
extern s32 Frontend_GetMenuImageState(s32 *record);

/* Refreshes the option block g_gameSettings from the menu g_matchOptionsScreen points to: the bytes at 0x24 to
   0x27 from the values N64Eng_GetNumericWidgetValue reports for its items at 0x28, 0x24, 0x2C and 0x30, and the
   byte at 0x28 from the selection SmpButton_GetListSelection reports for its item at 0x1C. */







/* Synchronizes screen g_matchOptionsScreen's option widgets and player-count widget with the stored option
 * block g_gameSettings and the live player count: pushes the four stored option bytes back into their
 * checkbox widgets, sets the player-count widget to the lesser of the screen's cap and the live
 * player count (or the screen's default when that count is zero), and sets the selection and
 * cursor widgets from the stored selection byte and the current cursor value. */







extern void N64Eng_SetNumericWidgetValue(struct RecordN64EngCreateNumericWidget *widget, s32 value);

extern void SmpButton_SelectListEntry(void *menu, s32 index);


/* Refreshes the entry list of screen g_matchOptionsScreen: reads the selection of its cursor at 0x20 through
   SmpButton_GetListSelection and the entry count of its list at 0x34 through N64Eng_GetNumericWidgetValue. With no entries it
   clears the list through Join_ResetJoinRequestEntries; otherwise, when the count differs from what
   Join_CountUsedSlots_FrontendActivatematchoptionaction shows or force is 1, it clears the list and rebuilds it for the count and
   selection through Join_RandomizeJoinRequestEntries. */




extern void Join_ResetJoinRequestEntries(void);


/* Releases the object g_matchOptionsScreen holds through Cache_FreeMemory, clears g_matchOptionsScreen and returns zero. */





/* Handles the menu message Menu_GetFocusedElementId reports after MarkMenuEventHandled unless Frontend_GetMenuImageState reports
   screen g_matchOptionsScreen busy: 0x36B closes the menu through Frontend_StoreMatchOptionWidgets, sends code -1 to
   Random_SetMenuChoiceResult and calls Menu_ReturnToPreviousScreen; 0x369 does the same with page reset Frontend_SyncMatchJoinSlots(0)
   and code 0x17 when N64Eng_GetNumericWidgetValue reports the screen's list at 0x34 non-empty; 0x36A always does
   it with Join_SeatJoinRequests and code 0x19, then calls Tsmos_DeactivateControllerState. Returns zero. */







/* Calls MarkMenuEventHandled and, unless Frontend_GetMenuImageState reports one for the object g_matchOptionsScreen holds, calls
   Frontend_StoreMatchOptionWidgets, Random_SetMenuChoiceResult with -1 and Menu_ReturnToPreviousScreen. Returns zero. */




/* Dispatches event event through this file's 12-byte handler table, whose rows hold an event at g_matchOptionsEventCodes, an actor kind at g_matchOptionsActorKinds and a handler at g_matchOptionsEventCallbacks: the first row whose event equals event and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

typedef s32 (*MatchOptionsEventCallback)(void *, s32, s32, s32, s32);



extern MatchOptionsEventCallback g_matchOptionsEventCallbacks;

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

s32 Frontend_DestroyMatchOptions(void) {
    Cache_FreeMemory(g_matchOptionsScreen);
    g_matchOptionsScreen = 0;
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Frontend_ReturnMatchOptionsEventZero(void) {
    return 0;
}

s32 Frontend_ResetMatchOptionOnEvent(s32 unused0, s32 unused1, u32 eventData, s32 eventValue) {
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

s32 Frontend_DispatchMatchOptionsEvent(void *object, s32 event, s32 eventData, s32 eventValue, s32 eventContext) {
    MatchOptionsEventCallback *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuActorInputView *actor;

    if (g_matchOptionsEventCallbacks != 0) {
        wildcard = 30000;
        entry = &g_matchOptionsEventCallbacks;
        index = 0;
        do {
            if (g_matchOptionsEventCodes[index].value == event) {
                actor = object;
                actor_kind = actor->input;
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
