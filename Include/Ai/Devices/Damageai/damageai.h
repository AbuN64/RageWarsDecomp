#ifndef AI_DEVICES_DAMAGEAI_DAMAGEAI_H
#define AI_DEVICES_DAMAGEAI_DAMAGEAI_H
struct LevelActor;
extern void DamageAI_RequestCurrentActorState(struct LevelActor *actor, void *requestContext);
extern void DamageAI_ActivateActor(Obj5324 *actor, s32 *activationContext);
#endif
