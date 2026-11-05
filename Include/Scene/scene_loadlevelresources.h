#ifndef SCENE_SCENE_LOADLEVELRESOURCES_H
#define SCENE_SCENE_LOADLEVELRESOURCES_H
#include "Common/scene_switch.h"
#include "Scene/scene_updateanddrawworld.h"
struct Shared_World;
extern void Scene_CollectLevelSwitches(struct Shared_World *world);
extern void Scene_BuildPlacedInstances(struct Shared_World *world, void * * *handle);
extern void Scene_UpdateActorVisibility(struct Shared_World *world);
#endif
