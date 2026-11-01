#ifndef GOBJINST_GASTATE_ADVANCEROOTMOTION_DATA_H
#define GOBJINST_GASTATE_ADVANCEROOTMOTION_DATA_H
#include "COMMON/WORLD.H"
extern void Gobjinst_AdvanceActorRootMotion(void *actor);
extern void Gobjinst_DispatchAnimationIntervalEvents(char *obj, void *anim, f32 from, f32 to);
extern CQuatern Gobjinst_BuildAssistedAimQuaternion(char *actor, CVector3 point, CQuatern *assist, f32 cone);
#endif
