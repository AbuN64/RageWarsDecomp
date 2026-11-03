#ifndef MENU_MENU_CREATEMENUFROMPARAMETERS_H
#define MENU_MENU_CREATEMENUFROMPARAMETERS_H
struct LayeredText;
int Menu_CountLineChars(struct LayeredText *item);
struct MenuCreationOwnerView;
struct MenuCreationParameters;
void *Menu_CreateMenuFromParameters(struct MenuCreationOwnerView *owner, struct MenuCreationParameters *params);
#endif
