#ifndef COMMON_SCREEN_H
#define COMMON_SCREEN_H
#include "Menu/menu.h"
#include "types.h"
#include "Common/numberpadscreen.h"

/* After MarkMenuEventHandled, opens screen g_extraOptionsScreen through Menu_ShowExtraOptionsPanel while its word at 0x34 is
   zero; otherwise handles the menu message Menu_GetFocusedElementId reports: 0x3AC closes the screen's first
   word through SmpSlider_SetTransitionMode with 2 and calls Menu_ApplyExtraOptionFlags, and 0x3B6 calls Menu_OpenOptionsKeypad.
   Returns zero. */

extern struct NumberPadScreen *g_extraOptionsScreen;
extern void MarkMenuEventHandled(void);
extern void Menu_ShowExtraOptionsPanel(void);
extern void SmpSlider_SetTransitionMode(struct SliderTransitionView *object, s32 mode);
extern void Menu_ApplyExtraOptionFlags(void);
extern void Menu_OpenOptionsKeypad(void);
#endif
