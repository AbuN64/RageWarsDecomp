#ifndef PICKUP_PICKUP_CANCOLLECT_H
#define PICKUP_PICKUP_CANCOLLECT_H
struct Player;
s32 Pickup_CanCollect(s32 prop, struct Player *actor);
struct Other;
s32 Pickup_DispatchHandler(struct Other *actor, s32 target, s32 id);
#endif
