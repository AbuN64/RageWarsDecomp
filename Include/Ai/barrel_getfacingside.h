#ifndef AI_BARREL_GETFACINGSIDE_H
#define AI_BARREL_GETFACINGSIDE_H
#include "types.h"
#include "Common/probe.h"
extern f32 Barrel_FindClearAimAngle(Actor_u1 *actor, CVector3 point, s32 target, f32 distance);
#include "types.h"
#include "Common/probe.h"
#include "Common/vector.h"
struct LevelActor;
struct Tracker;
struct BarrelTargetInfo;
extern void Barrel_FillAnchorTargetInfo(struct LevelActor *actor, struct Tracker *tracker, s32 boostFlag, struct BarrelTargetInfo *targetInfo);



#endif
