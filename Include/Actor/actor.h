#ifndef ACTOR_ACTOR_H
#define ACTOR_ACTOR_H
struct LevelActor;
struct Dest;
struct ActorSpawnCallbacks;
void Actor_InitSpawnedActor(struct LevelActor *source, struct Dest *actor, struct ActorSpawnCallbacks *callbacks);
#endif
