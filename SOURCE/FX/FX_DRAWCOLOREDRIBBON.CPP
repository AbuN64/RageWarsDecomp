#include "COMMON/WORLD.H"
#include "include_asm.h"
#include "COMMON/EFFECTCONTRIBUTION.H"
#include "RENDER/ANIMATION_FRAME_AND_RIBBON_VIEWS.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include <PR/gbi.h>
#include <ultra64.h>
#include "RENDER/RIBBON_DRAW.H"
#include "COMMON/SELF.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "COMMON/TRIPLE.H"
#include "FX.H"
#include "ENGINE/LISTS.H"

/* Detaches an entity from linked effects while preserving their transforms and lifetimes; the unsigned offset-to-pointer cast preserves matrix-address scheduling and addition operand order. */
extern void Graphu64_ConvertMatrixToFixed(void *,void *),Graphu64_ConvertMatrixToFloat(void *,void *),Graphu64_ClampMatrixToFixedRange(void *),Graphu64_GetMatrixTranslation(void *,void *),Graphu64_GetMatrixScale(void *,void *),ScaleMatrixLocal(void *,f32,f32,f32),Linked_AppendRibbonSegment(void *,Node44 *,void *);

void Fx_DrawColoredRibbon(VertexArena *pool, RibbonActor *actor, GameplayCamera *camera) {
    Morph storage;
    Morph *morph = &storage;
    RibbonClockNode *clock, *next;
    Vtx *vertices;
    u32 count, i;
    s32 edges;
    morph->blends = actor->track->blends;
    morph->count = actor->track->count;
    if (actor->flags & 2) { morph->first = actor->first; morph->second = actor->second; }
    else { morph->first = actor->first; morph->second = actor->first; }
    morph->scaleS = actor->track->scaleS * g_coloredRibbonTextureCoordinateScale;
    morph->scaleT = actor->track->scaleT * g_coloredRibbonTextureCoordinateScale;
    clock = actor->clock;
    next = clock->next;
    count = actor->track->count;
    edges = count - 1;
    gSPMatrix(g_displayListCursor++, &clock->matrix[g_lightingBufferIndex], G_MTX_LOAD);
    while (clock != 0 && next != 0 && 0.0f < clock->time && 0.0f < next->time) {
        vertices = Fx_AllocateRibbonVertices(pool, count);
        if (vertices == 0) break;
        Linked_BuildColoredRibbonVertices(actor, clock, vertices, &storage);
        gSPVertex(g_displayListCursor++, vertices, count, 0);
        gSPMatrix(g_displayListCursor++, &next->matrix[g_lightingBufferIndex], G_MTX_LOAD);
        vertices = Fx_AllocateRibbonVertices(pool, count);
        if (vertices == 0) return;
        Linked_BuildColoredRibbonVertices(actor, next, vertices, &storage);
        gSPVertex(g_displayListCursor++, vertices, count, count);
        i = 0;
        while ((s32)i < edges) {
            { Gfx *cmd = g_displayListCursor++;
              cmd->words.w0 = (((i * 2 & 255) << 16) | (((count + i) * 2 & 255) << 8) | ((count + i + 1) * 2 & 255)) | (G_TRI2 << 24);
              cmd->words.w1 = ((i * 2 & 255) << 16) | (((count + i + 1) * 2 & 255) << 8) | ((i + 1) * 2 & 255);
            }
            i++;
        }
        if (actor->track->closed) {
            { Gfx *cmd = g_displayListCursor++;
              cmd->words.w0 = (((i * 2 & 255) << 16) | (((count + i) * 2 & 255) << 8) | (count * 2 & 255)) | (G_TRI2 << 24);
              cmd->words.w1 = ((i * 2 & 255) << 16) | ((count * 2 & 255) << 8);
            }
        }
        clock = next;
        next = clock->next;

    }
}

/* Partial storage views: the named fields are the ones this routine accesses.
   The prefix and intervening bytes retain the observed node and descriptor layout. */





