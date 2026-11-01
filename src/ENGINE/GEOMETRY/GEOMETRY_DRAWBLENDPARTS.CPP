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
extern s32 Geometry_SetupMaterial(void *material, s32 pass);
extern void Geometry_SetCombineMode(u32 mode);

void Geometry_DrawTintedModelParts(void **resource, void *unused, void *matrix, s32 segment, void *lights, void *textures, s32 pass, u8 r, u8 g, u8 b, u8 a) {
    void *header;
    void *base;
    void **parts;
    void *part;
    void *material;
    s32 count;
    s32 i;
    SharedModelTintMaterial *shared;
    f32 *tint;

    shared = &g_tintedModelSharedMaterial;
    g_menuModelFillEnabled = 3;
    shared->fog[0] = 0;
    shared->fog[1] = 0;
    shared->fog[2] = 0;
    shared->flags |= 0x1402;
    tint = g_menuModelFillColor;
    tint[0] = r;
    tint[1] = g;
    tint[2] = b;
    tint[3] = a;
    shared->fog[3] = a;
    pass = (pass + 1) % 18;
#if defined(VERSION_DE)
    if (g_displayListCapacityDe - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
#elif defined(VERSION_EU)
    if (g_displayListCapacityEu - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
#elif defined(VERSION_EU_X)
    if (g_displayListCapacityEuX - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
#elif defined(VERSION_US)
    if (g_displayListCapacityUs - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
#elif defined(VERSION_US_REV1)
    if (g_displayListCapacityUsRev1 - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
#endif
        return;
    }
    if (Geometry_SetupMaterial(shared, pass) != 0) {
        gDPSetRenderMode(g_displayListCursor++, 0x0C184DD8, 0);
        Geometry_SetCombineMode(1);
        header = *resource;
        Cache_MarkResourceInUse(0, resource);
        if (segment != 0) gSPSegment(g_displayListCursor++, 1, matrix) else gSPMatrix(g_displayListCursor++, matrix, G_MTX_LOAD);
        base = textures;
        if (base == 0) {
            base = SetN64_GetPackSection(header, 0);
        }
        gSPSegment(g_displayListCursor++, 2, (unsigned int)base);
        parts = SetN64_GetPackSection(header, 2);
        count = *(s32 *)parts;
        for (i = 0; i < count; i++) {
            part = SetN64_GetPackSection(parts, i);
            material = SetN64_GetPackSection(part, 0);
            if (i == 0) {
                Geometry_ApplyMaterialLighting(matrix, lights, material);
            }
            if ((((unsigned char *)material)[6] & 0x38) == 0x38 && Geometry_SetupMaterial(material, pass) != 0) {
                Gfx *cmd;
                void *list = SetN64_GetPackSection(part, 1);

                cmd = g_displayListCursor++;
                gSPDisplayList(cmd, (unsigned int)list);
            }
        }
    }
    g_menuModelFillEnabled = 0;
}

extern void Geometry_ExpandModelCommands(s32 unused, s32 res, s32 extra, s32 sentinel);

void Geometry_ExpandBasicModel(s32 unused, s32 modelResource) {
    Geometry_ExpandModelCommands(unused, modelResource, 0, 0);
}

void Geometry_ExpandModelWithSentinel(s32 unused, s32 modelResource) {
    Geometry_ExpandModelCommands(unused, modelResource, 0, 1);
}

void Geometry_ExpandExtendedModel(s32 unused, s32 modelResource) {
    Geometry_ExpandModelCommands(unused, modelResource, 1, 0);
}

void Geometry_AlternateNoOperation(void) {
}
/* An empty function. */
void Geometry_NoOperation(void) {
}

/* Geometry_InitializeModelRenderState_GeometryDrawblendparts.CPP */
extern void Graphu64_BuildScaleMatrix(void *, float, float, float);

extern void GraphU64_PackFixedMatrix(void *, void *);

extern s32 g_opaqueMaterialGroupTree;

extern s32 g_opaqueMaterialGroupList;

extern s32 g_translucentMaterialGroupTree;

extern s32 g_translucentMaterialGroupList;

extern s32 g_modelBatchResource;

extern QueuedModelInstance g_modelInstanceQueue[];

extern void Cache_LockResource(s32, s32);

extern void Geometry_QueueModelById(s32 modelIndex, void *matrix, void *lights, s32 textures, s32 pass, s32 direct);

extern s32 Geometry_SetModePreset(s32 mode);

extern void **Textload_RequestTextureVariationSync(void *resource, s32 variation);

void Geometry_InitializeModelRenderState(void) {
    char local[64];

    Geometry_InvalidateMaterialKeys();
    Graphu64_BuildScaleMatrix(local, g_geometryInitialScale, g_geometryInitialScale, g_geometryInitialScale);
    GraphU64_PackFixedMatrix(local, &g_geometryInitialScaleMatrix);
}

void Geometry_SelectEffectModes(void) {
    if (g_geometryFogEffectEnabled != 0 || g_geometryViewEffect != 0) {
        g_geometryEffectGeometryMode = 0x10000;
        g_geometryOpaqueRenderMode = 0xC4000000;
        g_geometryTranslucentRenderMode = 0xC8000000;
        return;
    }
    g_geometryEffectGeometryMode = 0;
    g_geometryOpaqueRenderMode = 0x0C080000;
    g_geometryTranslucentRenderMode = 0x0C080000;
}

/** Reset two global indices to minus one. */
void Geometry_InvalidateMaterialKeys(void) {
    g_geometryPreviousCombineMode = -1;
    g_geometryPreviousModePreset = -1;
}

void Geometry_SetColorDither(s32 ditherMode) {
    if (g_geometryViewEffect == 0) gDPSetColorDither(g_displayListCursor++, ditherMode) else gDPSetColorDither(g_displayListCursor++, G_CD_NOISE);
}

void Geometry_BeginModelBatch(void) {
    g_modelBatchResource = 0;
    g_modelInstanceQueueCount = 0;
    g_materialGroupCount = 0;
    g_materialInstanceCount = 0;
    g_modelBatchResourceCount = 0;
    g_opaqueMaterialGroupList = 0;
    g_opaqueMaterialGroupTree = 0;
    g_translucentMaterialGroupList = 0;
    g_translucentMaterialGroupTree = 0;
}

void Geometry_FlushModelBatch(void) {
    s32 resourceHandle;
    s32 i;

    Geometry_GroupModelInstances();
    i = 0;
    Geometry_DrawMaterialGroups();
    if (g_modelBatchResourceCount > 0) {
        do {
            resourceHandle = g_modelBatchResources[i];
            Cache_MarkResourceInUse(0, resourceHandle);
            Cache_UnlockResource(0, resourceHandle);
            i += 1;
        } while (i < g_modelBatchResourceCount);
    }
}

void Geometry_DrawModelResource(void **resource, void *matrix, s32 segment, void *lights, void *textures, s32 pass) {
    void *header;
    void *base;
    void **parts;
    void *part;
    void *material;
    s32 count;
    s32 i;

    if (g_displayListCapacityUsRev1 - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
        return;
    }
    header = *resource;
    Cache_MarkResourceInUse(0, resource);
    if (segment != 0) { gSPSegment(g_displayListCursor++, 1, matrix); } else { gSPMatrix(g_displayListCursor++, matrix, G_MTX_LOAD); }
    base = textures;
    if (base == 0) {
        base = SetN64_GetPackSection(header, 0);
    }
    gSPSegment(g_displayListCursor++, 2, (unsigned int)base);
    parts = SetN64_GetPackSection(header, 2);
    count = *(s32 *)parts;
    for (i = 0; i < count; i++) {
        part = SetN64_GetPackSection(parts, i);
        material = SetN64_GetPackSection(part, 0);
        if (i == 0) {
            Geometry_ApplyMaterialLighting(matrix, lights, material);
        }
        if (Geometry_SetupMaterial(material, pass) != 0) {
            Gfx *cmd;
            void *list = SetN64_GetPackSection(part, 1);

            cmd = g_displayListCursor++;
            gSPDisplayList(cmd, (unsigned int)list);
        }
    }
}

void Geometry_QueueModelInstance(void **a, void *b, s32 c, void *d, void *e, s32 f) {
    s32 instanceCount;
    void *vertexBase;
    QueuedModelInstance *queuedInstance;
    void *modelHeader;
    s32 *countp;
    s32 count;
    s32 *queue_countp;

    modelHeader = *a;
    vertexBase = e;
    if (vertexBase == 0) {
        vertexBase = SetN64_GetPackSection(modelHeader, 0);
    }
    if ((g_modelBatchResource != (s32)a) || (g_modelBatchPass != f) || (g_modelInstanceQueueCount == 32)) {
        Geometry_GroupModelInstances();
        if (g_modelBatchResourceCount != 256) {
            Cache_LockResource(0, (s32)a);
            countp = &g_modelBatchResourceCount;
            count = *countp;
            g_modelBatchResources[count] = (s32)a;
            *countp = count + 1;
            goto block_7;
        }
    } else {
block_7:
        g_modelBatchResource = (s32)a;
        g_modelBatchPass = f;
        queue_countp = &g_modelInstanceQueueCount;
        instanceCount = *queue_countp;
        queuedInstance = &g_modelInstanceQueue[instanceCount];
        instanceCount += 1;
        *queue_countp = instanceCount;
        queuedInstance->matrix = b;
        queuedInstance->segmented = c;
        queuedInstance->lights = d;
        queuedInstance->vertices = vertexBase;
    }
}

void Geometry_DrawBlendParts(void **resource, s32 unused, s32 matrix, s32 segment, s32 lights, void *textures, s32 pass) {
    void *header;
    void *base;
    void **parts;
    void *part;
    void *material;
    s32 count;
    s32 i;

    if (g_displayListCapacityUsRev1 - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
        return;
    }
    header = *resource;
    Cache_MarkResourceInUse(0, resource);
    if (segment != 0) { gSPSegment(g_displayListCursor++, 1, matrix); } else { gSPMatrix(g_displayListCursor++, matrix, G_MTX_LOAD); }
    base = textures;
    if (base == 0) {
        base = SetN64_GetPackSection(header, 0);
    }
    gSPSegment(g_displayListCursor++, 2, (unsigned int)base);
    parts = SetN64_GetPackSection(header, 2);
    count = *(s32 *)parts;
    for (i = 0; i < count; i++) {
        part = SetN64_GetPackSection(parts, i);
        material = SetN64_GetPackSection(part, 0);
        if (i == 0) {
            Geometry_ApplyMaterialLighting(matrix, lights, material);
        }
        if ((((unsigned char *)material)[6] & 0x38) == 0x38 && Geometry_SetupMaterial(material, pass) != 0) {
            Gfx *cmd;
            void *list = SetN64_GetPackSection(part, 1);

            cmd = g_displayListCursor++;
            gSPDisplayList(cmd, (unsigned int)list);
        }
    }
}

void Geometry_QueueDirectModel(s32 model, void *matrix, void *lights, s32 textures, s32 pass) {
    Geometry_QueueModelById(model, matrix, lights, textures, pass, 1);
}

void Geometry_QueueDeferredModel(s32 modelIndex, void *matrix, void *lights, s32 textures, s32 pass) {
    Geometry_QueueModelById(modelIndex, matrix, lights, textures, pass, 0);
}

void Geometry_DrawWithMaterialOverride(void *shared, s32 mode, void **resource, s32 matrix, s32 segment, s32 lights, void *textures, s32 pass) {
    void *header;
    void *base;
    void **parts;
    void *part;
    void *material;
    s32 count;
    s32 i;

    if (g_displayListCapacityUsRev1 - ((u32)g_displayListCursor - (u32)g_gameSession.ring.current->commands) / sizeof(Gfx) < 3000) {
        return;
    }
    if (Geometry_SetupMaterial(shared, pass) == 0) {
        return;
    }
    if (segment != 0) { gSPSegment(g_displayListCursor++, 1, matrix); } else { gSPMatrix(g_displayListCursor++, matrix, G_MTX_LOAD); }
    if (mode != -1) {
        Geometry_SetModePreset(mode);
    }
    Cache_MarkResourceInUse(0, resource);
    header = *resource;
    base = textures;
    if (base == 0) {
        base = SetN64_GetPackSection(header, 0);
    }
    gSPSegment(g_displayListCursor++, 2, (unsigned int)base);
    parts = SetN64_GetPackSection(header, 2);
    count = *(s32 *)parts;
    for (i = 0; i < count; i++) {
        part = SetN64_GetPackSection(parts, i);
        material = SetN64_GetPackSection(part, 0);
        if (i == 0) {
            Geometry_ApplyMaterialLighting(matrix, lights, material);
        }
        {
            Gfx *cmd;
            void *list = SetN64_GetPackSection(part, 1);

            cmd = g_displayListCursor++;
            gSPDisplayList(cmd, (unsigned int)list);
        }
    }
}

void Geometry_UnlockMaterialResources(void **modelResource) {
    void *packSectionResult;
    s32 count;
    s32 i;
    void *rec;
    s32 result;

    packSectionResult = SetN64_GetPackSection(*modelResource, 2);
    count = *(s32 *)packSectionResult;
    for (i = 0; i < count; i++) {
        rec = SetN64_GetPackSection(SetN64_GetPackSection(packSectionResult, i), 0);
        if (((ResourceSectionReference *)rec)->resource == 0) {
            continue;
        }
        result = Textload_RequestTextureVariationSync(&((ResourceSectionReference *)rec)->resource, -1);
        if (result == 0) {
            continue;
        }
        Cache_UnlockResource(0, result);
    }
}

/* 8026AC38_6.CPP */


/* 8026E1F8.CPP */
extern void Cache_TouchResourceByKey(s32 cache, s32 resourceKey);

void Geometry_RefreshMaterialResources(void **resource) {
    void *packSectionResult;
    s32 count;
    s32 i;
    void *rec;

    packSectionResult = SetN64_GetPackSection(*resource, 2);
    count = *(s32 *)packSectionResult;
    for (i = 0; i < count; i++) {
        rec = SetN64_GetPackSection(SetN64_GetPackSection(packSectionResult, i), 0);
        if (((struct ResourceSectionReference *)(rec))->resource == 0) {
            continue;
        }
        Cache_TouchResourceByKey(0, ((struct ResourceSectionReference *)(rec))->resource);
    }
}

s32 *Geometry_CollectMaterialResources(void **modelResource, s32 variation, s32 *resourcesOut) {
    void *packSectionResult;
    s32 count;
    s32 i;
    s32 *out;
    void *rec;
    s32 result;

    out = resourcesOut;
    packSectionResult = SetN64_GetPackSection(*modelResource, 2);
    count = *(s32 *)packSectionResult;
    for (i = 0; i < count; i++) {
        rec = SetN64_GetPackSection(SetN64_GetPackSection(packSectionResult, i), 0);
        if (((struct ResourceSectionReference *)(rec))->resource == 0) {
            continue;
        }
        result = Textload_RequestTextureVariationSync(&((struct ResourceSectionReference *)(rec))->resource, variation);
        if (result != 0) {
            *out = result;
            out += 1;
        }
    }
    return out;
}

void Geometry_SetViewEffect(int viewEffect) {
    g_geometryViewEffect = viewEffect;
}

/** Return the global word at g_geometryViewEffect. */

int Geometry_GetViewEffect(void) {
    return g_geometryViewEffect;
}

/** Store four bytes in the global color-like value. */

void Geometry_SetPrimitiveColorOverride(unsigned char first, unsigned char second,
                   unsigned char third, unsigned char fourth) {
    g_primitiveColorOverrideEnabled = first;
    g_primitiveColorOverrideRed = second;
    g_primitiveColorOverrideGreen = fourth;
    g_primitiveColorOverrideBlue = third;
}

void Geometry_SetPrimitiveAlphaOverride(int enabled, int alpha) {
    g_primitiveAlphaOverrideEnabled = (unsigned char)enabled;
    g_primitiveAlphaOverride = (unsigned char)alpha;
}

void Geometry_LoadRenderMicrocode(void) {
    Gfx *cmd;

    cmd = g_displayListCursor++;
    gDPFullSync(cmd);
    gSPLoadUcodeEx(g_displayListCursor++, &g_primaryRenderMicrocodeText, &g_primaryRenderMicrocodeData, 0x800);
    cmd = g_displayListCursor++;
    gSPDisplayList(cmd, (u32) &g_cameraViewDisplayListFirst);
    cmd = g_displayListCursor++;
    gSPDisplayList(cmd, (u32) &g_cameraViewDisplayListSecond_de);
}

void Geometry_SwitchRenderMicrocode(void) {
    Gfx *cmd;

    cmd = g_displayListCursor++;
    gDPFullSync(cmd);
    gSPLoadUcodeEx(g_displayListCursor++, &g_alternateRenderMicrocodeText, &g_alternateRenderMicrocodeData, 0x800);
    cmd = g_displayListCursor++;
    gSPDisplayList(cmd, (u32) &g_cameraViewDisplayListFirst);
    cmd = g_displayListCursor++;
    gSPDisplayList(cmd, (u32) &g_cameraViewDisplayListSecond_de);
}

/** Initialize the two-word state to minus one and zero. */
void Geometry_ResetDisplayListState(int *state) {
    state[0] = -1;
    state[1] = 0;
}


/** Clear four related global state words. */
void Geometry_ClearMaterialGroups(void) {
    g_opaqueMaterialGroupList = 0;
    g_opaqueMaterialGroupTree = 0;
    g_translucentMaterialGroupList = 0;
    g_translucentMaterialGroupTree = 0;
}

void *Geometry_FindMaterialNodeOrParent(MaterialTreeNode **root, u32 materialKey)
{
  u32 nodeKey;
  MaterialTreeNode *parent;
  MaterialTreeNode *node;
  node = *root;
  parent = 0;
  if (node != 0)
  {
    loop_1:
    nodeKey = node->key;

    if (node->key)
    {
      parent = node;
    }
    else
    {
      parent = node;
    }
    if (nodeKey != materialKey)
    {
      if (materialKey < nodeKey)
      {
        node = parent->left;
      }
      else
      {
        node = parent->right;
      }
      if (node == 0)
      {
        goto block_6;
      }
      goto loop_1;
    }
  }
  else
  {
    block_6:
    node = parent;

  }
  return node;
}

/** Insert a node adjacent to the supplied node in an intrusive ordered tree. */
void Geometry_InsertMaterialNode(TreeNode **root, TreeNode **empty_root, TreeNode *node, TreeNode *current) {
    if (current != 0) {
        if (node->key < current->key) {
            current->link18 = node;
            node->link1c = 0;
            node->link18 = 0;
            node->link14 = current;
            node->link10 = current->link10;
            if (current->link10 != 0)
                current->link10->link14 = node;
            current->link10 = node;
            if (*root == current)
                *root = node;
        } else {
            current->link1c = node;
            node->link1c = 0;
            node->link18 = 0;
            node->link14 = current->link14;
            if (current->link14 != 0)
                current->link14->link10 = node;
            node->link10 = current;
            current->link14 = node;
        }
    } else {
        *empty_root = node;
        *root = node;
        node->link1c = 0;
        node->link18 = 0;
        node->link14 = 0;
        node->link10 = 0;
    }
}


/* 800C979C.CPP */
#if !(defined(VERSION_US_REV1))
const float g_geometryInitialModelScale[1] = {
    2.0f,
};
#endif

#if defined(VERSION_DE)
const float g_geometryMaterialSetupConstantsDe[3] = {
    15.0f, 5.0f, 256.0f,
};
#endif


#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_geometryInitialModelScaleUsRev1_GeometryDrawblendparts.c */
const float g_geometryInitialModelScaleUsRev1[1] = {
    2.0f,
};
#endif
