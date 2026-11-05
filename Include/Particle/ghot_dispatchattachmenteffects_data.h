#ifndef PARTICLE_GHOT_DISPATCHATTACHMENTEFFECTS_DATA_H
#define PARTICLE_GHOT_DISPATCHATTACHMENTEFFECTS_DATA_H
struct EffectSystem;
struct Shared_Particle;
struct CVector3_t;
struct CQuatern_t;
struct EffectSystem;
s32 Particle_SpawnEffectGroup(struct EffectSystem *sys, void *source, void *owner, s32 *refCount, s32 followTarget, s32 kind,
                  CVector3 inheritedVelocity, CQuatern rotation, CVector3 pos, CVector3 *aim, s32 requestedMode, s32 spawnFlags);
#endif
