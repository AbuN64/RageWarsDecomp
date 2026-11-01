#ifndef MENU_ITEMS_SCENE_SELECTION_PREVIEW_OPERATIONS_H
#define MENU_ITEMS_SCENE_SELECTION_PREVIEW_OPERATIONS_H
#include "COMMON/OBJB.H"
#include "COMMON/WORLD.H"
#include "MENU/SCENE_RESOURCE_PREVIEW_AND_COLLISION_VIEWS.H"
extern void Scene_ResetSelectionState(char *);
extern void Scene_InitPreview(struct Shared_World *world, s32 level);
extern void Scene_ChangePreviewSelection(ItemsPreviewStateB *state, int selection);
extern s32 Scene_FindPlacedObjectsByKey(void *world, s32 kind, s32 key, Shared_Placed *out, s32 max);
#endif
