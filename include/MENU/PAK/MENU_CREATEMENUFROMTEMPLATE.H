#ifndef MENU_PAK_MENU_CREATEMENUFROMTEMPLATE_H
#define MENU_PAK_MENU_CREATEMENUFROMTEMPLATE_H
#include "COMMON/TEXTLAYERMETRICS.H"
#include "MENU/OPTION_AND_TEXT_LAYER_VIEWS.H"
#include "COMMON/ITEMRECAT20V1.H"

extern s32 Menu_GetInnerMenuLock(struct Outer *outer);
extern float Menu_GetGlyphAdvance(int c, unsigned char next, float sx, float sy);
extern char *Menu_GetObjectDetailData(struct GamePlayerListView *object);
struct MenuValueStepView;
s32 Menu_AdjustValue(struct MenuValueStepView *menu,s32 value,s32 step,s32 minimum,s32 maximum,s32 wrap);
struct MenuCreationOwnerView;
struct ParamsPakAllocateMenu;
struct MenuBuildDefinition;
struct MenuBuildState *Menu_AllocateMenu(struct MenuCreationOwnerView *owner, struct ParamsPakAllocateMenu *params, struct MenuBuildDefinition *list);
struct MenuBuildState *Menu_OpenDialog(void *parent, struct MenuBuildDefinition *list, s32 player, s32 controller, s32 d);
s32 Menu_TryCreateMenu(void *first, void *second, void *third);
#endif
