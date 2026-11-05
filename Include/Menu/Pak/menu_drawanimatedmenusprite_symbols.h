#ifndef MENU_PAK_MENU_DRAWANIMATEDMENUSPRITE_SYMBOLS_H
#define MENU_PAK_MENU_DRAWANIMATEDMENUSPRITE_SYMBOLS_H
#include "types.h"
extern struct CMenuFontInfo_t g_menuFontStyles[];
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US) || defined(VERSION_US_REV1)
#else
extern void * Menu_GetGermanDynamicItemText(struct MenuItemTargetView *);
#endif
#endif
