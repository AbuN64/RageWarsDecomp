#ifndef MENU_ITEMS_MENU_VALUE_AND_LINE_TEXT_H
#define MENU_ITEMS_MENU_VALUE_AND_LINE_TEXT_H
#include "TYPES.H"
extern s32 Menu_CountLineChars(void *item);
extern s32 Menu_AdjustValue(void *menu, s32 value, s32 step, s32 minimum, s32 maximum, s32 wrap);
#endif
