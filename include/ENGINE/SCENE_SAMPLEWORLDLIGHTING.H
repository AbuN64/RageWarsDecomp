#ifndef ENGINE_SCENE_SAMPLEWORLDLIGHTING_H
#define ENGINE_SCENE_SAMPLEWORLDLIGHTING_H
#include "TYPES.H"
#include "COMMON/PARTICLE_LIGHTING.H"
struct Shared_World;
extern void Scene_SampleWorldLighting(struct Shared_World *world, CVector3 *position, Shared_ParticleLighting *out);
#endif
