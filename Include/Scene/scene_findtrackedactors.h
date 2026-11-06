struct Shared_World;
struct LevelActor;
#ifndef SCENE_SCENE_FINDTRACKEDACTORS_H
#define SCENE_SCENE_FINDTRACKEDACTORS_H
#include "Engine/scene_findtrackedactors.h"
struct Shared_World;
struct WorldSortEntry;
struct Shared_World;
#include "Common/world_scene.h"
#include "Common/world.h"
#include "Common/colorentry.h"
#include "Engine/scene.h"
#include "Common/runtime_declarations.h"
struct CVector3_t;
struct SceneLightVolume;
struct Shared_ParticleLighting;
extern void Scene_ReleaseCachedGeometry(struct Shared_World *);
extern void Scene_CollectVisibleEffects(s32);
extern void Scene_ClearTransparentInstanceCount(void *object);
extern void Scene_UpdateStaticEventInstances(struct Shared_World *);
extern s32 Scene_GetLevelActorIndex(void *container, void *);
extern void Scene_FindSelectedTriggerRange(struct Shared_World *world, s32, s32, s32 *, s32 *);
extern void Scene_CacheBlLevelData(struct Shared_World *world, s32);
extern void Scene_AccessLevelStateSection(struct Shared_World *, s32, s32 index, s32);
extern void Scene_SetSelectedLevelStateBit(struct Shared_World *, s32, s32 index, s32, s32, s32);
extern s32 Scene_TestSelectedLevelStateBit(struct Shared_World *, s32, s32 index, s32, s32);
extern s32 Scene_TestSecondaryLevelBit(struct Shared_World *, s32 index, s32);
extern s32 Scene_TestActorBitForLevel(struct Shared_World *, s32 index, s32);
extern s32 Scene_TestRecordBitForLevel(struct Shared_World *, s32 index, s32);
extern s32 Scene_TestTriggerBitForLevel(struct Shared_World *, s32 index, s32);
extern s32 Scene_GetTriggerCounterAddress(struct Shared_World *world, s32);
extern void Scene_SwapDistanceSortEntries(struct WorldSortEntry *, struct WorldSortEntry *);
extern s32 Scene_CompareDistanceAscending(struct WorldSortEntry *, struct WorldSortEntry *);
extern s32 Scene_CompareDistanceDescending(struct WorldSortEntry *, struct WorldSortEntry *);
extern void Scene_CollectTypeFourteenActors(struct Shared_World *world);
extern void Scene_FindTrackedActors(struct Shared_World *world);
#include "Common/world.h"
extern void Scene_CopyLevelName(struct Shared_World *world, s32 type, void *levelName, s32 maximumBytes);
extern char *Scene_GetPlatformRoute(void *world, s32 index);
extern void Scene_SampleVolumeLighting(struct SceneLightVolume **volumes, s32 count, struct CVector3_t *position, struct Shared_ParticleLighting *lighting);
#endif
