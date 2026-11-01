#ifndef AI_NAV_FARTHEST_H
#define AI_NAV_FARTHEST_H
#include "COMMON/SELF.H"
extern void Nav_UpdateRetreatMovement(void *actorObject);
extern void Nav_InitCombatTargetApproach(void *actor);
extern void Nav_SeekUnclaimedMarker(void *actor);
extern void Nav_SeekNearbyUnrestrictedGoal(struct Shared_Actor *actor);
extern void Nav_ApproachCombatTargetAlongRoute(CloseAttackActor *actor);
extern void Nav_InitRetreatMovement(struct LevelActor *actor);
extern void Nav_InitNearbyUnrestrictedGoal(struct LevelActor *actor);
extern void Nav_InitUnclaimedMarkerSearch(void *actor);
#endif
