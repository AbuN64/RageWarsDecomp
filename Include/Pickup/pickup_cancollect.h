#ifndef PICKUP_PICKUP_CANCOLLECT_H
#define PICKUP_PICKUP_CANCOLLECT_H
struct Player;
s32 Pickup_CanCollect(s32 prop, struct Player *actor);
struct Other;
struct Player;
s32 Pickup_DispatchHandler(struct Player *actor, s32 target, s32 id);
#endif
