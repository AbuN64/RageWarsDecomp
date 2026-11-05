#ifndef UI_TSMOS_SMP_SMP_FLICKER_H
#define UI_TSMOS_SMP_SMP_FLICKER_H
#include "Common/animation.h"

struct FlickerUpdateState;
extern void SmpFlicker_RegisterFlickerClass(void);

extern s32 SmpFlicker_DispatchEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra);
extern void SmpFlicker_IgnoreEvent(s32 widget, struct Triple eventData);
extern void SmpFlicker_InitFlicker(struct FlickerUpdateState*flicker, s32 sampleCount);
extern s32 SmpFlicker_DestroyController(void *allocation);
extern s32 SmpFlicker_UpdateFlicker(struct FlickerUpdateState *flicker);
#endif
