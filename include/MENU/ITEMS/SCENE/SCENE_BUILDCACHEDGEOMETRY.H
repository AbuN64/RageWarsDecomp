#ifndef MENU_ITEMS_SCENE_SCENE_BUILDCACHEDGEOMETRY_H
#define MENU_ITEMS_SCENE_SCENE_BUILDCACHEDGEOMETRY_H
struct CScene_t;
struct GameplayCamera;
void Scene_DrawVisibleInstances(struct CScene_t *world, struct GameplayCamera *camera);
struct DraftStreamWorld;
void Scene_RequestVisibleGridSections(struct DraftStreamWorld *world);
#endif
