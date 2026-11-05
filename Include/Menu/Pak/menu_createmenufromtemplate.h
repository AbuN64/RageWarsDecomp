#ifndef MENU_PAK_MENU_CREATEMENUFROMTEMPLATE_H
#define MENU_PAK_MENU_CREATEMENUFROMTEMPLATE_H
#include "Menu/built_menu.h"
#include "Common/session_state.h"
#include "Common/textlayermetrics.h"
#include "Menu/option_and_text_layer_views.h"

extern s32 Menu_GetInnerMenuLock(struct Outer *outer);
extern float Menu_GetGlyphAdvance(int c, unsigned char next, float sx, float sy);
extern char *Menu_GetObjectDetailData(struct MenuBuildEntry *object);
struct MenuValueStepView;
s32 Menu_AdjustValue(struct MenuValueStepView *menu,s32 value,s32 step,s32 minimum,s32 maximum,s32 wrap);
struct ParamsPakAllocateMenu;
struct MenuBuildDefinition;
struct MenuBuildState *Menu_AllocateMenu(struct MessageList *owner, struct ParamsPakAllocateMenu *params, struct MenuBuildDefinition *list);
struct MenuBuildState *Menu_OpenDialog(void *parent, struct MenuBuildDefinition *list, s32 player, s32 controller, s32 d);
s32 Menu_TryCreateMenu(void *first, void *second, void *third);
extern int Menu_CountLiveNodes(struct CMenu_t **head);

#endif
