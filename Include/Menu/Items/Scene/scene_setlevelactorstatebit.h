struct Shared_World;
struct LevelActor;
#ifndef MENU_ITEMS_SCENE_SCENE_SETLEVELACTORSTATEBIT_H
#define MENU_ITEMS_SCENE_SCENE_SETLEVELACTORSTATEBIT_H
struct Shared_World;
struct WorldTrigger;
void Scene_DecrementTriggerCounter(struct Shared_World *world, s32 triggerIndex);
void Scene_SetLevelActorStateBit(void *world, s32 index, s32 actorIndex, s32 enabled);
struct ObjB;
void Scene_SetLevelRecordStateBit(void *world, struct ObjB *levelBitRecord, s32 recordIndex);
void Scene_SetTriggerStateBit(void *world, void *trigger, s32 triggerIndex);
struct Shared_World;
s32 Scene_StartWorldEffect(struct Shared_World *world, s32 id, s32 flags, s32 extra);
struct Shared_World;
s32 Scene_TestTriggerCounterZero(struct Shared_World *world, s32 triggerIndex);
s32 Scene_TestTriggerStateBit(struct Shared_World *world, struct WorldTrigger *trigger);
#endif
