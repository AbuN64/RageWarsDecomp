#ifndef ENGINE_GEOMETRY_H
#define ENGINE_GEOMETRY_H
extern int g_geometryAntialiasingEnabled;
extern int g_geometryTranslucentRenderMode;
extern int g_geometryOpaqueRenderMode;
#include "Ai/ai_shared_symbols.h"
#include "Common/ballisticparams.h"
#include <PR/gbi.h>
#include "Common/rendercounters.h"
#include "Common/runtime_declarations.h"
#include "types.h"
#include "Common/geometry_blend_and_instance_views.h"

struct QueuedModelInstance;
struct SharedModelTintMaterial;
extern u32 g_geometryEffectGeometryMode;

extern void Geometry_AlternateNoOperation(void);

extern void Geometry_DrawMaterialGroups(void);

extern void Geometry_GroupModelInstances(void);

struct TreeNode {
    unsigned int key;
    unsigned char padding[12];
    struct TreeNode *link10;
    struct TreeNode *link14;
    struct TreeNode *link18;
    struct TreeNode *link1c;
};
typedef struct { s32 flagWord; char pad4[2]; u8 flags; } ModelMaterial;
extern s32 Geometry_ApplyMaterialLighting(void *model, void *lights, ModelMaterial *material);
extern void Geometry_QueueModelById(s32 modelIndex, void *matrix, void *lights, s32 textures, s32 pass, s32 direct);
extern const char s_simpObjectIndexText[18];
extern const char s_simpModelsIndexText[18];
extern const char s_simpModelText[11];
extern void Geometry_DrawIntensityMask(void *matrix, s32 pass, u32 alpha);
extern void Geometry_QueueModelInstance(void **a, void *b, s32 c, void *d, void *e, s32 f);
extern char g_applyDirectDamageAddress[];
extern char g_Events_ApplyDirectDamagePackedAddress_us_rev1[];
extern char addrLow_Events_ApplyFlag100RadialDamage_eu[];
extern char addrLow_Events_ApplyFlag100RadialKnockback_eu[];
extern char addrLow_Events_ApplyFlag200RadialDamage_eu[];
extern char addrLow_Events_ApplyFlag200RadialKnockback_eu[];
extern char addrLow_Events_ApplyFlag400RadialDamage_eu[];
extern char addrLow_Events_ApplyFlag400RadialKnockback_eu[];
extern char g_applyRadialDamageWithKnockbackAddress[];
extern char g_Events_ApplyRadialDamageWithKnockbackPackedAddress_us_rev1[];
extern char addrLow_Events_ApplyDirectDamage_us_rev1[];
extern char addrLow_Events_ApplyRadialDamageWithKnockback_us_rev1[];
extern char g_consumeEventArgumentAddress[];
extern char g_deactivateActorAddress[];
extern char g_fireWithinHeightRangeAddress[];
extern char g_ignoreEventAddress[];
extern char g_incrementNearbyPlayerCounterAddress[];
extern char g_playClipEventAddress[];
extern char g_playTeamClipAddress[];
extern char g_playTeamEffectAddress[];
extern char g_postGameplayMessageAddress[];
extern char g_preserveEventArgumentAddress[];
extern char g_requestActorPositionAddress[];
extern char g_runNextNodeOperationAddress[];
extern char g_setActorEffectModeAddress[];
extern char g_setActorEventBitAddress[];
extern char g_setActorLoopingSoundAddress[];
extern char g_Events_SetActorLoopingSoundPackedAddress_us_rev1[];
extern char addrLow_Events_SetActorLoopingSound_us_rev1[];
extern char g_spawnActorEffectAddress[];
extern char g_spawnAttachedEffectAddress[];
extern char g_spawnFilteredActorEffectAddress[];
extern char g_spawnPositionedEffectAddress[];
extern char g_startActorEmitterAddress[];
extern char g_startDisabledCameraEmitterAddress[];
extern char g_startEnabledCameraEmitterAddress[];
extern char g_geometryMaterialIntensityTexture;
extern const f32 g_geometryOpaqueTintAlpha;
extern s32 **g_modelBatchResource;
extern s32 g_geometryViewEffect;
extern signed char g_geometryMaterialLightDirection[3];
extern u32 g_primaryDisplayListCapacity;
extern u32 g_geometryEffectGeometryMode;
extern f32 g_geometryDefaultTintAlpha;
extern f32 g_geometryDefaultTintColor;
extern CGameStatus g_matchRoundCounters;
extern struct QueuedModelInstance g_modelInstanceQueue[];
extern struct SharedModelTintMaterial g_tintedModelSharedMaterial;
extern struct NodeGeometryGroupModelInstances *g_opaqueMaterialGroupList;
extern struct NodeGeometryGroupModelInstances *g_opaqueMaterialGroupTree;
extern struct NodeGeometryGroupModelInstances *g_translucentMaterialGroupList;
extern struct NodeGeometryGroupModelInstances *g_translucentMaterialGroupTree;
extern Gfx g_geometryDefaultMaterialDisplayList[], g_geometryAlternateMaterialDisplayList[];
struct Shared_GfxMaterial; extern s32 Geometry_SetupMaterial(struct Shared_GfxMaterial *mat, s32 pass);
struct CacheResourceNode; extern void Geometry_ExpandModelCommands(s32 cacheContext, struct CacheResourceNode **res, s32 extra, s32 sentinel);
#endif

