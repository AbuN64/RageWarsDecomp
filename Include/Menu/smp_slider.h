#ifndef MENU_SMP_SLIDER_H
#define MENU_SMP_SLIDER_H
#include "Menu/scroll.h"
extern void SmpSlider_IgnoreFormattedMessage(void *target, const char *format, ...);
extern s32 SmpSlider_DispatchSliderEvent(void *element, s32 event, s32 source, s32 parameter, s32 value);
extern void SmpSlider_RegisterSliderClass(void);
extern s32 SmpSlider_DispatchTransitionEvent(void *element, s32 event, s32 source, s32 parameter, s32 value);
extern s32 SmpSlider_DestroyController(void *allocation);
extern s32 SmpSlider_HighlightSliderItems(struct SmpControlItemListView *menu);
#endif
