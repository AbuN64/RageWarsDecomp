#ifndef FX_FX_DRAWCOLOREDRIBBON_H
#define FX_FX_DRAWCOLOREDRIBBON_H
struct EffectWorld;
struct FxActor;
void Fx_AttachActorRibbon(struct EffectWorld *world, struct FxActor *actor, s32 resourceId);
struct Root752C;
struct Entity1DC;
void Fx_DetachParticleSwooshes(struct Root752C *effectWorld, struct Entity1DC *detachedEntity);
struct VertexArena;
struct RibbonActor;
struct GameplayCamera;
void Fx_DrawColoredRibbon(struct VertexArena *pool, struct RibbonActor *actor, struct GameplayCamera *camera);
void Fx_DrawLinkedGeometry(struct VertexArena *pool, struct GameplayCamera *camera);
#endif
