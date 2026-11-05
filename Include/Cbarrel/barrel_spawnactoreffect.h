#ifndef CBARREL_BARREL_SPAWNACTOREFFECT_H
#define CBARREL_BARREL_SPAWNACTOREFFECT_H
struct Player;
struct ActorMotionState;
struct CAIMovementInfo;
void Barrel_ComputeTargetOffset(struct Player *player, struct ActorMotionState *motionState, struct CAIMovementInfo *result);
struct SourceBarrelUpdateActorController;
struct DestBarrelUpdateActorController;
void Barrel_UpdateActorController(struct SourceBarrelUpdateActorController *src, struct DestBarrelUpdateActorController *dst);
#include "Ai/cbarrel.h"

#endif
