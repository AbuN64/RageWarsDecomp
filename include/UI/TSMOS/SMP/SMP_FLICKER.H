#ifndef UI_TSMOS_SMP_SMP_FLICKER_H
#define UI_TSMOS_SMP_SMP_FLICKER_H
#include "COMMON/ANIMATION.H"

extern void SmpFlicker_RegisterFlickerClass(void);

extern s32 SmpFlicker_DispatchEvent(void *eventObject, s32 eventId, s32 eventPayload, s32 eventValue, s32 eventExtra);
extern void SmpFlicker_IgnoreEvent(s32 unused0, struct Triple unused1);
extern void SmpFlicker_InitFlicker(FlickerUpdateState*flicker, s32 sampleCount);
#endif
