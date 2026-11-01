#ifndef COMMON_PARTICLE_LIGHTING_H
#define COMMON_PARTICLE_LIGHTING_H
#include "TYPES.H"

typedef struct Shared_ParticleLighting Shared_ParticleLighting;
struct Shared_ParticleLighting {
    u8 ambient[3], reserved3;
    u8 ambientCopy[3], reserved7;
    u8 diffuse[3], reservedB;
    u8 diffuseCopy[3], reservedF;
    s8 direction[3];
    u8 reserved13[5];
} __attribute__((aligned(4)));
extern Shared_ParticleLighting g_defaultParticleLighting;
#endif
