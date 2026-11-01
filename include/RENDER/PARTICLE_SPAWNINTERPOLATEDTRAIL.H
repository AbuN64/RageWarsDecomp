#ifndef RENDER_PARTICLE_SPAWNINTERPOLATEDTRAIL_H
#define RENDER_PARTICLE_SPAWNINTERPOLATEDTRAIL_H
#include "COMMON/PACKEDMESHMATERIAL.H"
#include "COMMON/SHAREDPLAYER.H"
struct ObjParticleMarkNearbyObjects {
    char pad[4];
    unsigned short flags;
    char pad6[2];
    f32 pos[3];
    char pad14[0x138];
    short nearbyEffectFlags;
};
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
struct ParticleTrailEmitterView {
    char pad0[0x24];
    s32 mode;
    char pad28[0x100];
    CVector3 position128;
};
extern float Particle_GetConditionalFirstValue(struct ParticleEffect *effect);
extern s32 Particle_RandomInclusiveCount(s32 maximumCount);
extern f32 Particle_GetConditionalSecondValue(struct ParticleEffect *effect);
extern void Particle_AdvanceRandomWhenNonzero(f32 value);
#endif
