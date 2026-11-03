#ifndef CBARREL_CBARREL_SELECTCOMBATTARGET_H
#define CBARREL_CBARREL_SELECTCOMBATTARGET_H
struct BarrelAnchorActorView;
struct Tracker;
struct BarrelAnchorActorView *Cbarrel_SelectCombatTarget(struct BarrelAnchorActorView *actor, struct Tracker *tracker, s32 lineOfSight, s32 combat);
struct TrackerAimActorView;
struct Plan;
s32 Cbarrel_UpdateTrackerAim(struct TrackerAimActorView *actor, struct Plan *tracker, struct TrackerAimActorView *candidate);
#endif
