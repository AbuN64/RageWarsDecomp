#ifndef ACTOR_ACTOR_UPDATEACTORSTATEANIMATION_H
#define ACTOR_ACTOR_UPDATEACTORSTATEANIMATION_H
struct Source110;
struct Dest;
void Actor_UpdateActorStateAnimation(struct Source110 *src, struct Dest *dst);
s32 Actor_RequestActorState(void *actor, void *stateController, s32 action);
#endif
