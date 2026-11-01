#ifndef COMMON_MODEL_RENDER_H
#define COMMON_MODEL_RENDER_H
#include "TYPES.H"
#include "COMMON/PARTICLE_LIGHTING.H"
/* Resource render entry points: matrices and lighting are caller-owned buffers. */
void Geometry_DrawActorModelParts(void **resource, void *owner, void *matrix, s32 segment, void *lights, void *textures, s32 pass);
void Geometry_DrawTintedModelParts(void **resource, void *owner, void *matrix, s32 segment, void *lights, void *textures, s32 pass, u8 red, u8 green, u8 blue, u8 alpha);
void Geometry_DrawModelResource(void **resource, void *matrix, s32 segment, void *lights, void *textures, s32 pass);
void Geometry_DrawOwnerFilteredPass(void **resource, void *owner, void *matrix, s32 segment, Shared_ParticleLighting *lights, void *textures, s32 pass);
#endif
