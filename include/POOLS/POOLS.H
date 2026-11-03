#ifndef POOLS_POOLS_H
#define POOLS_POOLS_H
struct Triple;
void Pools_InitGroupPools(struct Triple *group);
struct Draw;
void *Pools_RecycleModel(struct Draw *owner);
struct ScreenMessageOwner;
void Pools_ResetPlayers(struct ScreenMessageOwner *actor);
#endif
