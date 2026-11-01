#ifndef SCENE_SCENE_FINDTRACKEDACTORS_H
#define SCENE_SCENE_FINDTRACKEDACTORS_H
#include "COMMON/WORLDRECAT1B6A4.H"
#include "COMMON/WORLD.H"
#include "COMMON/COLORENTRY.H"
#include "ENGINE/SCENE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
extern void Scene_ReleaseCachedGeometry(void *);
extern void Scene_CollectVisibleEffects(s32);
extern void Scene_ClearTransparentInstanceCount(void *object);
extern void Scene_UpdateStaticEventInstances(StateSceneUpdateStaticEventInstances *);
extern s32 Scene_GetLevelActorIndex(void *container, void *);
extern void Scene_FindSelectedTriggerRange(char *world, s32, s32, s32 *, s32 *);
extern void Scene_CacheBlLevelData(void *world, s32);
extern void Scene_AccessLevelStateSection(struct WorldSceneDispatchEnabledEntityTrigger *, s32, s32 index, s32);
extern void Scene_SetSelectedLevelStateBit(struct WorldSceneDispatchEnabledEntityTrigger *, s32, s32 index, s32, s32, s32);
extern s32 Scene_TestSelectedLevelStateBit(struct WorldSceneDispatchEnabledEntityTrigger *, s32, s32 index, s32, s32);
extern s32 Scene_TestSecondaryLevelBit(void *, s32 index, s32);
extern s32 Scene_TestActorBitForLevel(Field_void_80 *, s32 index, s32);
extern s32 Scene_TestRecordBitForLevel(Field_void_80 *, s32 index, s32);
extern s32 Scene_TestTriggerBitForLevel(Field_void_80 *, s32 index, s32);
extern s32 Scene_GetTriggerCounterAddress(Shared_World *world, s32);
extern void Scene_SwapDistanceSortEntries(WorldSortEntry *, WorldSortEntry *);
extern s32 Scene_CompareDistanceAscending(WorldSortEntry *, WorldSortEntry *);
extern s32 Scene_CompareDistanceDescending(WorldSortEntry *, WorldSortEntry *);
extern void Scene_CollectTypeFourteenActors(Shared_World *world);
extern void Scene_FindTrackedActors(Shared_World *world);
#endif
