#ifndef ENGINE_INSTANCE_GASTATE_ADVANCEROOTMOTION_DATA_H
#define ENGINE_INSTANCE_GASTATE_ADVANCEROOTMOTION_DATA_H
#include "Gobjinst/gameobject_getactorheight.h"
#include "Collide/ccollision_testsegmentdisk.h"
#include "Common/localdecoderange.h"
extern void Gobjinst_DispatchAnimationIntervalEvents(char *,void *,f32,f32);
extern s32 Gastate_IsAnimationResourceRetained(void *);
extern char *Gastate_GetAnimationPoseSection(void *animationState);
extern char g_actorRotationBlendAndResourceTuning;
extern s32 Gastate_GetAnimationEventEntries(void *animationState);
extern void MatrixFromQuaternion(f32 *q, f32 *m);
extern s32 g_gameFrameCounter;
#endif
