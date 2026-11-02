#include "COMMON/MODEL_RENDER.H"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "RENDER/MATERIAL_COLOR_AND_FOG_VIEWS.H"
#include <PR/gbi.h>
#include "TYPES.H"
#include "ENGINE/GEOMETRY.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "COMMON/DISPLAY.H"
#include "COMMON/INTEGERSTATEB0.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include <PR/abi.h>
#include "COMMON/MEASUREDRECAT0V1.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/OBJRECAT4V7.H"
#include "SCENE/CACHE_ALLOCATERESOURCEAT.H"
#include "include_asm.h"
#include <ultra64.h>

/* 8026AC38_5.CPP */
/* Draws the parts of a model resource tinted by an RGBA colour through the shared material g_tintedModelSharedMaterial: sets the tint mode g_menuModelFillEnabled to 3, clears the material's fog colour and sets its flags, records the colour as floats and its alpha on the material, advances the pass modulo 18, and when the frame's command buffer still has 3000 commands free and Geometry_SetupMaterial accepts the material sets the render mode, selects blend 1, registers the resource, loads the matrix (or sets it as segment 1), sets segment 2 to the given texture base or the model's own, sets the lighting on the first part and emits each part whose material blend bits are all set and accepted for the pass, clearing the tint mode afterwards. Adapted from Geometry_DrawBlendParts with the tint setup, the render mode and blend commands and the trailing clear added. */

extern Gfx *g_displayListCursor;
#if defined(VERSION_DE)
extern u32 g_displayListCapacityDe;
#elif defined(VERSION_EU)
extern u32 g_displayListCapacityEu;
#elif defined(VERSION_EU_X)
extern u32 g_displayListCapacityEuX;
#elif defined(VERSION_US)
extern u32 g_displayListCapacityUs;
#elif defined(VERSION_US_REV1)
extern u32 g_displayListCapacityUsRev1;
#endif
extern SharedModelTintMaterial g_tintedModelSharedMaterial;

extern s32 Geometry_ApplyMaterialLighting(void *matrix, void *lights, void *material);
struct Shared_GfxMaterial; extern s32 Geometry_SetupMaterial(struct Shared_GfxMaterial *mat, s32 pass);
extern void Geometry_SetCombineMode(u32 mode);

struct CacheResourceBlockView; extern void Geometry_ExpandModelCommands(s32 unused, struct CacheResourceBlockView **res, s32 extra, s32 sentinel);

/* Geometry_InitializeModelRenderState_GeometryDrawblendparts.CPP */
extern void Graphu64_BuildScaleMatrix(void *, float, float, float);

extern void GraphU64_PackFixedMatrix(void *, void *);

extern struct NodeGeometryGroupModelInstances *g_opaqueMaterialGroupTree;

extern struct NodeGeometryGroupModelInstances *g_opaqueMaterialGroupList;

extern struct NodeGeometryGroupModelInstances *g_translucentMaterialGroupTree;

extern struct NodeGeometryGroupModelInstances *g_translucentMaterialGroupList;

extern s32 **g_modelBatchResource;

extern QueuedModelInstance g_modelInstanceQueue[];

struct CacheResourceNode; extern void Cache_LockResource(void *,struct CacheResourceNode *);

extern void Geometry_QueueModelById(s32 modelIndex, void *matrix, void *lights, s32 textures, s32 pass, s32 direct);

extern s32 Geometry_SetModePreset(s32 mode);

extern void **Textload_RequestTextureVariationSync(s32 *resource, s32 variation);

/* 8026AC38_6.CPP */


/* 8026E1F8.CPP */
extern void Cache_TouchResourceByKey(s32 cache, s32 resourceKey);
#if defined(VERSION_DE)

const float g_geometryMaterialSetupConstantsDe[3] = {
    15.0f, 5.0f, 256.0f,
};
#endif
