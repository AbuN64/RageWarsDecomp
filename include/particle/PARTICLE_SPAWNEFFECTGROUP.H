#ifndef PARTICLE_PARTICLE_SPAWNEFFECTGROUP_H
#define PARTICLE_PARTICLE_SPAWNEFFECTGROUP_H
#include "TYPES.H"
#include "COMMON/VECTOR4F.H"
struct EffectActor;
struct EffectSystem;
extern s32 Particle_SpawnEffectGroup(struct EffectSystem *sys, struct EffectActor *source, struct EffectActor *owner,
                            s32 *refCount, s32 followTarget, s32 kind, CVector3 inheritedVelocity, CQuatern rotation, CVector3 pos,
                            CVector3 *aim, s32 requestedMode, s32 spawnFlags);
#endif
