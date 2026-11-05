#ifndef MENU_ITEMS_SCENE_SCENE_REGISTERACTORINSCENELISTS_H
#define MENU_ITEMS_SCENE_SCENE_REGISTERACTORINSCENELISTS_H
struct Shared_World;
void Scene_DispatchSecondaryTriggersOfKind(struct Shared_World *world, s32 triggerKind);
struct Shared_World;
struct CVector3_t;
struct Shared_ParticleLighting;
void Scene_SampleWorldLighting(struct Shared_World *world, struct CVector3_t *position, struct Shared_ParticleLighting *out);
#endif