/* Selects a frame using clamping, looping, ping-pong or random playback. */
s32 Fx_SelectAnimationFrame(AnimationFrameState *state,
                     AnimationFrameDefinition *definition, s32 *frame_count) {
    s32 frame = (s32)state->frame;
    s32 *selected = &frame;
    s32 value;

    switch (definition->mode) {
    case 0:
        value = *frame_count - 1;
        if (*selected >= value) {
            *selected = value;
            state->endpoint = (f32)*frame_count;
        }
        break;
    case 1:
        if (*selected >= *frame_count) {
            *selected = *frame_count - 1;
        }
        break;
    case 2:
        *selected %= *frame_count;
        break;
    case 3:
        value = *frame_count * 2 - 2;
        if (value > 0) {
            value = *selected % value;
        } else {
            value = 0;
        }
        *selected = value;
        if (value >= *frame_count) {
            s32 reflected = *frame_count * 2;
            s32 adjusted = value + 2;
            *selected = reflected - adjusted;
        }
        break;
    case 4:
        *selected = Graphu64_NextRandom() % *frame_count;
        break;
    case 5:
        if (state->cached_frame == -1) {
            state->cached_frame = Graphu64_NextRandom() % *frame_count;
        }
        *selected = state->cached_frame;
        break;
    }
    return frame;
}

void Fx_DetachParticleSwooshes(Root752C *effectWorld, Entity1DC *detachedEntity) {
    f32 localMatrix[16];
    f32 minimumLifetime;
    f32 scale;
    f32 entityScale;
    s32 effectFlags;
    u8 effectReferences;
    u8 ribbonReferences;
    char *unusedPointer;
    Entity1DC *attachedEntity;
    Entity1DC *ribbonEntity;
    struct MenuPlayerScissorRect *unusedPointer1;
    ChildB4 *segment;
    Node44 *ribbon;
    struct MenuPlayerScissorRect *unusedPointer2;
    ribbon = effectWorld->activeRibbons;
    if (ribbon != 0) {
        do {
            effectFlags = ribbon->flags;
            if (effectFlags & 8) {
                segment = ribbon->segments;
                if (segment != 0) {
loop_4:
                    if (segment->attachedEntity == detachedEntity) {
                        if (detachedEntity != 0) {
                            if (detachedEntity == (void *)-1) {
                                ((struct RibbonFrameBufferView *) (((char *) segment) + (g_lightingBufferIndex << 6)))->matrix=((struct RibbonFrameBufferView *) (((char *) segment) + ((g_lightingBufferIndex ^ 1) << 6)))->matrix;
                                segment->attachedEntity = 0;
                            } else {
                                Graphu64_ConvertMatrixToFloat(&localMatrix, &((struct EffectActor *)detachedEntity)->u60.matrices[g_lightingBufferIndex]);
                                scale = g_detachedRibbonActorScale;
                                if (detachedEntity->renderDefinition->flags != 0) {
                                    scale = g_detachedRibbonSpecialActorScale;
                                }
                                ScaleMatrixLocal(&localMatrix, scale, scale, scale);
                                Graphu64_ClampMatrixToFixedRange(&localMatrix);
                                Graphu64_GetMatrixTranslation(&localMatrix, segment->pos);
                                if (ribbon->flags & 4) {
                                    Graphu64_GetMatrixScale(&localMatrix, segment->rot);
                                } else {
                                    Graphu64_ConvertMatrixToFixed(&localMatrix, &segment->mat[g_lightingBufferIndex]);
                                }
                            }
                            segment->remainingLifetime = (f32) ribbon->definition->segmentLifetime;
                        }
                        segment->attachedEntity = (Entity1DC *)-1;
                    }
                    segment = segment->next;
                    if (segment != 0) {
                        goto loop_4;
                    }
                }
            } else if (ribbon->attachedEntity == detachedEntity) {
                if (effectFlags & 2) {
                    unsigned int offset = g_lightingBufferIndex << 6;
                    char *matrix = (char *)offset;
                    matrix += (unsigned int)detachedEntity;
                    matrix += ((char *)&((struct EffectActor *)0)->u60 - (char *)0);
                    if (ribbon->lifetime > 0.0f) {
                    Graphu64_ConvertMatrixToFloat(&localMatrix, matrix);
                    entityScale = g_detachedRibbonEntityScale;
                    if (detachedEntity->renderDefinition->flags != 0) {
                        entityScale = g_detachedRibbonSpecialEntityScale;
                    }
                    ScaleMatrixLocal(&localMatrix, entityScale, entityScale, entityScale);
                    Graphu64_ClampMatrixToFixedRange(&localMatrix);
                    Linked_AppendRibbonSegment(&g_actorParticleScene, ribbon, &localMatrix);
                }
                }
                attachedEntity = ribbon->attachedEntity;
                if (attachedEntity != 0) {
                    if (ribbon->flags & 1) {
                        effectReferences = attachedEntity->effectReferenceCount;
                        if (effectReferences != 0) {
                            attachedEntity->effectReferenceCount = (u8) (effectReferences - 1);
                        }
                    }
                    if (ribbon->flags & 2) {
                        ribbonEntity = ribbon->attachedEntity;
                        ribbonReferences = ribbonEntity->ribbonReferenceCount;
                        if (ribbonReferences != 0) {
                            ribbonEntity->ribbonReferenceCount = (u8) (ribbonReferences - 1);
                        }
                    }
                }
                ribbon->attachedEntity = 0;
                minimumLifetime = ribbon->definition->minimumLifetime;
                if (ribbon->lifetime < minimumLifetime) {
                    ribbon->lifetime = minimumLifetime;
                }
            }
            ribbon = ribbon->next;
        } while (ribbon != 0);
    }
}

