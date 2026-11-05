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
extern void Nav_UpdateRetreatMovement(void *actorObject);
extern void Nav_InitCombatTargetApproach(void *actor);
extern void Nav_SeekUnclaimedMarker(void *actor);
extern void Nav_SeekNearbyUnrestrictedGoal(struct Shared_Actor *actor);
extern void Nav_ApproachCombatTargetAlongRoute(struct CloseAttackActor *actor);
extern void Nav_InitRetreatMovement(struct LevelActor *actor);
extern void Nav_InitNearbyUnrestrictedGoal(struct LevelActor *actor);
extern void Nav_InitUnclaimedMarkerSearch(void *actor);
#endif
