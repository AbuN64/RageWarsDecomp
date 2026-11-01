#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "FRONTEND/FRONTEND_DISPATCHPLAYMODEEVENT.H"

/* On event 3 with value 0xA, calls MarkMenuEventHandled, sets the word at offset 0x18 of the object
   g_playModeMenuState points to to 0x1C and calls SmpSlider_SetTransitionMode on its first word with 2. Returns zero. */


extern struct StateFrontendHandlePlayModeShortcut *g_playModeMenuState;

extern void MarkMenuEventHandled();

extern void SmpSlider_SetTransitionMode(struct SliderTransitionView *object, s32 mode);

/* Dispatches event event through this file's 12-byte handler table, whose rows hold an event at g_playModeEventIds, an actor kind at g_playModeEventKinds and a handler at g_playModeEventHandlers: the first row whose event equals event and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

typedef s32 (*PlayModeEventHandler)(void *, s32, s32, s32, s32);

extern PlayModeEventHandler g_playModeEventHandlers;

s32 Frontend_HandlePlayModeShortcut(void *first, void *second, u32 event, s32 value) {
    struct StateFrontendHandlePlayModeShortcut *state;

    if ((event >> 16) == 3 && value == 10) {
        MarkMenuEventHandled();
        state = g_playModeMenuState;
        state->value = 28;
        SmpSlider_SetTransitionMode(state->first, 2);
    }
    return 0;
}

s32 Frontend_ConsumePlayModeEvent(void) {
    MarkMenuEventHandled();
    return 0;
}

s32 Frontend_DispatchPlayModeEvent(void *eventTarget, s32 event, s32 itemId, s32 value, s32 context) {
    PlayModeEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuActorInputView *actor;

    if (g_playModeEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_playModeEventHandlers;
        index = 0;
        do {
            if (g_playModeEventIds[index].value == event) {
                actor = eventTarget;
                actor_kind = actor->input;
                table_kind = g_playModeEventKinds[index].value;
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
