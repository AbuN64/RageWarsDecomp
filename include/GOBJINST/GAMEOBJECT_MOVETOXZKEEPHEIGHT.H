#ifndef GOBJINST_GAMEOBJECT_MOVETOXZKEEPHEIGHT_H
#define GOBJINST_GAMEOBJECT_MOVETOXZKEEPHEIGHT_H
struct ActorHorizontalMovementView;
struct HorizontalMovementSurfaceView;
struct CVector3_t;
void GameObject_ApplyMaterialCurrents(struct ActorHorizontalMovementView *actor, struct HorizontalMovementSurfaceView *material, struct CVector3_t *movement, s32 applyDirectionalCurrent);
void GameObject_ResetActorMotion(void *levelActor);
#endif
