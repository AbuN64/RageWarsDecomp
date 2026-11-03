#ifndef GOBJINST_GAMEOBJECT_LOADMODEL_H
#define GOBJINST_GAMEOBJECT_LOADMODEL_H
void Gobjinst_LoadModel(void *actorStorage, s32 *modelDirectory, s32 directoryBank, s32 extra);
struct ActorModelLoadState;
void Gobjinst_UpdateActorGroundRotation(struct ActorModelLoadState *actor);
#endif
