#ifndef MENU_MENU_CREATEMENUFROMPARAMETERS_H
#define MENU_MENU_CREATEMENUFROMPARAMETERS_H
#include "Common/session_state.h"
struct Field;
struct LayeredText;
int Menu_CountLineChars(struct LayeredText *item);
struct MenuCreationParameters;
struct MenuBuildEntry;
struct StyledMenuTextEntryView;
struct StyledMenuTextPanel;
extern void Menu_DrawStyledMenuText(struct MenuBuildEntry *option, struct StyledMenuTextEntryView *entry, s32 unusedDirection, struct StyledMenuTextPanel *menu, void *text, s32 forceTileMode);
extern void Menu_DrawLocalizedMenuItemText(struct Field *object, s32 second, s32 third, s32 fourth);
extern struct PreviewWidget *Menu_SelectPreviewModel(struct MenuPreviewSelectionView *widget,int selection,int kind);

void *Menu_CreateMenuFromParameters(struct MessageList *owner, struct MenuCreationParameters *params);
struct Field {
    char pad[0x14];
    char **text;
    char pad18[0x4];
    signed int value;
};

#endif
