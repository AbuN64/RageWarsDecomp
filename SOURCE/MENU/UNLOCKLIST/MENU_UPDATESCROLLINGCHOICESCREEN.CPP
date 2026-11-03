#include "COMMON/SHAREDPLAYER.H"
#include "include_asm.h"
#include "COMMON/MENULISTSCREEN.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/OWNERRECAT8V1.H"
#include "TYPES.H"
#include "SCENE/CACHE_FREEMEMORY.H"
#include "PLAYERCOUNT/FRONTEND_UPDATEPLAYERCOUNTSCREEN.H"
extern struct StateMenuUpdateScrollingChoiceScreen *g_unlockGatedListScreen;
extern void SmpSlider_SetTransitionMode(struct SliderTransitionView *object, s32 mode);
extern s32 Defs_TestBit(void *, s32);

/* Releases the object g_unlockGatedListScreen holds through Cache_FreeMemory, clears g_unlockGatedListScreen and returns zero. */

#if defined(VERSION_DE)
enum { MENU_RESOURCE = 313 };
#elif defined(VERSION_EU)
enum { MENU_RESOURCE = 315 };
#elif defined(VERSION_EU_X)
enum { MENU_RESOURCE = 319 };
#elif defined(VERSION_US_REV1) || defined(VERSION_US)
enum { MENU_RESOURCE = 315 };
#endif

/* Runs the screen g_unlockGatedListScreen each frame: when its menu reports 1 for the first time it marks the
   word at 0x14 and, unless bit 0 of the flag set at 0x7E of the first 400-byte record of
   g_localPlayerProfiles is set, passes 0x13B to Menu_SetFocusedElement; while the menu reports 3 it counts the delay
   at 0xC down and on expiry scrolls the list at 0x8 back one row, wrapping to the menu's own row
   count, and restarts the delay at 3; when the menu reports 4 it calls MarkMenuEventHandled and leaves
   through SmXlate_SwitchScreen with the target at 0x10, or 3 when that is -1. Returns zero. Adapted from
   Frontend_UpdatePlayerCountScreen with the stage test removed, case 1 added and the -1 target mapped to 3. */

extern u8 g_localPlayerProfiles[];

extern s32 SmpSlider_GetTransitionMode(s32 *record);

extern void Menu_SetFocusedElement(s32);

extern void MarkMenuEventHandled();

extern void SmXlate_SwitchScreen(s32);

/* Calls MarkMenuEventHandled, then sets the word at offset 0x10 of the object g_unlockGatedListScreen points to to -1 and
   calls SmpSlider_SetTransitionMode on the object's first word with 2, returning zero. */

/* Handles menu selection and updates the active menu state. */

extern u8 g_profileCharacterSelections;
extern char g_profileModeOnePlayedLevels[];
extern u8 g_activeProfileCharacterSelections;

 void MarkMenuEventHandled(void);

 s32 Menu_GetFocusedElementId(void);





s32 Menu_FreeScrollingChoiceScreen(void) {
    Cache_FreeMemory(g_unlockGatedListScreen);
    g_unlockGatedListScreen = 0;
    return 0;
}

/* Calls SmpButton_WrapButtonWidget with 0x13B, 0x13A and 0x13C in turn and returns zero. */
s32 Menu_WrapScrollingChoiceNodes(void) {
#if defined(VERSION_DE)
    SmpButton_WrapButtonWidget(313);
    SmpButton_WrapButtonWidget(312);
    SmpButton_WrapButtonWidget(314);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    SmpButton_WrapButtonWidget(315);
    SmpButton_WrapButtonWidget(314);
    SmpButton_WrapButtonWidget(316);
#elif defined(VERSION_EU_X)
    SmpButton_WrapButtonWidget(319);
    SmpButton_WrapButtonWidget(318);
    SmpButton_WrapButtonWidget(320);
#endif
    return 0;
}

s32 Menu_UpdateScrollingChoiceScreen(void) {
    s32 result;
    s32 target;

    switch (result = SmpSlider_GetTransitionMode(g_unlockGatedListScreen->menu)) {
    case 1:
        if (g_unlockGatedListScreen->seen != 0) {
            return 0;
        }
        g_unlockGatedListScreen->seen = result;
        if (Defs_TestBit(((Profile *)g_localPlayerProfiles)->levelFlags[0], 0) != 0) {
            return 0;
        }
        Menu_SetFocusedElement(MENU_RESOURCE);
        return 0;
    case 3:
        if (--g_unlockGatedListScreen->delay <= 0) {
            g_unlockGatedListScreen->list->transitionTimer--;
            if (g_unlockGatedListScreen->list->transitionTimer + g_unlockGatedListScreen->list->transitionDuration < 0) {
                g_unlockGatedListScreen->list->transitionTimer = g_unlockGatedListScreen->menu->list->transitionDuration;
            }
            g_unlockGatedListScreen->delay = result;
        }
        break;
    case 4:
        MarkMenuEventHandled();
        target = g_unlockGatedListScreen->target;
        if (target == -1) {
            target = 3;
        }
        SmXlate_SwitchScreen(target);
        break;
    default:
        return 0;
    }
    return 0;
}

s32 Menu_CancelScrollingChoiceScreen(void) {
    struct StateMenuUpdateScrollingChoiceScreen *state;

    MarkMenuEventHandled();
    state = g_unlockGatedListScreen;
    state->target = -1;
    SmpSlider_SetTransitionMode(state->menu, 2);
    return 0;
}

s32 Menu_HandleScrollingChoice(void) {
    s32 focusedElementIdResult;
    s32 unusedInteger1;
    MarkMenuEventHandled();
    focusedElementIdResult = Menu_GetFocusedElementId();
    switch (focusedElementIdResult) { /* irregular */
#if defined(VERSION_DE)
    case 312 + 2:
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    case 314 + 2:
#elif defined(VERSION_EU_X)
    case 318 + 2:
#endif
        g_unlockGatedListScreen->target = -1;
        break;
#if defined(VERSION_DE)
    case 312 + 1:
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    case 314 + 1:
#elif defined(VERSION_EU_X)
    case 318 + 1:
#endif
        if (Defs_TestBit(&g_profileModeOnePlayedLevels, 0) == 0) {
            g_unlockGatedListScreen->target = 7;
        } else {
            g_unlockGatedListScreen->target = 30;
        }
        break;
#if defined(VERSION_DE)
    case 312:
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    case 314:
#elif defined(VERSION_EU_X)
    case 318:
#endif
        g_activeProfileCharacterSelections = g_profileCharacterSelections;
        g_unlockGatedListScreen->target = 10;
        break;
    }
    SmpSlider_SetTransitionMode(g_unlockGatedListScreen->menu, 2);
    return 0;
}
