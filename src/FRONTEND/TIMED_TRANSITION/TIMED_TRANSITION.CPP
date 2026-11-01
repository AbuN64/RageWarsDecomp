#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/SCREEN.H"
#include "include_asm.h"
#include "COMMON/WIDGETRECAT1A.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/OBJECTRECAT28.H"
#include "TYPES.H"
#include "COMMON/MENULISTSCREEN.H"
#include "FRONTEND/FRONTEND_DISPATCHNODEPAIRMENUEVENT.H"

#if defined(VERSION_EU_X)
extern void SmpButton_WrapButtonWidget(int id);

int Frontend_WrapNodePairExtended(void) { SmpButton_WrapButtonWidget(990); SmpButton_WrapButtonWidget(991); return 0; }
#endif

/* Handles the menu message Menu_GetFocusedElementId reports after MarkMenuEventHandled: 0x3DA waits through
   SmXlate_SwitchScreen for a time chosen by setting g_gameControllerMode through k_timedTransitionControllerModeJumpTable (20, 15 or 10, and
   3 for any other setting); 0x3DB sends code -1 to Random_SetMenuChoiceResult and calls Menu_ReturnToPreviousScreen.
   Returns zero. */
extern void SmXlate_SwitchScreen(s32);

#if defined(VERSION_DE)
enum { MENU_TIMED_TRANSITION_SWITCH_SCREEN = 980, MENU_TIMED_TRANSITION_RETURN = 981 };
#elif defined(VERSION_EU_X)
enum { MENU_TIMED_TRANSITION_SWITCH_SCREEN = 990, MENU_TIMED_TRANSITION_RETURN = 991 };
#else
enum { MENU_TIMED_TRANSITION_SWITCH_SCREEN = 986, MENU_TIMED_TRANSITION_RETURN = 987 };
#endif

s32 Frontend_UpdateTimedTransition(void) {
    s32 time;

    MarkMenuEventHandled();
    switch (Menu_GetFocusedElementId()) {
    case MENU_TIMED_TRANSITION_SWITCH_SCREEN:
        switch (g_gameSettings.controllerMode) {
        case 0:
            time = 20;
            break;
        case 2:
            time = 15;
            break;
        case 3:
        case 4:
            time = 10;
            break;
        case 1:
        default:
            time = 3;
            break;
        }
        SmXlate_SwitchScreen(time);
        return 0;
    case MENU_TIMED_TRANSITION_RETURN:
        Random_SetMenuChoiceResult(-1);
        Menu_ReturnToPreviousScreen();
        return 0;
    }
    return 0;
}

/* Calls MarkMenuEventHandled, then Random_SetMenuChoiceResult with -1, then Menu_ReturnToPreviousScreen, and returns zero. */

s32 Frontend_CancelNodePairMenu(void) {
    MarkMenuEventHandled();
    Random_SetMenuChoiceResult(-1);
    Menu_ReturnToPreviousScreen();
    return 0;
}

/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_nodePairMenuEventIds, an actor kind at g_nodePairMenuEventActorKinds and a handler at g_nodePairMenuEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

typedef s32 (*NodePairMenuEventHandler)(void *, s32, s32, s32, s32);


extern FieldRow g_nodePairMenuEventIds[];
extern FieldRow g_nodePairMenuEventActorKinds[];
extern NodePairMenuEventHandler g_nodePairMenuEventHandlers;




s32 Frontend_DispatchNodePairMenuEvent(struct Tree *eventTarget, s32 eventId, s32 eventCode, s32 eventValue, s32 repeatCount) {
    char *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_nodePairMenuEventHandlers != 0) {
        wildcard = 30000;
        entry = (char *)&g_nodePairMenuEventHandlers;
        index = 0;
        do {
            if (g_nodePairMenuEventIds[index].value == eventId) {
                actor_kind = eventTarget->id;
                table_kind = g_nodePairMenuEventActorKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*(NodePairMenuEventHandler *)entry)(eventTarget, eventId, eventCode, eventValue, repeatCount);
                }
            }
            entry += sizeof(ResidentEventHandlerEntry);
            index++;
        } while (*(NodePairMenuEventHandler *)entry != 0);
    }
    return 0;
}
