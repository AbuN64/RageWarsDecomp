#ifndef ENGINE_SCENE_DRAWOPAQUEACTORS_H
#define ENGINE_SCENE_DRAWOPAQUEACTORS_H
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "COMMON/SCENERECAT10C0.H"
extern void Scene_ChangeInstanceModel(struct SceneModelBankView *, struct ObjectSceneChangeInstanceModel *, s32, s32);
extern void Scene_EmptyHandlerAfterSetSecondaryLevelBit(void);
extern s32 Scene_TestCurrentSecondaryLevelBit(struct Shared_World *world, s32 bitIndex);
extern void Scene_SetCurrentSecondaryLevelBit(struct Shared_World *world, s32 bitIndex, s32 enabled);
#endif
