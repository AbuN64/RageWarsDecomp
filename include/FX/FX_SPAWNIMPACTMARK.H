#ifndef FX_FX_SPAWNIMPACTMARK_H
#define FX_FX_SPAWNIMPACTMARK_H
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/OBJRECAT18V6.H"
#include "COMMON/EFFECTCONTRIBUTION.H"
#include "SYSTEM/TIMED_EFFECT_AND_ITEM_MENU_VIEWS.H"
extern void Fx_AccumulateEffectComponents(EffectColorContribution *);
extern void Fx_ClampScalarRange(f32 *);
extern void Fx_AddTimedCallback(s32, s32, s32, s32, f32);
extern void Fx_ResolveEntryResource(void *unused, void *, void *);
extern void Fx_UpdateChildTransform(Node44 *, void *);
extern void Fx_UpdateNodeFractions(void *);
extern void Fx_DrawEffectGeometry(s32 pool, void *, s32 camera);
extern void Fx_AppendAttachedTransform(void *, void *, void *, s32);
extern void *Fx_FindAttachedEffect(RibbonWorld *, s32, s32);
extern void Fx_DrawEffectPasses(void *pool, void *camera);
struct AttachedEffectDetachState;
void Fx_DetachEffectObject(struct AttachedEffectDetachState *state);
struct ParticleQuadPoolScene;
struct CVector3_t;
struct Particle *Fx_SpawnImpactMark(struct ParticleQuadPoolScene *scene, struct CVector3_t position, struct CVector3_t normal, s32 surface, s32 owner);
struct RibbonWorld;
void Fx_UpdateAttachedEffects(struct RibbonWorld *owner);
void Fx_UpdateTimedCallbacks(void *owner);
#endif
