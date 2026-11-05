#ifndef MENU_ITEMS_SCENE_SELECTION_PREVIEW_OPERATIONS_H
#define MENU_ITEMS_SCENE_SELECTION_PREVIEW_OPERATIONS_H
struct Shared_World;
struct Shared_Placed;
struct Shared_World;
#include "Common/objb.h"
#include "Common/world.h"
#include "Menu/scene_resource_preview_and_collision_views.h"
extern void Scene_ResetSelectionState(char *);
extern void Scene_InitPreview(struct Shared_World *world, s32 level);
extern void Scene_ChangePreviewSelection(struct Shared_World *state, int selection);
extern s32 Scene_FindPlacedObjectsByKey(void *world, s32 kind, s32 key, struct Shared_Placed *out, s32 max);
#endif
