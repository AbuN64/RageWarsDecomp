#ifndef RENDER_PARTICLE_SPAWNINTERPOLATEDTRAIL_H
#define RENDER_PARTICLE_SPAWNINTERPOLATEDTRAIL_H
#include "Common/packedmeshmaterial.h"
#include "Common/sharedplayer.h"
struct ResourcePayloadSizeView {
    void * payload;
    s32 byteCount;
};
struct RncCompressedResourceHeaderView {
    s32 magicAndMethod;
    s32 decodedByteCount;
    s32 packedByteCount;
    char pad8[0x6];
    s8 payloadStart;
};
extern float Particle_GetConditionalFirstValue(struct Shared_Particle *effect);
extern s32 Particle_RandomInclusiveCount(s32 maximumCount);
extern f32 Particle_GetConditionalSecondValue(struct Shared_Particle *effect);
extern void Particle_AdvanceRandomWhenNonzero(f32 value);
struct EffectSystem;
struct CVector3_t;
void Particle_AverageOwnerEffectPositions(struct EffectSystem *effectSystem, s32 ownerId, CVector3 *averagePositionOut);
struct Shared_Particle;
void Particle_UpdateMatrix(struct Shared_Particle *particle);
struct LevelActor;
extern void Particle_FindNearestForeignEffectDistance(struct EffectSystem *effectSystem, struct LevelActor *actor, f32 *distanceOut);
#endif
