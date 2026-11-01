#include "COMMON/NUMBERPADSCREEN.H"
#include "MENU/STATE.H"
#include "TYPES.H"

#if !(defined(VERSION_DE))
/* Calls MarkMenuEventHandled, then Menu_ShowExtraOptionsPanel when the word at offset 0x34 of the object g_extraOptionsScreen
   points to is clear, or SmpSlider_SetTransitionMode on its first word with 2 and Menu_ApplyExtraOptionFlags otherwise.
   Returns zero. */
struct StateMenuConfirmGermanExtraOptions;

extern struct StateMenuConfirmGermanExtraOptions *g_extraOptionsScreen;
extern void MarkMenuEventHandled();

extern void SmpSlider_SetTransitionMode(struct SliderTransitionView *object, s32 mode);


s32 Menu_ConfirmExtraOptions(void) {
    struct StateMenuConfirmGermanExtraOptions *state;

    MarkMenuEventHandled();
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
