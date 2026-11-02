#include "RSP/RANDOM_DIRECTION_AND_AFFINE_MATH.H"
#include "COMMON/EFFECTCONTRIBUTION.H"
#include "COMMON/GAME_SESSION.H"
#include "RENDER/ANIMATION_FRAME_AND_RIBBON_VIEWS.H"
#include <PR/abi.h>
#include "FX.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include <PR/gbi.h>
#include "COMMON/S1.H"
#include "COMMON/GEOMETRY_BLEND_AND_INSTANCE_VIEWS.H"
#include "COMMON/SHARED_PARTICLEINSTANCE.H"
#include "COMMON/FRUSTUM.H"
#include "COMMON/OBJRECAT18V6.H"
#include "TYPES.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "SYSTEM/TEXTLOAD_RESETTEXTURECACHE.H"
#include "ENGINE/LISTS.H"
#include "ENGINE/CACHE/LIST.H"


extern void Graphu64_CrossVectors(CVector3 *out, CVector3 *a, CVector3 *b);


extern void Graphu64_ScaleVector(CVector3 *out, CVector3 *in, f32 scale);

/* Draws the scene's ten particle lists unless the free list holds exactly 100 particles: sets the render state and the shared particle texture g_materialIntensityMaskTexture (a 16x16 texture drawn in grey at alpha 200 through g_particleQuadRenderSetup), then for every particle inside the view box ending at g_cameraVolumeBoundsMinZ + 4 loads its matrix and draws the shared quad g_particleQuadVertices, while particles outside it are unlinked (List_RemoveIntrusive) and returned to the free list (List_AppendIntrusive); finally restores the render state through Geometry_InvalidateMaterialKeys and TextLoad_ResetTextureCache. */











extern f32 g_cameraVolumeBoundsMinZ;

extern unsigned char g_materialIntensityMaskTexture[];

extern char g_particleQuadRenderSetup;




extern char g_particleQuadRenderRestoreList;

void Fx_UpdateAttachedEffects(void *);

s32 Fx_UpdateTimedCallbacks(s32);

extern s32 g_particleQuadDisplayListState;


extern s32 g_lightingBufferIndex;

extern void CopyMatrix(f32 *destinationMatrix, f32 *sourceMatrix);

extern void ScaleMatrixLocal(void *matrix, f32 sx, f32 sy, f32 sz);

extern void Graphu64_ClampMatrixToFixedRange(f32 *matrixComponents);

extern void Linked_AppendRibbonSegment(void *effectSystem, void *ribbon, f32 *local);

extern void Graphu64_ConvertMatrixToFloat(f32 *, PackedMatrixWords *);

extern f32 g_effectContributionInitialScale;

CQuatern *Fx_BuildUpAxisQuaternion(CQuatern *out, u32 bx, u32 by, u32 bz) {
    CVector3 axis;
    CVector3 cross;
    CQuatern result;
    f32 one;
    f32 magnitude;
    f32 angle;
    f32 trig;

    one = g_effectUpQuaternionConstants;
    axis.x = 0.0f;
    axis.y = one;
    axis.z = 0.0f;
    Graphu64_CrossVectors(&cross, &axis, (CVector3 *)&bx);

    magnitude = Gu_Sqrtf((cross.x * cross.x) +
                              (cross.y * cross.y) +
                              (cross.z * cross.z));
    if (magnitude == 0.0f) {
        result.z = 0.0f;
        result.y = 0.0f;
        result.x = 0.0f;
        result.w = one;
    } else {
        Graphu64_ScaleVector(&cross, &cross, one / magnitude);
        angle = Graphu64_ArcCos((axis.x * *(f32 *)&bx) +
                              (axis.y * *(f32 *)&by) +
                              (axis.z * *(f32 *)&bz));
        angle *= ((struct PaddedFloatView *) ((f32 *) (&g_effectUpQuaternionConstants)))->value;
        trig = Gu_Sinf(angle);
        result.x = cross.x * trig;
        result.y = cross.y * trig;
        result.z = cross.z * trig;
        g_turretAimSine = trig;
        result.w = Math_Cosf(angle);
    }
    *out = result;
    return out;
}

