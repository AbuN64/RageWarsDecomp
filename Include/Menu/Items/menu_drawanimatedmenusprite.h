#ifndef MENU_ITEMS_MENU_DRAWANIMATEDMENUSPRITE_H
#define MENU_ITEMS_MENU_DRAWANIMATEDMENUSPRITE_H
#include "Menu/menu_item_views.h"
#include "Menu/built_menu.h"
struct MenuBuildState;
struct WidgetDescriptor;
extern void Menu_EnableMenuItemExtra(s16 *record, struct MenuItemVisibilityFlagView *object);
extern void Menu_InitMenuItemFromDescriptor(CMenuItem *w, struct WidgetDescriptor *d, char **arena, int id, int arg);
extern void Menu_StopMenuPulse(struct MenuBuildState *object);
extern void Menu_StartMenuPulse(struct MenuBuildState *object);
extern void Menu_StepSpriteFrame(struct MenuBuildState *object);
extern void Menu_DrawAnimatedMenuSprite(struct MenuBuildState *e);
extern s32 Menu_GetMirroredMenuFrame(struct MenuBuildState *object);
extern s32 Menu_GetMenuItemExtraSize(s16 *record);
#endif
