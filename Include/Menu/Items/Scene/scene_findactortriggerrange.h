struct Shared_World;
struct LevelActor;
#ifndef MENU_ITEMS_SCENE_SCENE_FINDACTORTRIGGERRANGE_H
#define MENU_ITEMS_SCENE_SCENE_FINDACTORTRIGGERRANGE_H
struct Shared_World;
void Scene_FindActorTriggerRange(struct Shared_World *world, struct LevelActor *levelActor, s32 *firstIndex, s32 *lastIndex);
s32 Scene_FindAlternateTriggerRange(struct Shared_World *world, u16 *triggerIds, s32 *firstIndex, s32 *lastIndex);
struct Shared_World;
s32 Scene_GetIndexedModelResource(struct Shared_World *world, s32 type);
s32 Scene_TestTriggerKindFlags(struct Shared_World *object, s32 type);
#endif
