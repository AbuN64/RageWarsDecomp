#ifndef PARTICLE_GHOT_DISPATCHATTACHMENTEFFECTS_DATA_H
#define PARTICLE_GHOT_DISPATCHATTACHMENTEFFECTS_DATA_H
struct EffectSystem;
struct EffectActor;
struct CVector3_t;
struct CQuatern_t;
s32 Particle_SpawnEffectGroup(struct EffectSystem *sys, struct EffectActor *source, struct EffectActor *owner, s32 *refCount, s32 followTarget, s32 kind, struct CVector3_t inheritedVelocity, struct CQuatern_t rotation, struct CVector3_t pos, struct CVector3_t *aim, s32 requestedMode, s32 spawnFlags);
#endif
