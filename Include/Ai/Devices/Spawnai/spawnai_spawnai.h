#ifndef AI_DEVICES_SPAWNAI_SPAWNAI_SPAWNAI_H
#define AI_DEVICES_SPAWNAI_SPAWNAI_SPAWNAI_H
struct Action;
struct ActorTriggerDescriptorView;
extern void SpawnAI_DispatchSpawnChoice(SpawnDispatchObject *object, SpawnDispatchOwner *owner);
extern void SpawnAI_InitializeActionDelay(struct ActorTriggerDescriptorView *actor, struct Action *action);
#endif
