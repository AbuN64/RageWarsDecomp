#ifndef COMMON_PACKEDMESHMATERIAL_H
#define COMMON_PACKEDMESHMATERIAL_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
/* Section zero of packed and expanded mesh resources. */
typedef struct CROMSection {
    s32 textureId;
    s32 flags;
    u16 renderMode;
    u8 mode;
    u8 reservedB;
    u8 primaryColor[4];
    u8 secondaryColor[4];
    u16 width;
    u16 height;
} CROMSection;
typedef struct MeshMaterial {
    s32 flags;
    s16 renderMode;
    u8 mode;
    u8 reserved7;
    s32 texture;
    u8 reservedC[4];
    u8 primaryColor[4];
    u8 secondaryColor[4];
    u16 width;
    u16 height;
} MeshMaterial;

struct ObjParticleMarkNearbyObjects;


struct ParticleEffect;


struct RncCompressedResourceHeaderView;
typedef struct RncCompressedResourceHeaderView RncCompressedResourceHeaderView;







struct ResourcePayloadSizeView;
typedef struct ResourcePayloadSizeView ResourcePayloadSizeView;


struct ParticleTrailEmitterView;
typedef struct ParticleTrailEmitterView ParticleTrailEmitterView;

struct ObjParticleMarkNearbyObjects;

extern float g_packedFloatRandomScale;








extern float g_particleMaximumSearchDistance;




struct ResourcePayloadSizeView;




struct RncCompressedResourceHeaderView;

struct ParticleTrailEmitterView;




struct ObjParticleMarkNearbyObjects;
typedef struct ObjParticleMarkNearbyObjects ObjParticleMarkNearbyObjects;



extern float g_particleNearestEffectDistanceTuning;





extern double g_packedFloatRandomBias;





#endif
