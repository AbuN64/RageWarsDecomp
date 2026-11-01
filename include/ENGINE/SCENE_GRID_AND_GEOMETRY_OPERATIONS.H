#ifndef ENGINE_SCENE_GRID_AND_GEOMETRY_OPERATIONS_H
#define ENGINE_SCENE_GRID_AND_GEOMETRY_OPERATIONS_H
#include "COMMON/SCENE_FRAME_AND_EFFECT_UPDATES.H"
#include "SCENE/SCENE_UPDATEANDDRAWWORLD.H"
#include "COMMON/GLOBALS.H"
#include "COMMON/OBJB.H"
#include "MENU/SCENE_RESOURCE_PREVIEW_AND_COLLISION_VIEWS.H"
#include "COMMON/WORLD.H"
extern void Scene_RequestVisibleGridSections(DraftStreamWorld *);
extern void Scene_BuildCachedGeometry(DraftStreamWorld*world);
extern const char s_gridSectionText[];
extern void Scene_DrawCachedOpaqueGeometry(SceneSceneDrawCachedOpaqueGeometry *scene, void *camera);
extern void Scene_BuildPlacedActors(World *world, struct CacheResourceBlockView * *handle);
extern void Scene_LoadGridCells(SceneGridCellLoadView *level);
extern void Scene_InitPreview(Shared_World *world, s32 level);
#endif
