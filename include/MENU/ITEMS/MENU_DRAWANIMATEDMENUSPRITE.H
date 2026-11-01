#ifndef MENU_ITEMS_MENU_DRAWANIMATEDMENUSPRITE_H
#define MENU_ITEMS_MENU_DRAWANIMATEDMENUSPRITE_H
#include "MENU/OBJECT1C8.H"
extern void Menu_EnableMenuItemExtra(s16 *record, struct MenuItemVisibilityFlagView *object);
extern void Menu_InitMenuItemFromDescriptor(CMenuItem *w, WidgetDescriptor *d, char **arena, int id, int arg);
extern void Menu_StepSpriteFrame(struct Object1C8 *object);
extern void Menu_DrawAnimatedMenuSprite(MenuSpriteElement *e);
extern s32 Menu_GetMirroredMenuFrame(struct MenuItemCountView *object);
extern s32 Menu_GetMenuItemExtraSize(s16 *record);
#endif
