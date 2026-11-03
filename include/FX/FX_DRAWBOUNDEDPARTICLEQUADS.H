#ifndef FX_FX_DRAWBOUNDEDPARTICLEQUADS_H
#define FX_FX_DRAWBOUNDEDPARTICLEQUADS_H
struct RibbonWorld;
void Fx_AddActorRibbonSamples(struct RibbonWorld *ribbonWorld, s32 actor, char *boneMatrices);
struct ParticleActorListView;
s32 Fx_AllocateRibbonSegment(struct ParticleActorListView *ribbonWorld, s32 ribbon);
struct ParticleRibbonLifetimeView;
struct FloatStateB0;
void Fx_FreeRibbonSegment(s32 ribbonWorld, struct ParticleRibbonLifetimeView *ribbon, struct FloatStateB0 *actors);
#endif
