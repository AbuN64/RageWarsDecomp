#ifndef MENU_ITEMS_SCENE_SCENE_SETLEVELACTORSTATEBIT_H
#define MENU_ITEMS_SCENE_SCENE_SETLEVELACTORSTATEBIT_H
void Scene_DecrementTriggerCounter(void *world, s32 triggerIndex);
void Scene_SetLevelActorStateBit(void *world, s32 index, s32 actorIndex, s32 enabled);
struct LevelBitRecord;
void Scene_SetLevelRecordStateBit(void *world, struct LevelBitRecord *levelBitRecord, s32 recordIndex);
void Scene_SetTriggerStateBit(void *world, void *trigger, s32 triggerIndex);
struct Shared_World;
s32 Scene_StartWorldEffect(struct Shared_World *world, s32 id, s32 flags, s32 extra);
s32 Scene_TestTriggerCounterZero(void *world, s32 triggerIndex);
s32 Scene_TestTriggerStateBit(struct Shared_World *world, void *trigger);
#endif
