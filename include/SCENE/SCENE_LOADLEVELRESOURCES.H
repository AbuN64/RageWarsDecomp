#ifndef SCENE_SCENE_LOADLEVELRESOURCES_H
#define SCENE_SCENE_LOADLEVELRESOURCES_H
#include "COMMON/SCENERECAT10C0.H"
#include "SCENE/SCENE_UPDATEANDDRAWWORLD.H"
extern void Scene_CollectLevelSwitches(SceneLevelSwitchCollectionView *world);
extern void Scene_BuildPlacedInstances(Shared_World *world, void * * *handle);
extern void Scene_UpdateActorVisibility(Shared_World *world);
#endif
