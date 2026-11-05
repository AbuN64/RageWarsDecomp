#ifndef MENU_MENU_MEASUREMENUTEXT_H
#define MENU_MENU_MEASUREMENUTEXT_H
#include "types.h"
extern u8 *Menu_GetDynamicItemText(struct TextBoundsText *);
extern void Menu_MeasureMenuText(struct TextBoundsText *text, struct CItemInfo_t *metrics);
#endif
