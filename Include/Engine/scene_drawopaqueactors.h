#ifndef ENGINE_SCENE_DRAWOPAQUEACTORS_H
#define ENGINE_SCENE_DRAWOPAQUEACTORS_H
#include "Engine/scene.h"
#include "Common/geometry_blend_and_instance_views.h"
#include "Common/scene_switch.h"
extern void Scene_ChangeInstanceModel(struct Shared_World *, struct ObjectSceneChangeInstanceModel *, s32, s32);
extern void Scene_EmptyHandlerAfterSetSecondaryLevelBit(void);
extern s32 Scene_TestCurrentSecondaryLevelBit(struct Shared_World *world, s32 bitIndex);
extern void Scene_SetCurrentSecondaryLevelBit(struct Shared_World *world, s32 bitIndex, s32 enabled);
struct Shared_World;
void Scene_DrawOpaqueActors(struct Shared_World *scene, void *camera);
void Scene_DrawWorldParticles(s32 world, s32 view);
s32 Scene_FindModelIdIndex(struct Shared_World *world, s32 modelId);
char *Scene_GetLinkedResourceSection(struct Shared_World *world, s32 resourceId);
void *Scene_GetModelRecordByIndexPointer(struct Shared_World *world, u16 *modelIndex);
u32 Scene_GetModelSectionTwoIndex(struct Shared_World *world, s32 modelId);
#endif
