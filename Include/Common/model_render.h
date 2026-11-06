#ifndef COMMON_MODEL_RENDER_H
#define COMMON_MODEL_RENDER_H
#include "types.h"
#include "Common/particle_lighting.h"
struct Shared_ParticleLighting;
/* Resource render entry points: matrices and lighting are caller-owned buffers. */
struct Player;
void Geometry_DrawActorModelParts(void **resource, struct Player *owner, void *matrix, s32 segment, struct Shared_ParticleLighting *lights, void *textures, s32 pass);
void Geometry_DrawTintedModelParts(void **resource, void *owner, void *matrix, s32 segment, void *lights, void *textures, s32 pass, u8 red, u8 green, u8 blue, u8 alpha);
void Geometry_DrawModelResource(void **resource, void *matrix, s32 segment, void *lights, void *textures, s32 pass);
void Geometry_DrawOwnerFilteredPass(void **resource, struct PlayerDamageFlagsView *owner, void *matrix, s32 segment, struct Shared_ParticleLighting *lights, void *textures, s32 pass);
#endif
