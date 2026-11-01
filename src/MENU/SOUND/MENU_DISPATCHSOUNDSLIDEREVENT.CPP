#include "include_asm.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/OBJECTRECAT28.H"
#include "TYPES.H"
#include "FRONTEND/MENU_DISPATCHSOUNDSLIDEREVENT.H"

/* Dispatches event event through this file's 12-byte handler table, whose rows hold an event at g_soundSliderEventIds, an actor kind at g_soundSliderEventKinds and a handler at g_soundSliderEventHandlers: the first row whose event equals event and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

typedef s32 (*SoundSliderEventHandler)(void *, s32, s32, s32, s32);


extern FieldRow g_soundSliderEventIds[];
extern FieldRow g_soundSliderEventKinds[];
extern SoundSliderEventHandler g_soundSliderEventHandlers;




s32 Menu_DispatchSoundSliderEvent(void *eventTarget, s32 event, s32 itemId, s32 value, s32 context) {
    SoundSliderEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuActorInputView *actor;

    if (g_soundSliderEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_soundSliderEventHandlers;
        index = 0;
        do {
            if (g_soundSliderEventIds[index].value == event) {
                actor = eventTarget;
                actor_kind = actor->input;
                table_kind = g_soundSliderEventKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(eventTarget, event, itemId, value, context);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}


