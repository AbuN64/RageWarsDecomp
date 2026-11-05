struct LevelActor;
#ifndef GOBJINST_GAMEOBJECT_LOADMODEL_H
#define GOBJINST_GAMEOBJECT_LOADMODEL_H
#include "Ai/player_death_playerai.h"
#include "Engine/Instance/gobjinst.h"
#include "Ai/player_symbols.h"
#include "Engine/Instance/gastate_advancerootmotion_data.h"
void Gobjinst_LoadModel(void *actorStorage, s32 *modelDirectory, s32 directoryBank, s32 extra);
struct ActorModelLoadState;
void Gobjinst_UpdateActorGroundRotation(struct ActorModelLoadState *actor);
extern void Gastate_ResetAnimationReference(void *);
extern s32 Gobjinst_ChooseAnimationVariant(struct LevelActor *, s32, s32);
#endif
