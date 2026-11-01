#ifndef SCHED_SCHED_RUNEVENTLOOPUS_H
#define SCHED_SCHED_RUNEVENTLOOPUS_H
#include "COMMON/WORLDSORTENTRY.H"
extern s32 Scene_TestSectorSectionTwoEntries(struct Shared_World *world);
extern void *Scene_GetStridedActorRecord(struct Shared_World *object, int index);
extern void Scene_CollectSecondarySpecialActors(LevelActorArrayView *scene);
#endif
