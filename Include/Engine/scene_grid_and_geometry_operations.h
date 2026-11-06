#ifndef ENGINE_SCENE_GRID_AND_GEOMETRY_OPERATIONS_H
#define ENGINE_SCENE_GRID_AND_GEOMETRY_OPERATIONS_H
struct Shared_World;
#include "Common/scene_frame_and_effect_updates.h"
#include "Scene/scene_updateanddrawworld.h"
#include "Common/globals.h"
#include "Common/objb.h"
#include "Menu/scene_resource_preview_and_collision_views.h"
#include "Common/world.h"
#include "Menu/Items/Scene/scene_buildcachedgeometry.h"

struct Shared_World;
extern void Scene_BuildCachedGeometry(struct Shared_World*world);

extern void Scene_BuildCachedGeometry(struct Shared_World *world);
extern const char s_gridSectionText[];
extern const char s_sceneVisibilityResourceText[12];
extern const char s_sceneMultiplayerResourceText[20];
extern void Scene_DrawCachedOpaqueGeometry(struct Shared_World *scene, void *camera);
extern void Scene_BuildPlacedActors(struct Shared_World *world, struct CacheResourceNode * *handle);
extern void Scene_LoadGridCells(struct Shared_World *level);
extern void Scene_InitPreview(struct Shared_World *world, s32 level);
#endif
