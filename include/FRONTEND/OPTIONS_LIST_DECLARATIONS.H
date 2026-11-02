#ifndef FRONTEND_OPTIONS_LIST_DECLARATIONS_H
#define FRONTEND_OPTIONS_LIST_DECLARATIONS_H
#include "TYPES.H"
/* The one declaration of the options-list widget calls and of the German second-list label words (adjacent pointer words at 0x800D3488..0x800D3490). */
struct MenuListWidget;
extern struct MenuListWidget *SmpButton_CreateListWidget(s32, s32);
extern void SmpButton_AppendListText(struct MenuListWidget *, u8 *);
extern void SmpButton_SelectListEntry(struct MenuListWidget *, s32);
extern u8 *g_optionsSecondListPrimaryLabels, *g_optionsSecondListSecondaryLabels, *g_optionsSecondListTertiaryLabels;
#endif
