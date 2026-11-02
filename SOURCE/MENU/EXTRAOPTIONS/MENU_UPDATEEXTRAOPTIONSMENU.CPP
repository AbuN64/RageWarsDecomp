#include "COMMON/SCREEN.H"
#include "COMMON/NUMBERPADSCREEN.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/PAKQUEUESTATE.H"
#include <ultra64.h>
#include "TYPES.H"
#include "MENU/MENU_REFRESHEXTRAOPTIONLOCKS.H"
#include "MENU/MENU_SCROLLOPTIONSKEYPAD.H"
#include "SCENE/CACHE_FREEMEMORY.H"
extern MenuWidget *Node_FindWidgetByResourceId(void *, s32);

/* Calls Widget_SetWidgetFlag08_EquipActivateequipmentpanel with zero on the object at offset 0x20 of the structure g_extraOptionsScreen points
   to, and with one on the entry 0x3AB that Node_FindWidgetByResourceId finds in the list at offset 8, then sets
   the word at offset 0x34. */


extern void Widget_SetWidgetFlag08(void *object, int enabled);

/* Advances the animation frame countdown and wraps exhausted frames. */


 /* extern */
void Menu_AdvanceTextRows(void *, void *);

 /* extern */


/* Releases the object g_extraOptionsScreen holds through Cache_FreeMemory, clears g_extraOptionsScreen and returns zero. */



/* Polls the dialog of screen g_extraOptionsScreen through SmpSlider_GetTransitionMode: state 3 opens the screen through
   Menu_ScrollOptionsKeypad while its word at 0x34 is zero, and otherwise, when g_combinedControllerProfile.buttons is 0x433, marks the
   screen confirmed at 0x38 and calls Menu_RefreshExtraOptionLocks; state 4 calls MarkMenuEventHandled and waits 3
   through SmXlate_SwitchScreen. Returns zero. */





extern s32 SmpSlider_GetTransitionMode(s32 *record);


extern void SmXlate_SwitchScreen(s32);

void Menu_ShowExtraOptionsPanel(void) {
    Widget_SetWidgetFlag08(g_extraOptionsScreen->pad, 0);
#if defined(VERSION_DE)
    Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, 933), 1);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, 939), 1);
#elif defined(VERSION_EU_X)
    Widget_SetWidgetFlag08(Node_FindWidgetByResourceId(g_extraOptionsScreen->window, 943), 1);
#endif
    g_extraOptionsScreen->open = 1;
}

void Menu_ScrollOptionsKeypad(void) {
    s32 currentMode;
    MenuWidget *scrollingPad;
    MenuWidget *wrappedPad;
    MenuWidget *textRow;
    currentMode = g_extraOptionsScreen->mode - 1;
    g_extraOptionsScreen->mode = currentMode;
    if (currentMode <= 0) {
#if defined(VERSION_DE)
        textRow = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, 946);
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
        textRow = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, 952);
#elif defined(VERSION_EU_X)
        textRow = Node_FindWidgetByResourceId(g_extraOptionsScreen->window, 956);
#endif
        scrollingPad = g_extraOptionsScreen->pad;
        scrollingPad->y = (u16) (scrollingPad->y - 1);
        wrappedPad = g_extraOptionsScreen->pad;
        if (((s16) wrappedPad->y + textRow->height) < 0) {
            wrappedPad->y = 2U;
            Menu_AdvanceTextRows(wrappedPad, g_extraOptionsScreen);
        }
        g_extraOptionsScreen->mode = 1;
    }
}

s32 Menu_DestroyExtraOptionsMenu(void) {
    Cache_FreeMemory(g_extraOptionsScreen);
    g_extraOptionsScreen = 0;
    return 0;
}

s32 Menu_UpdateExtraOptionsMenu(void) {
    switch (SmpSlider_GetTransitionMode(g_extraOptionsScreen->dialog)) {
    case 3:
        if (g_extraOptionsScreen->open == 0) {
            Menu_ScrollOptionsKeypad();
            return 0;
        }
        if (g_combinedControllerProfile.buttons != 0x433) {
            return 0;
        }
        g_extraOptionsScreen->confirmed = 1;
        Menu_RefreshExtraOptionLocks();
        return 0;
    case 4:
        MarkMenuEventHandled();
        SmXlate_SwitchScreen(3);
        return 0;
    }
    return 0;
}
