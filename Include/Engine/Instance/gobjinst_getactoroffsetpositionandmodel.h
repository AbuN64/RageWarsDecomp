#ifndef ENGINE_INSTANCE_GOBJINST_GETACTOROFFSETPOSITIONANDMODEL_H
#define ENGINE_INSTANCE_GOBJINST_GETACTOROFFSETPOSITIONANDMODEL_H
#include "Engine/Instance/Gobjinst/gastate_advancerootmotion_data.h"
#include "Engine/map.h"
#include "Common/actorresourceheader.h"
extern CVector3 *Gobjinst_TransformVectorByActorAim(CVector3 *out, void *actor, CVector3 localVector);
extern float Gobjinst_GetActorOffsetDefault(void);
extern void Gobjinst_SetAttachmentEffectBitTwo(void *object, int enabled);
extern s32 Gobjinst_TestActorTriangleVerticalClearance(struct Shared_CollisionActor *actor);
struct Camera;
void Gobjinst_DrawModelWithProjection(void *actor, struct Camera *camera, f32 *transform, u8 layer);
s32 Gobjinst_GetModelRenderMode(void *typedActor);
struct LevelActor;
void Gobjinst_UpdateActorController(struct LevelActor *base);
extern void MatrixFromQuaternion(f32 *q, f32 *m);
#endif
