#ifndef AI_NAV_TARGETFOLLOW_H
#define AI_NAV_TARGETFOLLOW_H
#include "AI/SOURCE.H"

extern void Nav_InitTargetFollowing(struct TargetFollowingActorView *actor);

extern void Nav_UpdateTargetRouteFollow(void *actorObject);
extern void Nav_ResetTargetFollowStateDe(void * object);
#endif
