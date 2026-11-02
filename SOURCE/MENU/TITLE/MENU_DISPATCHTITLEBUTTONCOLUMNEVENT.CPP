#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/MENU_INITIALIZEOPTIONSSCENE.H"
#include "TYPES.H"
#include "MENU/EXTERNS.H"
#include "COMMON/CHEATCODE.H"
#include "MENU/MENU_DISPATCHTITLEBUTTONCOLUMNEVENT.H"

/* 80406A88_17.CPP */
#if defined(VERSION_EU_X)
/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_titleButtonEventTable, an actor kind at g_titleButtonEventActorKinds and a handler at g_titleButtonEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from Menu_DispatchOptionsTransitionEvent. */

s32 Menu_DispatchTitleButtonOffsetEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    char *entry;
    s32 offset;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_titleButtonEventHandlers != 0) {
        wildcard = 30000;
        entry = (char *)&g_titleButtonEventHandlers;
        offset = 0;
        do {
            if (((struct AnimationEventMaskView *) (((char *) (&g_titleButtonEventTable)) + offset))->value == eventId) {
                actor_kind = ((struct MenuActorInputView *) ((char *) widget))->input;
                table_kind = ((struct AnimationEventMaskView *) (((char *) (&g_titleButtonEventActorKinds)) + offset))->value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*(WidgetEventHandler *)entry)(widget, eventId, eventData0, eventData1, eventData2);
                }
            }
            entry += sizeof(ResidentEventHandlerEntry);
            offset += 12;
        } while (*(WidgetEventHandler *)entry != 0);
    }
    return 0;
}
#endif


/* 80408AC4_36.CPP */
#if defined(VERSION_DE)
/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_titleButtonEventTable, an actor kind at g_titleButtonEventActorKinds and a handler at g_titleButtonEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

typedef s32 (*TitleButtonColumnEventHandler)(void *, s32, s32, s32, s32);

extern FieldRow g_titleButtonColumnEventIds[];

extern FieldRow g_titleButtonColumnEventActorKinds[];

extern TitleButtonColumnEventHandler g_titleButtonColumnEventHandlers;

s32 Menu_DispatchTitleButtonColumnEvent(void *widget, s32 eventId, s32 eventData0, s32 eventData1, s32 eventData2) {
    TitleButtonColumnEventHandler *entry;
    MenuActorInputView *actor;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_titleButtonColumnEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_titleButtonColumnEventHandlers;
        index = 0;
        do {
            if (g_titleButtonColumnEventIds[index].value == eventId) {
                actor = widget;
                actor_kind = actor->input;
                table_kind = g_titleButtonColumnEventActorKinds[index].value;
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
