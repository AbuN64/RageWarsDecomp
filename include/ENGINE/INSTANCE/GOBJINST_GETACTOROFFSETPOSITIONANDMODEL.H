#ifndef ENGINE_INSTANCE_GOBJINST_GETACTOROFFSETPOSITIONANDMODEL_H
#define ENGINE_INSTANCE_GOBJINST_GETACTOROFFSETPOSITIONANDMODEL_H
#include "COMMON/ACTORRESOURCEHEADER.H"
extern CVector3 *Gobjinst_TransformVectorByActorAim(CVector3 *out, void *actor, CVector3 localVector);
extern float Gobjinst_GetActorOffsetDefault(void);
extern void Gobjinst_SetAttachmentEffectBitTwo(void *object, int enabled);
extern s32 Gobjinst_TestActorTriangleVerticalClearance(struct Shared_CollisionActor *actor);
#endif
