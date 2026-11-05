#include "Common/resident_event_handler.h"
#include "Common/screen.h"
#include "include_asm.h"
#include "Common/widget_tree.h"
#include "Common/shared_gameslot.h"
#include "Common/aiprofile.h"
#include "Common/menu_model_preview.h"
#include "types.h"
#include "Common/menulistscreen.h"
#include "Frontend/frontend_dispatchnodepairmenuevent.h"
#include "Common/shared_menureply.h"
#include "Common/runtime_declarations.h"
#include "Smp/smp_button.h"
#include "Frontend/frontend_address_symbols.h"

/* unit TIMED_TRANSITION.CPP */
#if defined(VERSION_EU_X)

int Frontend_WrapNodePairExtended(void) { SmpButton_WrapButtonWidget(990); SmpButton_WrapButtonWidget(991); return 0; }
#endif

/* Handles the menu message Menu_GetFocusedElementId reports after MarkMenuEventHandled: 0x3DA waits through
   SmXlate_SwitchScreen for a time chosen by setting g_gameControllerMode through k_timedTransitionControllerModeJumpTable (20, 15 or 10, and
   3 for any other setting); 0x3DB sends code -1 to Random_SetMenuChoiceResult and calls Menu_ReturnToPreviousScreen.
   Returns zero. */

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

/* Calls the handler registered for eventId (tables g_nodePairMenuEventIds, g_nodePairMenuEventActorKinds, g_nodePairMenuEventHandlers). A row matches when its event equals eventId and its kind equals the actor's kind or is the any-kind wildcard 0x7530. Returns the handler's result, or zero when no row matches. */


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

/* unit G_FRONTENDENCODEDWORDS.CPP */
#if defined(VERSION_US_REV1)
unsigned int g_FrontendEncodedWords[3] = {
    0x0000003E, 0x00000000, 0x00000008,
};
#endif
