#include "COMMON/ENTRYRECAT6C.H"
#include "FRONTEND/PAKMENU.H"
#include "TYPES.H"
#include "FRONTEND/FRONTEND_SETPLAYERPROFILELINK.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "FRONTEND/FRONTEND_DISPATCHPAKPROFILEEVENT.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"

/* 8042E080_64.CPP */
/* Fills entry i of the 12-byte records at offset 0x2DF8 of the object g_pakProfileScreenState points to with
   two values and marks it set. */

void Frontend_SetPlayerProfileLink(s32 first, s32 second, s32 index) {
    g_pakProfileScreenState->links[index].player = first;
    g_pakProfileScreenState->links[index].entry = second;
    g_pakProfileScreenState->links[index].state = 1;
}

/* 8042E080_65.CPP */
/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Frontend_ReturnProfileEventZero(void) {
    return 0;
}

/* 8042E080_66.CPP */
/* Releases the object g_pakProfileScreenState holds through Cache_FreeMemory, clears g_pakProfileScreenState, calls
   Tsmos_ActivateControllerState and Tsmos_SetTimerState with 1, and returns zero. */
extern void Tsmos_ActivateControllerState(void);
extern void Tsmos_SetTimerState(s32);

s32 Frontend_DestroyPakProfileScreen(void) {
    Cache_FreeMemory(g_pakProfileScreenState);
    g_pakProfileScreenState = 0;
    Tsmos_ActivateControllerState();
    Tsmos_SetTimerState(1);
    return 0;
}

/* 8042E080_67.CPP */
/* Handles a packed message for a player in g_pakProfileScreenState: when the player (low half) is in state 12, the
   message type (high half) is 3 and the argument is 4 or 5, moves the player to phase 2 with a zero
   timer; always returns 0. */

int Frontend_ResetNameRepeatOnEvent(int unused0, int unused1, unsigned int message, int arg) {
    PakNameRepeatView *p = (PakNameRepeatView *)((char *)g_pakProfileScreenState + (message & 0xFFFF) * sizeof(PakProfilePanelState));

    if (p->state == 12 && (message >> 16) == 3 && arg < 6 && arg >= 4) {
        p->timer = 0;
        p->phase = 2;
    }
    return 0;
}

/* 8042E080_68.CPP */
#if !(defined(VERSION_US))
/* Dispatches event event through this file's 12-byte handler table, whose rows hold an event at g_pakProfileHandlerEvents, an actor kind at g_pakProfileHandlerKinds and a handler at g_pakProfileHandlers: the first row whose event equals event and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */

typedef s32 (*PakProfileEventHandler)(void *, s32, s32, s32, s32);

extern FieldRow g_pakProfileHandlerEvents[];
extern PakProfileEventHandler g_pakProfileHandlers;

s32 Frontend_DispatchPakProfileEvent(void *eventTarget, s32 event, s32 eventValue, s32 eventData, s32 eventContext) {
    PakProfileEventHandler *entry;
    s32 index;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;
    MenuActorInputView *actor;

    if (g_pakProfileHandlers != 0) {
        wildcard = 30000;
        entry = &g_pakProfileHandlers;
        index = 0;
        do {
            if (g_pakProfileHandlerEvents[index].value == event) {
                actor = eventTarget;
                actor_kind = actor->input;
                table_kind = g_pakProfileHandlerKinds[index].value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*entry)(eventTarget, event, eventValue, eventData, eventContext);
                }
            }
            entry += 3;
            index++;
        } while (*entry != 0);
    }
    return 0;
}
#endif
