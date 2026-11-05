#ifndef FRONTEND_OPTIONS_LIST_DECLARATIONS_H
#define FRONTEND_OPTIONS_LIST_DECLARATIONS_H
#include "types.h"
#include "Ui/Tsmos/Smp/smp_button.h"
/* The one declaration of the options-list widget calls and of the German second-list label words (adjacent pointer words at 0x800D3488..0x800D3490). */
struct MenuListWidget;

extern void SmpButton_AppendListText(struct MenuListWidget *, u8 *);

extern u8 *g_optionsLowResolutionLabels[1];
extern u8 *g_optionsHighResolutionLabels, *g_optionsLetterboxLabels;
#endif
