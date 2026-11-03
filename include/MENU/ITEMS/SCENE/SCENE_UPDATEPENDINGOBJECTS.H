#ifndef MENU_ITEMS_SCENE_SCENE_UPDATEPENDINGOBJECTS_H
#define MENU_ITEMS_SCENE_SCENE_UPDATEPENDINGOBJECTS_H
struct ItemsSelectionState;
void Scene_SetSelection(struct ItemsSelectionState *state,int selection,int mode);
struct ItemsPendingState;
void Scene_UpdatePendingObjects(struct ItemsPendingState *pendingWorld);
#endif
