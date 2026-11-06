#ifndef AI_NAV_FARTHEST_H
#define AI_NAV_FARTHEST_H
#include "types.h"
#include "Common/small_records.h"

struct Link;
struct Link {
    unsigned short from;
    unsigned short to;
    unsigned char type;
};
typedef struct Link Link;

#include "Common/self.h"
struct CloseAttackActor;
struct ObjNavComputeScaledPointCentroid;
struct ObjNavFindSpecialLinkedCandidate;
extern void Nav_UpdateRetreatMovement(void *actorObject);
extern void Nav_InitCombatTargetApproach(void *actor);
extern void Nav_SeekUnclaimedMarker(void *actor);
extern void Nav_SeekNearbyUnrestrictedGoal(struct Shared_Actor *actor);
extern void Nav_ApproachCombatTargetAlongRoute(struct CloseAttackActor *actor);
extern void Nav_InitRetreatMovement(struct LevelActor *actor);
extern void Nav_InitNearbyUnrestrictedGoal(struct LevelActor *actor);
extern void Nav_InitUnclaimedMarkerSearch(void *actor);
struct AiController;
extern void Nav_AccumulateNodeTickCosts(struct AiController *controller);
extern void Nav_AddPickupCategoryCosts(struct AiController *controller);
extern s32 Nav_ComputeScaledPointCentroid(struct ObjNavComputeScaledPointCentroid *request);
extern int Nav_FindSpecialLinkedCandidate(struct ObjNavFindSpecialLinkedCandidate *request);
extern void Nav_RequestRandomArmedWeapon(void *brain);
extern void Nav_SetLinkedActorNodeCosts(char *actor);
#endif
