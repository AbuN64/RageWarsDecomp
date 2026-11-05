#ifndef SCENE_SCENE_UNPACKVISIBILITYGEOMETRY_H
#define SCENE_SCENE_UNPACKVISIBILITYGEOMETRY_H
#include "Common/objb.h"
struct Shared_World;
extern void Scene_UnpackVisibilityGeometry(struct Shared_World *world, void * * *handle);
struct SceneResourceOwnerView;
struct Shared_World;
void Scene_FreeSceneResources(struct Shared_World *sceneToFree);
struct Shared_World;
void Scene_LoadSceneLight(struct Shared_World *scene);
#endif
