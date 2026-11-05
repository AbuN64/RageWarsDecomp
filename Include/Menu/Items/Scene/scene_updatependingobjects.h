#ifndef MENU_ITEMS_SCENE_SCENE_UPDATEPENDINGOBJECTS_H
#define MENU_ITEMS_SCENE_SCENE_UPDATEPENDINGOBJECTS_H
struct Shared_World;
void Scene_SetSelection(struct Shared_World *state,int selection,int mode);
struct ItemsPendingState;
struct Shared_World;
void Scene_UpdatePendingObjects(struct Shared_World *pendingWorld);
#endif
