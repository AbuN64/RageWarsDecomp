#ifndef MENU_ITEMS_SCENE_OVLSCENE_FINDPLACEDOBJECTSBYKEY_H
#define MENU_ITEMS_SCENE_OVLSCENE_FINDPLACEDOBJECTSBYKEY_H
struct Shared_World;
struct Shared_Placed;
s32 Scene_FindNearestPlacedObject(struct Shared_World *world, f32 *position, s32 kind, struct Shared_Placed *out);
struct Shared_World;
void Scene_LoadPreviewBufferB(struct Shared_World *state);
#endif