void Fx_DrawBoundedParticleQuads(ParticleQuadPoolScene *scene) {
    Particle *particle;
    Particle *next;
    f32 *max;
    IntrusiveList *list;
    f32 pos[3];
    s32 i;

    if (scene->free.count == 100) {
        return;
    }
    gDPPipeSync(g_displayListCursor++);
    gDPSetCycleType(g_displayListCursor++, G_CYC_2CYCLE);
    gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_16b, 1, (u32)&g_materialIntensityMaskTexture);
    gDPSetTile(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    gDPLoadSync(g_displayListCursor++);
    gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, 127, 1024);
    gDPPipeSync(g_displayListCursor++);
    gDPSetTile(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_8b, 2, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, 60, 60);
    gDPSetPrimColor(g_displayListCursor++, 0, 0, 255, 255, 255, 200);
    gSPDisplayList(g_displayListCursor++, (u32)&g_particleQuadRenderSetup);
    for (i = 0; i < 10; i++) {
        max = (&g_cameraVolumeBoundsMinZ + 1);
        list = &scene->lists[i];
        particle = list->head;
        while (particle != 0) {
            Transform *transform = &particle->transform;

            next = particle->next;
            pos[0] = transform->position[0];
            pos[1] = transform->position[1];
            pos[2] = transform->position[2];
            if (!(pos[0] < max[0] && pos[1] < max[1] && pos[2] < max[2] && max[-3] <= pos[0] &&
                  max[-2] <= pos[1] && max[-1] <= pos[2])) {
                List_RemoveIntrusive(list, particle);
                List_AppendIntrusive(&scene->free, particle);
            } else {
                gSPMatrix(g_displayListCursor++, (u32)transform, G_MTX_LOAD);
                gSPVertex(g_displayListCursor++, (u32)&g_particleQuadVertices, 4, 0);
                gSP2Triangles(g_displayListCursor++, 0, 1, 2, 0, 2, 3, 0, 0);
            }
            particle = next;
        }
    }
    Geometry_InvalidateMaterialKeys();
    TextLoad_ResetTextureCache();
}

