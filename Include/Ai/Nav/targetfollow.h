#ifndef AI_NAV_TARGETFOLLOW_H
#define AI_NAV_TARGETFOLLOW_H
struct LevelActor;
#include "Ai/source.h"

extern void Nav_InitTargetFollowing(struct LevelActor *actor);

extern void Nav_UpdateTargetRouteFollow(void *actorObject);
extern void Nav_ResetTargetFollowStateDe(void * object);
#endif
