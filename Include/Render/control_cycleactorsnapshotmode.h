#ifndef RENDER_CONTROL_CYCLEACTORSNAPSHOTMODE_H
#define RENDER_CONTROL_CYCLEACTORSNAPSHOTMODE_H
#include "types.h"
#include "Common/snapshot_actor.h"
struct SampledEffectCurveState;
extern f32 Control_SampleEffectCurve(struct SampledEffectCurveState *p);
extern s32 Control_GetSnapshotActorId(void);
extern void Control_InitializeCurvePlayer(unsigned int *record, unsigned int value);
struct ControllerProfile;
void Control_SetProfileMode(struct ControllerProfile *slot, s32 profileMode);
#endif
