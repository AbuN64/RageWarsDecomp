#ifndef GOBJINST_GASTATE_ADVANCEROOTMOTION_DATA_H
#define GOBJINST_GASTATE_ADVANCEROOTMOTION_DATA_H
#include "Common/world.h"
#include "Common/actorresourceheader.h"
extern void Gobjinst_AdvanceActorRootMotion(void *actor);
extern void Gobjinst_DispatchAnimationIntervalEvents(char *obj, void *anim, f32 from, f32 to);
extern CQuatern Gobjinst_BuildAssistedAimQuaternion(char *actor, CVector3 point, CQuatern *assist, f32 cone);
struct CVector3_t;
extern void Gobjinst_ApplyImpactBoneTwist(char *actor, struct ActorBoneTwistState *twistState, char *boneMatrix, struct CVector3_t impactPosition, struct CVector3_t impactDirection, s32 hitBoneIndex);
#endif
