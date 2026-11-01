#include "include_asm.h"
#include "COMMON/NUMBERPADSCREEN.H"
#include "COMMON/CHEATCODE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "MENU/STATE.H"
#include "TYPES.H"
#if defined(VERSION_EU_X)
#include "COMMON/SCREEN.H"
/* 80406A88_5.CPP */
s32 Menu_HandleEuxExtraOptionsChoice(void) {
    s32 message;
    MarkMenuEventHandled();
    if (g_extraOptionsScreen->open == 0) {
        Menu_ShowExtraOptionsPanel();
    } else {
        message = Menu_GetFocusedElementId();
        switch (message) {
        case 954:
            SmpSlider_SetTransitionMode(g_extraOptionsScreen->dialog, 2);
            Menu_ApplyExtraOptionFlags();
            break;
        case 946:
            Menu_OpenOptionsKeypad();
            break;
        }
    }
    return 0;
}
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
extern s32 Menu_GetFocusedElementId(void);
/* Calls MarkMenuEventHandled, then Menu_ShowExtraOptionsPanel when the word at offset 0x34 of the object g_extraOptionsScreen
   points to is clear, or SmpSlider_SetTransitionMode on its first word with 2 and Menu_ApplyExtraOptionFlags otherwise.
   Returns zero. */
extern void MarkMenuEventHandled();
s32 Menu_HandleGermanExtraOptionsChoice(void) {
    extern s32 SmpSlider_GetTransitionMode(s32);
    extern void SmpSlider_SetTransitionMode(s32, s32);
    extern struct RecordFrontendSetPreviewModel *g_extraOptionsScreen;
    if (SmpSlider_GetTransitionMode(g_extraOptionsScreen->count) != 3) {
        return 0;
    }
    MarkMenuEventHandled();
    if (g_extraOptionsScreen->handle == 0) {
        Menu_ShowExtraOptionsPanel();
    } else {
        switch (Menu_GetFocusedElementId()) {
        case menu_id_3ac:
            SmpSlider_SetTransitionMode(g_extraOptionsScreen->count, 2);
            Menu_ApplyExtraOptionFlags();
            break;
        case menu_id_3b6:
            Menu_OpenOptionsKeypad();
            break;
        }
    }
    return 0;
}
#endif
