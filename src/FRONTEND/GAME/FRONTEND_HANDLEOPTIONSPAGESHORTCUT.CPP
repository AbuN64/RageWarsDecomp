#include "COMMON/MENU_OPTIONS_AND_RESULTS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include <ultra64.h>
#include "TYPES.H"

/* Acts on the mode of the menu held first in the block g_optionsPage points to: in mode 4 it calls
   MarkMenuEventHandled and then either SmXlate_SwitchScreen with the block's word at 0x20, when that is not -1,
   or Menu_ReturnToPreviousScreen. Returns zero. */




extern struct StateFrontendUpdateOptionsPageExit *g_optionsPage;

extern s32 SmpSlider_GetTransitionMode(s32 *record);

extern void MarkMenuEventHandled();

extern void SmXlate_SwitchScreen(s32);

extern void Menu_ReturnToPreviousScreen(void);

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
enum { SHORTCUT_RESET = 80, SHORTCUT_SIX = 87, SHORTCUT_FIVE = 88 };
#elif defined(VERSION_EU_X)
enum { SHORTCUT_RESET = 92, SHORTCUT_SIX = 82, SHORTCUT_FIVE = 85 };
#endif

/* Handles the menu shortcut codes by selecting an entry and refreshing the screen. */


extern void MarkMenuEventHandled(void);
extern Menu_CommitOptionsPage(void);
extern void SmpSlider_SetTransitionMode(struct SliderTransitionView *object, s32 mode);

extern s32 Menu_GetFocusedElementId(void);

s32 Frontend_UpdateOptionsPageExit(void) {
    switch (SmpSlider_GetTransitionMode(g_optionsPage->menu)) {
    case 3:
        break;
    case 4:
        MarkMenuEventHandled();
        if (g_optionsPage->value != -1) {
            SmXlate_SwitchScreen(g_optionsPage->value);
        } else {
            Menu_ReturnToPreviousScreen();
        }
        break;
    }
    return 0;
}

s32 Frontend_HandleOptionsPageShortcut(void) {
    s32 focusedElementIdResult;
    s32 shortcutHandled;
    MarkMenuEventHandled();
    shortcutHandled = 1;
    focusedElementIdResult = Menu_GetFocusedElementId();
    switch(focusedElementIdResult) {
    case SHORTCUT_RESET:g_optionsPage->value=-1;break;
    case SHORTCUT_SIX:g_optionsPage->value=6;break;
    case SHORTCUT_FIVE:g_optionsPage->value=5;break;
    default:shortcutHandled=0;break;
    }
    if (shortcutHandled == 1) {
        Menu_CommitOptionsPage();
        SmpSlider_SetTransitionMode(g_optionsPage->menu, 2);
    }
    return 0;
}
