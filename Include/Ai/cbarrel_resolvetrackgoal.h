#ifndef AI_CBARREL_RESOLVETRACKGOAL_H
#define AI_CBARREL_RESOLVETRACKGOAL_H
#include "types.h"
struct LevelActor;
struct Tracker;
struct BarrelTargetInfo;
extern void Cbarrel_ResolveTrackGoal(struct LevelActor *actor, struct Tracker *tracker, s32 boost, struct BarrelTargetInfo *out);

#endif
