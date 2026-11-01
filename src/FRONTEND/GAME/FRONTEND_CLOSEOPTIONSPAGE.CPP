#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "TYPES.H"

/* 80423280_28.CPP */
/* Calls MarkMenuEventHandled, sets the word at offset 0x20 of the object g_optionsPage points to to -1,
   calls SmpSlider_SetTransitionMode on the object's first word with 2 and then Menu_CommitOptionsPage, returning zero. */

extern struct StateFrontendUpdateOptionsPageExit *g_optionsPage;
extern void MarkMenuEventHandled();
extern void SmpSlider_SetTransitionMode(struct SliderTransitionView *object, s32 mode);
extern void Menu_CommitOptionsPage(void);

s32 Frontend_CloseOptionsPage(void) {
    struct StateFrontendUpdateOptionsPageExit *state;

    MarkMenuEventHandled();
    state = g_optionsPage;
    state->value = -1;
    SmpSlider_SetTransitionMode(state->menu, 2);
    Menu_CommitOptionsPage();
    return 0;
}

/* 80423280_29.CPP */
#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* Returns zero. */
s32 Frontend_ReturnOptionsEventZeroA(void) {
    return 0;
}

/* Returns zero. */
s32 Frontend_ReturnOptionsEventZeroB(void) {
    return 0;
}
#endif
