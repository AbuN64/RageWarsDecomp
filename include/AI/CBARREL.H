#ifndef AI_CBARREL_H
#define AI_CBARREL_H
#include "MENU/TEAMMENU.H"
#include "COMMON/FIELD_VEC_B0.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"

extern void Barrel_ClearTargetInfo(struct Shared_ActorView *actorView, void *unused1, BarrelTargetInfo *targetInfo);

extern void Barrel_AddActorYaw(ActorYawView *actor, f32 yawDelta);

extern void Barrel_FillWordPair(int *value, int word);

extern f32 g_barrelFlaggedEffectRandomRanges;

extern s32 Cbarrel_ClassifyTrackTarget(struct LevelActor *actor, struct RouteChaseBot *routeChaseBot, struct LevelActor *targetActor);

extern void Cbarrel_LockTrackerTarget(void *unused0, void *trackerState, struct BarrelAnchorActorView *target, float lockDuration);

extern float g_trackGoalTargetHeightFactor;
extern float k_barrelKindTwoApproachPadding;
extern float k_barrelClearAimSearchRange;
extern const float g_goalBesideActorClearance;
#endif