/* Absolute packed callback words supplied by the regional linker aliases. */
extern char addrLow_Events_ApplyDirectDamage_us_rev1[];
extern char addrLow_Events_ApplyFlag100RadialDamage[];
extern char addrLow_Events_ApplyFlag100RadialKnockback[];
extern char addrLow_Events_ApplyFlag200RadialDamage[];
extern char addrLow_Events_ApplyFlag200RadialKnockback[];
extern char addrLow_Events_ApplyFlag400RadialDamage[];
extern char addrLow_Events_ApplyFlag400RadialKnockback[];
extern char addrLow_Events_ApplyRadialDamage[];
extern char addrLow_Events_ApplyRadialDamageWithKnockback_us_rev1[];
extern char addrLow_Events_ClearActorEventBit[];
extern char addrLow_Events_ConsumeEventArgument[];
extern char addrLow_Events_DeactivateActor[];
extern char addrLow_Events_FireWithinHeightRange[];
extern char addrLow_Events_IgnoreEvent[];
extern char addrLow_Events_IncrementNearbyPlayerCounter[];
extern char addrLow_Events_PlayClipEvent[];
extern char addrLow_Events_PlayTeamClip[];
extern char addrLow_Events_PlayTeamEffect[];
extern char addrLow_Events_PostGameplayMessage[];
extern char addrLow_Events_PreserveEventArgument[];
extern char addrLow_Events_RequestActorPosition[];
extern char addrLow_Events_RunFirstNodeOperation[];
extern char addrLow_Events_RunSecondNodeOperation_us_rev1[];
extern char addrLow_Events_SetActorEffectMode[];
extern char addrLow_Events_SetActorEventBit[];
extern char addrLow_Events_SetActorLoopingSound_us_rev1[];
extern char addrLow_Events_SpawnActorEffect[];
extern char addrLow_Events_SpawnAttachedEffect[];
extern char addrLow_Events_SpawnFilteredActorEffect[];
extern char addrLow_Events_SpawnPositionedEffect[];
extern char addrLow_Events_StartActorEmitter[];
extern char addrLow_Events_StartCameraFadeAtPoint[];
extern char addrLow_Events_StartDisabledCameraEmitter[];
extern char addrLow_Events_StartEnabledCameraEmitter[];
extern char addrLow_Events_StopActorLoopingSound[];
extern char addrLow_Events_StopClipEvent[];
