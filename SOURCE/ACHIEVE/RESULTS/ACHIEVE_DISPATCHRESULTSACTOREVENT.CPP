#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "COMMON/MENULISTSCREEN.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "COMMON/MENUSELECTIONMESSAGE.H"
#include "TYPES.H"
#include "ACHIEVE/ACHIEVE_DISPATCHRESULTSACTOREVENT.H"

/* Calls MarkMenuEventHandled with the arguments it was given and returns zero. */
extern void MarkMenuEventHandled();

s32 Achieve_AcknowledgeResultsEvent(void) {
    MarkMenuEventHandled();
    return 0;
}

/* Dispatches event event through this file's 12-byte handler table, whose rows hold an event at g_resultsActorEventIds, an actor kind at g_resultsActorEventKinds and a handler at g_resultsActorEventHandlers: the first row whose event equals event and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

typedef s32 (*ResultsActorEventHandler)(void *, s32, s32, s32, s32);


extern ResultsActorEventHandler g_resultsActorEventHandlers;




s32 Achieve_DispatchResultsActorEvent(ActorDefinitionHeader *actor, s32 event, s32 itemId, s32 value, s32 context) {
    ResultsActorEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_resultsActorEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_resultsActorEventHandlers;
        index = 0;
        do {
            if (g_resultsActorEventIds[index].value == event) {
                actor_kind = actor->character;
                table_kind = g_resultsActorEventKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(actor, event, itemId, value, context);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}


