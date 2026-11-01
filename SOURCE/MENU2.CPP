#include "include_asm.h"
#include "COMMON/NUMBERPADSCREEN.H"
#include "COMMON/CHEATCODE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "MENU/STATE.H"
#include "TYPES.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "MENU/MENU_DISPATCHEXTRAOPTIONSEVENT.H"
#include "DATA/OVLTBL/MENU_OPENOPTIONSKEYPAD_DATA.H"

/* MENU.CPP */
#if defined(VERSION_EU_X)
#include "COMMON/SCREEN.H"
#endif
#if defined(VERSION_DE)
#if defined(VERSION_DE)
/* 80408AC4_23.CPP */
enum { menu_id_3ac = 934, menu_id_3b6 = 944 };
#endif
/* After MarkMenuEventHandled, opens screen g_extraOptionsScreen through Menu_ShowExtraOptionsPanel while its word at 0x34 is
   zero; otherwise handles the menu message Menu_GetFocusedElementId reports: menu_id_3ac closes the screen's first
   word through SmpSlider_SetTransitionMode with 2 and calls Menu_ApplyExtraOptionFlags, and menu_id_3b6 calls Menu_OpenOptionsKeypad.
   Returns zero. */
extern void MarkMenuEventHandled(void);
/* Calls MarkMenuEventHandled, then Menu_ShowExtraOptionsPanel when the word at offset 0x34 of the object g_extraOptionsScreen
   points to is clear, or SmpSlider_SetTransitionMode on its first word with 2 and Menu_ApplyExtraOptionFlags otherwise.
   Returns zero. */
extern void MarkMenuEventHandled();
s32 Menu_ConfirmGermanExtraOptions(void) {
    extern s32 SmpSlider_GetTransitionMode(void *);
    extern void SmpSlider_SetTransitionMode(void *, s32);
    extern struct StateMenuConfirmGermanExtraOptions *g_extraOptionsScreen;
    struct StateMenuConfirmGermanExtraOptions *state;

    MarkMenuEventHandled();
    if (SmpSlider_GetTransitionMode(g_extraOptionsScreen->first) != 3) {
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

/* MENU_DISPATCHEXTRAOPTIONSEVENT.CPP */
#if defined(VERSION_DE)
/* Dispatches event event through this file's 12-byte handler table, whose rows hold an event at g_extraOptionsEventCodes, an actor kind at g_extraOptionsActorKinds and a handler at g_extraOptionsEventCallbacks: the first row whose event equals event and whose kind equals the actor's halfword kind at 0xC, or is the wildcard 0x7530, receives all five arguments and its result is returned; with no such row, or an empty table, the result is zero. Adapted from N64Eng_DispatchNumericWidgetEvent. */
s32 Menu_DispatchExtraOptionsEvent(void *object, s32 event, s32 eventData, s32 eventValue, s32 eventContext) {
    char *entry;
    s32 offset;
    s32 wildcard;
    s32 actor_kind;
    s32 table_kind;

    if (g_extraOptionsEventCallbacks != 0) {
        wildcard = 30000;
        entry = (char *)&g_extraOptionsEventCallbacks;
        offset = 0;
        do {
            if (((struct AnimationEventMaskView *) (((char *) (&g_extraOptionsEventCodes)) + offset))->value == event) {
                actor_kind = ((struct MenuActorInputView *) ((char *) object))->input;
                table_kind = ((struct AnimationEventMaskView *) (((char *) (&g_extraOptionsActorKinds)) + offset))->value;
                if ((table_kind == actor_kind) || (table_kind == wildcard)) {
                    return (*(WidgetEventHandler *)entry)(object, event, eventData, eventValue, eventContext);
                }
            }
            entry += sizeof(ResidentEventHandlerEntry);
            offset += 12;
        } while (*(WidgetEventHandler *)entry != 0);
    }
    return 0;
}
#endif

/* MENU_OPENOPTIONSKEYPAD_DATA.CPP */
#if defined(VERSION_DE)
/* 800E4400.CPP */
/* ROM-grounded data: rodata/writable/800E4400 */
struct {
    void * g_extraOptionsScreen;
} k_MenuOpenoptionskeypadZeroWords __attribute__((aligned(4))) = {
    0
};
typedef char k_MenuOpenoptionskeypadZeroWordsSizeCheck[(sizeof(k_MenuOpenoptionskeypadZeroWords) == 4) ? 1 : -1];
#endif
#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#if defined(VERSION_DE)
/* 800E4404.CPP */
extern char Menu_UpdateExtraOptionsMenu_Address[];
extern char Menu_OpenRuleToggleScreen_Address[];
extern char Menu_DestroyExtraOptionsMenu_Address[];
#if defined(VERSION_DE)
struct {
    ResidentEventHandlerEntry handlers[6];
    u32 alignmentFill[1];
} D_src_16391c30 __attribute__((aligned(4))) = {
    { { 3592, 28, (ResidentEventHandler)(void *)&Menu_UpdateExtraOptionsMenu_Address }, { 3590, 28, (ResidentEventHandler)(void *)&Menu_OpenRuleToggleScreen_Address }, { 3587, 28, (ResidentEventHandler)(void *)&Menu_DestroyExtraOptionsMenu_Address }, { 2, 28, (ResidentEventHandler)(void *)(Menu_UpdateExtraOptionsMenu_Address + 348) }, { 1, 28, (ResidentEventHandler)(void *)(Menu_UpdateExtraOptionsMenu_Address + 164) }, { 0, 0, (ResidentEventHandler)0 } },
    { 0x00421BAC }
};
#endif
#endif
#endif
