#ifndef ENGINE_SCENE_LOADLEVELRESOURCES_H
#define ENGINE_SCENE_LOADLEVELRESOURCES_H
#include "COMMON/SCENE_FRAME_AND_EFFECT_UPDATES.H"
struct Shared_World; extern void Scene_UpdateActorVisibility(struct Shared_World *world);
extern void Scene_DispatchEnabledEntityTrigger(WorldSceneDispatchEnabledEntityTrigger*world, Entity*entity);
#endif
