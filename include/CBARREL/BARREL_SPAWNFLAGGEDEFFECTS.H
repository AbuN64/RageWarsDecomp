#ifndef CBARREL_BARREL_SPAWNFLAGGEDEFFECTS_H
#define CBARREL_BARREL_SPAWNFLAGGEDEFFECTS_H
struct LevelActor;
struct CVector3_t;
f32 Barrel_GetFlatDistanceSquared(struct LevelActor *actor, struct CVector3_t point);
struct ActorDamageHookView;
void Barrel_RunDamageHook(void *actor, struct ActorDamageHookView *callbackState, void *damage);
void Barrel_SetLoopingSound(void *actor, void *stateController, s32 sixth);
struct Player;
void Barrel_SpawnFlaggedEffects(struct Player *actor, s32 *emittedFlags, s32 emissionFlag, s32 primaryEffectMask, s32 secondaryEffectMask);
void Barrel_StopActorLoopingSound(void *actor, void *soundState);
#endif
