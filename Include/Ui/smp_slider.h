#ifndef UI_SMP_SLIDER_H
#define UI_SMP_SLIDER_H
#include "types.h"
struct MenuSliderWidget;
extern void SmpSlider_IncrementSliderItem(struct Scroll *scroll);
extern void SmpSlider_DecrementSliderItem(struct Scroll *scroll);
extern void SmpSlider_EnableTransition(struct Access_s32_5C *object);
extern struct MenuSliderWidget *SmpSlider_CreateSliderWidget(s32, s32, s32);
extern s32 SmpSlider_GetSliderItem(s32 *record);
extern void SmpSlider_SetSliderItem(struct Scroll *, s32);
#endif
