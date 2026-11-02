#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RESERVED_SHARED_DECLARATIONS.H"
#include "TYPES.H"
#include "FRONTEND/FRONTEND_DISPATCHCONFIRMATIONEVENT.H"
#include "COMMON/LONE/RESIDENT_CHOICE_SCREEN.H"

/* 8042E080_86.CPP */
/* Dispatches event eventId through this file's 12-byte handler table, whose rows hold an event at g_confirmationMenuEventIds, an actor kind at g_confirmationMenuEventActorKinds and a handler at g_confirmationMenuEventHandlers: the first row whose event equals eventId and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

typedef s32 (*ConfirmationMenuEventHandler)(void *, s32, s32, s32, s32);

extern FieldRow g_confirmationMenuEventIds[];
extern FieldRow g_confirmationMenuEventActorKinds[];
extern ConfirmationMenuEventHandler g_confirmationMenuEventHandlers;

s32 Frontend_DispatchConfirmationEvent(void *eventTarget, s32 eventId, s32 eventCode, s32 eventValue, s32 repeatCount) {
    ConfirmationMenuEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuActorInputView *actor;

    if (g_confirmationMenuEventHandlers != 0) {
        wildcard = 30000;
        entry = &g_confirmationMenuEventHandlers;
        index = 0;
        do {
            if (g_confirmationMenuEventIds[index].value == eventId) {
                actor = eventTarget;
                actor_kind = actor->input;
                table_kind = g_confirmationMenuEventActorKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(eventTarget, eventId, eventCode, eventValue, repeatCount);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}

/* 8042E080_87.CPP */
/* Builds screen state g_residentChoiceScreen: allocates its 0x1C bytes, resets through Tsmos_ActivateControllerState and opens
   it as page 0x67 through Frontend_InitMenuImage; then places the given window at 0x62, 0x45 in mode 1 of
   Frontend_GetCurrentVideoModeIndex_de, or at x 0x69 in mode 2. Returns zero. */

extern struct Record *Cache_AllocateMemory(s32 size);
extern void Tsmos_ActivateControllerState(void);
extern void Frontend_InitMenuImage(s32 *record, s32 first, s32 second, s32 third, s32 fourth);
extern s32 Frontend_GetScreenMode(void);

s32 Frontend_CreateTimedMenu(struct Pair14 *window) {
    g_residentChoiceScreen = Cache_AllocateMemory(28);
    Tsmos_ActivateControllerState();
    Frontend_InitMenuImage(g_residentChoiceScreen, 103, 0, 0, 0);
    if (Frontend_GetScreenMode() == 1) {
        window->first = 98;
        window->second = 69;
    } else if (Frontend_GetScreenMode() == 2) {
        window->first = 105;
    }
    return 0;
}
