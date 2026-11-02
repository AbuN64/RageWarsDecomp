#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/SETTINGSRECAT24.H"
#include "COMMON/ENTRYRECAT6C.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/MENULISTSCREEN.H"
#include "FRONTEND/SCENARIO_RESULT_ROWS.H"
#include "FRONTEND/FRONTEND_DISPATCHRESULTSEVENT.H"
#include "FRONTEND/PAKINTERFACE_SETSCREENPHASE.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
extern MatchScoreScreen *g_matchResultBadgeScreen;

/* Handles the answer on the screen g_matchResultBadgeScreen. */





extern void MarkMenuEventHandled();

extern s32 Frontend_GetMenuImageState(s32 *record);

extern s32 Menu_GetFocusedElementId();

extern void Frontend_StartMenuImageTransition(s32 *record);



extern void SmXlate_SwitchScreen(s32);

/* When the fourth argument is one, calls MarkMenuEventHandled and, while the counter at offset 0xE8 of
   the object g_matchResultBadgeScreen points to is positive, decrements it and calls ScenarioSetup_FillResultRows. Returns zero. */





/* When the fourth argument is one, calls MarkMenuEventHandled and, while the position at offset 0xE8 of
   the object g_matchResultBadgeScreen points to is more than four below the limit at 0xEC, advances it and calls
   ScenarioSetup_FillResultRows. Returns zero. */




/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_resultsEventIds, an actor kind at g_resultsEventKinds and a handler at g_resultsEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

typedef s32 (*ResultsEventHandler)(void *, s32, s32, s32, s32);



extern ResultsEventHandler g_resultsEventHandlers;

extern s32 g_simpleObjectPauseState; /* MIXED Frontend_ActivateResultsAction */
s32 Frontend_ActivateResultsAction(void) {
    s32 *paused;
    MarkMenuEventHandled();
    if (Frontend_GetMenuImageState(g_matchResultBadgeScreen) == 1) {
        return 0;
    }
    paused = &g_simpleObjectPauseState;
    *paused = 0;
    switch (Menu_GetFocusedElementId()) {
#if defined(VERSION_DE)
    case 565 - 2:
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    case 569 - 2:
#elif defined(VERSION_EU_X)
    case 574 - 2:
#endif
        if (((u8 *)paused)[-(((char *)&((Shared_MenuData *)0)->pause - (char *)0) - ((char *)&((Shared_MenuData *)0)->game.controllerMode - (char *)0))] == 0) {
            Frontend_StartMenuImageTransition(g_matchResultBadgeScreen);
            g_matchResultBadgeScreen->active = 0;
        } else {
            g_resultReplayPending = 0;
            g_resultExitPending = 0;
            SmXlate_SwitchScreen(15);
        }
        break;
#if defined(VERSION_DE)
    case 565 - 1:
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    case 569 - 1:
#elif defined(VERSION_EU_X)
    case 574 - 1:
#endif
        PAKInterface_SetScreenPhase(5);
        SmXlate_SwitchScreen(19);
        break;
#if defined(VERSION_DE)
    case 565 + 3:
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    case 569 + 3:
#elif defined(VERSION_EU_X)
    case 574 + 3:
#endif
        if (ScenarioSetup_IsCupSelected() == 1) {
            Random_SetMenuChoiceResult(33);
            return 0;
        }
        if (((u8 *)paused)[-(((char *)&((Shared_MenuData *)0)->pause - (char *)0) - ((char *)&((Shared_MenuData *)0)->game.controllerMode - (char *)0))] == 0) {
            SmXlate_SwitchScreen(20);
        } else {
            SmXlate_SwitchScreen(15);
        }
        break;
    default:
        return 0;
    }
    return 0;
}

s32 Frontend_ConsumeResultsEvent(void) {
    MarkMenuEventHandled();
    return 0;
}

s32 Frontend_ScrollResultsBackward(void *first, void *second, void *third, s32 fourth) {
    MatchScoreScreen *state;

    if (fourth == 1) {
        MarkMenuEventHandled();
        state = g_matchResultBadgeScreen;
        if (state->first > 0) {
            state->first--;
            ScenarioSetup_FillResultRows();
            return 0;
        }
    }
    return 0;
}

s32 Frontend_ScrollResultsForward(void *first, void *second, void *third, s32 fourth) {
    MatchScoreScreen *state;
    s32 position;

    if (fourth == 1) {
        MarkMenuEventHandled();
        state = g_matchResultBadgeScreen;
        position = state->first;
        if (position + 4 < state->count) {
            state->first = position + 1;
            ScenarioSetup_FillResultRows();
            return 0;
        }
    }
    return 0;
}

s32 Frontend_DispatchResultsEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra) {
    ResultsEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuActorInputView *actor;

    if (g_resultsEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_resultsEventHandlers;
        index = 0;
        do {
            if (g_resultsEventIds[index].value == eventId) {
                actor = eventObject;
                actor_kind = actor->input;
                table_kind = g_resultsEventKinds[index].value;
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

