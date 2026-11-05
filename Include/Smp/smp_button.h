#ifndef SMP_SMP_BUTTON_H
#define SMP_SMP_BUTTON_H
#include "types.h"
#include "Menu/scroll.h"
extern s32 SmpButton_GetListSelection(s32 *record);
extern void SmpButton_AppendListText(struct MenuListWidget *menu, u8 *text);
extern void SmpButton_WrapButtonWidget(s32);
#endif
