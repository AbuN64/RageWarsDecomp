#include "COMMON/CHEATCODE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "TYPES.H"
#include "MENU/MENU_DISPATCHGERMANMATCHMENUEVENT.H"
#if defined(VERSION_DE)
/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_matchMenuEventIds, an actor kind at g_matchMenuEventKinds and a handler at g_matchMenuEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */
typedef s32 (*MatchMenuEventHandler)(void *, s32, s32, s32, s32);
extern FieldRow g_germanMatchMenuEventIds[];
extern FieldRow g_germanMatchMenuEventKinds[];
extern MatchMenuEventHandler g_germanMatchMenuEventHandlers;
s32 Menu_DispatchGermanMatchMenuEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra) {
    MatchMenuEventHandler *entry;
    MenuActorInputView *actor;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_germanMatchMenuEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_germanMatchMenuEventHandlers;
        index = 0;
        do {
            if (g_germanMatchMenuEventIds[index].value == eventId) {
                actor = eventObject;
                actor_kind = actor->input;
                table_kind = g_germanMatchMenuEventKinds[index].value;
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