#include "TYPES.H"

typedef struct EffectResource {
    f32 value; char pad04[0xC]; s16 attachment; char pad12[0xD]; u8 first, second;
} EffectResource;
typedef struct FxActor {
    char pad00[4]; u16 kind; char pad06[0x112]; u32 *flags;
    char pad11C[0x10]; void *owner; char pad130[0xA9]; u8 references;
} FxActor;
typedef struct EffectList { void *head, *tail; s32 count; } EffectList;
typedef struct EffectNode {
    struct EffectNode *previous, *next; EffectResource *resource;
    void *first, *second; f32 coordinates[2]; void *owner; s32 kind;
    f32 value; s32 reservedWordAfterValue, clearedWordAfterReserved, clearedWordBeforeAttachment, attachment, handle, flags;
    EffectList children; s32 reservedWordAfterChildren, reservedWordTrailing;
} EffectNode;
typedef struct EffectPool { EffectList free, used; } EffectPool;
typedef struct EffectWorld { char pad00[0x751C]; EffectPool pool; } EffectWorld;
typedef struct EffectInstance { char pad00[0xB0]; FxActor *actor; } EffectInstance;
extern EffectResource *Scene_GetLinkedResourceSection(void *, s32);
extern void Lists_ClearHeader(void *);
extern void Textload_LocateTextureResource(void *, s32);
extern void Particle_EncodeRenderLayer(void *, void *);
extern void Graphu64_IdentityMatrix(void *);

static inline EffectNode *FX_FIND_NODE(EffectWorld *world, FxActor *actor) {
    EffectNode *it;
    void *owner = actor->owner;
    s32 kind = actor->kind;
    for (it = world->pool.used.head; it; it = it->next) {
        if (it->owner == owner && it->kind == kind) return it;
    }
    return 0;
}
void Fx_AttachActorRibbon(EffectWorld *world, FxActor *actor, s32 resourceId) {
    EffectNode *node;
    EffectResource *resource;
    void *first, *second;
    f32 matrix[4][4];
    EffectInstance *instance;
    if (*actor->flags & 0x10000) {
        node = FX_FIND_NODE(world, actor);
    } else {
        node = 0;
    }
    if (!node) {
        node = Lists_MoveHeadToInactiveList(&world->pool);
        if (node) {
        resource = Scene_GetLinkedResourceSection(&g_world, resourceId);
        first = ((void **)g_ribbonBlendResourceTable)[resource->first];
        second = ((void **)g_ribbonBlendResourceTable)[resource->second];
        Lists_ClearHeader(&node->children);
        node->flags = 2;
        if (*actor->flags & 0x10000) {
            node->flags = 10;
            node->owner = actor->owner;
            node->kind = actor->kind;
        } else {
            node->owner = actor;
            node->kind = -1;
        }
        node->resource = resource;
        node->first = first;
        node->second = second;
        node->value = resource->value;
        node->reservedWordAfterValue = 0;
        node->attachment = resource->attachment;
        node->reservedWordAfterChildren = 0;
        node->reservedWordTrailing = 0;
        node->clearedWordAfterReserved = 0;
        node->clearedWordBeforeAttachment = 0;
        node->handle = -1;
        if (node->attachment != -1) {
            Textload_LocateTextureResource(node->coordinates, node->attachment);
            if (actor) Particle_EncodeRenderLayer(actor, node->coordinates);
        }
        }
    }
    if (node) {
    ++actor->references;
    if (*actor->flags & 0x10000) {
        Graphu64_IdentityMatrix(matrix);
        instance = ((EffectInstance *(*)(void *, void *, void *))Linked_AppendRibbonSegment)(world, node, matrix);
        if (instance) instance->actor = actor;
    }
    }
}

