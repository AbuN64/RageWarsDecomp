#ifndef CONTROL_CONTROL_CYCLEACTORSNAPSHOTMODE_H
#define CONTROL_CONTROL_CYCLEACTORSNAPSHOTMODE_H
#include "Common/Lone/controller_rumble_pool.h"
#include "Common/snapshot_actor.h"
struct SampledEffectCurveState;
extern void Control_ResetControllerProfiles(void);
extern void Control_SetControllerMode(s32 a);
extern void Control_SaveControllerSetup(void);
extern void Control_SetMenuControlFlag(void);
extern void Control_CycleActorSnapshotMode(void);
extern void Control_ResetActorSnapshot(void);
extern s32 Control_GetSnapshotActorId(void);
extern void Control_DeactivateActorSnapshot(void);
extern void Control_RestoreActorSnapshot(void);
extern void Control_TickSnapshotCountdown(void);
extern void Control_SaveActorSnapshot(void);
extern void Control_InitializeCurvePlayer(unsigned int *record, unsigned int value);
extern s32 Control_AdvanceEffectCurve(struct SampledEffectCurveState *curvePlayer);
extern float Control_SampleEffectCurve(struct SampledEffectCurveState *p);
#endif
