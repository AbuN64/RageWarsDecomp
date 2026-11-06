#include "menu2_symbols.h"
#include "include_asm.h"
#include "Common/numberpadscreen.h"
#include "Common/cheatcode.h"
#include "Menu/state.h"
#include "types.h"
#include "Common/resident_event_handler.h"
#include "Common/runtime_declarations.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Menu/menu_dispatchextraoptionsevent.h"
#include "Data/Ovltbl/menu_openoptionskeypad_data.h"

#if defined(VERSION_EU_X)
#include "Common/screen.h"
#include "Menu/menu_advancefademeter.h"
#include "menu2_symbols.h"
#include "Frontend/frontend.h"
#endif
#if defined(VERSION_DE)
enum { menuId3ac = 934, menuId3b6 = 944 };
/* Calls MarkMenuEventHandled, then Menu_ShowExtraOptionsPanel when a field of the object g_extraOptionsScreen
   points to is clear, or SmpSlider_SetTransitionMode on its first word with 2 and Menu_ApplyExtraOptionFlags otherwise.
   Returns zero. */
s32 Menu_ConfirmGermanExtraOptions(void) {
    struct StateMenuConfirmGermanExtraOptions *state;

    MarkMenuEventHandled();
    if (SmpSlider_GetTransitionMode(((struct StateMenuConfirmGermanExtraOptions *)g_extraOptionsScreen)->first) != 3) {
        return 0;
    }
    state = g_extraOptionsScreen;
    if (state->ready == 0) {
        Menu_ShowExtraOptionsPanel();
    } else {
        SmpSlider_SetTransitionMode(state->first, 2);
        Menu_ApplyExtraOptionFlags();
    }
    return 0;
}
#endif

#if defined(VERSION_DE)
/* Dispatches event event through this file's 12-byte handler table, whose rows hold an event at g_extraOptionsEventCodes, an actor kind at g_extraOptionsActorKinds and a handler at g_extraOptionsEventCallbacks: the first row whose event equals event and whose kind equals the actor's input kind, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. */
s32 Menu_DispatchExtraOptionsEvent(void *object, s32 event, s32 eventData, s32 eventValue, s32 eventContext) {
    /* The ROM walks the handler column by pointer and reads the event and kind columns by byte offset from their own symbols. */
    WidgetEventHandler *handler;
    s32 wildcardKind;
    s32 offset;

    if (g_extraOptionsEventCallbacks != 0) {
        wildcardKind = ANY_ACTOR_KIND;
        handler = &g_extraOptionsEventCallbacks;
        offset = 0;
        do {
            if (*(s32 *)((u8 *)g_extraOptionsEventCodes + offset) == event) {
                s32 actorKind = ((struct MenuWidget *)object)->resource;
                s32 tableKind = *(s32 *)((u8 *)g_extraOptionsActorKinds + offset);

                if (tableKind == actorKind || tableKind == wildcardKind) {
                    return (*handler)(object, event, eventData, eventValue, eventContext);
                }
            }
            handler = (WidgetEventHandler *)((u8 *)handler + sizeof(ResidentEventHandlerEntry));
            offset += sizeof(ResidentEventHandlerEntry);
        } while (*handler != 0);
    }
    return 0;
}
#endif

#if defined(VERSION_DE)
struct {
    void * g_extraOptionsScreen;
} k_MenuOpenoptionskeypadZeroWords __attribute__((aligned(4))) = {
    0
};
typedef char k_MenuOpenoptionskeypadZeroWordsSizeCheck[(sizeof(k_MenuOpenoptionskeypadZeroWords) == 4) ? 1 : -1];
#endif
#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)
struct {
    ResidentEventHandlerEntry handlers[6];
    u32 retainedRecordWords[1];
} g_menuOpenOptionsKeypadRecord __attribute__((aligned(4))) = {
    { { 3592, 28, (ResidentEventHandler)(void *)&Menu_UpdateExtraOptionsMenu_Address }, { 3590, 28, (ResidentEventHandler)(void *)&Menu_OpenRuleToggleScreen_Address }, { 3587, 28, (ResidentEventHandler)(void *)&Menu_DestroyExtraOptionsMenu_Address }, { 2, 28, (ResidentEventHandler)(void *)(Menu_UpdateExtraOptionsMenu_Address + 348) }, { 1, 28, (ResidentEventHandler)(void *)(Menu_UpdateExtraOptionsMenu_Address + 164) }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x00421BAC }
};
#endif
#endif
