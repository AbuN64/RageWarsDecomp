#ifndef COMMON_SCENE_FRAME_AND_EFFECT_UPDATES_H
#define COMMON_SCENE_FRAME_AND_EFFECT_UPDATES_H
#include "COMMON/SHARED_GAMESLOT.H"
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RESULTS.H"
#include "COMMON/SCENERECAT10C0.H"
struct Shared_Pickup;
#include "COMMON/WORLD.H"
#include "COMMON/MENU_UI_PROVIDERS.H"






#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/TRIPLE.H"

#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/BALLISTICPARAMS.H"
#include "COMMON/SHARED_MENUREPLY.H"

extern s32 g_litGeometryResourceKeysChanged;


struct Shared_World;
extern void Scene_UpdateSelectionTransition(struct Shared_World *);
extern void Scene_ClearSceneObjectCounts(void *object);

struct CacheResourceNode;
extern void Cache_MarkResourceInUse(s32, struct CacheResourceNode *);
extern void Fx_ResetRibbonVertexPool(void *);
struct CPlayerPool_t;
extern void Playerai_RotatePlayerPoseBuffers(struct CPlayerPool_t *);
extern void Scene_CollectVisibleEffects(s32);
extern void Fx_UpdateEffectLists(s32 owner);
extern void Scene_UpdateActorsAndRoundState(void *);
extern void Scene_UpdateTriggerTimers(void *);
extern void Particle_UpdateSystem(struct CParticleSystem_t *world);
extern void Camera_DrawActiveViews(struct Race *race, s32 world);
extern void Scene_UpdateStaticEventInstances(struct StateSceneUpdateStaticEventInstances *);
extern void Scene_UnlockActiveSectionResources(struct OwnerSceneUnlockActiveSectionResources *owner);
extern void Scene_DrawTransitionColorOverlay(Shared_World *);
#endif
