#ifndef ENGINE_LIGHTING_H
#define ENGINE_LIGHTING_H
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/LIGHT_VOLUME_AND_TRIGGER_VIEWS.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "ACTORS/VERTEX_LIGHT_AND_ACTOR_VIEWS.H"
extern s32 Lighting_EvaluateLightVolume(SceneLightVolume *lightVolume, CVector3 worldPoint, CVector3 surfaceNormal, f32 *lightTransform, CVector3 *lightContribution, f32 *contributionWeight);
extern void Lighting_AccumulateVertexLighting(SceneLightVolume * *lights, s32 lightCount, Vertices38 *mesh, PackedMatrixWords *matrices, CVector3 *output, s32 multiple);
extern void Lighting_AccumulateDirectionalLighting(Vertices38 *data, PackedMatrixWords *matrices, CVector3 *output, s32 skin);
#endif