extern void TextLoad_ResetTextureCache(void);
extern void Linked_UpdateLinkedNodeTransforms(RibbonActor *ribbon);
extern void Linked_UpdateRibbonMatrices(RibbonActor *ribbon, GameplayCamera *camera);
extern void Linked_DrawTexturedRibbon(VertexArena *pool, RibbonActor *ribbon, GameplayCamera *camera);
/* The ribbon arena keeps its built display list at 0 and its ribbon list at 0x7528 (SwooshAttachmentOwnerView/Root752C
 * view the same list). */
struct VertexArena {
    Gfx *displayList; /* 0x0 */
    u8 pad4[0x7528 - 0x4];
    RibbonActor *ribbons; /* 0x7528 */
};
/* Updates one ribbon's linked transforms and points, then draws it once it has at least two points. */
static inline void Render_DrawLinkedRibbon(VertexArena *pool, RibbonActor *ribbon, GameplayCamera *camera) {
    if (ribbon->flags & 8) {
        Linked_UpdateLinkedNodeTransforms(ribbon);
    }
    if (ribbon->flags & 4) {
        Linked_UpdateRibbonMatrices(ribbon, camera);
    }
    if (ribbon->pointCount >= 2) {
        if (ribbon->layer >= 0) {
            Linked_DrawTexturedRibbon(pool, ribbon, camera);
        } else {
            Fx_DrawColoredRibbon(pool, ribbon, camera);
        }
    }
}
/* Builds the arena's ribbon display list once and replays it afterwards: the first call opens a branch list
 * (patched at the end to jump over the body), sets the fixed render state, then updates and draws every ribbon,
 * those with a negative layer first and positive layers second. */
void Fx_DrawLinkedGeometry(VertexArena *pool, GameplayCamera *camera) {
    RibbonActor *ribbon;
    Geometry_InvalidateMaterialKeys();
    TextLoad_ResetTextureCache();
    if (pool->displayList != 0) {
        gSPDisplayList(g_displayListCursor++, pool->displayList);
        return;
    }
    pool->displayList = g_displayListCursor;
    gSPBranchList(g_displayListCursor++, 0);
    gDPPipeSync(g_displayListCursor++);
    Geometry_SetModePreset(14);
    Geometry_SetCombineMode(28);
    /* 0x80 has no F3DEX2 geometry-mode name. */
    gSPGeometryMode(g_displayListCursor++, G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | 0x80, 0);
    gSPGeometryMode(g_displayListCursor++, 0, G_SHADE | G_SHADING_SMOOTH);
    gDPSetCycleType(g_displayListCursor++, G_CYC_1CYCLE);
    gDPSetTexturePersp(g_displayListCursor++, G_TP_PERSP);
    gSPTexture(g_displayListCursor++, 0, 0, 0, G_TX_RENDERTILE, G_OFF);
    for (ribbon = pool->ribbons; ribbon != 0; ribbon = ribbon->next) {
        if (ribbon->layer < 0) Render_DrawLinkedRibbon(pool, ribbon, camera);
    }
    for (ribbon = pool->ribbons; ribbon != 0; ribbon = ribbon->next) {
        if (ribbon->layer > 0) Render_DrawLinkedRibbon(pool, ribbon, camera);
    }
    gSPEndDisplayList(g_displayListCursor++);
    gSPBranchList(pool->displayList++, g_displayListCursor);
    gSPDisplayList(g_displayListCursor++, pool->displayList);
}
