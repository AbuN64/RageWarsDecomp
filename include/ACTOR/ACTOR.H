#ifndef ACTOR_ACTOR_H
#define ACTOR_ACTOR_H
struct Source;
struct Dest;
struct ActorSpawnCallbacks;
void Actor_InitSpawnedActor(struct Source *source, struct Dest *actor, struct ActorSpawnCallbacks *callbacks);
#endif
