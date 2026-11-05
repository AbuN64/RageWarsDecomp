#ifndef FX_FX_SPAWNIMPACTMARK_H
#define FX_FX_SPAWNIMPACTMARK_H
#include "Common/vector4f.h"
#include "Common/hud_effects.h"
#include "Common/effectcontribution.h"
#include "System/timed_effect_and_item_menu_views.h"
struct RibbonWorld;
struct EffectColorContribution;
struct RibbonActor;
extern void Fx_AccumulateEffectComponents(struct EffectColorContribution *);
extern void Fx_ClampScalarRange(f32 *);
extern void Fx_AddTimedCallback(s32, s32, s32, s32, f32);
extern void Fx_ResolveEntryResource(void *callbackContext, void *, void *);
extern void Fx_UpdateChildTransform(struct RibbonActor *, void *);
extern void Fx_UpdateNodeFractions(void *);
extern void Fx_DrawEffectGeometry(s32 pool, void *, s32 camera);
extern void Fx_AppendAttachedTransform(void *, void *, void *, s32);
extern void *Fx_FindAttachedEffect(struct RibbonWorld *, s32, s32);
extern void Fx_DrawEffectPasses(void *pool, void *camera);
struct AttachedEffectDetachState;
void Fx_DetachEffectObject(struct RibbonActor *state);
struct RibbonWorld;
struct CVector3_t;
struct ProjectedMark;
struct RibbonWorld;
struct ProjectedMark *Fx_SpawnImpactMark(struct RibbonWorld *scene, CVector3 position, CVector3 normal, s32 surface, s32 owner);
struct RibbonWorld;
void Fx_UpdateAttachedEffects(struct RibbonWorld *owner);
void Fx_UpdateTimedCallbacks(void *owner);
extern void Fx_RecycleOwnerParticles(struct RibbonWorld *particlePool, s32 ownerId);

#endif
