#ifndef SCENE_SCENE_BUILDCOLLISIONGEOMETRY_H
#define SCENE_SCENE_BUILDCOLLISIONGEOMETRY_H
#include "Menu/scene_resource_preview_and_collision_views.h"
#include "Common/world.h"
struct Shared_World;
extern void Scene_BuildCollisionGeometry(struct Shared_World *world, CollisionBuildMeshHandle * *handle);
#endif
