#ifndef MENU_PAK_MENU_ENTRIES_H
#define MENU_PAK_MENU_ENTRIES_H
#include "Menu/built_menu.h"
struct MenuBuildState;
extern void Menu_MoveMenuCursor(struct MenuBuildState *menu, u8 direction);
extern s32 Menu_UpdateMenuEntries(struct MenuBuildState *menu, void *context);
#endif
