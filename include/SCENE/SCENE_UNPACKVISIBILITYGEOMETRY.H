#ifndef SCENE_SCENE_UNPACKVISIBILITYGEOMETRY_H
#define SCENE_SCENE_UNPACKVISIBILITYGEOMETRY_H
#include "COMMON/OBJB.H"
extern void Scene_UnpackVisibilityGeometry(SceneVisibilityGeometryView *world, void * * *handle);
struct SceneResourceOwnerView;
void Scene_FreeSceneResources(struct SceneResourceOwnerView *sceneToFree);
struct SceneLightLoadView;
void Scene_LoadSceneLight(struct SceneLightLoadView *scene);
#endif
