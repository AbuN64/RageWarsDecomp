#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "COMMON/MENULISTSCREEN.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/MENUSELECTIONMESSAGE.H"
#include "TYPES.H"

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_titleButtonEventTable, an actor kind at g_titleButtonEventActorKinds and a handler at g_titleButtonEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

typedef s32 (*TitleButtonColumnEventHandler)(void *, s32, s32, s32, s32);

extern FieldRow g_titleButtonEventTable[];

extern FieldRow g_titleButtonEventActorKinds[];

extern TitleButtonColumnEventHandler g_titleButtonEventHandlers;

struct MenuActorInputView;

s32 Menu_DispatchTitleButtonEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    TitleButtonColumnEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuActorInputView *actor;

    if (g_titleButtonEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_titleButtonEventHandlers;
        index = 0;
        do {
            if (g_titleButtonEventTable[index].value == eventId) {
                actor = widget;
                actor_kind = actor->input;
                table_kind = g_titleButtonEventActorKinds[index].value;
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
#endif
