#ifndef FX_FX_DRAWCOLOREDRIBBON_H
#define FX_FX_DRAWCOLOREDRIBBON_H
struct EffectWorld;
struct FxActor;
struct RibbonWorld;
struct Shared_Particle;
void Fx_AttachActorRibbon(struct RibbonWorld *world, struct Shared_Particle *actor, s32 resourceId);
struct Root752C;
struct Entity1DC;
struct RibbonWorld;
void Fx_DetachParticleSwooshes(struct RibbonWorld *effectWorld, void *detachedEntity);
struct RibbonWorld;
struct RibbonActor;
struct GameplayCamera;
void Fx_DrawColoredRibbon(struct RibbonWorld *pool, struct RibbonActor *actor, struct GameplayCamera *camera);
void Fx_DrawLinkedGeometry(struct RibbonWorld *pool, struct GameplayCamera *camera);
#endif