void Fx_DrawRedParticleQuad(u32 matrixAddress) {
    DrawMatrixScratch local;
    Gfx *cmd;

    local.matrix[0] = 0.0f;
    local.matrix[1] = 0.0f;
    local.matrix[2] = 0.0f;
    local.matrix[4] = 0.0f;
    local.matrix[6] = 0.0f;
    local.matrix[5] = g_particleQuadMatrixAxisScale;

    cmd = g_displayListCursor++;
    gDPPipeSync(cmd);
    cmd = g_displayListCursor++;
    gDPSetCycleType(cmd, G_CYC_2CYCLE);
    cmd = g_displayListCursor++;
    gDPSetTextureImage(cmd, G_IM_FMT_I, G_IM_SIZ_16b, 1, &g_materialIntensityMaskTexture);
    cmd = g_displayListCursor++;
    gDPSetTile(cmd, G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    cmd = g_displayListCursor++;
    gDPLoadSync(cmd);
    cmd = g_displayListCursor++;
    gDPLoadBlock(cmd, G_TX_LOADTILE, 0, 0, 127, 1024);
    cmd = g_displayListCursor++;
    gDPPipeSync(cmd);
    cmd = g_displayListCursor++;
    gDPSetTile(cmd, G_IM_FMT_I, G_IM_SIZ_8b, 2, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    cmd = g_displayListCursor++;
    gDPSetTileSize(cmd, G_TX_RENDERTILE, 0, 0, 60, 60);
    cmd = g_displayListCursor++;
    gDPSetPrimColor(cmd, 255, 255, 200, 0, 0, 150);
    cmd = g_displayListCursor++;
    gSPDisplayList(cmd, &g_particleQuadRenderRestoreList);
    cmd = g_displayListCursor++;
    gSPMatrix(cmd, matrixAddress, G_MTX_LOAD);
    cmd = g_displayListCursor++;
    gSPVertex(cmd, &g_particleQuadVertices, 4, 0);
    cmd = g_displayListCursor++;
    gSP2Triangles(cmd, 0, 1, 2, 0, 2, 3, 0, 0);

    Geometry_InvalidateMaterialKeys();
    TextLoad_ResetTextureCache();
}

void Fx_UpdateEffectLists(s32 owner) {
    g_particleQuadDisplayListState = 0;
    if (g_gameSession.clockPaused == 0) {
        Fx_UpdateAttachedEffects((void *)owner);
        Fx_UpdateTimedCallbacks(owner);
    }
}

Vtx *Fx_AllocateRibbonVertices(VertexArena *vertexPool, s32 vertexCount)
{
    struct RibbonVertexPool *pool = (struct RibbonVertexPool *)vertexPool;
    s32 avail;
    s32 head;

    avail = pool->remaining;
    if (avail < vertexCount) {
        return 0;
    }
    head = (s32)pool->next;
    pool->remaining = avail - vertexCount;
    pool->next += vertexCount;
    return (Vtx *)head;
}

/** Reset the object and compute its trailing-data end pointer. */
void Fx_ResetRibbonVertexPool(void *object) {
    struct RibbonVertexPool *pool = object;
    u32 index = g_lightingBufferIndex;
    pool->state = 0;
    pool->remaining = 300;
    pool->next = pool->vertices[index];
}

s32 Fx_AllocateRibbonSegment(struct ParticleActorListView *ribbonWorld, s32 ribbon) {
    s32 actors;
    actors = ribbonWorld->particleActors;
    if (actors != 0) {
        Lists_Remove(&ribbonWorld->particleActors, (ListLink *)actors);
        Lists_Append(ribbon + 64, actors);
    }
    return actors;
}

void Fx_FreeRibbonSegment(s32 ribbonWorld, struct ParticleRibbonLifetimeView *ribbon, struct FloatStateB0 *actors) {
    ribbon->length = (f32) (ribbon->length - actors->segmentLength);
    Lists_Remove(&((Node44 *)ribbon)->segments, actors);
    Lists_Append(ribbonWorld + 27280, actors);
}

void Fx_RibbonNoop(void) {
}

void Fx_AddActorRibbonSamples(RibbonWorld *ribbonWorld, s32 actor, char *boneMatrices) {
    f32 quadMatrix[16];
    f32 quadScale;
    f32 zero;
    ItemMenuRenderNode *node;

    node = ribbonWorld->lists.inactive.head;
    if (node != 0) {
        zero = 0.0f;
        quadScale = g_particleQuadMatrixScale;
        do {
            if ((s32)node->object == actor && node->value > zero) {
                CopyMatrix(quadMatrix, (f32 *)(boneMatrices + (node->node->matrixIndex << 6)));
                ScaleMatrixLocal(quadMatrix, quadScale, quadScale, quadScale);
                Graphu64_ClampMatrixToFixedRange(quadMatrix);
                Linked_AppendRibbonSegment(ribbonWorld, node, quadMatrix);
            }
            node = node->next;
        } while (node != 0);
    }
}

void Fx_AddParticleRibbonSamples(ParticleRibbonStorageView *ribbonWorld, Shared_Particle *particle, PackedMatrixWords *packedMatrixWords) {
    f32 local[16];
    f32 scale;
    f32 zero;
    ParticleRibbonNodeView *node;

    node = ribbonWorld->ribbonStorage;
    if (node != 0) {
        zero = 0.0f;
        do {
            if (node->samples == particle &&
                node->time > zero &&
                node->time > zero) {
                Graphu64_ConvertMatrixToFloat(local, packedMatrixWords);
                scale = g_particleRibbonActorScale;
                if (particle->desc->renderModel != 0) {
                    scale = g_particleRibbonSpecialActorScale;
                }
                ScaleMatrixLocal(local, scale, scale, scale);
                Graphu64_ClampMatrixToFixedRange(local);
                Linked_AppendRibbonSegment(ribbonWorld, node, local);
            }
            node = node->next;
        } while (node != 0);
    }
}

void Fx_DetachEffectOwner(SwooshAttachmentOwnerView *owner, int object) {
    float minimumValue;
    u8 effectReferenceCount;
    u8 ribbonReferenceCount;
    void *attachedObject;
    void *secondaryObject;
    void *effect;

    effect = owner->head;
    if (effect != 0) {
        do {
            attachedObject = ((struct ParticleSwooshAttachment *)effect)->object;
            if ((int)attachedObject == object) {
                if (attachedObject != 0) {
                    if (((struct ParticleSwooshAttachment *)effect)->flags & 1) {
                        effectReferenceCount = ((Entity1DC *)attachedObject)->effectReferenceCount;
                        if (effectReferenceCount != 0) {
                            ((Entity1DC *)attachedObject)->effectReferenceCount = (u8)(effectReferenceCount - 1);
                        }
                    }
                    if (((struct ParticleSwooshAttachment *)effect)->flags & 2) {
                        secondaryObject = ((struct ParticleSwooshAttachment *)effect)->object;
                        ribbonReferenceCount = ((Entity1DC *)secondaryObject)->ribbonReferenceCount;
                        if (ribbonReferenceCount != 0) {
                            ((Entity1DC *)secondaryObject)->ribbonReferenceCount = (u8)(ribbonReferenceCount - 1);
                        }
                    }
                }
                ((struct ParticleSwooshAttachment *)effect)->object = 0;
                minimumValue = ((struct ParticleSwooshAttachment *)effect)->node->value;
                if (((struct ParticleSwooshAttachment *)effect)->value < minimumValue) {
                    ((struct ParticleSwooshAttachment *)effect)->value = minimumValue;
                }
            }
            effect = ((struct ParticleSwooshAttachment *)effect)->next;
        } while (effect != 0);
    }
}

void Fx_ResetEffectContribution(EffectContribution *contribution, s32 effectId)
{
  contribution->scale = (f32) g_effectContributionInitialScale;
  contribution->id = effectId;
  contribution->state = 0;
  contribution->stateC = 0;
  contribution->state10 = 0;
  contribution->weight = 0;
  contribution->x = 0;
  contribution->y = 0;
  contribution->z = 0;
}
