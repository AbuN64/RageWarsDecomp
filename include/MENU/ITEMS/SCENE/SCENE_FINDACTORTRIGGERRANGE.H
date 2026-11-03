#ifndef MENU_ITEMS_SCENE_SCENE_FINDACTORTRIGGERRANGE_H
#define MENU_ITEMS_SCENE_SCENE_FINDACTORTRIGGERRANGE_H
void Scene_FindActorTriggerRange(char *world, void *levelActor, s32 *firstIndex, s32 *lastIndex);
s32 Scene_FindAlternateTriggerRange(char *world, u16 *triggerIds, s32 *firstIndex, s32 *lastIndex);
struct Shared_World;
s32 Scene_GetIndexedModelResource(struct Shared_World *world, s32 type);
s32 Scene_TestTriggerKindFlags(char *object, s32 type);
#endif
