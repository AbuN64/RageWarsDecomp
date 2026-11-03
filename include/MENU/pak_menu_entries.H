#ifndef MENU_PAK_MENU_ENTRIES_H
#define MENU_PAK_MENU_ENTRIES_H
#include "MENU/BUILT_MENU.H"
extern void Menu_MoveMenuCursor(MenuBuildState *menu, u8 direction);
extern s32 Menu_UpdateMenuEntries(MenuBuildState *menu, void *context);
#endif
