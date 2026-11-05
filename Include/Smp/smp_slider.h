#ifndef SMP_SMP_SLIDER_H
#define SMP_SMP_SLIDER_H
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Menu/smp_records.h"
struct MenuSliderWidget;
extern s32 SmpSlider_GetTransitionMode(s32 *record);
extern void SmpSlider_DisableTransition(struct Access_s32_5C *object);
extern void SmpSlider_EnableTransition(struct Access_s32_5C *object);
#include "Menu/scroll.h"
extern void SmpSlider_SetSliderItem(struct Scroll *scroll, s32 item);
struct MenuSliderWidget *SmpSlider_CreateSliderWidget(s32 sliderWidgetId, s32 childWidgetId, s32 initialTransition);
extern void SmpSlider_SetSliderItem(struct Scroll *, s32);
#endif
