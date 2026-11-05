#ifndef GOBJINST_GAMEOBJECT_MOVETOXZKEEPHEIGHT_H
#define GOBJINST_GAMEOBJECT_MOVETOXZKEEPHEIGHT_H
#include "types.h"
extern void Insthdr_ResetInstanceRenderIndices(signed char *prop);
#include "types.h"

#include "Collide/ccollision_testsegmentdisk.h"
#include "Engine/Instance/gobjinst.h"
struct ActorHorizontalMovementView;
struct HorizontalMovementSurfaceView;
struct CVector3_t;
void GameObject_ApplyMaterialCurrents(struct ActorHorizontalMovementView *actor, struct HorizontalMovementSurfaceView *material, struct CVector3_t *movement, s32 applyDirectionalCurrent);
void GameObject_ResetActorMotion(void *levelActor);

extern int InstHdr_GetActorMotionState(void *levelActor);
#endif
