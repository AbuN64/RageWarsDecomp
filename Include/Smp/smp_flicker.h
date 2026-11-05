#ifndef SMP_SMP_FLICKER_H
#define SMP_SMP_FLICKER_H
#include "types.h"
struct FlickerStartView;
struct FlickerActivityView;
struct FlickerRestoreView;
struct MenuResourceWidget;
extern s32 SmpFlicker_IsFlickerIdle(struct FlickerActivityView *object);
extern void SmpFlicker_RestoreFlickerValue(struct FlickerRestoreView *source);
extern void SmpFlicker_StartFlicker(struct FlickerStartView *object, s32 count);
#include "Common/animation.h"
struct MenuResourceWidget *SmpFlicker_CreateFlickerWidget(s32 widgetResourceId, s32 ownerValue);
#endif
