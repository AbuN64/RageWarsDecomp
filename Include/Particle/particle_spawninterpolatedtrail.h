struct GameplayCamera;
#ifndef PARTICLE_PARTICLE_SPAWNINTERPOLATEDTRAIL_H
#define PARTICLE_PARTICLE_SPAWNINTERPOLATEDTRAIL_H
#include "Engine/particle.h"
#include "Common/runtime_declarations.h"
#include "Common/packedmeshmaterial.h"
#include "Render/particle_spawninterpolatedtrail.h"
struct ActorInstanceHeader;
struct EffectSystem;
struct Shared_Particle;
struct Shared_ParticleDesc;

extern void Particle_ReleaseFirstHandle(char *obj, unsigned char count);
extern void *Particle_FindOwnerEntry(struct EffectSystem *effectSystem, s32, struct Shared_ParticleDesc *effectEntry);
extern void Particle_InsertEntryGroup(struct EffectSystem *, struct Shared_Particle *);
extern s32 Particle_RandomInclusiveCount(s32);
extern void Particle_AdvanceRandomWhenNonzero(f32);
extern float Particle_GetConditionalFirstValue(struct Shared_Particle *effect);
extern f32 Particle_GetConditionalSecondValue(struct Shared_Particle *effect);
extern s32 Particle_IsKind2Or86Or273Or294(struct Shared_Particle *effect);
extern s32 Particle_IsKind5To7Or9Or17Or19Or26Or257Or272(struct Shared_Particle *effect);
extern s32 Particle_IsKind8Or13Or18(struct Shared_Particle *effect);
extern void Particle_UpdateForcesAndMotion(struct Shared_Particle *effect);
extern void Particle_CheckNearbyPlayerContacts(struct Shared_Particle *particle);
extern s32 Particle_HasClearMotionPath(struct ActorInstanceHeader *, struct GameplayCamera *);
extern void Particle_MarkNearbyObjects(s32 particleContext, struct Shared_Particle *center, struct Shared_Particle * *objects, s32 count);
extern void Particle_UpdateNearbyObjectFlags(int context, struct Shared_Particle * *objects, int count);
#endif
