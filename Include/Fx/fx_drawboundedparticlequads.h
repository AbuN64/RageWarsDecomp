#ifndef FX_FX_DRAWBOUNDEDPARTICLEQUADS_H
#define FX_FX_DRAWBOUNDEDPARTICLEQUADS_H
struct FixedPointMatrix;
struct Shared_Particle;
struct RibbonWorld;
void Fx_AddActorRibbonSamples(struct RibbonWorld *ribbonWorld, s32 actor, char *boneMatrices);
struct ParticleActorListView;
struct RibbonWorld;
s32 Fx_AllocateRibbonSegment(struct RibbonWorld *ribbonWorld, s32 ribbon);
struct ParticleRibbonLifetimeView;
struct FloatStateB0;
#include "Common/effectcontribution.h"
void Fx_DrawBoundedParticleQuads(struct RibbonWorld *scene, char *view);

struct RibbonActor;
struct RibbonSegment;
void Fx_FreeRibbonSegment(s32 ribbonWorld, struct RibbonActor *ribbon, struct RibbonSegment *actors);

extern void Fx_AddParticleRibbonSamples(struct RibbonWorld *ribbonWorld, struct Shared_Particle *particle, struct FixedPointMatrix *packedMatrixWords);
#endif
