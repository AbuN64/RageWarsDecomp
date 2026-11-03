#ifndef PARTICLE_PARTICLE_RELEASEOWNERLISTONEEFFECTS_H
#define PARTICLE_PARTICLE_RELEASEOWNERLISTONEEFFECTS_H
struct EffectSystem;
s32 Particle_CountOwnerListOneEffects(struct EffectSystem *effectSystem, s32 ownerAddress);
void Particle_ReleaseOwnerListOneEffects(struct EffectSystem *effectSystem, s32 ownerAddress);
void Particle_ReleaseOwnerListTwoEffects(struct EffectSystem *effectSystem, s32 ownerAddress);
#endif
