#ifndef MENU_ITEMS_MENU_DRAWANIMATEDMENUSPRITE_H
#define MENU_ITEMS_MENU_DRAWANIMATEDMENUSPRITE_H
#include "MENU/OBJECT1C8.H"
#include "MENU/BUILT_MENU.H"
extern void Menu_EnableMenuItemExtra(s16 *record, struct MenuItemVisibilityFlagView *object);
extern void Menu_InitMenuItemFromDescriptor(CMenuItem *w, WidgetDescriptor *d, char **arena, int id, int arg);
extern void Menu_StopMenuPulse(MenuBuildState *object);
extern void Menu_StartMenuPulse(MenuBuildState *object);
extern void Menu_StepSpriteFrame(MenuBuildState *object);
extern void Menu_DrawAnimatedMenuSprite(MenuBuildState *e);
extern s32 Menu_GetMirroredMenuFrame(MenuBuildState *object);
extern s32 Menu_GetMenuItemExtraSize(s16 *record);
#endif
