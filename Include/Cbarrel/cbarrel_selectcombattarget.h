#ifndef CBARREL_CBARREL_SELECTCOMBATTARGET_H
#define CBARREL_CBARREL_SELECTCOMBATTARGET_H
struct LevelActor;
struct LevelActor;
struct Tracker;
struct LevelActor *Cbarrel_SelectCombatTarget(struct LevelActor *actor, struct Tracker *tracker, s32 lineOfSight, s32 combat);
struct Plan;
s32 Cbarrel_UpdateTrackerAim(struct LevelActor *actor, struct Plan *tracker, struct LevelActor *candidate);
#endif
