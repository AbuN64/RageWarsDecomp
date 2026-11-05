struct Shared_World;
struct LevelActor;
#ifndef COMMON_SCENE_FRAME_AND_EFFECT_UPDATES_H
#define COMMON_SCENE_FRAME_AND_EFFECT_UPDATES_H
#include "Common/shared_gameslot.h"
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/results.h"
#include "Common/scene_switch.h"
struct Shared_World;
struct Shared_Pickup;
#include "Common/world.h"
#include "Common/menu_ui_providers.h"






#include "Common/runtime_declarations.h"
#include "Common/triple.h"

#include "Common/weapon_screen_message_operations.h"
#include "Common/ballisticparams.h"
#include "Common/shared_menureply.h"

extern s32 g_litGeometryResourceKeysChanged;


struct Shared_World;
extern void Scene_UpdateSelectionTransition(struct Shared_World *);
extern void Scene_ClearSceneObjectCounts(struct Shared_World *object);

struct CacheResourceNode;
extern void Cache_MarkResourceInUse(s32, struct CacheResourceNode *);
extern void Fx_ResetRibbonVertexPool(void *);
struct CPlayerPool_t;
extern void Playerai_RotatePlayerPoseBuffers(struct CPlayerPool_t *);
extern void Scene_CollectVisibleEffects(s32);
extern void Fx_UpdateEffectLists(s32 owner);
extern void Scene_UpdateActorsAndRoundState(struct Shared_World *);
extern void Scene_UpdateTriggerTimers(struct Shared_World *);
extern void Particle_UpdateSystem(struct EffectSystem *world);
extern void Camera_DrawActiveViews(struct ScreenMessageOwner *race, s32 world);
extern void Scene_UpdateStaticEventInstances(struct Shared_World *);
extern void Scene_UnlockActiveSectionResources(struct Shared_World *owner);
extern void Scene_DrawTransitionColorOverlay(struct Shared_World *);
#endif
