#ifndef GOBJINST_GOBJINST_BUILDACTORPOSE_H
#define GOBJINST_GOBJINST_BUILDACTORPOSE_H
#include "Engine/graphics_math.h"
#include "Engine/map.h"
#include "Engine/Instance/gastate_advancerootmotion_data.h"
#include "Gobjinst/gameobject_getactorheight.h"
#include "Common/shared_menureply.h"
struct SceneObject;
struct GameplayCamera;
void Gobjinst_DrawVisibleCachedActor(struct SceneObject *object, struct GameplayCamera *camera);
extern s32 g_gameFrameCounter;
extern struct Shared_FrameProfile g_actorPoseTiming;
extern void Gobjinst_ApplyTimedMatrixWobble(s32 time, s32 flags, f32 *matrix);
extern void Gastate_PrepareAnimationFrames();
extern char s_actorModelVariantResourceTag[];
struct Shared_PoseActor;
s32 Gobjinst_BuildActorPose(struct Shared_PoseActor *actor, void *modelPack, s32 model);
#endif
