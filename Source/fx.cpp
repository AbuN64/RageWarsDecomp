#include "data_overlay_layouts.h"
#include "Ai/weaponai.h"
#include "Fx/retained_screen_message_owners.h"
#include "Frontend/controllerpak_message_pool.h"
#include "Fx/eu_screen_message_setup.h"
#include "Fx/us_screen_message_data.h"
#include "Common/Lone/weapon_locked_notice_text.h"
#include "Texture/archive_image_records.h"
#include "Engine/graphics_math.h"
#include "Common/shared_particleinstance.h"
#include "Common/game_session.h"
#include "Common/world.h"
#include "include_asm.h"
#include "Common/effectcontribution.h"
#include "Render/animation_frame_and_ribbon_views.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "System/textload_resettexturecache.h"
#include <PR/gbi.h>
#include <platform_sdk.h>
#include "Render/ribbon_draw.h"
#include "Common/self.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Common/sessionhandlerrow.h"
#include "Common/triple.h"
#include "fx.h"
#include "Engine/lists.h"
#include "Engine/scene_drawopaqueactors.h"
#include "Fx/fx_drawcoloredribbon.h"
#include "Game/builddirectionmatrix.h"
#include "Graphu64/graphu64_packfixedmatrix.h"
#include "Particle/particle_haskindzeroentry.h"
#include "Render/linked_drawtexturedribbon.h"
#include "Textload/textload_locatetextureresource.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Rsp/random_direction_and_affine_math.h"
#include <PR/abi.h>
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "Common/heap_arena_entry.h"
#include "Common/geometry_blend_and_instance_views.h"
#include "Common/frustum.h"
#include "Common/hud_effects.h"
#include "Engine/Cache/list.h"
#include "Fx/fx_drawboundedparticlequads.h"
#include "Fx/fx_spawnimpactmark.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Fx/fx_address_symbols.h"
#include "Render/material_color_and_fog_views.h"
#include "Common/ballisticparams.h"
#include "Common/trigger_and_float_value_operations.h"
#include "System/timed_effect_and_item_menu_views.h"
#include "Fx/normalize_vector.h"
#include "Common/weapon_screen_message_operations.h"
#include "Common/packed_callback.h"
#include "Data/rest_source_records.h"
#include "Data/Gfxdata/audio_decodeframe_data.h"
#include "Gfxdata/audio_decodeframe_data.h"
#include "Fx/sky_postscaledscreenmessage_data.h"

/* Detaches an entity from linked effects while preserving their transforms and lifetimes; the unsigned offset-to-pointer cast preserves matrix-address scheduling and addition operand order. */


void Fx_DrawColoredRibbon(RibbonWorld *pool, RibbonActor *actor, GameplayCamera *camera) {
    Morph storage;
    Morph *morph = &storage;
    RibbonSegment *clock, *next;
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
    next = clock->previous;
    count = actor->track->count;
    edges = count - 1;
    gSPMatrix(g_displayListCursor++, &clock->matrices[g_lightingBufferIndex], G_MTX_LOAD);
    while (clock != 0 && next != 0 && 0.0f < clock->remainingLifetime && 0.0f < next->remainingLifetime) {
        vertices = Fx_AllocateRibbonVertices(pool, count);
        if (vertices == 0) break;
        Linked_BuildColoredRibbonVertices(actor, clock, vertices, &storage);
        gSPVertex(g_displayListCursor++, vertices, count, 0);
        gSPMatrix(g_displayListCursor++, &next->matrices[g_lightingBufferIndex], G_MTX_LOAD);
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
        next = clock->previous;

    }
}

/* Partial storage views: the named fields are the ones this routine accesses.
   The prefix and intervening bytes retain the observed node and descriptor layout. */

/* Selects a frame using clamping, looping, ping-pong or random playback. */
s32 Fx_SelectAnimationFrame(RibbonActor *state,
                     struct CROMSwoosh_t *definition, s32 *frame_count) {
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

void Fx_DetachParticleSwooshes(RibbonWorld *effectWorld, void *detachedEntity) {
    f32 localMatrix[16];
    f32 minimumLifetime;
    f32 scale;
    f32 entityScale;
    s32 effectFlags;
    u8 effectReferences;
    u8 ribbonReferences;
    char *unusedPointer;
    LevelActor *attachedEntity;
    Shared_Particle *ribbonEntity;
    OverlayScissorRect *unusedPointer1;
    RibbonSegment *segment;
    RibbonActor *ribbon;
    OverlayScissorRect *unusedPointer2;
    ribbon = (RibbonActor *)effectWorld->pool.used.head;
    if (ribbon != 0) {
        do {
            effectFlags = ribbon->flags;
            if (effectFlags & 8) {
                segment = ribbon->tail;
                if (segment != 0) {
loop_4:
                    if (segment->attachedEntity == detachedEntity) {
                        if (detachedEntity != 0) {
                            if (detachedEntity == (void *)-1) {
                                segment->matrices[g_lightingBufferIndex] = segment->matrices[g_lightingBufferIndex ^ 1];
                                segment->attachedEntity = 0;
                            } else {
                                Graphu64_ConvertMatrixToFloat(&localMatrix, &((Shared_Particle *)detachedEntity)->mtx[g_lightingBufferIndex]);
                                scale = g_detachedRibbonActorScale;
                                if (((Shared_Particle *)detachedEntity)->desc->renderModel != 0) {
                                    scale = g_detachedRibbonSpecialActorScale;
                                }
                                ScaleMatrixLocal(&localMatrix, scale, scale, scale);
                                Graphu64_ClampMatrixToFixedRange(&localMatrix);
                                Graphu64_GetMatrixTranslation(&localMatrix, &segment->position.x);
                                if (ribbon->flags & 4) {
                                    Graphu64_GetMatrixScale(&localMatrix, &segment->scale.x);
                                } else {
                                    Graphu64_ConvertMatrixToFixed(&localMatrix, &segment->matrices[g_lightingBufferIndex]);
                                }
                            }
                            segment->remainingLifetime = (f32) ribbon->track->segmentLifetime;
                        }
                        segment->attachedEntity = (Shared_Particle *)-1;
                    }
                    segment = segment->next;
                    if (segment != 0) {
                        goto loop_4;
                    }
                }
            } else if (ribbon->object == detachedEntity) {
                if (effectFlags & 2) {
                    unsigned int offset = g_lightingBufferIndex << 6;
                    char *matrix = (char *)offset;
                    matrix += (unsigned int)detachedEntity;
                    matrix += ((char *)&((Shared_Particle *)0)->mtx - (char *)0);
                    if (ribbon->time > 0.0f) {
                    Graphu64_ConvertMatrixToFloat(&localMatrix, matrix);
                    entityScale = g_detachedRibbonEntityScale;
                    if (((Shared_Particle *)detachedEntity)->desc->renderModel != 0) {
                        entityScale = g_detachedRibbonSpecialEntityScale;
                    }
                    ScaleMatrixLocal(&localMatrix, entityScale, entityScale, entityScale);
                    Graphu64_ClampMatrixToFixedRange(&localMatrix);
                    Linked_AppendRibbonSegment(&g_gameSession.hud.actors, ribbon, &localMatrix);
                }
                }
                attachedEntity = (LevelActor *)ribbon->object;
                if (attachedEntity != 0) {
                    if (ribbon->flags & 1) {
                        effectReferences = attachedEntity->ribbonReferenceCount;
                        if (effectReferences != 0) {
                            attachedEntity->ribbonReferenceCount = (u8) (effectReferences - 1);
                        }
                    }
                    if (ribbon->flags & 2) {
                        ribbonEntity = (Shared_Particle *)ribbon->object;
                        ribbonReferences = ribbonEntity->ribbonReferenceCount;
                        if (ribbonReferences != 0) {
                            ribbonEntity->ribbonReferenceCount = (u8) (ribbonReferences - 1);
                        }
                    }
                }
                ribbon->object = 0;
                minimumLifetime = ribbon->track->minimumLifetime;
                if (ribbon->time < minimumLifetime) {
                    ribbon->time = minimumLifetime;
                }
            }
            ribbon = ribbon->next;
        } while (ribbon != 0);
    }
}

#include "types.h"
#include "Menu/g_menuplayerscissorrects.h"







static inline RibbonActor *FX_FIND_NODE(RibbonWorld *world, Shared_Particle *actor) {
    RibbonActor *it;
    void *owner = actor->owner;
    s32 kind = actor->inst.type;
    for (it = world->pool.used.head; it; it = it->next) {
        if (it->object == owner && it->contextId == kind) return it;
    }
    return 0;
}
void Fx_AttachActorRibbon(RibbonWorld *world, Shared_Particle *actor, s32 resourceId) {
    RibbonActor *node;
    struct CROMSwoosh_t *resource;
    void *first, *second;
    f32 matrix[4][4];
    RibbonSegment *instance;
    if (actor->desc->flags & 0x10000) {
        node = FX_FIND_NODE(world, actor);
    } else {
        node = 0;
    }
    if (!node) {
        node = Lists_MoveHeadToInactiveList(&world->pool);
        if (node) {
        resource = Scene_GetLinkedResourceSection(&g_world, resourceId);
        first = ((void **)g_ribbonBlendResourceTable)[resource->firstBlend];
        second = ((void **)g_ribbonBlendResourceTable)[resource->secondBlend];
        Lists_ClearHeader(&node->tail);
        node->flags = 2;
        if (actor->desc->flags & 0x10000) {
            node->flags = 10;
            node->object = actor->owner;
            node->contextId = actor->inst.type;
        } else {
            node->object = actor;
            node->contextId = -1;
        }
        node->track = resource;
        node->first = first;
        node->second = second;
        node->time = resource->initialLifetime;
        node->phaseWord = 0;
        node->layer = resource->textureId;
        node->lengthWord = 0;
        node->retries = 0;
        node->endpointWord = 0;
        node->frameWord = 0;
        node->cached_frame = -1;
        if (node->layer != -1) {
            Textload_LocateTextureResource(node->textureWords, node->layer);
            if (actor) Particle_EncodeRenderLayer(actor, node->textureWords);
        }
        }
    }
    if (node) {
    ++actor->ribbonReferenceCount;
    if (actor->desc->flags & 0x10000) {
        Graphu64_IdentityMatrix(matrix);
        instance = ((RibbonSegment *(*)(void *, void *, void *))Linked_AppendRibbonSegment)(world, node, matrix);
        if (instance) instance->attachedEntity = actor;
    }
    }
}

extern void TextLoad_ResetTextureCache(void);

/* Updates one ribbon's linked transforms and points, then draws it once it has at least two points. */
static inline void Render_DrawLinkedRibbon(RibbonWorld *pool, RibbonActor *ribbon, GameplayCamera *camera) {
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
void Fx_DrawLinkedGeometry(RibbonWorld *pool, GameplayCamera *camera) {
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
    for (ribbon = (RibbonActor *)pool->pool.used.head; ribbon != 0; ribbon = ribbon->next) {
        if (ribbon->layer < 0) Render_DrawLinkedRibbon(pool, ribbon, camera);
    }
    for (ribbon = (RibbonActor *)pool->pool.used.head; ribbon != 0; ribbon = ribbon->next) {
        if (ribbon->layer > 0) Render_DrawLinkedRibbon(pool, ribbon, camera);
    }
    gSPEndDisplayList(g_displayListCursor++);
    gSPBranchList(pool->displayList++, g_displayListCursor);
    gSPDisplayList(g_displayListCursor++, pool->displayList);
}

/* Draws the scene's ten particle lists unless the free list holds exactly 100 particles: sets the render state and the shared particle texture g_materialIntensityMaskTexture (a 16x16 texture drawn in grey at alpha 200 through g_particleQuadRenderSetup), then for every particle inside the view box ending at g_cameraVolumeBounds.max loads its matrix and draws the shared quad g_particleQuadVertices, while particles outside it are unlinked (List_RemoveIntrusive) and returned to the free list (List_AppendIntrusive); finally restores the render state through Geometry_InvalidateMaterialKeys and TextLoad_ResetTextureCache. */












extern unsigned char g_materialIntensityMaskTexture[];





extern char g_particleQuadRenderRestoreList;





extern s32 g_particleQuadDisplayListState;


extern s32 g_lightingBufferIndex;













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

void Fx_DrawBoundedParticleQuads(RibbonWorld *scene) {
    ProjectedMark *particle;
    ProjectedMark *next;
    f32 *max;
    IntrusiveList *list;
    f32 pos[3];
    s32 i;

    if (scene->recordList.count == 100) {
        return;
    }
    gDPPipeSync(g_displayListCursor++);
    gDPSetCycleType(g_displayListCursor++, G_CYC_2CYCLE);
    gDPSetTextureImage(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_16b, 1, (uintptr_t)&g_materialIntensityMaskTexture);
    gDPSetTile(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    gDPLoadSync(g_displayListCursor++);
    gDPLoadBlock(g_displayListCursor++, G_TX_LOADTILE, 0, 0, 127, 1024);
    gDPPipeSync(g_displayListCursor++);
    gDPSetTile(g_displayListCursor++, G_IM_FMT_I, G_IM_SIZ_8b, 2, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    gDPSetTileSize(g_displayListCursor++, G_TX_RENDERTILE, 0, 0, 60, 60);
    gDPSetPrimColor(g_displayListCursor++, 0, 0, 255, 255, 255, 200);
    gSPDisplayList(g_displayListCursor++, (uintptr_t)&g_particleQuadRenderSetup);
    for (i = 0; i < 10; i++) {
        max = &g_cameraVolumeBounds.max;
        list = &scene->cells[i];
        particle = list->head;
        while (particle != 0) {
            ProjectedMarkTransform *transform = &particle->transform;

            next = particle->next;
            pos[0] = transform->position[0];
            pos[1] = transform->position[1];
            pos[2] = transform->position[2];
            if (!(pos[0] < max[0] && pos[1] < max[1] && pos[2] < max[2] && max[-3] <= pos[0] &&
                  max[-2] <= pos[1] && max[-1] <= pos[2])) {
                List_RemoveIntrusive(list, particle);
                List_AppendIntrusive(&scene->recordList, particle);
            } else {
                gSPMatrix(g_displayListCursor++, (u32)transform, G_MTX_LOAD);
                gSPVertex(g_displayListCursor++, (uintptr_t)&g_particleQuadVertices, 4, 0);
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

Vtx *Fx_AllocateRibbonVertices(RibbonWorld *pool, s32 vertexCount)
{
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
    struct RibbonWorld *pool = object;
    u32 index = g_lightingBufferIndex;
    pool->displayList = 0;
    pool->remaining = 300;
    pool->next = pool->vertices[index];
}

s32 Fx_AllocateRibbonSegment(struct RibbonWorld *ribbonWorld, s32 ribbon) {
    s32 actors;
    actors = (s32)ribbonWorld->actorList.head;
    if (actors != 0) {
        Lists_Remove(&ribbonWorld->actorList.head, (ListLink *)actors);
        Lists_Append(ribbon + 64, actors);
    }
    return actors;
}

void Fx_FreeRibbonSegment(s32 ribbonWorld, struct RibbonActor *ribbon, struct RibbonSegment *actors) {
    ribbon->length = (f32) (ribbon->length - actors->length);
    Lists_Remove(&ribbon->tail, actors);
    Lists_Append(ribbonWorld + 27280, actors);
}

void Fx_RibbonNoop(void) {
}

void Fx_AddActorRibbonSamples(RibbonWorld *ribbonWorld, s32 actor, char *boneMatrices) {
    f32 quadMatrix[16];
    f32 quadScale;
    f32 zero;
    RibbonActor *node;

    node = ribbonWorld->pool.used.head;
    if (node != 0) {
        zero = 0.0f;
        quadScale = g_particleQuadMatrixScale;
        do {
            if ((s32)node->object == actor && node->time > zero) {
                CopyMatrix(quadMatrix, (f32 *)(boneMatrices + (node->track->matrixIndex << 6)));
                ScaleMatrixLocal(quadMatrix, quadScale, quadScale, quadScale);
                Graphu64_ClampMatrixToFixedRange(quadMatrix);
                Linked_AppendRibbonSegment(ribbonWorld, node, quadMatrix);
            }
            node = node->next;
        } while (node != 0);
    }
}

void Fx_AddParticleRibbonSamples(RibbonWorld *ribbonWorld, Shared_Particle *particle, FixedPointMatrix *packedMatrixWords) {
    f32 local[16];
    f32 scale;
    f32 zero;
    RibbonActor *node;

    node = ribbonWorld->pool.used.head;
    if (node != 0) {
        zero = 0.0f;
        do {
            if (node->object == particle &&
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

void Fx_DetachEffectOwner(RibbonWorld *owner, int object) {
    float minimumValue;
    u8 effectReferenceCount;
    u8 ribbonReferenceCount;
    void *attachedObject;
    void *secondaryObject;
    void *effect;

    effect = owner->pool.used.head;
    if (effect != 0) {
        do {
            attachedObject = ((struct RibbonActor *)effect)->object;
            if ((int)attachedObject == object) {
                if (attachedObject != 0) {
                    if (((struct RibbonActor *)effect)->flags & 1) {
                        effectReferenceCount = ((LevelActor *)attachedObject)->ribbonReferenceCount;
                        if (effectReferenceCount != 0) {
                            ((LevelActor *)attachedObject)->ribbonReferenceCount = (u8)(effectReferenceCount - 1);
                        }
                    }
                    if (((struct RibbonActor *)effect)->flags & 2) {
                        secondaryObject = ((struct RibbonActor *)effect)->object;
                        ribbonReferenceCount = ((Shared_Particle *)secondaryObject)->ribbonReferenceCount;
                        if (ribbonReferenceCount != 0) {
                            ((Shared_Particle *)secondaryObject)->ribbonReferenceCount = (u8)(ribbonReferenceCount - 1);
                        }
                    }
                }
                ((struct RibbonActor *)effect)->object = 0;
                minimumValue = ((struct RibbonActor *)effect)->track->minimumLifetime;
                if (((struct RibbonActor *)effect)->time < minimumValue) {
                    ((struct RibbonActor *)effect)->time = minimumValue;
                }
            }
            effect = ((struct RibbonActor *)effect)->next;
        } while (effect != 0);
    }
}

void Fx_ResetEffectContribution(EffectContribution *contribution, s32 effectId)
{
  contribution->scale = (f32) g_effectContributionInitialScale[0];
  contribution->id = effectId;
  contribution->state = 0;
  contribution->stateC = 0;
  contribution->state10 = 0;
  contribution->weight = 0;
  contribution->x = 0;
  contribution->y = 0;
  contribution->z = 0;
}

void Fx_SetAnimatorScript(void *animator, int scriptAddress) {
    Animator *animation = animator;
    animation->mode = 0;
    animation->loop = (f32 *)scriptAddress;
    animation->script = (f32 *)scriptAddress;
}

void Fx_ApplyEffectContribution(EffectContribution *effectContribution) {
    if (effectContribution->weight != 0.0f) {
        g_menuModelFillColor[0] = effectContribution->x;
        g_menuModelFillColor[1] = effectContribution->y;
        g_menuModelFillColor[2] = effectContribution->z;
    } else {
        g_menuModelFillColor[0] = 0.0f;
        g_menuModelFillColor[1] = 0.0f;
        g_menuModelFillColor[2] = 0.0f;
    }
    g_menuModelFillColor[3] = effectContribution->weight;
    g_menuModelFillColor[4] = effectContribution->scale;
}

void Fx_AccumulateEffectComponents(struct EffectColorContribution *contribution) {
    if (contribution->alpha != 0.0f) {
        g_menuModelFillColor[0] += contribution->red;
        g_menuModelFillColor[1] += contribution->green;
        g_menuModelFillColor[2] += contribution->blue;
        g_menuModelFillColor[3] += contribution->alpha;
    }
    g_menuModelFillColor[4] += contribution->auxiliaryAlpha;
}


void Fx_ClampScalarRange(f32 *scalarPointer) {
    f32 maximum;
    f32 contributionScale;

    contributionScale = (contributionScale = *scalarPointer);
    if (*scalarPointer < 0.0f) {
        *scalarPointer = 0.0f;
    } else {
        maximum = g_effectContributionInitialScale[1];
        if (maximum < contributionScale) {
            *scalarPointer = maximum;
        }
    }
}

void Fx_AddTimedCallback(s32 ownerAddress, s32 callbackContextAddress, s32 callbackAddress, s32 remainingCalls, f32 interval) {
    void *node;

    node = Lists_MoveHeadToInactiveList(&((struct RibbonWorld *)ownerAddress)->timers);
    if (node != 0) {
        ((EffectTimer *)(node))->callback = (void (*)(void *))callbackContextAddress;
        ((EffectTimer *)(node))->callbackData = callbackAddress;
        ((EffectTimer *)(node))->countdown = 0;
        ((EffectTimer *)(node))->interval = interval;
        ((EffectTimer *)(node))->remainingCalls = remainingCalls;
    }
}



ProjectedMark *Fx_SpawnImpactMark(RibbonWorld *scene, CVector3 position, CVector3 normal, s32 surface, s32 owner) {
    f32 matrix[16];
    CQuatern rotation;
    ProjectedMark *node;
    IntrusiveList *list;

    rotation = Graphu64_BuildDirectionQuaternion(&normal.x);
    if (g_particleQuadDisplayListState != 0) return 0;
    g_particleQuadDisplayListState = 1;
    list = &scene->cells[surface];
    node = scene->recordList.head;
    if (node != 0) {
        List_RemoveIntrusive(&scene->recordList, node);
    } else {
        node = list->head;
        if (node == 0) goto done;
        List_RemoveIntrusive(list, node);
    }
    List_AppendIntrusive(list, node);
    if (node != 0) {
        node->owner = owner;
        MatrixFromQuaternion(&rotation.x, matrix);
        PitchMatrixLocal(matrix, 1.5707965f);
        Graphu64_NormalizeVec3(&normal);
        Graphu64_ScaleVector(&normal, &normal, 2.048f);
        Graphu64_AddVec3(&position, &position, &normal);
        TranslateMatrix((char *)matrix, position.x, position.y, position.z);
        ScaleMatrixLocal(matrix, g_impactMarkScaleConstants[0], 1.0f, g_impactMarkScaleConstants[0]);
        Graphu64_ConvertMatrixToFixed(matrix, &node->transform.matrix);
    }
done:
    return node;
}

/* 802A6AC0_2.CPP */


extern f32 g_frameElapsedTime;






extern s32 g_lightingBufferIndex;





















void Fx_RecycleOwnerParticles(RibbonWorld *particlePool, s32 ownerId) {
    s32 count;
    s32 offset;
    void **slot;
    ProjectedMark *node;
    ProjectedMark *next;

    if (particlePool->recordList.count != 100) {
        count = 0;
        offset = 38112;
        do {
            slot = &particlePool->cells[count].head;
            node = *slot;
            if (node != 0) {
                do {
                    next = node->next;
                    if (node->owner == ownerId) {
                        List_RemoveIntrusive(slot, node);
                        List_AppendIntrusive(&particlePool->recordList, node);
                    }
                    node = next;
                } while (node != 0);
            }
            count += 1;
            offset += 20;
        } while (count < 10);
    }
}

void Fx_UpdateAttachedEffects(RibbonWorld *owner) {
    RibbonActor *state;
    RibbonActor *next;
    u8 *object;

    state = owner->pool.used.head;
    if (state != 0) {
        do {
            next = state->next;
            if (Linked_UpdateRibbonLifetime((s32)owner, state) == 0) {
                object = state->object;
                if (object != 0) {
                    if (state->flags & 1) {
                        if (((LevelActor *)object)->ribbonReferenceCount != 0) {
                            ((LevelActor *)object)->ribbonReferenceCount--;
                        }
                    }
                    if (state->flags & 2) {
                        object = state->object;
                        if (((Shared_Particle *)object)->ribbonReferenceCount != 0) {
                            ((Shared_Particle *)object)->ribbonReferenceCount--;
                        }
                    }
                }
                state->object = 0;
                if (state->time < state->track->minimumLifetime) {
                    state->time = state->track->minimumLifetime;
                }
                Lists_MoveNodeToActiveList((struct Lists18 *)&owner->pool, (ListLink *)state);
            }
            state = next;
        } while (state != 0);
    }
}

void Fx_UpdateTimedCallbacks(void *owner)
{
  void *node;
  char *callbackNodeAddress;
  void *next;
  f32 value;
  s32 count;
  node = ((RibbonWorld *)(owner))->timers.used.head;
  if (node != 0)
  {
    do
    {
      value = (((EffectTimer *)(node))->remainingTime = (((EffectTimer *)(node))->remainingTime) - g_frameElapsedTime);
      next = ((EffectTimer *)(node))->next;
      if (value <= 0.0f)
      {
        value += ((EffectTimer *)(node))->interval;
        ((EffectTimer *)(node))->remainingTime = value;
        if (value < 0.0f)
        {
          ((EffectTimer *)(node))->remainingTime = 0.0f;
        }
        (((struct EffectTimer *) ((char *) node))->callback)(node);
        count = (((EffectTimer *) (callbackNodeAddress = (char *) node))->remainingCalls) - 1;
        ((EffectTimer *)(node))->remainingCalls = count;
        if (count <= 0)
        {
          Lists_MoveNodeToActiveList((struct Lists18 *)&((RibbonWorld *)(owner))->timers, node);
        }
      }
      node = next;
    }
    while (node != 0);
  }
}

void Fx_ResolveEntryResource(void *callbackContext, void *itemEntry, void *actor) {
    CItem *entry = itemEntry;
    s32 resourceId;
    s32 *p;

    resourceId = entry->updateCallbackOrTextureId;
    if (resourceId != -1) {
        p = &entry->imageFrameOrTextureHandle;
        Textload_LocateTextureResource(p, resourceId);
        if (actor != 0) {
            Particle_EncodeRenderLayer(actor, p);
        }
    }
}

void Fx_DetachEffectObject(RibbonActor *state) {
    u8 *object;

    object = state->object;
    if (object != 0) {
        if (state->flags & 1) {
            if (((LevelActor *)object)->ribbonReferenceCount != 0) {
                ((LevelActor *)object)->ribbonReferenceCount--;
            }
        }
        if (state->flags & 2) {
            object = state->object;
            if (((Shared_Particle *)object)->ribbonReferenceCount != 0) {
                ((Shared_Particle *)object)->ribbonReferenceCount--;
            }
        }
    }
    state->object = 0;
    if (state->time < state->track->minimumLifetime) {
        state->time = state->track->minimumLifetime;
    }
}

/* Fills a GameSprite descriptor from an image: its pixel data and format, its two palette or data words, its scaled width and height, and when a second image is given the texture extents from its size shifts and the derived scale and step. */
void Fx_ConfigureSpriteImage(GameImage *image, GameImage *texture, GameSprite *GameSprite) {
    f32 scale;
    s32 height;
    f32 *unit;

    GameSprite->data = image->header->data;
    GameSprite->format = image->header->format;
    if (image->flags & 2) {
        GameSprite->primaryData = image->primaryData;
        GameSprite->secondaryData = image->secondaryData;
    } else {
        GameSprite->primaryData = image->primaryData;
        GameSprite->secondaryData = image->primaryData;
    }
    scale = g_impactMarkScaleConstants[1];
    GameSprite->width = image->header->width * scale;
    GameSprite->height = image->header->height * scale;
    if (texture != 0) {
        GameSprite->extentX = 1 << (texture->header->widthShift + 5);
        GameSprite->extentX = GameSprite->extentX * image->header->scale - g_spriteExtentAndUnitConstants;
        height = 1 << (texture->header->heightShift + 5);
        unit = &g_spriteExtentAndUnitConstants + 1;
        GameSprite->step = *unit / ((f32)GameSprite->format - *unit);
        GameSprite->extentY = height;
    }
}

void Fx_UpdateChildTransform(RibbonActor *parentNode, void *childNode) {
    f32 local[16];
    f32 scale;
    void *entry;
    Matrix *dst;
    Matrix *src;

    entry = ((RibbonSegment *)childNode)->attachedEntity;
    if (entry != 0) {
        if (entry == (void *)-1) {
            ((RibbonSegment *)childNode)->matrices[g_lightingBufferIndex] = ((RibbonSegment *)childNode)->matrices[g_lightingBufferIndex ^ 1];
            ((RibbonSegment *)childNode)->attachedEntity = 0;
        } else {
            Graphu64_ConvertMatrixToFloat(local, &((Shared_Particle *)entry)->mtx[g_lightingBufferIndex]);
            scale = g_childTransformDefaultScale;
            if (((Shared_Particle *)entry)->desc->renderModel != 0) {
                scale = g_childTransformAlternateScale;
            }
            ScaleMatrixLocal(local, scale, scale, scale);
            Graphu64_ClampMatrixToFixedRange(local);
            Graphu64_GetMatrixTranslation((char *)local, &((RibbonSegment *)childNode)->position.x);
            if (parentNode->flags & 4) {
                Graphu64_GetMatrixScale(local, &((RibbonSegment *)childNode)->scale.x);
            } else {
                Graphu64_ConvertMatrixToFixed(local, (FixedPointMatrix *)(&((struct RibbonSegment *)childNode)->matrices[g_lightingBufferIndex]));
            }
        }
        ((RibbonSegment *)childNode)->remainingLifetime = parentNode->track->segmentLifetime;
    }
}

void Fx_UpdateNodeFractions(void *ribbonState) {
    RibbonActor *state = ribbonState;
    f32 accum;
    f32 delta;
    RibbonSegment *node;

    if (state->length > 0.0f) {
        accum = 0.0f;
        node = (RibbonSegment *)state->tail;
        if (node != 0) {
            do {
                node->fraction = accum / state->length;
                delta = node->length;
                node = node->next;
                accum += delta;
            } while (node != 0);
        }
    }
}

void Fx_DrawEffectGeometry(s32 pool, void *ribbon, s32 camera) {
    RibbonActor *state = ribbon;
    if (state->flags & 8) {
        Linked_UpdateLinkedNodeTransforms(ribbon);
    }
    if (state->flags & 4) {
        Linked_UpdateRibbonMatrices(ribbon, camera);
    }
    if (state->pointCount >= 2) {
        if (state->layer >= 0) {
            Linked_DrawTexturedRibbon(pool, ribbon, camera);
            return;
        }
        Fx_DrawColoredRibbon(pool, ribbon, camera);
    }
}

void Fx_AppendAttachedTransform(void *ribbonOwner, void *attachmentState, void *particle, s32 sourceMatrix) {
    RibbonActor *state = attachmentState;
    f32 local[16];
    Shared_Particle *entry;
    f32 scale;

    entry = state->object;
    if (entry == particle && state->time > 0.0f) {
        Graphu64_ConvertMatrixToFloat(local, sourceMatrix);
        scale = g_attachedTransformDefaultScale;
        if (entry->desc->renderModel != 0) {
            scale = g_attachedTransformModelScale;
        }
        ScaleMatrixLocal(local, scale, scale, scale);
        Graphu64_ClampMatrixToFixedRange(local);
        Linked_AppendRibbonSegment(ribbonOwner, state, local);
    }
}

void *Fx_FindAttachedEffect(RibbonWorld *owner, s32 particleAddress, s32 contextId) {
    RibbonActor *node;

    node = owner->pool.used.head;
    if (node != 0) {
        do {
            if ((s32)node->object == particleAddress) {
                if (node->contextId == contextId) {
                    return node;
                }
            }
            node = node->next;
        } while (node != 0);
    }
    return 0;
}

void Fx_DrawEffectPasses(void *pool, void *camera) {
    RibbonActor *node;

    node = ((RibbonWorld *)pool)->pool.used.head;
    while (node != 0) {
        if (node->layer < 0) {
            if (node->flags & 8) {
                Linked_UpdateLinkedNodeTransforms(node);
            }
            if (node->flags & 4) {
                Linked_UpdateRibbonMatrices(node, camera);
            }
            if (node->pointCount >= 2) {
                if (node->layer >= 0) {
                    Linked_DrawTexturedRibbon(pool, node, camera);
                } else {
                    Fx_DrawColoredRibbon(pool, node, camera);
                }
            }
        }
        node = node->next;
    }

    node = ((RibbonWorld *)pool)->pool.used.head;
    while (node != 0) {
        if (node->layer > 0) {
            if (node->flags & 8) {
                Linked_UpdateLinkedNodeTransforms(node);
            }
            if (node->flags & 4) {
                Linked_UpdateRibbonMatrices(node, camera);
            }
            if (node->pointCount >= 2) {
                if (node->layer >= 0) {
                    Linked_DrawTexturedRibbon(pool, node, camera);
                } else {
                    Fx_DrawColoredRibbon(pool, node, camera);
                }
            }
        }
        node = node->next;
    }
}

void Fx_UpdateAnimatorScript(Animator *a) {
    s32 next;
    f32 op0;
    f32 op1;
    f32 op2;
    f32 op3;
    f32 op4;
    f32 op5;

    next = 0;
    switch (a->mode) {
    case 0:
        if (a->loop != 0) {
            next = 1;
        }
        break;
    case 1:
        a->time -= g_frameElapsedTime;
        if (a->time < 0.0f) {
            next = 1;
        }
        break;
    case 4:
        a->time += g_frameElapsedTime;
        if (a->valueDuration <= a->time) {
            a->time = a->valueDuration;
            next = 1;
        }
        op1 = a->time / a->valueDuration;
        op0 = 1.0f - op1;
        a->value = op0 * a->valueFrom + op1 * a->valueTo;
        break;
    case 6:
        a->time += g_frameElapsedTime;
        if (a->colourDuration <= a->time) {
            a->time = a->colourDuration;
            next = 1;
        }
        op1 = a->time / a->colourDuration;
        op0 = 1.0f - op1;
        a->rgb[0] = op0 * a->rgbFrom[0] + op1 * a->rgbTo[0];
        a->rgb[1] = op0 * a->rgbFrom[1] + op1 * a->rgbTo[1];
        a->rgb[2] = op0 * a->rgbFrom[2] + op1 * a->rgbTo[2];
        a->alpha = op0 * a->alphaFrom + op1 * a->alphaTo;
        break;
    }
    while (next) {
        a->mode = *a->script++;
        next = 0;
        switch (a->mode) {
        case 0:
            a->script = 0;
            a->loop = 0;
            break;
        case 1:
            op5 = *a->script++;
            a->time = op5;
            break;
        case 2:
            op0 = *a->script++;
            op1 = *a->script++;
            a->mode = 1;
            a->time = Graphu64_RandomBetween(op0, op1);
            break;
        case 3:
            next = 1;
            op4 = *a->script++;
            a->value = op4;
            break;
        case 4:
            op4 = *a->script++;
            op5 = *a->script++;
            a->valueFrom = a->value;
            a->time = 0.0f;
            a->valueTo = op4;
            a->valueDuration = op5;
            break;
        case 5:
            next = 1;
            op2 = *a->script++;
            op3 = *a->script++;
            op1 = *a->script++;
            op4 = *a->script++;
            a->rgb[0] = op2;
            a->rgb[1] = op3;
            a->rgb[2] = op1;
            a->alpha = op4;
            break;
        case 6:
            op2 = *a->script++;
            op3 = *a->script++;
            op1 = *a->script++;
            op4 = *a->script++;
            op5 = *a->script++;
            a->rgbFrom[0] = a->rgb[0];
            a->rgbFrom[1] = a->rgb[1];
            a->rgbFrom[2] = a->rgb[2];
            a->alphaFrom = a->alpha;
            a->time = 0.0f;
            a->rgbTo[0] = op2;
            a->rgbTo[1] = op3;
            a->rgbTo[2] = op1;
            a->alphaTo = op4;
            a->colourDuration = op5;
            break;
        case 7:
            next = 1;
            a->script++;
            break;
        case 8:
            next = 1;
            a->script = a->loop;
            break;
        }
    }
}

/* Fill colour state (the render header names it f32 g_menuModelFillColor[5]). The five floats are declared here as
 * separate globals so that every clamp access loads its own address. */
typedef struct FillFade {
    f32 alpha;
    f32 target;
} FillFade;
#define FILL_FADE ((FillFade *)&g_menuModelFillAlpha)

void Fx_UpdateFillMode(void) {
    f32 target;
    f32 alpha;

    if (g_menuModelFillColor[0] < 0.0f) g_menuModelFillColor[0] = 0.0f; else if (g_menuModelFillColor[0] > 255.0f) g_menuModelFillColor[0] = 255.0f;
    if (g_menuModelFillGreen < 0.0f) g_menuModelFillGreen = 0.0f; else if (g_menuModelFillGreen > 255.0f) g_menuModelFillGreen = 255.0f;
    if (g_menuModelFillBlue < 0.0f) g_menuModelFillBlue = 0.0f; else if (g_menuModelFillBlue > 255.0f) g_menuModelFillBlue = 255.0f;
    if (g_menuModelFillAlpha < 0.0f) g_menuModelFillAlpha = 0.0f; else if (g_menuModelFillAlpha > 255.0f) g_menuModelFillAlpha = 255.0f;
    if (g_menuModelFillTargetAlpha < 0.0f) g_menuModelFillTargetAlpha = 0.0f; else if (g_menuModelFillTargetAlpha > 255.0f) g_menuModelFillTargetAlpha = 255.0f;
    target = FILL_FADE->target;
    alpha = FILL_FADE->alpha;
    if (target == 255.0f && alpha == 0.0f) {
        g_menuModelFillEnabled = 0;
        return;
    }
    if (target != 255.0f && alpha == 0.0f) {
        g_menuModelFillEnabled = 1;
        FILL_FADE->alpha = FILL_FADE->target;
        return;
    }
    if (target == 255.0f && alpha != 0.0f) {
        g_menuModelFillEnabled = 3;
        return;
    }
    if (target != 255.0f && alpha != 0.0f) {
        g_menuModelFillEnabled = 6;
    }
}





















#if defined(VERSION_US)
UsScreenMessageData s_SkyPostscaledscreenmessageFREEZEKLMOFormatText = {
    {
        0x00000003, 0x00000000, 0x00000000, 0x00000002, 0x00000000, 0x00000003, 0x00000000, 0x00000000,
        0x00000002, 0x00000000, 0x00000003, 0x00000000, 0xFFFFFFD8, 0x00000002, 0x00000000, 0x5F465245,
        0x455A455F, 0x800D1DB4, 0x084B0E0C, 0xFFFF0000, 0x00120003, 0x00010000, 0x002AC59C, 0x800D1DB8,
        0x084C0E0C, 0xFFFF0000, 0x00130004, 0x00030000, 0x002AC59C, 0x800D1DBC, 0x084D0E0C, 0xFFFF0000,
        0x00140006, 0x00010000, 0x002AC59C, 0x800D1DC4, 0x084F0E0C, 0xFFFF0000, 0x00150005, 0x00010000,
        0x002AC59C, 0x800D1E70, 0x0BC40DB6, 0x00000000, 0x00010064, 0x002ACA48, 0x800D1E74, 0x0BC50DB6,
        0x00000000, 0x00010064, 0x002ACA48, 0x800D1E78, 0x0BC60DAC, 0x00000000, 0x00000032, 0x002ACA48,
        0x800D1E7C, 0x0BC70DAC, 0x00000000, 0x00000032, 0x002ACA48, 0x800D1E80, 0x0BC80DC0, 0x00000000,
        0x00020005, 0x002ACA48, 0x800D1E84, 0x0BC90DC0, 0x00000000, 0x00020005, 0x002ACA48, 0x800D1CF0,
        0x06A50001, 0x00000000, 0x00000002, 0x000000C8, 0x002ACB34, 0x800D1CF4, 0x06A60001, 0x00000000,
        0x0000000A, 0x00000064, 0x002ACB34, 0x800D1D04, 0x06A70001, 0x012B0000, 0x00000064, 0x00000064,
        0x002ACB34, 0x800D1D08, 0x06A80001, 0x012B0000, 0x00000064, 0x000000C8, 0x002ACB34, 0x800D1CF4,
        0x06B80001, 0x00000000, 0x0000000A, 0x00000064, 0x002ACB34, 0x800D1CF8, 0x06B90DE8, 0x00000000,
        0x0000000F, 0x00000064, 0x002ACB34, 0x800D1CFC, 0x06BA0DE8, 0x00000000, 0x00000019, 0x00000064,
        0x002ACB34, 0x800D1D00, 0x06BB0DF2, 0x00000000, 0x00000032, 0x00000064, 0x002ACB34, 0x00000000,
        0x06A90001, 0x00000000, 0x00010000, 0x002ACC58, 0x00000000, 0x06AA0001, 0x00000000, 0x000A0000,
        0x002ACC58, 0x800D1D54, 0x0BD60E0E, 0x00000000, 0x002ABB0C, 0x800D1D58, 0x0BD702C6, 0x00000000,
        0x002ABB0C, 0x800D1D64, 0x0BD80DCA, 0x00000000, 0x002ABB0C, 0x800D1D14, 0x07080001, 0x012B0000,
        0x002ACD68, 0x800D1D18, 0x07090001, 0x012B0000, 0x002ACD68, 0x800D1D1C, 0x070A0001, 0x012B0000,
        0x002ACD68, 0x800D1D20, 0x070B0001, 0x012B0000, 0x002ACD68, 0x800D1D28, 0x111C0001, 0x012B0000,
        0x002ACD68, 0x800D1D2C, 0x111D0001, 0x012B0000, 0x002ACD68, 0x800D1D30, 0x111E0001, 0x012B0000,
        0x002ACD68, 0x800D1D34, 0x111F0001, 0x012B0000, 0x002ACD68, 0x800D1D38, 0x11200001, 0x012B0000,
        0x002ACD68, 0x800D1D3C, 0x11300001, 0x012B0000, 0x002ACD68, 0x800D1D40, 0x11310001, 0x012B0000,
        0x002ACD68, 0x800D1D44, 0x11320001, 0x012B0000, 0x002ACD68, 0x800D1D48, 0x11330001, 0x012B0000,
        0x002ACD68, 0x800D1D4C, 0x11340001, 0x012B0000, 0x002ACD68, 0x800D1D50, 0x11940001, 0x012B0000,
        0x002ACD68, 0x800D1D24, 0x070F0001, 0x012B0000, 0x002ACD68, 0x800D1E88, 0x0BD90DFC, 0x00000000,
        0x00000000, 0x00000000, 0x002ACEE0, 0x800D1E88, 0x0BDA0DFC, 0x00000000, 0x00000000, 0x00000000,
        0x002ACEE0, 0x800D1E88, 0x0BDB0DFC, 0x00000000, 0x00000000, 0x00000000, 0x002ACEE0, 0x800D1E88,
        0x0BDC0DFC, 0x00000000, 0x00000000, 0x00000000, 0x002ACEE0, 0x800D1E88, 0x0BDD0DFC, 0x00000000,
        0x00000000, 0x00000000, 0x002ACEE0, 0x800D1E88, 0x0BDE0DFC, 0x00000000, 0x00000000, 0x00000000,
        0x002ACEE0, 0x800D1E88, 0x0BDF0DFC, 0x00000000, 0x00000000, 0x00000000, 0x002ACEE0, 0x800D1E88,
        0x0BE00DFC, 0x00000000, 0x00000000, 0x00000000, 0x002ACEE0, 0x800D1E88, 0x0BE10DFC, 0x00000000,
        0x00000000, 0x00000000, 0x002ACEE0, 0x800D1E88, 0x0BE20DFC, 0x00000000, 0x00000000, 0x00000000,
        0x002ACEE0, 0x800D1E88, 0x0BE30DFC, 0x00000000, 0x00000000, 0x00000000, 0x002ACEE0, 0x800D1E88,
        0x0BE40DFC, 0x00000000, 0x00000000, 0x00000000, 0x002ACEE0, 0x800D1E88, 0x0BE50DFC, 0x00000000,
        0x00000000, 0x00000000, 0x002ACEE0, 0x800D1E88, 0x0BE60DFC, 0x00000000, 0x00000000, 0x00000000,
        0x002ACEE0, 0x800D1E88, 0x0BE70DFC, 0x00000000, 0x00000000, 0x00000000, 0x002ACEE0, 0x800D1E88,
        0x0BE80DFC, 0x00000000, 0x00000000, 0x00000000, 0x002ACEE0, 0x6E6F6E65, 0x00000000,
    },
    {
        0x800C6234, 0x800C6230, 0x800C6220, 0x00000000,
    },
    { "", "" },
    {
        0x800C6244, 0x00000000,
    },
    {
        0x800C6258, 0x00000000,
    },
    "2 health\000\000\000",
    "10 health\000\000",
    "15 health\000\000",
    "25 health\000\000",
    "50 health\000\000",
    "full health",
    "ultra health\000\000\000",
    "1 life force\000\000\000",
    "10 life force\000\000",
    "invincibility\000\000",
    "plane walker\000\000\000",
    "flashlight\000",
    "flashlight battery\000",
    "InfraRed Goggles\000\000\000",
    "breath of life\000",
    "eye of truth\000\000\000",
    "leap of faith\000\000",
    "whispers\000\000\000",
    "heart of fire\000\000",
    "blue eagle feather\000",
    "grey eagle feather\000",
    "brown eagle feather",
    "purple eagle feather\000\000\000",
    "red eagle feather\000\000",
    "nuke weapon part\000\000\000",
    "Retaliation !\000\000",
    "Flag was claimed\000\000\000",
    "Flag was captured\000\000",
    "Flag returned\000\000",
    "The Power is Yours\000",
    "Function Not Available\000",
    "WARHAMMER\000\000",
    "RAPTOR CLAW",
    "MITE BITE\000\000",
    "BOOMERANG\000\000",
    "TEK CROSSBOW\000\000\000",
    "MAG 60\000",
    "SHOTGUN",
    "ASSAUlT RIFLE\000\000",
    "MINIGUN",
    "PLASMA RIFLE\000\000\000",
    "FREEZE GUN\000",
    "FLARE GUN\000\000",
    "GRENADES\000\000\000",
    "SCORPION\000\000\000",
    "NAPALM GEL\000",
    "EMACIATOR\000\000",
    "INFLATOR\000\000\000",
    "CHEST BURSTER\000\000",
    "CEREBRAL BORE\000\000",
    "PFM MINE\000\000\000",
    "IRON CLAW\000\000",
    "TELEPORT MINE\000\000",
    "SENTRY TURRET\000\000",
    "ATTRACT REMOVED",
    "ATTRACT MARKED\000",
    "REPULSE MARKED\000",
    "Joined Team Coyote\000",
    "Joined Team Bear\000\000\000",
    "Joined Team Cougar\000",
    "Joined Team Viper\000\000",
    "You fragged yourself.\000\000",
    "Mangled by %s.\000",
    "Fragged by %s.\000",
    "Smacked  by %s.",
    "%s obliterated you.",
    "%s butchered you.\000\000",
    "%s crushed you.",
    "Pounded by %s.\000",
    "your other left.\000\000\000",
    "Oops...",
    "Bad move...",
    "Um...  Watch your step?",
    "Oops...",
    "You were bested.\000\000\000",
    "Munch.\000",
    "Embryo Implanted\000\000\000",
    "Embryo Destroyed\000\000\000",
    "Smack %s\000\000\000",
    "or find Power Core\000",
    "Energy rounds\000\000",
    "Energy rounds\000\000",
    "Bullet rounds\000\000",
    "Bullet rounds\000\000",
    "Explosive rounds\000\000\000",
    "Explosive rounds\000\000\000",
    "Ammo pack\000\000",
    "bullet\000",
    "energy round\000\000\000",
    "explosive round",
    "cerebral bore\000\000",
    "pfm mine\000\000\000",
    "sentry turret\000\000",
    "iron claw\000\000",
    "teleport mine\000\000",
    "Slow Time...\000\000\000",
    "Blast Shield...",
    "Regeneration...",
    "Petrify...\000",
    "Damage Reversal...\000",
    "Invisibility...",
    "Life Force Vampire...\000\000",
    "Speed Burst...\000",
    "Teleportation...\000\000\000",
    "Teleported to safety...(?)\000",
    "Massive Damage...\000\000",
    "Invunerability...\000\000",
    "Bullet Shield...\000\000\000",
    "Energy Absorption...\000\000\000",
    "Something Else...\000\000",
    "Shield\000",
    "NOVICE\000",
    "NEWCOMER\000\000\000",
    "GRUNT\000\000",
    "SCOUT\000\000",
    "BRAVE\000\000",
    "TRACKER",
    "HUNTER\000",
    "WARRIOR",
    "DARKLING\000\000\000",
    "SEEKER\000",
    "ASSASSIN\000\000\000",
    "BANE\000\000\000",
    "WARLORD",
    "DEATHWIND\000\000",
    "CONQUEROR\000\000",
    "MASTER\000",
    "TYRANT\000",
    "WARSLAVE\000\000\000",
    "GODHAND",
    "CHIEFTAIN\000\000",
    "ACHIEVEMENT ON PROVING GROUNDS\000",
    "ACHIEVEMENT ON BASIC TRAINING\000\000",
    "ACHIEVEMENT ON CROSSROADS\000\000",
    "ACHIEVEMENT ON GRIM RETREAT",
    "ACHIEVEMENT ON CATHEDRAL\000\000\000",
    "ACHIEVEMENT ON FALLOUT\000",
    "ACHIEVEMENT ON BOXED SET\000\000\000",
    "ACHIEVEMENT ON DIRE STRAIGHT\000\000\000",
    "ACHIEVEMENT ON PREY",
    "ACHIEVEMENT ON WAREHOUSE\000\000\000",
    "ACHIEVEMENT ON WATER TEMPLE",
    "ACHIEVEMENT ON BOMB SHELTER",
    "ACHIEVEMENT ON TEMPERED",
    "ACHIEVEMENT ON EARTH TEMPLE",
    "ACHIEVEMENT ON FIRE TEMPLE\000",
    "ACHIEVEMENT ON MYSTIC\000\000",
    "ACHIEVEMENT ON BOTTLENECK\000\000",
    "ACHIEVEMENT ON TIGHTROPE\000\000\000",
    "ACHIEVEMENT ON THE PIT\000",
    "ACHIEVEMENT ON LEAP OF FAITH\000\000\000",
    "ACHIEVEMENT ON WICKED DANCE",
    "ACHIEVEMENT ON BUNKER\000\000",
    "ACHIEVEMENT ON AMPHITHEATER",
    "ACHIEVEMENT ON FIRE WALKER\000",
    "ACHIEVEMENT ON CRYPTS\000\000",
    "ACHIEVEMENT ON BREAKDOWN\000\000\000",
    "ACHIEVEMENT ON RETALIATION\000",
    "ACHIEVEMENT ON HOPELESS",
    "ACHIEVEMENT ON MATRIX\000\000",
    "ACHIEVEMENT ON FATHOM\000\000",
    "ACHIEVEMENT ON THE PEDESTAL",
    "ACHIEVEMENT ON DEFCON 5",
    "ACHIEVEMENT ON SPIRIT TEMPLE\000\000\000",
    "ACHIEVEMENT ON STRONGHOLD\000\000",
    "ACHIEVEMENT ON COURTYARD\000\000\000",
    "ACHIEVEMENT ON STARLIGHT\000\000\000",
    "ATTAINED 15 FRAGS IN 5 MINUTES\000",
    "ATTAINED 25 FRAGS IN 10 MINUTES",
    "NOT GETTING ANY FRAGS\000\000",
    "KILLING YOURSELF 5 TIMES\000\000\000",
    "COMING IN LAST\000",
    "TOTAL FRAG AWARD\000\000\000",
    "TOTAL BEING KILLED AWARD\000\000\000",
    "SNIPING 10 PEOPLE IN A ROUND\000\000\000",
    "NOT BEING KILLED IN A ROUND",
    "DEFEATED BASTILLE\000\000",
    "DEFEATED SYRA\000\000",
    "DEFEATED SYMBIONT\000\000",
    "DEFEATED TAL SET\000\000\000",
    "BEATING THE COOPERATIVE SCENARIO\000\000\000",
    "<EMPTY>",
    "<NEW PLAYER>\000\000\000",
    "TUROK\000\000",
    "WARRIOR",
    "MASTER\000",
    "ADON\000\000\000",
    "SEEKER\000",
    "HUNTRESS\000\000\000",
    "CAMPAIN",
    "SLAVER\000",
    "TYRANT\000",
    "FIREBORN\000\000\000",
    "ICELORD",
    "ENTRAIL",
    "MITES\000\000",
    "COMPIES",
    "TEDDIES",
    "JUGGNAUT\000\000\000",
    "SLOTH\000\000",
    "MAULER\000",
    "DRONE\000\000",
    "GRUNT\000\000",
    "SLAVE\000\000",
    "SOLDIER",
    "CAPTAIN",
    "KING\000\000\000",
    "BASTILLE\000\000\000",
    "TAL SET",
    "SYRA\000\000\000",
    "SYMBIONT\000\000\000",
    "GUARDIAN\000\000\000",
    "RAVAGE\000",
    "CYCLOPS",
    "LORDDEAD\000\000\000",
    "MAGGOT\000",
    "VILE\000\000\000",
    "ELITE\000\000",
    "BIOBOT\000",
    "KILLBOT",
    "DEATH\000\000",
    "REAPER\000",
    "MAW",
    "RAPTOR\000",
    "SLAG\000\000\000",
    "CLAW\000\000\000",
    "WARCLUBS\000\000\000",
    "TUROK\000\000",
    "MANTID DRONE\000\000\000",
    "CAMPAIGNER\000",
    "FIREBORN\000\000\000",
    "MANTID SOLDIER\000",
    "ADON\000\000\000",
    "LORD OF THE DEAD\000\000\000",
    "ELITE GUARD",
    "GUARDIAN\000\000\000",
    "JUGGERNAUT\000",
    "OBLIVION SPAWN\000",
    "BASTILLE\000\000\000",
    "SYRA\000\000\000",
    "SYMBIONT\000\000\000",
    "TAL SET",
    "RAPTOR\000",
    "MANTID MITES\000\000\000",
    "capture the flag %d time\000\000\000",
    "capture the flag %d times\000\000",
    "acquire %d team captures\000\000\000",
    "tag the monkey %d time\000",
    "tag the monkey %d times",
    "acquire %d creature tags\000\000\000",
    "acquire %d frag",
    "acquire %d frags\000\000\000",
    "acquire %d team frag\000\000\000",
    "acquire %d team frags\000\000",
    "in %02d seconds or less",
    "in %d minute and %02d seconds or less\000\000",
    "in %d minutes and %02d seconds or less\000",
    "in %d minute or less\000\000\000",
    "in %d minutes or less\000\000",
    "with %d life\000\000\000",
    "with %d lives\000\000",
    "defeat %s\000\000",
    "defeat both %s and %s\000\000",
    "every man for themselves\000\000\000",
    "EASY\000\000\000",
    "MEDIUM\000",
    "HARD\000\000\000",
    "OFF",
    "ON\000",
    "RED",
    "GREEN\000\000",
    "HORIZONTAL\000",
    "VERTICAL\000\000\000",
    "LOREZ\000\000",
    "HIREZ\000\000",
    "LETTERBOX\000\000",
    "NO\000",
    "YES",
    "NOVICE\000",
    "EASY\000\000\000",
    "NORMAL\000",
    "VETERAN",
    "EXPERT\000",
    "ARCADE\000",
    "WHEEL\000\000",
    "TAP",
    "MIXED\000\000",
    "CONTROLLER %d\000\000",
    "CTF",
    "TBL",
    "BL\000",
    "FT\000",
    "GAUNTLET\000\000\000",
    "FRAG FEST\000\000",
    "TIME TRIAL\000",
    "PLAYER%d\000\000\000",
    "ACQUIRED EAGLE TALISMAN. 1 UP!\000",
    "ACQUIRED HALF EAGLE TALISMAN. ANoTHER GIVES 1 UP\000\000\000",
    "ACQUIRED THE OTHER EAGLE TALISMAN, GAINED 1 UP!",
    "ACQUIRED BEAR TALISMAN. EXPLOSIVE AMMO UP 5",
    "ACQUIRED COYOTE TALISMAN. BULLET AMMO UP 50",
    "ACQUIRED COUGAR TALISMAN. ENERGY AMMO UP 50",
    "ACQUIRED VIPER TALISMAN. HEAlTH MAX UP 5\000\000\000",
    "ACQUIRED COOPERATIVE TALISMAN\000\000",
    "ACQUIRED MINIGAME ICON\000",
    "ACQUIRED ASSAULT RIFLE\000",
    "ACQUIRED ASSAULT RIFLE RAPID FIRE UPGRADE\000\000",
    "ACQUIRED TEK CROSS BOW SNIPER SCOPE",
    "ACQUIRED GRENADE LAUNCHER\000\000",
    "ACQUIRED GRENADE LAUNCHER UPGRADE\000\000",
    "ACQUIRED PLASMA RIFLE\000\000",
    "ACQUIRED PLASMA RIFLE SCOPE",
    "ACQUIRED ACID SPIT ATTACK\000\000",
    "ACQUIRED JUMP CLAW ATTACK\000\000",
    "ACQUIRED RADIOACTIVE FLARE GUN\000",
    "ACQUIRED RADIOACTIVE FLARE GUN UPGRADE\000",
    "ACQUIRED SCORPION LAUNCHER\000",
    "ACQUIRED SCORPION LAUNCHER MAGNET UPGRADE\000\000",
    "ACQUIRED FREEZE GUN",
    "ACQUIRED FREEZE GUN UPGRADE",
    "ACQUIRED NAPALM GEL",
    "ACQUIRED MAG 60 LASER SIGHT UPGRADE",
    "ACQUIRED CHESTBURSTER\000\000",
    "ACQUIRED INFLATOR\000\000",
    "ACQUIRED INFLATOR UPGRADE\000\000",
    "ACQUIRED BOOMERANG\000",
    "ACQUIRED BOOMERANG UPGRADE\000",
    "ACQUIRED MINIGUN\000\000\000",
    "ACQUIRED MINIGUN PERSONAL SHIELD UPGRADE\000\000\000",
    "ACQUIRED SHOTGUN STREETSWEEPER UPGRADE\000",
    "ACQUIRED EMACIATOR\000",
    "ACQUIRED EMACIATOR UPGRADE\000",
    "ACQUIRED WARHAMMER ROCKET UPGRADE\000\000",
    "YOU HAVE UNLOCKED %s\000\000\000",
    "MISSION FAILED\000",
    "ITEM PREVIOUSLY ACQUIRED\000\000\000",
    "TEAM\000\000\000",
    "HIT%\000\000\000",
    "TAGS\000\000\000",
    "FLAGS\000\000",
    "CONGRATULATIONS! YOU HAVE COMPLETED FRAG FEST\000\000",
    "CONGRATULATIONS! YOU HAVE COMPLETED TIME TRIAL\000",
    "ENGLISH",
    "pistol clip (10 rounds)",
    "rifle clip (10 rounds)\000",
    "difficulty   :     easy",
    "difficulty   :   normal",
    "difficulty   :     hard",
    "control type :   expert",
    "control type :   arcade",
    "control type :   ??????",
    "control side :     left",
    "control side :    right",
    "look spring  :       on",
    "look spring  :      off",
    "auto aim     :       on",
    "auto aim     :      off",
    "blood color  :      off",
    "blood color  :      red",
    "blood color  :    green",
    "2 plyr layout:     horz",
    "2 plyr layout:     vert",
    "opacity      :    clear",
    "opacity      :   opaque",
    "opacity      :         ",
    "control stick horz:norm",
    "control stick horz:    ",
    "control stick vert:norm",
    "control stick vert:    ",
    "Weapon Select:    quick",
    "Weapon Select:     norm",
    "Resolution   :   lo-rez",
    "Resolution   :   hi-rez",
    "Resolution   :hi-rez-lb",
    "Resolution   :sm-lo-rez",
    "Resolution   :lo-rez-lb",
    "brightness   :     norm",
    "brightness   :         ",
    "language     :  english",
    "go back",
    { "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" },
    "choose\000",
    "blue blood\000",
    "red blood\000\000",
    "final score",
    "blue blood score :    \000",
    " red blood score :    \000",
    "please wait.....\000\000\000",
    "paused\000",
    "resume game",
    "mission status\000",
    "mission objectives\000",
    "inventory\000\000",
    "load\000\000\000",
    "options",
    "cheats\000",
    "quit\000\000\000",
    "inventory\000\000",
    "ok\000",
    "RAGE WARS\000\000",
    "TUROK 2",
    "51\000",
    "NRWE\000\000\000",
    { "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" },
    "OTHER GAME\000",
    { "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" },
    "note info\000\000",
    "delete note",
    "difficulty :  easy\000",
    "difficulty :normal\000",
    "difficulty :  hard\000",
    "health     :      \000",
    "lives      :      \000",
    "time :000.00.00",
    "note info\000\000",
    "delete note",
    "delete note",
    "name             ext \000\000",
    "                     \000\000",
    "name  :            ",
    "type  :            ",
    "frags :            ",
    "rank  :            ",
    "load?\000\000",
    "delete?",
    "delete?",
    "error\000\000",
    "important\000\000",
    "ok\000",
    { "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" },
    "   save",
    "   load",
    " health",
    "   ammo",
    "go back",
    { "", "", "", "", "", "", "", "", "", "" },
    "pmf shot!\000\000",
    "body shot!\000",
    "head shot!\000",
    "arm shot!\000\000",
    "edit\000\000\000",
    {
        0x02000000,
    },
    {
        0x03000000,
    },
    {
        0x04000000,
    },
    "tagged by \000",
    "you tagged ",
    "killed by \000",
    "you killed ",
    "you killed yourself",
    "you lost the flag!!!\000\000\000",
    "He dropped the flag!!!\000",
    "are you sure?\000\000",
    "you want to",
    "yes",
    "no\000",
    "cheats\000",
    "load\000\000\000",
    "save\000\000\000",
    "enter cheat",
    "join now\000\000\000",
    "waiting..\000\000",
    "connect..\000\000",
    "go back",
    "continue ?\000",
    "game over\000\000",
    "time : xx\000\000",
    "done\000\000\000",
    "new cheat enabled\000\000",
    "invincibility activated",
    "infinite lives activated\000\000\000",
    "all weapons activated\000\000",
    "unlimited ammo activated\000\000\000",
    "all keys activated\000",
    "big head mode activated",
    "tiny mode activated",
    "stick mode activated\000\000\000",
    "big hands and feet mode activated\000\000",
    "pen and ink mode activated\000",
    "gouraud mode activated\000",
    "juans cheat activated\000\000",
    "zach attack cheat activated",
    "all map activated\000\000",
    "blackout mode activated",
    "mmmm... tasty frooty stripes\000\000\000",
    "warp level 1 activated\000",
    "warp level 2 activated\000",
    "warp level 3 activated\000",
    "warp level 4 activated\000",
    "warp level 5 activated\000",
    "warp level 6 activated\000",
    "warp queen boss activated\000\000",
    "warp blind one boss activated\000\000",
    "warp mother boss activated\000",
    "warp primagen boss activated\000\000\000",
    "warp credits activated\000",
    "invincibility         :  on",
    "invincibility         : off",
    "infinite lives        :  on",
    "infinite lives        : off",
    "all weapons           :  on",
    "all weapons           : off",
    "unlimited ammo        :  on",
    "unlimited ammo        : off",
    "all special objects   :  on",
    "all special objects   : off",
    "big head mode         :  on",
    "big head mode         : off",
    "tiny mode             :  on",
    "tiny mode             : off",
    "stick mode            :  on",
    "stick mode            : off",
    "big hands / feet mode :  on",
    "big hands / feet mode : off",
    "pen and ink mode      :  on",
    "pen and ink mode      : off",
    "gouraud mode          :  on",
    "gouraud mode          : off",
    "juans cheat           :  on",
    "juans cheat           : off",
    "zach attack cheat     :  on",
    "zach attack cheat     : off",
    "all map               :  on",
    "all map               : off",
    "blackout              :  on",
    "blackout              : off",
    "frooty stripes        :  on",
    "frooty stripes        : off",
    "warp:          port of adia",
    "warp:        river of souls",
    "warp:         death marshes",
    "warp:lair of the blind ones",
    "warp:   hive of the mantids",
    "warp:  primagen's lightship",
    "warp:            queen boss",
    "warp:        blind one boss",
    "warp:           mother boss",
    "warp:         primagen boss",
    "warp:               credits",
    "you fragged",
    "you tagged\000",
    "totals\000",
    "one     :0000                \000\000",
    "two     :0000                \000\000",
    "three   :0000                \000\000",
    "four    :0000                \000\000",
    "tags    :0000                \000\000",
    "frags   :0000                \000\000",
    "deaths  :0000                \000\000",
    "suicides:0000\000\000",
    "one     :0000                \000\000",
    "two     :0000                \000\000",
    "three   :0000                \000\000",
    "four    :0000                \000\000",
    "tags    :0000\000\000",
    "frags   :0000\000\000",
    "deaths  :0000\000\000",
    "suicides:0000\000\000",
    "one     :0000                \000\000",
    "two     :0000                \000\000",
    "three   :0000                \000\000",
    "four    :0000                \000\000",
    "tags    :0000\000\000",
    "frags   :0000\000\000",
    "deaths  :0000\000\000",
    "suicides:0000\000\000",
    "one     :0000                \000\000",
    "two     :0000                \000\000",
    "three   :0000                \000\000",
    "four    :0000                \000\000",
    "tags    :0000\000\000",
    "frags   :0000\000\000",
    "deaths  :0000\000\000",
    "suicides:0000\000\000",
    "player 1\000\000\000",
    "player 2\000\000\000",
    "player 3\000\000\000",
    "player 4\000\000\000",
    "single\000",
    "new game\000\000\000",
    "load\000\000\000",
    "multi\000\000",
    "deathmatch\000",
    "select game type\000\000\000",
    "blood lust\000",
    "blood lust\000",
    "timed game       :none\000",
    "frag limit       :none\000",
    "level:          random\000",
    "level:   experimentata\000",
    "level:  moonlit mayhem\000",
    "level: close quartered\000",
    "level:  vulcan's forge\000",
    "level:   teleportastic\000",
    "level:     mirrororrim\000",
    "level:fish in a barrel\000",
    "level:       h 2 whoa!\000",
    "level:        escheria\000",
    "level:      mosh crypt\000",
    "level:   squares cubed\000",
    "level:     crazy eight\000",
    "level:        bullseye\000",
    "texture set:    castle\000",
    "texture set:steel mill\000",
    "texture set:  oak fort\000",
    "texture set: catacombs\000",
    "texture set: jailhouse\000",
    "texture set:  big city\000",
    "texture set:red dragon\000",
    "texture set: paintball\000",
    "texture set:  mr happy\000",
    "crosshairs       :  on\000",
    "crosshairs       : off\000",
    "start game\000",
    "go back",
    "frag tag\000\000\000",
    "frag tag\000\000\000",
    "tag limit        :none\000",
    "level:       madhouse!\000",
    "level:            snap\000",
    "level:sneaks n ladders\000",
    "level:      primattica\000",
    "level:       crossfire\000",
    "level:  y.n.g.w.t.s.f.\000",
    "team blood\000",
    "customize weapons\000\000",
    "charge dart rifle : on\000",
    "charge dart rifle :off\000",
    "firestorm         : on\000",
    "firestorm         :off\000",
    "assault rifle     : on\000",
    "assault rifle     :off\000",
    "plasma rifle      : on\000",
    "plasma rifle      :off\000",
    "cerebral bore     : on\000",
    "cerebral bore     :off\000",
    "grenade launcher  : on\000",
    "grenade launcher  :off\000",
    "scorpion launcher : on\000",
    "scorpion launcher :off\000",
    "torpedo launcher  : on\000",
    "torpedo launcher  :off\000",
    "training\000\000\000",
    "level      :    random\000",
    "level      :   archery\000",
    "level      :  shooting\000",
    "level      :decathalon\000",
    "no of laps :          \000",
    "start game\000",
    "go back",
    "load\000\000\000",
    "options",
    "cheats\000",
    "check point",
    "save point\000",
    "sound options\000\000",
    "music volume  :   off\000\000",
    "music volume  :   max\000\000",
    "music volume  :  norm\000\000",
    "music volume  :      \000\000",
    "sfx volume    :   off\000\000",
    "sfx volume    :   max\000\000",
    "sfx volume    :  norm\000\000",
    "sfx volume    :      \000\000",
    "speech volume :   off\000\000",
    "speech volume :   max\000\000",
    "speech volume :  norm\000\000",
    "speech volume :      \000\000",
    "music         :  none\000\000",
    "music         :      \000\000",
    "index        :  none\000\000\000",
    "speech       :  none\000\000\000",
    "mission complete.\000\000",
    "mission failed.",
    "defend the totem\000\000\000",
    "player speed :        \000",
    "player speed : default\000",
    "default",
    "low health\000",
    " \000\000",
    "0\000\000",
    "1\000\000",
    "2\000\000",
    "3\000\000",
    "4\000\000",
    "5\000\000",
    "6\000\000",
    "7\000\000",
    "8\000\000",
    "9\000\000",
    {
        0x800C71D8, 0x800C6230, 0x800C71C8, 0x800C71BC, 0x800C6230, 0x800C71AC, 0x800C7190, 0x800C6230,
        0x800C6230, 0x800C7184, 0x800C7174, 0x800C6230, 0x800C6230, 0x800C7160, 0x800C7144, 0x800C7128,
        0x800C7104, 0x800C70EC, 0x800C70D4, 0x800C70BC, 0x800C7094, 0x800C7070, 0x800C704C, 0x800C7030,
        0x800C700C, 0x800C6FF4, 0x800C6FCC, 0x800C6FA8, 0x800C6230, 0x800C6230, 0x800C6F80, 0x800C6230,
        0x800C6F70, 0x800C6F60, 0x800C6F50, 0x800C6F44, 0x800C6F2C, 0x800C6230, 0x800C6230, 0x800C6F00,
        0x800C6230, 0x800C6EF0, 0x800C6EE4, 0x800C6ED8, 0x800C6ECC, 0x800C6EBC, 0x800C6230, 0x800C6230,
        0x800C6E90, 0x800C6230, 0x800C6E7C, 0x800C6E6C, 0x800C6230, 0x800C6230, 0x800C6E44, 0x800C6230,
        0x800C6E34, 0x800C6E24, 0x800C6E18, 0x800C6230, 0x800C6230, 0x800C6DF0, 0x800C6230, 0x800C6DE4,
        0x800C6DD8, 0x800C6230, 0x800C6DC8, 0x800C6DBC, 0x800C6230, 0x800C6230, 0x800C6D90, 0x800C6230,
        0x800C6D80, 0x800C6D70, 0x800C6D60, 0x800C6D50, 0x800C6D44, 0x800C6D38, 0x800C6D28, 0x800C6230,
        0x800C6230, 0x800C6D00, 0x800C6230, 0x800C6CE8, 0x800C6CD0, 0x800C6CBC, 0x800C6CA0, 0x800C6C7C,
        0x800C6C5C, 0x800C6C38, 0x800C6C20, 0x800C6C04, 0x800C6BE0, 0x800C6230, 0x800C6230, 0x800C6BB4,
        0x800C6230, 0x800C6B94, 0x800C6B84, 0x800C6230, 0x800C6B70, 0x800C6B60, 0x800C6230, 0x800C6B40,
        0x800C6B2C, 0x800C6230, 0x800C6B18, 0x800C6E7C, 0x800C6230, 0x800C6B08, 0x800C6E34, 0x800C6230,
        0x800C6AE8, 0x800C6AD8, 0x800C6230, 0x800C6230, 0x800C6AB0, 0x800C6230, 0x800C6A88, 0x800C6A7C,
        0x800C6230, 0x800C6A60, 0x800C6A54, 0x800C6230, 0x800C6A40, 0x800C6A30, 0x800C6230, 0x800C6A10,
        0x800C69FC, 0x800C6230, 0x800C6230, 0x800C69CC, 0x800C6230, 0x800C69A0, 0x800C6974, 0x800C6230,
        0x800C6230, 0x800C6968, 0x800C695C, 0x800C6230, 0x800C6230, 0x800C6948, 0x800C6938, 0x800C6928,
        0x800C6230, 0x800C6230, 0x800C6910, 0x800C6900, 0x800C6230, 0x800C6230, 0x800C6DE4, 0x800C68EC,
        0x800C6230, 0x800C6230, 0x800C68DC, 0x800C68D0, 0x800C68C4, 0x800C6230, 0x800C6230, 0x800C68B0,
        0x800C68A4, 0x800C6894, 0x800C6230, 0x800C6230, 0x800C6884, 0x800C6878, 0x800C6868, 0x800C6230,
        0x800C6230, 0x800C6858, 0x800C684C, 0x800C6840, 0x800C6230, 0x800C6230, 0x800C6D90, 0x800C6830,
        0x800C6820, 0x800C6814, 0x800C6804, 0x800C67F4, 0x800C67E4, 0x800C67D4, 0x800C67C8, 0x800C67B8,
        0x800C67AC, 0x800C679C, 0x800C678C, 0x800C677C, 0x800C6770, 0x800C6230, 0x800C6758, 0x800C674C,
        0x800C6230, 0x800C6738, 0x800C6728, 0x800C6230, 0x800C671C, 0x800C6710, 0x800C6700, 0x800C66F0,
        0x800C66E0, 0x800C6230, 0x800C66C4, 0x800C66B8, 0x800C6230, 0x800C66A0, 0x800C6690, 0x800C6680,
        0x800C6230, 0x800C6674, 0x800C6660, 0x800C6230, 0x800C6644, 0x800C6634, 0x800C6230, 0x800C6620,
        0x800C6614, 0x800C6230, 0x800C6604, 0x800C65F8, 0x800C6230, 0x800C6230, 0x800C65D0, 0x800C6230,
        0x800C65AC, 0x800C6594, 0x800C6578, 0x800C655C, 0x800C6540, 0x800C6524, 0x800C6230, 0x800C64FC,
        0x800C64EC, 0x800C64CC, 0x800C64A8, 0x800C6488, 0x800C6464, 0x800C6444, 0x800C6420, 0x800C63FC,
        0x800C63E8, 0x800C63C0, 0x800C63B0, 0x800C639C, 0x800C6378, 0x800C6358, 0x800C6330, 0x800C630C,
        0x800C62F0, 0x800C62CC, 0x800C62C0, 0x800C62A4, 0x800C6294, 0x800C6230, 0x800C6230, 0x800C6230,
        0x800C6230, 0x800C6230, 0x800C6230, 0x800C6230, 0x800C6230, 0x800C6230, 0x800C626C, 0x00000000,
        0x00000000, 0x800D1CA8, 0x800CE2E0,
    },
};
#endif
#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#ifdef VERSION_DE
struct {
    unsigned int w0[299];
    unsigned char b1[2624];
    unsigned int w2[10];
    unsigned char b3[1796];
    unsigned int w4[3];
    unsigned char b5[56];
    unsigned int w6;
    unsigned char b7[10188];
    unsigned int w8[3];
    unsigned char b9[3828];
    unsigned int w10[266];
} k_SkyPostscaledscreenmessageEncodedWords = {
    {
        0x00000003, 0x00000000, 0x00000000, 0x00000002, 0x00000000, 0x00000003, 0x00000000, 0x00000000,
        0x00000002, 0x00000000, 0x00000003, 0x00000000, 0xFFFFFFD8, 0x00000002, 0x00000000, (unsigned int)g_weaponLockedNoticeText + 0x4C,
        0x084B0E0C, 0xFFFF0000, 0x00120003, 0x00010000, PACKED_CALLBACK_LOW(Pickup_HandlePowerWeaponPickupEntryVariant1), (unsigned int)g_weaponLockedNoticeText + 0x50, 0x084C0E0C,
        0xFFFF0000, 0x00130004, 0x00030000, PACKED_CALLBACK_LOW(Pickup_HandlePowerWeaponPickupEntryVariant1), (unsigned int)g_weaponLockedNoticeText + 0x54, 0x084D0E0C, 0xFFFF0000,
        0x00140006, 0x00010000, PACKED_CALLBACK_LOW(Pickup_HandlePowerWeaponPickupEntryVariant1), (unsigned int)g_weaponLockedNoticeText + 0x5C, 0x084F0E0C, 0xFFFF0000, 0x00150005,
        0x00010000, PACKED_CALLBACK_LOW(Pickup_HandlePowerWeaponPickupEntryVariant1), (unsigned int)&g_commonConstant.energiestETextLinks, 0x0BC40DB6, 0x00000000, 0x00010064,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoEntryVariant1), (unsigned int)&g_commonConstant.energiestE2TextLinks, 0x0BC50DB6, 0x00000000, 0x00010064, PACKED_CALLBACK_LOW(Pickup_ApplyAmmoEntryVariant1),
        (unsigned int)&g_commonConstant.schuTextLinks, 0x0BC60DAC, 0x00000000, 0x00000032, PACKED_CALLBACK_LOW(Pickup_ApplyAmmoEntryVariant1), (unsigned int)&g_commonConstant.schu2TextLinks, 0x0BC70DAC,
        0x00000000, 0x00000032, PACKED_CALLBACK_LOW(Pickup_ApplyAmmoEntryVariant1), (unsigned int)&g_commonConstant.explosivgeschosseTextLinks, 0x0BC80DC0, 0x00000000, 0x00020005,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoEntryVariant1), (unsigned int)&g_commonConstant.explosivgeschosse2TextLinks, 0x0BC90DC0, 0x00000000, 0x00020005, PACKED_CALLBACK_LOW(Pickup_ApplyAmmoEntryVariant1),
        (unsigned int)&g_introTextLines + 0xC, 0x06A50001, 0x00000000, 0x00000002, 0x000000C8, PACKED_CALLBACK_LOW(Pickup_ApplyHealthEntryVariant1), (unsigned int)&g_introTextLines + 0x10,
        0x06A60001, 0x00000000, 0x0000000A, 0x00000064, PACKED_CALLBACK_LOW(Pickup_ApplyHealthEntryVariant1), (unsigned int)&g_introTextLines + 0x20, 0x06A70001,
        0x012B0000, 0x00000064, 0x00000064, PACKED_CALLBACK_LOW(Pickup_ApplyHealthEntryVariant1), (unsigned int)&g_introTextLines + 0x24, 0x06A80001, 0x012B0000,
        0x00000064, 0x000000C8, PACKED_CALLBACK_LOW(Pickup_ApplyHealthEntryVariant1), (unsigned int)&g_introTextLines + 0x10, 0x06B80001, 0x00000000, 0x0000000A,
        0x00000064, PACKED_CALLBACK_LOW(Pickup_ApplyHealthEntryVariant1), (unsigned int)&g_introTextLines + 0x14, 0x06B90DE8, 0x00000000, 0x0000000F, 0x00000064,
        PACKED_CALLBACK_LOW(Pickup_ApplyHealthEntryVariant1), (unsigned int)&g_introTextLines + 0x18, 0x06BA0DE8, 0x00000000, 0x00000019, 0x00000064,
        PACKED_CALLBACK_LOW(Pickup_ApplyHealthEntryVariant1), (unsigned int)&g_introTextLines + 0x1C, 0x06BB0DF2, 0x00000000, 0x00000032, 0x00000064,
        PACKED_CALLBACK_LOW(Pickup_ApplyHealthEntryVariant1), 0x00000000, 0x06A90001, 0x00000000, 0x00010000, (unsigned int)g_Pickup_ApplyLifePointsEncodedCallbackEntry_de,
        0x00000000, 0x06AA0001, 0x00000000, 0x000A0000, (unsigned int)g_Pickup_ApplyLifePointsEncodedCallbackEntry_de, (unsigned int)&g_introTextLines + 0x70, 0x0BD60E0E,
        0x00000000, PACKED_CALLBACK_LOW(Pickup_ApplySpecialPickupEntryVariant1), (unsigned int)g_pickupFlagCarriedText, 0x0BD702C6, 0x00000000, PACKED_CALLBACK_LOW(Pickup_ApplySpecialPickupEntryVariant1),
        (unsigned int)&g_gameplayResetMessage + 0x4, 0x0BD80DCA, 0x00000000, PACKED_CALLBACK_LOW(Pickup_ApplySpecialPickupEntryVariant1), (unsigned int)&g_introTextLines + 0x30, 0x07080001, 0x012B0000,
        0x002ACE38, (unsigned int)&g_introTextLines + 0x34, 0x07090001, 0x012B0000, 0x002ACE38, (unsigned int)&g_introTextLines + 0x38, 0x070A0001, 0x012B0000,
        0x002ACE38, (unsigned int)&g_introTextLines + 0x3C, 0x070B0001, 0x012B0000, 0x002ACE38, (unsigned int)&g_introTextLines + 0x44, 0x111C0001, 0x012B0000,
        0x002ACE38, (unsigned int)&g_introTextLines + 0x48, 0x111D0001, 0x012B0000, 0x002ACE38, (unsigned int)&g_introTextLines + 0x4C, 0x111E0001, 0x012B0000,
        0x002ACE38, (unsigned int)&g_introTextLines + 0x50, 0x111F0001, 0x012B0000, 0x002ACE38, (unsigned int)&g_introTextLines + 0x54, 0x11200001, 0x012B0000,
        0x002ACE38, (unsigned int)&g_introTextLines + 0x58, 0x11300001, 0x012B0000, 0x002ACE38, (unsigned int)&g_introTextLines + 0x5C, 0x11310001, 0x012B0000,
        0x002ACE38, (unsigned int)&g_introTextLines + 0x60, 0x11320001, 0x012B0000, 0x002ACE38, (unsigned int)&g_introTextLines + 0x64, 0x11330001, 0x012B0000,
        0x002ACE38, (unsigned int)&g_introTextLines + 0x68, 0x11340001, 0x012B0000, 0x002ACE38, (unsigned int)&g_introTextLines + 0x6C, 0x11940001, 0x012B0000,
        0x002ACE38, (unsigned int)&g_introTextLines + 0x40, 0x070F0001, 0x012B0000, 0x002ACE38, (unsigned int)&g_commonConstant.munitionTextLinks, 0x0BD90DFC, 0x00000000,
        0x00000000, 0x00000000, PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant1), (unsigned int)&g_commonConstant.munitionTextLinks, 0x0BDA0DFC, 0x00000000, 0x00000000,
        0x00000000, PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant1), (unsigned int)&g_commonConstant.munitionTextLinks, 0x0BDB0DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant1), (unsigned int)&g_commonConstant.munitionTextLinks, 0x0BDC0DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant1), (unsigned int)&g_commonConstant.munitionTextLinks, 0x0BDD0DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant1), (unsigned int)&g_commonConstant.munitionTextLinks, 0x0BDE0DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant1), (unsigned int)&g_commonConstant.munitionTextLinks, 0x0BDF0DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant1), (unsigned int)&g_commonConstant.munitionTextLinks, 0x0BE00DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant1), (unsigned int)&g_commonConstant.munitionTextLinks, 0x0BE10DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant1), (unsigned int)&g_commonConstant.munitionTextLinks, 0x0BE20DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant1), (unsigned int)&g_commonConstant.munitionTextLinks, 0x0BE30DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant1), (unsigned int)&g_commonConstant.munitionTextLinks, 0x0BE40DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant1), (unsigned int)&g_commonConstant.munitionTextLinks, 0x0BE50DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant1), (unsigned int)&g_commonConstant.munitionTextLinks, 0x0BE60DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant1), (unsigned int)&g_commonConstant.munitionTextLinks, 0x0BE70DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant1), (unsigned int)&g_commonConstant.munitionTextLinks, 0x0BE80DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant1),
    },
    {
        0x6B, 0x65, 0x69, 0x6E, 0x65, 0x00, 0x00, 0x00, 0x77, 0x61, 0x72, 0x6E, 0x2D, 0x6C, 0x65, 0x75,
        0x63, 0x68, 0x74, 0x75, 0x72, 0x6D, 0x20, 0x61, 0x6B, 0x74, 0x69, 0x76, 0x69, 0x65, 0x72, 0x74,
        0x2E, 0x00, 0x00, 0x00, 0x61, 0x6C, 0x6C, 0x65, 0x20, 0x77, 0x61, 0x72, 0x6E, 0x2D, 0x6C, 0x65,
        0x75, 0x63, 0x68, 0x74, 0x74, 0xFC, 0x72, 0x6D, 0x65, 0x20, 0x61, 0x6B, 0x74, 0x69, 0x76, 0x69,
        0x65, 0x72, 0x74, 0x2E, 0x20, 0x6D, 0x69, 0x73, 0x73, 0x69, 0x6F, 0x6E, 0x20, 0x62, 0x65, 0x65,
        0x6E, 0x64, 0x65, 0x74, 0x2E, 0x00, 0x00, 0x00, 0x6B, 0x69, 0x6E, 0x64, 0x20, 0x67, 0x65, 0x72,
        0x65, 0x74, 0x74, 0x65, 0x74, 0x2E, 0x00, 0x00, 0x6B, 0x69, 0x6E, 0x64, 0x65, 0x72, 0x20, 0x69,
        0x6E, 0x20, 0x73, 0x69, 0x63, 0x68, 0x65, 0x72, 0x68, 0x65, 0x69, 0x74, 0x2E, 0x20, 0x0A, 0x6D,
        0x69, 0x73, 0x73, 0x69, 0x6F, 0x6E, 0x20, 0x62, 0x65, 0x65, 0x6E, 0x64, 0x65, 0x74, 0x2E, 0x00,
        0x65, 0x6D, 0x62, 0x72, 0x79, 0x6F, 0x20, 0x76, 0x65, 0x72, 0x6E, 0x69, 0x63, 0x68, 0x74, 0x65,
        0x74, 0x2E, 0x00, 0x00, 0x61, 0x6C, 0x6C, 0x65, 0x20, 0x65, 0x6D, 0x62, 0x72, 0x79, 0x6F, 0x73,
        0x20, 0x76, 0x65, 0x72, 0x6E, 0x69, 0x63, 0x68, 0x74, 0x65, 0x74, 0x2E, 0x20, 0x0A, 0x6D, 0x69,
        0x73, 0x73, 0x69, 0x6F, 0x6E, 0x20, 0x62, 0x65, 0x65, 0x6E, 0x64, 0x65, 0x74, 0x2E, 0x00, 0x00,
        0x6B, 0x72, 0x61, 0x66, 0x74, 0x66, 0x65, 0x6C, 0x64, 0x67, 0x65, 0x6E, 0x65, 0x72, 0x61, 0x74,
        0x6F, 0x72, 0x20, 0x7A, 0x65, 0x72, 0x73, 0x74, 0xF6, 0x72, 0x74, 0x2E, 0x00, 0x00, 0x00, 0x00,
        0x68, 0x61, 0x75, 0x70, 0x74, 0x63, 0x6F, 0x6D, 0x70, 0x75, 0x74, 0x65, 0x72, 0x20, 0x7A, 0x65,
        0x72, 0x73, 0x74, 0xF6, 0x72, 0x74, 0x2E, 0x20, 0x0A, 0x6D, 0x69, 0x73, 0x73, 0x69, 0x6F, 0x6E,
        0x20, 0x62, 0x65, 0x65, 0x6E, 0x64, 0x65, 0x74, 0x2E, 0x00, 0x00, 0x00, 0x67, 0x65, 0x66, 0x61,
        0x6E, 0x67, 0x65, 0x6E, 0x65, 0x72, 0x20, 0x66, 0x72, 0x65, 0x69, 0x2E, 0x00, 0x00, 0x00, 0x00,
        0x61, 0x6C, 0x6C, 0x65, 0x20, 0x67, 0x65, 0x66, 0x61, 0x6E, 0x67, 0x65, 0x6E, 0x65, 0x6E, 0x20,
        0x66, 0x72, 0x65, 0x69, 0x2E, 0x20, 0x0A, 0x6D, 0x69, 0x73, 0x73, 0x69, 0x6F, 0x6E, 0x20, 0x62,
        0x65, 0x65, 0x6E, 0x64, 0x65, 0x74, 0x2E, 0x00, 0x77, 0x61, 0x66, 0x66, 0x65, 0x6E, 0x20, 0x64,
        0x65, 0x73, 0x20, 0x70, 0x72, 0x69, 0x6D, 0x61, 0x67, 0x65, 0x6E, 0x20, 0x76, 0x65, 0x72, 0x6E,
        0x69, 0x63, 0x68, 0x74, 0x65, 0x74, 0x2E, 0x00, 0x61, 0x6C, 0x6C, 0x65, 0x20, 0x70, 0x72, 0x69,
        0x6D, 0x61, 0x67, 0x65, 0x6E, 0x2D, 0x77, 0x61, 0x66, 0x66, 0x65, 0x6E, 0x20, 0x76, 0x65, 0x72,
        0x6E, 0x69, 0x63, 0x68, 0x74, 0x65, 0x74, 0x2E, 0x20, 0x0A, 0x6D, 0x69, 0x73, 0x73, 0x69, 0x6F,
        0x6E, 0x20, 0x62, 0x65, 0x65, 0x6E, 0x64, 0x65, 0x74, 0x2E, 0x00, 0x00, 0x65, 0x6E, 0x65, 0x72,
        0x67, 0x69, 0x65, 0x7A, 0x65, 0x6C, 0x6C, 0x65, 0x20, 0x65, 0x72, 0x66, 0x6F, 0x72, 0x64, 0x65,
        0x72, 0x6C, 0x69, 0x63, 0x68, 0x2E, 0x00, 0x00, 0x6B, 0xE4, 0x66, 0x69, 0x67, 0x20, 0x6F, 0x66,
        0x66, 0x65, 0x6E, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x74, 0x61, 0x73, 0x63, 0x68, 0x65, 0x6E, 0x73,
        0x70, 0x72, 0x65, 0x6E, 0x67, 0x73, 0x61, 0x74, 0x7A, 0x20, 0x65, 0x72, 0x66, 0x6F, 0x72, 0x64,
        0x65, 0x72, 0x6C, 0x69, 0x63, 0x68, 0x2E, 0x00, 0x61, 0x63, 0x68, 0x74, 0x75, 0x6E, 0x67, 0x3A,
        0x20, 0x66, 0xFC, 0x6E, 0x66, 0x20, 0x73, 0x65, 0x6B, 0x75, 0x6E, 0x64, 0x65, 0x6E, 0x20, 0x62,
        0x69, 0x73, 0x20, 0x65, 0x78, 0x70, 0x6C, 0x6F, 0x73, 0x69, 0x6F, 0x6E, 0x2E, 0x00, 0x00, 0x00,
        0x61, 0x72, 0x73, 0x65, 0x6E, 0x61, 0x6C, 0x20, 0x7A, 0x65, 0x72, 0x73, 0x74, 0xF6, 0x72, 0x74,
        0x2E, 0x00, 0x00, 0x00, 0x61, 0x72, 0x73, 0x65, 0x6E, 0x61, 0x6C, 0x65, 0x20, 0x7A, 0x65, 0x72,
        0x73, 0x74, 0xF6, 0x72, 0x74, 0x2E, 0x20, 0x0A, 0x6D, 0x69, 0x73, 0x73, 0x69, 0x6F, 0x6E, 0x20,
        0x62, 0x65, 0x65, 0x6E, 0x64, 0x65, 0x74, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x64, 0x65, 0x6D, 0x6F,
        0x2D, 0x73, 0x70, 0x69, 0x65, 0x6C, 0x20, 0x62, 0x65, 0x65, 0x6E, 0x64, 0x65, 0x74, 0x21, 0x00,
        0x72, 0x69, 0x65, 0x73, 0x69, 0x67, 0x65, 0x20, 0x77, 0x65, 0x6C, 0x74, 0x65, 0x6E, 0x2E, 0x00,
        0x6D, 0x61, 0x6E, 0x74, 0x69, 0x64, 0x2D, 0x73, 0x74, 0x6F, 0x63, 0x6B, 0x2E, 0x00, 0x00, 0x00,
        0x68, 0xF6, 0x68, 0x6C, 0x65, 0x6E, 0x2E, 0x00, 0x66, 0x6C, 0x65, 0x69, 0x73, 0x63, 0x68, 0x66,
        0x72, 0x65, 0x73, 0x73, 0x65, 0x72, 0x2E, 0x00, 0x73, 0x74, 0x61, 0x64, 0x74, 0x65, 0x69, 0x6E,
        0x67, 0x61, 0x6E, 0x67, 0x2E, 0x00, 0x00, 0x00, 0x6D, 0x65, 0x68, 0x72, 0x65, 0x72, 0x65, 0x20,
        0x6D, 0x69, 0x73, 0x73, 0x69, 0x6F, 0x6E, 0x73, 0x7A, 0x69, 0x65, 0x6C, 0x65, 0x2E, 0x00, 0x00,
        0x6B, 0x6C, 0x61, 0x74, 0x73, 0x63, 0x68, 0x65, 0x6E, 0x64, 0x65, 0x73, 0x20, 0x6B, 0x69, 0x6E,
        0x64, 0x2E, 0x00, 0x00, 0x62, 0x65, 0x69, 0x6E, 0x68, 0x61, 0x72, 0x74, 0x65, 0x20, 0x67, 0x65,
        0x67, 0x6E, 0x65, 0x72, 0x2E, 0x00, 0x00, 0x00, 0x6B, 0x6F, 0x6C, 0x6F, 0x6E, 0x69, 0x65, 0x20,
        0x64, 0x65, 0x72, 0x20, 0x6D, 0x61, 0x6E, 0x74, 0x69, 0x64, 0x73, 0x2E, 0x00, 0x00, 0x00, 0x00,
        0x70, 0x75, 0x72, 0x72, 0x2D, 0x6C, 0x69, 0x6E, 0x6E, 0x2E, 0x00, 0x00, 0x66, 0x6C, 0x65, 0x69,
        0x73, 0x63, 0x68, 0x66, 0x72, 0x65, 0x73, 0x73, 0x65, 0x72, 0x2E, 0x00, 0x67, 0x6E, 0x61, 0x64,
        0x65, 0x6E, 0x6C, 0x6F, 0x73, 0x65, 0x20, 0x62, 0x6F, 0x73, 0x73, 0x65, 0x2E, 0x00, 0x00, 0x00,
        0x6B, 0xF6, 0x6E, 0x69, 0x67, 0x69, 0x6E, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x6D, 0x75, 0x74, 0x74,
        0x65, 0x72, 0x2E, 0x00, 0x62, 0x6C, 0x69, 0x6E, 0x64, 0x65, 0x72, 0x2D, 0x6A, 0xE4, 0x67, 0x65,
        0x72, 0x2D, 0x61, 0x75, 0x67, 0x65, 0x2E, 0x00, 0x61, 0x72, 0x73, 0x65, 0x6E, 0x61, 0x6C, 0x20,
        0x67, 0x65, 0x66, 0x75, 0x6E, 0x64, 0x65, 0x6E, 0x2E, 0x00, 0x00, 0x00, 0x73, 0x70, 0x69, 0x65,
        0x6C, 0x64, 0x65, 0x6D, 0x6F, 0x20, 0x2D, 0x20, 0x6B, 0x65, 0x69, 0x6E, 0x20, 0x7A, 0x75, 0x67,
        0x72, 0x69, 0x66, 0x66, 0x2E, 0x00, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65, 0x6C, 0x20, 0x31, 0x20,
        0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x20, 0x65, 0x72, 0x66, 0x6F, 0x72, 0x64,
        0x65, 0x72, 0x6C, 0x69, 0x63, 0x68, 0x2E, 0x00, 0x6C, 0x65, 0x76, 0x65, 0x6C, 0x20, 0x32, 0x20,
        0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x20, 0x65, 0x72, 0x66, 0x6F, 0x72, 0x64,
        0x65, 0x72, 0x6C, 0x69, 0x63, 0x68, 0x2E, 0x00, 0x6C, 0x65, 0x76, 0x65, 0x6C, 0x20, 0x33, 0x20,
        0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x20, 0x65, 0x72, 0x66, 0x6F, 0x72, 0x64,
        0x65, 0x72, 0x6C, 0x69, 0x63, 0x68, 0x2E, 0x00, 0x6C, 0x65, 0x76, 0x65, 0x6C, 0x20, 0x34, 0x20,
        0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x20, 0x65, 0x72, 0x66, 0x6F, 0x72, 0x64,
        0x65, 0x72, 0x6C, 0x69, 0x63, 0x68, 0x2E, 0x00, 0x6C, 0x65, 0x76, 0x65, 0x6C, 0x20, 0x35, 0x20,
        0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x20, 0x65, 0x72, 0x66, 0x6F, 0x72, 0x64,
        0x65, 0x72, 0x6C, 0x69, 0x63, 0x68, 0x2E, 0x00, 0x6C, 0x65, 0x76, 0x65, 0x6C, 0x20, 0x36, 0x20,
        0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x20, 0x65, 0x72, 0x66, 0x6F, 0x72, 0x64,
        0x65, 0x72, 0x6C, 0x69, 0x63, 0x68, 0x2E, 0x00, 0x70, 0x72, 0x69, 0x6D, 0x61, 0x67, 0x65, 0x6E,
        0x2D, 0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x20, 0x31, 0x20, 0x65, 0x72, 0x66,
        0x6F, 0x72, 0x64, 0x65, 0x72, 0x6C, 0x69, 0x63, 0x68, 0x2E, 0x00, 0x00, 0x70, 0x72, 0x69, 0x6D,
        0x61, 0x67, 0x65, 0x6E, 0x2D, 0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x20, 0x32,
        0x20, 0x65, 0x72, 0x66, 0x6F, 0x72, 0x64, 0x65, 0x72, 0x6C, 0x69, 0x63, 0x68, 0x2E, 0x00, 0x00,
        0x70, 0x72, 0x69, 0x6D, 0x61, 0x67, 0x65, 0x6E, 0x2D, 0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73,
        0x65, 0x6C, 0x20, 0x33, 0x20, 0x65, 0x72, 0x66, 0x6F, 0x72, 0x64, 0x65, 0x72, 0x6C, 0x69, 0x63,
        0x68, 0x2E, 0x00, 0x00, 0x70, 0x72, 0x69, 0x6D, 0x61, 0x67, 0x65, 0x6E, 0x2D, 0x73, 0x63, 0x68,
        0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x20, 0x34, 0x20, 0x65, 0x72, 0x66, 0x6F, 0x72, 0x64, 0x65,
        0x72, 0x6C, 0x69, 0x63, 0x68, 0x2E, 0x00, 0x00, 0x70, 0x72, 0x69, 0x6D, 0x61, 0x67, 0x65, 0x6E,
        0x2D, 0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x20, 0x35, 0x20, 0x65, 0x72, 0x66,
        0x6F, 0x72, 0x64, 0x65, 0x72, 0x6C, 0x69, 0x63, 0x68, 0x2E, 0x00, 0x00, 0x70, 0x72, 0x69, 0x6D,
        0x61, 0x67, 0x65, 0x6E, 0x2D, 0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x20, 0x36,
        0x20, 0x65, 0x72, 0x66, 0x6F, 0x72, 0x64, 0x65, 0x72, 0x6C, 0x69, 0x63, 0x68, 0x2E, 0x00, 0x00,
        0x7A, 0x75, 0x67, 0x72, 0x69, 0x66, 0x66, 0x20, 0x61, 0x75, 0x66, 0x20, 0x6C, 0x65, 0x76, 0x65,
        0x6C, 0x20, 0x31, 0x20, 0x67, 0x65, 0x77, 0xE4, 0x68, 0x72, 0x74, 0x2E, 0x00, 0x00, 0x00, 0x00,
        0x7A, 0x75, 0x67, 0x72, 0x69, 0x66, 0x66, 0x20, 0x61, 0x75, 0x66, 0x20, 0x6C, 0x65, 0x76, 0x65,
        0x6C, 0x20, 0x32, 0x20, 0x67, 0x65, 0x77, 0xE4, 0x68, 0x72, 0x74, 0x2E, 0x00, 0x00, 0x00, 0x00,
        0x7A, 0x75, 0x67, 0x72, 0x69, 0x66, 0x66, 0x20, 0x61, 0x75, 0x66, 0x20, 0x6C, 0x65, 0x76, 0x65,
        0x6C, 0x20, 0x33, 0x20, 0x67, 0x65, 0x77, 0xE4, 0x68, 0x72, 0x74, 0x2E, 0x00, 0x00, 0x00, 0x00,
        0x7A, 0x75, 0x67, 0x72, 0x69, 0x66, 0x66, 0x20, 0x61, 0x75, 0x66, 0x20, 0x6C, 0x65, 0x76, 0x65,
        0x6C, 0x20, 0x34, 0x20, 0x67, 0x65, 0x77, 0xE4, 0x68, 0x72, 0x74, 0x2E, 0x00, 0x00, 0x00, 0x00,
        0x7A, 0x75, 0x67, 0x72, 0x69, 0x66, 0x66, 0x20, 0x61, 0x75, 0x66, 0x20, 0x6C, 0x65, 0x76, 0x65,
        0x6C, 0x20, 0x35, 0x20, 0x67, 0x65, 0x77, 0xE4, 0x68, 0x72, 0x74, 0x2E, 0x00, 0x00, 0x00, 0x00,
        0x7A, 0x75, 0x67, 0x72, 0x69, 0x66, 0x66, 0x20, 0x61, 0x75, 0x66, 0x20, 0x6C, 0x65, 0x76, 0x65,
        0x6C, 0x20, 0x36, 0x20, 0x67, 0x65, 0x77, 0xE4, 0x68, 0x72, 0x74, 0x2E, 0x00, 0x00, 0x00, 0x00,
        0x7A, 0x75, 0x67, 0x61, 0x6E, 0x67, 0x20, 0x7A, 0x75, 0x6D, 0x20, 0x70, 0x72, 0x69, 0x6D, 0x61,
        0x67, 0x65, 0x6E, 0x20, 0x67, 0x65, 0x77, 0xE4, 0x68, 0x72, 0x74, 0x2E, 0x00, 0x00, 0x00, 0x00,
        0x61, 0x6C, 0x6C, 0x65, 0x20, 0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x20, 0x67,
        0x65, 0x66, 0x75, 0x6E, 0x64, 0x65, 0x6E, 0x2E, 0x20, 0x0A, 0x6D, 0x69, 0x73, 0x73, 0x69, 0x6F,
        0x6E, 0x20, 0x62, 0x65, 0x65, 0x6E, 0x64, 0x65, 0x74, 0x2E, 0x00, 0x00, 0x64, 0x69, 0x65, 0x73,
        0x65, 0x20, 0x74, 0xFC, 0x72, 0x20, 0x65, 0x72, 0x66, 0x6F, 0x72, 0x64, 0x65, 0x72, 0x74, 0x20,
        0x65, 0x69, 0x6E, 0x65, 0x6E, 0x20, 0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x2E,
        0x00, 0x00, 0x00, 0x00, 0x65, 0x72, 0x66, 0x6F, 0x72, 0x64, 0x65, 0x72, 0x74, 0x20, 0x62, 0x6C,
        0x61, 0x75, 0x65, 0x20, 0x66, 0x65, 0x64, 0x65, 0x72, 0x0A, 0x20, 0x61, 0x6C, 0x73, 0x20, 0x6F,
        0x70, 0x66, 0x65, 0x72, 0x67, 0x61, 0x62, 0x65, 0x2E, 0x00, 0x00, 0x00, 0x65, 0x72, 0x66, 0x6F,
        0x72, 0x64, 0x65, 0x72, 0x74, 0x20, 0x67, 0x72, 0x61, 0x75, 0x65, 0x20, 0x66, 0x65, 0x64, 0x65,
        0x72, 0x0A, 0x20, 0x61, 0x6C, 0x73, 0x20, 0x6F, 0x70, 0x66, 0x65, 0x72, 0x67, 0x61, 0x62, 0x65,
        0x2E, 0x00, 0x00, 0x00, 0x65, 0x72, 0x66, 0x6F, 0x72, 0x64, 0x65, 0x72, 0x74, 0x20, 0x62, 0x72,
        0x61, 0x75, 0x6E, 0x65, 0x20, 0x66, 0x65, 0x64, 0x65, 0x72, 0x0A, 0x20, 0x61, 0x6C, 0x73, 0x20,
        0x6F, 0x70, 0x66, 0x65, 0x72, 0x67, 0x61, 0x62, 0x65, 0x2E, 0x00, 0x00, 0x65, 0x72, 0x66, 0x6F,
        0x72, 0x64, 0x65, 0x72, 0x74, 0x20, 0x6C, 0x69, 0x6C, 0x61, 0x20, 0x66, 0x65, 0x64, 0x65, 0x72,
        0x0A, 0x20, 0x61, 0x6C, 0x73, 0x20, 0x6F, 0x70, 0x66, 0x65, 0x72, 0x67, 0x61, 0x62, 0x65, 0x2E,
        0x00, 0x00, 0x00, 0x00, 0x65, 0x72, 0x66, 0x6F, 0x72, 0x64, 0x65, 0x72, 0x74, 0x20, 0x72, 0x6F,
        0x74, 0x65, 0x20, 0x66, 0x65, 0x64, 0x65, 0x72, 0x0A, 0x20, 0x61, 0x6C, 0x73, 0x20, 0x6F, 0x70,
        0x66, 0x65, 0x72, 0x67, 0x61, 0x62, 0x65, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x74, 0xFC, 0x72, 0x20,
        0x6F, 0x66, 0x66, 0x65, 0x6E, 0x2E, 0x00, 0x00, 0x75, 0x6E, 0x74, 0x65, 0x72, 0x77, 0x61, 0x73,
        0x73, 0x65, 0x72, 0x74, 0xFC, 0x72, 0x20, 0x6F, 0x66, 0x66, 0x65, 0x6E, 0x2E, 0x00, 0x00, 0x00,
        0x73, 0x74, 0x72, 0x6F, 0x6D, 0x67, 0x65, 0x6E, 0x65, 0x72, 0x61, 0x74, 0x6F, 0x72, 0x20, 0x72,
        0x65, 0x6B, 0x61, 0x6C, 0x69, 0x62, 0x72, 0x69, 0x65, 0x72, 0x74, 0x2E, 0x00, 0x00, 0x00, 0x00,
        0x61, 0x6C, 0x6C, 0x65, 0x20, 0x73, 0x74, 0x72, 0x6F, 0x6D, 0x67, 0x65, 0x6E, 0x65, 0x72, 0x61,
        0x74, 0x6F, 0x72, 0x65, 0x6E, 0x20, 0x72, 0x65, 0x6B, 0x61, 0x6C, 0x69, 0x62, 0x72, 0x69, 0x65,
        0x72, 0x74, 0x0A, 0x6D, 0x69, 0x73, 0x73, 0x69, 0x6F, 0x6E, 0x20, 0x62, 0x65, 0x65, 0x6E, 0x64,
        0x65, 0x74, 0x2E, 0x00, 0x6B, 0x72, 0x69, 0x73, 0x74, 0x61, 0x6C, 0x6C, 0x69, 0x6F, 0x6E, 0x65,
        0x6E, 0x2D, 0x6B, 0x6F, 0x6E, 0x64, 0x65, 0x6E, 0x73, 0x61, 0x74, 0x6F, 0x72, 0x20, 0x65, 0x72,
        0x66, 0x6F, 0x72, 0x64, 0x65, 0x72, 0x6C, 0x69, 0x63, 0x68, 0x2E, 0x00, 0x72, 0x6F, 0x62, 0x6F,
        0x74, 0x65, 0x72, 0x2D, 0x66, 0x61, 0x62, 0x72, 0x69, 0x6B, 0x20, 0x7A, 0x65, 0x72, 0x73, 0x74,
        0xF6, 0x72, 0x74, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x61, 0x6C, 0x6C, 0x65, 0x20, 0x72, 0x6F, 0x62,
        0x6F, 0x74, 0x65, 0x72, 0x2D, 0x66, 0x61, 0x62, 0x72, 0x69, 0x6B, 0x65, 0x6E, 0x20, 0x7A, 0x65,
        0x72, 0x73, 0x74, 0xF6, 0x72, 0x74, 0x0A, 0x6D, 0x69, 0x73, 0x73, 0x69, 0x6F, 0x6E, 0x20, 0x62,
        0x65, 0x65, 0x6E, 0x64, 0x65, 0x74, 0x2E, 0x00, 0x73, 0x63, 0x68, 0x61, 0x63, 0x68, 0x74, 0x6B,
        0x61, 0x6D, 0x6D, 0x65, 0x72, 0x20, 0x67, 0x65, 0x66, 0x75, 0x6E, 0x64, 0x65, 0x6E, 0x2E, 0x00,
        0x74, 0x68, 0x65, 0x72, 0x6D, 0x61, 0x6C, 0x73, 0x63, 0x68, 0x61, 0x63, 0x68, 0x74, 0x20, 0x76,
        0x65, 0x72, 0x73, 0x69, 0x65, 0x67, 0x65, 0x6C, 0x74, 0x2E, 0x00, 0x00, 0x62, 0x6C, 0x69, 0x6E,
        0x64, 0x65, 0x20, 0x6A, 0xE4, 0x67, 0x65, 0x72, 0x20, 0x69, 0x6E, 0x20, 0x66, 0x61, 0x6C, 0x6C,
        0x65, 0x20, 0x0A, 0x6D, 0x69, 0x73, 0x73, 0x69, 0x6F, 0x6E, 0x20, 0x62, 0x65, 0x65, 0x6E, 0x64,
        0x65, 0x74, 0x2E, 0x00, 0x6B, 0x72, 0x61, 0x66, 0x74, 0x66, 0x65, 0x6C, 0x64, 0x20, 0x64, 0x65,
        0x61, 0x6B, 0x74, 0x69, 0x76, 0x69, 0x65, 0x72, 0x74, 0x2E, 0x00, 0x00, 0x68, 0x61, 0x75, 0x70,
        0x74, 0x63, 0x6F, 0x6D, 0x70, 0x75, 0x74, 0x65, 0x72, 0x2D, 0x6B, 0x72, 0x61, 0x66, 0x74, 0x66,
        0x65, 0x6C, 0x64, 0x20, 0x64, 0x65, 0x61, 0x6B, 0x74, 0x69, 0x76, 0x69, 0x65, 0x72, 0x74, 0x2E,
        0x00, 0x00, 0x00, 0x00, 0x6C, 0x61, 0x73, 0x65, 0x72, 0x65, 0x6E, 0x65, 0x72, 0x67, 0x69, 0x65,
        0x6B, 0x72, 0x69, 0x73, 0x74, 0x61, 0x6C, 0x6C, 0x20, 0x65, 0x72, 0x66, 0x6F, 0x72, 0x64, 0x65,
        0x72, 0x6C, 0x69, 0x63, 0x68, 0x2E, 0x00, 0x00, 0x74, 0x6F, 0x72, 0x20, 0x61, 0x6B, 0x74, 0x69,
        0x76, 0x69, 0x65, 0x72, 0x74, 0x2E, 0x00, 0x00, 0x74, 0x6F, 0x72, 0x73, 0x63, 0x68, 0x6C, 0xFC,
        0x73, 0x73, 0x65, 0x6C, 0x20, 0x65, 0x72, 0x66, 0x6F, 0x72, 0x64, 0x65, 0x72, 0x6C, 0x69, 0x63,
        0x68, 0x2E, 0x00, 0x00, 0x66, 0x72, 0x69, 0x65, 0x64, 0x68, 0x6F, 0x66, 0x73, 0x73, 0x63, 0x68,
        0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x20, 0x65, 0x72, 0x66, 0x6F, 0x72, 0x64, 0x65, 0x72, 0x6C,
        0x69, 0x63, 0x68, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x66, 0x72, 0x69, 0x65, 0x64, 0x68, 0x6F, 0x66,
        0x73, 0x74, 0x6F, 0x72, 0x20, 0x67, 0x65, 0xF6, 0x66, 0x66, 0x6E, 0x65, 0x74, 0x2E, 0x00, 0x00,
        0x66, 0x72, 0x69, 0x65, 0x64, 0x68, 0x6F, 0x66, 0x73, 0x74, 0x6F, 0x72, 0x20, 0x67, 0x65, 0x66,
        0x75, 0x6E, 0x64, 0x65, 0x6E, 0x2E, 0x00, 0x00, 0x73, 0x65, 0x65, 0x6C, 0x65, 0x6E, 0x74, 0x6F,
        0x72, 0x20, 0x67, 0x65, 0x66, 0x75, 0x6E, 0x64, 0x65, 0x6E, 0x2E, 0x00, 0x73, 0x65, 0x65, 0x6C,
        0x65, 0x6E, 0x74, 0x6F, 0x72, 0x20, 0x7A, 0x65, 0x72, 0x73, 0x74, 0xF6, 0x72, 0x74, 0x2E, 0x00,
        0x61, 0x6C, 0x6C, 0x65, 0x20, 0x73, 0x65, 0x65, 0x6C, 0x65, 0x6E, 0x74, 0x6F, 0x72, 0x65, 0x20,
        0x67, 0x65, 0x66, 0x75, 0x6E, 0x64, 0x65, 0x6E, 0x2E, 0x0A, 0x6D, 0x69, 0x73, 0x73, 0x69, 0x6F,
        0x6E, 0x20, 0x62, 0x65, 0x65, 0x6E, 0x64, 0x65, 0x74, 0x2E, 0x00, 0x00, 0x73, 0x63, 0x68, 0x77,
        0x65, 0x73, 0x74, 0x65, 0x72, 0x20, 0x64, 0x65, 0x72, 0x20, 0x76, 0x65, 0x72, 0x7A, 0x77, 0x65,
        0x69, 0x66, 0x6C, 0x75, 0x6E, 0x67, 0x20, 0x76, 0x65, 0x72, 0x62, 0x61, 0x6E, 0x6E, 0x74, 0x2E,
        0x00, 0x00, 0x00, 0x00, 0x61, 0x6C, 0x6C, 0x65, 0x20, 0x73, 0x63, 0x68, 0x77, 0x65, 0x73, 0x74,
        0x65, 0x72, 0x6E, 0x20, 0x64, 0x65, 0x72, 0x20, 0x76, 0x65, 0x72, 0x7A, 0x77, 0x65, 0x69, 0x66,
        0x6C, 0x75, 0x6E, 0x67, 0x20, 0x76, 0x65, 0x72, 0x62, 0x61, 0x6E, 0x6E, 0x74, 0x2E, 0x0A, 0x6D,
        0x69, 0x73, 0x73, 0x69, 0x6F, 0x6E, 0x20, 0x62, 0x65, 0x65, 0x6E, 0x64, 0x65, 0x74, 0x2E, 0x00,
        0x6B, 0x72, 0x61, 0x66, 0x74, 0x66, 0x65, 0x6C, 0x64, 0x67, 0x65, 0x6E, 0x65, 0x72, 0x61, 0x74,
        0x6F, 0x72, 0x20, 0x64, 0x65, 0x61, 0x6B, 0x74, 0x69, 0x76, 0x69, 0x65, 0x72, 0x74, 0x2E, 0x00,
        0x66, 0x61, 0x62, 0x72, 0x69, 0x6B, 0x63, 0x6F, 0x6D, 0x70, 0x75, 0x74, 0x65, 0x72, 0x00, 0x00,
    },
    {
        (unsigned int)&s_controllerPakMessageDe_ZugriffAufDas, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak, 0x00000000, 0x00000000, 0x00000000, (unsigned int)&s_controllerPakMessageDe_ExpansionPakGefunden, 0x00000000,
        (unsigned int)&s_controllerPakMessageDe_DrCkeEineTaste, 0x00000000,
    },
    {
        0x32, 0x20, 0x47, 0x65, 0x73, 0x75, 0x6E, 0x64, 0x68, 0x65, 0x69, 0x74, 0x00, 0x00, 0x00, 0x00,
        0x31, 0x30, 0x20, 0x47, 0x65, 0x73, 0x75, 0x6E, 0x64, 0x68, 0x65, 0x69, 0x74, 0x00, 0x00, 0x00,
        0x31, 0x35, 0x20, 0x47, 0x65, 0x73, 0x75, 0x6E, 0x64, 0x68, 0x65, 0x69, 0x74, 0x00, 0x00, 0x00,
        0x32, 0x35, 0x20, 0x47, 0x65, 0x73, 0x75, 0x6E, 0x64, 0x68, 0x65, 0x69, 0x74, 0x00, 0x00, 0x00,
        0x35, 0x30, 0x20, 0x47, 0x65, 0x73, 0x75, 0x6E, 0x64, 0x68, 0x65, 0x69, 0x74, 0x00, 0x00, 0x00,
        0x56, 0x6F, 0x6C, 0x6C, 0x65, 0x20, 0x47, 0x65, 0x73, 0x75, 0x6E, 0x64, 0x68, 0x65, 0x69, 0x74,
        0x00, 0x00, 0x00, 0x00, 0x75, 0x6C, 0x74, 0x72, 0x61, 0x2D, 0x67, 0x65, 0x73, 0x75, 0x6E, 0x64,
        0x68, 0x65, 0x69, 0x74, 0x00, 0x00, 0x00, 0x00, 0x31, 0x20, 0x6C, 0x65, 0x62, 0x65, 0x6E, 0x73,
        0x70, 0x75, 0x6E, 0x6B, 0x74, 0x00, 0x00, 0x00, 0x31, 0x30, 0x20, 0x6C, 0x65, 0x62, 0x65, 0x6E,
        0x73, 0x70, 0x75, 0x6E, 0x6B, 0x74, 0x65, 0x00, 0x75, 0x6E, 0x62, 0x65, 0x73, 0x69, 0x65, 0x67,
        0x62, 0x61, 0x72, 0x6B, 0x65, 0x69, 0x74, 0x00, 0x7A, 0x65, 0x69, 0x74, 0x72, 0x61, 0x66, 0x66,
        0x65, 0x72, 0x00, 0x00, 0x74, 0x61, 0x73, 0x63, 0x68, 0x65, 0x6E, 0x6C, 0x61, 0x6D, 0x70, 0x65,
        0x00, 0x00, 0x00, 0x00, 0x74, 0x61, 0x73, 0x63, 0x68, 0x65, 0x6E, 0x6C, 0x61, 0x6D, 0x70, 0x65,
        0x6E, 0x62, 0x61, 0x74, 0x74, 0x65, 0x72, 0x69, 0x65, 0x00, 0x00, 0x00, 0x49, 0x6E, 0x66, 0x72,
        0x61, 0x72, 0x6F, 0x74, 0x62, 0x72, 0x69, 0x6C, 0x6C, 0x65, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65,
        0x6C, 0x2D, 0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x00, 0x74, 0x61, 0x73, 0x63,
        0x68, 0x65, 0x6E, 0x73, 0x70, 0x72, 0x65, 0x6E, 0x67, 0x73, 0x61, 0x74, 0x7A, 0x00, 0x00, 0x00,
        0x65, 0x6E, 0x65, 0x72, 0x67, 0x69, 0x65, 0x7A, 0x65, 0x6C, 0x6C, 0x65, 0x00, 0x00, 0x00, 0x00,
        0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x00, 0x00, 0x00, 0x68, 0xF6, 0x68, 0x6C,
        0x65, 0x6E, 0x74, 0xFC, 0x72, 0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x00, 0x00,
        0x6C, 0x61, 0x73, 0x65, 0x72, 0x65, 0x6E, 0x65, 0x72, 0x67, 0x69, 0x65, 0x6B, 0x72, 0x69, 0x73,
        0x74, 0x61, 0x6C, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x69, 0x6F, 0x6E, 0x65, 0x6E, 0x6B, 0x6F, 0x6E,
        0x64, 0x65, 0x6E, 0x73, 0x61, 0x74, 0x6F, 0x72, 0x00, 0x00, 0x00, 0x00, 0x72, 0x6F, 0x74, 0x65,
        0x20, 0x6C, 0x61, 0x73, 0x65, 0x72, 0x7A, 0x65, 0x6C, 0x6C, 0x65, 0x00, 0x62, 0x6C, 0x61, 0x75,
        0x65, 0x20, 0x6C, 0x61, 0x73, 0x65, 0x72, 0x7A, 0x65, 0x6C, 0x6C, 0x65, 0x00, 0x00, 0x00, 0x00,
        0x74, 0x6F, 0x72, 0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x00, 0x00, 0x00, 0x00,
        0x66, 0x72, 0x69, 0x65, 0x64, 0x68, 0x6F, 0x66, 0x73, 0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73,
        0x65, 0x6C, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65, 0x6C, 0x20, 0x31, 0x20, 0x73, 0x63, 0x68, 0x6C,
        0xFC, 0x73, 0x73, 0x65, 0x6C, 0x00, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65, 0x6C, 0x20, 0x32, 0x20,
        0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x00, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65,
        0x6C, 0x20, 0x33, 0x20, 0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x00, 0x00, 0x00,
        0x6C, 0x65, 0x76, 0x65, 0x6C, 0x20, 0x34, 0x20, 0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73, 0x65,
        0x6C, 0x00, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65, 0x6C, 0x20, 0x35, 0x20, 0x73, 0x63, 0x68, 0x6C,
        0xFC, 0x73, 0x73, 0x65, 0x6C, 0x00, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65, 0x6C, 0x20, 0x36, 0x20,
        0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x00, 0x00, 0x00, 0x70, 0x72, 0x69, 0x6D,
        0x61, 0x67, 0x65, 0x6E, 0x2D, 0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x20, 0x31,
        0x00, 0x00, 0x00, 0x00, 0x70, 0x72, 0x69, 0x6D, 0x61, 0x67, 0x65, 0x6E, 0x2D, 0x73, 0x63, 0x68,
        0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x20, 0x32, 0x00, 0x00, 0x00, 0x00, 0x70, 0x72, 0x69, 0x6D,
        0x61, 0x67, 0x65, 0x6E, 0x2D, 0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x20, 0x33,
        0x00, 0x00, 0x00, 0x00, 0x70, 0x72, 0x69, 0x6D, 0x61, 0x67, 0x65, 0x6E, 0x2D, 0x73, 0x63, 0x68,
        0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x20, 0x34, 0x00, 0x00, 0x00, 0x00, 0x70, 0x72, 0x69, 0x6D,
        0x61, 0x67, 0x65, 0x6E, 0x2D, 0x73, 0x63, 0x68, 0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x20, 0x35,
        0x00, 0x00, 0x00, 0x00, 0x70, 0x72, 0x69, 0x6D, 0x61, 0x67, 0x65, 0x6E, 0x2D, 0x73, 0x63, 0x68,
        0x6C, 0xFC, 0x73, 0x73, 0x65, 0x6C, 0x20, 0x36, 0x00, 0x00, 0x00, 0x00, 0x61, 0x74, 0x65, 0x6D,
        0x20, 0x64, 0x65, 0x73, 0x20, 0x6C, 0x65, 0x62, 0x65, 0x6E, 0x73, 0x00, 0x61, 0x75, 0x67, 0x65,
        0x20, 0x64, 0x65, 0x72, 0x20, 0x77, 0x61, 0x68, 0x72, 0x68, 0x65, 0x69, 0x74, 0x00, 0x00, 0x00,
        0x73, 0x70, 0x72, 0x75, 0x6E, 0x67, 0x20, 0x64, 0x65, 0x73, 0x20, 0x67, 0x6C, 0x61, 0x75, 0x62,
        0x65, 0x6E, 0x73, 0x00, 0x66, 0x6C, 0xFC, 0x73, 0x74, 0x65, 0x72, 0x20, 0x74, 0x61, 0x6C, 0x69,
        0x73, 0x6D, 0x61, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x68, 0x65, 0x72, 0x7A, 0x20, 0x61, 0x75, 0x73,
        0x20, 0x66, 0x65, 0x75, 0x65, 0x72, 0x00, 0x00, 0x62, 0x6C, 0x61, 0x75, 0x65, 0x20, 0x61, 0x64,
        0x6C, 0x65, 0x72, 0x66, 0x65, 0x64, 0x65, 0x72, 0x00, 0x00, 0x00, 0x00, 0x67, 0x72, 0x61, 0x75,
        0x65, 0x20, 0x61, 0x64, 0x6C, 0x65, 0x72, 0x66, 0x65, 0x64, 0x65, 0x72, 0x00, 0x00, 0x00, 0x00,
        0x62, 0x72, 0x61, 0x75, 0x6E, 0x65, 0x20, 0x61, 0x64, 0x6C, 0x65, 0x72, 0x66, 0x65, 0x64, 0x65,
        0x72, 0x00, 0x00, 0x00, 0x6C, 0x69, 0x6C, 0x61, 0x20, 0x61, 0x64, 0x6C, 0x65, 0x72, 0x66, 0x65,
        0x64, 0x65, 0x72, 0x00, 0x72, 0x6F, 0x74, 0x65, 0x20, 0x61, 0x64, 0x6C, 0x65, 0x72, 0x66, 0x65,
        0x64, 0x65, 0x72, 0x00, 0x46, 0x75, 0x6E, 0x6B, 0x74, 0x69, 0x6F, 0x6E, 0x20, 0x6E, 0x69, 0x63,
        0x68, 0x74, 0x20, 0x76, 0x65, 0x72, 0x66, 0xFC, 0x67, 0x62, 0x61, 0x72, 0x00, 0x00, 0x00, 0x00,
        0x57, 0x41, 0x52, 0x48, 0x41, 0x4D, 0x4D, 0x45, 0x52, 0x00, 0x00, 0x00, 0x52, 0x41, 0x50, 0x54,
        0x4F, 0x52, 0x2D, 0x4B, 0x4C, 0x41, 0x55, 0x45, 0x00, 0x00, 0x00, 0x00, 0x4D, 0x49, 0x54, 0x45,
        0x2D, 0x42, 0x49, 0x53, 0x53, 0x00, 0x00, 0x00, 0x42, 0x55, 0x4D, 0x45, 0x52, 0x41, 0x4E, 0x47,
        0x00, 0x00, 0x00, 0x00, 0x54, 0x45, 0x4B, 0x2D, 0x41, 0x52, 0x4D, 0x42, 0x52, 0x55, 0x53, 0x54,
        0x00, 0x00, 0x00, 0x00, 0x4D, 0x41, 0x47, 0x2E, 0x20, 0x36, 0x30, 0x00, 0x53, 0x48, 0x4F, 0x54,
        0x47, 0x55, 0x4E, 0x00, 0x53, 0x54, 0x55, 0x52, 0x4D, 0x47, 0x45, 0x57, 0x45, 0x48, 0x52, 0x00,
        0x4D, 0x49, 0x4E, 0x49, 0x47, 0x55, 0x4E, 0x00, 0x50, 0x4C, 0x41, 0x53, 0x4D, 0x41, 0x2D, 0x47,
        0x45, 0x57, 0x45, 0x48, 0x52, 0x00, 0x00, 0x00, 0x46, 0x52, 0x45, 0x45, 0x5A, 0x45, 0x2D, 0x47,
        0x55, 0x4E, 0x00, 0x00, 0x46, 0x4C, 0x41, 0x52, 0x45, 0x2D, 0x47, 0x55, 0x4E, 0x00, 0x00, 0x00,
        0x47, 0x52, 0x41, 0x4E, 0x41, 0x54, 0x45, 0x4E, 0x00, 0x00, 0x00, 0x00, 0x53, 0x4B, 0x4F, 0x52,
        0x50, 0x49, 0x4F, 0x4E, 0x00, 0x00, 0x00, 0x00, 0x4E, 0x41, 0x50, 0x41, 0x4C, 0x4D, 0x2D, 0x47,
        0x45, 0x4C, 0x00, 0x00, 0x45, 0x4D, 0x41, 0x43, 0x49, 0x41, 0x54, 0x4F, 0x52, 0x00, 0x00, 0x00,
        0x49, 0x4E, 0x46, 0x4C, 0x41, 0x54, 0x4F, 0x52, 0x00, 0x00, 0x00, 0x00, 0x42, 0x52, 0x55, 0x53,
        0x54, 0x42, 0x52, 0x45, 0x43, 0x48, 0x45, 0x52, 0x00, 0x00, 0x00, 0x00, 0x5A, 0x45, 0x52, 0x45,
        0x42, 0x52, 0x41, 0x4C, 0x42, 0x4F, 0x48, 0x52, 0x45, 0x52, 0x00, 0x00, 0x50, 0x46, 0x4D, 0x2D,
        0x4D, 0x49, 0x4E, 0x45, 0x00, 0x00, 0x00, 0x00, 0x45, 0x49, 0x53, 0x45, 0x4E, 0x4B, 0x4C, 0x41,
        0x55, 0x45, 0x00, 0x00, 0x54, 0x45, 0x4C, 0x45, 0x50, 0x4F, 0x52, 0x54, 0x2D, 0x4D, 0x49, 0x4E,
        0x45, 0x00, 0x00, 0x00, 0x57, 0x41, 0x43, 0x48, 0x54, 0x55, 0x52, 0x4D, 0x00, 0x00, 0x00, 0x00,
        0x53, 0x49, 0x47, 0x4E, 0x41, 0x4C, 0x20, 0x45, 0x4E, 0x54, 0x46, 0x45, 0x52, 0x4E, 0x54, 0x00,
        0x5A, 0x49, 0x45, 0x4C, 0x20, 0x4D, 0x41, 0x52, 0x4B, 0x49, 0x45, 0x52, 0x54, 0x00, 0x00, 0x00,
        0x41, 0x42, 0x57, 0x45, 0x48, 0x52, 0x20, 0x4D, 0x41, 0x52, 0x4B, 0x49, 0x45, 0x52, 0x54, 0x00,
        0x41, 0x6E, 0x20, 0x54, 0x65, 0x61, 0x6D, 0x20, 0x4B, 0x6F, 0x6A, 0x6F, 0x74, 0x65, 0x20, 0x61,
        0x6E, 0x67, 0x65, 0x73, 0x63, 0x68, 0x6C, 0x6F, 0x73, 0x73, 0x65, 0x6E, 0x00, 0x00, 0x00, 0x00,
        0x41, 0x6E, 0x20, 0x54, 0x65, 0x61, 0x6D, 0x20, 0x42, 0xE4, 0x72, 0x20, 0x61, 0x6E, 0x67, 0x65,
        0x73, 0x63, 0x68, 0x6C, 0x6F, 0x73, 0x73, 0x65, 0x6E, 0x00, 0x00, 0x00, 0x41, 0x6E, 0x20, 0x54,
        0x65, 0x61, 0x6D, 0x20, 0x50, 0x75, 0x6D, 0x61, 0x20, 0x61, 0x6E, 0x67, 0x65, 0x73, 0x63, 0x68,
        0x6C, 0x6F, 0x73, 0x73, 0x65, 0x6E, 0x00, 0x00, 0x41, 0x6E, 0x20, 0x54, 0x65, 0x61, 0x6D, 0x20,
        0x56, 0x69, 0x70, 0x65, 0x72, 0x20, 0x61, 0x6E, 0x67, 0x65, 0x73, 0x63, 0x68, 0x6C, 0x6F, 0x73,
        0x73, 0x65, 0x6E, 0x00, 0x57, 0x61, 0x73, 0x20, 0x66, 0xFC, 0x72, 0x20, 0x65, 0x69, 0x6E, 0x65,
        0x20, 0x44, 0x65, 0x6D, 0xFC, 0x74, 0x69, 0x67, 0x75, 0x6E, 0x67, 0x2E, 0x00, 0x00, 0x00, 0x00,
        0x47, 0x65, 0x74, 0xF6, 0x74, 0x65, 0x74, 0x20, 0x76, 0x6F, 0x6E, 0x20, 0x25, 0x73, 0x2E, 0x00,
        0x45, 0x72, 0x77, 0x69, 0x73, 0x63, 0x68, 0x74, 0x20, 0x76, 0x6F, 0x6E, 0x20, 0x25, 0x73, 0x2E,
        0x00, 0x00, 0x00, 0x00, 0x47, 0x65, 0x73, 0x63, 0x68, 0x6C, 0x61, 0x67, 0x65, 0x6E, 0x20, 0x76,
        0x6F, 0x6E, 0x20, 0x25, 0x73, 0x2E, 0x00, 0x00, 0x25, 0x73, 0x20, 0x68, 0x61, 0x74, 0x20, 0x44,
        0x69, 0x63, 0x68, 0x20, 0x61, 0x75, 0x73, 0x67, 0x65, 0x6C, 0xF6, 0x73, 0x63, 0x68, 0x74, 0x2E,
        0x00, 0x00, 0x00, 0x00, 0x25, 0x73, 0x20, 0x68, 0x61, 0x74, 0x20, 0x44, 0x69, 0x63, 0x68, 0x20,
        0x62, 0x65, 0x73, 0x69, 0x65, 0x67, 0x74, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x25, 0x73, 0x20, 0x68,
        0x61, 0x74, 0x20, 0x44, 0x69, 0x63, 0x68, 0x20, 0x67, 0x65, 0x6C, 0x79, 0x6E, 0x63, 0x68, 0x74,
        0x2E, 0x00, 0x00, 0x00, 0x56, 0x6F, 0x6E, 0x20, 0x25, 0x73, 0x20, 0x7A, 0x65, 0x72, 0x6D, 0x61,
        0x6C, 0x6D, 0x74, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x44, 0x75, 0x72, 0x63, 0x68, 0x20, 0x44, 0x65,
        0x69, 0x6E, 0x65, 0x20, 0x65, 0x69, 0x67, 0x65, 0x6E, 0x65, 0x20, 0x48, 0x61, 0x6E, 0x64, 0x2E,
        0x00, 0x00, 0x00, 0x00, 0x57, 0x61, 0x73, 0x20, 0x66, 0xFC, 0x72, 0x20, 0x65, 0x69, 0x6E, 0x65,
        0x20, 0x42, 0x65, 0x73, 0x74, 0x72, 0x61, 0x66, 0x75, 0x6E, 0x67, 0x2E, 0x00, 0x00, 0x00, 0x00,
        0x53, 0x63, 0x68, 0x6C, 0x65, 0x63, 0x68, 0x74, 0x65, 0x72, 0x20, 0x5A, 0x75, 0x67, 0x20, 0x2E,
        0x2E, 0x2E, 0x00, 0x00, 0xC4, 0x68, 0x6D, 0x20, 0x2E, 0x2E, 0x2E, 0x20, 0x20, 0x56, 0x6F, 0x72,
        0x73, 0x69, 0x63, 0x68, 0x74, 0x21, 0x00, 0x00, 0x53, 0x63, 0x68, 0x6D, 0x61, 0x74, 0x7A, 0x2E,
        0x00, 0x00, 0x00, 0x00, 0x55, 0x75, 0x70, 0x73, 0x20, 0x2E, 0x2E, 0x2E, 0x00, 0x00, 0x00, 0x00,
        0x44, 0x75, 0x20, 0x77, 0x75, 0x72, 0x64, 0x65, 0x73, 0x74, 0x20, 0x62, 0x65, 0x73, 0x69, 0x65,
        0x67, 0x74, 0x2E, 0x00, 0x45, 0x6D, 0x62, 0x72, 0x79, 0x6F, 0x20, 0x69, 0x6D, 0x70, 0x6C, 0x61,
        0x6E, 0x74, 0x69, 0x65, 0x72, 0x74, 0x00, 0x00, 0x45, 0x6D, 0x62, 0x72, 0x79, 0x6F, 0x20, 0x7A,
        0x65, 0x72, 0x73, 0x74, 0xF6, 0x72, 0x74, 0x00, 0x45, 0x72, 0x6C, 0x65, 0x64, 0x69, 0x67, 0x65,
        0x20, 0x25, 0x73, 0x00, 0x6F, 0x64, 0x65, 0x72, 0x20, 0x66, 0x69, 0x6E, 0x64, 0x65, 0x20, 0x64,
        0x65, 0x6E, 0x20, 0x45, 0x6E, 0x65, 0x72, 0x67, 0x69, 0x65, 0x6B, 0x65, 0x72, 0x6E, 0x00, 0x00,
        0x45, 0x6E, 0x65, 0x72, 0x67, 0x69, 0x65, 0x73, 0x74, 0xF6, 0xDF, 0x65, 0x00, 0x00, 0x00, 0x00,
        0x45, 0x6E, 0x65, 0x72, 0x67, 0x69, 0x65, 0x73, 0x74, 0xF6, 0xDF, 0x65, 0x00, 0x00, 0x00, 0x00,
        0x53, 0x63, 0x68, 0x75,
    },
    {
        0xDF000000, 0x53636875, 0xDF000000,
    },
    {
        0x45, 0x78, 0x70, 0x6C, 0x6F, 0x73, 0x69, 0x76, 0x67, 0x65, 0x73, 0x63, 0x68, 0x6F, 0x73, 0x73,
        0x65, 0x00, 0x00, 0x00, 0x45, 0x78, 0x70, 0x6C, 0x6F, 0x73, 0x69, 0x76, 0x67, 0x65, 0x73, 0x63,
        0x68, 0x6F, 0x73, 0x73, 0x65, 0x00, 0x00, 0x00, 0x4D, 0x75, 0x6E, 0x69, 0x74, 0x69, 0x6F, 0x6E,
        0x00, 0x00, 0x00, 0x00, 0x53, 0x63, 0x68, 0x75,
    },
    0xDF000000,
    {
        0x45, 0x6E, 0x65, 0x72, 0x67, 0x69, 0x65, 0x73, 0x74, 0x6F, 0xDF, 0x00, 0x45, 0x78, 0x70, 0x6C,
        0x6F, 0x73, 0x69, 0x76, 0x67, 0x65, 0x73, 0x63, 0x68, 0x6F, 0xDF, 0x00, 0x5A, 0x65, 0x72, 0x65,
        0x62, 0x72, 0x61, 0x6C, 0x62, 0x6F, 0x68, 0x72, 0x65, 0x72, 0x00, 0x00, 0x50, 0x66, 0x6D, 0x2D,
        0x4D, 0x69, 0x6E, 0x65, 0x00, 0x00, 0x00, 0x00, 0x57, 0x61, 0x63, 0x68, 0x74, 0x75, 0x72, 0x6D,
        0x00, 0x00, 0x00, 0x00, 0x45, 0x69, 0x73, 0x65, 0x6E, 0x6B, 0x6C, 0x61, 0x75, 0x65, 0x00, 0x00,
        0x54, 0x65, 0x6C, 0x65, 0x70, 0x6F, 0x72, 0x74, 0x2D, 0x4D, 0x69, 0x6E, 0x65, 0x00, 0x00, 0x00,
        0x56, 0x65, 0x72, 0x6C, 0x61, 0x6E, 0x67, 0x73, 0x61, 0x6D, 0x75, 0x6E, 0x67, 0x20, 0x2E, 0x2E,
        0x2E, 0x00, 0x00, 0x00, 0x53, 0x63, 0x68, 0x75, 0x74, 0x7A, 0x20, 0x2E, 0x2E, 0x2E, 0x00, 0x00,
        0x52, 0x65, 0x67, 0x65, 0x6E, 0x65, 0x72, 0x61, 0x74, 0x69, 0x6F, 0x6E, 0x20, 0x2E, 0x2E, 0x2E,
        0x00, 0x00, 0x00, 0x00, 0x56, 0x65, 0x72, 0x73, 0x74, 0x65, 0x69, 0x6E, 0x65, 0x72, 0x75, 0x6E,
        0x67, 0x20, 0x2E, 0x2E, 0x2E, 0x00, 0x00, 0x00, 0x53, 0x63, 0x68, 0x61, 0x64, 0x65, 0x6E, 0x73,
        0x75, 0x6D, 0x6B, 0x65, 0x68, 0x72, 0x20, 0x2E, 0x2E, 0x2E, 0x00, 0x00, 0x55, 0x6E, 0x73, 0x69,
        0x63, 0x68, 0x74, 0x62, 0x61, 0x72, 0x6B, 0x65, 0x69, 0x74, 0x20, 0x2E, 0x2E, 0x2E, 0x00, 0x00,
        0x45, 0x6E, 0x65, 0x72, 0x67, 0x69, 0x65, 0x2D, 0xFC, 0x62, 0x65, 0x72, 0x74, 0x72, 0x61, 0x67,
        0x75, 0x6E, 0x67, 0x20, 0x2E, 0x2E, 0x2E, 0x00, 0x47, 0x65, 0x73, 0x63, 0x68, 0x77, 0x69, 0x6E,
        0x64, 0x69, 0x67, 0x6B, 0x65, 0x69, 0x74, 0x20, 0x2E, 0x2E, 0x2E, 0x00, 0x54, 0x65, 0x6C, 0x65,
        0x70, 0x6F, 0x72, 0x74, 0x69, 0x65, 0x72, 0x65, 0x6E, 0x20, 0x2E, 0x2E, 0x2E, 0x00, 0x00, 0x00,
        0x49, 0x6E, 0x20, 0x53, 0x69, 0x63, 0x68, 0x65, 0x72, 0x68, 0x65, 0x69, 0x74, 0x20, 0x74, 0x65,
        0x6C, 0x65, 0x70, 0x6F, 0x72, 0x74, 0x69, 0x65, 0x72, 0x74, 0x20, 0x2E, 0x2E, 0x2E, 0x28, 0x3F,
        0x29, 0x00, 0x00, 0x00, 0x53, 0x63, 0x68, 0x77, 0x65, 0x72, 0x65, 0x72, 0x20, 0x53, 0x63, 0x68,
        0x61, 0x64, 0x65, 0x6E, 0x20, 0x2E, 0x2E, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x55, 0x6E, 0x76, 0x65,
        0x72, 0x77, 0x75, 0x6E, 0x64, 0x62, 0x61, 0x72, 0x6B, 0x65, 0x69, 0x74, 0x20, 0x2E, 0x2E, 0x2E,
        0x00, 0x00, 0x00, 0x00, 0x4B, 0x75, 0x67, 0x65, 0x6C, 0x73, 0x63, 0x68, 0x69, 0x6C, 0x64, 0x20,
        0x2E, 0x2E, 0x2E, 0x00, 0x45, 0x6E, 0x65, 0x72, 0x67, 0x69, 0x65, 0x73, 0x63, 0x68, 0x77, 0x75,
        0x6E, 0x64, 0x20, 0x2E, 0x2E, 0x2E, 0x00, 0x00, 0x45, 0x74, 0x77, 0x61, 0x73, 0x20, 0x61, 0x6E,
        0x64, 0x65, 0x72, 0x65, 0x73, 0x2E, 0x2E, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x53, 0x63, 0x68, 0x69,
        0x6C, 0x64, 0x00, 0x00, 0x70, 0x61, 0x72, 0x74, 0x69, 0x6B, 0x65, 0x6C, 0x62, 0x65, 0x73, 0x63,
        0x68, 0x6C, 0x65, 0x75, 0x6E, 0x69, 0x67, 0x65, 0x72, 0x2D, 0x74, 0x65, 0x69, 0x6C, 0x00, 0x00,
        0x56, 0x65, 0x72, 0x67, 0x65, 0x6C, 0x74, 0x75, 0x6E, 0x67, 0x21, 0x00, 0x46, 0x6C, 0x61, 0x67,
        0x67, 0x65, 0x20, 0x67, 0x65, 0x66, 0x6F, 0x72, 0x64, 0x65, 0x72, 0x74, 0x00, 0x00, 0x00, 0x00,
        0x46, 0x6C, 0x61, 0x67, 0x67, 0x65, 0x20, 0x65, 0x72, 0x6F, 0x62, 0x65, 0x72, 0x74, 0x00, 0x00,
        0x46, 0x6C, 0x61, 0x67, 0x67, 0x65, 0x20, 0x7A, 0x75, 0x72, 0xFC, 0x63, 0x6B, 0x67, 0x65, 0x62,
        0x72, 0x61, 0x63, 0x68, 0x74, 0x00, 0x00, 0x00, 0x44, 0x75, 0x20, 0x68, 0x61, 0x73, 0x74, 0x20,
        0x64, 0x69, 0x65, 0x20, 0x4D, 0x61, 0x63, 0x68, 0x74, 0x00, 0x00, 0x00, 0x74, 0x61, 0x6C, 0x6F,
        0x6E, 0x00, 0x00, 0x00, 0x6B, 0x61, 0x6D, 0x70, 0x66, 0x6B, 0x6C, 0x69, 0x6E, 0x67, 0x65, 0x00,
        0x62, 0x6F, 0x67, 0x65, 0x6E, 0x00, 0x00, 0x00, 0x74, 0x65, 0x6B, 0x20, 0x62, 0x6F, 0x67, 0x65,
        0x6E, 0x00, 0x00, 0x00, 0x70, 0x69, 0x73, 0x74, 0x6F, 0x6C, 0x65, 0x00, 0x6D, 0x61, 0x67, 0x6E,
        0x75, 0x6D, 0x00, 0x00, 0x62, 0x65, 0x74, 0xE4, 0x75, 0x62, 0x75, 0x6E, 0x67, 0x73, 0x67, 0x65,
        0x77, 0x65, 0x68, 0x72, 0x00, 0x00, 0x00, 0x00, 0x67, 0x65, 0x66, 0x72, 0x69, 0x65, 0x72, 0x6B,
        0x61, 0x6E, 0x6F, 0x6E, 0x65, 0x00, 0x00, 0x00, 0x67, 0x65, 0x77, 0x65, 0x68, 0x72, 0x00, 0x00,
        0x73, 0x63, 0x68, 0x72, 0x65, 0x64, 0x64, 0x65, 0x72, 0x00, 0x00, 0x00, 0x70, 0x6C, 0x61, 0x73,
        0x6D, 0x61, 0x67, 0x65, 0x73, 0x63, 0x68, 0xFC, 0x74, 0x7A, 0x00, 0x00, 0x66, 0x65, 0x75, 0x65,
        0x72, 0x73, 0x74, 0x75, 0x72, 0x6D, 0x2D, 0x6B, 0x61, 0x6E, 0x6F, 0x6E, 0x65, 0x00, 0x00, 0x00,
        0x73, 0x6F, 0x6E, 0x6E, 0x65, 0x6E, 0x66, 0x65, 0x75, 0x65, 0x72, 0x2D, 0x6B, 0x75, 0x67, 0x65,
        0x6C, 0x00, 0x00, 0x00, 0x73, 0x6F, 0x6E, 0x6E, 0x65, 0x6E, 0x66, 0x65, 0x75, 0x65, 0x72, 0x2D,
        0x6B, 0x75, 0x67, 0x65, 0x6C, 0x77, 0x65, 0x72, 0x66, 0x65, 0x72, 0x00, 0x7A, 0x69, 0x65, 0x6C,
        0x73, 0x75, 0x63, 0x68, 0x6B, 0x61, 0x6E, 0x6F, 0x6E, 0x65, 0x00, 0x00, 0x75, 0x2E, 0x66, 0x2E,
        0x6D, 0x2E, 0x2D, 0x77, 0x65, 0x72, 0x66, 0x65, 0x72, 0x00, 0x00, 0x00, 0x67, 0x72, 0x61, 0x6E,
        0x61, 0x74, 0x65, 0x6E, 0x77, 0x65, 0x72, 0x66, 0x65, 0x72, 0x00, 0x00, 0x73, 0x6B, 0x6F, 0x72,
        0x70, 0x69, 0x6F, 0x6E, 0x2D, 0x72, 0x61, 0x6B, 0x65, 0x74, 0x65, 0x6E, 0x77, 0x65, 0x72, 0x66,
        0x65, 0x72, 0x00, 0x00, 0x73, 0x70, 0x65, 0x65, 0x72, 0x67, 0x65, 0x73, 0x63, 0x68, 0xFC, 0x74,
        0x7A, 0x00, 0x00, 0x00, 0x74, 0x6F, 0x72, 0x70, 0x65, 0x64, 0x6F, 0x77, 0x65, 0x72, 0x66, 0x65,
        0x72, 0x00, 0x00, 0x00, 0x72, 0x69, 0x74, 0x74, 0x6B, 0x61, 0x6E, 0x6F, 0x6E, 0x65, 0x00, 0x00,
        0x66, 0x6C, 0x75, 0x67, 0x6B, 0x61, 0x6E, 0x6F, 0x6E, 0x65, 0x00, 0x00, 0x66, 0x6C, 0x61, 0x6D,
        0x6D, 0x65, 0x6E, 0x77, 0x65, 0x72, 0x66, 0x65, 0x72, 0x00, 0x00, 0x00, 0x6B, 0x6C, 0x69, 0x6E,
        0x67, 0x65, 0x6E, 0x77, 0x69, 0x6E, 0x64, 0x00, 0x70, 0x61, 0x72, 0x74, 0x69, 0x6B, 0x65, 0x6C,
        0x62, 0x65, 0x73, 0x63, 0x68, 0x6C, 0x65, 0x75, 0x6E, 0x69, 0x67, 0x65, 0x72, 0x00, 0x00, 0x00,
        0x6C, 0x65, 0x75, 0x63, 0x68, 0x74, 0x6B, 0x75, 0x67, 0x65, 0x6C, 0x00, 0x47, 0x72, 0x61, 0x70,
        0x70, 0x6C, 0x69, 0x6E, 0x67, 0x20, 0x48, 0x6F, 0x6F, 0x6B, 0x00, 0x00, 0x61, 0x72, 0x6D, 0x62,
        0x72, 0x75, 0x73, 0x74, 0x00, 0x00, 0x00, 0x00, 0x67, 0x65, 0x66, 0x72, 0x69, 0x65, 0x72, 0x6B,
        0x61, 0x6E, 0x6F, 0x6E, 0x65, 0x00, 0x00, 0x00, 0x66, 0x65, 0x75, 0x65, 0x72, 0x73, 0x74, 0x75,
        0x72, 0x6D, 0x2D, 0x6B, 0x61, 0x6E, 0x6F, 0x6E, 0x65, 0x00, 0x00, 0x00, 0x73, 0x63, 0x68, 0x72,
        0x65, 0x64, 0x64, 0x65, 0x72, 0x00, 0x00, 0x00, 0x70, 0x6C, 0x61, 0x73, 0x6D, 0x61, 0x67, 0x65,
        0x73, 0x63, 0x68, 0xFC, 0x74, 0x7A, 0x00, 0x00, 0x7A, 0x69, 0x65, 0x6C, 0x73, 0x75, 0x63, 0x68,
        0x6B, 0x61, 0x6E, 0x6F, 0x6E, 0x65, 0x00, 0x00, 0x67, 0x72, 0x61, 0x6E, 0x61, 0x74, 0x65, 0x6E,
        0x77, 0x65, 0x72, 0x66, 0x65, 0x72, 0x00, 0x00, 0x73, 0x6B, 0x6F, 0x72, 0x70, 0x69, 0x6F, 0x6E,
        0x2D, 0x0A, 0x72, 0x61, 0x6B, 0x65, 0x74, 0x65, 0x6E, 0x77, 0x65, 0x72, 0x66, 0x65, 0x72, 0x00,
        0x73, 0x70, 0x65, 0x65, 0x72, 0x67, 0x65, 0x73, 0x63, 0x68, 0xFC, 0x74, 0x7A, 0x00, 0x00, 0x00,
        0x74, 0x6F, 0x72, 0x70, 0x65, 0x64, 0x6F, 0x77, 0x65, 0x72, 0x66, 0x65, 0x72, 0x00, 0x00, 0x00,
        0x72, 0x61, 0x70, 0x74, 0x6F, 0x72, 0x2D, 0x6B, 0x6C, 0x61, 0x75, 0x65, 0x00, 0x00, 0x00, 0x00,
        0x4E, 0x4F, 0x56, 0x49, 0x5A, 0x45, 0x00, 0x00, 0x4E, 0x45, 0x55, 0x4C, 0x49, 0x4E, 0x47, 0x00,
        0x47, 0x52, 0x55, 0x4E, 0x5A, 0x45, 0x52, 0x00, 0x53, 0x43, 0x4F, 0x55, 0x54, 0x00, 0x00, 0x00,
        0x48, 0x45, 0x4C, 0x44, 0x00, 0x00, 0x00, 0x00, 0x53, 0x50, 0x55, 0x52, 0x45, 0x4E, 0x53, 0x55,
        0x43, 0x48, 0x45, 0x52, 0x00, 0x00, 0x00, 0x00, 0x4A, 0x65, 0x47, 0x45, 0x52, 0x00, 0x00, 0x00,
        0x4B, 0x65, 0x4D, 0x50, 0x46, 0x45, 0x52, 0x00, 0x44, 0x41, 0x52, 0x4B, 0x4C, 0x49, 0x4E, 0x47,
        0x00, 0x00, 0x00, 0x00, 0x53, 0x55, 0x43, 0x48, 0x45, 0x4E, 0x44, 0x45, 0x52, 0x00, 0x00, 0x00,
        0x4D, 0x6E, 0x52, 0x44, 0x45, 0x52, 0x00, 0x00, 0x56, 0x45, 0x52, 0x4E, 0x49, 0x43, 0x48, 0x54,
        0x45, 0x52, 0x00, 0x00, 0x4B, 0x52, 0x49, 0x45, 0x47, 0x53, 0x48, 0x45, 0x52, 0x52, 0x00, 0x00,
        0x54, 0x4F, 0x44, 0x45, 0x53, 0x57, 0x49, 0x4E, 0x44, 0x00, 0x00, 0x00, 0x45, 0x52, 0x4F, 0x42,
        0x45, 0x52, 0x45, 0x52, 0x00, 0x00, 0x00, 0x00, 0x4D, 0x45, 0x49, 0x53, 0x54, 0x45, 0x52, 0x00,
        0x54, 0x59, 0x52, 0x41, 0x4E, 0x54, 0x00, 0x00, 0x4B, 0x52, 0x49, 0x45, 0x47, 0x53, 0x53, 0x4B,
        0x4C, 0x41, 0x56, 0x45, 0x00, 0x00, 0x00, 0x00, 0x48, 0x41, 0x4E, 0x44, 0x20, 0x47, 0x4F, 0x54,
        0x54, 0x45, 0x53, 0x00, 0x48, 0x65, 0x55, 0x50, 0x54, 0x4C, 0x49, 0x4E, 0x47, 0x00, 0x00, 0x00,
        0x44, 0x55, 0x52, 0x43, 0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x46, 0x49,
        0x52, 0x53, 0x54, 0x20, 0x54, 0x52, 0x49, 0x41, 0x4C, 0x00, 0x00, 0x00, 0x44, 0x55, 0x52, 0x43,
        0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x42, 0x41, 0x53, 0x49, 0x43, 0x20,
        0x54, 0x52, 0x41, 0x49, 0x4E, 0x49, 0x4E, 0x47, 0x00, 0x00, 0x00, 0x00, 0x44, 0x55, 0x52, 0x43,
        0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x43, 0x52, 0x4F, 0x53, 0x53, 0x52,
        0x4F, 0x41, 0x44, 0x53, 0x00, 0x00, 0x00, 0x00, 0x44, 0x55, 0x52, 0x43, 0x48, 0x47, 0x45, 0x46,
        0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x47, 0x52, 0x49, 0x4D, 0x20, 0x52, 0x45, 0x54, 0x52, 0x45,
        0x41, 0x54, 0x00, 0x00, 0x44, 0x55, 0x52, 0x43, 0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54,
        0x3A, 0x20, 0x43, 0x41, 0x54, 0x48, 0x45, 0x44, 0x52, 0x41, 0x4C, 0x00, 0x44, 0x55, 0x52, 0x43,
        0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x46, 0x41, 0x4C, 0x4C, 0x4F, 0x55,
        0x54, 0x00, 0x00, 0x00, 0x44, 0x55, 0x52, 0x43, 0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54,
        0x3A, 0x20, 0x42, 0x4F, 0x58, 0x45, 0x44, 0x20, 0x53, 0x45, 0x54, 0x00, 0x44, 0x55, 0x52, 0x43,
        0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x44, 0x49, 0x52, 0x45, 0x20, 0x53,
        0x54, 0x52, 0x41, 0x49, 0x47, 0x48, 0x54, 0x00, 0x44, 0x55, 0x52, 0x43, 0x48, 0x47, 0x45, 0x46,
        0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x50, 0x52, 0x45, 0x59, 0x00, 0x00, 0x44, 0x55, 0x52, 0x43,
        0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x57, 0x41, 0x52, 0x45, 0x48, 0x4F,
        0x55, 0x53, 0x45, 0x00, 0x44, 0x55, 0x52, 0x43, 0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54,
        0x3A, 0x20, 0x57, 0x41, 0x54, 0x45, 0x52, 0x20, 0x54, 0x45, 0x4D, 0x50, 0x4C, 0x45, 0x00, 0x00,
        0x44, 0x55, 0x52, 0x43, 0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x42, 0x4F,
        0x4D, 0x42, 0x20, 0x53, 0x48, 0x45, 0x4C, 0x54, 0x45, 0x52, 0x00, 0x00, 0x44, 0x55, 0x52, 0x43,
        0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x54, 0x45, 0x4D, 0x50, 0x45, 0x52,
        0x45, 0x44, 0x00, 0x00, 0x44, 0x55, 0x52, 0x43, 0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54,
        0x3A, 0x20, 0x45, 0x41, 0x52, 0x54, 0x48, 0x20, 0x54, 0x45, 0x4D, 0x50, 0x4C, 0x45, 0x00, 0x00,
        0x44, 0x55, 0x52, 0x43, 0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x46, 0x49,
        0x52, 0x45, 0x20, 0x54, 0x45, 0x4D, 0x50, 0x4C, 0x45, 0x00, 0x00, 0x00, 0x44, 0x55, 0x52, 0x43,
        0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x4D, 0x59, 0x53, 0x54, 0x49, 0x43,
        0x00, 0x00, 0x00, 0x00, 0x44, 0x55, 0x52, 0x43, 0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54,
        0x3A, 0x20, 0x42, 0x4F, 0x54, 0x54, 0x4C, 0x45, 0x4E, 0x45, 0x43, 0x4B, 0x00, 0x00, 0x00, 0x00,
        0x44, 0x55, 0x52, 0x43, 0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x54, 0x49,
        0x47, 0x48, 0x54, 0x52, 0x4F, 0x50, 0x45, 0x00, 0x44, 0x55, 0x52, 0x43, 0x48, 0x47, 0x45, 0x46,
        0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x54, 0x48, 0x45, 0x20, 0x50, 0x49, 0x54, 0x00, 0x00, 0x00,
        0x44, 0x55, 0x52, 0x43, 0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x4C, 0x45,
        0x41, 0x50, 0x20, 0x4F, 0x46, 0x20, 0x46, 0x41, 0x49, 0x54, 0x48, 0x00, 0x44, 0x55, 0x52, 0x43,
        0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x57, 0x49, 0x43, 0x4B, 0x45, 0x44,
        0x20, 0x44, 0x41, 0x4E, 0x43, 0x45, 0x00, 0x00, 0x44, 0x55, 0x52, 0x43, 0x48, 0x47, 0x45, 0x46,
        0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x42, 0x55, 0x4E, 0x4B, 0x45, 0x52, 0x00, 0x00, 0x00, 0x00,
        0x44, 0x55, 0x52, 0x43, 0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x41, 0x4D,
        0x50, 0x48, 0x49, 0x54, 0x48, 0x45, 0x41, 0x54, 0x45, 0x52, 0x00, 0x00, 0x44, 0x55, 0x52, 0x43,
        0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x46, 0x49, 0x52, 0x45, 0x20, 0x57,
        0x41, 0x4C, 0x4B, 0x45, 0x52, 0x00, 0x00, 0x00, 0x44, 0x55, 0x52, 0x43, 0x48, 0x47, 0x45, 0x46,
        0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x43, 0x52, 0x59, 0x50, 0x54, 0x53, 0x00, 0x00, 0x00, 0x00,
        0x44, 0x55, 0x52, 0x43, 0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x42, 0x52,
        0x45, 0x41, 0x4B, 0x44, 0x4F, 0x57, 0x4E, 0x00, 0x44, 0x55, 0x52, 0x43, 0x48, 0x47, 0x45, 0x46,
        0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x52, 0x45, 0x54, 0x41, 0x4C, 0x49, 0x41, 0x54, 0x49, 0x4F,
        0x4E, 0x00, 0x00, 0x00, 0x44, 0x55, 0x52, 0x43, 0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54,
        0x3A, 0x20, 0x48, 0x4F, 0x50, 0x45, 0x4C, 0x45, 0x53, 0x53, 0x00, 0x00, 0x44, 0x55, 0x52, 0x43,
        0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x4D, 0x41, 0x54, 0x52, 0x49, 0x58,
        0x00, 0x00, 0x00, 0x00, 0x44, 0x55, 0x52, 0x43, 0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54,
        0x3A, 0x20, 0x46, 0x41, 0x54, 0x48, 0x4F, 0x4D, 0x00, 0x00, 0x00, 0x00, 0x44, 0x55, 0x52, 0x43,
        0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x54, 0x48, 0x45, 0x20, 0x50, 0x45,
        0x44, 0x45, 0x53, 0x54, 0x41, 0x4C, 0x00, 0x00, 0x44, 0x55, 0x52, 0x43, 0x48, 0x47, 0x45, 0x46,
        0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x44, 0x45, 0x46, 0x43, 0x4F, 0x4E, 0x20, 0x35, 0x00, 0x00,
        0x44, 0x55, 0x52, 0x43, 0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x53, 0x50,
        0x49, 0x52, 0x49, 0x54, 0x20, 0x54, 0x45, 0x4D, 0x50, 0x4C, 0x45, 0x00, 0x44, 0x55, 0x52, 0x43,
        0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x53, 0x54, 0x52, 0x4F, 0x4E, 0x47,
        0x48, 0x4F, 0x4C, 0x44, 0x00, 0x00, 0x00, 0x00, 0x44, 0x55, 0x52, 0x43, 0x48, 0x47, 0x45, 0x46,
        0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x43, 0x4F, 0x55, 0x52, 0x54, 0x59, 0x41, 0x52, 0x44, 0x00,
        0x44, 0x55, 0x52, 0x43, 0x48, 0x47, 0x45, 0x46, 0x62, 0x48, 0x52, 0x54, 0x3A, 0x20, 0x53, 0x54,
        0x41, 0x52, 0x4C, 0x49, 0x47, 0x48, 0x54, 0x00, 0x31, 0x35, 0x20, 0x46, 0x52, 0x41, 0x47, 0x53,
        0x20, 0x49, 0x4E, 0x20, 0x35, 0x20, 0x4D, 0x49, 0x4E, 0x55, 0x54, 0x45, 0x4E, 0x00, 0x00, 0x00,
        0x32, 0x35, 0x20, 0x46, 0x52, 0x41, 0x47, 0x53, 0x20, 0x49, 0x4E, 0x20, 0x31, 0x30, 0x20, 0x4D,
        0x49, 0x4E, 0x55, 0x54, 0x45, 0x4E, 0x00, 0x00, 0x4B, 0x45, 0x49, 0x4E, 0x45, 0x20, 0x46, 0x52,
        0x41, 0x47, 0x53, 0x00, 0x46, 0x62, 0x4E, 0x46, 0x4D, 0x41, 0x4C, 0x20, 0x53, 0x45, 0x4C, 0x42,
        0x53, 0x54, 0x20, 0x47, 0x45, 0x54, 0x6E, 0x54, 0x45, 0x54, 0x00, 0x00, 0x4C, 0x45, 0x54, 0x5A,
        0x54, 0x45, 0x52, 0x00, 0x46, 0x52, 0x41, 0x47, 0x2D, 0x41, 0x55, 0x53, 0x5A, 0x45, 0x49, 0x43,
        0x48, 0x4E, 0x55, 0x4E, 0x47, 0x45, 0x4E, 0x00, 0x54, 0x52, 0x4F, 0x50, 0x48, 0x65, 0x45, 0x4E,
        0x20, 0x46, 0x62, 0x52, 0x20, 0x41, 0x42, 0x53, 0x43, 0x48, 0x62, 0x53, 0x53, 0x45, 0x00, 0x00,
        0x31, 0x30, 0x20, 0x53, 0x50, 0x49, 0x45, 0x4C, 0x45, 0x52, 0x20, 0x49, 0x4E, 0x20, 0x45, 0x49,
        0x4E, 0x45, 0x52, 0x20, 0x52, 0x55, 0x4E, 0x44, 0x45, 0x20, 0x41, 0x55, 0x53, 0x47, 0x45, 0x53,
        0x43, 0x48, 0x41, 0x4C, 0x54, 0x45, 0x54, 0x00, 0x49, 0x4E, 0x20, 0x44, 0x49, 0x45, 0x53, 0x45,
        0x52, 0x20, 0x52, 0x55, 0x4E, 0x44, 0x45, 0x20, 0x4E, 0x49, 0x43, 0x48, 0x54, 0x20, 0x47, 0x45,
        0x54, 0x6E, 0x54, 0x45, 0x54, 0x00, 0x00, 0x00, 0x42, 0x41, 0x53, 0x54, 0x49, 0x4C, 0x4C, 0x45,
        0x20, 0x42, 0x45, 0x53, 0x49, 0x45, 0x47, 0x54, 0x00, 0x00, 0x00, 0x00, 0x53, 0x59, 0x52, 0x41,
        0x20, 0x42, 0x45, 0x53, 0x49, 0x45, 0x47, 0x54, 0x00, 0x00, 0x00, 0x00, 0x53, 0x59, 0x4D, 0x42,
        0x49, 0x4F, 0x4E, 0x54, 0x20, 0x42, 0x45, 0x53, 0x49, 0x45, 0x47, 0x54, 0x00, 0x00, 0x00, 0x00,
        0x54, 0x41, 0x4C, 0x2D, 0x53, 0x45, 0x54, 0x20, 0x42, 0x45, 0x53, 0x49, 0x45, 0x47, 0x54, 0x00,
        0x4B, 0x4F, 0x4F, 0x50, 0x45, 0x52, 0x41, 0x54, 0x49, 0x56, 0x2D, 0x53, 0x5A, 0x45, 0x4E, 0x41,
        0x52, 0x49, 0x4F, 0x20, 0x42, 0x45, 0x45, 0x4E, 0x44, 0x45, 0x54, 0x00, 0x3C, 0x4C, 0x45, 0x45,
        0x52, 0x3E, 0x00, 0x00, 0x3C, 0x4E, 0x45, 0x55, 0x45, 0x52, 0x20, 0x53, 0x50, 0x49, 0x45, 0x4C,
        0x45, 0x52, 0x3E, 0x00, 0x54, 0x55, 0x52, 0x4F, 0x4B, 0x00, 0x00, 0x00, 0x57, 0x41, 0x52, 0x52,
        0x49, 0x4F, 0x52, 0x00, 0x4D, 0x41, 0x53, 0x54, 0x45, 0x52, 0x00, 0x00, 0x41, 0x4C, 0x50, 0x48,
        0x41, 0x00, 0x00, 0x00, 0x42, 0x45, 0x54, 0x41, 0x00, 0x00, 0x00, 0x00, 0x47, 0x41, 0x4D, 0x4D,
        0x41, 0x00, 0x00, 0x00, 0x43, 0x41, 0x4D, 0x50, 0x41, 0x49, 0x4E, 0x00, 0x53, 0x4C, 0x41, 0x56,
        0x45, 0x52, 0x00, 0x00, 0x54, 0x59, 0x52, 0x41, 0x4E, 0x54, 0x00, 0x00, 0x46, 0x49, 0x52, 0x45,
        0x42, 0x4F, 0x52, 0x4E, 0x00, 0x00, 0x00, 0x00, 0x49, 0x43, 0x45, 0x4C, 0x4F, 0x52, 0x44, 0x00,
        0x45, 0x4E, 0x54, 0x52, 0x41, 0x49, 0x4C, 0x00, 0x4D, 0x49, 0x54, 0x45, 0x53, 0x00, 0x00, 0x00,
        0x43, 0x4F, 0x4D, 0x50, 0x49, 0x45, 0x53, 0x00, 0x54, 0x45, 0x44, 0x44, 0x49, 0x45, 0x53, 0x00,
        0x4A, 0x55, 0x47, 0x47, 0x4E, 0x41, 0x55, 0x54, 0x00, 0x00, 0x00, 0x00, 0x53, 0x4C, 0x4F, 0x54,
        0x48, 0x00, 0x00, 0x00, 0x4D, 0x41, 0x55, 0x4C, 0x45, 0x52, 0x00, 0x00, 0x44, 0x52, 0x4F, 0x4E,
        0x45, 0x00, 0x00, 0x00, 0x47, 0x52, 0x55, 0x4E, 0x54, 0x00, 0x00, 0x00, 0x53, 0x4C, 0x41, 0x56,
        0x45, 0x00, 0x00, 0x00, 0x53, 0x4F, 0x4C, 0x44, 0x49, 0x45, 0x52, 0x00, 0x43, 0x41, 0x50, 0x54,
        0x41, 0x49, 0x4E, 0x00, 0x4B, 0x49, 0x4E, 0x47, 0x00, 0x00, 0x00, 0x00, 0x42, 0x41, 0x53, 0x54,
        0x49, 0x4C, 0x4C, 0x45, 0x00, 0x00, 0x00, 0x00, 0x54, 0x41, 0x4C, 0x20, 0x53, 0x45, 0x54, 0x00,
        0x53, 0x59, 0x52, 0x41, 0x00, 0x00, 0x00, 0x00, 0x53, 0x59, 0x4D, 0x42, 0x49, 0x4F, 0x4E, 0x54,
        0x00, 0x00, 0x00, 0x00, 0x47, 0x55, 0x41, 0x52, 0x44, 0x49, 0x41, 0x4E, 0x00, 0x00, 0x00, 0x00,
        0x52, 0x41, 0x56, 0x41, 0x47, 0x45, 0x00, 0x00, 0x43, 0x59, 0x43, 0x4C, 0x4F, 0x50, 0x53, 0x00,
        0x4C, 0x4F, 0x52, 0x44, 0x44, 0x45, 0x41, 0x44, 0x00, 0x00, 0x00, 0x00, 0x4D, 0x41, 0x47, 0x47,
        0x4F, 0x54, 0x00, 0x00, 0x56, 0x49, 0x4C, 0x45, 0x00, 0x00, 0x00, 0x00, 0x45, 0x4C, 0x49, 0x54,
        0x45, 0x00, 0x00, 0x00, 0x42, 0x49, 0x4F, 0x42, 0x4F, 0x54, 0x00, 0x00, 0x4B, 0x49, 0x4C, 0x4C,
        0x42, 0x4F, 0x54, 0x00, 0x44, 0x45, 0x41, 0x54, 0x48, 0x00, 0x00, 0x00, 0x52, 0x45, 0x41, 0x50,
        0x45, 0x52, 0x00, 0x00, 0x4D, 0x41, 0x57, 0x00, 0x52, 0x41, 0x50, 0x54, 0x4F, 0x52, 0x00, 0x00,
        0x53, 0x4C, 0x41, 0x47, 0x00, 0x00, 0x00, 0x00, 0x43, 0x4C, 0x41, 0x57, 0x00, 0x00, 0x00, 0x00,
        0x57, 0x41, 0x52, 0x43, 0x4C, 0x55, 0x42, 0x53, 0x00, 0x00, 0x00, 0x00, 0x54, 0x55, 0x52, 0x4F,
        0x4B, 0x00, 0x00, 0x00, 0x4D, 0x41, 0x4E, 0x54, 0x49, 0x44, 0x20, 0x44, 0x52, 0x4F, 0x4E, 0x45,
        0x00, 0x00, 0x00, 0x00, 0x43, 0x41, 0x4D, 0x50, 0x41, 0x49, 0x47, 0x4E, 0x45, 0x52, 0x00, 0x00,
        0x46, 0x49, 0x52, 0x45, 0x42, 0x4F, 0x52, 0x4E, 0x00, 0x00, 0x00, 0x00, 0x4D, 0x41, 0x4E, 0x54,
        0x49, 0x44, 0x20, 0x53, 0x4F, 0x4C, 0x44, 0x49, 0x45, 0x52, 0x00, 0x00, 0x41, 0x4C, 0x50, 0x48,
        0x41, 0x00, 0x00, 0x00, 0x4C, 0x4F, 0x52, 0x44, 0x20, 0x4F, 0x46, 0x20, 0x54, 0x48, 0x45, 0x20,
        0x44, 0x45, 0x41, 0x44, 0x00, 0x00, 0x00, 0x00, 0x45, 0x4C, 0x49, 0x54, 0x45, 0x20, 0x47, 0x55,
        0x41, 0x52, 0x44, 0x00, 0x47, 0x55, 0x41, 0x52, 0x44, 0x49, 0x41, 0x4E, 0x00, 0x00, 0x00, 0x00,
        0x4A, 0x55, 0x47, 0x47, 0x45, 0x52, 0x4E, 0x41, 0x55, 0x54, 0x00, 0x00, 0x4F, 0x42, 0x4C, 0x49,
        0x56, 0x49, 0x4F, 0x4E, 0x20, 0x53, 0x50, 0x41, 0x57, 0x4E, 0x00, 0x00, 0x42, 0x41, 0x53, 0x54,
        0x49, 0x4C, 0x4C, 0x45, 0x00, 0x00, 0x00, 0x00, 0x53, 0x59, 0x52, 0x41, 0x00, 0x00, 0x00, 0x00,
        0x53, 0x59, 0x4D, 0x42, 0x49, 0x4F, 0x4E, 0x54, 0x00, 0x00, 0x00, 0x00, 0x54, 0x41, 0x4C, 0x20,
        0x53, 0x45, 0x54, 0x00, 0x52, 0x41, 0x50, 0x54, 0x4F, 0x52, 0x00, 0x00, 0x4D, 0x41, 0x4E, 0x54,
        0x49, 0x44, 0x20, 0x4D, 0x49, 0x54, 0x45, 0x53, 0x00, 0x00, 0x00, 0x00, 0x46, 0x6C, 0x61, 0x67,
        0x67, 0x65, 0x20, 0x25, 0x64, 0x20, 0x4D, 0x61, 0x6C, 0x20, 0x65, 0x72, 0x6F, 0x62, 0x65, 0x72,
        0x6E, 0x00, 0x00, 0x00, 0x46, 0x6C, 0x61, 0x67, 0x67, 0x65, 0x20, 0x25, 0x64, 0x20, 0x4D, 0x61,
        0x6C, 0x20, 0x65, 0x72, 0x6F, 0x62, 0x65, 0x72, 0x6E, 0x00, 0x00, 0x00, 0x25, 0x64, 0x20, 0x54,
        0x65, 0x61, 0x6D, 0x2D, 0x43, 0x61, 0x70, 0x74, 0x75, 0x72, 0x65, 0x73, 0x20, 0x65, 0x72, 0x6F,
        0x62, 0x65, 0x72, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x54, 0x61, 0x67, 0x20, 0x74, 0x68, 0x65, 0x20,
        0x4D, 0x6F, 0x6E, 0x6B, 0x65, 0x79, 0x20, 0x25, 0x64, 0x20, 0x4D, 0x61, 0x6C, 0x00, 0x00, 0x00,
        0x54, 0x61, 0x67, 0x20, 0x74, 0x68, 0x65, 0x20, 0x4D, 0x6F, 0x6E, 0x6B, 0x65, 0x79, 0x20, 0x25,
        0x64, 0x20, 0x4D, 0x61, 0x6C, 0x00, 0x00, 0x00, 0x25, 0x64, 0x20, 0x4B, 0x72, 0x65, 0x61, 0x74,
        0x75, 0x72, 0x2D, 0x54, 0x61, 0x67, 0x73, 0x20, 0x65, 0x72, 0x6F, 0x62, 0x65, 0x72, 0x6E, 0x00,
        0x25, 0x64, 0x20, 0x46, 0x72, 0x61, 0x67, 0x20, 0x65, 0x72, 0x6F, 0x62, 0x65, 0x72, 0x6E, 0x00,
        0x25, 0x64, 0x20, 0x46, 0x72, 0x61, 0x67, 0x73, 0x20, 0x65, 0x72, 0x6F, 0x62, 0x65, 0x72, 0x6E,
        0x00, 0x00, 0x00, 0x00, 0x25, 0x64, 0x20, 0x54, 0x65, 0x61, 0x6D, 0x2D, 0x46, 0x72, 0x61, 0x67,
        0x20, 0x65, 0x72, 0x6F, 0x62, 0x65, 0x72, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x25, 0x64, 0x20, 0x54,
        0x65, 0x61, 0x6D, 0x2D, 0x46, 0x72, 0x61, 0x67, 0x73, 0x20, 0x65, 0x72, 0x6F, 0x62, 0x65, 0x72,
        0x6E, 0x00, 0x00, 0x00, 0x69, 0x6E, 0x20, 0x25, 0x30, 0x32, 0x64, 0x20, 0x53, 0x65, 0x6B, 0x75,
        0x6E, 0x64, 0x65, 0x6E, 0x20, 0x6F, 0x64, 0x65, 0x72, 0x20, 0x77, 0x65, 0x6E, 0x69, 0x67, 0x65,
        0x72, 0x00, 0x00, 0x00, 0x69, 0x6E, 0x20, 0x25, 0x64, 0x20, 0x4D, 0x69, 0x6E, 0x75, 0x74, 0x65,
        0x20, 0x75, 0x6E, 0x64, 0x20, 0x25, 0x30, 0x32, 0x64, 0x20, 0x53, 0x65, 0x6B, 0x75, 0x6E, 0x64,
        0x65, 0x6E, 0x20, 0x6F, 0x64, 0x65, 0x72, 0x20, 0x77, 0x65, 0x6E, 0x69, 0x67, 0x65, 0x72, 0x00,
        0x69, 0x6E, 0x20, 0x25, 0x64, 0x20, 0x4D, 0x69, 0x6E, 0x75, 0x74, 0x65, 0x6E, 0x20, 0x75, 0x6E,
        0x64, 0x20, 0x25, 0x30, 0x32, 0x64, 0x20, 0x53, 0x65, 0x6B, 0x75, 0x6E, 0x64, 0x65, 0x6E, 0x20,
        0x6F, 0x64, 0x65, 0x72, 0x20, 0x77, 0x65, 0x6E, 0x69, 0x67, 0x65, 0x72, 0x00, 0x00, 0x00, 0x00,
        0x69, 0x6E, 0x20, 0x25, 0x64, 0x20, 0x4D, 0x69, 0x6E, 0x75, 0x74, 0x65, 0x20, 0x6F, 0x64, 0x65,
        0x72, 0x20, 0x77, 0x65, 0x6E, 0x69, 0x67, 0x65, 0x72, 0x00, 0x00, 0x00, 0x69, 0x6E, 0x20, 0x25,
        0x64, 0x20, 0x4D, 0x69, 0x6E, 0x75, 0x74, 0x65, 0x6E, 0x20, 0x6F, 0x64, 0x65, 0x72, 0x20, 0x77,
        0x65, 0x6E, 0x69, 0x67, 0x65, 0x72, 0x00, 0x00, 0x6D, 0x69, 0x74, 0x20, 0x25, 0x64, 0x20, 0x4C,
        0x65, 0x62, 0x65, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x6D, 0x69, 0x74, 0x20, 0x25, 0x64, 0x20, 0x4C,
        0x65, 0x62, 0x65, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x25, 0x73, 0x20, 0x62, 0x65, 0x73, 0x69, 0x65,
        0x67, 0x74, 0x00, 0x00, 0x25, 0x73, 0x20, 0x75, 0x6E, 0x64, 0x20, 0x25, 0x73, 0x20, 0x62, 0x65,
        0x73, 0x69, 0x65, 0x67, 0x74, 0x00, 0x00, 0x00, 0x4A, 0x65, 0x64, 0x65, 0x72, 0x20, 0x66, 0xFC,
        0x72, 0x20, 0x73, 0x69, 0x63, 0x68, 0x00, 0x00, 0x45, 0x49, 0x4E, 0x46, 0x41, 0x43, 0x48, 0x00,
        0x4D, 0x49, 0x54, 0x54, 0x45, 0x4C, 0x00, 0x00, 0x53, 0x43, 0x48, 0x57, 0x45, 0x52, 0x00, 0x00,
        0x41, 0x55, 0x53, 0x00, 0x45, 0x49, 0x4E, 0x00, 0x52, 0x4F, 0x54, 0x00, 0x47, 0x52, 0x62, 0x4E,
        0x00, 0x00, 0x00, 0x00, 0x48, 0x4F, 0x52, 0x49, 0x5A, 0x4F, 0x4E, 0x54, 0x41, 0x4C, 0x00, 0x00,
        0x56, 0x45, 0x52, 0x54, 0x49, 0x4B, 0x41, 0x4C, 0x00, 0x00, 0x00, 0x00, 0x4E, 0x49, 0x45, 0x44,
        0x52, 0x49, 0x47, 0x45, 0x20, 0x41, 0x55, 0x46, 0x4C, 0x6E, 0x53, 0x2E, 0x00, 0x00, 0x00, 0x00,
        0x48, 0x4F, 0x48, 0x45, 0x20, 0x41, 0x55, 0x46, 0x4C, 0x6E, 0x53, 0x2E, 0x00, 0x00, 0x00, 0x00,
        0x4C, 0x45, 0x54, 0x54, 0x45, 0x52, 0x42, 0x4F, 0x58, 0x00, 0x00, 0x00, 0x4E, 0x45, 0x49, 0x4E,
        0x00, 0x00, 0x00, 0x00, 0x4A, 0x41, 0x00, 0x00, 0x4E, 0x4F, 0x56, 0x49, 0x5A, 0x45, 0x00, 0x00,
        0x45, 0x49, 0x4E, 0x46, 0x41, 0x43, 0x48, 0x00, 0x4E, 0x4F, 0x52, 0x4D, 0x41, 0x4C, 0x00, 0x00,
        0x56, 0x45, 0x54, 0x45, 0x52, 0x41, 0x4E, 0x00, 0x45, 0x58, 0x50, 0x45, 0x52, 0x54, 0x45, 0x00,
        0x41, 0x52, 0x43, 0x41, 0x44, 0x45, 0x00, 0x00, 0x52, 0x41, 0x44, 0x00, 0x54, 0x41, 0x50, 0x00,
        0x47, 0x45, 0x4D, 0x49, 0x53, 0x43, 0x48, 0x54, 0x00, 0x00, 0x00, 0x00, 0x43, 0x4F, 0x4E, 0x54,
        0x52, 0x4F, 0x4C, 0x4C, 0x45, 0x52, 0x20, 0x25, 0x64, 0x00, 0x00, 0x00, 0x43, 0x54, 0x46, 0x00,
        0x54, 0x42, 0x4C, 0x00, 0x42, 0x4C, 0x00, 0x00, 0x46, 0x54, 0x00, 0x00, 0x47, 0x41, 0x55, 0x4E,
        0x54, 0x4C, 0x45, 0x54, 0x00, 0x00, 0x00, 0x00, 0x46, 0x52, 0x41, 0x47, 0x46, 0x45, 0x53, 0x54,
        0x00, 0x00, 0x00, 0x00, 0x5A, 0x45, 0x49, 0x54, 0x53, 0x50, 0x49, 0x45, 0x4C, 0x00, 0x00, 0x00,
        0x53, 0x50, 0x49, 0x45, 0x4C, 0x45, 0x52, 0x25, 0x64, 0x00, 0x00, 0x00, 0x41, 0x44, 0x4C, 0x45,
        0x52, 0x2D, 0x54, 0x41, 0x4C, 0x49, 0x53, 0x4D, 0x41, 0x4E, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E,
        0x44, 0x45, 0x4E, 0x2E, 0x20, 0x31, 0x20, 0x4C, 0x45, 0x42, 0x45, 0x4E, 0x20, 0x47, 0x45, 0x57,
        0x4F, 0x4E, 0x4E, 0x45, 0x4E, 0x00, 0x00, 0x00, 0x48, 0x41, 0x4C, 0x42, 0x45, 0x4E, 0x20, 0x41,
        0x44, 0x4C, 0x45, 0x52, 0x2D, 0x54, 0x41, 0x4C, 0x49, 0x53, 0x4D, 0x41, 0x4E, 0x2E, 0x20, 0x31,
        0x20, 0x4C, 0x45, 0x42, 0x45, 0x4E, 0x20, 0x46, 0x62, 0x52, 0x20, 0x45, 0x49, 0x4E, 0x45, 0x4E,
        0x20, 0x5A, 0x57, 0x45, 0x49, 0x54, 0x45, 0x4E, 0x00, 0x00, 0x00, 0x00, 0x5A, 0x57, 0x45, 0x49,
        0x54, 0x45, 0x4E, 0x20, 0x41, 0x44, 0x4C, 0x45, 0x52, 0x2D, 0x54, 0x41, 0x4C, 0x49, 0x53, 0x4D,
        0x41, 0x4E, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x2E, 0x20, 0x45, 0x49, 0x4E,
        0x20, 0x4C, 0x45, 0x42, 0x45, 0x4E, 0x20, 0x47, 0x45, 0x57, 0x4F, 0x4E, 0x4E, 0x45, 0x4E, 0x21,
        0x00, 0x00, 0x00, 0x00, 0x42, 0x65, 0x52, 0x2D, 0x54, 0x41, 0x4C, 0x49, 0x53, 0x4D, 0x41, 0x4E,
        0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x2E, 0x20, 0x35, 0x20, 0x5A, 0x55, 0x53,
        0x65, 0x54, 0x5A, 0x4C, 0x49, 0x43, 0x48, 0x45, 0x20, 0x53, 0x50, 0x52, 0x45, 0x4E, 0x47, 0x4B,
        0x6E, 0x52, 0x50, 0x45, 0x52, 0x00, 0x00, 0x00, 0x4B, 0x4F, 0x4A, 0x4F, 0x54, 0x45, 0x2D, 0x54,
        0x41, 0x4C, 0x49, 0x53, 0x4D, 0x41, 0x4E, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E,
        0x2E, 0x20, 0x35, 0x30, 0x20, 0x53, 0x43, 0x48, 0x55, 0x53, 0x53, 0x20, 0x4D, 0x55, 0x4E, 0x49,
        0x54, 0x49, 0x4F, 0x4E, 0x00, 0x00, 0x00, 0x00, 0x50, 0x55, 0x4D, 0x41, 0x2D, 0x54, 0x41, 0x4C,
        0x49, 0x53, 0x4D, 0x41, 0x4E, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x2E, 0x20,
        0x35, 0x30, 0x20, 0x5A, 0x55, 0x53, 0x65, 0x54, 0x5A, 0x4C, 0x49, 0x43, 0x48, 0x45, 0x20, 0x45,
        0x4E, 0x45, 0x52, 0x47, 0x49, 0x45, 0x53, 0x54, 0x6E, 0x53, 0x53, 0x45, 0x00, 0x00, 0x00, 0x00,
        0x56, 0x49, 0x50, 0x45, 0x52, 0x2D, 0x54, 0x41, 0x4C, 0x49, 0x53, 0x4D, 0x41, 0x4E, 0x20, 0x47,
        0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x2E, 0x20, 0x4D, 0x41, 0x58, 0x2E, 0x20, 0x47, 0x45,
        0x53, 0x55, 0x4E, 0x44, 0x48, 0x45, 0x49, 0x54, 0x20, 0x55, 0x4D, 0x20, 0x35, 0x20, 0x45, 0x52,
        0x48, 0x6E, 0x48, 0x54, 0x00, 0x00, 0x00, 0x00, 0x4B, 0x4F, 0x4F, 0x50, 0x45, 0x52, 0x41, 0x54,
        0x49, 0x56, 0x45, 0x2D, 0x54, 0x41, 0x4C, 0x49, 0x53, 0x4D, 0x41, 0x4E, 0x20, 0x47, 0x45, 0x46,
        0x55, 0x4E, 0x44, 0x45, 0x4E, 0x00, 0x00, 0x00, 0x4D, 0x49, 0x4E, 0x49, 0x47, 0x41, 0x4D, 0x45,
        0x2D, 0x53, 0x59, 0x4D, 0x42, 0x4F, 0x4C, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E,
        0x00, 0x00, 0x00, 0x00, 0x53, 0x54, 0x55, 0x52, 0x4D, 0x47, 0x45, 0x57, 0x45, 0x48, 0x52, 0x20,
        0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x00, 0x00, 0x00, 0x00, 0x53, 0x43, 0x48, 0x4E,
        0x45, 0x4C, 0x4C, 0x46, 0x45, 0x55, 0x45, 0x52, 0x2D, 0x55, 0x50, 0x47, 0x52, 0x41, 0x44, 0x45,
        0x20, 0x46, 0x62, 0x52, 0x20, 0x53, 0x54, 0x55, 0x52, 0x4D, 0x47, 0x45, 0x57, 0x45, 0x48, 0x52,
        0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x00, 0x00, 0x00, 0x53, 0x43, 0x48, 0x41,
        0x52, 0x46, 0x53, 0x43, 0x48, 0x62, 0x54, 0x5A, 0x45, 0x4E, 0x56, 0x49, 0x53, 0x49, 0x45, 0x52,
        0x20, 0x46, 0x62, 0x52, 0x20, 0x54, 0x45, 0x4B, 0x2D, 0x41, 0x52, 0x4D, 0x42, 0x52, 0x55, 0x53,
        0x54, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x00, 0x00, 0x47, 0x52, 0x41, 0x4E,
        0x41, 0x54, 0x57, 0x45, 0x52, 0x46, 0x45, 0x52, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45,
        0x4E, 0x00, 0x00, 0x00, 0x47, 0x52, 0x41, 0x4E, 0x41, 0x54, 0x57, 0x45, 0x52, 0x46, 0x45, 0x52,
        0x2D, 0x55, 0x50, 0x47, 0x52, 0x41, 0x44, 0x45, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45,
        0x4E, 0x00, 0x00, 0x00, 0x50, 0x4C, 0x41, 0x53, 0x4D, 0x41, 0x2D, 0x47, 0x45, 0x57, 0x45, 0x48,
        0x52, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x00, 0x00, 0x56, 0x49, 0x53, 0x49,
        0x45, 0x52, 0x20, 0x46, 0x62, 0x52, 0x20, 0x50, 0x4C, 0x41, 0x53, 0x4D, 0x41, 0x2D, 0x47, 0x45,
        0x57, 0x45, 0x48, 0x52, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x00, 0x00, 0x00,
        0x53, 0x65, 0x55, 0x52, 0x45, 0x41, 0x4E, 0x47, 0x52, 0x49, 0x46, 0x46, 0x20, 0x4D, 0x6E, 0x47,
        0x4C, 0x49, 0x43, 0x48, 0x00, 0x00, 0x00, 0x00, 0x53, 0x50, 0x52, 0x55, 0x4E, 0x47, 0x4B, 0x4C,
        0x41, 0x55, 0x45, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x00, 0x00, 0x00, 0x00,
        0x52, 0x41, 0x44, 0x49, 0x4F, 0x41, 0x4B, 0x54, 0x49, 0x56, 0x45, 0x20, 0x46, 0x4C, 0x41, 0x52,
        0x45, 0x2D, 0x47, 0x55, 0x4E, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x00, 0x00,
        0x55, 0x50, 0x47, 0x52, 0x41, 0x44, 0x45, 0x20, 0x46, 0x62, 0x52, 0x20, 0x44, 0x49, 0x45, 0x20,
        0x52, 0x41, 0x44, 0x49, 0x4F, 0x41, 0x4B, 0x54, 0x49, 0x56, 0x45, 0x20, 0x46, 0x4C, 0x41, 0x52,
        0x45, 0x2D, 0x47, 0x55, 0x4E, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x00, 0x00,
        0x53, 0x4B, 0x4F, 0x52, 0x50, 0x49, 0x4F, 0x4E, 0x2D, 0x57, 0x45, 0x52, 0x46, 0x45, 0x52, 0x20,
        0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x00, 0x00, 0x00, 0x00, 0x4D, 0x41, 0x47, 0x4E,
        0x45, 0x54, 0x2D, 0x55, 0x50, 0x47, 0x52, 0x41, 0x44, 0x45, 0x20, 0x46, 0x62, 0x52, 0x20, 0x53,
        0x4B, 0x4F, 0x52, 0x50, 0x49, 0x4F, 0x4E, 0x2D, 0x57, 0x45, 0x52, 0x46, 0x45, 0x52, 0x20, 0x47,
        0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x00, 0x46, 0x52, 0x45, 0x45, 0x5A, 0x45, 0x2D, 0x47,
        0x55, 0x4E, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x00, 0x55, 0x50, 0x47, 0x52,
        0x41, 0x44, 0x45, 0x20, 0x46, 0x62, 0x52, 0x20, 0x46, 0x52, 0x45, 0x45, 0x5A, 0x45, 0x2D, 0x47,
        0x55, 0x4E, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x00, 0x4E, 0x41, 0x50, 0x41,
        0x4C, 0x4D, 0x2D, 0x47, 0x45, 0x4C, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x00,
        0x4C, 0x41, 0x53, 0x45, 0x52, 0x53, 0x49, 0x43, 0x48, 0x54, 0x47, 0x45, 0x52, 0x65, 0x54, 0x20,
        0x46, 0x62, 0x52, 0x20, 0x4D, 0x41, 0x47, 0x20, 0x36, 0x30, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E,
        0x44, 0x45, 0x4E, 0x00, 0x42, 0x52, 0x55, 0x53, 0x54, 0x42, 0x52, 0x45, 0x43, 0x48, 0x45, 0x52,
        0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x00, 0x00, 0x00, 0x49, 0x4E, 0x46, 0x4C,
        0x41, 0x54, 0x4F, 0x52, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x00, 0x00, 0x00,
        0x49, 0x4E, 0x46, 0x4C, 0x41, 0x54, 0x4F, 0x52, 0x2D, 0x55, 0x50, 0x47, 0x52, 0x41, 0x44, 0x45,
        0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x00, 0x00, 0x00, 0x42, 0x55, 0x4D, 0x45,
        0x52, 0x41, 0x4E, 0x47, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x00, 0x00, 0x00,
        0x55, 0x50, 0x47, 0x52, 0x41, 0x44, 0x45, 0x20, 0x46, 0x62, 0x52, 0x20, 0x42, 0x55, 0x4D, 0x45,
        0x52, 0x41, 0x4E, 0x47, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x00, 0x00, 0x00,
        0x4D, 0x49, 0x4E, 0x49, 0x47, 0x55, 0x4E, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E,
        0x00, 0x00, 0x00, 0x00, 0x53, 0x43, 0x48, 0x49, 0x4C, 0x44, 0x2D, 0x55, 0x50, 0x47, 0x52, 0x41,
        0x44, 0x45, 0x20, 0x46, 0x62, 0x52, 0x20, 0x4D, 0x49, 0x4E, 0x49, 0x47, 0x55, 0x4E, 0x20, 0x47,
        0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x00, 0x53, 0x48, 0x4F, 0x54, 0x47, 0x55, 0x4E, 0x2D,
        0x53, 0x54, 0x52, 0x41, 0x53, 0x53, 0x45, 0x4E, 0x46, 0x45, 0x47, 0x45, 0x52, 0x2D, 0x55, 0x50,
        0x47, 0x52, 0x41, 0x44, 0x45, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x20, 0x00,
        0x45, 0x4D, 0x41, 0x43, 0x49, 0x41, 0x54, 0x4F, 0x52, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44,
        0x45, 0x4E, 0x00, 0x00, 0x55, 0x50, 0x47, 0x52, 0x41, 0x44, 0x45, 0x20, 0x46, 0x62, 0x52, 0x20,
        0x45, 0x4D, 0x41, 0x43, 0x49, 0x41, 0x54, 0x4F, 0x52, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44,
        0x45, 0x4E, 0x00, 0x00, 0x57, 0x41, 0x52, 0x48, 0x41, 0x4D, 0x4D, 0x45, 0x52, 0x2D, 0x52, 0x41,
        0x4B, 0x45, 0x54, 0x45, 0x4E, 0x2D, 0x55, 0x50, 0x47, 0x52, 0x41, 0x44, 0x45, 0x20, 0x47, 0x45,
        0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x00, 0x00, 0x44, 0x55, 0x20, 0x48, 0x41, 0x53, 0x54, 0x20,
        0x25, 0x73, 0x20, 0x45, 0x4E, 0x54, 0x52, 0x49, 0x45, 0x47, 0x45, 0x4C, 0x54, 0x00, 0x00, 0x00,
        0x4D, 0x49, 0x53, 0x53, 0x49, 0x4F, 0x4E, 0x20, 0x47, 0x45, 0x53, 0x43, 0x48, 0x45, 0x49, 0x54,
        0x45, 0x52, 0x54, 0x00, 0x47, 0x45, 0x47, 0x45, 0x4E, 0x53, 0x54, 0x41, 0x4E, 0x44, 0x20, 0x42,
        0x45, 0x52, 0x45, 0x49, 0x54, 0x53, 0x20, 0x47, 0x45, 0x46, 0x55, 0x4E, 0x44, 0x45, 0x4E, 0x00,
        0x54, 0x45, 0x41, 0x4D, 0x00, 0x00, 0x00, 0x00, 0x54, 0x52, 0x45, 0x46, 0x46, 0x45, 0x52, 0x25,
        0x00, 0x00, 0x00, 0x00, 0x54, 0x41, 0x47, 0x53, 0x00, 0x00, 0x00, 0x00, 0x46, 0x4C, 0x41, 0x47,
        0x53, 0x00, 0x00, 0x00, 0x47, 0x52, 0x41, 0x54, 0x55, 0x4C, 0x41, 0x54, 0x49, 0x4F, 0x4E, 0x21,
        0x20, 0x46, 0x52, 0x41, 0x47, 0x46, 0x45, 0x53, 0x54, 0x20, 0x62, 0x42, 0x45, 0x52, 0x53, 0x54,
        0x41, 0x4E, 0x44, 0x45, 0x4E, 0x00, 0x00, 0x00, 0x47, 0x52, 0x41, 0x54, 0x55, 0x4C, 0x41, 0x54,
        0x49, 0x4F, 0x4E, 0x21, 0x20, 0x5A, 0x45, 0x49, 0x54, 0x53, 0x50, 0x49, 0x45, 0x4C, 0x20, 0x42,
        0x45, 0x45, 0x4E, 0x44, 0x45, 0x54, 0x00, 0x00, 0x47, 0x45, 0x52, 0x4D, 0x41, 0x4E, 0x00, 0x00,
        0x70, 0x69, 0x73, 0x74, 0x6F, 0x6C, 0x20, 0x63, 0x6C, 0x69, 0x70, 0x20, 0x28, 0x31, 0x30, 0x20,
        0x72, 0x6F, 0x75, 0x6E, 0x64, 0x73, 0x29, 0x00, 0x72, 0x69, 0x66, 0x6C, 0x65, 0x20, 0x63, 0x6C,
        0x69, 0x70, 0x20, 0x28, 0x31, 0x30, 0x20, 0x72, 0x6F, 0x75, 0x6E, 0x64, 0x73, 0x29, 0x00, 0x00,
        0x70, 0x66, 0x65, 0x69, 0x6C, 0x00, 0x00, 0x00, 0x74, 0x65, 0x6B, 0x20, 0x70, 0x66, 0x65, 0x69,
        0x6C, 0x00, 0x00, 0x00, 0x35, 0x20, 0x70, 0x66, 0x65, 0x69, 0x6C, 0x65, 0x00, 0x00, 0x00, 0x00,
        0x6B, 0xF6, 0x63, 0x68, 0x65, 0x72, 0x20, 0x6D, 0x69, 0x74, 0x20, 0x31, 0x30, 0x20, 0x70, 0x66,
        0x65, 0x69, 0x6C, 0x65, 0x6E, 0x00, 0x00, 0x00, 0x33, 0x20, 0x74, 0x65, 0x6B, 0x20, 0x70, 0x66,
        0x65, 0x69, 0x6C, 0x65, 0x00, 0x00, 0x00, 0x00, 0x6B, 0xF6, 0x63, 0x68, 0x65, 0x72, 0x20, 0x6D,
        0x69, 0x74, 0x20, 0x35, 0x20, 0x74, 0x65, 0x6B, 0x20, 0x70, 0x66, 0x65, 0x69, 0x6C, 0x65, 0x6E,
        0x00, 0x00, 0x00, 0x00, 0x31, 0x30, 0x20, 0x70, 0x69, 0x73, 0x74, 0x6F, 0x6C, 0x65, 0x6E, 0x6B,
        0x75, 0x67, 0x65, 0x6C, 0x6E, 0x20, 0x28, 0x6C, 0x61, 0x64, 0x65, 0x73, 0x74, 0x72, 0x65, 0x69,
        0x66, 0x65, 0x6E, 0x29, 0x00, 0x00, 0x00, 0x00, 0x35, 0x20, 0x6D, 0x61, 0x67, 0x6E, 0x75, 0x6D,
        0x2D, 0x6B, 0x75, 0x67, 0x65, 0x6C, 0x6E, 0x20, 0x28, 0x6C, 0x61, 0x64, 0x65, 0x73, 0x74, 0x72,
        0x65, 0x69, 0x66, 0x65, 0x6E, 0x29, 0x00, 0x00, 0x73, 0x63, 0x68, 0x61, 0x63, 0x68, 0x74, 0x65,
        0x6C, 0x20, 0x6D, 0x69, 0x74, 0x20, 0x34, 0x30, 0x20, 0x6B, 0x75, 0x67, 0x65, 0x6C, 0x6E, 0x00,
        0x31, 0x20, 0x62, 0x65, 0x74, 0xE4, 0x75, 0x62, 0x75, 0x6E, 0x67, 0x73, 0x70, 0x66, 0x65, 0x69,
        0x6C, 0x00, 0x00, 0x00, 0x35, 0x20, 0x62, 0x65, 0x74, 0xE4, 0x75, 0x62, 0x75, 0x6E, 0x67, 0x73,
        0x70, 0x66, 0x65, 0x69, 0x6C, 0x65, 0x20, 0x28, 0x70, 0x61, 0x63, 0x6B, 0x29, 0x00, 0x00, 0x00,
        0x35, 0x20, 0x67, 0x65, 0x66, 0x72, 0x69, 0x65, 0x72, 0x70, 0x72, 0x6F, 0x6A, 0x65, 0x6B, 0x74,
        0x69, 0x6C, 0x65, 0x00, 0x32, 0x30, 0x20, 0x67, 0x65, 0x66, 0x72, 0x69, 0x65, 0x72, 0x70, 0x72,
        0x6F, 0x6A, 0x65, 0x6B, 0x74, 0x69, 0x6C, 0x65, 0x20, 0x28, 0x70, 0x61, 0x63, 0x6B, 0x29, 0x00,
        0x33, 0x20, 0x67, 0x65, 0x77, 0x65, 0x68, 0x72, 0x70, 0x61, 0x74, 0x72, 0x6F, 0x6E, 0x65, 0x6E,
        0x00, 0x00, 0x00, 0x00, 0x73, 0x63, 0x68, 0x61, 0x63, 0x68, 0x74, 0x65, 0x6C, 0x20, 0x6D, 0x69,
        0x74, 0x20, 0x31, 0x30, 0x20, 0x67, 0x65, 0x77, 0x65, 0x68, 0x72, 0x70, 0x61, 0x74, 0x72, 0x6F,
        0x6E, 0x65, 0x6E, 0x00, 0x33, 0x20, 0x65, 0x78, 0x70, 0x6C, 0x6F, 0x73, 0x69, 0x76, 0x67, 0x65,
        0x73, 0x63, 0x68, 0x6F, 0x73, 0x73, 0x65, 0x00, 0x33, 0x30, 0x20, 0x70, 0x6C, 0x61, 0x73, 0x6D,
        0x61, 0x67, 0x65, 0x73, 0x63, 0x68, 0x6F, 0x73, 0x73, 0x65, 0x00, 0x00, 0x31, 0x35, 0x30, 0x20,
        0x70, 0x6C, 0x61, 0x73, 0x6D, 0x61, 0x67, 0x65, 0x73, 0x63, 0x68, 0x6F, 0x73, 0x73, 0x65, 0x28,
        0x70, 0x61, 0x63, 0x6B, 0x29, 0x00, 0x00, 0x00, 0x33, 0x20, 0x73, 0x6F, 0x6E, 0x6E, 0x65, 0x6E,
        0x66, 0x65, 0x75, 0x65, 0x72, 0x2D, 0x6B, 0x75, 0x67, 0x65, 0x6C, 0x6E, 0x00, 0x00, 0x00, 0x00,
        0x32, 0x20, 0x7A, 0x69, 0x65, 0x6C, 0x73, 0x75, 0x63, 0x68, 0x70, 0x72, 0x6F, 0x6A, 0x65, 0x6B,
        0x74, 0x69, 0x6C, 0x65, 0x00, 0x00, 0x00, 0x00, 0x31, 0x20, 0x75, 0x2E, 0x66, 0x2E, 0x6D, 0x2E,
        0x00, 0x00, 0x00, 0x00, 0x31, 0x20, 0x67, 0x72, 0x61, 0x6E, 0x61, 0x74, 0x65, 0x00, 0x00, 0x00,
        0x35, 0x20, 0x67, 0x72, 0x61, 0x6E, 0x61, 0x74, 0x65, 0x6E, 0x20, 0x28, 0x73, 0x63, 0x68, 0x61,
        0x63, 0x68, 0x74, 0x65, 0x6C, 0x29, 0x00, 0x00, 0x34, 0x20, 0x73, 0x6B, 0x6F, 0x72, 0x70, 0x69,
        0x6F, 0x6E, 0x2D, 0x72, 0x61, 0x6B, 0x65, 0x74, 0x65, 0x6E, 0x00, 0x00, 0x31, 0x20, 0x73, 0x70,
        0x65, 0x65, 0x72, 0x00, 0x33, 0x20, 0x73, 0x70, 0x65, 0x65, 0x72, 0x65, 0x00, 0x00, 0x00, 0x00,
        0x31, 0x20, 0x74, 0x6F, 0x72, 0x70, 0x65, 0x64, 0x6F, 0x00, 0x00, 0x00, 0x32, 0x30, 0x20, 0x30,
        0x2E, 0x32, 0x30, 0x6D, 0x6D, 0x20, 0x6B, 0x75, 0x67, 0x65, 0x6C, 0x6E, 0x00, 0x00, 0x00, 0x00,
        0x33, 0x20, 0x65, 0x78, 0x70, 0x6C, 0x6F, 0x73, 0x69, 0x76, 0x70, 0x61, 0x74, 0x72, 0x6F, 0x6E,
        0x65, 0x6E, 0x00, 0x00, 0x33, 0x20, 0x73, 0x70, 0x6C, 0x69, 0x74, 0x74, 0x65, 0x72, 0x67, 0x65,
        0x73, 0x63, 0x68, 0x6F, 0x73, 0x73, 0x65, 0x00, 0x32, 0x20, 0x66, 0x6C, 0x61, 0x6D, 0x6D, 0x65,
        0x6E, 0x77, 0x65, 0x72, 0x66, 0x65, 0x72, 0x74, 0x61, 0x6E, 0x6B, 0x00, 0x32, 0x20, 0x70, 0x61,
        0x72, 0x74, 0x69, 0x6B, 0x65, 0x6C, 0x62, 0x65, 0x73, 0x63, 0x68, 0x6C, 0x65, 0x75, 0x6E, 0x69,
        0x67, 0x65, 0x72, 0x2D, 0x6C, 0x61, 0x64, 0x75, 0x6E, 0x67, 0x65, 0x6E, 0x00, 0x00, 0x00, 0x00,
        0x67, 0x65, 0x66, 0x72, 0x69, 0x65, 0x72, 0x70, 0x72, 0x6F, 0x6A, 0x65, 0x6B, 0x74, 0x69, 0x6C,
        0x65, 0x00, 0x00, 0x00, 0x73, 0x63, 0x68, 0x72, 0x65, 0x64, 0x64, 0x65, 0x72, 0x67, 0x65, 0x73,
        0x63, 0x68, 0x6F, 0x73, 0x73, 0x65, 0x00, 0x00, 0x70, 0x6C, 0x61, 0x73, 0x6D, 0x61, 0x7A, 0x65,
        0x6C, 0x6C, 0x65, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x7A, 0x69, 0x65, 0x6C, 0x73, 0x75, 0x63, 0x68,
        0x70, 0x72, 0x6F, 0x6A, 0x65, 0x6B, 0x74, 0x69, 0x6C, 0x65, 0x00, 0x00, 0x67, 0x72, 0x61, 0x6E,
        0x61, 0x74, 0x65, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x72, 0x61, 0x6B, 0x65, 0x74, 0x65, 0x6E, 0x00,
        0x73, 0x70, 0x65, 0x65, 0x72, 0x65, 0x00, 0x00, 0x74, 0x6F, 0x72, 0x70, 0x65, 0x64, 0x6F, 0x00,
        0x73, 0x63, 0x68, 0x77, 0x69, 0x65, 0x72, 0x69, 0x67, 0x6B, 0x65, 0x69, 0x74, 0x20, 0x20, 0x20,
        0x3A, 0x20, 0x65, 0x69, 0x6E, 0x66, 0x61, 0x63, 0x68, 0x00, 0x00, 0x00, 0x73, 0x63, 0x68, 0x77,
        0x69, 0x65, 0x72, 0x69, 0x67, 0x6B, 0x65, 0x69, 0x74, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x20, 0x6D,
        0x69, 0x74, 0x74, 0x65, 0x6C, 0x00, 0x00, 0x00, 0x73, 0x63, 0x68, 0x77, 0x69, 0x65, 0x72, 0x69,
        0x67, 0x6B, 0x65, 0x69, 0x74, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x20, 0x73, 0x63, 0x68, 0x77, 0x65,
        0x72, 0x00, 0x00, 0x00, 0x73, 0x74, 0x65, 0x75, 0x65, 0x72, 0x6D, 0x6F, 0x64, 0x75, 0x73, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x65, 0x78, 0x70, 0x65, 0x72, 0x74, 0x65, 0x00, 0x00, 0x00,
        0x73, 0x74, 0x65, 0x75, 0x65, 0x72, 0x6D, 0x6F, 0x64, 0x75, 0x73, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x3A, 0x20, 0x20, 0x61, 0x72, 0x63, 0x61, 0x64, 0x65, 0x00, 0x00, 0x00, 0x73, 0x74, 0x65, 0x75,
        0x65, 0x72, 0x6D, 0x6F, 0x64, 0x75, 0x73, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x20, 0x3F,
        0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x73, 0x74, 0x65, 0x75, 0x65, 0x72, 0x73, 0x65,
        0x69, 0x74, 0x65, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x6C, 0x69, 0x6E, 0x6B,
        0x73, 0x00, 0x00, 0x00, 0x73, 0x74, 0x65, 0x75, 0x65, 0x72, 0x73, 0x65, 0x69, 0x74, 0x65, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x20, 0x72, 0x65, 0x63, 0x68, 0x74, 0x73, 0x00, 0x00, 0x00,
        0x51, 0x75, 0x65, 0x6C, 0x6C, 0x62, 0x6C, 0x69, 0x63, 0x6B, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x65, 0x69, 0x6E, 0x00, 0x00, 0x00, 0x51, 0x75, 0x65, 0x6C,
        0x6C, 0x62, 0x6C, 0x69, 0x63, 0x6B, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x61, 0x75, 0x73, 0x00, 0x00, 0x00, 0x61, 0x75, 0x74, 0x6F, 0x6D, 0x2E, 0x7A, 0x69,
        0x65, 0x6C, 0x65, 0x6E, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x65, 0x69,
        0x6E, 0x00, 0x00, 0x00, 0x61, 0x75, 0x74, 0x6F, 0x6D, 0x2E, 0x20, 0x7A, 0x69, 0x65, 0x6C, 0x65,
        0x6E, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x61, 0x75, 0x73, 0x00, 0x00, 0x00,
        0x66, 0x61, 0x72, 0x62, 0x65, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x61, 0x75, 0x73, 0x00, 0x00, 0x00, 0x66, 0x61, 0x72, 0x62,
        0x65, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x72, 0x6F, 0x74, 0x00, 0x00, 0x00, 0x66, 0x61, 0x72, 0x62, 0x65, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x67, 0x72, 0xFC,
        0x6E, 0x00, 0x00, 0x00, 0x32, 0x20, 0x73, 0x70, 0x2E, 0x20, 0x6C, 0x61, 0x79, 0x6F, 0x75, 0x74,
        0x20, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x68, 0x6F, 0x72, 0x7A, 0x00, 0x00, 0x00,
        0x32, 0x20, 0x73, 0x70, 0x2E, 0x20, 0x6C, 0x61, 0x79, 0x6F, 0x75, 0x74, 0x20, 0x20, 0x20, 0x20,
        0x3A, 0x20, 0x20, 0x20, 0x20, 0x76, 0x65, 0x72, 0x74, 0x00, 0x00, 0x00, 0x6F, 0x62, 0x65, 0x72,
        0x66, 0x6C, 0xE4, 0x63, 0x68, 0x65, 0x3A, 0x20, 0x20, 0x64, 0x75, 0x72, 0x63, 0x68, 0x73, 0x69,
        0x63, 0x68, 0x74, 0x69, 0x67, 0x00, 0x00, 0x00, 0x6F, 0x62, 0x65, 0x72, 0x66, 0x6C, 0xE4, 0x63,
        0x68, 0x65, 0x3A, 0x75, 0x6E, 0x64, 0x75, 0x72, 0x63, 0x68, 0x73, 0x69, 0x63, 0x68, 0x74, 0x69,
        0x67, 0x00, 0x00, 0x00, 0x6F, 0x62, 0x65, 0x72, 0x66, 0x6C, 0xE4, 0x63, 0x68, 0x65, 0x3A, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00,
        0x63, 0x6F, 0x6E, 0x74, 0x72, 0x6F, 0x6C, 0x20, 0x73, 0x74, 0x69, 0x63, 0x6B, 0x20, 0x68, 0x6F,
        0x72, 0x7A, 0x20, 0x3A, 0x20, 0x6E, 0x6F, 0x72, 0x6D, 0x00, 0x00, 0x00, 0x63, 0x6F, 0x6E, 0x74,
        0x72, 0x6F, 0x6C, 0x20, 0x73, 0x74, 0x69, 0x63, 0x6B, 0x20, 0x68, 0x6F, 0x72, 0x7A, 0x20, 0x3A,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x63, 0x6F, 0x6E, 0x74, 0x72, 0x6F, 0x6C, 0x20,
        0x73, 0x74, 0x69, 0x63, 0x6B, 0x20, 0x76, 0x65, 0x72, 0x74, 0x20, 0x3A, 0x20, 0x6E, 0x6F, 0x72,
        0x6D, 0x00, 0x00, 0x00, 0x63, 0x6F, 0x6E, 0x74, 0x72, 0x6F, 0x6C, 0x20, 0x73, 0x74, 0x69, 0x63,
        0x6B, 0x20, 0x76, 0x65, 0x72, 0x74, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00,
        0x77, 0x61, 0x66, 0x66, 0x65, 0x6E, 0x77, 0x61, 0x68, 0x6C, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x3A, 0x20, 0x73, 0x63, 0x68, 0x6E, 0x65, 0x6C, 0x6C, 0x00, 0x00, 0x00, 0x77, 0x61, 0x66, 0x66,
        0x65, 0x6E, 0x77, 0x61, 0x68, 0x6C, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x20, 0x20,
        0x20, 0x6E, 0x6F, 0x72, 0x6D, 0x00, 0x00, 0x00, 0x61, 0x75, 0x66, 0x6C, 0xF6, 0x73, 0x75, 0x6E,
        0x67, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x6E, 0x69, 0x65, 0x64, 0x72, 0x69,
        0x67, 0x00, 0x00, 0x00, 0x61, 0x75, 0x66, 0x6C, 0xF6, 0x73, 0x75, 0x6E, 0x67, 0x20, 0x3A, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x68, 0x6F, 0x63, 0x68, 0x00, 0x00, 0x00,
        0x61, 0x75, 0x66, 0x6C, 0xF6, 0x73, 0x75, 0x6E, 0x67, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x68, 0x6F,
        0x63, 0x68, 0x20, 0x28, 0x66, 0x69, 0x6C, 0x6D, 0x29, 0x00, 0x00, 0x00, 0x61, 0x75, 0x66, 0x6C,
        0xF6, 0x73, 0x75, 0x6E, 0x67, 0x20, 0x3A, 0x20, 0x20, 0x73, 0x75, 0x70, 0x65, 0x72, 0x6E, 0x69,
        0x65, 0x64, 0x72, 0x69, 0x67, 0x00, 0x00, 0x00, 0x61, 0x75, 0x66, 0x6C, 0xF6, 0x73, 0x75, 0x6E,
        0x67, 0x20, 0x3A, 0x20, 0x6E, 0x69, 0x65, 0x64, 0x72, 0x69, 0x67, 0x28, 0x66, 0x69, 0x6C, 0x6D,
        0x29, 0x00, 0x00, 0x00, 0x48, 0x65, 0x6C, 0x6C, 0x69, 0x67, 0x6B, 0x65, 0x69, 0x74, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x6E, 0x6F, 0x72, 0x6D, 0x00, 0x00, 0x00,
        0x48, 0x65, 0x6C, 0x6C, 0x69, 0x67, 0x6B, 0x65, 0x69, 0x74, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x6C, 0x61, 0x6E, 0x67,
        0x75, 0x61, 0x67, 0x65, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x20, 0x67,
        0x65, 0x72, 0x6D, 0x61, 0x6E, 0x00, 0x00, 0x00, 0x7A, 0x75, 0x72, 0xFC, 0x63, 0x6B, 0x00, 0x00,
        0x6B, 0x65, 0x69, 0x6E, 0x73, 0x00, 0x00, 0x00, 0x6C, 0x61, 0x64, 0x65, 0x6E, 0x00, 0x00, 0x00,
        0x6E, 0x61, 0x6D, 0x65, 0x6E, 0x20, 0xE4, 0x6E, 0x64, 0x65, 0x72, 0x6E, 0x00, 0x00, 0x00, 0x00,
        0x62, 0x6C, 0x61, 0x68, 0x62, 0x6C, 0x61, 0x68, 0x00, 0x00, 0x00, 0x00, 0x68, 0x61, 0x6E, 0x64,
        0x69, 0x63, 0x61, 0x70, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00,
        0x68, 0x61, 0x6E, 0x64, 0x69, 0x63, 0x61, 0x70, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x00, 0x00, 0x00, 0x68, 0x61, 0x6E, 0x64, 0x69, 0x63, 0x61, 0x70, 0x20, 0x3A, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x68, 0x61, 0x6E, 0x64, 0x69, 0x63, 0x61, 0x70,
        0x20, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x68, 0x61, 0x6E, 0x64,
        0x69, 0x63, 0x61, 0x70, 0x20, 0x3A, 0x20, 0x20, 0x6B, 0x65, 0x69, 0x6E, 0x73, 0x00, 0x00, 0x00,
        0x68, 0x61, 0x6E, 0x64, 0x69, 0x63, 0x61, 0x70, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x6D, 0x61,
        0x78, 0x00, 0x00, 0x00, 0x73, 0x74, 0x65, 0x75, 0x65, 0x72, 0x75, 0x6E, 0x67, 0x3A, 0x65, 0x78,
        0x70, 0x65, 0x72, 0x74, 0x65, 0x00, 0x00, 0x00, 0x73, 0x74, 0x65, 0x75, 0x65, 0x72, 0x75, 0x6E,
        0x67, 0x3A, 0x20, 0x61, 0x72, 0x63, 0x61, 0x64, 0x65, 0x00, 0x00, 0x00, 0x73, 0x74, 0x65, 0x75,
        0x65, 0x72, 0x75, 0x6E, 0x67, 0x3A, 0x20, 0x20, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x00, 0x00, 0x00,
        0x73, 0x70, 0x69, 0x65, 0x6C, 0x65, 0x6E, 0x00, 0x64, 0x69, 0x65, 0x73, 0x65, 0x73, 0x20, 0x73,
        0x70, 0x69, 0x65, 0x6C, 0x20, 0x69, 0x73, 0x74, 0x00, 0x00, 0x00, 0x00, 0x6D, 0x69, 0x74, 0x20,
        0x64, 0x65, 0x6D, 0x20, 0x72, 0x75, 0x6D, 0x62, 0x6C, 0x65, 0x00, 0x00, 0x70, 0x61, 0x6B, 0x20,
        0x6B, 0x6F, 0x6D, 0x70, 0x61, 0x74, 0x69, 0x62, 0x65, 0x6C, 0x2E, 0x00, 0x62, 0x69, 0x74, 0x74,
        0x65, 0x20, 0x73, 0x65, 0x74, 0x7A, 0x65, 0x20, 0x64, 0x61, 0x73, 0x00, 0x72, 0x75, 0x6D, 0x62,
        0x6C, 0x65, 0x20, 0x70, 0x61, 0x6B, 0x00, 0x00, 0x6A, 0x65, 0x74, 0x7A, 0x74, 0x20, 0x65, 0x69,
        0x6E, 0x2C, 0x20, 0x75, 0x6D, 0x20, 0x65, 0x73, 0x00, 0x00, 0x00, 0x00, 0x66, 0xFC, 0x72, 0x20,
        0x64, 0x69, 0x65, 0x73, 0x65, 0x73, 0x20, 0x73, 0x70, 0x69, 0x65, 0x6C, 0x00, 0x00, 0x00, 0x00,
        0x7A, 0x75, 0x20, 0x76, 0x65, 0x72, 0x77, 0x65, 0x6E, 0x64, 0x65, 0x6E, 0x2E, 0x00, 0x00, 0x00,
        0x77, 0xE4, 0x68, 0x6C, 0x65, 0x6E, 0x00, 0x00, 0x62, 0x6C, 0x61, 0x75, 0x00, 0x00, 0x00, 0x00,
        0x72, 0x6F, 0x74, 0x20, 0x00, 0x00, 0x00, 0x00, 0x65, 0x6E, 0x64, 0x65, 0x72, 0x67, 0x65, 0x62,
        0x6E, 0x69, 0x73, 0x00, 0x65, 0x72, 0x67, 0x65, 0x62, 0x6E, 0x69, 0x73, 0x20, 0x62, 0x6C, 0x61,
        0x75, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x20, 0x65, 0x72, 0x67,
        0x65, 0x62, 0x6E, 0x69, 0x73, 0x20, 0x72, 0x6F, 0x74, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x20,
        0x20, 0x20, 0x00, 0x00, 0x62, 0x69, 0x74, 0x74, 0x65, 0x20, 0x77, 0x61, 0x72, 0x74, 0x65, 0x6E,
        0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x00, 0x00, 0x00, 0x70, 0x61, 0x75, 0x73, 0x65, 0x00, 0x00, 0x00,
        0x73, 0x70, 0x69, 0x65, 0x6C, 0x20, 0x77, 0x69, 0x65, 0x64, 0x65, 0x72, 0x20, 0x61, 0x75, 0x66,
        0x6E, 0x65, 0x68, 0x6D, 0x65, 0x6E, 0x00, 0x00, 0x6D, 0x69, 0x73, 0x73, 0x69, 0x6F, 0x6E, 0x73,
        0x73, 0x74, 0x61, 0x74, 0x75, 0x73, 0x00, 0x00, 0x6D, 0x69, 0x73, 0x73, 0x69, 0x6F, 0x6E, 0x00,
        0x69, 0x6E, 0x76, 0x65, 0x6E, 0x74, 0x61, 0x72, 0x00, 0x00, 0x00, 0x00, 0x6C, 0x61, 0x64, 0x65,
        0x6E, 0x00, 0x00, 0x00, 0x6F, 0x70, 0x74, 0x69, 0x6F, 0x6E, 0x65, 0x6E, 0x00, 0x00, 0x00, 0x00,
        0x63, 0x68, 0x65, 0x61, 0x74, 0x73, 0x00, 0x00, 0x61, 0x62, 0x62, 0x72, 0x65, 0x63, 0x68, 0x65,
        0x6E, 0x00, 0x00, 0x00, 0x6D, 0x69, 0x73, 0x73, 0x69, 0x6F, 0x6E, 0x73, 0x73, 0x74, 0x61, 0x74,
        0x75, 0x73, 0x00, 0x00, 0x6D, 0x69, 0x73, 0x73, 0x69, 0x6F, 0x6E, 0x20, 0x67, 0x65, 0x73, 0x63,
        0x68, 0x65, 0x69, 0x74, 0x65, 0x72, 0x74, 0x00, 0x6E, 0x69, 0x63, 0x68, 0x74, 0x20, 0x76, 0x65,
        0x72, 0x66, 0xFC, 0x67, 0x62, 0x61, 0x72, 0x00, 0x68, 0x61, 0x66, 0x65, 0x6E, 0x20, 0x76, 0x6F,
        0x6E, 0x20, 0x61, 0x64, 0x69, 0x61, 0x00, 0x00, 0x61, 0x6B, 0x74, 0x69, 0x76, 0x69, 0x65, 0x72,
        0x74, 0x20, 0x78, 0x20, 0x76, 0x6F, 0x6E, 0x20, 0x33, 0x00, 0x00, 0x00, 0x77, 0x61, 0x72, 0x6E,
        0x2D, 0x6C, 0x65, 0x75, 0x63, 0x68, 0x74, 0x74, 0xFC, 0x72, 0x6D, 0x65, 0x6E, 0x00, 0x00, 0x00,
        0x67, 0x65, 0x72, 0x65, 0x74, 0x74, 0x65, 0x74, 0x20, 0x78, 0x20, 0x76, 0x6F, 0x6E, 0x20, 0x34,
        0x00, 0x00, 0x00, 0x00, 0x6B, 0x69, 0x6E, 0x64, 0x65, 0x72, 0x6E, 0x00, 0x66, 0x6C, 0x75, 0x73,
        0x73, 0x20, 0x64, 0x65, 0x72, 0x20, 0x73, 0x65, 0x65, 0x6C, 0x65, 0x6E, 0x00, 0x00, 0x00, 0x00,
        0x7A, 0x65, 0x72, 0x73, 0x74, 0xF6, 0x72, 0x74, 0x20, 0x78, 0x20, 0x76, 0x6F, 0x6E, 0x20, 0x32,
        0x00, 0x00, 0x00, 0x00, 0x73, 0x65, 0x65, 0x6C, 0x65, 0x6E, 0x74, 0x6F, 0x72, 0x65, 0x6E, 0x00,
        0x76, 0x65, 0x72, 0x6E, 0x69, 0x63, 0x68, 0x74, 0x65, 0x74, 0x20, 0x78, 0x20, 0x76, 0x6F, 0x6E,
        0x20, 0x33, 0x00, 0x00, 0x73, 0x63, 0x68, 0x77, 0x65, 0x73, 0x74, 0x65, 0x72, 0x6E, 0x20, 0x64,
        0x65, 0x72, 0x20, 0x76, 0x65, 0x72, 0x7A, 0x77, 0x65, 0x69, 0x66, 0x6C, 0x75, 0x6E, 0x67, 0x00,
        0x73, 0xFC, 0x6D, 0x70, 0x66, 0x65, 0x20, 0x64, 0x65, 0x73, 0x20, 0x74, 0x6F, 0x64, 0x65, 0x73,
        0x00, 0x00, 0x00, 0x00, 0x67, 0x65, 0x72, 0x65, 0x74, 0x74, 0x65, 0x74, 0x20, 0x78, 0x20, 0x76,
        0x6F, 0x6E, 0x20, 0x35, 0x00, 0x00, 0x00, 0x00, 0x67, 0x65, 0x66, 0x61, 0x6E, 0x67, 0x65, 0x6E,
        0x65, 0x6E, 0x00, 0x00, 0x7A, 0x65, 0x72, 0x73, 0x74, 0xF6, 0x72, 0x74, 0x20, 0x78, 0x20, 0x76,
        0x6F, 0x6E, 0x20, 0x33, 0x00, 0x00, 0x00, 0x00, 0x6D, 0x75, 0x6E, 0x69, 0x74, 0x69, 0x6F, 0x6E,
        0x73, 0x6C, 0x61, 0x67, 0x65, 0x72, 0x6E, 0x00, 0x68, 0xF6, 0x68, 0x6C, 0x65, 0x20, 0x64, 0x65,
        0x72, 0x20, 0x62, 0x6C, 0x69, 0x6E, 0x64, 0x65, 0x6E, 0x20, 0x6A, 0xE4, 0x67, 0x65, 0x72, 0x00,
        0x76, 0x65, 0x72, 0x73, 0x69, 0x65, 0x67, 0x65, 0x6C, 0x74, 0x20, 0x78, 0x20, 0x76, 0x6F, 0x6E,
        0x20, 0x33, 0x00, 0x00, 0x74, 0x68, 0x65, 0x72, 0x6D, 0x61, 0x6C, 0x73, 0x63, 0x68, 0xE4, 0x63,
        0x68, 0x74, 0x65, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x6B, 0x6F, 0x6C, 0x6F, 0x6E, 0x69, 0x65, 0x20,
        0x64, 0x65, 0x72, 0x20, 0x6D, 0x61, 0x6E, 0x74, 0x69, 0x64, 0x73, 0x00, 0x76, 0x65, 0x72, 0x6E,
        0x69, 0x63, 0x68, 0x74, 0x65, 0x74, 0x20, 0x78, 0x20, 0x76, 0x6F, 0x6E, 0x20, 0x33, 0x00, 0x00,
        0x65, 0x6D, 0x62, 0x72, 0x79, 0x6F, 0x2D, 0x6B, 0xF6, 0x6E, 0x69, 0x67, 0x69, 0x6E, 0x6E, 0x65,
        0x6E, 0x00, 0x00, 0x00, 0x7A, 0x65, 0x72, 0x73, 0x74, 0xF6, 0x72, 0x74, 0x20, 0x78, 0x20, 0x76,
        0x6F, 0x6E, 0x20, 0x31, 0x00, 0x00, 0x00, 0x00, 0x68, 0x61, 0x75, 0x70, 0x74, 0x63, 0x6F, 0x6D,
        0x70, 0x75, 0x74, 0x65, 0x72, 0x6E, 0x00, 0x00, 0x72, 0x61, 0x75, 0x6D, 0x73, 0x63, 0x68, 0x69,
        0x66, 0x66, 0x20, 0x64, 0x65, 0x73, 0x20, 0x70, 0x72, 0x69, 0x6D, 0x61, 0x67, 0x65, 0x6E, 0x00,
        0x72, 0x65, 0x6B, 0x61, 0x6C, 0x69, 0x62, 0x72, 0x69, 0x65, 0x72, 0x74, 0x20, 0x78, 0x20, 0x76,
        0x6F, 0x6E, 0x20, 0x34, 0x00, 0x00, 0x00, 0x00, 0x73, 0x74, 0x72, 0x6F, 0x6D, 0x67, 0x65, 0x6E,
        0x65, 0x72, 0x61, 0x74, 0x6F, 0x72, 0x65, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x7A, 0x65, 0x72, 0x73,
        0x74, 0xF6, 0x72, 0x74, 0x20, 0x78, 0x20, 0x76, 0x6F, 0x6E, 0x20, 0x33, 0x00, 0x00, 0x00, 0x00,
        0x7A, 0x65, 0x72, 0x73, 0x74, 0xF6, 0x72, 0x74, 0x20, 0x78, 0x20, 0x76, 0x6F, 0x6E, 0x20, 0x3F,
        0x00, 0x00, 0x00, 0x00, 0x72, 0x6F, 0x62, 0x6F, 0x2D, 0x66, 0x61, 0x62, 0x72, 0x69, 0x6B, 0x65,
        0x6E, 0x00, 0x00, 0x00, 0x6F, 0x6B, 0x00, 0x00, 0x6D, 0x69, 0x73, 0x73, 0x69, 0x6F, 0x6E, 0x20,
        0x6F, 0x62, 0x6A, 0x65, 0x63, 0x74, 0x69, 0x76, 0x65, 0x73, 0x00, 0x00, 0x70, 0x6F, 0x72, 0x74,
        0x20, 0x6F, 0x66, 0x20, 0x61, 0x64, 0x69, 0x61, 0x00, 0x00, 0x00, 0x00, 0x61, 0x63, 0x74, 0x69,
        0x76, 0x61, 0x74, 0x65, 0x20, 0x33, 0x00, 0x00, 0x64, 0x69, 0x73, 0x74, 0x72, 0x65, 0x73, 0x73,
        0x20, 0x62, 0x65, 0x61, 0x63, 0x6F, 0x6E, 0x73, 0x00, 0x00, 0x00, 0x00, 0x72, 0x65, 0x73, 0x63,
        0x75, 0x65, 0x20, 0x34, 0x20, 0x63, 0x68, 0x69, 0x6C, 0x64, 0x72, 0x65, 0x6E, 0x00, 0x00, 0x00,
        0x61, 0x63, 0x74, 0x69, 0x76, 0x61, 0x74, 0x65, 0x20, 0x74, 0x68, 0x65, 0x20, 0x77, 0x61, 0x72,
        0x70, 0x20, 0x70, 0x6F, 0x72, 0x74, 0x61, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x64, 0x65, 0x66, 0x65,
        0x6E, 0x64, 0x20, 0x74, 0x68, 0x65, 0x20, 0x65, 0x6E, 0x65, 0x72, 0x67, 0x79, 0x20, 0x74, 0x6F,
        0x74, 0x65, 0x6D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x72, 0x69, 0x76, 0x65, 0x72, 0x20, 0x6F, 0x66,
        0x20, 0x73, 0x6F, 0x75, 0x6C, 0x73, 0x00, 0x00, 0x64, 0x65, 0x73, 0x74, 0x72, 0x6F, 0x79, 0x20,
        0x32, 0x20, 0x73, 0x6F, 0x75, 0x6C, 0x67, 0x61, 0x74, 0x65, 0x73, 0x00, 0x64, 0x65, 0x73, 0x74,
        0x72, 0x6F, 0x79, 0x20, 0x74, 0x68, 0x65, 0x20, 0x20, 0x33, 0x00, 0x00, 0x73, 0x69, 0x73, 0x74,
        0x65, 0x72, 0x73, 0x20, 0x6F, 0x66, 0x20, 0x64, 0x65, 0x73, 0x70, 0x61, 0x69, 0x72, 0x00, 0x00,
        0x61, 0x63, 0x74, 0x69, 0x76, 0x61, 0x74, 0x65, 0x20, 0x74, 0x68, 0x65, 0x20, 0x77, 0x61, 0x72,
        0x70, 0x20, 0x70, 0x6F, 0x72, 0x74, 0x61, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x64, 0x65, 0x66, 0x65,
        0x6E, 0x64, 0x20, 0x74, 0x68, 0x65, 0x20, 0x65, 0x6E, 0x65, 0x72, 0x67, 0x79, 0x20, 0x74, 0x6F,
        0x74, 0x65, 0x6D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x65, 0x61, 0x74, 0x68, 0x20, 0x6D, 0x61,
        0x72, 0x73, 0x68, 0x65, 0x73, 0x00, 0x00, 0x00, 0x72, 0x65, 0x73, 0x63, 0x75, 0x65, 0x20, 0x35,
        0x20, 0x70, 0x72, 0x69, 0x73, 0x6F, 0x6E, 0x65, 0x72, 0x73, 0x00, 0x00, 0x64, 0x65, 0x73, 0x74,
        0x72, 0x6F, 0x79, 0x20, 0x33, 0x20, 0x61, 0x6D, 0x6D, 0x75, 0x6E, 0x69, 0x74, 0x69, 0x6F, 0x6E,
        0x00, 0x00, 0x00, 0x00, 0x73, 0x74, 0x6F, 0x72, 0x61, 0x67, 0x65, 0x20, 0x66, 0x61, 0x63, 0x69,
        0x6C, 0x69, 0x74, 0x69, 0x65, 0x73, 0x00, 0x00, 0x61, 0x63, 0x74, 0x69, 0x76, 0x61, 0x74, 0x65,
        0x20, 0x74, 0x68, 0x65, 0x20, 0x77, 0x61, 0x72, 0x70, 0x20, 0x70, 0x6F, 0x72, 0x74, 0x61, 0x6C,
        0x00, 0x00, 0x00, 0x00, 0x64, 0x65, 0x66, 0x65, 0x6E, 0x64, 0x20, 0x74, 0x68, 0x65, 0x20, 0x65,
        0x6E, 0x65, 0x72, 0x67, 0x79, 0x20, 0x74, 0x6F, 0x74, 0x65, 0x6D, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x6C, 0x61, 0x69, 0x72, 0x20, 0x6F, 0x66, 0x20, 0x74, 0x68, 0x65, 0x20, 0x62, 0x6C, 0x69, 0x6E,
        0x64, 0x20, 0x6F, 0x6E, 0x65, 0x73, 0x00, 0x00, 0x73, 0x65, 0x61, 0x6C, 0x20, 0x33, 0x20, 0x74,
        0x68, 0x65, 0x72, 0x6D, 0x61, 0x6C, 0x20, 0x76, 0x65, 0x6E, 0x74, 0x73, 0x00, 0x00, 0x00, 0x00,
        0x61, 0x63, 0x74, 0x69, 0x76, 0x61, 0x74, 0x65, 0x20, 0x74, 0x68, 0x65, 0x20, 0x77, 0x61, 0x72,
        0x70, 0x20, 0x70, 0x6F, 0x72, 0x74, 0x61, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x64, 0x65, 0x66, 0x65,
        0x6E, 0x64, 0x20, 0x74, 0x68, 0x65, 0x20, 0x65, 0x6E, 0x65, 0x72, 0x67, 0x79, 0x20, 0x74, 0x6F,
        0x74, 0x65, 0x6D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x68, 0x69, 0x76, 0x65, 0x20, 0x6F, 0x66, 0x20, 0x74, 0x68, 0x65, 0x20, 0x6D, 0x61, 0x6E, 0x74,
        0x69, 0x64, 0x73, 0x00, 0x64, 0x65, 0x73, 0x74, 0x72, 0x6F, 0x79, 0x20, 0x33, 0x00, 0x00, 0x00,
        0x71, 0x75, 0x65, 0x65, 0x6E, 0x20, 0x65, 0x6D, 0x62, 0x72, 0x79, 0x6F, 0x73, 0x00, 0x00, 0x00,
        0x64, 0x65, 0x73, 0x74, 0x72, 0x6F, 0x79, 0x20, 0x74, 0x68, 0x65, 0x20, 0x6D, 0x61, 0x73, 0x74,
        0x65, 0x72, 0x20, 0x63, 0x6F, 0x6D, 0x70, 0x75, 0x74, 0x65, 0x72, 0x00, 0x61, 0x63, 0x74, 0x69,
        0x76, 0x61, 0x74, 0x65, 0x20, 0x74, 0x68, 0x65, 0x20, 0x77, 0x61, 0x72, 0x70, 0x20, 0x70, 0x6F,
        0x72, 0x74, 0x61, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x64, 0x65, 0x66, 0x65, 0x6E, 0x64, 0x20, 0x74,
        0x68, 0x65, 0x20, 0x65, 0x6E, 0x65, 0x72, 0x67, 0x79, 0x20, 0x74, 0x6F, 0x74, 0x65, 0x6D, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x70, 0x72, 0x69, 0x6D, 0x61, 0x67, 0x65, 0x6E, 0x73, 0x20, 0x6C, 0x69,
        0x67, 0x68, 0x74, 0x73, 0x68, 0x69, 0x70, 0x00, 0x72, 0x65, 0x63, 0x61, 0x6C, 0x69, 0x62, 0x72,
        0x61, 0x74, 0x65, 0x20, 0x34, 0x00, 0x00, 0x00, 0x70, 0x6F, 0x77, 0x65, 0x72, 0x20, 0x67, 0x65,
        0x6E, 0x65, 0x72, 0x61, 0x74, 0x6F, 0x72, 0x73, 0x00, 0x00, 0x00, 0x00, 0x64, 0x65, 0x73, 0x74,
        0x72, 0x6F, 0x79, 0x20, 0x33, 0x00, 0x00, 0x00, 0x61, 0x73, 0x73, 0x65, 0x6D, 0x62, 0x6C, 0x79,
        0x20, 0x70, 0x6C, 0x61, 0x6E, 0x74, 0x73, 0x00, 0x61, 0x63, 0x74, 0x69, 0x76, 0x61, 0x74, 0x65,
        0x20, 0x74, 0x68, 0x65, 0x20, 0x77, 0x61, 0x72, 0x70, 0x20, 0x70, 0x6F, 0x72, 0x74, 0x61, 0x6C,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x69, 0x6E, 0x76, 0x65, 0x6E, 0x74, 0x61, 0x72,
        0x00, 0x00, 0x00, 0x00, 0x6F, 0x6B, 0x00, 0x00, 0x52, 0x41, 0x47, 0x45, 0x20, 0x57, 0x41, 0x52,
        0x53, 0x00, 0x00, 0x00, 0x54, 0x55, 0x52, 0x4F, 0x4B, 0x20, 0x32, 0x00, 0x35, 0x31, 0x00, 0x00,
        0x4E, 0x52, 0x57, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x4E, 0x44, 0x45,
        0x52, 0x45, 0x53, 0x20, 0x53, 0x50, 0x49, 0x45, 0x4C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x66, 0x65, 0x68, 0x6C, 0x65, 0x72, 0x00, 0x00, 0x77, 0x69, 0x63, 0x68, 0x74, 0x69, 0x67, 0x00,
        0x6F, 0x6B, 0x00, 0x00, 0x2D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x73, 0x70, 0x65,
        0x69, 0x63, 0x68, 0x65, 0x72, 0x6E, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x6C, 0x61, 0x64,
        0x65, 0x6E, 0x00, 0x00, 0x67, 0x65, 0x73, 0x75, 0x6E, 0x64, 0x68, 0x65, 0x69, 0x74, 0x00, 0x00,
        0x20, 0x20, 0x6D, 0x75, 0x6E, 0x69, 0x74, 0x69, 0x6F, 0x6E, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20,
        0x7A, 0x75, 0x72, 0xFC, 0x63, 0x6B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x75, 0x66, 0x6D, 0x2D, 0x74, 0x72, 0x65, 0x66, 0x66, 0x65, 0x72, 0x21, 0x00, 0x00, 0x00, 0x00,
        0x74, 0x72, 0x65, 0x66, 0x66, 0x65, 0x72, 0x21, 0x00, 0x00, 0x00, 0x00, 0x74, 0x72, 0x65, 0x66,
        0x66, 0x65, 0x72, 0x21, 0x00, 0x00, 0x00, 0x00, 0x74, 0x72, 0x65, 0x66, 0x66, 0x65, 0x72, 0x21,
        0x00, 0x00, 0x00, 0x00, 0xE4, 0x6E, 0x64, 0x65, 0x72, 0x6E, 0x00, 0x00,
    },
    {
        0x02000000, 0x03000000, 0x04000000,
    },
    {
        0x54, 0x61, 0x67, 0x20, 0x76, 0x6F, 0x6E, 0x20, 0x00, 0x00, 0x00, 0x00, 0x44, 0x65, 0x69, 0x6E,
        0x65, 0x20, 0x54, 0x61, 0x67, 0x73, 0x20, 0x00, 0x42, 0x65, 0x73, 0x69, 0x65, 0x67, 0x74, 0x20,
        0x76, 0x6F, 0x6E, 0x20, 0x00, 0x00, 0x00, 0x00, 0x62, 0x65, 0x73, 0x69, 0x65, 0x67, 0x74, 0x3A,
        0x20, 0x00, 0x00, 0x00, 0x53, 0x65, 0x6C, 0x62, 0x73, 0x74, 0x20, 0x67, 0x65, 0x74, 0xF6, 0x74,
        0x65, 0x74, 0x00, 0x00, 0x46, 0x6C, 0x61, 0x67, 0x67, 0x65, 0x20, 0x76, 0x65, 0x72, 0x6C, 0x6F,
        0x68, 0x72, 0x65, 0x6E, 0x21, 0x21, 0x21, 0x00, 0x45, 0x72, 0x20, 0x68, 0x61, 0x74, 0x20, 0x64,
        0x69, 0x65, 0x20, 0x46, 0x6C, 0x61, 0x67, 0x67, 0x65, 0x20, 0x61, 0x62, 0x67, 0x65, 0x6C, 0x65,
        0x67, 0x74, 0x21, 0x21, 0x21, 0x00, 0x00, 0x00, 0x77, 0x69, 0x6C, 0x6C, 0x73, 0x74, 0x20, 0x64,
        0x75, 0x3F, 0x00, 0x00, 0x77, 0x69, 0x72, 0x6B, 0x6C, 0x69, 0x63, 0x68, 0x00, 0x00, 0x00, 0x00,
        0x6A, 0x61, 0x00, 0x00, 0x6E, 0x65, 0x69, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x63, 0x68, 0x65, 0x61,
        0x74, 0x73, 0x00, 0x00, 0x6C, 0x61, 0x64, 0x65, 0x6E, 0x00, 0x00, 0x00, 0x73, 0x70, 0x65, 0x69,
        0x63, 0x68, 0x65, 0x72, 0x6E, 0x00, 0x00, 0x00, 0x63, 0x68, 0x65, 0x61, 0x74, 0x20, 0x65, 0x69,
        0x6E, 0x67, 0x65, 0x62, 0x65, 0x6E, 0x00, 0x00, 0x6A, 0x65, 0x74, 0x7A, 0x74, 0x20, 0x62, 0x65,
        0x69, 0x74, 0x72, 0x65, 0x74, 0x65, 0x6E, 0x00, 0x77, 0x61, 0x72, 0x74, 0x65, 0x2E, 0x2E, 0x00,
        0x76, 0x65, 0x72, 0x62, 0x69, 0x6E, 0x64, 0x65, 0x2E, 0x2E, 0x00, 0x00, 0x7A, 0x75, 0x72, 0xFC,
        0x63, 0x6B, 0x00, 0x00, 0x77, 0x65, 0x69, 0x74, 0x65, 0x72, 0x3F, 0x00, 0x67, 0x61, 0x6D, 0x65,
        0x20, 0x6F, 0x76, 0x65, 0x72, 0x00, 0x00, 0x00, 0x7A, 0x65, 0x69, 0x74, 0x3A, 0x20, 0x78, 0x78,
        0x00, 0x00, 0x00, 0x00, 0x66, 0x65, 0x72, 0x74, 0x69, 0x67, 0x00, 0x00, 0x6E, 0x65, 0x75, 0x65,
        0x72, 0x20, 0x63, 0x68, 0x65, 0x61, 0x74, 0x20, 0x61, 0x6B, 0x74, 0x69, 0x76, 0x69, 0x65, 0x72,
        0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x65, 0x69, 0x6E,
        0x65, 0x20, 0x66, 0x72, 0x61, 0x67, 0x73, 0x00, 0x64, 0x65, 0x69, 0x6E, 0x65, 0x20, 0x74, 0x61,
        0x67, 0x73, 0x00, 0x00, 0x67, 0x65, 0x73, 0x61, 0x6D, 0x74, 0x00, 0x00, 0x65, 0x69, 0x6E, 0x73,
        0x20, 0x20, 0x20, 0x20, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x7A, 0x77, 0x65, 0x69,
        0x20, 0x20, 0x20, 0x20, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x64, 0x72, 0x65, 0x69,
        0x20, 0x20, 0x20, 0x20, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x76, 0x69, 0x65, 0x72,
        0x20, 0x20, 0x20, 0x20, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x74, 0x61, 0x67, 0x73,
        0x20, 0x20, 0x20, 0x20, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x66, 0x72, 0x61, 0x67,
        0x73, 0x20, 0x20, 0x20, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x65, 0x72, 0x6C, 0x65,
        0x64, 0x69, 0x67, 0x74, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x74, 0x73, 0x63, 0x68,
        0x75, 0x65, 0x73, 0x73, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x65, 0x69, 0x6E, 0x73,
        0x20, 0x20, 0x20, 0x20, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x7A, 0x77, 0x65, 0x69,
        0x20, 0x20, 0x20, 0x20, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x64, 0x72, 0x65, 0x69,
        0x20, 0x20, 0x20, 0x20, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x76, 0x69, 0x65, 0x72,
        0x20, 0x20, 0x20, 0x20, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x74, 0x61, 0x67, 0x73,
        0x20, 0x20, 0x20, 0x20, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x66, 0x72, 0x61, 0x67,
        0x73, 0x20, 0x20, 0x20, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x65, 0x72, 0x6C, 0x65,
        0x64, 0x69, 0x67, 0x74, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x74, 0x73, 0x63, 0x68,
        0x75, 0x65, 0x73, 0x73, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x65, 0x69, 0x6E, 0x73,
        0x20, 0x20, 0x20, 0x20, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x7A, 0x77, 0x65, 0x69,
        0x20, 0x20, 0x20, 0x20, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x64, 0x72, 0x65, 0x69,
        0x20, 0x20, 0x20, 0x20, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x76, 0x69, 0x65, 0x72,
        0x20, 0x20, 0x20, 0x20, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x74, 0x61, 0x67, 0x73,
        0x20, 0x20, 0x20, 0x20, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x66, 0x72, 0x61, 0x67,
        0x73, 0x20, 0x20, 0x20, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x65, 0x72, 0x6C, 0x65,
        0x64, 0x69, 0x67, 0x74, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x74, 0x73, 0x63, 0x68,
        0x75, 0x65, 0x73, 0x73, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x65, 0x69, 0x6E, 0x73,
        0x20, 0x20, 0x20, 0x20, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x7A, 0x77, 0x65, 0x69,
        0x20, 0x20, 0x20, 0x20, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x64, 0x72, 0x65, 0x69,
        0x20, 0x20, 0x20, 0x20, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x76, 0x69, 0x65, 0x72,
        0x20, 0x20, 0x20, 0x20, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x74, 0x61, 0x67, 0x73,
        0x20, 0x20, 0x20, 0x20, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x66, 0x72, 0x61, 0x67,
        0x73, 0x20, 0x20, 0x20, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x65, 0x72, 0x6C, 0x65,
        0x64, 0x69, 0x67, 0x74, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x74, 0x73, 0x63, 0x68,
        0x75, 0x65, 0x73, 0x73, 0x3A, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x73, 0x70, 0x69, 0x65,
        0x6C, 0x65, 0x72, 0x31, 0x00, 0x00, 0x00, 0x00, 0x73, 0x70, 0x69, 0x65, 0x6C, 0x65, 0x72, 0x32,
        0x00, 0x00, 0x00, 0x00, 0x73, 0x70, 0x69, 0x65, 0x6C, 0x65, 0x72, 0x33, 0x00, 0x00, 0x00, 0x00,
        0x73, 0x70, 0x69, 0x65, 0x6C, 0x65, 0x72, 0x34, 0x00, 0x00, 0x00, 0x00, 0x65, 0x69, 0x6E, 0x7A,
        0x65, 0x6C, 0x00, 0x00, 0x6E, 0x65, 0x75, 0x65, 0x73, 0x20, 0x73, 0x70, 0x69, 0x65, 0x6C, 0x00,
        0x6C, 0x61, 0x64, 0x65, 0x6E, 0x00, 0x00, 0x00, 0x6D, 0x65, 0x68, 0x72, 0x73, 0x70, 0x69, 0x65,
        0x6C, 0x65, 0x72, 0x00, 0x6D, 0x65, 0x68, 0x72, 0x73, 0x70, 0x69, 0x65, 0x6C, 0x65, 0x72, 0x20,
        0x73, 0x70, 0x69, 0x65, 0x6C, 0x00, 0x00, 0x00, 0x73, 0x70, 0x69, 0x65, 0x6C, 0x61, 0x72, 0x74,
        0x20, 0x77, 0xE4, 0x68, 0x6C, 0x65, 0x6E, 0x00, 0x6A, 0x65, 0x64, 0x65, 0x72, 0x20, 0x67, 0x65,
        0x67, 0x65, 0x6E, 0x20, 0x6A, 0x65, 0x64, 0x65, 0x6E, 0x00, 0x00, 0x00, 0x6A, 0x65, 0x64, 0x65,
        0x72, 0x20, 0x67, 0x65, 0x67, 0x65, 0x6E, 0x20, 0x6A, 0x65, 0x64, 0x65, 0x6E, 0x00, 0x00, 0x00,
        0x7A, 0x65, 0x69, 0x74, 0x6C, 0x69, 0x6D, 0x69, 0x74, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x3A, 0x6B, 0x65, 0x69, 0x6E, 0x73, 0x00, 0x00, 0x00, 0x66, 0x72, 0x61, 0x67,
        0x20, 0x6C, 0x69, 0x6D, 0x69, 0x74, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A,
        0x6B, 0x65, 0x69, 0x6E, 0x73, 0x00, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65, 0x6C, 0x3A, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x77, 0x69, 0x6C, 0x6C, 0x6B, 0xFC, 0x72, 0x6C, 0x69, 0x63,
        0x68, 0x00, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65, 0x6C, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x65, 0x78,
        0x70, 0x65, 0x72, 0x69, 0x6D, 0x65, 0x6E, 0x74, 0x65, 0x6C, 0x6C, 0x65, 0x73, 0x00, 0x00, 0x00,
        0x6C, 0x65, 0x76, 0x65, 0x6C, 0x3A, 0x20, 0x6D, 0x6F, 0x72, 0x64, 0x20, 0x69, 0x6D, 0x20, 0x6D,
        0x6F, 0x6E, 0x64, 0x73, 0x63, 0x68, 0x65, 0x69, 0x6E, 0x00, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65,
        0x6C, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x61, 0x75, 0x66, 0x20, 0x65, 0x6E, 0x67, 0x65, 0x6D,
        0x20, 0x72, 0x61, 0x75, 0x6D, 0x00, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65, 0x6C, 0x3A, 0x53, 0x63,
        0x68, 0x6D, 0x69, 0x65, 0x64, 0x65, 0x20, 0x64, 0x65, 0x73, 0x20, 0x56, 0x75, 0x6C, 0x6B, 0x61,
        0x6E, 0x00, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65, 0x6C, 0x3A, 0x20, 0x54, 0x65, 0x6C, 0x65, 0x70,
        0x6F, 0x72, 0x74, 0x65, 0x72, 0x73, 0x70, 0x6F, 0x72, 0x74, 0x6C, 0x65, 0x72, 0x00, 0x00, 0x00,
        0x6C, 0x65, 0x76, 0x65, 0x6C, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x53, 0x70,
        0x69, 0x65, 0x67, 0x65, 0x6C, 0x72, 0x61, 0x6E, 0x64, 0x00, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65,
        0x6C, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5A, 0x69, 0x65, 0x6C, 0x73, 0x63, 0x68,
        0x65, 0x69, 0x62, 0x65, 0x6E, 0x00, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65, 0x6C, 0x3A, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x57, 0x61, 0x73, 0x73, 0x65, 0x72, 0x77, 0x61, 0x68, 0x6E, 0x73, 0x69, 0x6E,
        0x6E, 0x00, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65, 0x6C, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x68, 0x79, 0x73, 0x74, 0x65, 0x72, 0x69, 0x65, 0x00, 0x00, 0x00,
        0x6C, 0x65, 0x76, 0x65, 0x6C, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x47, 0x72, 0x75, 0x66, 0x74, 0x00, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65,
        0x6C, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x69, 0x6D, 0x20, 0x51, 0x75,
        0x61, 0x64, 0x72, 0x61, 0x74, 0x00, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65, 0x6C, 0x3A, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x61, 0x62, 0x61, 0x72, 0x74, 0x69, 0x67, 0x65, 0x20, 0x61, 0x63, 0x68,
        0x74, 0x00, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65, 0x6C, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x69, 0x6E, 0x73, 0x20, 0x53, 0x63, 0x68, 0x77, 0x61, 0x72, 0x7A, 0x65, 0x00, 0x00, 0x00,
        0x73, 0x74, 0x72, 0x75, 0x6B, 0x74, 0x75, 0x72, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x62, 0x75, 0x72, 0x67, 0x00, 0x00, 0x00, 0x73, 0x74, 0x72, 0x75,
        0x6B, 0x74, 0x75, 0x72, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x73, 0x74, 0x61, 0x68,
        0x6C, 0x77, 0x65, 0x72, 0x6B, 0x00, 0x00, 0x00, 0x73, 0x74, 0x72, 0x75, 0x6B, 0x74, 0x75, 0x72,
        0x20, 0x20, 0x20, 0x3A, 0x70, 0x61, 0x6C, 0x69, 0x73, 0x61, 0x64, 0x65, 0x6E, 0x66, 0x6F, 0x72,
        0x74, 0x00, 0x00, 0x00, 0x73, 0x74, 0x72, 0x75, 0x6B, 0x74, 0x75, 0x72, 0x20, 0x20, 0x20, 0x3A,
        0x20, 0x20, 0x20, 0x6B, 0x61, 0x74, 0x61, 0x6B, 0x6F, 0x6D, 0x62, 0x65, 0x6E, 0x00, 0x00, 0x00,
        0x73, 0x74, 0x72, 0x75, 0x6B, 0x74, 0x75, 0x72, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x20,
        0x47, 0x65, 0x66, 0xE4, 0x6E, 0x67, 0x6E, 0x69, 0x73, 0x00, 0x00, 0x00, 0x73, 0x74, 0x72, 0x75,
        0x6B, 0x74, 0x75, 0x72, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x67, 0x72, 0x6F, 0x73, 0x73,
        0x73, 0x74, 0x61, 0x64, 0x74, 0x00, 0x00, 0x00, 0x73, 0x74, 0x72, 0x75, 0x6B, 0x74, 0x75, 0x72,
        0x20, 0x20, 0x20, 0x3A, 0x20, 0x72, 0x6F, 0x74, 0x65, 0x72, 0x20, 0x64, 0x72, 0x61, 0x63, 0x68,
        0x65, 0x00, 0x00, 0x00, 0x73, 0x74, 0x72, 0x75, 0x6B, 0x74, 0x75, 0x72, 0x20, 0x20, 0x20, 0x3A,
        0x20, 0x20, 0x20, 0x20, 0x70, 0x61, 0x69, 0x6E, 0x74, 0x62, 0x61, 0x6C, 0x6C, 0x00, 0x00, 0x00,
        0x73, 0x74, 0x72, 0x75, 0x6B, 0x74, 0x75, 0x72, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x53, 0x6D, 0x69, 0x6C, 0x65, 0x79, 0x00, 0x00, 0x00, 0x66, 0x61, 0x64, 0x65,
        0x6E, 0x6B, 0x72, 0x65, 0x75, 0x7A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A,
        0x20, 0x20, 0x20, 0x61, 0x6E, 0x00, 0x00, 0x00, 0x66, 0x61, 0x64, 0x65, 0x6E, 0x6B, 0x72, 0x65,
        0x75, 0x7A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x20, 0x61, 0x75,
        0x73, 0x00, 0x00, 0x00, 0x73, 0x70, 0x69, 0x65, 0x6C, 0x73, 0x74, 0x61, 0x72, 0x74, 0x00, 0x00,
        0x7A, 0x75, 0x72, 0xFC, 0x63, 0x6B, 0x00, 0x00, 0x66, 0x72, 0x61, 0x67, 0x20, 0x74, 0x61, 0x67,
        0x00, 0x00, 0x00, 0x00, 0x66, 0x72, 0x61, 0x67, 0x20, 0x74, 0x61, 0x67, 0x00, 0x00, 0x00, 0x00,
        0x74, 0x61, 0x67, 0x20, 0x6C, 0x69, 0x6D, 0x69, 0x74, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x3A, 0x6B, 0x65, 0x69, 0x6E, 0x73, 0x00, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65,
        0x6C, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x69, 0x72, 0x72, 0x65,
        0x6E, 0x68, 0x61, 0x75, 0x73, 0x00, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65, 0x6C, 0x3A, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x65, 0x72, 0x77, 0x69, 0x73, 0x63, 0x68,
        0x74, 0x00, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65, 0x6C, 0x3A, 0x20, 0x6C, 0xFC, 0x67, 0x65, 0x6E,
        0x20, 0x75, 0x6E, 0x64, 0x20, 0x62, 0x65, 0x74, 0x72, 0xFC, 0x67, 0x65, 0x6E, 0x00, 0x00, 0x00,
        0x6C, 0x65, 0x76, 0x65, 0x6C, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70,
        0x72, 0x69, 0x6D, 0x61, 0x74, 0x74, 0x69, 0x63, 0x61, 0x00, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65,
        0x6C, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x6B, 0x75, 0x67, 0x65, 0x6C,
        0x68, 0x61, 0x67, 0x65, 0x6C, 0x00, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65, 0x6C, 0x3A, 0x20, 0x61,
        0x6E, 0x64, 0x65, 0x72, 0x73, 0x20, 0x61, 0x6C, 0x73, 0x20, 0x65, 0x72, 0x68, 0x6F, 0x66, 0x66,
        0x74, 0x00, 0x00, 0x00, 0x74, 0x65, 0x61, 0x6D, 0x20, 0x67, 0x65, 0x67, 0x6E, 0x65, 0x72, 0x00,
        0x77, 0x61, 0x66, 0x66, 0x65, 0x6E, 0x20, 0x65, 0x69, 0x6E, 0x72, 0x69, 0x63, 0x68, 0x74, 0x65,
        0x6E, 0x00, 0x00, 0x00, 0x67, 0x65, 0x66, 0x72, 0x69, 0x65, 0x72, 0x6B, 0x61, 0x6E, 0x6F, 0x6E,
        0x65, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x61, 0x6E, 0x00, 0x00,
        0x67, 0x65, 0x66, 0x72, 0x69, 0x65, 0x72, 0x6B, 0x61, 0x6E, 0x6F, 0x6E, 0x65, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x61, 0x75, 0x73, 0x00, 0x00, 0x66, 0x65, 0x75, 0x65,
        0x72, 0x73, 0x74, 0x75, 0x72, 0x6D, 0x2D, 0x6B, 0x61, 0x6E, 0x6F, 0x6E, 0x65, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x3A, 0x20, 0x61, 0x6E, 0x00, 0x00, 0x66, 0x65, 0x75, 0x65, 0x72, 0x73, 0x74, 0x75,
        0x72, 0x6D, 0x2D, 0x6B, 0x61, 0x6E, 0x6F, 0x6E, 0x65, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x61,
        0x75, 0x73, 0x00, 0x00, 0x73, 0x63, 0x68, 0x72, 0x65, 0x64, 0x64, 0x65, 0x72, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x61, 0x6E, 0x00, 0x00,
        0x73, 0x63, 0x68, 0x72, 0x65, 0x64, 0x64, 0x65, 0x72, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x61, 0x75, 0x73, 0x00, 0x00, 0x70, 0x6C, 0x61, 0x73,
        0x6D, 0x61, 0x67, 0x65, 0x73, 0x63, 0x68, 0xFC, 0x74, 0x7A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x3A, 0x20, 0x61, 0x6E, 0x00, 0x00, 0x70, 0x6C, 0x61, 0x73, 0x6D, 0x61, 0x67, 0x65,
        0x73, 0x63, 0x68, 0xFC, 0x74, 0x7A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x61,
        0x75, 0x73, 0x00, 0x00, 0x7A, 0x69, 0x65, 0x6C, 0x73, 0x75, 0x63, 0x68, 0x6B, 0x61, 0x6E, 0x6F,
        0x6E, 0x65, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x61, 0x6E, 0x00, 0x00,
        0x7A, 0x69, 0x65, 0x6C, 0x73, 0x75, 0x63, 0x68, 0x6B, 0x61, 0x6E, 0x6F, 0x6E, 0x65, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x61, 0x75, 0x73, 0x00, 0x00, 0x67, 0x72, 0x61, 0x6E,
        0x61, 0x74, 0x65, 0x6E, 0x77, 0x65, 0x72, 0x66, 0x65, 0x72, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x3A, 0x20, 0x61, 0x6E, 0x00, 0x00, 0x67, 0x72, 0x61, 0x6E, 0x61, 0x74, 0x65, 0x6E,
        0x77, 0x65, 0x72, 0x66, 0x65, 0x72, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x61,
        0x75, 0x73, 0x00, 0x00, 0x73, 0x6B, 0x6F, 0x72, 0x70, 0x69, 0x6F, 0x6E, 0x2D, 0x72, 0x61, 0x6B,
        0x65, 0x74, 0x65, 0x6E, 0x77, 0x65, 0x72, 0x66, 0x65, 0x72, 0x3A, 0x20, 0x61, 0x6E, 0x00, 0x00,
        0x73, 0x6B, 0x6F, 0x72, 0x70, 0x69, 0x6F, 0x6E, 0x2D, 0x72, 0x61, 0x6B, 0x65, 0x74, 0x65, 0x6E,
        0x77, 0x65, 0x72, 0x66, 0x65, 0x72, 0x3A, 0x61, 0x75, 0x73, 0x00, 0x00, 0x74, 0x6F, 0x72, 0x70,
        0x65, 0x64, 0x6F, 0x77, 0x65, 0x72, 0x66, 0x65, 0x72, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x3A, 0x20, 0x61, 0x6E, 0x00, 0x00, 0x74, 0x6F, 0x72, 0x70, 0x65, 0x64, 0x6F, 0x77,
        0x65, 0x72, 0x66, 0x65, 0x72, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x61,
        0x75, 0x73, 0x00, 0x00, 0x74, 0x72, 0x61, 0x69, 0x6E, 0x69, 0x6E, 0x67, 0x00, 0x00, 0x00, 0x00,
        0x6C, 0x65, 0x76, 0x65, 0x6C, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x77,
        0x69, 0x6C, 0x6C, 0x6B, 0xFC, 0x72, 0x6C, 0x69, 0x63, 0x68, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65,
        0x6C, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x62, 0x6F, 0x67, 0x65, 0x6E, 0x73, 0x63, 0x68,
        0x69, 0x65, 0x73, 0x73, 0x65, 0x6E, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65, 0x6C, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x73, 0x63, 0x68, 0x69, 0x65, 0x73, 0x73,
        0x65, 0x6E, 0x00, 0x00, 0x6C, 0x65, 0x76, 0x65, 0x6C, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x7A, 0x65, 0x68, 0x6E, 0x6B, 0x61, 0x6D, 0x70, 0x66, 0x00, 0x00,
        0x72, 0x75, 0x6E, 0x64, 0x65, 0x6E, 0x7A, 0x61, 0x68, 0x6C, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x73, 0x70, 0x69, 0x65,
        0x6C, 0x73, 0x74, 0x61, 0x72, 0x74, 0x00, 0x00, 0x7A, 0x75, 0x72, 0xFC, 0x63, 0x6B, 0x00, 0x00,
        0x6C, 0x61, 0x64, 0x65, 0x6E, 0x00, 0x00, 0x00, 0x6F, 0x70, 0x74, 0x69, 0x6F, 0x6E, 0x65, 0x6E,
        0x00, 0x00, 0x00, 0x00, 0x63, 0x68, 0x65, 0x61, 0x74, 0x73, 0x00, 0x00, 0x63, 0x68, 0x65, 0x63,
        0x6B, 0x70, 0x6F, 0x69, 0x6E, 0x74, 0x00, 0x00, 0x73, 0x70, 0x65, 0x69, 0x63, 0x68, 0x65, 0x72,
        0x70, 0x75, 0x6E, 0x6B, 0x74, 0x00, 0x00, 0x00, 0x73, 0x6F, 0x75, 0x6E, 0x64, 0x2D, 0x6F, 0x70,
        0x74, 0x69, 0x6F, 0x6E, 0x65, 0x6E, 0x00, 0x00, 0x6C, 0x61, 0x75, 0x74, 0x73, 0x74, 0xE4, 0x72,
        0x6B, 0x65, 0x2F, 0x6D, 0x75, 0x73, 0x69, 0x6B, 0x20, 0x20, 0x3A, 0x20, 0x61, 0x75, 0x73, 0x00,
        0x6C, 0x61, 0x75, 0x74, 0x73, 0x74, 0xE4, 0x72, 0x6B, 0x65, 0x2F, 0x6D, 0x75, 0x73, 0x69, 0x6B,
        0x20, 0x20, 0x3A, 0x20, 0x6D, 0x61, 0x78, 0x00, 0x6C, 0x61, 0x75, 0x74, 0x73, 0x74, 0xE4, 0x72,
        0x6B, 0x65, 0x2F, 0x6D, 0x75, 0x73, 0x69, 0x6B, 0x20, 0x20, 0x3A, 0x6E, 0x6F, 0x72, 0x6D, 0x00,
        0x6C, 0x61, 0x75, 0x74, 0x73, 0x74, 0xE4, 0x72, 0x6B, 0x65, 0x2F, 0x6D, 0x75, 0x73, 0x69, 0x6B,
        0x20, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x00, 0x6C, 0x61, 0x75, 0x74, 0x73, 0x74, 0xE4, 0x72,
        0x6B, 0x65, 0x2F, 0x73, 0x66, 0x78, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x20, 0x61, 0x75, 0x73, 0x00,
        0x6C, 0x61, 0x75, 0x74, 0x73, 0x74, 0xE4, 0x72, 0x6B, 0x65, 0x2F, 0x73, 0x66, 0x78, 0x20, 0x20,
        0x20, 0x20, 0x3A, 0x20, 0x6D, 0x61, 0x78, 0x00, 0x6C, 0x61, 0x75, 0x74, 0x73, 0x74, 0xE4, 0x72,
        0x6B, 0x65, 0x2F, 0x73, 0x66, 0x78, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x6E, 0x6F, 0x72, 0x6D, 0x00,
        0x6C, 0x61, 0x75, 0x74, 0x73, 0x74, 0xE4, 0x72, 0x6B, 0x65, 0x2F, 0x73, 0x66, 0x78, 0x20, 0x20,
        0x20, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x00, 0x6C, 0x61, 0x75, 0x74, 0x73, 0x74, 0xE4, 0x72,
        0x6B, 0x65, 0x2F, 0x73, 0x70, 0x72, 0x61, 0x63, 0x68, 0x65, 0x3A, 0x20, 0x61, 0x75, 0x73, 0x00,
        0x6C, 0x61, 0x75, 0x74, 0x73, 0x74, 0xE4, 0x72, 0x6B, 0x65, 0x2F, 0x73, 0x70, 0x72, 0x61, 0x63,
        0x68, 0x65, 0x3A, 0x20, 0x6D, 0x61, 0x78, 0x00, 0x6C, 0x61, 0x75, 0x74, 0x73, 0x74, 0xE4, 0x72,
        0x6B, 0x65, 0x2F, 0x73, 0x70, 0x72, 0x61, 0x63, 0x68, 0x65, 0x3A, 0x6E, 0x6F, 0x72, 0x6D, 0x00,
        0x6C, 0x61, 0x75, 0x74, 0x73, 0x74, 0xE4, 0x72, 0x6B, 0x65, 0x2F, 0x73, 0x70, 0x72, 0x61, 0x63,
        0x68, 0x65, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x00, 0x6D, 0x75, 0x73, 0x69, 0x6B, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x6E, 0x65, 0x69, 0x6E, 0x00,
        0x6D, 0x75, 0x73, 0x69, 0x63, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x00, 0x69, 0x6E, 0x64, 0x65, 0x78, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x6E, 0x65, 0x69, 0x6E, 0x00,
        0x73, 0x70, 0x72, 0x61, 0x63, 0x68, 0x65, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x3A, 0x6E, 0x65, 0x69, 0x6E, 0x00, 0x6D, 0x69, 0x73, 0x73, 0x69, 0x6F, 0x6E, 0x20,
        0x62, 0x65, 0x65, 0x6E, 0x64, 0x65, 0x74, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x6D, 0x69, 0x73, 0x73,
        0x69, 0x6F, 0x6E, 0x20, 0x67, 0x65, 0x73, 0x63, 0x68, 0x65, 0x69, 0x74, 0x65, 0x72, 0x74, 0x2E,
        0x00, 0x00, 0x00, 0x00, 0x74, 0x6F, 0x74, 0x65, 0x6D, 0x20, 0x76, 0x65, 0x72, 0x74, 0x65, 0x69,
        0x64, 0x69, 0x67, 0x65, 0x6E, 0x00, 0x00, 0x00, 0x73, 0x70, 0x69, 0x65, 0x6C, 0x65, 0x72, 0x74,
        0x65, 0x6D, 0x70, 0x6F, 0x20, 0x3A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x00, 0x00, 0x00, 0x73, 0x70, 0x69, 0x65, 0x6C, 0x65, 0x72, 0x74, 0x65, 0x6D, 0x70, 0x6F,
        0x20, 0x3A, 0x20, 0x20, 0x20, 0x73, 0x74, 0x61, 0x6E, 0x64, 0x61, 0x72, 0x64, 0x00, 0x00, 0x00,
        0x73, 0x74, 0x61, 0x6E, 0x64, 0x61, 0x72, 0x64, 0x00, 0x00, 0x00, 0x00, 0x67, 0x65, 0x73, 0x75,
        0x6E, 0x64, 0x68, 0x65, 0x69, 0x74, 0x20, 0x73, 0x63, 0x68, 0x6C, 0x65, 0x63, 0x68, 0x74, 0x00,
        0x20, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00,
        0x33, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00,
        0x37, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x39, 0x00, 0x00, 0x00, 0x4D, 0x69, 0x6E, 0x69,
        0x47, 0x61, 0x6D, 0x65, 0x73, 0x00, 0x00, 0x00, 0x43, 0x68, 0x69, 0x63, 0x6B, 0x65, 0x6E, 0x73,
        0x20, 0x49, 0x6E, 0x20, 0x54, 0x68, 0x65, 0x20, 0x4D, 0x69, 0x73, 0x74, 0x00, 0x00, 0x00, 0x00,
        0x57, 0x69, 0x6C, 0x6C, 0x69, 0x61, 0x6D, 0x20, 0x54, 0x65, 0x6C, 0x6C, 0x00, 0x00, 0x00, 0x00,
        0x54, 0x72, 0x61, 0x70, 0x20, 0x53, 0x68, 0x6F, 0x6F, 0x74, 0x69, 0x6E, 0x67, 0x00, 0x00, 0x00,
        0x53, 0x70, 0x61, 0x6E, 0x6B, 0x20, 0x54, 0x68, 0x65, 0x20, 0x4D, 0x6F, 0x6E, 0x6B, 0x65, 0x79,
        0x00, 0x00, 0x00, 0x00, 0x4D, 0x6F, 0x6E, 0x6B, 0x65, 0x79, 0x20, 0x42, 0x75, 0x73, 0x69, 0x6E,
        0x65, 0x73, 0x73, 0x00, 0x42, 0x6F, 0x77, 0x20, 0x46, 0x69, 0x73, 0x68, 0x69, 0x6E, 0x67, 0x00,
        0x53, 0x6B, 0x65, 0x65, 0x74, 0x20, 0x47, 0x72, 0x61, 0x70, 0x70, 0x6C, 0x65, 0x00, 0x00, 0x00,
        0x50, 0x6C, 0x61, 0x79, 0x65, 0x72, 0x20, 0x4F, 0x6E, 0x65, 0x20, 0x57, 0x69, 0x6E, 0x73, 0x00,
        0x50, 0x6C, 0x61, 0x79, 0x65, 0x72, 0x20, 0x54, 0x77, 0x6F, 0x20, 0x57, 0x69, 0x6E, 0x73, 0x00,
        0x50, 0x6C, 0x61, 0x79, 0x65, 0x72, 0x20, 0x54, 0x68, 0x72, 0x65, 0x65, 0x20, 0x57, 0x69, 0x6E,
        0x73, 0x00, 0x00, 0x00, 0x50, 0x6C, 0x61, 0x79, 0x65, 0x72, 0x20, 0x46, 0x6F, 0x75, 0x72, 0x20,
        0x57, 0x69, 0x6E, 0x73, 0x00, 0x00, 0x00, 0x00, 0x47, 0x61, 0x6D, 0x65, 0x20, 0x54, 0x69, 0x65,
        0x64, 0x21, 0x00, 0x00, 0x47, 0x65, 0x74, 0x20, 0x52, 0x65, 0x61, 0x64, 0x79, 0x21, 0x00, 0x00,
        0x47, 0x4F, 0x21, 0x00,
    },
    {
        (unsigned int)&s_controllerPakMessageDe_RageWarsTeam, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_Projektmanager, (unsigned int)&s_controllerPakMessageDe_MarkPacini, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_Programmierleitung, (unsigned int)&s_controllerPakMessageDe_FranciscoJavierLafuente, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16],
        (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_KbnstlerischeLeitung, (unsigned int)&s_controllerPakMessageDe_MichaelDaubert, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_JasonBehrDesign, (unsigned int)&s_controllerPakMessageDe_BruceCoonerProgrammierung, (unsigned int)&s_controllerPakMessageDe_JimCowlishawProgrammierung,
        (unsigned int)&s_controllerPakMessageDe_MichaelFongDigitalproduktion, (unsigned int)&s_controllerPakMessageDe_NeillGlancyDesign, (unsigned int)&s_controllerPakMessageDe_MichaelHueyDesign, (unsigned int)&s_controllerPakMessageDe_MattKyleProgrammierung, (unsigned int)&s_controllerPakMessageDe_TrevorLemoineDigitalproduktion, (unsigned int)&s_controllerPakMessageDe_MarcMackinDigitalproduktion, (unsigned int)&s_controllerPakMessageDe_BradMarquesDigitalproduktion, (unsigned int)&s_controllerPakMessageDe_PaulMastersProgrammierung,
        (unsigned int)&s_controllerPakMessageDe_RobbieMillerDigitalproduktion, (unsigned int)&s_controllerPakMessageDe_JeffSheltonDesign, (unsigned int)&s_controllerPakMessageDe_RobertWilsherDigitalproduktion, (unsigned int)&s_controllerPakMessageDe_RobWhitakerDigitalproduktion, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ZusetzlichesDesignCopy, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16],
        (unsigned int)&s_controllerPakMessageDe_ScottBrocker, (unsigned int)&s_controllerPakMessageDe_PeterFranco, (unsigned int)&s_controllerPakMessageDe_AlexOmlansky, (unsigned int)&s_controllerPakMessageDe_RyanTracy, (unsigned int)&s_controllerPakMessageDe_DigitalImagingGroup, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ZusetzlicheProgrammierung,
        (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_SteveBroumley, (unsigned int)&s_controllerPakMessageDe_StevanHird, (unsigned int)&s_controllerPakMessageDe_AndyOneil, (unsigned int)&s_controllerPakMessageDe_DavidSmith, (unsigned int)&s_controllerPakMessageDe_BrianWatson, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16],
        (unsigned int)&s_controllerPakMessageDe_ZusetzlichesDesign, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_DavidDienstbier, (unsigned int)&s_controllerPakMessageDe_BeyBickerton, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_Sounddesign, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16],
        (unsigned int)&s_controllerPakMessageDe_DarrenMitchell, (unsigned int)&s_controllerPakMessageDe_MarcSchaefgen, (unsigned int)&s_controllerPakMessageDe_JohnHenke, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_AustinQs, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_LeiterQs,
        (unsigned int)&s_controllerPakMessageDe_ToddDowd, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_Projektleitung, (unsigned int)&s_controllerPakMessageDe_RussBrewer, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_Tester, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16],
        (unsigned int)&s_controllerPakMessageDe_JerremyArnston, (unsigned int)&s_controllerPakMessageDe_ChrisKendall, (unsigned int)&s_controllerPakMessageDe_MarkRichards, (unsigned int)&s_controllerPakMessageDe_BrandonRowlett, (unsigned int)&s_controllerPakMessageDe_JimStrong, (unsigned int)&s_controllerPakMessageDe_ShaneTate, (unsigned int)&s_controllerPakMessageDe_JustinWithers, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16],
        (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_Sprecher, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_TravisDavisTurok, (unsigned int)&s_controllerPakMessageDe_BernadetteNasonAdon, (unsigned int)&s_controllerPakMessageDe_ToddLowePurlin, (unsigned int)&s_controllerPakMessageDe_JessicaRobertsonSyra, (unsigned int)&s_controllerPakMessageDe_DavidKrauseFirebornDinosoids,
        (unsigned int)&s_controllerPakMessageDe_DavidDienstbierCampaigner, (unsigned int)&s_controllerPakMessageDe_JoseBrownOblivionGuardian, (unsigned int)&s_controllerPakMessageDe_DougForrestBastille, (unsigned int)&s_controllerPakMessageDe_TitosMenchacaTalSet, (unsigned int)&s_controllerPakMessageDe_MarcSchaefgenLordOfThe, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_LeitungAcclaimStudiosAustin,
        (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_GmDerAcclaimStudiosAustin, (unsigned int)&s_controllerPakMessageDe_RussellByrd, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_TechnischerLeiter, (unsigned int)&s_controllerPakMessageDe_StevenBroumley, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_LeiterProduktentwicklung,
        (unsigned int)&s_controllerPakMessageDe_MalcolmCrummack, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_Kreativdirektor, (unsigned int)&s_controllerPakMessageDe_DavidDienstbier, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_AudioManager, (unsigned int)&s_controllerPakMessageDe_DarrenMitchell, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16],
        (unsigned int)&s_controllerPakMessageDe_LeitungDigitalproduktion, (unsigned int)&s_controllerPakMessageDe_AlanJohnson, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_WeltweitesManagement, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_VpFbrProduktentwicklungUndDesign, (unsigned int)&s_controllerPakMessageDe_NigelCook,
        (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_VpFbrDieDigitalproduktion, (unsigned int)&s_controllerPakMessageDe_CyrusLum, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_VpTechnologie, (unsigned int)&s_controllerPakMessageDe_CraigGalley, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_AusfbherenderVpDerAcclaimStudios,
        (unsigned int)&s_controllerPakMessageDe_DarrenStubbington, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_PublisherCredits, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_AcclaimEntertainmentInc, (unsigned int)&s_controllerPakMessageDe_NyProductDevelopment, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16],
        (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_Produzent, (unsigned int)&s_controllerPakMessageDe_JamesDaly, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_Projektleitung, (unsigned int)&s_controllerPakMessageDe_KathleenByrne, (unsigned int)&s_controllerPakMessageDe_NicoleRuisi,
        (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_Handbuch, (unsigned int)&s_controllerPakMessageDe_BillDickson, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_QsManager, (unsigned int)&s_controllerPakMessageDe_CarolCaracciolo,
        (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_QsLeitung, (unsigned int)&s_controllerPakMessageDe_DaleTaylor, (unsigned int)&s_controllerPakMessageDe_JeffRosa, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_LeitungAnalyse,
        (unsigned int)&s_controllerPakMessageDe_BrianRegan, (unsigned int)&s_controllerPakMessageDe_MikePatterson, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_Analyse, (unsigned int)&s_controllerPakMessageDe_MarkGarone, (unsigned int)&s_controllerPakMessageDe_MattCanonico, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16],
        (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_Projektleiter, (unsigned int)&s_controllerPakMessageDe_ChrisRappo, (unsigned int)&s_controllerPakMessageDe_JonNicolai, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_Tester, (unsigned int)&s_controllerPakMessageDe_PaulDicarlo,
        (unsigned int)&s_controllerPakMessageDe_JoshuaRogers, (unsigned int)&s_controllerPakMessageDe_DanBadilla, (unsigned int)&s_controllerPakMessageDe_BrhettHohwald, (unsigned int)&s_controllerPakMessageDe_LucAngrandIi, (unsigned int)&s_controllerPakMessageDe_ScottSnopowski, (unsigned int)&s_controllerPakMessageDe_MauricePhilips, (unsigned int)&s_controllerPakMessageDe_JoeCarbone, (unsigned int)&s_controllerPakMessageDe_PaulJohnson,
        (unsigned int)&s_controllerPakMessageDe_DjPeluso, (unsigned int)&s_controllerPakMessageDe_JayCapozello, (unsigned int)&s_controllerPakMessageDe_MarkBerkowitz, (unsigned int)&s_controllerPakMessageDe_LloydThompson, (unsigned int)&s_controllerPakMessageDe_MaxImas, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_TurnoverKoordinator, (unsigned int)&s_controllerPakMessageDe_ChrisMaher,
        (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_TurnoverTechniker, (unsigned int)&s_controllerPakMessageDe_AnthonyGentile, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_Techniker, (unsigned int)&s_controllerPakMessageDe_ChrisZino, (unsigned int)&s_controllerPakMessageDe_MikeSterzel, (unsigned int)&s_controllerPakMessageDe_ChrisFrisone,
        (unsigned int)&s_controllerPakMessageDe_UlisesBatalla, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_MarketingProduktmanager, (unsigned int)&s_controllerPakMessageDe_DonJackson, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_MarketingSpielanalyse, (unsigned int)&s_controllerPakMessageDe_JpCarnovale, (unsigned int)&s_controllerPakMessageDe_JackScalici,
        (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_PrManager, (unsigned int)&s_controllerPakMessageDe_MichelleSeebach, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_SrManagerAcclaimOnline, (unsigned int)&s_controllerPakMessageDe_BenFischbach, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_InternetArchitekt,
        (unsigned int)&s_controllerPakMessageDe_BobbySaha, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_OnlineEditor, (unsigned int)&s_controllerPakMessageDe_EdFortune, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_BesondererDankAn, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16],
        (unsigned int)&s_controllerPakMessageDe_WirMnchtenBesondersUnseren, (unsigned int)&s_controllerPakMessageDe_FreundenUndFamilienFbr, (unsigned int)&s_controllerPakMessageDe_IhreUnterstbtzungUndIhr, (unsigned int)&s_controllerPakMessageDe_VerstendnisDassWirNieZuhause, (unsigned int)&s_controllerPakMessageDe_WarenDanken, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_NochMehrDankAn, (unsigned int)&s_controllerPakMessageDe_JennyCowlishaw,
        (unsigned int)&s_controllerPakMessageDe_DamarisAuchCocoUndSnikers, (unsigned int)&s_controllerPakMessageDe_MarleneUndRaymondPaciniDanke, (unsigned int)&s_controllerPakMessageDe_DassIchTunDurfteWas, (unsigned int)&s_controllerPakMessageDe_DrDonTHueyJr, (unsigned int)&s_controllerPakMessageDe_BrotherIchVermisseDich, (unsigned int)&s_controllerPakMessageDe_DavidUndMattImSatellite, (unsigned int)&s_controllerPakMessageDe_JeffEverettDafbrDassEr, (unsigned int)&s_controllerPakMessageDe_HalbesTeamGeliehenHat,
        (unsigned int)&s_controllerPakMessageDe_SheaMackinCadeKylanUnd, (unsigned int)&s_controllerPakMessageDe_MikeMarques, (unsigned int)&s_controllerPakMessageDe_DanHillUndFamilie, (unsigned int)&s_controllerPakMessageDe_GreyThanksKasTsBehr, (unsigned int)&s_controllerPakMessageDe_LorraineBrittanyUndKatie, (unsigned int)&s_controllerPakMessageDe_AngelaDafbrDassSieIn, (unsigned int)&s_controllerPakMessageDe_RamiFbrAllesWasSie, (unsigned int)&s_controllerPakMessageDe_AnnaLangstonSimonSkedd,
        (unsigned int)&s_controllerPakMessageDe_JimDelbridgeHaileySebastian, (unsigned int)&s_controllerPakMessageDe_UndLilly, (unsigned int)&s_controllerPakMessageDe_PamTrumanUndTuckerFbr, (unsigned int)&s_controllerPakMessageDe_IhreGeduld, (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16],
        (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_ControllerPak[16], (unsigned int)&s_controllerPakMessageDe_BesuchenSieUnsereWebsiteUnter, 0x00000000, 0x00000000,
        (unsigned int)g_screenMessageSubstitutionReplacement, (unsigned int)g_pickupAmmoDefinitions + 0x180,
    },
};
#endif
#ifdef VERSION_EU_X
struct {
    unsigned int screenMessageSetupWords[313];
    unsigned char emptyTextSlots[12];
    unsigned char emptyTextSlots_repeat2[12];
    unsigned char emptyTextSlots_repeat3[12];
    unsigned char emptyTextSlots_repeat4[12];
    unsigned char emptyTextSlots_repeat5[12];
    unsigned char emptyTextSlots_repeat6[12];
    unsigned char emptyTextSlots_repeat7[16];
    unsigned char emptyTextSlots_repeat8[16];
    unsigned char emptyTextSlots_repeat9[16];
    unsigned char emptyTextSlots_repeat10[16];
    unsigned char emptyTextSlots_repeat11[16];
    unsigned char emptyTextSlots_repeat12[12];
    unsigned char emptyTextSlots_repeat13[20];
    unsigned char emptyTextSlots_repeat14[20];
    unsigned char emptyTextSlots_repeat15[16];
    unsigned char emptyTextSlots_repeat16[16];
    unsigned char emptyTextSlots_repeat17[16];
    unsigned char emptyTextSlots_repeat18[12];
    unsigned char emptyTextSlots_repeat19[16];
    unsigned char emptyTextSlots_repeat20[20];
    unsigned char emptyTextSlots_repeat21[20];
    unsigned char emptyTextSlots_repeat22[20];
    unsigned char emptyTextSlots_repeat23[24];
    unsigned char emptyTextSlots_repeat24[20];
    unsigned char emptyTextSlots_repeat25[20];
    unsigned char emptyTextSlots_repeat26[16];
    unsigned char emptyTextSlots_repeat27[20];
    unsigned char emptyTextSlots_repeat28[20];
    unsigned char emptyTextSlots_repeat29[16];
    unsigned char emptyTextSlots_repeat30[20];
    unsigned char emptyTextSlots_repeat31[24];
    unsigned char emptyTextSlots_repeat32[12];
    unsigned char emptyTextSlots_repeat33[12];
    unsigned char emptyTextSlots_repeat34[12];
    unsigned char emptyTextSlots_repeat35[12];
    unsigned char emptyTextSlots_repeat36[16];
    unsigned char emptyTextSlots_repeat37[8];
    unsigned char emptyTextSlots_repeat38[8];
    unsigned char emptyTextSlots_repeat39[16];
    unsigned char emptyTextSlots_repeat40[8];
    unsigned char emptyTextSlots_repeat41[16];
    unsigned char emptyTextSlots_repeat42[12];
    unsigned char emptyTextSlots_repeat43[12];
    unsigned char emptyTextSlots_repeat44[12];
    unsigned char emptyTextSlots_repeat45[12];
    unsigned char emptyTextSlots_repeat46[12];
    unsigned char emptyTextSlots_repeat47[12];
    unsigned char emptyTextSlots_repeat48[12];
    unsigned char emptyTextSlots_repeat49[16];
    unsigned char emptyTextSlots_repeat50[16];
    unsigned char emptyTextSlots_repeat51[12];
    unsigned char emptyTextSlots_repeat52[12];
    unsigned char emptyTextSlots_repeat53[16];
    unsigned char emptyTextSlots_repeat54[16];
    unsigned char emptyTextSlots_repeat55[16];
    unsigned char emptyTextSlots_repeat56[16];
    unsigned char emptyTextSlots_repeat57[16];
    unsigned char emptyTextSlots_repeat58[20];
    unsigned char emptyTextSlots_repeat59[20];
    unsigned char emptyTextSlots_repeat60[20];
    unsigned char emptyTextSlots_repeat61[20];
    unsigned char emptyTextSlots_repeat62[24];
    unsigned char emptyTextSlots_repeat63[16];
    unsigned char emptyTextSlots_repeat64[16];
    unsigned char emptyTextSlots_repeat65[16];
    unsigned char emptyTextSlots_repeat66[20];
    unsigned char emptyTextSlots_repeat67[20];
    unsigned char emptyTextSlots_repeat68[16];
    unsigned char emptyTextSlots_repeat69[16];
    unsigned char emptyTextSlots_repeat70[20];
    unsigned char emptyTextSlots_repeat71[8];
    unsigned char emptyTextSlots_repeat72[12];
    unsigned char emptyTextSlots_repeat73[24];
    unsigned char emptyTextSlots_repeat74[8];
    unsigned char emptyTextSlots_repeat75[20];
    unsigned char emptyTextSlots_repeat76[8];
    unsigned char emptyTextSlots_repeat77[20];
    unsigned char emptyTextSlots_repeat78[20];
    unsigned char emptyTextSlots_repeat79[12];
    unsigned char emptyTextSlots_repeat80[20];
    unsigned char emptyTextSlots_repeat81[16];
    unsigned char emptyTextSlots_repeat82[16];
    unsigned char emptyTextSlots_repeat83[16];
    unsigned char emptyTextSlots_repeat84[16];
    unsigned char emptyTextSlots_repeat85[20];
    unsigned char emptyTextSlots_repeat86[20];
    unsigned char emptyTextSlots_repeat87[12];
    unsigned char emptyTextSlots_repeat88[8];
    unsigned char emptyTextSlots_repeat89[16];
    unsigned char emptyTextSlots_repeat90[16];
    unsigned char emptyTextSlots_repeat91[16];
    unsigned char emptyTextSlots_repeat92[12];
    unsigned char emptyTextSlots_repeat93[16];
    unsigned char emptyTextSlots_repeat94[12];
    unsigned char emptyTextSlots_repeat95[16];
    unsigned char emptyTextSlots_repeat96[16];
    unsigned char emptyTextSlots_repeat97[16];
    unsigned char emptyTextSlots_repeat98[16];
    unsigned char emptyTextSlots_repeat99[12];
    unsigned char emptyTextSlots_repeat100[20];
    unsigned char emptyTextSlots_repeat101[16];
    unsigned char emptyTextSlots_repeat102[24];
    unsigned char emptyTextSlots_repeat103[16];
    unsigned char emptyTextSlots_repeat104[20];
    unsigned char emptyTextSlots_repeat105[28];
    unsigned char emptyTextSlots_repeat106[20];
    unsigned char emptyTextSlots_repeat107[20];
    unsigned char emptyTextSlots_repeat108[20];
    unsigned char emptyTextSlots_repeat109[24];
    unsigned char emptyTextSlots_repeat110[20];
    unsigned char emptyTextSlots_repeat111[8];
    unsigned char emptyTextSlots_repeat112[8];
    unsigned char emptyTextSlots_repeat113[12];
    unsigned char emptyTextSlots_repeat114[8];
    unsigned char emptyTextSlots_repeat115[8];
    unsigned char emptyTextSlots_repeat116[8];
    unsigned char emptyTextSlots_repeat117[8];
    unsigned char emptyTextSlots_repeat118[8];
    unsigned char emptyTextSlots_repeat119[8];
    unsigned char emptyTextSlots_repeat120[12];
    unsigned char emptyTextSlots_repeat121[8];
    unsigned char emptyTextSlots_repeat122[12];
    unsigned char emptyTextSlots_repeat123[8];
    unsigned char emptyTextSlots_repeat124[8];
    unsigned char emptyTextSlots_repeat125[12];
    unsigned char emptyTextSlots_repeat126[12];
    unsigned char emptyTextSlots_repeat127[8];
    unsigned char emptyTextSlots_repeat128[8];
    unsigned char emptyTextSlots_repeat129[12];
    unsigned char emptyTextSlots_repeat130[8];
    unsigned char emptyTextSlots_repeat131[12];
    unsigned char emptyTextSlots_repeat132[32];
    unsigned char emptyTextSlots_repeat133[32];
    unsigned char emptyTextSlots_repeat134[28];
    unsigned char emptyTextSlots_repeat135[28];
    unsigned char emptyTextSlots_repeat136[28];
    unsigned char emptyTextSlots_repeat137[24];
    unsigned char emptyTextSlots_repeat138[28];
    unsigned char emptyTextSlots_repeat139[32];
    unsigned char emptyTextSlots_repeat140[20];
    unsigned char emptyTextSlots_repeat141[28];
    unsigned char emptyTextSlots_repeat142[28];
    unsigned char emptyTextSlots_repeat143[28];
    unsigned char emptyTextSlots_repeat144[24];
    unsigned char emptyTextSlots_repeat145[28];
    unsigned char emptyTextSlots_repeat146[28];
    unsigned char emptyTextSlots_repeat147[24];
    unsigned char emptyTextSlots_repeat148[28];
    unsigned char emptyTextSlots_repeat149[28];
    unsigned char emptyTextSlots_repeat150[24];
    unsigned char emptyTextSlots_repeat151[32];
    unsigned char emptyTextSlots_repeat152[28];
    unsigned char emptyTextSlots_repeat153[24];
    unsigned char emptyTextSlots_repeat154[28];
    unsigned char emptyTextSlots_repeat155[28];
    unsigned char emptyTextSlots_repeat156[24];
    unsigned char emptyTextSlots_repeat157[28];
    unsigned char emptyTextSlots_repeat158[28];
    unsigned char emptyTextSlots_repeat159[24];
    unsigned char emptyTextSlots_repeat160[24];
    unsigned char emptyTextSlots_repeat161[24];
    unsigned char emptyTextSlots_repeat162[28];
    unsigned char emptyTextSlots_repeat163[24];
    unsigned char emptyTextSlots_repeat164[32];
    unsigned char emptyTextSlots_repeat165[28];
    unsigned char emptyTextSlots_repeat166[28];
    unsigned char emptyTextSlots_repeat167[28];
    unsigned char emptyTextSlots_repeat168[32];
    unsigned char emptyTextSlots_repeat169[32];
    unsigned char emptyTextSlots_repeat170[24];
    unsigned char emptyTextSlots_repeat171[28];
    unsigned char emptyTextSlots_repeat172[16];
    unsigned char emptyTextSlots_repeat173[20];
    unsigned char emptyTextSlots_repeat174[28];
    unsigned char emptyTextSlots_repeat175[32];
    unsigned char emptyTextSlots_repeat176[28];
    unsigned char emptyTextSlots_repeat177[20];
    unsigned char emptyTextSlots_repeat178[16];
    unsigned char emptyTextSlots_repeat179[20];
    unsigned char emptyTextSlots_repeat180[20];
    unsigned char emptyTextSlots_repeat181[36];
    unsigned char emptyTextSlots_repeat182[8];
    unsigned char emptyTextSlots_repeat183[16];
    unsigned char emptyTextSlots_repeat184[8];
    unsigned char emptyTextSlots_repeat185[8];
    unsigned char emptyTextSlots_repeat186[8];
    unsigned char emptyTextSlots_repeat187[8];
    unsigned char emptyTextSlots_repeat188[8];
    unsigned char emptyTextSlots_repeat189[12];
    unsigned char emptyTextSlots_repeat190[8];
    unsigned char emptyTextSlots_repeat191[8];
    unsigned char emptyTextSlots_repeat192[8];
    unsigned char emptyTextSlots_repeat193[12];
    unsigned char emptyTextSlots_repeat194[8];
    unsigned char emptyTextSlots_repeat195[8];
    unsigned char emptyTextSlots_repeat196[8];
    unsigned char emptyTextSlots_repeat197[8];
    unsigned char emptyTextSlots_repeat198[8];
    unsigned char emptyTextSlots_repeat199[12];
    unsigned char emptyTextSlots_repeat200[8];
    unsigned char emptyTextSlots_repeat201[8];
    unsigned char emptyTextSlots_repeat202[8];
    unsigned char emptyTextSlots_repeat203[8];
    unsigned char emptyTextSlots_repeat204[8];
    unsigned char emptyTextSlots_repeat205[8];
    unsigned char emptyTextSlots_repeat206[8];
    unsigned char emptyTextSlots_repeat207[8];
    unsigned char emptyTextSlots_repeat208[12];
    unsigned char emptyTextSlots_repeat209[8];
    unsigned char emptyTextSlots_repeat210[8];
    unsigned char emptyTextSlots_repeat211[12];
    unsigned char emptyTextSlots_repeat212[12];
    unsigned char emptyTextSlots_repeat213[8];
    unsigned char emptyTextSlots_repeat214[8];
    unsigned char emptyTextSlots_repeat215[12];
    unsigned char emptyTextSlots_repeat216[8];
    unsigned char emptyTextSlots_repeat217[8];
    unsigned char emptyTextSlots_repeat218[8];
    unsigned char emptyTextSlots_repeat219[8];
    unsigned char emptyTextSlots_repeat220[8];
    unsigned char emptyTextSlots_repeat221[8];
    unsigned char emptyTextSlots_repeat222[8];
    unsigned char emptyTextSlots_repeat223[4];
    unsigned char emptyTextSlots_repeat224[8];
    unsigned char emptyTextSlots_repeat225[8];
    unsigned char emptyTextSlots_repeat226[8];
    unsigned char emptyTextSlots_repeat227[12];
    unsigned char emptyTextSlots_repeat228[8];
    unsigned char emptyTextSlots_repeat229[16];
    unsigned char emptyTextSlots_repeat230[12];
    unsigned char emptyTextSlots_repeat231[12];
    unsigned char emptyTextSlots_repeat232[16];
    unsigned char emptyTextSlots_repeat233[8];
    unsigned char emptyTextSlots_repeat234[20];
    unsigned char emptyTextSlots_repeat235[12];
    unsigned char emptyTextSlots_repeat236[12];
    unsigned char emptyTextSlots_repeat237[12];
    unsigned char emptyTextSlots_repeat238[16];
    unsigned char emptyTextSlots_repeat239[12];
    unsigned char emptyTextSlots_repeat240[8];
    unsigned char emptyTextSlots_repeat241[12];
    unsigned char emptyTextSlots_repeat242[8];
    unsigned char emptyTextSlots_repeat243[8];
    unsigned char emptyTextSlots_repeat244[16];
    unsigned char emptyTextSlots_repeat245[28];
    unsigned char emptyTextSlots_repeat246[28];
    unsigned char emptyTextSlots_repeat247[28];
    unsigned char emptyTextSlots_repeat248[24];
    unsigned char emptyTextSlots_repeat249[24];
    unsigned char emptyTextSlots_repeat250[28];
    unsigned char emptyTextSlots_repeat251[16];
    unsigned char emptyTextSlots_repeat252[20];
    unsigned char emptyTextSlots_repeat253[24];
    unsigned char emptyTextSlots_repeat254[24];
    unsigned char emptyTextSlots_repeat255[24];
    unsigned char emptyTextSlots_repeat256[40];
    unsigned char emptyTextSlots_repeat257[40];
    unsigned char emptyTextSlots_repeat258[24];
    unsigned char emptyTextSlots_repeat259[24];
    unsigned char emptyTextSlots_repeat260[16];
    unsigned char emptyTextSlots_repeat261[16];
    unsigned char emptyTextSlots_repeat262[12];
    unsigned char emptyTextSlots_repeat263[24];
    unsigned char emptyTextSlots_repeat264[28];
    unsigned char emptyTextSlots_repeat265[8];
    unsigned char emptyTextSlots_repeat266[8];
    unsigned char emptyTextSlots_repeat267[8];
    unsigned char emptyTextSlots_repeat268[4];
    unsigned char emptyTextSlots_repeat269[4];
    unsigned char emptyTextSlots_repeat270[4];
    unsigned char emptyTextSlots_repeat271[8];
    unsigned char emptyTextSlots_repeat272[12];
    unsigned char emptyTextSlots_repeat273[12];
    unsigned char emptyTextSlots_repeat274[8];
    unsigned char emptyTextSlots_repeat275[8];
    unsigned char emptyTextSlots_repeat276[12];
    unsigned char emptyTextSlots_repeat277[4];
    unsigned char emptyTextSlots_repeat278[4];
    unsigned char emptyTextSlots_repeat279[8];
    unsigned char emptyTextSlots_repeat280[8];
    unsigned char emptyTextSlots_repeat281[8];
    unsigned char emptyTextSlots_repeat282[8];
    unsigned char emptyTextSlots_repeat283[8];
    unsigned char emptyTextSlots_repeat284[8];
    unsigned char emptyTextSlots_repeat285[8];
    unsigned char emptyTextSlots_repeat286[4];
    unsigned char emptyTextSlots_repeat287[8];
    unsigned char emptyTextSlots_repeat288[16];
    unsigned char emptyTextSlots_repeat289[4];
    unsigned char emptyTextSlots_repeat290[4];
    unsigned char emptyTextSlots_repeat291[4];
    unsigned char emptyTextSlots_repeat292[4];
    unsigned char emptyTextSlots_repeat293[12];
    unsigned char emptyTextSlots_repeat294[12];
    unsigned char emptyTextSlots_repeat295[12];
    unsigned char emptyTextSlots_repeat296[12];
    unsigned char emptyTextSlots_repeat297[32];
    unsigned char emptyTextSlots_repeat298[52];
    unsigned char emptyTextSlots_repeat299[48];
    unsigned char emptyTextSlots_repeat300[44];
    unsigned char emptyTextSlots_repeat301[44];
    unsigned char emptyTextSlots_repeat302[44];
    unsigned char emptyTextSlots_repeat303[44];
    unsigned char emptyTextSlots_repeat304[32];
    unsigned char emptyTextSlots_repeat305[24];
    unsigned char emptyTextSlots_repeat306[24];
    unsigned char emptyTextSlots_repeat307[44];
    unsigned char emptyTextSlots_repeat308[36];
    unsigned char emptyTextSlots_repeat309[28];
    unsigned char emptyTextSlots_repeat310[36];
    unsigned char emptyTextSlots_repeat311[24];
    unsigned char emptyTextSlots_repeat312[28];
    unsigned char emptyTextSlots_repeat313[28];
    unsigned char emptyTextSlots_repeat314[28];
    unsigned char emptyTextSlots_repeat315[32];
    unsigned char emptyTextSlots_repeat316[40];
    unsigned char emptyTextSlots_repeat317[28];
    unsigned char emptyTextSlots_repeat318[44];
    unsigned char emptyTextSlots_repeat319[20];
    unsigned char emptyTextSlots_repeat320[28];
    unsigned char emptyTextSlots_repeat321[20];
    unsigned char emptyTextSlots_repeat322[36];
    unsigned char emptyTextSlots_repeat323[24];
    unsigned char emptyTextSlots_repeat324[20];
    unsigned char emptyTextSlots_repeat325[28];
    unsigned char emptyTextSlots_repeat326[20];
    unsigned char emptyTextSlots_repeat327[28];
    unsigned char emptyTextSlots_repeat328[20];
    unsigned char emptyTextSlots_repeat329[44];
    unsigned char emptyTextSlots_repeat330[40];
    unsigned char emptyTextSlots_repeat331[20];
    unsigned char emptyTextSlots_repeat332[28];
    unsigned char emptyTextSlots_repeat333[36];
    unsigned char emptyTextSlots_repeat334[24];
    unsigned char emptyTextSlots_repeat335[16];
    unsigned char emptyTextSlots_repeat336[28];
    unsigned char emptyTextSlots_repeat337[8];
    unsigned char emptyTextSlots_repeat338[8];
    unsigned char emptyTextSlots_repeat339[8];
    unsigned char emptyTextSlots_repeat340[8];
    unsigned char emptyTextSlots_repeat341[48];
    unsigned char emptyTextSlots_repeat342[48];
    unsigned char emptyTextSlots_repeat343[8];
    unsigned char emptyTextSlots_repeat344[24];
    unsigned char emptyTextSlots_repeat345[24];
    unsigned char emptyTextSlots_repeat346[24];
    unsigned char emptyTextSlots_repeat347[24];
    unsigned char emptyTextSlots_repeat348[24];
    unsigned char emptyTextSlots_repeat349[24];
    unsigned char emptyTextSlots_repeat350[24];
    unsigned char emptyTextSlots_repeat351[24];
    unsigned char emptyTextSlots_repeat352[24];
    unsigned char emptyTextSlots_repeat353[24];
    unsigned char emptyTextSlots_repeat354[24];
    unsigned char emptyTextSlots_repeat355[24];
    unsigned char emptyTextSlots_repeat356[24];
    unsigned char emptyTextSlots_repeat357[24];
    unsigned char emptyTextSlots_repeat358[24];
    unsigned char emptyTextSlots_repeat359[24];
    unsigned char emptyTextSlots_repeat360[24];
    unsigned char emptyTextSlots_repeat361[24];
    unsigned char emptyTextSlots_repeat362[24];
    unsigned char emptyTextSlots_repeat363[24];
    unsigned char emptyTextSlots_repeat364[24];
    unsigned char emptyTextSlots_repeat365[24];
    unsigned char emptyTextSlots_repeat366[24];
    unsigned char emptyTextSlots_repeat367[24];
    unsigned char emptyTextSlots_repeat368[24];
    unsigned char emptyTextSlots_repeat369[24];
    unsigned char emptyTextSlots_repeat370[24];
    unsigned char emptyTextSlots_repeat371[24];
    unsigned char emptyTextSlots_repeat372[24];
    unsigned char emptyTextSlots_repeat373[24];
    unsigned char emptyTextSlots_repeat374[24];
    unsigned char emptyTextSlots_repeat375[24];
    unsigned char emptyTextSlots_repeat376[24];
    unsigned char emptyTextSlots_repeat377[24];
    unsigned char emptyTextSlots_repeat378[24];
    unsigned char emptyTextSlots_repeat379[24];
    unsigned char emptyTextSlots_repeat380[8];
    unsigned char emptyTextSlots_repeat381[4];
    unsigned char emptyTextSlots_repeat382[4];
    unsigned char emptyTextSlots_repeat383[4];
    unsigned char emptyTextSlots_repeat384[4];
    unsigned char emptyTextSlots_repeat385[4];
    unsigned char emptyTextSlots_repeat386[4];
    unsigned char emptyTextSlots_repeat387[4];
    unsigned char emptyTextSlots_repeat388[4];
    unsigned char emptyTextSlots_repeat389[4];
    unsigned char emptyTextSlots_repeat390[4];
    unsigned char emptyTextSlots_repeat391[4];
    unsigned char emptyTextSlots_repeat392[4];
    unsigned char emptyTextSlots_repeat393[4];
    unsigned char emptyTextSlots_repeat394[4];
    unsigned char emptyTextSlots_repeat395[4];
    unsigned char emptyTextSlots_repeat396[4];
    unsigned char emptyTextSlots_repeat397[4];
    unsigned char emptyTextSlots_repeat398[4];
    unsigned char emptyTextSlots_repeat399[4];
    unsigned char emptyTextSlots_repeat400[4];
    unsigned char emptyTextSlots_repeat401[4];
    unsigned char emptyTextSlots_repeat402[4];
    unsigned char emptyTextSlots_repeat403[8];
    unsigned char emptyTextSlots_repeat404[12];
    unsigned char emptyTextSlots_repeat405[12];
    unsigned char emptyTextSlots_repeat406[12];
    unsigned char emptyTextSlots_repeat407[24];
    unsigned char emptyTextSlots_repeat408[24];
    unsigned char emptyTextSlots_repeat409[20];
    unsigned char emptyTextSlots_repeat410[8];
    unsigned char emptyTextSlots_repeat411[12];
    unsigned char emptyTextSlots_repeat412[16];
    unsigned char emptyTextSlots_repeat413[20];
    unsigned char emptyTextSlots_repeat414[12];
    unsigned char emptyTextSlots_repeat415[8];
    unsigned char emptyTextSlots_repeat416[8];
    unsigned char emptyTextSlots_repeat417[8];
    unsigned char emptyTextSlots_repeat418[8];
    unsigned char emptyTextSlots_repeat419[12];
    unsigned char emptyTextSlots_repeat420[4];
    unsigned char emptyTextSlots_repeat421[12];
    unsigned char emptyTextSlots_repeat422[8];
    unsigned char emptyTextSlots_repeat423[4];
    unsigned char emptyTextSlots_repeat424[8];
    unsigned char emptyTextSlots_repeat425[4];
    unsigned char emptyTextSlots_repeat426[4];
    unsigned char emptyTextSlots_repeat427[4];
    unsigned char emptyTextSlots_repeat428[4];
    unsigned char emptyTextSlots_repeat429[4];
    unsigned char emptyTextSlots_repeat430[4];
    unsigned char emptyTextSlots_repeat431[4];
    unsigned char emptyTextSlots_repeat432[4];
    unsigned char emptyTextSlots_repeat433[4];
    unsigned char emptyTextSlots_repeat434[4];
    unsigned char emptyTextSlots_repeat435[4];
    unsigned char emptyTextSlots_repeat436[4];
    unsigned char emptyTextSlots_repeat437[4];
    unsigned char emptyTextSlots_repeat438[4];
    unsigned char emptyTextSlots_repeat439[4];
    unsigned char emptyTextSlots_repeat440[4];
    unsigned char emptyTextSlots_repeat441[4];
    unsigned char emptyTextSlots_repeat442[4];
    unsigned char emptyTextSlots_repeat443[4];
    unsigned char emptyTextSlots_repeat444[4];
    unsigned char emptyTextSlots_repeat445[4];
    unsigned char emptyTextSlots_repeat446[4];
    unsigned char emptyTextSlots_repeat447[4];
    unsigned char emptyTextSlots_repeat448[4];
    unsigned char emptyTextSlots_repeat449[4];
    unsigned char emptyTextSlots_repeat450[4];
    unsigned char emptyTextSlots_repeat451[4];
    unsigned char emptyTextSlots_repeat452[4];
    unsigned char emptyTextSlots_repeat453[4];
    unsigned char emptyTextSlots_repeat454[4];
    unsigned char emptyTextSlots_repeat455[12];
    unsigned char emptyTextSlots_repeat456[4];
    unsigned char emptyTextSlots_repeat457[4];
    unsigned char emptyTextSlots_repeat458[4];
    unsigned char emptyTextSlots_repeat459[4];
    unsigned char emptyTextSlots_repeat460[4];
    unsigned char emptyTextSlots_repeat461[4];
    unsigned char emptyTextSlots_repeat462[4];
    unsigned char emptyTextSlots_repeat463[4];
    unsigned char emptyTextSlots_repeat464[4];
    unsigned char emptyTextSlots_repeat465[4];
    unsigned char emptyTextSlots_repeat466[4];
    unsigned char emptyTextSlots_repeat467[4];
    unsigned char emptyTextSlots_repeat468[4];
    unsigned char emptyTextSlots_repeat469[4];
    unsigned char emptyTextSlots_repeat470[4];
    unsigned char emptyTextSlots_repeat471[4];
    unsigned char emptyTextSlots_repeat472[12];
    unsigned char emptyTextSlots_repeat473[12];
    unsigned char emptyTextSlots_repeat474[20];
    unsigned char emptyTextSlots_repeat475[20];
    unsigned char emptyTextSlots_repeat476[20];
    unsigned char emptyTextSlots_repeat477[20];
    unsigned char emptyTextSlots_repeat478[20];
    unsigned char emptyTextSlots_repeat479[16];
    unsigned char emptyTextSlots_repeat480[12];
    unsigned char emptyTextSlots_repeat481[12];
    unsigned char emptyTextSlots_repeat482[12];
    unsigned char emptyTextSlots_repeat483[24];
    unsigned char emptyTextSlots_repeat484[24];
    unsigned char emptyTextSlots_repeat485[20];
    unsigned char emptyTextSlots_repeat486[20];
    unsigned char emptyTextSlots_repeat487[20];
    unsigned char emptyTextSlots_repeat488[20];
    unsigned char emptyTextSlots_repeat489[8];
    unsigned char emptyTextSlots_repeat490[8];
    unsigned char emptyTextSlots_repeat491[8];
    unsigned char emptyTextSlots_repeat492[8];
    unsigned char emptyTextSlots_repeat493[12];
    unsigned char emptyTextSlots_repeat494[4];
    unsigned char emptyTextSlots_repeat495[4];
    unsigned char emptyTextSlots_repeat496[4];
    unsigned char emptyTextSlots_repeat497[4];
    unsigned char emptyTextSlots_repeat498[4];
    unsigned char emptyTextSlots_repeat499[4];
    unsigned char emptyTextSlots_repeat500[4];
    unsigned char emptyTextSlots_repeat501[4];
    unsigned char emptyTextSlots_repeat502[4];
    unsigned char emptyTextSlots_repeat503[4];
    unsigned char emptyTextSlots_repeat504[4];
    unsigned char emptyTextSlots_repeat505[4];
    unsigned char emptyTextSlots_repeat506[4];
    unsigned char emptyTextSlots_repeat507[4];
    unsigned char emptyTextSlots_repeat508[4];
    unsigned char emptyTextSlots_repeat509[4];
    unsigned char emptyTextSlots_repeat510[4];
    unsigned char emptyTextSlots_repeat511[4];
    unsigned char emptyTextSlots_repeat512[4];
    unsigned char emptyTextSlots_repeat513[4];
    unsigned char emptyTextSlots_repeat514[4];
    unsigned char emptyTextSlots_repeat515[4];
    unsigned char emptyTextSlots_repeat516[4];
    unsigned char emptyTextSlots_repeat517[4];
    unsigned char emptyTextSlots_repeat518[4];
    unsigned char emptyTextSlots_repeat519[4];
    unsigned char emptyTextSlots_repeat520[4];
    unsigned char emptyTextSlots_repeat521[4];
    unsigned char emptyTextSlots_repeat522[4];
    unsigned char emptyTextSlots_repeat523[4];
    unsigned char emptyTextSlots_repeat524[4];
    unsigned char emptyTextSlots_repeat525[4];
    unsigned char emptyTextSlots_repeat526[4];
    unsigned char emptyTextSlots_repeat527[4];
    unsigned char emptyTextSlots_repeat528[4];
    unsigned char emptyTextSlots_repeat529[4];
    unsigned char emptyTextSlots_repeat530[4];
    unsigned char emptyTextSlots_repeat531[4];
    unsigned char emptyTextSlots_repeat532[4];
    unsigned char emptyTextSlots_repeat533[4];
    unsigned char emptyTextSlots_repeat534[4];
    unsigned char emptyTextSlots_repeat535[4];
    unsigned char emptyTextSlots_repeat536[4];
    unsigned char emptyTextSlots_repeat537[4];
    unsigned char emptyTextSlots_repeat538[4];
    unsigned char emptyTextSlots_repeat539[4];
    unsigned char emptyTextSlots_repeat540[4];
    unsigned char emptyTextSlots_repeat541[4];
    unsigned char emptyTextSlots_repeat542[4];
    unsigned char emptyTextSlots_repeat543[4];
    unsigned char emptyTextSlots_repeat544[4];
    unsigned char emptyTextSlots_repeat545[4];
    unsigned char emptyTextSlots_repeat546[4];
    unsigned char emptyTextSlots_repeat547[4];
    unsigned char emptyTextSlots_repeat548[4];
    unsigned char emptyTextSlots_repeat549[4];
    unsigned char emptyTextSlots_repeat550[4];
    unsigned char emptyTextSlots_repeat551[4];
    unsigned char emptyTextSlots_repeat552[4];
    unsigned char emptyTextSlots_repeat553[4];
    unsigned char emptyTextSlots_repeat554[4];
    unsigned char emptyTextSlots_repeat555[4];
    unsigned char emptyTextSlots_repeat556[4];
    unsigned char emptyTextSlots_repeat557[4];
    unsigned char emptyTextSlots_repeat558[4];
    unsigned char emptyTextSlots_repeat559[4];
    unsigned char emptyTextSlots_repeat560[4];
    unsigned char emptyTextSlots_repeat561[4];
    unsigned char emptyTextSlots_repeat562[4];
    unsigned char emptyTextSlots_repeat563[4];
    unsigned char emptyTextSlots_repeat564[4];
    unsigned char emptyTextSlots_repeat565[4];
    unsigned char emptyTextSlots_repeat566[4];
    unsigned char emptyTextSlots_repeat567[4];
    unsigned char emptyTextSlots_repeat568[4];
    unsigned char emptyTextSlots_repeat569[4];
    unsigned char emptyTextSlots_repeat570[4];
    unsigned char emptyTextSlots_repeat571[4];
    unsigned char emptyTextSlots_repeat572[4];
    unsigned char emptyTextSlots_repeat573[4];
    unsigned char emptyTextSlots_repeat574[4];
    unsigned char emptyTextSlots_repeat575[4];
    unsigned char emptyTextSlots_repeat576[4];
    unsigned char emptyTextSlots_repeat577[4];
    unsigned char emptyTextSlots_repeat578[4];
    unsigned char emptyTextSlots_repeat579[4];
    unsigned char emptyTextSlots_repeat580[4];
    unsigned char emptyTextSlots_repeat581[4];
    unsigned char emptyTextSlots_repeat582[4];
    unsigned char emptyTextSlots_repeat583[4];
    unsigned char emptyTextSlots_repeat584[4];
    unsigned char emptyTextSlots_repeat585[4];
    unsigned char emptyTextSlots_repeat586[4];
    unsigned char emptyTextSlots_repeat587[4];
    unsigned char emptyTextSlots_repeat588[4];
    unsigned char emptyTextSlots_repeat589[4];
    unsigned char emptyTextSlots_repeat590[4];
    unsigned char emptyTextSlots_repeat591[4];
    unsigned char emptyTextSlots_repeat592[4];
    unsigned char emptyTextSlots_repeat593[4];
    unsigned char emptyTextSlots_repeat594[4];
    unsigned char emptyTextSlots_repeat595[4];
    unsigned char emptyTextSlots_repeat596[4];
    unsigned char emptyTextSlots_repeat597[4];
    unsigned char emptyTextSlots_repeat598[4];
    unsigned char emptyTextSlots_repeat599[4];
    unsigned char emptyTextSlots_repeat600[4];
    unsigned char emptyTextSlots_repeat601[4];
    unsigned char emptyTextSlots_repeat602[4];
    unsigned char emptyTextSlots_repeat603[4];
    unsigned char emptyTextSlots_repeat604[4];
    unsigned char emptyTextSlots_repeat605[4];
    unsigned char emptyTextSlots_repeat606[4];
    unsigned char emptyTextSlots_repeat607[4];
    unsigned char emptyTextSlots_repeat608[4];
    unsigned char emptyTextSlots_repeat609[4];
    unsigned char emptyTextSlots_repeat610[4];
    unsigned char emptyTextSlots_repeat611[4];
    unsigned char emptyTextSlots_repeat612[4];
    unsigned char emptyTextSlots_repeat613[4];
    unsigned char emptyTextSlots_repeat614[4];
    unsigned char emptyTextSlots_repeat615[4];
    unsigned char emptyTextSlots_repeat616[4];
    unsigned char emptyTextSlots_repeat617[8];
    unsigned char emptyTextSlots_repeat618[8];
    unsigned char emptyTextSlots_repeat619[8];
    unsigned char emptyTextSlots_repeat620[8];
    unsigned char emptyTextSlots_repeat621[8];
    unsigned char emptyTextSlots_repeat622[4];
    unsigned char emptyTextSlots_repeat623[4];
    unsigned char emptyTextSlots_repeat624[4];
    unsigned char emptyTextSlots_repeat625[4];
    unsigned char emptyTextSlots_repeat626[4];
    unsigned char emptyTextSlots_repeat627[4];
    unsigned char emptyTextSlots_repeat628[4];
    unsigned char emptyTextSlots_repeat629[4];
    unsigned char emptyTextSlots_repeat630[4];
    unsigned char emptyTextSlots_repeat631[4];
    unsigned char emptyTextSlots_repeat632[12];
    unsigned char emptyTextSlots_repeat633[12];
    unsigned char emptyTextSlots_repeat634[12];
    unsigned char emptyTextSlots_repeat635[12];
    unsigned char emptyTextSlots_repeat636[4];
    unsigned int controlCodeTexts[4];
    unsigned char emptyTextSlots_repeat637[12];
    unsigned char emptyTextSlots_repeat638[12];
    unsigned char emptyTextSlots_repeat639[12];
    unsigned char emptyTextSlots_repeat640[12];
    unsigned char emptyTextSlots_repeat641[20];
    unsigned char emptyTextSlots_repeat642[24];
    unsigned char emptyTextSlots_repeat643[24];
    unsigned char emptyTextSlots_repeat644[16];
    unsigned char emptyTextSlots_repeat645[12];
    unsigned char emptyTextSlots_repeat646[4];
    unsigned char emptyTextSlots_repeat647[4];
    unsigned char emptyTextSlots_repeat648[8];
    unsigned char emptyTextSlots_repeat649[8];
    unsigned char emptyTextSlots_repeat650[8];
    unsigned char emptyTextSlots_repeat651[12];
    unsigned char emptyTextSlots_repeat652[12];
    unsigned char emptyTextSlots_repeat653[12];
    unsigned char emptyTextSlots_repeat654[12];
    unsigned char emptyTextSlots_repeat655[8];
    unsigned char emptyTextSlots_repeat656[12];
    unsigned char emptyTextSlots_repeat657[12];
    unsigned char emptyTextSlots_repeat658[12];
    unsigned char emptyTextSlots_repeat659[8];
    unsigned char emptyTextSlots_repeat660[20];
    unsigned char emptyTextSlots_repeat661[24];
    unsigned char emptyTextSlots_repeat662[28];
    unsigned char emptyTextSlots_repeat663[24];
    unsigned char emptyTextSlots_repeat664[28];
    unsigned char emptyTextSlots_repeat665[20];
    unsigned char emptyTextSlots_repeat666[24];
    unsigned char emptyTextSlots_repeat667[20];
    unsigned char emptyTextSlots_repeat668[24];
    unsigned char emptyTextSlots_repeat669[36];
    unsigned char emptyTextSlots_repeat670[28];
    unsigned char emptyTextSlots_repeat671[24];
    unsigned char emptyTextSlots_repeat672[24];
    unsigned char emptyTextSlots_repeat673[28];
    unsigned char emptyTextSlots_repeat674[20];
    unsigned char emptyTextSlots_repeat675[24];
    unsigned char emptyTextSlots_repeat676[32];
    unsigned char emptyTextSlots_repeat677[24];
    unsigned char emptyTextSlots_repeat678[24];
    unsigned char emptyTextSlots_repeat679[24];
    unsigned char emptyTextSlots_repeat680[24];
    unsigned char emptyTextSlots_repeat681[24];
    unsigned char emptyTextSlots_repeat682[24];
    unsigned char emptyTextSlots_repeat683[28];
    unsigned char emptyTextSlots_repeat684[32];
    unsigned char emptyTextSlots_repeat685[28];
    unsigned char emptyTextSlots_repeat686[32];
    unsigned char emptyTextSlots_repeat687[24];
    unsigned char emptyTextSlots_repeat688[28];
    unsigned char emptyTextSlots_repeat689[28];
    unsigned char emptyTextSlots_repeat690[28];
    unsigned char emptyTextSlots_repeat691[28];
    unsigned char emptyTextSlots_repeat692[28];
    unsigned char emptyTextSlots_repeat693[28];
    unsigned char emptyTextSlots_repeat694[28];
    unsigned char emptyTextSlots_repeat695[28];
    unsigned char emptyTextSlots_repeat696[28];
    unsigned char emptyTextSlots_repeat697[28];
    unsigned char emptyTextSlots_repeat698[28];
    unsigned char emptyTextSlots_repeat699[28];
    unsigned char emptyTextSlots_repeat700[28];
    unsigned char emptyTextSlots_repeat701[28];
    unsigned char emptyTextSlots_repeat702[28];
    unsigned char emptyTextSlots_repeat703[28];
    unsigned char emptyTextSlots_repeat704[28];
    unsigned char emptyTextSlots_repeat705[28];
    unsigned char emptyTextSlots_repeat706[28];
    unsigned char emptyTextSlots_repeat707[28];
    unsigned char emptyTextSlots_repeat708[28];
    unsigned char emptyTextSlots_repeat709[28];
    unsigned char emptyTextSlots_repeat710[28];
    unsigned char emptyTextSlots_repeat711[28];
    unsigned char emptyTextSlots_repeat712[28];
    unsigned char emptyTextSlots_repeat713[28];
    unsigned char emptyTextSlots_repeat714[28];
    unsigned char emptyTextSlots_repeat715[28];
    unsigned char emptyTextSlots_repeat716[28];
    unsigned char emptyTextSlots_repeat717[28];
    unsigned char emptyTextSlots_repeat718[28];
    unsigned char emptyTextSlots_repeat719[28];
    unsigned char emptyTextSlots_repeat720[28];
    unsigned char emptyTextSlots_repeat721[28];
    unsigned char emptyTextSlots_repeat722[28];
    unsigned char emptyTextSlots_repeat723[28];
    unsigned char emptyTextSlots_repeat724[28];
    unsigned char emptyTextSlots_repeat725[28];
    unsigned char emptyTextSlots_repeat726[28];
    unsigned char emptyTextSlots_repeat727[28];
    unsigned char emptyTextSlots_repeat728[28];
    unsigned char emptyTextSlots_repeat729[28];
    unsigned char emptyTextSlots_repeat730[28];
    unsigned char emptyTextSlots_repeat731[12];
    unsigned char emptyTextSlots_repeat732[12];
    unsigned char emptyTextSlots_repeat733[8];
    unsigned char emptyTextSlots_repeat734[32];
    unsigned char emptyTextSlots_repeat735[32];
    unsigned char emptyTextSlots_repeat736[32];
    unsigned char emptyTextSlots_repeat737[32];
    unsigned char emptyTextSlots_repeat738[32];
    unsigned char emptyTextSlots_repeat739[32];
    unsigned char emptyTextSlots_repeat740[32];
    unsigned char emptyTextSlots_repeat741[16];
    unsigned char emptyTextSlots_repeat742[32];
    unsigned char emptyTextSlots_repeat743[32];
    unsigned char emptyTextSlots_repeat744[32];
    unsigned char emptyTextSlots_repeat745[32];
    unsigned char emptyTextSlots_repeat746[16];
    unsigned char emptyTextSlots_repeat747[16];
    unsigned char emptyTextSlots_repeat748[16];
    unsigned char emptyTextSlots_repeat749[16];
    unsigned char emptyTextSlots_repeat750[32];
    unsigned char emptyTextSlots_repeat751[32];
    unsigned char emptyTextSlots_repeat752[32];
    unsigned char emptyTextSlots_repeat753[32];
    unsigned char emptyTextSlots_repeat754[16];
    unsigned char emptyTextSlots_repeat755[16];
    unsigned char emptyTextSlots_repeat756[16];
    unsigned char emptyTextSlots_repeat757[16];
    unsigned char emptyTextSlots_repeat758[32];
    unsigned char emptyTextSlots_repeat759[32];
    unsigned char emptyTextSlots_repeat760[32];
    unsigned char emptyTextSlots_repeat761[32];
    unsigned char emptyTextSlots_repeat762[16];
    unsigned char emptyTextSlots_repeat763[16];
    unsigned char emptyTextSlots_repeat764[16];
    unsigned char emptyTextSlots_repeat765[16];
    unsigned char emptyTextSlots_repeat766[12];
    unsigned char emptyTextSlots_repeat767[12];
    unsigned char emptyTextSlots_repeat768[12];
    unsigned char emptyTextSlots_repeat769[12];
    unsigned char emptyTextSlots_repeat770[8];
    unsigned char emptyTextSlots_repeat771[12];
    unsigned char emptyTextSlots_repeat772[8];
    unsigned char emptyTextSlots_repeat773[8];
    unsigned char emptyTextSlots_repeat774[12];
    unsigned char emptyTextSlots_repeat775[20];
    unsigned char emptyTextSlots_repeat776[12];
    unsigned char emptyTextSlots_repeat777[12];
    unsigned char emptyTextSlots_repeat778[24];
    unsigned char emptyTextSlots_repeat779[24];
    unsigned char emptyTextSlots_repeat780[24];
    unsigned char emptyTextSlots_repeat781[24];
    unsigned char emptyTextSlots_repeat782[24];
    unsigned char emptyTextSlots_repeat783[24];
    unsigned char emptyTextSlots_repeat784[24];
    unsigned char emptyTextSlots_repeat785[24];
    unsigned char emptyTextSlots_repeat786[24];
    unsigned char emptyTextSlots_repeat787[24];
    unsigned char emptyTextSlots_repeat788[24];
    unsigned char emptyTextSlots_repeat789[24];
    unsigned char emptyTextSlots_repeat790[24];
    unsigned char emptyTextSlots_repeat791[24];
    unsigned char emptyTextSlots_repeat792[24];
    unsigned char emptyTextSlots_repeat793[24];
    unsigned char emptyTextSlots_repeat794[24];
    unsigned char emptyTextSlots_repeat795[24];
    unsigned char emptyTextSlots_repeat796[24];
    unsigned char emptyTextSlots_repeat797[24];
    unsigned char emptyTextSlots_repeat798[24];
    unsigned char emptyTextSlots_repeat799[24];
    unsigned char emptyTextSlots_repeat800[24];
    unsigned char emptyTextSlots_repeat801[24];
    unsigned char emptyTextSlots_repeat802[24];
    unsigned char emptyTextSlots_repeat803[24];
    unsigned char emptyTextSlots_repeat804[24];
    unsigned char emptyTextSlots_repeat805[12];
    unsigned char emptyTextSlots_repeat806[8];
    unsigned char emptyTextSlots_repeat807[12];
    unsigned char emptyTextSlots_repeat808[12];
    unsigned char emptyTextSlots_repeat809[24];
    unsigned char emptyTextSlots_repeat810[24];
    unsigned char emptyTextSlots_repeat811[24];
    unsigned char emptyTextSlots_repeat812[24];
    unsigned char emptyTextSlots_repeat813[24];
    unsigned char emptyTextSlots_repeat814[24];
    unsigned char emptyTextSlots_repeat815[24];
    unsigned char emptyTextSlots_repeat816[12];
    unsigned char emptyTextSlots_repeat817[20];
    unsigned char emptyTextSlots_repeat818[24];
    unsigned char emptyTextSlots_repeat819[24];
    unsigned char emptyTextSlots_repeat820[24];
    unsigned char emptyTextSlots_repeat821[24];
    unsigned char emptyTextSlots_repeat822[24];
    unsigned char emptyTextSlots_repeat823[24];
    unsigned char emptyTextSlots_repeat824[24];
    unsigned char emptyTextSlots_repeat825[24];
    unsigned char emptyTextSlots_repeat826[24];
    unsigned char emptyTextSlots_repeat827[24];
    unsigned char emptyTextSlots_repeat828[24];
    unsigned char emptyTextSlots_repeat829[24];
    unsigned char emptyTextSlots_repeat830[24];
    unsigned char emptyTextSlots_repeat831[24];
    unsigned char emptyTextSlots_repeat832[24];
    unsigned char emptyTextSlots_repeat833[24];
    unsigned char emptyTextSlots_repeat834[12];
    unsigned char emptyTextSlots_repeat835[24];
    unsigned char emptyTextSlots_repeat836[24];
    unsigned char emptyTextSlots_repeat837[24];
    unsigned char emptyTextSlots_repeat838[24];
    unsigned char emptyTextSlots_repeat839[24];
    unsigned char emptyTextSlots_repeat840[12];
    unsigned char emptyTextSlots_repeat841[8];
    unsigned char emptyTextSlots_repeat842[8];
    unsigned char emptyTextSlots_repeat843[8];
    unsigned char emptyTextSlots_repeat844[8];
    unsigned char emptyTextSlots_repeat845[12];
    unsigned char emptyTextSlots_repeat846[12];
    unsigned char emptyTextSlots_repeat847[16];
    unsigned char emptyTextSlots_repeat848[24];
    unsigned char emptyTextSlots_repeat849[24];
    unsigned char emptyTextSlots_repeat850[24];
    unsigned char emptyTextSlots_repeat851[24];
    unsigned char emptyTextSlots_repeat852[24];
    unsigned char emptyTextSlots_repeat853[24];
    unsigned char emptyTextSlots_repeat854[24];
    unsigned char emptyTextSlots_repeat855[24];
    unsigned char emptyTextSlots_repeat856[24];
    unsigned char emptyTextSlots_repeat857[24];
    unsigned char emptyTextSlots_repeat858[24];
    unsigned char emptyTextSlots_repeat859[24];
    unsigned char emptyTextSlots_repeat860[24];
    unsigned char emptyTextSlots_repeat861[24];
    unsigned char emptyTextSlots_repeat862[24];
    unsigned char emptyTextSlots_repeat863[24];
    unsigned char emptyTextSlots_repeat864[20];
    unsigned char emptyTextSlots_repeat865[16];
    unsigned char emptyTextSlots_repeat866[20];
    unsigned char emptyTextSlots_repeat867[24];
    unsigned char emptyTextSlots_repeat868[24];
    unsigned char emptyTextSlots_repeat869[8];
    unsigned char emptyTextSlots_repeat870[12];
    unsigned char emptyTextSlots_repeat871[4];
    unsigned char emptyTextSlots_repeat872[4];
    unsigned char emptyTextSlots_repeat873[4];
    unsigned char emptyTextSlots_repeat874[4];
    unsigned char emptyTextSlots_repeat875[4];
    unsigned char emptyTextSlots_repeat876[4];
    unsigned char emptyTextSlots_repeat877[4];
    unsigned char emptyTextSlots_repeat878[4];
    unsigned char emptyTextSlots_repeat879[4];
    unsigned char emptyTextSlots_repeat880[4];
    unsigned char emptyTextSlots_repeat881[4];
    unsigned int creditsNameLinks[265];
    unsigned char emptyTextSlots_repeat882[2472];
    unsigned int textSoeurWords[2];
    unsigned char emptyTextSlots_repeat883[36];
    unsigned int textOeurs;
    unsigned char emptyTextSlots_repeat884[172];
    unsigned int controllerPakTextLinks[11];
    unsigned char emptyTextSlots_repeat885[16];
    unsigned int textEAcute;
    unsigned char emptyTextSlots_repeat886[20];
    unsigned char emptyTextSlots_repeat887[20];
    unsigned char emptyTextSlots_repeat888[20];
    unsigned char emptyTextSlots_repeat889[20];
    unsigned char emptyTextSlots_repeat890[16];
    unsigned char emptyTextSlots_repeat891[24];
    unsigned char emptyTextSlots_repeat892[24];
    unsigned char emptyTextSlots_repeat893[28];
    unsigned char emptyTextSlots_repeat894[12];
    unsigned int textEAcuteCopy;
    unsigned char emptyTextSlots_repeat895[16];
    unsigned char emptyTextSlots_repeat896[16];
    unsigned char emptyTextSlots_repeat897[24];
    unsigned char emptyTextSlots_repeat898[416];
    unsigned char emptyTextSlots_repeat899[16];
    unsigned int textOeil;
    unsigned char emptyTextSlots_repeat900[16];
    unsigned char emptyTextSlots_repeat901[16];
    unsigned char emptyTextSlots_repeat902[16];
    unsigned int textCoeur;
    unsigned char emptyTextSlots_repeat903[8];
    unsigned char emptyTextSlots_repeat904[20];
    unsigned char emptyTextSlots_repeat905[20];
    unsigned char emptyTextSlots_repeat906[24];
    unsigned char emptyTextSlots_repeat907[24];
    unsigned char emptyTextSlots_repeat908[20];
    unsigned char emptyTextSlots_repeat909[24];
    unsigned char emptyTextSlots_repeat910[20];
    unsigned char emptyTextSlots_repeat911[20];
    unsigned char emptyTextSlots_repeat912[16];
    unsigned char emptyTextSlots_repeat913[12];
    unsigned char emptyTextSlots_repeat914[16];
    unsigned char emptyTextSlots_repeat915[8];
    unsigned char emptyTextSlots_repeat916[8];
    unsigned char emptyTextSlots_repeat917[16];
    unsigned char emptyTextSlots_repeat918[8];
    unsigned char emptyTextSlots_repeat919[16];
    unsigned char emptyTextSlots_repeat920[16];
    unsigned char emptyTextSlots_repeat921[16];
    unsigned char emptyTextSlots_repeat922[12];
    unsigned char emptyTextSlots_repeat923[12];
    unsigned char emptyTextSlots_repeat924[12];
    unsigned char emptyTextSlots_repeat925[12];
    unsigned char emptyTextSlots_repeat926[12];
    unsigned char emptyTextSlots_repeat927[8];
    unsigned char emptyTextSlots_repeat928[20];
    unsigned char emptyTextSlots_repeat929[16];
    unsigned char emptyTextSlots_repeat930[16];
    unsigned char emptyTextSlots_repeat931[24];
    unsigned char emptyTextSlots_repeat932[12];
    unsigned char emptyTextSlots_repeat933[16];
    unsigned char emptyTextSlots_repeat934[16];
    unsigned char emptyTextSlots_repeat935[20];
    unsigned char emptyTextSlots_repeat936[16];
    unsigned char emptyTextSlots_repeat937[12];
    unsigned char emptyTextSlots_repeat938[12];
    unsigned char emptyTextSlots_repeat939[16];
    unsigned char emptyTextSlots_repeat940[24];
    unsigned char emptyTextSlots_repeat941[20];
    unsigned char emptyTextSlots_repeat942[16];
    unsigned char emptyTextSlots_repeat943[16];
    unsigned char emptyTextSlots_repeat944[24];
    unsigned char emptyTextSlots_repeat945[20];
    unsigned char emptyTextSlots_repeat946[20];
    unsigned char emptyTextSlots_repeat947[16];
    unsigned char emptyTextSlots_repeat948[28];
    unsigned char emptyTextSlots_repeat949[8];
    unsigned char emptyTextSlots_repeat950[12];
    unsigned char emptyTextSlots_repeat951[40];
    unsigned char emptyTextSlots_repeat952[8];
    unsigned char emptyTextSlots_repeat953[8];
    unsigned char emptyTextSlots_repeat954[24];
    unsigned char emptyTextSlots_repeat955[20];
    unsigned char emptyTextSlots_repeat956[16];
    unsigned char emptyTextSlots_repeat957[12];
    unsigned char emptyTextSlots_repeat958[28];
    unsigned char emptyTextSlots_repeat959[8];
    unsigned char emptyTextSlots_repeat960[8];
    unsigned char emptyTextSlots_repeat961[8];
    unsigned char emptyTextSlots_repeat962[8];
    unsigned char emptyTextSlots_repeat963[12];
    unsigned char emptyTextSlots_repeat964[12];
    unsigned char emptyTextSlots_repeat965[12];
    unsigned char emptyTextSlots_repeat966[8];
    unsigned char emptyTextSlots_repeat967[8];
    unsigned char emptyTextSlots_repeat968[12];
    unsigned char emptyTextSlots_repeat969[20];
    unsigned char emptyTextSlots_repeat970[16];
    unsigned char emptyTextSlots_repeat971[12];
    unsigned char emptyTextSlots_repeat972[16];
    unsigned char emptyTextSlots_repeat973[24];
    unsigned char emptyTextSlots_repeat974[16];
    unsigned char emptyTextSlots_repeat975[28];
    unsigned char emptyTextSlots_repeat976[16];
    unsigned char emptyTextSlots_repeat977[20];
    unsigned char emptyTextSlots_repeat978[24];
    unsigned char emptyTextSlots_repeat979[16];
    unsigned char emptyTextSlots_repeat980[24];
    unsigned char emptyTextSlots_repeat981[16];
    unsigned char emptyTextSlots_repeat982[20];
    unsigned char emptyTextSlots_repeat983[28];
    unsigned char emptyTextSlots_repeat984[4];
} k_SkyPostscaledscreenmessageEncodedWords = {
    {
        0x00000003, 0x00000000, 0x00000000, 0x00000002, 0x00000000, 0x00000003, 0x00000000, 0x00000000,
        0x00000002, 0x00000000, 0x00000003, 0x00000000, 0xFFFFFFD8, 0x00000002, 0x00000000, 0x4F4E2043,
        0x4F555254, (unsigned int)g_weaponLockedNoticeTextEuX+0xE4, 0x084B0E0C, 0xFFFF0000, 0x00120003, 0x00010000, PACKED_CALLBACK_LOW(Pickup_HandlePowerWeaponPickupEntryVariant3),
        (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[169], 0x084C0E0C, 0xFFFF0000, 0x00130004, 0x00030000, PACKED_CALLBACK_LOW(Pickup_HandlePowerWeaponPickupEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[172],
        0x084D0E0C, 0xFFFF0000, 0x00140006, 0x00010000, PACKED_CALLBACK_LOW(Pickup_HandlePowerWeaponPickupEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[178], 0x084F0E0C,
        0xFFFF0000, 0x00150005, 0x00010000, PACKED_CALLBACK_LOW(Pickup_HandlePowerWeaponPickupEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[307], 0x0BC40DB6, 0x00000000,
        0x00010064, PACKED_CALLBACK_LOW(Pickup_ApplyAmmoEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[310], 0x0BC50DB6, 0x00000000, 0x00010064,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[313], 0x0BC60DAC, 0x00000000, 0x00000032, PACKED_CALLBACK_LOW(Pickup_ApplyAmmoEntryVariant3),
        (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[316], 0x0BC70DAC, 0x00000000, 0x00000032, PACKED_CALLBACK_LOW(Pickup_ApplyAmmoEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[319], 0x0BC80DC0,
        0x00000000, 0x00020005, PACKED_CALLBACK_LOW(Pickup_ApplyAmmoEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[322], 0x0BC90DC0, 0x00000000, 0x00020005,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[19], 0x06A50001, 0x00000000, 0x00000002, 0x000000C8,
        PACKED_CALLBACK_LOW(Pickup_ApplyHealthEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[22], 0x06A60001, 0x00000000, 0x0000000A, 0x00000064,
        PACKED_CALLBACK_LOW(Pickup_ApplyHealthEntryVariant3), (unsigned int)g_backdropTextLinesByLanguage+0x54, 0x06A70001, 0x012B0000, 0x00000064, 0x00000064,
        PACKED_CALLBACK_LOW(Pickup_ApplyHealthEntryVariant3), (unsigned int)g_backdropTextLinesByLanguage+0x60, 0x06A80001, 0x012B0000, 0x00000064, 0x000000C8,
        PACKED_CALLBACK_LOW(Pickup_ApplyHealthEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[22], 0x06B80001, 0x00000000, 0x0000000A, 0x00000064,
        PACKED_CALLBACK_LOW(Pickup_ApplyHealthEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[25], 0x06B90DE8, 0x00000000, 0x0000000F, 0x00000064,
        PACKED_CALLBACK_LOW(Pickup_ApplyHealthEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[28], 0x06BA0DE8, 0x00000000, 0x00000019, 0x00000064,
        PACKED_CALLBACK_LOW(Pickup_ApplyHealthEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[31], 0x06BB0DF2, 0x00000000, 0x00000032, 0x00000064,
        PACKED_CALLBACK_LOW(Pickup_ApplyHealthEntryVariant3), 0x00000000, 0x06A90001, 0x00000000, 0x00010000, (unsigned int)g_Pickup_ApplyLifePointsEncodedCallbackEntry_eu_x,
        0x00000000, 0x06AA0001, 0x00000000, 0x000A0000, (unsigned int)g_Pickup_ApplyLifePointsEncodedCallbackEntry_eu_x, (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[94], 0x0BD60E0E,
        0x00000000, PACKED_CALLBACK_LOW(Pickup_ApplySpecialPickupEntryVariant3), (unsigned int)g_pickupFlagCarriedText, 0x0BD702C6, 0x00000000, PACKED_CALLBACK_LOW(Pickup_ApplySpecialPickupEntryVariant3),
        (unsigned int)&g_gameplayResetMessagesEuX + 0xC, 0x0BD80DCA, 0x00000000, PACKED_CALLBACK_LOW(Pickup_ApplySpecialPickupEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[46], 0x07080001, 0x012B0000,
        0x002ACB98, (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[49], 0x07090001, 0x012B0000, 0x002ACB98, (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[52], 0x070A0001, 0x012B0000,
        0x002ACB98, (unsigned int)g_backdropTextLinesByLanguage+0xA8, 0x070B0001, 0x012B0000, 0x002ACB98, (unsigned int)g_backdropTextLinesByLanguage+0xC0, 0x111C0001, 0x012B0000,
        0x002ACB98, (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[64], 0x111D0001, 0x012B0000, 0x002ACB98, (unsigned int)g_backdropTextLinesByLanguage+0xD8, 0x111E0001, 0x012B0000,
        0x002ACB98, (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[70], 0x111F0001, 0x012B0000, 0x002ACB98, (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[73], 0x11200001, 0x012B0000,
        0x002ACB98, (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[76], 0x11300001, 0x012B0000, 0x002ACB98, (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[79], 0x11310001, 0x012B0000,
        0x002ACB98, (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[82], 0x11320001, 0x012B0000, 0x002ACB98, (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[85], 0x11330001, 0x012B0000,
        0x002ACB98, (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[88], 0x11340001, 0x012B0000, 0x002ACB98, (unsigned int)g_backdropTextLinesByLanguage+0x138, 0x11940001, 0x012B0000,
        0x002ACB98, (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[58], 0x070F0001, 0x012B0000, 0x002ACB98, (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[325], 0x0BD90DFC, 0x00000000,
        0x00000000, 0x00000000, PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[325], 0x0BDA0DFC, 0x00000000, 0x00000000,
        0x00000000, PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[325], 0x0BDB0DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[325], 0x0BDC0DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[325], 0x0BDD0DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[325], 0x0BDE0DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[325], 0x0BDF0DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[325], 0x0BE00DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[325], 0x0BE10DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[325], 0x0BE20DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[325], 0x0BE30DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[325], 0x0BE40DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[325], 0x0BE50DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[325], 0x0BE60DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[325], 0x0BE70DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant3), (unsigned int)&g_GfxdataEncodedWords.screenMessageLinks[325], 0x0BE80DFC, 0x00000000, 0x00000000, 0x00000000,
        PACKED_CALLBACK_LOW(Pickup_ApplyAmmoBundleEntryVariant3), 0x6E6F6E65, 0x00000000, (unsigned int)g_pickupTrailingRodataEuX.accessingThe, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)&g_pickupTrailingRodataEuX.nDeMemcontrollerPak[8], 0x00000000,
        0x00000000, 0x00000000, (unsigned int)g_pickupTrailingRodataEuX.expansionPakFound, 0x00000000, (unsigned int)g_pickupTrailingRodataEuX.pressAnyButton, 0x00000000,
    },
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000",
    {
        0x00000000, 0x02000000, 0x03000000, 0x04000000,
    },
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    {
        (unsigned int)g_pickupTrailingRodataEuX.rageWarsTeam, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.projectManager, (unsigned int)g_pickupTrailingRodataEuX.markPacini, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.leadProgrammer, (unsigned int)g_pickupTrailingRodataEuX.franciscoJavierLafuente, (unsigned int)g_pickupTrailingRodataEuX.empty,
        (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.leadArtist, (unsigned int)g_pickupTrailingRodataEuX.michaelDaubert, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.jasonBehrDesign, (unsigned int)g_pickupTrailingRodataEuX.bruceCoonerProgramming, (unsigned int)g_pickupTrailingRodataEuX.jimCowlishawProgramming,
        (unsigned int)g_pickupTrailingRodataEuX.michaelFongDigitalProductions, (unsigned int)g_pickupTrailingRodataEuX.neillGlancyDesign, (unsigned int)g_pickupTrailingRodataEuX.michaelHueyDesign, (unsigned int)g_pickupTrailingRodataEuX.mattKyleProgramming, (unsigned int)g_pickupTrailingRodataEuX.trevorLemoineDigitalProductions, (unsigned int)g_pickupTrailingRodataEuX.marcMackinDigitalProductions, (unsigned int)g_pickupTrailingRodataEuX.bradMarquesDigitalProductions, (unsigned int)g_pickupTrailingRodataEuX.paulMastersProgramming,
        (unsigned int)g_pickupTrailingRodataEuX.robbieMillerDigitalProductions, (unsigned int)g_pickupTrailingRodataEuX.jeffSheltonDesign, (unsigned int)g_pickupTrailingRodataEuX.robertWilsherDigitalProductions, (unsigned int)g_pickupTrailingRodataEuX.robWhitakerDigitalProductions, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.additionalArt, (unsigned int)g_pickupTrailingRodataEuX.empty,
        (unsigned int)g_pickupTrailingRodataEuX.scottBrocker, (unsigned int)g_pickupTrailingRodataEuX.peterFranco, (unsigned int)g_pickupTrailingRodataEuX.alexOmlansky, (unsigned int)g_pickupTrailingRodataEuX.ryanTracy, (unsigned int)g_pickupTrailingRodataEuX.digitalImagingGroup, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.additionalProgramming,
        (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.steveBroumley, (unsigned int)g_pickupTrailingRodataEuX.stevanHird, (unsigned int)g_pickupTrailingRodataEuX.andyOneil, (unsigned int)g_pickupTrailingRodataEuX.davidSmith, (unsigned int)g_pickupTrailingRodataEuX.brianWatson, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty,
        (unsigned int)g_pickupTrailingRodataEuX.additionalDesign, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.davidDienstbier, (unsigned int)g_pickupTrailingRodataEuX.beyBickerton, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.soundDesign, (unsigned int)g_pickupTrailingRodataEuX.empty,
        (unsigned int)g_pickupTrailingRodataEuX.darrenMitchell, (unsigned int)g_pickupTrailingRodataEuX.marcSchaefgen, (unsigned int)g_pickupTrailingRodataEuX.johnHenke, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.austinQa, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.qaManager,
        (unsigned int)g_pickupTrailingRodataEuX.toddDowd, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.projectLead, (unsigned int)g_pickupTrailingRodataEuX.russBrewer, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.testers, (unsigned int)g_pickupTrailingRodataEuX.empty,
        (unsigned int)g_pickupTrailingRodataEuX.jerremyArnston, (unsigned int)g_pickupTrailingRodataEuX.chrisKendall, (unsigned int)g_pickupTrailingRodataEuX.markRichards, (unsigned int)g_pickupTrailingRodataEuX.brandonRowlett, (unsigned int)g_pickupTrailingRodataEuX.jimStrong, (unsigned int)g_pickupTrailingRodataEuX.shaneTate, (unsigned int)g_pickupTrailingRodataEuX.justinWithers, (unsigned int)g_pickupTrailingRodataEuX.empty,
        (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.characterVoices, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.travisDavisTurok, (unsigned int)g_pickupTrailingRodataEuX.bernadetteNasonAdon, (unsigned int)g_pickupTrailingRodataEuX.toddLowePurlin, (unsigned int)g_pickupTrailingRodataEuX.jessicaRobertsonSyra, (unsigned int)g_pickupTrailingRodataEuX.davidKrauseFirebornDinosoids,
        (unsigned int)g_pickupTrailingRodataEuX.davidDienstbierCampaigner, (unsigned int)g_pickupTrailingRodataEuX.joseBrownOblivionGuardian, (unsigned int)g_pickupTrailingRodataEuX.dougForrestBastille, (unsigned int)g_pickupTrailingRodataEuX.titosMenchacaTalSet, (unsigned int)g_pickupTrailingRodataEuX.marcSchaefgenLordOfTheDead, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.acclaimStudiosAustinDirectors,
        (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.gmOfAcclaimStudiosAustin, (unsigned int)g_pickupTrailingRodataEuX.russellByrd, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.technicalDirector, (unsigned int)g_pickupTrailingRodataEuX.stevenBroumley, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.directorOfProductDevelopment,
        (unsigned int)g_pickupTrailingRodataEuX.malcolmCrummack, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.creativeDirector, (unsigned int)g_pickupTrailingRodataEuX.davidDienstbier, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.audioManager, (unsigned int)g_pickupTrailingRodataEuX.darrenMitchell, (unsigned int)g_pickupTrailingRodataEuX.empty,
        (unsigned int)g_pickupTrailingRodataEuX.directorOfDigitalProductions, (unsigned int)g_pickupTrailingRodataEuX.alanJohnson, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.globalDirectors, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.vpOfProductDevelopmentAndDesign, (unsigned int)g_pickupTrailingRodataEuX.nigelCook,
        (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.vpOfDigitalProductions, (unsigned int)g_pickupTrailingRodataEuX.cyrusLum, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.vpOfTechnology, (unsigned int)g_pickupTrailingRodataEuX.craigGalley, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.executiveVpOfAcclaimStudios,
        (unsigned int)g_pickupTrailingRodataEuX.darrenStubbington, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.publisherCredits, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.acclaimEntertainmentInc, (unsigned int)g_pickupTrailingRodataEuX.nyProductDevelopment, (unsigned int)g_pickupTrailingRodataEuX.empty,
        (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.producer, (unsigned int)g_pickupTrailingRodataEuX.jamesDaly, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.projectTracking, (unsigned int)g_pickupTrailingRodataEuX.kathleenByrne, (unsigned int)g_pickupTrailingRodataEuX.nicoleRuisi,
        (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.manualSupportManager, (unsigned int)g_pickupTrailingRodataEuX.billDickson, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.qaManager, (unsigned int)g_pickupTrailingRodataEuX.carolCaracciolo,
        (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.qaSupervisor, (unsigned int)g_pickupTrailingRodataEuX.daleTaylor, (unsigned int)g_pickupTrailingRodataEuX.jeffRosa, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.seniorLeadAnalyst,
        (unsigned int)g_pickupTrailingRodataEuX.brianRegan, (unsigned int)g_pickupTrailingRodataEuX.mikePatterson, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.leadAnalysts, (unsigned int)g_pickupTrailingRodataEuX.markGarone, (unsigned int)g_pickupTrailingRodataEuX.mattCanonico, (unsigned int)g_pickupTrailingRodataEuX.empty,
        (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.projectLeads, (unsigned int)g_pickupTrailingRodataEuX.chrisRappo, (unsigned int)g_pickupTrailingRodataEuX.jonNicolai, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.testers, (unsigned int)g_pickupTrailingRodataEuX.paulDicarlo,
        (unsigned int)g_pickupTrailingRodataEuX.joshuaRogers, (unsigned int)g_pickupTrailingRodataEuX.danBadilla, (unsigned int)g_pickupTrailingRodataEuX.brhettHohwald, (unsigned int)g_pickupTrailingRodataEuX.lucAngrandIi, (unsigned int)g_pickupTrailingRodataEuX.scottSnopowski, (unsigned int)g_pickupTrailingRodataEuX.mauricePhilips, (unsigned int)g_pickupTrailingRodataEuX.joeCarbone, (unsigned int)g_pickupTrailingRodataEuX.paulJohnson,
        (unsigned int)g_pickupTrailingRodataEuX.djPeluso, (unsigned int)g_pickupTrailingRodataEuX.jayCapozello, (unsigned int)g_pickupTrailingRodataEuX.markBerkowitz, (unsigned int)g_pickupTrailingRodataEuX.lloydThompson, (unsigned int)g_pickupTrailingRodataEuX.maxImas, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.turnoverCoordinator, (unsigned int)g_pickupTrailingRodataEuX.chrisMaher,
        (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.turnoverTechnician, (unsigned int)g_pickupTrailingRodataEuX.anthonyGentile, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.technicians, (unsigned int)g_pickupTrailingRodataEuX.chrisZino, (unsigned int)g_pickupTrailingRodataEuX.mikeSterzel, (unsigned int)g_pickupTrailingRodataEuX.chrisFrisone,
        (unsigned int)g_pickupTrailingRodataEuX.ulisesBatalla, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.marketingProductManager, (unsigned int)g_pickupTrailingRodataEuX.donJackson, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.marketingGameAnalyst, (unsigned int)g_pickupTrailingRodataEuX.jpCarnovale, (unsigned int)g_pickupTrailingRodataEuX.jackScalici,
        (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.prManager, (unsigned int)g_pickupTrailingRodataEuX.michelleSeebach, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.srManagerAcclaimOnline, (unsigned int)g_pickupTrailingRodataEuX.benFischbach, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.internetArchitect,
        (unsigned int)g_pickupTrailingRodataEuX.bobbySaha, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.onlineEditor, (unsigned int)g_pickupTrailingRodataEuX.edFortune, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.specialThanks, (unsigned int)g_pickupTrailingRodataEuX.empty,
        (unsigned int)g_pickupTrailingRodataEuX.weWouldLikeToExtendA, (unsigned int)g_pickupTrailingRodataEuX.thankYouToAllOfThe, (unsigned int)g_pickupTrailingRodataEuX.friendsAndFamilyOfThe, (unsigned int)g_pickupTrailingRodataEuX.rageWarsTeamForTheir, (unsigned int)g_pickupTrailingRodataEuX.supportAndUnderstanding, (unsigned int)g_pickupTrailingRodataEuX.ofWhyWeWereNeverHome, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.additionalSpecialThanksTo,
        (unsigned int)g_pickupTrailingRodataEuX.jennyCowlishaw, (unsigned int)g_pickupTrailingRodataEuX.damarisCocoAndSnikersToo, (unsigned int)g_pickupTrailingRodataEuX.marleneAndRaymondPaciniThanks, (unsigned int)g_pickupTrailingRodataEuX.forLettingMeDoWhatI, (unsigned int)g_pickupTrailingRodataEuX.drDonTHueyJrD, (unsigned int)g_pickupTrailingRodataEuX.brotherBeFreeIMissYou, (unsigned int)g_pickupTrailingRodataEuX.davidAndMattAtSatelliteStudio, (unsigned int)g_pickupTrailingRodataEuX.jeffEverettForLettingUsBorrow,
        (unsigned int)g_pickupTrailingRodataEuX.halfOfHisTeam, (unsigned int)g_pickupTrailingRodataEuX.sheaMackinCadeKylanAndFamily, (unsigned int)g_pickupTrailingRodataEuX.mikeMarques, (unsigned int)g_pickupTrailingRodataEuX.danHillAndFamily, (unsigned int)g_pickupTrailingRodataEuX.greyThanksKasTsBehrAnd, (unsigned int)g_pickupTrailingRodataEuX.lorraineBrittanyAndKatie, (unsigned int)g_pickupTrailingRodataEuX.angelaForWaitingUpForMe, (unsigned int)g_pickupTrailingRodataEuX.ramiForTeachingMeAboutMonkeys,
        (unsigned int)g_pickupTrailingRodataEuX.annaLangstonSimonSkedd, (unsigned int)g_pickupTrailingRodataEuX.jimDelbridgeHaileySebastian, (unsigned int)g_pickupTrailingRodataEuX.andLilly, (unsigned int)g_pickupTrailingRodataEuX.pamTrumanAndTuckerFor, (unsigned int)g_pickupTrailingRodataEuX.theirPatience, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty,
        (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)g_pickupTrailingRodataEuX.visitOurWebsiteAtWwwAcclaim, 0x00000000,
        0x00000000,
    },
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    {
        0x00000000, 0x739C7572,
    },
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    0x9C757273,
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    {
        0x00000000, (unsigned int)g_pickupTrailingRodataEuX.data, (unsigned int)g_pickupTrailingRodataEuX.empty, (unsigned int)&g_pickupTrailingRodataEuX.nDeMemcontrollerPak[8], 0x00000000, 0x00000000, 0x00000000, (unsigned int)g_pickupTrailingRodataEuX.extensionDeMemoireTrouvee,
        0x00000000, (unsigned int)g_pickupTrailingRodataEuX.appuyezSurUnBouton, 0x00000000,
    },
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    0xE9000000,
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    0xE9000000,
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    0x9C696C20,
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    0x639C7572,
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    "\000\000\000",
};
#endif
#ifdef VERSION_EU
extern ScreenMessageSetupDataEU k_SkyPostscaledscreenmessageEncodedWords;
#endif
#endif
#if defined(VERSION_EU_X)
EuXScreenMessageTextData s_SkyPostscaledscreenmessageScreenMessageTextEuX = {
    "ts massifs...\000\000",
    "Invuln\351rabilit\351...\000",
    "Bouclier pare-balles...",
    "Absorption d'\351nergie...",
    "Quelque chose d'autre...\000\000\000",
    "Bouclier\000\000\000",
    "pi\350ce de l'arme nucl\351aire\000\000",
    "Repr\351sailles !\000",
    "Le Drapeau a \351t\351 attaqu\351\000\000\000",
    "Le Drapeau a \351t\351 captur\351\000\000\000",
    "Le Drapeau a \351t\351 reconquis\000",
    { 0x4C652050, 0x6F75766F, 0x69722065, 0x73742065, 0x6E747265, 0x20766F73, 0x206D6169, 0x6E730000, 0x67726966, 0x66650000, 0x6C616D65, 0x20646520, 0x67756572, 0x72650000, 0x61726300, 0x61726320, 0x74656B00, 0x70697374, 0x6F6C6574, 0x00000000, 0x6D61676E, 0x756D2036, 0x30000000, 0x66757369, 0x6C207472, 0x616E7175, 0x696C6C69, 0x73616E74, 0x00000000, 0x66757369, 0x6C20E020, 0x666CE963, 0x68657474, 0x657320E9, 0x6C656374, 0x72697175, 0x65730000, 0x66757369, 0x6C000000, 0x64E96368, 0x69717565, 0x74657572, 0x00000000, 0x66757369, 0x6C20E020, 0x706C6173, 0x6D610000, 0x63616E6F, 0x6E20E020, 0x6F726167, 0x65000000, 0x6E616365, 0x6C6C6520, 0x736F6C61, 0x69726500, 0x6C616E63, 0x652D6E61, 0x63656C6C, 0x65732073, 0x6F6C6169, 0x72657300, 0x70657263, 0x65757365, 0x2063E972, 0xE9627261, 0x6C650000, 0x506F7365, 0x75722064, 0x65206D69, 0x6E657300, 0x6C616E63, 0x652D6772, 0x656E6164, 0x65730000, 0x6C616E63, 0x652D6D69, 0x7373696C, 0x65732053, 0x636F7270, 0x696F6E00, 0x66757369, 0x6C20E020, 0x68617270, 0x6F6E0000, 0x6C616E63, 0x652D746F, 0x7270696C, 0x6C657300, 0x66757369, 0x6C206368, 0x65766175, 0x63686575, 0x72000000, 0x66757369, 0x6C206465, 0x20766F6C, 0x00000000, 0x6C616E63, 0x652D666C, 0x616D6D65, 0x73000000, 0x736F7566, 0x666C6520, 0x64752072, 0x61736F69, 0x72000000, 0x61726D65, 0x206E7563, 0x6CE96169, 0x72650000, 0x667573E9, 0x6520E963, 0x6C616972, 0x616E7465, 0x00000000, 0x47726170, 0x706C696E, 0x6720486F, 0x6F6B0000, 0x61726261, 0x6CE87465, 0x00000000, 0x66757369, 0x6C20E020, 0x666CE963, 0x68657474, 0x65730AE9, 0x6C656374, 0x72697175, 0x65730000, 0x63616E6F, 0x6E20E020, 0x6F726167, 0x65000000, 0x66757369, 0x6C206427, 0x61737361, 0x75740000, 0x66757369, 0x6C20E020, 0x706C6173, 0x6D610000, 0x70657263, 0x65757365, 0x2063E972, 0xE9627261, 0x6C650000, 0x6C616E63, 0x652D6772, 0x656E6164, 0x65730000, 0x6C616E63, 0x652D6D69, 0x7373696C, 0x65730A73, 0x636F7270, 0x696F6E00, 0x66757369, 0x6C20E020, 0x68617270, 0x6F6E0000, 0x6C616E63, 0x652D746F, 0x7270696C, 0x6C657300, 0x67726966, 0x66652064, 0x65207261, 0x70616365, 0x00000000 },
    "NOVICE\000",
    "DEBUTANT\000\000\000",
    "COMBATTANT\000",
    "ECLAIREUR\000\000",
    "BRAVE\000\000",
    "TRAQUEUR\000\000\000",
    "CHASSEUR\000\000\000",
    "GUERRIER\000\000\000",
    "CHEVALIER NOIR\000",
    "MARAUDEUR\000\000",
    "ASSASSIN\000\000\000",
    "FLEAU\000\000",
    "SEIGNEUR DE GUERRE\000",
    "VENT DE MORT\000\000\000",
    "CONQUERANT\000",
    "MAITRE\000",
    "TYRAN\000\000",
    "FOU DE GUERRE\000\000",
    "MAIN DE DIEU\000\000\000",
    "CHEF DE CLAN\000\000\000",
    "PROVING GROUNDS : ACHEVE\000\000\000",
    "BASIC TRAINING : ACHEVE",
    "CROSSROADS : ACHEVE",
    "GRIM RETREAT : ACHEVE\000\000",
    "CATHEDRAL : ACHEVE\000",
    "FALLOUT : ACHEVE\000\000\000",
    "BOXED SET : ACHEVE\000",
    "DIRE STRAIGHT : ACHEVE\000",
    "PREY : ACHEVE\000\000",
    "WAREHOUSE : ACHEVE\000",
    "WATER TEMPLE : ACHEVE\000\000",
    "BOMB SHELTER : ACHEVE\000\000",
    "TEMPERED : ACHEVE\000\000",
    "EARTH TEMPLE : ACHEVE\000\000",
    "FIRE TEMPLE : ACHEVE\000\000\000",
    "MYSTIC : ACHEVE",
    "BOTTLENECK : ACHEVE",
    "TIGHTROPE : ACHEVE\000",
    "THE PIT : ACHEVE\000\000\000",
    "LEAP OF FAITH : ACHEVE\000",
    "WICKED DANCE : ACHEVE\000\000",
    "BUNKER : ACHEVE",
    "AMPHITHEATER : ACHEVE\000\000",
    "FIRE WALKER : ACHEVE\000\000\000",
    "CRYPTS : ACHEVE",
    "BREAKDOWN : ACHEVE\000",
    "RETALIATION : ACHEVE\000\000\000",
    "HOPELESS : ACHEVE\000\000",
    "MATRIX : ACHEVE",
    "FATHOM : ACHEVE",
    "THE PEDESTAL : ACHEVE\000\000",
    "DEFCON 5 : ACHEVE\000\000",
    "SPIRIT TEMPLE : ACHEVE\000",
    "STRONGHOLD : ACHEVE",
    "COURTYARD : ACHEVE\000",
    "STARLIGHT : ACHEVE\000",
    "15 FRAGS EN 5 MINUTES\000\000",
    "25 FRAGS EN 10 MINUTES\000",
    "AUCUN FRAG\000",
    "VOUS VOUS ETES TUE 5 FOIS\000\000",
    "BON DERNIER",
    "RECOMPENSE POUR LES FRAGS\000\000",
    "RECOMPENSE POUR LES MORTS\000\000",
    "CANARDEZ 10 ADVERSAIRES DANS LE ROUND\000\000",
    "INVAINCU DANS LE ROUND\000",
    "VOUS AVEZ VAINCU BASTILLE\000\000",
    "VOUS AVEZ VAINCU SYRA\000\000",
    "VOUS AVEZ VAINCU SYMBIONT\000\000",
    "VOUS AVEZ VAINCU TAL SET\000\000\000",
    "FIN DU SCENARIO COOPERATIF\000",
    "<VIDE>\000",
    "<NOUVEAU JOUEUR>\000\000\000",
    "TUROK\000\000",
    "WARRIOR",
    "MASTER\000",
    "ADON\000\000\000",
    "SEEKER\000",
    "HUNTRESS\000\000\000",
    "CAMPAIN",
    "SLAVER\000",
    "TYRANT\000",
    "FIREBORN\000\000\000",
    "ICELORD",
    "ENTRAIL",
    "MITES\000\000",
    "COMPIES",
    "TEDDIES",
    "JUGGNAUT\000\000\000",
    "SLOTH\000\000",
    "MAULER\000",
    "DRONE\000\000",
    "GRUNT\000\000",
    "SLAVE\000\000",
    "SOLDIER",
    "CAPTAIN",
    "KING\000\000\000",
    "BASTILLE\000\000\000",
    "TAL SET",
    "SYRA\000\000\000",
    "SYMBIONT\000\000\000",
    "GUARDIAN\000\000\000",
    "RAVAGE\000",
    "CYCLOPS",
    "LORDDEAD\000\000\000",
    "MAGGOT\000",
    "VILE\000\000\000",
    "ELITE\000\000",
    "BIOBOT\000",
    "KILLBOT",
    "DEATH\000\000",
    "REAPER\000",
    "MAW",
    "RAPTOR\000",
    "SLAG\000\000\000",
    "CLAW\000\000\000",
    "WARCLUBS\000\000\000",
    "TUROK\000\000",
    "MANTID DRONE\000\000\000",
    "CAMPAIGNER\000",
    "FIREBORN\000\000\000",
    "MANTID SOLDIER\000",
    "ADON\000\000\000",
    "LORD OF THE DEAD\000\000\000",
    "ELITE GUARD",
    "GUARDIAN\000\000\000",
    "JUGGERNAUT\000",
    "OBLIVION SPAWN\000",
    "BASTILLE\000\000\000",
    "SYRA\000\000\000",
    "SYMBIONT\000\000\000",
    "TAL SET",
    "RAPTOR\000",
    "MANTID MITES\000\000\000",
    "capturez le drapeau %d fois",
    "capturez le drapeau %d fois",
    "%d captures par \351quipe\000",
    "tag le singe %d fois\000\000\000",
    "tag le singe %d fois\000\000\000",
    "obtenez %d tags de cr\351ature",
    "obtenez %d frag",
    "obtenez %d frags\000\000\000",
    "obtenez %d frag par \351quipe\000",
    "obtenez %d frags par \351quipe",
    "en %02d secondes maximum\000\000\000",
    "en %d minute et %02d secondes maximum\000\000",
    "en %d minutes et %02d secondes maximum\000",
    "en %d minute maximum\000\000\000",
    "en %d minutes maximum\000\000",
    "avec %d vie",
    "avec %d vies\000\000\000",
    "battez %s\000\000",
    "battez %s et %s",
    "un pour tous\000\000\000",
    "FACILE\000",
    "NORMAL\000",
    "DIFFICILE\000\000",
    "OFF",
    "ON\000",
    "ROUGE\000\000",
    "VERT\000\000\000",
    "HORIZONTAL\000",
    "VERTICAL\000\000\000",
    "BASSE RESOLUTION\000\000\000",
    "HAUTE RESOLUTION\000\000\000",
    "ECRAN\000\000",
    "NON",
    "OUI",
    "NOVICE\000",
    "FACILE\000",
    "NORMAL\000",
    "VETERAN",
    "EXPERT\000",
    "ARCADE\000",
    "BARILLET\000\000\000",
    "APPUYER",
    "MIXED\000\000",
    "MANETTE %d\000",
    "CTF",
    "TBL",
    "BL\000",
    "FT\000",
    "DEFI\000\000\000",
    "LA FOIRE DU FRAG\000\000\000",
    "CONTRE LA MONTRE\000\000\000",
    "JOUEUR %d\000\000",
    "TALISMAN AIGLE OBTENU. +1 !",
    "MOITIE DU TALISMAN AIGLE OBTENU. +1 AVEC L'AUTRE MOITIE",
    "SECONDE MOITIE DU TALISMAN OBTENUE, +1 !\000\000\000",
    "TALISMAN OURS OBTENU. EXPLOSIFS +5\000",
    "TALISMAN COYOTE OBTENU. BALLES +50\000",
    "TALISMAN PUMA OBTENU. ENERGIE +50\000\000",
    "TALISMAN VIPERE OBTENU. SANTE MAX +5\000\000\000",
    "TALISMAN COOPERATIF OBTENU\000",
    "ICONE MINI-PARTIES OBTENU\000\000",
    "FUSIL D'ASSAUT TROUVE\000\000",
    "TIR RAPIDE POUR FUSIL D'ASSAUT TROUVE\000\000",
    "LUNETTE DE VISEE POUR ARBALETE TEK TROUVEE\000",
    "LANCE-GRENADES TROUVE\000\000",
    "AMELIORATION POUR LANCE-GRENADES TROUVE",
    "FUSIL PLASMA TROUVE",
    "LUNETTE POUR FUSIL PLASMA TROUVEE\000\000",
    "JET D'ACIDE TROUVE\000",
    "ATTAQUE DE GRIFFE TROUVEE\000\000",
    "LANCE-FUSEES RADIOACTIVES TROUVE\000\000\000",
    "AMELIORATION POUR LANCE-FUSEES RADIOACTIVES TROUVEE",
    "LANCE-MISSILES SCORPION TROUVE\000",
    "AIMANT POUR LANCE-MISSILES SCORPION TROUVE\000",
    "PETRIFICATEUR TROUVE\000\000\000",
    "AMELIORATION POUR PETRIFICATEUR TROUVEE",
    "GEL NAPALM TROUVE\000\000",
    "VISEE LASER POUR MAG 60 TROUVEE",
    "RUPTEUR TROUVE\000",
    "DILATATEUR TROUVE\000\000",
    "AMELIORATION POUR DILATATEUR TROUVEE\000\000\000",
    "BOOMERANG TROUVE\000\000\000",
    "AMELIORATION POUR BOOMERANG TROUVEE",
    "MINIGUN TROUVE\000",
    "BOUCLIER POUR MINIGUN TROUVE\000\000\000",
    "AMELIORATION NETTOYEUR POUR FUSIL TROUVEE\000\000",
    "DECHARNEUR TROUVE\000\000",
    "AMELIORATION POUR DECHARNEUR TROUVEE\000\000\000",
    "AMELIORATION POUR MARTEAU DE GUERRE TROUVEE",
    "VOUS AVEZ LIBERE %s",
    "ECHEC DE LA MISSION",
    "OBJET DEJA OBTENU\000\000",
    "EQUIPE\000",
    "% PRECISION",
    "TAGS\000\000\000",
    "DRAPEAUX\000\000\000",
    "FELICITATIONS ! VOUS AVEZ ACHEVE LA FOIRE DU FRAG\000\000",
    "FELICITATIONS ! VOUS AVEZ ACHEVE LE CONTRE LA MONTRE\000\000\000",
    "FRENCH\000",
    "pistol clip (10 rounds)",
    { 0x7269666C, 0x6520636C, 0x69702028, 0x31302072, 0x6F756E64, 0x73290000, 0x666CE863, 0x68650000, 0x666CE863, 0x68652074, 0x656B0000, 0x3520666C, 0xE8636865, 0x73000000, 0x63617271, 0x756F6973, 0x20646520, 0x31302066, 0x6CE86368, 0x65730000, 0x3320666C, 0xE8636865, 0x73207465, 0x6B000000, 0x63617271, 0x756F6973, 0x20646520, 0x3520666C, 0xE8636865, 0x73207465, 0x6B000000, 0x31302062, 0x616C6C65, 0x73206465, 0x20706973, 0x746F6C65, 0x74202863, 0x68617267, 0x65757229, 0x00000000, 0x35206361, 0x72746F75, 0x63686573, 0x20646520, 0x6D61676E, 0x756D2028, 0x63686172, 0x67657572, 0x29000000, 0x626FEE74, 0x65206465, 0x20343020, 0x62616C6C, 0x65730000, 0x3120666C, 0xE9636865, 0x74746520, 0x7472616E, 0x7175696C, 0x6C697361, 0x6E746500, 0x3520666C, 0xE9636865, 0x74746573, 0x20747261, 0x6E717569, 0x6C6C6973, 0x616E7465, 0x73202870, 0x61717565, 0x74290000, 0x3520666C, 0xE9636865, 0x74746573, 0x20E96C65, 0x63747269, 0x71756573, 0x00000000, 0x32302066, 0x6CE96368, 0x65747465, 0x7320E96C, 0x65637472, 0x69717565, 0x73202870, 0x61717565, 0x74290000, 0x33206361, 0x72746F75, 0x63686573, 0x20646520, 0x66757369, 0x6C000000, 0x626FEE74, 0x65206465, 0x20313020, 0x63617274, 0x6F756368, 0x65732064, 0x65206675, 0x73696C00, 0x33206361, 0x72746F75, 0x63686573, 0x20646520, 0x66757369, 0x6C206578, 0x706C6F73, 0x69766573, 0x00000000, 0x33302063, 0x6172746F, 0x75636865, 0x73206465, 0x20706C61, 0x736D6100, 0x31353020, 0x63617274, 0x6F756368, 0x65732064, 0x6520706C, 0x61736D61, 0x20287061, 0x71756574, 0x29000000, 0x33206E61, 0x63656C6C, 0x65732073, 0x6F6C6169, 0x72657300, 0x32207065, 0x72636575, 0x73657300, 0x31206D69, 0x6E650000, 0x31206772, 0x656E6164, 0x65000000, 0x35206772, 0x656E6164, 0x65732028, 0x626FEE74, 0x65290000, 0x34206D69, 0x7373696C, 0x65732053, 0x636F7270, 0x696F6E00, 0x31206C61, 0x6E636500, 0x33206C61, 0x6E636573, 0x00000000, 0x3120746F, 0x7270696C, 0x6C650000, 0x32302063, 0x6172746F, 0x75636865, 0x73206465, 0x202E3230, 0x6D6D0000, 0x33206361, 0x72746F75, 0x63686573, 0x20657870, 0x6C6F7369, 0x76657300, 0x33206361, 0x72746F75, 0x63686573, 0x20E02066, 0x7261676D, 0x656E7461, 0x74696F6E, 0x00000000, 0x72E97365, 0x72766F69, 0x7220706F, 0x7572206C, 0x616E6365, 0x2D666C61, 0x6D6D6573, 0x00000000, 0x32206172, 0x6D657320, 0x6E75636C, 0xE9616972, 0x65730000, 0x666CE963, 0x68657474, 0x657320E9, 0x6C656374, 0x72697175, 0x65730000, 0x6D756E69, 0x74696F6E, 0x73206465, 0x2064E963, 0x68697175, 0x65746575, 0x72000000, 0x63656C6C, 0x756C6573, 0x20646520, 0x706C6173, 0x6D610000, 0x70657263, 0x65757365, 0x2063E972, 0xE9627261, 0x6C650000, 0x6772656E, 0x61646573, 0x00000000, 0x6D697373, 0x696C6573, 0x00000000, 0x68617270, 0x6F6E7300, 0x746F7270, 0x696C6C65, 0x00000000 },
    "difficult\351       :      facile\000",
    "difficult\351       :      normal\000",
    "difficult\351       :   difficile\000",
    "type de commande :      expert\000",
    "type de commande :      arcade\000",
    "type de commande :      ??????\000",
    "c\364t\351 de commande :      gauche\000",
    "c\364t\351 de commande :       droit\000",
    "vue surgissante  :     activ\351e\000",
    "vue surgissante  :  d\351sactiv\351e\000",
    "vis\351e automatique:     activ\351e\000",
    "vis\351e automatique:  d\351sactiv\351e\000",
    "couleur du sang  :  d\351sactiv\351e\000",
    "couleur du sang  :       rouge\000",
    "couleur du sang  :        vert\000",
    "Config. 2 joueurs:        horz\000",
    "Config. 2 joueurs:        vert\000",
    "opacit\351          : transparent\000",
    "opacit\351          :      opaque\000",
    "opacit\351          :            \000",
    "stick directionnel horiz.:norm\000",
    "stick directionnel horiz.:    \000",
    "stick directionnel vert. :norm\000",
    "stick directionnel vert. :    \000",
    "S\351lection des armes :   rapide\000",
    "S\351lection des armes :     norm\000",
    "R\351solution :       basse r\351so.\000",
    "R\351solution :       haute r\351so.\000",
    "R\351solution : haute r\351so.(cin\351)\000",
    "R\351solution :  tr\350s basse r\351so.\000",
    "R\351solution : basse r\351so.(cin\351)\000",
    "luminosit\351 :              norm\000",
    "luminosit\351 :                  \000",
    "language   :            french\000",
    "pr\351c\351dent\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "Ce jeu est\000",
    "compatible avec",
    "un rumble pak.\000",
    "Ins\351rez votre\000\000",
    "rumble pak maintenant\000\000",
    "si vous voulez\000",
    "jouer avec.",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "pause\000\000",
    "reprendre jeu\000\000",
    "statut de la mission\000\000\000",
    "mission",
    "inventaire\000",
    "chargement\000",
    "options",
    "triches",
    { 0x71756974, 0x74657200, 0x73746174, 0x75742064, 0x65206C61, 0x206D6973, 0x73696F6E, 0x00000000, 0xE9636865, 0x63206465, 0x206C6120, 0x6D697373, 0x696F6E00, 0x6E6F6E20, 0x64697370, 0x6F6E6962, 0x6C650000, 0x706F7274, 0x20642761, 0x64696100, 0x78207375, 0x72203320, 0x61637469, 0x76E92873, 0x29000000, 0x62616C69, 0x73652064, 0x652064E9, 0x74726573, 0x73650000, 0x78207375, 0x72203420, 0x73617576, 0xE9287329, 0x20000000, 0x656E6661, 0x6E747300, 0x72697669, 0xE8726520, 0x64657320, 0xE26D6573, 0x00000000, 0x78207375, 0x72203220, 0x64E97472, 0x75697428, 0x73290000, 0x706F7274, 0x61696C20, 0x64657320, 0xE26D6573, 0x00000000, 0x78207375, 0x72203320, 0x64E97472, 0x75697428, 0x73290000, 0x739C7572, 0x73206475, 0x2064E973, 0x6573706F, 0x69720000, 0x6D6172E9, 0x63616765, 0x73206465, 0x206C6120, 0x6D6F7274, 0x00000000, 0x78207375, 0x72203520, 0x73617576, 0xE9287329, 0x00000000, 0x70726973, 0x6F6E6E69, 0x65727300, 0x78207375, 0x72203320, 0x64E97472, 0x75697428, 0x73290000, 0x64E970F4, 0x74206465, 0x206D756E, 0x6974696F, 0x6E730000, 0x72657061, 0x69726520, 0x64657320, 0x6379636C, 0x6F706573, 0x00000000, 0x78207375, 0x72203320, 0x626F7563, 0x68E92873, 0x29000000, 0x636F6E64, 0x75697420, 0x64652076, 0x656E7469, 0x6C617469, 0x6F6E2074, 0x6865726D, 0x69717565, 0x00000000, 0x72756368, 0x65206465, 0x73206D61, 0x6E746964, 0x65730000, 0x78207375, 0x72203320, 0x64E97472, 0x75697428, 0x73290000, 0x656D6272, 0x796F6E73, 0x20646520, 0x7265696E, 0x65730000, 0x78207375, 0x72203120, 0x64E97472, 0x75697400, 0x6F726469, 0x6E617465, 0x75727320, 0x7072696E, 0x63697061, 0x75780000, 0x76616973, 0x73656175, 0x206C756D, 0x696E6575, 0x78206465, 0x20707269, 0x6D616765, 0x6E000000, 0x78207375, 0x72203420, 0x72656361, 0x6C696272, 0xE9287329, 0x00000000, 0x67E96EE9, 0x72617465, 0x75727320, 0xE96C6563, 0x74726971, 0x75657300, 0x78207375, 0x72203320, 0x64E97472, 0x75697428, 0x73290000, 0x78207375, 0x72203F20, 0x64E97472, 0x75697428, 0x73290000, 0x7573696E, 0x65206465, 0x206D6F6E, 0x74616765, 0x00000000, 0x6F6B0000, 0x6D697373, 0x696F6E00, 0x706F7274, 0x20649261, 0x64696100, 0x61637469, 0x76657A20, 0x33000000, 0x62616C69, 0x73657320, 0x64652064, 0xE9747265, 0x73736500, 0x73617576, 0x657A2034, 0x20656E66, 0x616E7473, 0x00000000, 0x61637469, 0x76657A20, 0x6C652074, 0xE96CE974, 0x72616E73, 0x706F7274, 0x65757200, 0x70726F74, 0xE967657A, 0x206C6520, 0x746F7465, 0x6D000000, 0x00000000, 0x72697669, 0xE8726520, 0x64657320, 0xE26D6573, 0x00000000, 0x64E97472, 0x75697365, 0x7A203220, 0x706F7274, 0x65732064, 0x657320E2, 0x6D657300, 0x64E97472, 0x75697365, 0x7A203300, 0x739C7572, 0x73206475, 0x2064E973, 0x6573706F, 0x69720000, 0x61637469, 0x76657A20, 0x6C652074, 0xE96CE974, 0x72616E73, 0x706F7274, 0x65757200, 0x70726F74, 0xE967657A, 0x206C6520, 0x746F7465, 0x6D000000, 0x00000000, 0x6C657320, 0x6D6172E9, 0x63616765, 0x73206465, 0x206C6120, 0x6D6F7274, 0x00000000, 0x73617576, 0x657A2035, 0x20707269, 0x736F6E6E, 0x69657273, 0x00000000, 0x64E97472, 0x75697365, 0x7A203300, 0x656E7472, 0x6570F474, 0x73206465, 0x206D756E, 0x6974696F, 0x6E730000, 0x61637469, 0x76657A20, 0x6C652074, 0xE96CE974, 0x72616E73, 0x706F7274, 0x65757200, 0x70726F74, 0xE967657A, 0x206C6520, 0x746F7465, 0x6D000000, 0x00000000, 0x72657061, 0x69726520, 0x64657320, 0x61766575, 0x676C6573, 0x00000000, 0x72656665, 0x726D657A, 0x2033206F, 0x72696669, 0x63657320, 0x74686572, 0x6D697175, 0x65730000, 0x61637469, 0x76657A20, 0x6C652074, 0xE96CE974, 0x72616E73, 0x706F7274, 0x65757200, 0x70726F74, 0xE967657A, 0x206C6520, 0x746F7465, 0x6D000000, 0x00000000, 0x00000000, 0x00000000, 0x6C926573, 0x7361696D, 0x20646573, 0x206D616E, 0x74696473, 0x00000000, 0x64E97472, 0x75697365, 0x7A203300, 0x656D6272, 0x796F6E73, 0x20646520, 0x6C612072, 0x65696E65, 0x00000000, 0x64E97472, 0x75697365, 0x7A206C92, 0x6F726469, 0x6E617465, 0x75722070, 0x72696E63, 0x6970616C, 0x00000000, 0x61637469, 0x76657A20, 0x6C652074, 0xE96CE974, 0x72616E73, 0x706F7274, 0x65757200, 0x70726F74, 0xE967657A, 0x206C6520, 0x746F7465, 0x6D000000, 0x00000000, 0x6C652076, 0x61697373, 0x65617520, 0x64752070, 0x72696D61, 0x67656E00, 0x72E9676C, 0x657A2034, 0x00000000, 0x67E96EE9, 0x72617465, 0x75727320, 0x64652070, 0x75697373, 0x616E6365, 0x00000000, 0x64E97472, 0x75697365, 0x7A203300, 0x636861EE, 0x6E657320, 0x64652070, 0x726F6475, 0x6374696F, 0x6E000000, 0x61637469, 0x76657A20, 0x6C652074, 0xE96CE974, 0x72616E73, 0x706F7274, 0x65757200, 0x00000000 },
    "inventaire\000",
    "ok\000",
    "RAGE WARS\000\000",
    "TUROK 2",
    "51\000",
    "NRWX\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "AUTRE PARTIE\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "info note\000\000",
    "effacer note\000\000\000",
    "difficult\351     :   facile\000\000",
    "difficult\351     :   normal\000\000",
    "difficult\351     :difficile\000\000",
    "points de sant\351:         \000\000",
    { 0x76696573, 0x20202020, 0x20202020, 0x2020203A, 0x20202020, 0x20202020, 0x20000000, 0x706F7274, 0x20642761, 0x64696100, 0x72697669, 0xE8726520, 0x64657320, 0xE26D6573, 0x00000000, 0x6D6172E9, 0x63616765, 0x73206465, 0x206C6120, 0x6D6F7274, 0x00000000, 0x72657061, 0x69726520, 0x64657320, 0x6379636C, 0x6F706573, 0x00000000, 0x72756368, 0x65206465, 0x73206D61, 0x6E746964, 0x65730000, 0x76616973, 0x73656175, 0x206C756D, 0x696E6575, 0x78206465, 0x20507269, 0x6D616765, 0x6E000000, 0x6C65206E, 0x6F796175, 0x00000000, 0x69642064, 0x65206E69, 0x76656175, 0x20696E63, 0x6F6E6E75, 0x65000000 },
    "heure:000.00.00",
    "info note\000\000",
    "effacer note\000\000\000",
    "effacer note\000\000\000",
    "nom              ext \000\000",
    "                     \000\000",
    "nom       :            ",
    "type      :            ",
    "victimes  :            ",
    "classement:            ",
    "charger?\000\000\000",
    "effacer?\000\000\000",
    "effacer?\000\000\000",
    "erreur\000",
    "important\000\000",
    "ok\000",
    "-\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "    sauvegarder",
    "        charger",
    "points de sant\351",
    "      munitions",
    "      pr\351c\351dent",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "tir de mine!\000\000\000",
    "tir \340 la t\352te !",
    "tir au corps!\000\000",
    "tir au bras!\000\000\000",
    "modifier\000\000\000",
    { 0x02000000 },
    { 0x03000000 },
    { 0x04000000 },
    "tagg\351 par \000",
    "vous avez tagg\351 \000\000\000",
    "tu\351 par \000\000\000",
    "vous avez tu\351 \000",
    "vous vous \352tes tu\351\000",
    "vous avez perdu votre drapeau !!!\000\000",
    "il a l\342ch\351 le drapeau !!!\000\000",
    "\352tes-vous s\373r?\000",
    "de vouloir\000",
    "oui",
    "non",
    "codes triche\000\000\000",
    "charger",
    "sauvegarder",
    "taper codes triche\000",
    "rejoindre\000\000",
    "veuillez patienter..\000\000\000",
    "connexion..",
    "pr\351c\351dent\000\000",
    "continuer ?",
    "partie termin\351e",
    "temps : xx\000",
    "termin\351",
    "nouveau mode de triche activ\351\000\000",
    "invincibilit\351 activ\351e\000\000",
    "vies infinies activ\351es\000",
    "toutes armes activ\351es\000\000",
    "munitions illimit\351es activ\351es\000\000",
    "toutes clefs activ\351es\000\000",
    "mode grosse t\352te activ\351",
    "mode minuscule activ\351\000\000",
    "mode trait activ\351\000\000",
    "mode gros pieds grosses mains activ\351\000\000\000",
    "mode stylo et encre activ\351\000",
    "mode gouraud activ\351",
    "code triche de juan activ\351\000",
    "code triche de l'attaque de zach activ\351",
    "carte compl\350te activ\351e\000",
    "cit\351 sombre activ\351e",
    "hmmm... d\351licieuses rayures",
    "warp niveau 1 activ\351\000\000\000",
    "warp niveau 2 activ\351\000\000\000",
    "warp niveau 3 activ\351\000\000\000",
    "warp niveau 4 activ\351\000\000\000",
    "warp niveau 5 activ\351\000\000\000",
    "warp niveau 6 activ\351\000\000\000",
    "boss warp reine activ\351\000",
    "boss warp cyclope activ\351\000\000\000",
    "boss warp m\350re activ\351\000\000",
    "warp boss primagen activ\351\000\000",
    "warp cr\351dits activ\351",
    "invincibilit\351                   :    activ\351e\000\000\000",
    "invincibilit\351                   : d\351sactiv\351e\000\000\000",
    "vies infinies                   :   activ\351es\000\000\000",
    "vies infinies                   :d\351sactiv\351es\000\000\000",
    "toutes armes                    :   activ\351es\000\000\000",
    "toutes armes                    :d\351sactiv\351es\000\000\000",
    "munitions illimit\351es            :   activ\351es\000\000\000",
    "munitions illimit\351es            :d\351sactiv\351es\000\000\000",
    "tous objets sp\351ciaux            :    activ\351s\000\000\000",
    "tous objets sp\351ciaux            : d\351sactiv\351s\000\000\000",
    "mode grosse t\352te                :     activ\351\000\000\000",
    "mode grosse t\352te                :  d\351sactiv\351\000\000\000",
    "mode minuscule                  :     activ\351\000\000\000",
    "mode minuscule                  :  d\351sactiv\351\000\000\000",
    "mode trait                      :     activ\351\000\000\000",
    "mode trait                      :  d\351sactiv\351\000\000\000",
    "mode gros pieds / grosses mains :     activ\351\000\000\000",
    "mode gros pieds / grosses mains :  d\351sactiv\351\000\000\000",
    "mode stylo et encre             :     activ\351\000\000\000",
    "mode stylo et encre             :  d\351sactiv\351\000\000\000",
    "mode gouraud                    :     activ\351\000\000\000",
    "mode gouraud                    :  d\351sactiv\351\000\000\000",
    "code triche de juan             :     activ\351\000\000\000",
    "code triche de juan             :  d\351sactiv\351\000\000\000",
    "code triche de l'attaque de zach:     activ\351\000\000\000",
    "code triche de l'attaque de zach:  d\351sactiv\351\000\000\000",
    "carte compl\350te                  :    activ\351e\000\000\000",
    "carte compl\350te                  : d\351sactiv\351e\000\000\000",
    "cit\351 sombre                     :    activ\351e\000\000\000",
    "cit\351 sombre                     : d\351sactiv\351e\000\000\000",
    "d\351licieuses rayures             :   activ\351es\000\000\000",
    "d\351licieuses rayures             :d\351sactiv\351es\000\000\000",
    "warp :                           port d'adia\000\000\000",
    "warp :                      rivi\350re des \342mes\000\000\000",
    "warp :                  mar\351cages de la mort\000\000\000",
    "warp :                  repaire des cyclopes\000\000\000",
    "warp :                    ruche des mantides\000\000\000",
    "warp :       vaisseau de lumi\350re de Primagen\000\000\000",
    "warp :                            boss reine\000\000\000",
    "warp :                          boss cyclope\000\000\000",
    "warp :                             boss m\350re\000\000\000",
    "warp :                         boss primagen\000\000\000",
    "warp :                               cr\351dits\000\000\000",
    "vous avez tu\351\000\000",
    "vous avez marqu\351\000\000\000",
    "totaux\000",
    "un      :0000\000\000",
    "deux    :0000\000\000",
    "trois   :0000\000\000",
    "quatre  :0000\000\000",
    "marques :0000\000\000",
    "victimes:0000\000\000",
    "morts   :0000\000\000",
    "suicides:0000\000\000",
    "un      :0000\000\000",
    "deux    :0000\000\000",
    "trois   :0000\000\000",
    "quatre  :0000\000\000",
    "marques :0000\000\000",
    "victimes:0000\000\000",
    "morts   :0000\000\000",
    "suicides:0000\000\000",
    "un      :0000\000\000",
    "deux    :0000\000\000",
    "trois   :0000\000\000",
    "quatre  :0000\000\000",
    "marques :0000\000\000",
    "victimes:0000\000\000",
    "morts   :0000\000\000",
    "suicides:0000\000\000",
    "un      :0000\000\000",
    "deux    :0000\000\000",
    "trois   :0000\000\000",
    "quatre  :0000\000\000",
    "marques :0000\000\000",
    "victimes:0000\000\000",
    "morts   :0000\000\000",
    "suicides:0000\000\000",
    "joueur 1\000\000\000",
    "joueur 2\000\000\000",
    "joueur 3\000\000\000",
    "joueur 4\000\000\000",
    "joueur seul",
    "nouvelle partie",
    "chargement\000",
    "multi\000\000",
    "match \340 mort\000\000\000",
    "s\351lectionner type de partie",
    "bloodlust\000\000",
    "bloodlust\000\000",
    "partie contre la montre :aucune",
    "limite victimes         :aucune",
    "niveau:               al\351atoire",
    "niveau:        exp\351rimentations",
    "niveau:panique au clair de lune",
    "niveau:             \340 proximit\351",
    "niveau:     la forge de Vulcain",
    "niveau:         t\351l\351portastique",
    "niveau:          image invers\351e",
    "niveau:            cible facile",
    "niveau:              h 2 whaou!",
    "niveau:                 d\351mence",
    "niveau:             crypte mosh",
    "niveau:            carr\351s cubes",
    "niveau:           huit en folie",
    "niveau:                   mille",
    "texture :               ch\342teau",
    "texture :               aci\351rie",
    "texture :         fort en ch\352ne",
    "texture :            catacombes",
    "texture :                 bagne",
    "texture :          grande ville",
    "texture :          dragon rouge",
    "texture :             paintball",
    "texture :             M. Joyeux",
    "viseur  :                activ\351",
    "viseur  :             d\351sactiv\351",
    "commencer partie\000\000\000",
    "pr\351c\351dent\000\000",
    "frag tag\000\000\000",
    "frag tag\000\000\000",
    "limite marquage         :aucune",
    "niveau:          maison de fous",
    "niveau:                bataille",
    "niveau:            jeu de l'oie",
    "niveau:              primattica",
    "niveau:              feu crois\351",
    "niveau:          v.o.j.c.q.v.d.",
    "sang \351quipe",
    "personnaliser armes",
    "fusil \340 fl\351chettes   :    activ\351\000\000\000",
    "fusil \340 fl\351chettes   : d\351sactiv\351\000\000\000",
    "canon \340 orage        :    activ\351\000\000\000",
    "canon \340 orage        : d\351sactiv\351\000\000\000",
    "fusil d'assaut       :    activ\351\000\000\000",
    "fusil d'assaut       : d\351sactiv\351\000\000\000",
    "fusil \340 plasma       :    activ\351\000\000\000",
    "fusil \340 plasma       : d\351sactiv\351\000\000\000",
    "perceuse c\351r\351brale   :   activ\351e\000\000\000",
    "perceuse c\351r\351brale   :d\351sactiv\351e\000\000\000",
    "lance-grenades       :    activ\351\000\000\000",
    "lance-grenades       : d\351sactiv\351\000\000\000",
    "lance-missiles Scorp.:    activ\351\000\000\000",
    "lance-missiles Scorp.: d\351sactiv\351\000\000\000",
    "lance-torpilles      :    activ\351\000\000\000",
    "lance-torpilles      : d\351sactiv\351\000\000\000",
    "entra\356nement\000\000\000",
    "niveau      :     al\351atoire",
    "niveau      :    tir \340 l'arc\000\000\000",
    "niveau      :   tir",
    "niveau      : d\351cathlon",
    "n\260 de tours :           \000\000\000",
    "commencer partie\000\000\000",
    "pr\351c\351dent\000\000",
    "charger",
    "options",
    "codes triche\000\000\000",
    "point de contr\364le\000\000",
    "point de sauvegarde",
    "options de son\000",
    "volume musique  :d\351sactiv\351\000",
    "volume musique  :      max\000",
    "volume musique  :     norm\000",
    "volume musique  :         \000",
    "volume effets   :d\351sactiv\351\000",
    "volume effets   :      max\000",
    "volume effets   :     norm\000",
    "volume effets   :         \000",
    "volume dialogues:d\351sactiv\351\000",
    "volume dialogues:      max\000",
    "volume dialogues:     norm\000",
    "volume dialogues:         \000",
    "musique         :   aucune\000",
    "musique         :         \000",
    "index           :    aucun\000",
    "dialogues       :    aucun\000",
    "mission accomplie.\000",
    "\351chec.\000",
    "d\351fendre le totem\000\000",
    "vitesse du joueur :            ",
    "vitesse du joueur :      d\351faut",
    "d\351faut\000",
    "sant\351 faible\000\000\000",
    " \000\000",
    "0\000\000",
    "1\000\000",
    "2\000\000",
    "3\000\000",
    "4\000\000",
    "5\000\000",
    "6\000\000",
    "7\000\000",
    "8\000\000",
    { 0x39000000, 0x4D696E69, 0x47616D65, 0x73000000, 0x43686963, 0x6B656E73, 0x20496E20, 0x54686520, 0x4D697374, 0x00000000, 0x57696C6C, 0x69616D20, 0x54656C6C, 0x00000000, 0x54726170, 0x2053686F, 0x6F74696E, 0x67000000, 0x5370616E, 0x6B205468, 0x65204D6F, 0x6E6B6579, 0x00000000, 0x4D6F6E6B, 0x65792042, 0x7573696E, 0x65737300, 0x426F7720, 0x46697368, 0x696E6700, 0x536B6565, 0x74204772, 0x6170706C, 0x65000000, 0x506C6179, 0x6572204F, 0x6E652057, 0x696E7300, 0x506C6179, 0x65722054, 0x776F2057, 0x696E7300, 0x506C6179, 0x65722054, 0x68726565, 0x2057696E, 0x73000000, 0x506C6179, 0x65722046, 0x6F757220, 0x57696E73, 0x00000000, 0x47616D65, 0x20546965, 0x64210000, 0x47657420, 0x52656164, 0x79210000, 0x474F2100 },
    { 0x800C7E88, 0x800C65E0, 0x800C7E74, 0x800C756C, 0x800C65E0, 0x800C7E5C, 0x800C7540, 0x800C65E0, 0x800C65E0, 0x800C7E48, 0x800C7524, 0x800C65E0, 0x800C65E0, 0x800C7510, 0x800C7E28, 0x800C7E08, 0x800C7DE4, 0x800C749C, 0x800C7484, 0x800C7DC8, 0x800C7DA0, 0x800C7D7C, 0x800C7D58, 0x800C7D38, 0x800C7D14, 0x800C73A4, 0x800C7CEC, 0x800C7CC8, 0x800C65E0, 0x800C65E0, 0x800C7C9C, 0x800C65E0, 0x800C7320, 0x800C7310, 0x800C7300, 0x800C72F4, 0x800C72DC, 0x800C65E0, 0x800C65E0, 0x800C7C70, 0x800C65E0, 0x800C72A0, 0x800C7294, 0x800C7288, 0x800C727C, 0x800C726C, 0x800C65E0, 0x800C65E0, 0x800C7C44, 0x800C65E0, 0x800C722C, 0x800C721C, 0x800C65E0, 0x800C65E0, 0x800C7C18, 0x800C65E0, 0x800C71E4, 0x800C71D4, 0x800C71C8, 0x800C65E0, 0x800C65E0, 0x800C7BEC, 0x800C65E0, 0x800C7194, 0x800C7188, 0x800C65E0, 0x800C7178, 0x800C716C, 0x800C65E0, 0x800C65E0, 0x800C7BC0, 0x800C65E0, 0x800C7130, 0x800C7120, 0x800C7110, 0x800C7100, 0x800C70F4, 0x800C70E8, 0x800C70D8, 0x800C65E0, 0x800C65E0, 0x800C7B94, 0x800C65E0, 0x800C7098, 0x800C7080, 0x800C706C, 0x800C7050, 0x800C702C, 0x800C700C, 0x800C6FE8, 0x800C6FD0, 0x800C6FB4, 0x800C6F90, 0x800C65E0, 0x800C65E0, 0x800C7B68, 0x800C65E0, 0x800C7B4C, 0x800C6F34, 0x800C65E0, 0x800C7B38, 0x800C6F10, 0x800C65E0, 0x800C7B20, 0x800C6EDC, 0x800C65E0, 0x800C7B0C, 0x800C722C, 0x800C65E0, 0x800C7AFC, 0x800C71E4, 0x800C65E0, 0x800C7ADC, 0x800C6E88, 0x800C65E0, 0x800C65E0, 0x800C7AC4, 0x800C65E0, 0x800C7AAC, 0x800C6E2C, 0x800C65E0, 0x800C7A98, 0x800C6E04, 0x800C65E0, 0x800C7A8C, 0x800C6DE0, 0x800C65E0, 0x800C7A7C, 0x800C6DAC, 0x800C65E0, 0x800C65E0, 0x800C6D7C, 0x800C65E0, 0x800C6D50, 0x800C6D24, 0x800C65E0, 0x800C65E0, 0x800C7A70, 0x800C6D0C, 0x800C65E0, 0x800C65E0, 0x800C7A60, 0x800C6CE8, 0x800C6CD8, 0x800C65E0, 0x800C65E0, 0x800C7A4C, 0x800C6CB0, 0x800C65E0, 0x800C65E0, 0x800C7A38, 0x800C6C9C, 0x800C65E0, 0x800C65E0, 0x800C7A24, 0x800C6C80, 0x800C6C74, 0x800C65E0, 0x800C65E0, 0x800C7A10, 0x800C6C54, 0x800C6C44, 0x800C65E0, 0x800C65E0, 0x800C79F8, 0x800C6C28, 0x800C6C18, 0x800C65E0, 0x800C65E0, 0x800C79E8, 0x800C6BFC, 0x800C6BF0, 0x800C65E0, 0x800C65E0, 0x800C79BC, 0x800C6BE0, 0x800C6BD0, 0x800C6BC4, 0x800C6BB4, 0x800C6BA4, 0x800C6B94, 0x800C6B84, 0x800C6B78, 0x800C6B68, 0x800C6B5C, 0x800C6B4C, 0x800C6B3C, 0x800C6B2C, 0x800C6B20, 0x800C65E0, 0x800C79A4, 0x800C6AFC, 0x800C65E0, 0x800C7990, 0x800C6AD8, 0x800C65E0, 0x800C7984, 0x800C6AC0, 0x800C6AB0, 0x800C6AA0, 0x800C6A90, 0x800C65E0, 0x800C7968, 0x800C6A68, 0x800C65E0, 0x800C7954, 0x800C6A40, 0x800C6A30, 0x800C65E0, 0x800C7930, 0x800C6A10, 0x800C65E0, 0x800C7914, 0x800C69E4, 0x800C65E0, 0x800C78F8, 0x800C69C4, 0x800C65E0, 0x800C78E8, 0x800C69A8, 0x800C65E0, 0x800C65E0, 0x800C78C4, 0x800C65E0, 0x800C78A8, 0x800C788C, 0x800C7870, 0x800C7858, 0x800C7844, 0x800C7828, 0x800C65E0, 0x800C7804, 0x800C689C, 0x800C77E8, 0x800C77C4, 0x800C779C, 0x800C7778, 0x800C775C, 0x800C7738, 0x800C7714, 0x800C76FC, 0x800C76D4, 0x800C6760, 0x800C76BC, 0x800C76A0, 0x800C7684, 0x800C766C, 0x800C7654, 0x800C66A0, 0x800C667C, 0x800C7648, 0x800C762C, 0x800C761C, 0x800C65E0, 0x800C65E0, 0x800C65E0, 0x800C65E0, 0x800C65E0, 0x800C65E0, 0x800C65E0, 0x800C65E0, 0x800C65E0, 0x800C75F8, 0x00000000, 0x6E657373, 0x756E6F00 },
    { 0x800C7EAC, 0x800C65E0, 0x800C65D0, 0x00000000 },
    "\000\000\000",
    "\000\000\000",
    { 0x800C7EB8, 0x00000000 },
    { 0x800C7ED0, 0x00000000 },
    "2 energia\000\000",
    "10 energia\000",
    "15 energia\000",
    "25 energia\000",
    "50 energia\000",
    "massima energia",
    "ultra energia\000\000",
    "1 forza vitale\000",
    "10 forze vitali",
    "invincibilit\340\000\000",
    "plane walker\000\000\000",
    "flashlight\000",
    "flashlight battery\000",
    "InfraRed Goggles\000\000\000",
    "breath of life\000",
    "eye of truth\000\000\000",
    "leap of faith\000\000",
    "whispers\000\000\000",
    "heart of fire\000\000",
    "blue eagle feather\000",
    "grey eagle feather\000",
    "brown eagle feather",
    "purple eagle feather\000\000\000",
    "red eagle feather\000\000",
    "nuke weapon part\000\000\000",
    "Inversione di sorte!\000\000\000",
    "La Bandiera \350 stata rivendicata",
    "La Bandiera \350 stata catturata\000\000",
    "La bandiera \350 stata restituita\000",
    "Il potere \350 tuo",
    "Funzione non disponibile\000\000\000",
    "MARTELLO DA GUERRA\000",
    "ARTIGLI RAPTOR\000",
    "PICCOLO MORSO\000\000",
    "BOOMERANG\000\000",
    "ARCO TEK\000\000\000",
    "MAG 60\000",
    "FUCILE\000",
    "FUCILE D'ASSALTO\000\000\000",
    "MINIFUCILE\000",
    "FUCILE AL PLASMA\000\000\000",
    "PISTOLA CONGELANTE\000",
    "LANCIAFIAMME\000\000\000",
    "GRANATE",
    "SCORPION\000\000\000",
    "GEL NAPALM\000",
    "EMACIATORE\000",
    "GONFIATORE\000",
    "DISTRUGGI PETTO",
    "NOIA CEREBRALE\000",
    "MINA PFM\000\000\000",
    "ARTIGLI DI FERRO\000\000\000",
    "MINA TELETRASPORTATRICE",
    "TORRETTA DI SENTINELLA\000",
    "SEGNALE RIMOSSO",
    "SEGNATO CON ATTRAZIONE\000",
    "SEGNATO CON REPULSIONE\000",
    "Unisciti al Team Coyote",
    "Unisciti al Team Orso\000\000",
    "Unisciti al Team Puma\000\000",
    "Unisciti al Team Vipera",
    "Ti sei ucciso.\000",
    "Mutilato da %s.",
    "Ucciso da %s.\000\000",
    "Sculacciato da %s.\000",
    "%s ti ha obliterato.\000\000\000",
    "%s ti ha battuto.\000\000",
    "%s ti ha linciato.\000",
    "Imprigionato da %s.",
    "E il livello colpisce.\000",
    "Oops...",
    "Cattiva mossa...\000\000\000",
    "Um... fai attenzione\000\000\000",
    "Oops...",
    "Sei stato superato.",
    "Munch.\000",
    "Embrione impiantato",
    "Embrione distrutto\000",
    "Uccidi %s\000\000",
    "o trova il nucleo della potenza",
    "cariche energetiche",
    "cariche energetiche",
    "cariche pallottole\000",
    "cariche pallottole\000",
    "cariche esplosive\000\000",
    "cariche esplosive\000\000",
    "Pacchetto di munizioni\000",
    "pallottola\000",
    "carica energetica\000\000",
    "carica esplosiva\000\000\000",
    "noia cerebrale\000",
    "mina pfm\000\000\000",
    "torretta di sentinella\000",
    "artigli di ferro\000\000\000",
    "mina teletrasportatrice",
    "Tempo rallentato...",
    "Scudo esplosivo...\000",
    "Rigenerazione...\000\000\000",
    "Pietrificazione...\000",
    "Inversione dei danni...",
    "Invisibilit\340...",
    "Forza vitale del vampiro...",
    "Scatto...\000\000",
    "Teletrasporto...\000\000\000",
    "Teletrasportato alla salvezza...(?)",
    "Danno ingente...\000\000\000",
    "Invulnerabilit\340...\000",
    "Scudo da proiettili...\000",
    "Assorbimento energia...",
    "Something Else...\000\000",
    "Scudo\000\000",
    "NOVIZIO",
    "NUOVO ARRIVATO\000",
    "GRUGNITO\000\000\000",
    "SCOUT\000\000",
    "CORAGGIOSO\000",
    "PERLUSTRATORE\000\000",
    "CACCIATORE\000",
    "GUERRIERO\000\000",
    "OSCURO\000",
    "INSEGUITORE",
    "ASSASSINO\000\000",
    "FLAGELLO\000\000\000",
    "SIGNORE DELLA GUERRA\000\000\000",
    "VENTO DI MORTE\000",
    "CONQUISTATORE\000\000",
    "MAESTRO",
    "TIRANNO",
    "SCHIAVO DELLA GUERRA\000\000\000",
    "MANO DI DIO",
    "CONDOTTIERO",
    "SUCCESSO: PROVING GROUNDS\000\000",
    "SUCCESSO: BASIC TRAINING\000\000\000",
    "SUCCESSO: CROSSROADS\000\000\000",
    "SUCCESSO: GRIM RETREAT\000",
    "SUCCESSO: CATHEDRAL",
    "SUCCESSO: FALLOUT\000\000",
    "SUCCESSO: BOXED SET",
    "SUCCESSO: DIRE STRAIGHT",
    "SUCCESSO: PREY\000",
    "SUCCESSO: WAREHOUSE",
    "SUCCESSO: WATER TEMPLE\000",
    "SUCCESSO: BOMB SHELTER\000",
    "SUCCESSO: TEMPERED\000",
    "SUCCESSO: EARTH TEMPLE\000",
    "SUCCESSO: FIRE TEMPLE\000\000",
    "SUCCESSO: MYSTIC\000\000\000",
    "SUCCESSO: BOTTLENECK\000\000\000",
    "SUCCESSO: TIGHTROPE",
    "SUCCESSO: THE PIT\000\000",
    "SUCCESSO: LEAP OF FAITH",
    "SUCCESSO: WICKED DANCE\000",
    "SUCCESSO: BUNKER\000\000\000",
    "SUCCESSO: AMPHITHEATER\000",
    "SUCCESSO: FIRE WALKER\000\000",
    "SUCCESSO: CRYPTS\000\000\000",
    "SUCCESSO: BREAKDOWN",
    "SUCCESSO: RETALIATION\000\000",
    "SUCCESSO: HOPELESS\000",
    "SUCCESSO: MATRIX\000\000\000",
    "SUCCESSO: FATHOM\000\000\000",
    "SUCCESSO: THE PEDESTAL\000",
    "SUCCESSO: DEFCON 5\000",
    "SUCCESSO: SPIRIT TEMPLE",
    "SUCCESSO: STRONGHOLD\000\000\000",
    "SUCCESSO: COURTYARD",
    "SUCCESSO: STARLIGHT",
    "OTTENUTE 15 UCCISIONI IN 5 MINUTI \000",
    "OTTENUTE 25 UCCISIONI IN 10 MINUTI\000",
    "NESSUNA UCCISIONE OTTENUTA\000",
    "UCCISO TE STESSO 5 VOLTE\000\000\000",
    "ARRIVATO IN ULTIMA\000",
    "PREMIO UCCISIONI TOTALI",
    "PREMIO MORTE TOTALE",
    "UCCISE 10 PERSONE IN UN ROUND\000\000",
    "MAI STATO UCCISO IN UN ROUND\000\000\000",
    "SCONFITTO BASTILLE\000",
    "SCONFITTO SYRA\000",
    "SCONFITTO SYMBIONT\000",
    "SCONFITTO TAL SET\000\000",
    "SCONFITTO LO SCENARIO COOPERATIVO\000\000",
    "<VUOTO>",
    "<NUOVO GIOCATORE>\000\000",
    "TUROK\000\000",
    "WARRIOR",
    "MASTER\000",
    "ADON\000\000\000",
    "SEEKER\000",
    "HUNTRESS\000\000\000",
    "CAMPAIN",
    "SLAVER\000",
    "TYRANT\000",
    "FIREBORN\000\000\000",
    "ICELORD",
    "ENTRAIL",
    "MITES\000\000",
    "COMPIES",
    "TEDDIES",
    "JUGGNAUT\000\000\000",
    "SLOTH\000\000",
    "MAULER\000",
    "DRONE\000\000",
    "GRUNT\000\000",
    "SLAVE\000\000",
    "SOLDIER",
    "CAPTAIN",
    "KING\000\000\000",
    "BASTILLE\000\000\000",
    "TAL SET",
    "SYRA\000\000\000",
    "SYMBIONT\000\000\000",
    "GUARDIAN\000\000\000",
    "RAVAGE\000",
    "CYCLOPS",
    "LORDDEAD\000\000\000",
    "MAGGOT\000",
    "VILE\000\000\000",
    "ELITE\000\000",
    "BIOBOT\000",
    "KILLBOT",
    "DEATH\000\000",
    "REAPER\000",
    "MAW",
    "RAPTOR\000",
    "SLAG\000\000\000",
    "CLAW\000\000\000",
    "WARCLUBS\000\000\000",
    "TUROK\000\000",
    "MANTID DRONE\000\000\000",
    "CAMPAIGNER\000",
    "FIREBORN\000\000\000",
    "MANTID SOLDIER\000",
    "ADON\000\000\000",
    "LORD OF THE DEAD\000\000\000",
    "ELITE GUARD",
    "GUARDIAN\000\000\000",
    "JUGGERNAUT\000",
    "OBLIVION SPAWN\000",
    "BASTILLE\000\000\000",
    "SYRA\000\000\000",
    "SYMBIONT\000\000\000",
    "TAL SET",
    "RAPTOR\000",
    "MANTID MITES\000\000\000",
    "catturata la bandiera %d volta\000",
    "catturata la bandiera %d volte\000",
    "acquisite %d catture di team\000\000\000",
    "toccata la scimmia %d volta",
    "toccata la scimmia %d volte",
    "acquisiti %d tocchi di creatura",
    "acquisita %d uccisione\000",
    "acquisite %d uccisioni\000",
    "acquisita %d uccisione di squadra\000\000",
    "acquisite %d uccisioni di squadra\000\000",
    "in %02d secondi o meno\000",
    "in %d minuto e %02d secondi o meno\000",
    "in %d minuti e %02d secondi o meno\000",
    "in %d minuto o meno",
    "in %d minuti o meno",
    "con %d vita",
    "con %d vite",
    "sconfitto %s\000\000\000",
    "sconfitto sia %s che %s",
    "ognuno per s\351\000\000",
    "FACILE\000",
    "MEDIO\000\000",
    "DIFFICILE\000\000",
    "OFF",
    "ON\000",
    "ROSSO\000\000",
    "VERDE\000\000",
    "ORIZZONTALE",
    "VERTICALE\000\000",
    "BASSARIS\000\000\000",
    "ALTARIS",
    "CASELLA TESTO\000\000",
    "NO\000",
    "Sl\000",
    "NOVIZIO",
    "FACILE\000",
    "NORMALE",
    "VETERANO\000\000\000",
    "ESPERTO",
    "ARCADE\000",
    "RUOTA\000\000",
    "TOCCO\000\000",
    "MISTO\000\000",
    "CONTROLLER  %d\000",
    "CATTURA LA BANDIERA",
    "SQUADRA BLOOD LUST\000",
    "BLOOD LUST\000",
    "FRAG TAG\000\000\000",
    "GUANTO\000",
    "FRAG FEST\000\000",
    "GARA A TEMPO\000\000\000",
    "GIOCATORE%d",
    "ACQUISITO IL TALISMANO DELL'AQUILA. IL CONTEGGIO VITALE AUMENTA DI 1!\000\000",
    "ACQUISITA META' DEL TALISMANO DELL'AQUILA. COLLEZIONA L'ALTRA MET\300 PER GUADAGNARE 1 VITA\000\000\000",
    "ACQUISITO L'ALTRO TALISMANO DELL'AQUILA. GUADAGNI 1 VITA!\000\000",
    "ACQUISITO IL TALISMANO DELL'ORSO. LA SCORTA DI MUNIZIONI ESPLOSIVE AUMENTA DI 5",
    "ACQUISITO IL TALISMANO DEL COYOTE. LA SCORTA DI PROIETTILI AUMENTA DI 50\000\000\000",
    "ACUISITO IL TALISMANO DEL PUMA. LA SCORTA DI MUNIZIONI ENERGETICHE AUMENTA DI 50\000\000\000",
    "ACQUISITO IL TALISMANO DELLA VIPERA. L'ENERGIA MASSIMA AUMENTA DI 5",
    "ACQUISITO IL TALISMANO COOPERATIVO\000",
    "ACQUISITO IL TALISMANO MINIGIOCO\000\000\000",
    "ACQUISITO IL FUCILE D'ASSALTO\000\000",
    "ACQUISITO POTENZIAMENTO PER IL FUOCO RAPIDO DEL FUCILE D'ASSALTO\000\000\000",
    "ACQUISITO IL MIRINO PER L'ARCO\000",
    "ACQUISITO IL LANCIAGRANATE\000",
    "ACQUISITO IL POTENZIAMENTO LANCIAGRANATE\000\000\000",
    "ACQUISITO FUCILE AL PLASMA\000",
    "ACQUISITO IL MIRINO PER IL FUCILE AL PLASMA",
    "ACQUISITO L'ATTACCO CON SPUTO D'ACIDO\000\000",
    "ACQUISITO L'ATTACCO VOLANTE CON ARTIGLI",
    "ACQUISITA LA PISTOLA A RAZZI RADIOATTIVI\000\000\000",
    "ACQUISITO POTENZIAMENTO PER PISTOLA A RAZZI RADIOATTIVI",
    "ACQUISITO IL LANCIARAZZI SCORPION\000\000",
    "ACQUISITO IL POTENZIAMENTO MAGNETICO PER LANCIARAZZI SCORPION\000\000",
    "ACQUISITA LA PISTOLA CONGELANTE",
    "ACQUISITO IL POTENZIAMENTO PISTOLA CONGELANTE\000\000",
    "ACQUISITO IL GEL AL NAPALM\000",
    "ACQUISITO IL POTENZIAMENTO VISTA LASER PER MAG 60\000\000",
    "ACQUISITO IL DISTRUGGI PETTO\000\000\000",
    "ACQUISITO IL GONFIATORE",
    "ACQUISITO IL POTENZIAMENTO PER GONFIATORE\000\000",
    "ACQUISITO IL BOOMERANG\000",
    "ACQUISITO IL POTENZIAMENTO BOOMERANG\000\000\000",
    "ACQUISITO IL MINIFUCILE",
    "ACQUISITO IL POTENZIAMENTO SCUDO PERSONALE PER MINIFUCILE\000\000",
    "ACQUISITO IL POTENZIAMENTO SPAZZASTRADA PER FUCILE\000",
    "ACQUISITO EMACIATORE\000\000\000",
    "ACQUISITO IL POTENZIAMENTO PER EMACIATORE\000\000",
    "ACQUISITO IL RAZZO DI POTENZIAMENTO PER IL MARTELLO DA GUERRA\000\000",
    "HAI SBLOCCATO %s\000\000\000",
    "MISSIONE FALLITA\000\000\000",
    "OGGETTO PRECEDENTEMENTE ACQUISITO\000\000",
    "TEAM\000\000\000",
    "COLPITO%\000\000\000",
    "TOCCHI\000",
    "BANDIERE\000\000\000",
    "CONGRATULAZIONI! HAI COMPLETATO IL FRAG FEST\000\000\000",
    "CONGRATULAZIONI! HAI COMPLETATO LA GARA A TEMPO",
    "ITALIANO\000\000\000",
    "pistol clip (10 rounds)",
    "rifle clip (10 rounds)\000",
    "difficulty   :     easy",
    "difficulty   :   normal",
    "difficulty   :     hard",
    "control type :   expert",
    "control type :   arcade",
    "control type :   ??????",
    "control side :     left",
    "control side :    right",
    "look spring  :       on",
    "look spring  :      off",
    "auto aim     :       on",
    "auto aim     :      off",
    "blood color  :      off",
    "blood color  :      red",
    "blood color  :    green",
    "2 plyr layout:     horz",
    "2 plyr layout:     vert",
    "opacity      :    clear",
    "opacity      :   opaque",
    "opacity      :         ",
    "control stick horz:norm",
    "control stick horz:    ",
    "control stick vert:norm",
    "control stick vert:    ",
    "Weapon Select:    quick",
    "Weapon Select:     norm",
    "Resolution   :   lo-rez",
    "Resolution   :   hi-rez",
    "Resolution   :hi-rez-lb",
    "Resolution   :sm-lo-rez",
    "Resolution   :lo-rez-lb",
    "brightness   :     norm",
    "brightness   :         ",
    "language     :  english",
    "go back",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "choose\000",
    "blue blood\000",
    "red blood\000\000",
    "final score",
    "blue blood score :    \000",
    " red blood score :    \000",
    "please wait.....\000\000\000",
    "paused\000",
    "resume game",
    "mission status\000",
    "mission objectives\000",
    "inventory\000\000",
    "load\000\000\000",
    "options",
    "cheats\000",
    "quit\000\000\000",
    "inventory\000\000",
    "ok\000",
    "RAGE WARS\000\000",
    "TUROK 2",
    "51\000",
    "NRWX\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "ALTRA PARTITA\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "note info\000\000",
    "delete note",
    "difficulty :  easy\000",
    "difficulty :normal\000",
    "difficulty :  hard\000",
    "health     :      \000",
    "lives      :      \000",
    "time :000.00.00",
    "note info\000\000",
    "delete note",
    "delete note",
    "name             ext \000\000",
    "                     \000\000",
    "name  :            ",
    "type  :            ",
    "frags :            ",
    "rank  :            ",
    "load?\000\000",
    "delete?",
    "delete?",
    "error\000\000",
    "important\000\000",
    "ok\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "   save",
    "   load",
    " health",
    "   ammo",
    "go back",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "\000\000\000",
    "pmf shot!\000\000",
    "body shot!\000",
    "head shot!\000",
    "arm shot!\000\000",
    "edit\000\000\000",
    { 0x02000000 },
    { 0x03000000 },
    { 0x04000000 },
    "tagged by \000",
    "you tagged ",
    "killed by \000",
    "you killed ",
    "you killed yourself",
    "you lost the flag!!!\000\000\000",
    "He dropped the flag!!!\000",
    "are you sure?\000\000",
    "you want to",
    "yes",
    "no\000",
    "cheats\000",
    "load\000\000\000",
    "save\000\000\000",
    "enter cheat",
    "join now\000\000\000",
    "waiting..\000\000",
    "connect..\000\000",
    "go back",
    "continue ?\000",
    "game over\000\000",
    "time : xx\000\000",
    "done\000\000\000",
    "new cheat enabled\000\000",
    "invincibility activated",
    "infinite lives activated\000\000\000",
    "all weapons activated\000\000",
    "unlimited ammo activated\000\000\000",
    "all keys activated\000",
    "big head mode activated",
    "tiny mode activated",
    "stick mode activated\000\000\000",
    "big hands and feet mode activated\000\000",
    "pen and ink mode activated\000",
    "gouraud mode activated\000",
    "juans cheat activated\000\000",
    "zach attack cheat activated",
    "all map activated\000\000",
    "blackout mode activated",
    "mmmm... tasty frooty stripes\000\000\000",
    "warp level 1 activated\000",
    "warp level 2 activated\000",
    "warp level 3 activated\000",
    "warp level 4 activated\000",
    "warp level 5 activated\000",
    "warp level 6 activated\000",
    "warp queen boss activated\000\000",
    "warp blind one boss activated\000\000",
    "warp mother boss activated\000",
    "warp primagen boss activated\000\000\000",
    "warp credits activated\000",
    "invincibility         :  on",
    "invincibility         : off",
    "infinite lives        :  on",
    "infinite lives        : off",
    "all weapons           :  on",
    "all weapons           : off",
    "unlimited ammo        :  on",
    "unlimited ammo        : off",
    "all special objects   :  on",
    "all special objects   : off",
    "big head mode         :  on",
    "big head mode         : off",
    "tiny mode             :  on",
    "tiny mode             : off",
    "stick mode            :  on",
    "stick mode            : off",
    "big hands / feet mode :  on",
    "big hands / feet mode : off",
    "pen and ink mode      :  on",
    "pen and ink mode      : off",
    "gouraud mode          :  on",
    "gouraud mode          : off",
    "juans cheat           :  on",
    "juans cheat           : off",
    "zach attack cheat     :  on",
    "zach attack cheat     : off",
    "all map               :  on",
    "all map               : off",
    "blackout              :  on",
    "blackout              : off",
    "frooty stripes        :  on",
    "frooty stripes        : off",
    "warp:          port of adia",
    "warp:        river of souls",
    "warp:         death marshes",
    "warp:lair of the blind ones",
    "warp:   hive of the mantids",
    "warp:  primagen's lightship",
    "warp:            queen boss",
    "warp:        blind one boss",
    "warp:           mother boss",
    "warp:         primagen boss",
    "warp:               credits",
    "you fragged",
    "you tagged\000",
    "totals\000",
    "one     :0000                \000\000",
    "two     :0000                \000\000",
    "three   :0000                \000\000",
    "four    :0000                \000\000",
    "tags    :0000                \000\000",
    "frags   :0000                \000\000",
    "deaths  :0000                \000\000",
    "suicides:0000\000\000",
    "one     :0000                \000\000",
    "two     :0000                \000\000",
    "three   :0000                \000\000",
    "four    :0000                \000\000",
    "tags    :0000\000\000",
    "frags   :0000\000\000",
    "deaths  :0000\000\000",
    "suicides:0000\000\000",
    "one     :0000                \000\000",
    "two     :0000                \000\000",
    "three   :0000                \000\000",
    "four    :0000                \000\000",
    "tags    :0000\000\000",
    "frags   :0000\000\000",
    "deaths  :0000\000\000",
    "suicides:0000\000\000",
    "one     :0000                \000\000",
    "two     :0000                \000\000",
    "three   :0000                \000\000",
    "four    :0000                \000\000",
    "tags    :0000\000\000",
    "frags   :0000\000\000",
    "deaths  :0000\000\000",
    "suicides:0000\000\000",
    "player 1\000\000\000",
    "player 2\000\000\000",
    "player 3\000\000\000",
    "player 4\000\000\000",
    "single\000",
    "new game\000\000\000",
    "load\000\000\000",
    "multi\000\000",
    "deathmatch\000",
    "select game type\000\000\000",
    "blood lust\000",
    "blood lust\000",
    "timed game       :none\000",
    "frag limit       :none\000",
    "level:          random\000",
    "level:   experimentata\000",
    "level:  moonlit mayhem\000",
    "level: close quartered\000",
    "level:  vulcan's forge\000",
    "level:   teleportastic\000",
    "level:     mirrororrim\000",
    "level:fish in a barrel\000",
    "level:       h 2 whoa!\000",
    "level:        escheria\000",
    "level:      mosh crypt\000",
    "level:   squares cubed\000",
    "level:     crazy eight\000",
    "level:        bullseye\000",
    "texture set:    castle\000",
    "texture set:steel mill\000",
    "texture set:  oak fort\000",
    "texture set: catacombs\000",
    "texture set: jailhouse\000",
    "texture set:  big city\000",
    "texture set:red dragon\000",
    "texture set: paintball\000",
    "texture set:  mr happy\000",
    "crosshairs       :  on\000",
    "crosshairs       : off\000",
    "start game\000",
    "go back",
    "frag tag\000\000\000",
    "frag tag\000\000\000",
    "tag limit        :none\000",
    "level:       madhouse!\000",
    "level:            snap\000",
    "level:sneaks n ladders\000",
    "level:      primattica\000",
    "level:       crossfire\000",
    "level:  y.n.g.w.t.s.f.\000",
    "team blood\000",
    "customize weapons\000\000",
    "charge dart rifle : on\000",
    "charge dart rifle :off\000",
    "firestorm         : on\000",
    "firestorm         :off\000",
    "assault rifle     : on\000",
    "assault rifle     :off\000",
    "plasma rifle      : on\000",
    "plasma rifle      :off\000",
    "cerebral bore     : on\000",
    "cerebral bore     :off\000",
    "grenade launcher  : on\000",
    "grenade launcher  :off\000",
    "scorpion launcher : on\000",
    "scorpion launcher :off\000",
    "torpedo launcher  : on\000",
    "torpedo launcher  :off\000",
    "training\000\000\000",
    "level      :    random\000",
    "level      :   archery\000",
    "level      :  shooting\000",
    "level      :decathalon\000",
    "no of laps :          \000",
    "start game\000",
    "go back",
    "load\000\000\000",
    "options",
    "cheats\000",
    "check point",
    "save point\000",
    "sound options\000\000",
    "music volume  :   off\000\000",
    "music volume  :   max\000\000",
    "music volume  :  norm\000\000",
    "music volume  :      \000\000",
    "sfx volume    :   off\000\000",
    "sfx volume    :   max\000\000",
    "sfx volume    :  norm\000\000",
    "sfx volume    :      \000\000",
    "speech volume :   off\000\000",
    "speech volume :   max\000\000",
    "speech volume :  norm\000\000",
    "speech volume :      \000\000",
    "music         :  none\000\000",
    "music         :      \000\000",
    "index        :  none\000\000\000",
    "speech       :  none\000\000\000",
    "mission complete.\000\000",
    "mission failed.",
    "defend the totem\000\000\000",
    "player speed :        \000",
    "player speed : default\000",
    "default",
    "low health\000",
    " \000\000",
    "0\000\000",
    "1\000\000",
    "2\000\000",
    "3\000\000",
    "4\000\000",
    "5\000\000",
    "6\000\000",
    "7\000\000",
    "8\000\000",
    "9\000\000",
    { 0x800C7588, 0x800C65E0, 0x800C8894, 0x800C756C, 0x800C65E0, 0x800C8880, 0x800C7540, 0x800C65E0, 0x800C65E0, 0x800C8870, 0x800C7524, 0x800C65E0, 0x800C65E0, 0x800C7510, 0x800C8850, 0x800C8830, 0x800C880C, 0x800C749C, 0x800C7484, 0x800C87F0, 0x800C87C8, 0x800C87A4, 0x800C8780, 0x800C8760, 0x800C873C, 0x800C73A4, 0x800C8714, 0x800C86F0, 0x800C65E0, 0x800C65E0, 0x800C86C4, 0x800C65E0, 0x800C7320, 0x800C7310, 0x800C7300, 0x800C72F4, 0x800C86A0, 0x800C65E0, 0x800C65E0, 0x800C8670, 0x800C65E0, 0x800C72A0, 0x800C7294, 0x800C7288, 0x800C727C, 0x800C726C, 0x800C65E0, 0x800C65E0, 0x800C8648, 0x800C65E0, 0x800C722C, 0x800C721C, 0x800C65E0, 0x800C65E0, 0x800C8620, 0x800C65E0, 0x800C71E4, 0x800C71D4, 0x800C71C8, 0x800C65E0, 0x800C65E0, 0x800C85EC, 0x800C65E0, 0x800C85CC, 0x800C7188, 0x800C65E0, 0x800C85B8, 0x800C716C, 0x800C65E0, 0x800C65E0, 0x800C858C, 0x800C65E0, 0x800C7130, 0x800C7120, 0x800C7110, 0x800C7100, 0x800C70F4, 0x800C70E8, 0x800C70D8, 0x800C65E0, 0x800C65E0, 0x800C8560, 0x800C65E0, 0x800C7098, 0x800C7080, 0x800C706C, 0x800C7050, 0x800C702C, 0x800C700C, 0x800C6FE8, 0x800C6FD0, 0x800C6FB4, 0x800C6F90, 0x800C65E0, 0x800C65E0, 0x800C8534, 0x800C65E0, 0x800C8510, 0x800C6F34, 0x800C65E0, 0x800C84FC, 0x800C6F10, 0x800C65E0, 0x800C84D4, 0x800C6EDC, 0x800C65E0, 0x800C84C0, 0x800C722C, 0x800C65E0, 0x800C84AC, 0x800C71E4, 0x800C65E0, 0x800C8488, 0x800C6E88, 0x800C65E0, 0x800C65E0, 0x800C845C, 0x800C65E0, 0x800C8430, 0x800C6E2C, 0x800C65E0, 0x800C8410, 0x800C6E04, 0x800C65E0, 0x800C83FC, 0x800C6DE0, 0x800C65E0, 0x800C83D8, 0x800C6DAC, 0x800C65E0, 0x800C65E0, 0x800C83A4, 0x800C65E0, 0x800C8374, 0x800C8344, 0x800C65E0, 0x800C65E0, 0x800C8338, 0x800C6D0C, 0x800C65E0, 0x800C65E0, 0x800C8320, 0x800C6CE8, 0x800C6CD8, 0x800C65E0, 0x800C65E0, 0x800C8300, 0x800C6CB0, 0x800C65E0, 0x800C65E0, 0x800C85CC, 0x800C6C9C, 0x800C65E0, 0x800C65E0, 0x800C82E0, 0x800C6C80, 0x800C6C74, 0x800C65E0, 0x800C65E0, 0x800C82D0, 0x800C6C54, 0x800C6C44, 0x800C65E0, 0x800C65E0, 0x800C82C4, 0x800C6C28, 0x800C6C18, 0x800C65E0, 0x800C65E0, 0x800C6C08, 0x800C6BFC, 0x800C6BF0, 0x800C65E0, 0x800C65E0, 0x800C858C, 0x800C6BE0, 0x800C6BD0, 0x800C6BC4, 0x800C6BB4, 0x800C6BA4, 0x800C6B94, 0x800C6B84, 0x800C6B78, 0x800C6B68, 0x800C6B5C, 0x800C6B4C, 0x800C6B3C, 0x800C6B2C, 0x800C6B20, 0x800C65E0, 0x800C82AC, 0x800C6AFC, 0x800C65E0, 0x800C8298, 0x800C6AD8, 0x800C65E0, 0x800C8290, 0x800C6AC0, 0x800C6AB0, 0x800C6AA0, 0x800C6A90, 0x800C65E0, 0x800C8278, 0x800C6A68, 0x800C65E0, 0x800C8264, 0x800C6A40, 0x800C6A30, 0x800C65E0, 0x800C8254, 0x800C6A10, 0x800C65E0, 0x800C8238, 0x800C69E4, 0x800C65E0, 0x800C8224, 0x800C69C4, 0x800C65E0, 0x800C8214, 0x800C69A8, 0x800C65E0, 0x800C65E0, 0x800C81E4, 0x800C65E0, 0x800C81BC, 0x800C81A4, 0x800C8190, 0x800C8174, 0x800C8158, 0x800C8138, 0x800C65E0, 0x800C8108, 0x800C689C, 0x800C80E8, 0x800C80C4, 0x800C80A0, 0x800C6814, 0x800C807C, 0x800C8058, 0x800C8030, 0x800C801C, 0x800C7FF4, 0x800C6760, 0x800C7FE0, 0x800C7FBC, 0x800C7FA0, 0x800C7F78, 0x800C7F44, 0x800C66A0, 0x800C667C, 0x800C7F3C, 0x800C7F20, 0x800C7F0C, 0x800C65E0, 0x800C65E0, 0x800C65E0, 0x800C65E0, 0x800C65E0, 0x800C65E0, 0x800C65E0, 0x800C65E0, 0x800C65E0, 0x800C7EE4, 0x00000000, 0x00000000, 0x800DCA70, 0x800DCA70, 0x800DCA70, 0x800DCA70 },
    { 0x800CF980, 0x800D334C, 0x800D8D4C },
};
#endif
#if defined(VERSION_EU)
extern EuScreenMessageTextData s_SkyPostscaledscreenmessageScreenMessageTextEu;
#endif
#if !(defined(VERSION_US_REV1))
const char s_fadeOutCinemaTextHint[36] =
    "<use this to fade out cinema text>\000\000";
#endif

#if defined(VERSION_EU_X)
extern struct ParticleQuadRenderSetup {
    unsigned int words0[70];
    char text1[8];
} g_particleQuadRenderSetup;
#endif

#if defined(VERSION_EU_X)
GfxdataEncodedWordsLayout g_GfxdataEncodedWords = {
    { (void *)&g_screenMessageSubstitutionSource, (void *)&g_screenMessageSubstitutionSource, (void *)&g_screenMessageSubstitutionSource, (void *)&g_screenMessageSubstitutionSource, (void *)&k_SkyPostscaledscreenmessageEncodedWords.screenMessageSetupWords[303], (void *)&k_SkyPostscaledscreenmessageEncodedWords.controllerPakTextLinks[1], (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.screenMessageLinkWords_repeat10, (void *)&k_SkyPostscaledscreenmessageEncodedWords.screenMessageSetupWords[307], (void *)&k_SkyPostscaledscreenmessageEncodedWords.controllerPakTextLinks[5], (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat200, (void *)&k_SkyPostscaledscreenmessageEncodedWords.screenMessageSetupWords[308], (void *)&k_SkyPostscaledscreenmessageEncodedWords.controllerPakTextLinks[6], (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat201, (void *)&k_SkyPostscaledscreenmessageEncodedWords.screenMessageSetupWords[309], (void *)&k_SkyPostscaledscreenmessageEncodedWords.controllerPakTextLinks[7], (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.screenMessageLinkWords_repeat11, (void *)&k_SkyPostscaledscreenmessageEncodedWords.screenMessageSetupWords[311], (void *)&k_SkyPostscaledscreenmessageEncodedWords.controllerPakTextLinks[9], (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.screenMessageLinkWords_repeat12,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat885, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text2Energia,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat886, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text10Energia,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat887, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text15Energia,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat888, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text25Energia,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat5, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat889, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text50Energia, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat6, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat890, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMassimaEnergia, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat7, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat891, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textUltraEnergia, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat8, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat892, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text1ForzaVitale, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat9, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat893, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text10ForzeVitali,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat10, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat894, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInvincibilit,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat11, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat895, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPlaneWalker,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat12, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat896, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFlashlight, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat13, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat897, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFlashlightBattery,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat14, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat898, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInfraredGoggles, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat15, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat899, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBreathOfLife,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat16, (void *)&k_SkyPostscaledscreenmessageEncodedWords.textOeil, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEyeOfTruth, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat17, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat901, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLeapOfFaith,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat18, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat902, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWhispers,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat19, (void *)&k_SkyPostscaledscreenmessageEncodedWords.textCoeur, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textHeartOfFire,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat20, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat904, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBlueEagleFeather,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat21, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat905, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGreyEagleFeather,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat22, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat906, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBrownEagleFeather,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat23, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat907, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPurpleEagleFeather,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat24, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat908, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRedEagleFeather, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat25, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPiCeDeLArmeNuclAire, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNukeWeaponPart,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat26, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textReprSailles, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInversioneDiSorte, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat27, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLeDrapeauATAttaqu, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLaBandieraStataRivendicata, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat28, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLeDrapeauATCaptur, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLaBandieraStataCatturata, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat29, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLeDrapeauATReconquis, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLaBandieraStataRestituita, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat30, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.screenMessageLinkWords, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textIlPotereTuo, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat31, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat909, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFunzioneNonDisponibile, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat32, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat910, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMartelloDaGuerra, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat33, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat911, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textArtigliRaptor, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat34, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat912, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPiccoloMorso, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat35, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat913, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBoomerang, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat36, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat914, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textArcoTek, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat37, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat915, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMag60, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat38, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat916, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFucile, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat39, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat917, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFucileDAssalto, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat40, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat918, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMinifucile, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat41, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat919, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFucileAlPlasma, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat42, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat920, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPistolaCongelante, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat43, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat921, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLanciafiamme, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat44, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat922, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGranate, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat45, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat923, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textScorpion, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat46, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat924, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGelNapalm, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat47, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat925, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEmaciatore, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat48, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat926, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGonfiatore, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat49, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat927, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDistruggiPetto, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat50, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat928, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNoiaCerebrale,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat51, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat929, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMinaPfm,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat52, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat930, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textArtigliDiFerro, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat53, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat931, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMinaTeletrasportatrice,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat54, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat932, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTorrettaDiSentinella, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat55, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat933, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSegnaleRimosso, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat56, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat934, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSegnatoConAttrazione, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat57, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat935, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSegnatoConRepulsione, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat96, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat974, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTempoRallentato, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat97, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat975, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textScudoEsplosivo, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat98, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat976, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRigenerazione, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat99, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat977, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPietrificazione, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat100, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat978, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInversioneDeiDanni, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat101, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat979, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInvisibilit, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat102, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat980, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textForzaVitaleDelVampiro, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat103, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat981, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textScatto, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat104, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat982, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTeletrasporto, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat105, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat983, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTeletrasportatoAllaSalvezza, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat106, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat984, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDannoIngente, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat107, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInvulnRabilit, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInvulnerabilit, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat108, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBouclierPareBalles, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textScudoDaProiettili, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat109, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAbsorptionDNergie, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAssorbimentoEnergia, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat110, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textQuelqueChoseDAutre, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSomethingElse, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat111, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBouclier, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textScudo, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat58, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat936, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textUniscitiAlTeamCoyote, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat59, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat937, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textUniscitiAlTeamOrso, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat60, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat938, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textUniscitiAlTeamPuma, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat61, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat939, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textUniscitiAlTeamVipera, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat62, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat940, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTiSeiUcciso, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat63, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat941, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMutilatoDaS, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat64, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat942, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textUccisoDaS, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat65, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat943, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSculacciatoDaS, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat66, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat944, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSTiHaObliterato, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat67, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat945, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSTiHaBattuto, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat68, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat946, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSTiHaLinciato, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat69, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat947, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textImprigionatoDaS, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat70, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat948, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEIlLivelloColpisce, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat71, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat949, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOops, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat72, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat950, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCattivaMossa, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat73, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat951, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textUmFaiAttenzione, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat76, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat952, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMunch, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat74, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat953, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOops_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat75, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat954, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSeiStatoSuperato, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat77, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat955, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEmbrioneImpiantato, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat78, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat956, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEmbrioneDistrutto, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat79, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat957, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textUccidiS, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat80, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat958, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOTrovaIlNucleoDellaPotenza,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat81, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat959, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCaricheEnergetiche,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat82, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat960, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCaricheEnergetiche_repeat2,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat83, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat961, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCarichePallottole,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat84, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat962, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCarichePallottole_repeat2,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat85, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat963, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCaricheEsplosive,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat86, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat964, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCaricheEsplosive_repeat2,
      (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat87, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat965, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPacchettoDiMunizioni, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat88, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat966, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPallottola, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat89, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat967, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCaricaEnergetica, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat90, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat968, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCaricaEsplosiva, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat91, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat969, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNoiaCerebrale_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat92, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat970, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMinaPfm_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat93, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat971, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTorrettaDiSentinella_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat94, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat972, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textArtigliDiFerro_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat95, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat973, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMinaTeletrasportatrice_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat112, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNovice, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNovizio, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat113, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDebutant, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNuovoArrivato, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat114, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCombattant, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGrugnito, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat115, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEclaireur, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textScout, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat116, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBrave, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCoraggioso, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat117, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTraqueur, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPerlustratore, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat118, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textChasseur, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCacciatore, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat119, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGuerrier, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGuerriero, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat120, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textChevalierNoir, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOscuro, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat121, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMaraudeur, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInseguitore, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat122, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAssassin, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAssassino, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat123, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFleau, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFlagello, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat124, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSeigneurDeGuerre, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSignoreDellaGuerra, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat125, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVentDeMort, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVentoDiMorte, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat126, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textConquerant, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textConquistatore, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat127, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMaitre, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMaestro, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat128, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTyran, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTiranno, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat129, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFouDeGuerre, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSchiavoDellaGuerra, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat130, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMainDeDieu, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textManoDiDio, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat131, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textChefDeClan, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCondottiero, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat182, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVide, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVuoto, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat183, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNouveauJoueur, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNuovoGiocatore, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat184, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTurok, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTurok_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat185, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarrior, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarrior_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat186, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMaster, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMaster_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat187, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAdon, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAdon_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat188, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSeeker, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSeeker_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat189, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textHuntress, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textHuntress_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat190, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCampain, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCampain_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat191, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSlaver, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSlaver_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat192, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTyrant, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTyrant_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat193, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFireborn, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFireborn_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat194, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textIcelord, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textIcelord_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat195, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEntrail, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEntrail_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat196, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMites, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMites_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat197, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCompies, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCompies_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat198, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTeddies, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTeddies_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat199, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textJuggnaut, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textJuggnaut_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat200, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSloth, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSloth_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat201, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMauler, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMauler_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat202, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDrone, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDrone_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat203, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGrunt, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGrunt_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat204, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSlave, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSlave_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat205, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSoldier, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSoldier_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat206, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCaptain, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCaptain_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat207, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textKing, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textKing_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat208, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBastille, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBastille_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat209, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTalSet, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTalSet_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat210, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSyra, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSyra_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat211, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSymbiont, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSymbiont_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat212, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGuardian, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGuardian_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat213, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRavage, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRavage_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat214, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCyclops, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCyclops_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat215, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLorddead, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLorddead_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat216, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMaggot, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMaggot_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat217, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVile, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVile_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat218, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textElite, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textElite_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat219, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBiobot, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBiobot_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat220, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textKillbot, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textKillbot_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat221, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDeath, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDeath_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat222, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textReaper, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textReaper_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat223, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMaw, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMaw_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat224, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRaptor, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRaptor_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat225, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSlag, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSlag_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat226, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textClaw, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textClaw_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat227, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarclubs, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarclubs_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat228, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTurok_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTurok_repeat4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat229, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMantidDrone, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMantidDrone_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat230, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCampaigner, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCampaigner_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat231, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFireborn_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFireborn_repeat4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat232, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMantidSoldier, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMantidSoldier_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat233, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAdon_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAdon_repeat4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat234, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLordOfTheDead, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLordOfTheDead_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat235, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEliteGuard, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEliteGuard_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat236, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGuardian_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGuardian_repeat4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat237, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textJuggernaut, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textJuggernaut_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat238, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOblivionSpawn, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOblivionSpawn_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat239, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBastille_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBastille_repeat4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat240, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSyra_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSyra_repeat4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat241, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSymbiont_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSymbiont_repeat4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat242, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTalSet_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTalSet_repeat4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat243, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRaptor_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRaptor_repeat4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat244, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMantidMites, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMantidMites_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat245, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCapturezLeDrapeauDFois, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCatturataLaBandieraDVolta, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat246, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCapturezLeDrapeauDFois_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCatturataLaBandieraDVolte, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat247, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDCapturesParQuipe, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisiteDCattureDiTeam, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat248, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTagLeSingeDFois, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textToccataLaScimmiaDVolta, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat249, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTagLeSingeDFois_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textToccataLaScimmiaDVolte, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat250, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textObtenezDTagsDeCrAture, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitiDTocchiDiCreatura, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat251, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textObtenezDFrag, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitaDUccisione, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat252, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textObtenezDFrags, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisiteDUccisioni, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat253, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textObtenezDFragParQuipe, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitaDUccisioneDiSquadra, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat254, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textObtenezDFragsParQuipe, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisiteDUccisioniDiSquadra, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat255, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEn02dSecondesMaximum, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textIn02dSecondiOMeno, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat256, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEnDMinuteEt02dSecondesMaximum, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInDMinutoE02dSecondiOMeno, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat257, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEnDMinutesEt02dSecondesMaximum, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInDMinutiE02dSecondiOMeno, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat258, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEnDMinuteMaximum, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInDMinutoOMeno, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat259, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEnDMinutesMaximum, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInDMinutiOMeno, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat260, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAvecDVie, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textConDVita, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat261, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAvecDVies, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textConDVite, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat262, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBattezS, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSconfittoS, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat263, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBattezSEtS, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSconfittoSiaSCheS, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat264, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textUnPourTous, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOgnunoPerS, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat132, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textProvingGroundsAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoProvingGrounds, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat133, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBasicTrainingAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoBasicTraining, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat134, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCrossroadsAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoCrossroads, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat135, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGrimRetreatAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoGrimRetreat, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat136, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCathedralAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoCathedral, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat137, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFalloutAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoFallout, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat138, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBoxedSetAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoBoxedSet, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat139, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDireStraightAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoDireStraight, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat140, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPreyAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoPrey, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat141, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarehouseAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoWarehouse, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat142, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWaterTempleAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoWaterTemple, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat143, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBombShelterAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoBombShelter, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat144, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTemperedAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoTempered, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat145, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEarthTempleAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoEarthTemple, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat146, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFireTempleAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoFireTemple, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat147, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMysticAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoMystic, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat148, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBottleneckAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoBottleneck, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat149, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTightropeAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoTightrope, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat150, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textThePitAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoThePit, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat151, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLeapOfFaithAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoLeapOfFaith, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat152, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWickedDanceAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoWickedDance, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat153, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBunkerAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoBunker, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat154, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAmphitheaterAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoAmphitheater, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat155, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFireWalkerAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoFireWalker, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat156, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCryptsAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoCrypts, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat157, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBreakdownAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoBreakdown, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat158, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRetaliationAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoRetaliation, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat159, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textHopelessAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoHopeless, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat160, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMatrixAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoMatrix, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat161, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFathomAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoFathom, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat162, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textThePedestalAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoThePedestal, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat163, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDefcon5Acheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoDefcon5, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat164, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSpiritTempleAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoSpiritTemple, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat165, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textStrongholdAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoStronghold, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat166, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCourtyardAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoCourtyard, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat167, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textStarlightAcheve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuccessoStarlight, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat168, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text15FragsEn5Minutes, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOttenute15UccisioniIn5Minuti, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat169, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text25FragsEn10Minutes, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOttenute25UccisioniIn10Minuti, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat170, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAucunFrag, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNessunaUccisioneOttenuta, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat171, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVousVousEtesTue5Fois, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textUccisoTeStesso5Volte, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat172, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBonDernier, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textArrivatoInUltima, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat173, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRecompensePourLesFrags, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPremioUccisioniTotali, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat174, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRecompensePourLesMorts, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPremioMorteTotale, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat175, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCanardez10AdversairesDansLeRound, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textUccise10PersoneInUnRound, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat176, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInvaincuDansLeRound, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMaiStatoUccisoInUnRound, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat177, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVousAvezVaincuBastille, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSconfittoBastille, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat178, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVousAvezVaincuSyra, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSconfittoSyra, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat179, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVousAvezVaincuSymbiont, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSconfittoSymbiont, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat180, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVousAvezVaincuTalSet, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSconfittoTalSet, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat181, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFinDuScenarioCooperatif, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSconfittoLoScenarioCooperativo, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat265, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFacile, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFacile_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat266, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNormal, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMedio, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat267, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDifficile, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDifficile_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat268, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOff, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOff_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat269, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOn, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOn_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat270, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRouge, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRosso, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat271, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVert, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVerde, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat272, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textHorizontal, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOrizzontale, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat273, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVertical, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVerticale, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat274, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBasseResolution, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBassaris, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat275, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textHauteResolution, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAltaris, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat276, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEcran, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCasellaTesto, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat277, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNon, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNo, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat278, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOui, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSl, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat279, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNovice_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNovizio_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat280, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFacile_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFacile_repeat4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat281, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNormal_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNormale, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat282, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVeteran, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVeterano, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat283, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textExpert, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEsperto, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat284, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textArcade, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textArcade_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat285, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBarillet, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRuota, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat286, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAppuyer, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTocco, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat287, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMixed, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMisto, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat288, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textManetteD, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textControllerD, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat289, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCtf, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCatturaLaBandiera, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat290, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTbl, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSquadraBloodLust, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat291, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBl, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBloodLust, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat292, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFt, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFragTag_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat293, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDefi, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGuanto, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat294, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLaFoireDuFrag, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFragFest, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat295, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textContreLaMontre, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGaraATempo, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat296, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textJoueurD, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGiocatoreD, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat297, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTalismanAigleObtenu1, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlTalismanoDellAquilaIlConteggioVitaleAumentaDi1, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat298, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMoitieDuTalismanAigleObtenu1AvecLAutreMoitie, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitaMetaDelTalismanoDellAquilaCollezionaLAltraMetPerGuadagnare1Vita, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat299, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSecondeMoitieDuTalismanObtenue1, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoLAltroTalismanoDellAquilaGuadagni1Vita, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat300, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTalismanOursObtenuExplosifs5, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlTalismanoDellOrsoLaScortaDiMunizioniEsplosiveAumentaDi5, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat301, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTalismanCoyoteObtenuBalles50, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlTalismanoDelCoyoteLaScortaDiProiettiliAumentaDi50, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat302, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTalismanPumaObtenuEnergie50, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcuisitoIlTalismanoDelPumaLaScortaDiMunizioniEnergeticheAumentaDi50, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat303, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTalismanVipereObtenuSanteMax5, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlTalismanoDellaViperaLEnergiaMassimaAumentaDi5, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat304, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTalismanCooperatifObtenu, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlTalismanoCooperativo, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat305, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textIconeMiniPartiesObtenu, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlTalismanoMinigioco, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat306, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFusilDAssautTrouve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlFucileDAssalto, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat307, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTirRapidePourFusilDAssautTrouve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoPotenziamentoPerIlFuocoRapidoDelFucileDAssalto, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat308, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLunetteDeViseePourArbaleteTekTrouvee, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlMirinoPerLArco, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat309, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLanceGrenadesTrouve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlLanciagranate, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat310, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAmeliorationPourLanceGrenadesTrouve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlPotenziamentoLanciagranate, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat311, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFusilPlasmaTrouve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoFucileAlPlasma, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat312, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLunettePourFusilPlasmaTrouvee, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlMirinoPerIlFucileAlPlasma, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat313, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textJetDAcideTrouve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoLAttaccoConSputoDAcido, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat314, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAttaqueDeGriffeTrouvee, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoLAttaccoVolanteConArtigli, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat315, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLanceFuseesRadioactivesTrouve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitaLaPistolaARazziRadioattivi, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat316, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAmeliorationPourLanceFuseesRadioactivesTrouvee, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoPotenziamentoPerPistolaARazziRadioattivi, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat317, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLanceMissilesScorpionTrouve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlLanciarazziScorpion, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat318, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAimantPourLanceMissilesScorpionTrouve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlPotenziamentoMagneticoPerLanciarazziScorpion, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat319, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPetrificateurTrouve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitaLaPistolaCongelante, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat320, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAmeliorationPourPetrificateurTrouvee, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlPotenziamentoPistolaCongelante, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat321, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGelNapalmTrouve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlGelAlNapalm, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat322, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textViseeLaserPourMag60Trouvee, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlPotenziamentoVistaLaserPerMag60, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat323, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRupteurTrouve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlDistruggiPetto, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat324, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDilatateurTrouve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlGonfiatore, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat325, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAmeliorationPourDilatateurTrouvee, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlPotenziamentoPerGonfiatore, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat326, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBoomerangTrouve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlBoomerang, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat327, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAmeliorationPourBoomerangTrouvee, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlPotenziamentoBoomerang, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat328, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMinigunTrouve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlMinifucile, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat329, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBouclierPourMinigunTrouve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlPotenziamentoScudoPersonalePerMinifucile, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat330, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAmeliorationNettoyeurPourFusilTrouvee, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlPotenziamentoSpazzastradaPerFucile, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat331, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDecharneurTrouve, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoEmaciatore, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat332, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAmeliorationPourDecharneurTrouvee, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlPotenziamentoPerEmaciatore, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat333, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAmeliorationPourMarteauDeGuerreTrouvee, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAcquisitoIlRazzoDiPotenziamentoPerIlMartelloDaGuerra, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat334, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVousAvezLibereS, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textHaiSbloccatoS, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat335, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEchecDeLaMission, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMissioneFallita, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat336, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textObjetDejaObtenu, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOggettoPrecedentementeAcquisito, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat337, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEquipe, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTeam, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat338, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPrecision, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textColpito, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat339, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTags, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTocchi, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat340, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDrapeaux, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBandiere, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat341, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFelicitationsVousAvezAcheveLaFoireDuFrag, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCongratulazioniHaiCompletatoIlFragFest, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat342, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFelicitationsVousAvezAcheveLeContreLaMontre, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCongratulazioniHaiCompletatoLaGaraATempo, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat343, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFrench, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textItaliano, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat344, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPistolClip10Rounds, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPistolClip10Rounds_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat345, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.screenMessageLinkWords_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRifleClip10Rounds, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat346, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDifficultFacile, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDifficultyEasy, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat347, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDifficultNormal, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDifficultyNormal, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat348, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDifficultDifficile, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDifficultyHard, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat349, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTypeDeCommandeExpert, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textControlTypeExpert, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat350, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTypeDeCommandeArcade, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textControlTypeArcade, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat351, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTypeDeCommande, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textControlType, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat352, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCTDeCommandeGauche, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textControlSideLeft, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat353, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCTDeCommandeDroit, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textControlSideRight, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat354, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVueSurgissanteActivE, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLookSpringOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat355, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVueSurgissanteDSactivE, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLookSpringOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat356, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVisEAutomatiqueActivE, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAutoAimOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat357, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVisEAutomatiqueDSactivE, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAutoAimOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat358, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCouleurDuSangDSactivE, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBloodColorOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat359, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCouleurDuSangRouge, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBloodColorRed, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat360, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCouleurDuSangVert, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBloodColorGreen, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat361, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textConfig2JoueursHorz, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text2PlyrLayoutHorz, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat362, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textConfig2JoueursVert, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text2PlyrLayoutVert, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat363, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOpacitTransparent, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOpacityClear, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat364, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOpacitOpaque, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOpacityOpaque, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat365, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOpacit, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOpacity, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat366, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textStickDirectionnelHorizNorm, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textControlStickHorzNorm, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat367, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textStickDirectionnelHoriz, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textControlStickHorz, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat368, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textStickDirectionnelVertNorm, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textControlStickVertNorm, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat369, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textStickDirectionnelVert, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textControlStickVert, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat370, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSLectionDesArmesRapide, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWeaponSelectQuick, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat371, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSLectionDesArmesNorm, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWeaponSelectNorm, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat372, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRSolutionBasseRSo, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textResolutionLoRez, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat373, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRSolutionHauteRSo, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textResolutionHiRez, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat374, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRSolutionHauteRSoCin, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textResolutionHiRezLb, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat375, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRSolutionTrSBasseRSo, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textResolutionSmLoRez, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat376, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRSolutionBasseRSoCin, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textResolutionLoRezLb, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat377, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLuminositNorm, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBrightnessNorm, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat378, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLuminosit, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBrightness, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat379, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLanguageFrench, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLanguageEnglish, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat380, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPrCDent, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGoBack, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat381, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat202, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat382, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat203, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat383, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat3, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat204, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat384, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat4, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat205, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat385, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat5, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat206, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat386, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat6, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat207, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat387, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat7, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat208, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat388, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat8, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat209, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat389, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat9, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat210, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat390, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat10, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat211, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat391, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat11, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat212, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat392, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat12, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat213, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat393, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat13, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat214, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat394, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat14, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat215, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat395, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCeJeuEst, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat216, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat396, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCompatibleAvec, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat217, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat397, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textUnRumblePak, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat218, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat398, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInsRezVotre, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat219, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat399, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRumblePakMaintenant, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat220, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat400, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSiVousVoulez, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat221, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat401, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textJouerAvec, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat222, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat402, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat15, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat223, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat403, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat16, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textChoose, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat404, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat17, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBlueBlood, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat405, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat18, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRedBlood, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat406, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat19, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFinalScore, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat407, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat20, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBlueBloodScore, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat408, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat21, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRedBloodScore, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat409, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat22, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPleaseWait, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat410, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPause, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPaused, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat411, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textReprendreJeu, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textResumeGame, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat412, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textStatutDeLaMission, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMissionStatus, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat413, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMission, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMissionObjectives, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat414, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInventaire, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInventory, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat415, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textChargement, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLoad, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat416, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOptions, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOptions_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat417, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTriches, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCheats, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat418, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.screenMessageLinkWords_repeat3, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textQuit, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat419, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInventaire_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInventory_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat420, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOk, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOk_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat421, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRageWars, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRageWars_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat422, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTurok2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTurok2_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat423, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text51, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text51_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat424, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNrwx, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNrwx_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat425, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat23, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat224, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat426, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat24, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat225, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat427, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat25, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat226, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat428, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat26, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat227, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat429, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat27, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat228, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat430, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat28, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat229, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat431, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat29, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat230, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat432, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat30, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat231, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat433, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat31, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat232, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat434, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat32, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat233, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat435, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat33, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat234, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat436, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat34, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat235, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat437, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat35, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat236, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat438, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat36, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat237, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat439, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat37, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat238, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat440, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat38, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat239, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat441, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat39, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat240, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat442, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat40, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat241, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat443, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat41, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat242, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat444, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat42, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat243, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat445, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat43, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat244, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat446, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat44, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat245, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat447, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat45, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat246, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat448, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat46, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat247, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat449, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat47, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat248, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat450, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat48, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat249, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat451, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat49, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat250, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat452, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat50, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat251, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat453, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat51, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat252, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat455, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAutrePartie, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAltraPartita, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat454, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat52, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat253, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat456, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat53, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat254, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat457, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat54, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat255, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat458, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat55, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat256, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat459, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat56, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat257, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat460, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat57, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat258, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat461, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat58, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat259, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat462, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat59, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat260, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat463, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat60, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat261, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat464, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat61, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat262, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat465, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat62, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat263, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat466, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat63, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat264, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat467, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat64, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat265, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat468, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat65, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat266, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat469, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat66, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat267, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat470, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat67, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat268, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat471, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat68, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat269, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat472, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInfoNote, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNoteInfo, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat473, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEffacerNote, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDeleteNote, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat474, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDifficultFacile_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDifficultyEasy_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat475, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDifficultNormal_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDifficultyNormal_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat476, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDifficultDifficile_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDifficultyHard_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat477, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPointsDeSant, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textHealth, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat478, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.screenMessageLinkWords_repeat4, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLives, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat479, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textHeureReadout, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTimeReadout, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat480, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInfoNote_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNoteInfo_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat481, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEffacerNote_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDeleteNote_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat482, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEffacerNote_repeat3, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDeleteNote_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat483, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNomExt, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNameExt, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat484, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text_repeat4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat485, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNom, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textName, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat486, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textType, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textType_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat487, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVictimes, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFrags, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat488, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textClassement, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRank, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat489, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCharger, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLoad_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat490, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEffacer, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDelete, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat491, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEffacer_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDelete_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat492, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textErreur, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textError, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat493, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textImportant, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textImportant_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat494, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOk_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOk_repeat4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat495, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat270, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat496, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat69, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat271, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat497, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat70, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat272, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat498, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat71, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat273, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat499, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat72, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat274, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat500, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat73, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat275, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat501, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat74, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat276, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat502, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat75, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat277, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat503, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat76, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat278, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat504, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat77, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat279, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat505, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat78, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat280, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat506, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat79, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat281, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat507, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat80, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat282, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat508, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat81, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat283, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat509, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat82, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat284, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat510, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat83, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat285, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat511, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat84, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat286, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat512, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat85, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat287, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat513, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat86, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat288, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat514, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat87, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat289, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat515, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat88, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat290, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat516, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat89, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat291, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat517, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat90, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat292, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat518, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat91, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat293, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat519, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat92, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat294, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat520, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat93, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat295, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat521, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat94, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat296, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat522, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat95, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat297, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat523, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat96, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat298, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat524, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat97, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat299, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat525, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat98, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat300, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat526, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat99, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat301, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat527, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat100, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat302, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat528, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat101, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat303, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat529, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat102, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat304, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat530, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat103, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat305, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat531, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat104, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat306, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat532, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat105, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat307, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat533, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat106, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat308, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat534, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat107, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat309, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat535, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat108, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat310, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat536, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat109, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat311, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat537, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat110, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat312, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat538, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat111, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat313, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat539, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat112, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat314, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat540, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat113, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat315, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat541, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat114, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat316, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat542, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat115, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat317, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat543, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat116, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat318, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat544, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat117, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat319, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat545, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat118, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat320, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat546, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat119, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat321, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat547, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat120, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat322, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat548, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat121, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat323, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat549, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat122, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat324, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat550, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat123, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat325, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat551, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat124, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat326, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat552, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat125, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat327, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat553, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat126, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat328, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat554, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat127, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat329, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat555, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat128, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat330, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat556, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat129, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat331, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat557, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat130, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat332, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat558, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat131, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat333, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat559, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat132, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat334, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat560, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat133, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat335, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat561, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat134, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat336, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat562, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat135, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat337, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat563, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat136, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat338, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat564, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat137, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat339, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat565, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat138, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat340, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat566, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat139, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat341, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat567, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat140, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat342, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat568, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat141, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat343, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat569, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat142, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat344, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat570, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat143, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat345, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat571, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat144, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat346, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat572, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat145, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat347, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat573, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat146, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat348, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat574, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat147, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat349, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat575, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat148, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat350, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat576, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat149, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat351, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat577, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat150, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat352, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat578, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat151, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat353, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat579, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat152, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat354, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat580, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat153, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat355, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat581, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat154, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat356, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat582, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat155, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat357, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat583, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat156, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat358, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat584, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat157, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat359, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat585, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat158, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat360, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat586, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat159, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat361, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat587, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat160, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat362, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat588, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat161, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat363, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat589, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat162, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat364, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat590, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat163, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat365, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat591, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat164, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat366, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat592, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat165, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat367, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat593, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat166, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat368, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat594, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat167, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat369, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat595, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat168, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat370, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat596, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat169, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat371, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat597, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat170, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat372, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat598, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat171, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat373, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat599, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat172, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat374, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat600, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat173, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat375, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat601, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat174, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat376, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat602, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat175, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat377, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat603, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat176, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat378, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat604, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat177, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat379, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat605, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat178, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat380, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat606, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat179, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat381, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat607, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat180, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat382, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat608, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat181, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat383, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat609, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat182, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat384, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat610, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat183, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat385, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat611, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat184, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat386, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat612, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat185, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat387, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat613, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat186, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat388, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat614, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat187, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat389, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat615, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat188, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat390, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat616, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat189, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat391, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat617, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSauvegarder, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSave, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat618, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCharger_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLoad_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat619, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPointsDeSant_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textHealth_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat620, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMunitions, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAmmo, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat621, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPrCDent_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGoBack_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat622, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat190, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat392, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat623, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat191, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat393, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat624, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat192, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat394, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat625, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat193, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat395, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat626, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat194, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat396, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat627, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat195, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat397, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat628, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat196, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat398, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat629, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat197, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat399, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat630, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat198, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat400, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat631, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat199, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.emptyTextSlots_repeat401, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat632, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTirDeMine, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPmfShot, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat633, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTirLaTTe, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBodyShot, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat634, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTirAuCorps, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textHeadShot, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat635, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTirAuBras, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textArmShot, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat636, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textModifier, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEdit, (void *)&k_SkyPostscaledscreenmessageEncodedWords.controlCodeTexts[1], (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.screenMessageLinkWords_repeat5, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.screenMessageLinkWords_repeat13, (void *)&k_SkyPostscaledscreenmessageEncodedWords.controlCodeTexts[2], (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.screenMessageLinkWords_repeat6, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.screenMessageLinkWords_repeat14, (void *)&k_SkyPostscaledscreenmessageEncodedWords.controlCodeTexts[3], (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.screenMessageLinkWords_repeat7, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.screenMessageLinkWords_repeat15, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat637, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTaggPar, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTaggedBy, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat638, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVousAvezTagg, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textYouTagged, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat639, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTuPar, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textKilledBy, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat640, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVousAvezTu, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textYouKilled, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat641, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVousVousTesTu, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textYouKilledYourself, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat642, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVousAvezPerduVotreDrapeau, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textYouLostTheFlag, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat643, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textIlALChLeDrapeau, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textHeDroppedTheFlag, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat644, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTesVousSR, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAreYouSure, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat645, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDeVouloir, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textYouWantTo, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat646, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOui_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textYes, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat647, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNon_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNo_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat648, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCodesTriche, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCheats_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat649, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCharger_repeat3, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLoad_repeat4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat650, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSauvegarder_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSave_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat651, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTaperCodesTriche, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEnterCheat, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat652, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textRejoindre, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textJoinNow, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat653, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVeuillezPatienter, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWaiting, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat654, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textConnexion, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textConnect, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat655, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPrCDent_repeat3, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGoBack_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat656, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textContinuer, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textContinue, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat657, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPartieTerminE, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGameOver, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat658, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTempsXx, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTimeXx, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat659, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTermin, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDone, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat660, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNouveauModeDeTricheActiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNewCheatEnabled, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat661, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInvincibilitActivE, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInvincibilityActivated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat662, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textViesInfiniesActivEs, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInfiniteLivesActivated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat663, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textToutesArmesActivEs, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAllWeaponsActivated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat664, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMunitionsIllimitEsActivEs, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textUnlimitedAmmoActivated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat665, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textToutesClefsActivEs, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAllKeysActivated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat666, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textModeGrosseTTeActiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBigHeadModeActivated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat667, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textModeMinusculeActiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTinyModeActivated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat668, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textModeTraitActiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textStickModeActivated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat669, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textModeGrosPiedsGrossesMainsActiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBigHandsAndFeetModeActivated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat670, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textModeStyloEtEncreActiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPenAndInkModeActivated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat671, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textModeGouraudActiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGouraudModeActivated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat672, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCodeTricheDeJuanActiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textJuansCheatActivated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat673, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCodeTricheDeLAttaqueDeZachActiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textZachAttackCheatActivated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat674, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCarteComplTeActivE, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAllMapActivated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat675, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCitSombreActivE, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBlackoutModeActivated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat676, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textHmmmDLicieusesRayures, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMmmmTastyFrootyStripes, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat677, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpNiveau1Activ, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpLevel1Activated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat678, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpNiveau2Activ, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpLevel2Activated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat679, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpNiveau3Activ, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpLevel3Activated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat680, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpNiveau4Activ, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpLevel4Activated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat681, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpNiveau5Activ, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpLevel5Activated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat682, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpNiveau6Activ, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpLevel6Activated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat683, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBossWarpReineActiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpQueenBossActivated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat684, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBossWarpCyclopeActiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpBlindOneBossActivated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat685, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBossWarpMReActiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpMotherBossActivated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat686, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpBossPrimagenActiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpPrimagenBossActivated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat687, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpCrDitsActiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpCreditsActivated, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat688, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInvincibilitActivE_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInvincibilityOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat689, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInvincibilitDSactivE, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInvincibilityOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat690, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textViesInfiniesActivEs_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInfiniteLivesOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat691, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textViesInfiniesDSactivEs, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textInfiniteLivesOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat692, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textToutesArmesActivEs_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAllWeaponsOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat693, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textToutesArmesDSactivEs, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAllWeaponsOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat694, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMunitionsIllimitEsActivEs_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textUnlimitedAmmoOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat695, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMunitionsIllimitEsDSactivEs, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textUnlimitedAmmoOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat696, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTousObjetsSpCiauxActivS, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAllSpecialObjectsOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat697, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTousObjetsSpCiauxDSactivS, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAllSpecialObjectsOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat698, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textModeGrosseTTeActiv_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBigHeadModeOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat699, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textModeGrosseTTeDSactiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBigHeadModeOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat700, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textModeMinusculeActiv_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTinyModeOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat701, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textModeMinusculeDSactiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTinyModeOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat702, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textModeTraitActiv_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textStickModeOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat703, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textModeTraitDSactiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textStickModeOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat704, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textModeGrosPiedsGrossesMainsActiv_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBigHandsFeetModeOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat705, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textModeGrosPiedsGrossesMainsDSactiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBigHandsFeetModeOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat706, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textModeStyloEtEncreActiv_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPenAndInkModeOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat707, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textModeStyloEtEncreDSactiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPenAndInkModeOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat708, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textModeGouraudActiv_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGouraudModeOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat709, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textModeGouraudDSactiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGouraudModeOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat710, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCodeTricheDeJuanActiv_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textJuansCheatOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat711, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCodeTricheDeJuanDSactiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textJuansCheatOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat712, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCodeTricheDeLAttaqueDeZachActiv_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textZachAttackCheatOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat713, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCodeTricheDeLAttaqueDeZachDSactiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textZachAttackCheatOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat714, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCarteComplTeActivE_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAllMapOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat715, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCarteComplTeDSactivE, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAllMapOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat716, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCitSombreActivE_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBlackoutOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat717, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCitSombreDSactivE, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBlackoutOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat718, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDLicieusesRayuresActivEs, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFrootyStripesOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat719, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDLicieusesRayuresDSactivEs, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFrootyStripesOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat720, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpPortDAdia, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpPortOfAdia, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat721, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpRiviReDesMes, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpRiverOfSouls, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat722, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpMarCagesDeLaMort, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpDeathMarshes, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat723, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpRepaireDesCyclopes, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpLairOfTheBlindOnes, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat724, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpRucheDesMantides, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpHiveOfTheMantids, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat725, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpVaisseauDeLumiReDePrimagen, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpPrimagenSLightship, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat726, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpBossReine, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpQueenBoss, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat727, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpBossCyclope, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpBlindOneBoss, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat728, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpBossMRe, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpMotherBoss, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat729, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpBossPrimagen, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpPrimagenBoss, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat730, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpCrDits, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textWarpCredits, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat731, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVousAvezTu_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textYouFragged, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat732, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVousAvezMarqu, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textYouTagged_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat733, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTotaux, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTotals, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat734, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textUn0000, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOne0000, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat735, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDeux0000, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTwo0000, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat736, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTrois0000, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textThree0000, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat737, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textQuatre0000, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFour0000, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat738, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMarques0000, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTags0000, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat739, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVictimes0000, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFrags0000, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat740, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMorts0000, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDeaths0000, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat741, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuicides0000, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuicides0000_repeat5, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat742, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textUn0000_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOne0000_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat743, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDeux0000_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTwo0000_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat744, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTrois0000_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textThree0000_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat745, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textQuatre0000_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFour0000_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat746, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMarques0000_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTags0000_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat747, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVictimes0000_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFrags0000_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat748, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMorts0000_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDeaths0000_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat749, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuicides0000_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuicides0000_repeat6, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat750, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textUn0000_repeat3, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOne0000_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat751, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDeux0000_repeat3, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTwo0000_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat752, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTrois0000_repeat3, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textThree0000_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat753, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textQuatre0000_repeat3, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFour0000_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat754, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMarques0000_repeat3, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTags0000_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat755, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVictimes0000_repeat3, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFrags0000_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat756, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMorts0000_repeat3, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDeaths0000_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat757, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuicides0000_repeat3, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuicides0000_repeat7, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat758, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textUn0000_repeat4, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOne0000_repeat4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat759, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDeux0000_repeat4, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTwo0000_repeat4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat760, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTrois0000_repeat4, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textThree0000_repeat4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat761, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textQuatre0000_repeat4, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFour0000_repeat4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat762, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMarques0000_repeat4, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTags0000_repeat4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat763, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVictimes0000_repeat4, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFrags0000_repeat4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat764, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMorts0000_repeat4, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDeaths0000_repeat4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat765, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuicides0000_repeat4, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSuicides0000_repeat8, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat766, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textJoueur1, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPlayer1, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat767, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textJoueur2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPlayer2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat768, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textJoueur3, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPlayer3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat769, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textJoueur4, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPlayer4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat770, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textJoueurSeul, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSingle, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat771, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNouvellePartie, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNewGame, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat772, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textChargement_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLoad_repeat5, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat773, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMulti, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMulti_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat774, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMatchMort, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDeathmatch, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat775, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSLectionnerTypeDePartie, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSelectGameType, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat776, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBloodlust, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBloodLust_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat777, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBloodlust_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textBloodLust_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat778, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPartieContreLaMontreAucune, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTimedGameNone, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat779, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLimiteVictimesAucune, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFragLimitNone, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat780, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNiveauAlAtoire, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLevelRandom, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat781, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNiveauExpRimentations, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLevelExperimentata, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat782, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNiveauPaniqueAuClairDeLune, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLevelMoonlitMayhem, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat783, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNiveauProximit, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLevelCloseQuartered, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat784, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNiveauLaForgeDeVulcain, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLevelVulcanSForge, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat785, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNiveauTLPortastique, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLevelTeleportastic, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat786, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNiveauImageInversE, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLevelMirrororrim, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat787, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNiveauCibleFacile, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLevelFishInABarrel, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat788, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNiveauH2Whaou, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLevelH2Whoa, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat789, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNiveauDMence, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLevelEscheria, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat790, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNiveauCrypteMosh, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLevelMoshCrypt, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat791, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNiveauCarrSCubes, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLevelSquaresCubed, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat792, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNiveauHuitEnFolie, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLevelCrazyEight, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat793, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNiveauMille, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLevelBullseye, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat794, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTextureChTeau, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTextureSetCastle, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat795, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTextureAciRie, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTextureSetSteelMill, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat796, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTextureFortEnChNe, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTextureSetOakFort, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat797, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTextureCatacombes, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTextureSetCatacombs, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat798, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTextureBagne, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTextureSetJailhouse, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat799, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTextureGrandeVille, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTextureSetBigCity, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat800, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTextureDragonRouge, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTextureSetRedDragon, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat801, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTexturePaintball, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTextureSetPaintball, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat802, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTextureMJoyeux, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTextureSetMrHappy, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat803, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textViseurActiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCrosshairsOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat804, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textViseurDSactiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCrosshairsOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat805, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCommencerPartie, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textStartGame, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat806, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPrCDent_repeat4, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGoBack_repeat4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat807, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFragTag, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFragTag_repeat4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat808, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFragTag_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFragTag_repeat5, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat809, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLimiteMarquageAucune, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTagLimitNone, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat810, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNiveauMaisonDeFous, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLevelMadhouse, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat811, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNiveauBataille, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLevelSnap, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat812, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNiveauJeuDeLOie, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLevelSneaksNLadders, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat813, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNiveauPrimattica, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLevelPrimattica, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat814, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNiveauFeuCrois, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLevelCrossfire, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat815, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNiveauVOJCQVD, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLevelYNGWTSF, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat816, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSangQuipe, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTeamBlood, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat817, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPersonnaliserArmes, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCustomizeWeapons, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat818, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFusilFlChettesActiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textChargeDartRifleOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat819, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFusilFlChettesDSactiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textChargeDartRifleOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat820, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCanonOrageActiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFirestormOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat821, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCanonOrageDSactiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFirestormOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat822, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFusilDAssautActiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAssaultRifleOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat823, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFusilDAssautDSactiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textAssaultRifleOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat824, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFusilPlasmaActiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPlasmaRifleOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat825, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textFusilPlasmaDSactiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPlasmaRifleOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat826, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPerceuseCRBraleActivE, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCerebralBoreOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat827, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPerceuseCRBraleDSactivE, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCerebralBoreOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat828, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLanceGrenadesActiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGrenadeLauncherOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat829, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLanceGrenadesDSactiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGrenadeLauncherOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat830, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLanceMissilesScorpActiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textScorpionLauncherOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat831, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLanceMissilesScorpDSactiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textScorpionLauncherOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat832, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLanceTorpillesActiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTorpedoLauncherOn, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat833, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLanceTorpillesDSactiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTorpedoLauncherOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat834, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textEntraNement, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textTraining, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat835, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNiveauAlAtoire_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLevelRandom_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat836, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNiveauTirLArc, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLevelArchery, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat837, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNiveauTir, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLevelShooting, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat838, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNiveauDCathlon, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLevelDecathalon, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat839, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNDeTours, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textNoOfLaps, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat840, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCommencerPartie_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textStartGame_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat841, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPrCDent_repeat5, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textGoBack_repeat5, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat842, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCharger_repeat4, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLoad_repeat6, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat843, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOptions_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOptions_repeat4, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat844, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCodesTriche_repeat2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCheats_repeat3, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat845, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPointDeContrLe, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textCheckPoint, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat846, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPointDeSauvegarde, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSavePoint, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat847, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textOptionsDeSon, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSoundOptions, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat848, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVolumeMusiqueDSactiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMusicVolumeOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat849, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVolumeMusiqueMax, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMusicVolumeMax, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat850, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVolumeMusiqueNorm, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMusicVolumeNorm, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat851, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVolumeMusique, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMusicVolume, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat852, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVolumeEffetsDSactiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSfxVolumeOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat853, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVolumeEffetsMax, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSfxVolumeMax, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat854, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVolumeEffetsNorm, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSfxVolumeNorm, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat855, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVolumeEffets, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSfxVolume, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat856, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVolumeDialoguesDSactiv, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSpeechVolumeOff, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat857, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVolumeDialoguesMax, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSpeechVolumeMax, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat858, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVolumeDialoguesNorm, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSpeechVolumeNorm, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat859, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVolumeDialogues, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSpeechVolume, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat860, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMusiqueAucune, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMusicNone, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat861, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMusique, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMusic, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat862, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textIndexAucun, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textIndexNone, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat863, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDialoguesAucun, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSpeechNone, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat864, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMissionAccomplie, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMissionComplete, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat865, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textChec, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textMissionFailed, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat866, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDFendreLeTotem, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDefendTheTotem, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat867, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVitesseDuJoueur, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPlayerSpeed, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat868, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textVitesseDuJoueurDFaut, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textPlayerSpeedDefault, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat869, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDFaut, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textDefault, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat870, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textSantFaible, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.textLowHealth, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat871, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text_repeat3, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text_repeat5, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat872, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text0, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text0_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat873, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text1, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text1_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat874, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text2, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text2_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat875, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text3, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text3_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat876, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text4, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text4_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat877, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text5, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text5_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat878, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text6, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text6_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat879, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text7, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text7_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat880, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text8, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text8_repeat2, (void *)&k_SkyPostscaledscreenmessageEncodedWords.emptyTextSlots_repeat881, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.screenMessageLinkWords_repeat8, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.text9, (void *)&k_SkyPostscaledscreenmessageEncodedWords.creditsNameLinks[0], (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.screenMessageLinkWords_repeat9, (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.screenMessageLinkWords_repeat16 },
    {
        { 8.0f, { (void *)&g_GfxdataEncodedWords.powerScales[0].value, (void *)&g_GfxdataEncodedWords.powerScales[0].value, (void *)&g_GfxdataEncodedWords.powerScales[0].value, (void *)&g_GfxdataEncodedWords.powerScales[0].value } },
        { 32.0f, { (void *)&g_GfxdataEncodedWords.powerScales[1].value, (void *)&g_GfxdataEncodedWords.powerScales[1].value, (void *)&g_GfxdataEncodedWords.powerScales[1].value, (void *)&g_GfxdataEncodedWords.powerScales[1].value } },
        { 128.0f, { (void *)&g_GfxdataEncodedWords.powerScales[2].value, (void *)&g_GfxdataEncodedWords.powerScales[2].value, (void *)&g_GfxdataEncodedWords.powerScales[2].value, (void *)&g_GfxdataEncodedWords.powerScales[2].value } },
        { 512.0f, { (void *)&g_GfxdataEncodedWords.powerScales[3].value, (void *)&g_GfxdataEncodedWords.powerScales[3].value, (void *)&g_GfxdataEncodedWords.powerScales[3].value, (void *)&g_GfxdataEncodedWords.powerScales[3].value } },
        { 2048.0f, { (void *)&g_GfxdataEncodedWords.powerScales[4].value, (void *)&g_GfxdataEncodedWords.powerScales[4].value, (void *)&g_GfxdataEncodedWords.powerScales[4].value, (void *)&g_GfxdataEncodedWords.powerScales[4].value } },
        { 8192.0f, { (void *)&g_GfxdataEncodedWords.powerScales[5].value, (void *)&g_GfxdataEncodedWords.powerScales[5].value, (void *)&g_GfxdataEncodedWords.powerScales[5].value, (void *)&g_GfxdataEncodedWords.powerScales[5].value } },
        { 32768.0f, { (void *)&g_GfxdataEncodedWords.powerScales[6].value, (void *)&g_GfxdataEncodedWords.powerScales[6].value, (void *)&g_GfxdataEncodedWords.powerScales[6].value, (void *)&g_GfxdataEncodedWords.powerScales[6].value } },
        { 131072.0f, { (void *)&g_GfxdataEncodedWords.powerScales[7].value, (void *)&g_GfxdataEncodedWords.powerScales[7].value, (void *)&g_GfxdataEncodedWords.powerScales[7].value, (void *)&g_GfxdataEncodedWords.powerScales[7].value } },
        { 524288.0f, { (void *)&g_GfxdataEncodedWords.powerScales[8].value, (void *)&g_GfxdataEncodedWords.powerScales[8].value, (void *)&g_GfxdataEncodedWords.powerScales[8].value, (void *)&g_GfxdataEncodedWords.powerScales[8].value } },
        { 2097152.0f, { (void *)&g_GfxdataEncodedWords.powerScales[9].value, (void *)&g_GfxdataEncodedWords.powerScales[9].value, (void *)&g_GfxdataEncodedWords.powerScales[9].value, (void *)&g_GfxdataEncodedWords.powerScales[9].value } },
        { 8388608.0f, { (void *)&g_GfxdataEncodedWords.powerScales[10].value, (void *)&g_GfxdataEncodedWords.powerScales[10].value, (void *)&g_GfxdataEncodedWords.powerScales[10].value, (void *)&g_GfxdataEncodedWords.powerScales[10].value } },
        { 33554432.0f, { (void *)&g_GfxdataEncodedWords.powerScales[11].value, (void *)&g_GfxdataEncodedWords.powerScales[11].value, (void *)&g_GfxdataEncodedWords.powerScales[11].value, (void *)&g_GfxdataEncodedWords.powerScales[11].value } },
        { 1.3421773e+08f, { (void *)&g_GfxdataEncodedWords.powerScales[12].value, (void *)&g_GfxdataEncodedWords.powerScales[12].value, (void *)&g_GfxdataEncodedWords.powerScales[12].value, (void *)&g_GfxdataEncodedWords.powerScales[12].value } },
        { 5.368709e+08f, { (void *)&g_GfxdataEncodedWords.powerScales[13].value, (void *)&g_GfxdataEncodedWords.powerScales[13].value, (void *)&g_GfxdataEncodedWords.powerScales[13].value, (void *)&g_GfxdataEncodedWords.powerScales[13].value } },
        { 2.1474836e+09f, { (void *)&g_GfxdataEncodedWords.powerScales[14].value, (void *)&g_GfxdataEncodedWords.powerScales[14].value, (void *)&g_GfxdataEncodedWords.powerScales[14].value, (void *)&g_GfxdataEncodedWords.powerScales[14].value } },
    },
    {
        { 0x50000000, { (void *)&g_GfxdataEncodedWords.characterCodes[0].value, (void *)&g_GfxdataEncodedWords.characterCodes[0].value, (void *)&g_GfxdataEncodedWords.characterCodes[0].value, (void *)&g_GfxdataEncodedWords.characterCodes[0].value } },
        { 0x51000000, { (void *)&g_GfxdataEncodedWords.characterCodes[1].value, (void *)&g_GfxdataEncodedWords.characterCodes[1].value, (void *)&g_GfxdataEncodedWords.characterCodes[1].value, (void *)&g_GfxdataEncodedWords.characterCodes[1].value } },
        { 0x52000000, { (void *)&g_GfxdataEncodedWords.characterCodes[2].value, (void *)&g_GfxdataEncodedWords.characterCodes[2].value, (void *)&g_GfxdataEncodedWords.characterCodes[2].value, (void *)&g_GfxdataEncodedWords.characterCodes[2].value } },
        { 0x53000000, { (void *)&g_GfxdataEncodedWords.characterCodes[3].value, (void *)&g_GfxdataEncodedWords.characterCodes[3].value, (void *)&g_GfxdataEncodedWords.characterCodes[3].value, (void *)&g_GfxdataEncodedWords.characterCodes[3].value } },
        { 0x54000000, { (void *)&g_GfxdataEncodedWords.characterCodes[4].value, (void *)&g_GfxdataEncodedWords.characterCodes[4].value, (void *)&g_GfxdataEncodedWords.characterCodes[4].value, (void *)&g_GfxdataEncodedWords.characterCodes[4].value } },
        { 0x55000000, { (void *)&g_GfxdataEncodedWords.characterCodes[5].value, (void *)&g_GfxdataEncodedWords.characterCodes[5].value, (void *)&g_GfxdataEncodedWords.characterCodes[5].value, (void *)&g_GfxdataEncodedWords.characterCodes[5].value } },
        { 0x56000000, { (void *)&g_GfxdataEncodedWords.characterCodes[6].value, (void *)&g_GfxdataEncodedWords.characterCodes[6].value, (void *)&g_GfxdataEncodedWords.characterCodes[6].value, (void *)&g_GfxdataEncodedWords.characterCodes[6].value } },
        { 0x57000000, { (void *)&g_GfxdataEncodedWords.characterCodes[7].value, (void *)&g_GfxdataEncodedWords.characterCodes[7].value, (void *)&g_GfxdataEncodedWords.characterCodes[7].value, (void *)&g_GfxdataEncodedWords.characterCodes[7].value } },
        { 0x58000000, { (void *)&g_GfxdataEncodedWords.characterCodes[8].value, (void *)&g_GfxdataEncodedWords.characterCodes[8].value, (void *)&g_GfxdataEncodedWords.characterCodes[8].value, (void *)&g_GfxdataEncodedWords.characterCodes[8].value } },
        { 0x59000000, { (void *)&g_GfxdataEncodedWords.characterCodes[9].value, (void *)&g_GfxdataEncodedWords.characterCodes[9].value, (void *)&g_GfxdataEncodedWords.characterCodes[9].value, (void *)&g_GfxdataEncodedWords.characterCodes[9].value } },
        { 0x5A000000, { (void *)&g_GfxdataEncodedWords.characterCodes[10].value, (void *)&g_GfxdataEncodedWords.characterCodes[10].value, (void *)&g_GfxdataEncodedWords.characterCodes[10].value, (void *)&g_GfxdataEncodedWords.characterCodes[10].value } },
        { 0x30000000, { (void *)&g_GfxdataEncodedWords.characterCodes[11].value, (void *)&g_GfxdataEncodedWords.characterCodes[11].value, (void *)&g_GfxdataEncodedWords.characterCodes[11].value, (void *)&g_GfxdataEncodedWords.characterCodes[11].value } },
        { 0x31000000, { (void *)&g_GfxdataEncodedWords.characterCodes[12].value, (void *)&g_GfxdataEncodedWords.characterCodes[12].value, (void *)&g_GfxdataEncodedWords.characterCodes[12].value, (void *)&g_GfxdataEncodedWords.characterCodes[12].value } },
        { 0x32000000, { (void *)&g_GfxdataEncodedWords.characterCodes[13].value, (void *)&g_GfxdataEncodedWords.characterCodes[13].value, (void *)&g_GfxdataEncodedWords.characterCodes[13].value, (void *)&g_GfxdataEncodedWords.characterCodes[13].value } },
        { 0x33000000, { (void *)&g_GfxdataEncodedWords.characterCodes[14].value, (void *)&g_GfxdataEncodedWords.characterCodes[14].value, (void *)&g_GfxdataEncodedWords.characterCodes[14].value, (void *)&g_GfxdataEncodedWords.characterCodes[14].value } },
        { 0x34000000, { (void *)&g_GfxdataEncodedWords.characterCodes[15].value, (void *)&g_GfxdataEncodedWords.characterCodes[15].value, (void *)&g_GfxdataEncodedWords.characterCodes[15].value, (void *)&g_GfxdataEncodedWords.characterCodes[15].value } },
        { 0x35000000, { (void *)&g_GfxdataEncodedWords.characterCodes[16].value, (void *)&g_GfxdataEncodedWords.characterCodes[16].value, (void *)&g_GfxdataEncodedWords.characterCodes[16].value, (void *)&g_GfxdataEncodedWords.characterCodes[16].value } },
        { 0x36000000, { (void *)&g_GfxdataEncodedWords.characterCodes[17].value, (void *)&g_GfxdataEncodedWords.characterCodes[17].value, (void *)&g_GfxdataEncodedWords.characterCodes[17].value, (void *)&g_GfxdataEncodedWords.characterCodes[17].value } },
        { 0x37000000, { (void *)&g_GfxdataEncodedWords.characterCodes[18].value, (void *)&g_GfxdataEncodedWords.characterCodes[18].value, (void *)&g_GfxdataEncodedWords.characterCodes[18].value, (void *)&g_GfxdataEncodedWords.characterCodes[18].value } },
    },
    {
        { 3.0517578e-05f, { (void *)&g_GfxdataEncodedWords.fractionScales[0].value, (void *)&g_GfxdataEncodedWords.fractionScales[0].value, (void *)&g_GfxdataEncodedWords.fractionScales[0].value, (void *)&g_GfxdataEncodedWords.fractionScales[0].value } },
        { 0.00012207031f, { (void *)&g_GfxdataEncodedWords.fractionScales[1].value, (void *)&g_GfxdataEncodedWords.fractionScales[1].value, (void *)&g_GfxdataEncodedWords.fractionScales[1].value, (void *)&g_GfxdataEncodedWords.fractionScales[1].value } },
    },
    {
        { 0x02000000, { (void *)&g_GfxdataEncodedWords.formatCodes[0].value, (void *)&g_GfxdataEncodedWords.formatCodes[0].value, (void *)&g_GfxdataEncodedWords.formatCodes[0].value, (void *)&g_GfxdataEncodedWords.formatCodes[0].value } },
        { 0x03000000, { (void *)&g_GfxdataEncodedWords.formatCodes[1].value, (void *)&g_GfxdataEncodedWords.formatCodes[1].value, (void *)&g_GfxdataEncodedWords.formatCodes[1].value, (void *)&g_GfxdataEncodedWords.formatCodes[1].value } },
        { 0x04000000, { (void *)&g_GfxdataEncodedWords.formatCodes[2].value, (void *)&g_GfxdataEncodedWords.formatCodes[2].value, (void *)&g_GfxdataEncodedWords.formatCodes[2].value, (void *)&g_GfxdataEncodedWords.formatCodes[2].value } },
    },
    { 0, (void *)&g_GfxdataEncodedWords.trailingLinks[0], (void *)&g_GfxdataEncodedWords.trailingLinks[0], (void *)&g_GfxdataEncodedWords.trailingLinks[0], (void *)&g_GfxdataEncodedWords.trailingLinks[0], (void *)&s_SkyPostscaledscreenmessageScreenMessageTextEuX.screenMessageLinkWords_repeat17, 0, 0, 0 },
    1280,
};
#endif

#if defined(VERSION_US)
PakAdjustownernotificationoptionDataConstantWordsLayout g_pakAdjustownernotificationoptionDataConstantWords = { { (void *)&g_screenMessageSubstitutionSource,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.messageLinkWords, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots[0],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots[1], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.messageLinkWords_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.messageLinkWords_repeat3, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.text2Health,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.text10Health, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.text15Health,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.text25Health, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.text50Health,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFullHealth, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textUltraHealth,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.text1LifeForce, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.text10LifeForce,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textInvincibility, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textPlaneWalker,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFlashlight, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFlashlightBattery,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textInfraredGoggles, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBreathOfLife,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textEyeOfTruth, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLeapOfFaith,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWhispers, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textHeartOfFire,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBlueEagleFeather, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textGreyEagleFeather,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBrownEagleFeather, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textPurpleEagleFeather,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textRedEagleFeather, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textNukeWeaponPart,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textRetaliation, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFlagWasClaimed,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFlagWasCaptured, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFlagReturned,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textThePowerIsYours, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFunctionNotAvailable,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarhammer, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textRaptorClaw,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMiteBite, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBoomerang,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTekCrossbow, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMag60,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textShotgun, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAssaultRifle,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMinigun, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textPlasmaRifle,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFreezeGun, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFlareGun,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textGrenades, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textScorpion,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textNapalmGel, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textEmaciator,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textInflator, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textChestBurster,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textCerebralBore, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textPfmMine,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textIronClaw, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTeleportMine,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSentryTurret, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAttractRemoved,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAttractMarked, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textRepulseMarked,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSlowTime, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBlastShield,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textRegeneration, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textPetrify,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDamageReversal, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textInvisibility,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLifeForceVampire, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSpeedBurst,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTeleportation, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTeleportedToSafety,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMassiveDamage, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textInvunerability,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBulletShield, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textEnergyAbsorption,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSomethingElse, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textShield,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textJoinedTeamCoyote, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textJoinedTeamBear,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textJoinedTeamCougar, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textJoinedTeamViper,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textYouFraggedYourself, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMangledByS,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFraggedByS, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSmackedByS,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSObliteratedYou, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSButcheredYou,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSCrushedYou, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textPoundedByS,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textYourOtherLeft, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textOops,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBadMove, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textUmWatchYourStep,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMunch, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textOops_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textYouWereBested, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textEmbryoImplanted,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textEmbryoDestroyed, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSmackS,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textOrFindPowerCore, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textEnergyRounds,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textEnergyRounds_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBulletRounds,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBulletRounds_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textExplosiveRounds,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textExplosiveRounds_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAmmoPack,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBullet, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textEnergyRound,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textExplosiveRound, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textCerebralBore_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textPfmMine_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSentryTurret_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textIronClaw_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTeleportMine_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textNovice, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textNewcomer,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textGrunt, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textScout,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBrave, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTracker,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textHunter, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarrior,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDarkling, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSeeker,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAssassin, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBane,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarlord, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDeathwind,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textConqueror, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMaster,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTyrant, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarslave,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textGodhand, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textChieftain,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textEmpty, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textNewPlayer,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTurok, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarrior_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMaster_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAdon,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSeeker_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textHuntress,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textCampain, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSlaver,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTyrant_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFireborn,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textIcelord, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textEntrail,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMites, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textCompies,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTeddies, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textJuggnaut,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSloth, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMauler,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDrone, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textGrunt_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSlave, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSoldier,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textCaptain, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textKing,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBastille, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTalSet,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSyra, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSymbiont,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textGuardian, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textRavage,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textCyclops, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLorddead,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMaggot, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textVile,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textElite, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBiobot,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textKillbot, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDeath,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textReaper, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMaw,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textRaptor, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSlag,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textClaw, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarclubs,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTurok_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMantidDrone,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textCampaigner, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFireborn_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMantidSoldier, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAdon_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLordOfTheDead, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textEliteGuard,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textGuardian_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textJuggernaut,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textOblivionSpawn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBastille_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSyra_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSymbiont_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTalSet_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textRaptor_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMantidMites, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textCaptureTheFlagDTime,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textCaptureTheFlagDTimes, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquireDTeamCaptures,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTagTheMonkeyDTime, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTagTheMonkeyDTimes,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquireDCreatureTags, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquireDFrag,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquireDFrags, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquireDTeamFrag,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquireDTeamFrags, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textIn02dSecondsOrLess,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textInDMinuteAnd02dSecondsOrLess, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textInDMinutesAnd02dSecondsOrLess,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textInDMinuteOrLess, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textInDMinutesOrLess,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWithDLife, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWithDLives,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDefeatS, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDefeatBothSAndS,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textEveryManForThemselves, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnProvingGrounds,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnBasicTraining, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnCrossroads,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnGrimRetreat, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnCathedral,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnFallout, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnBoxedSet,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnDireStraight, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnPrey,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnWarehouse, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnWaterTemple,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnBombShelter, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnTempered,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnEarthTemple, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnFireTemple,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnMystic, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnBottleneck,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnTightrope, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnThePit,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnLeapOfFaith, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnWickedDance,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnBunker, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnAmphitheater,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnFireWalker, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnCrypts,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnBreakdown, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnRetaliation,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnHopeless, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnMatrix,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnFathom, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnThePedestal,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnDefcon5, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnSpiritTemple,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnStronghold, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnCourtyard,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAchievementOnStarlight, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAttained15FragsIn5Minutes,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAttained25FragsIn10Minutes, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textNotGettingAnyFrags,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textKillingYourself5Times, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textComingInLast,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTotalFragAward, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTotalBeingKilledAward,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSniping10PeopleInARound, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textNotBeingKilledInARound,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDefeatedBastille, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDefeatedSyra,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDefeatedSymbiont, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDefeatedTalSet,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBeatingTheCooperativeScenario,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textEasy, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMedium,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textHard, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textRed,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textGreen, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textHorizontal,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textVertical, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLorez,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textHirez, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLetterbox,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textNo, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textYes,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textNovice_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textEasy_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textNormal, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textVeteran,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textExpert, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textArcade,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWheel, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTap,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMixed, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textControllerD,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textCtf, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTbl,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBl, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFt,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textGauntlet, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFragFest,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTimeTrial, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textPlayerD,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredEagleTalisman1Up, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredHalfEagleTalismanAnotherGives1Up,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredTheOtherEagleTalismanGained1Up,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredBearTalismanExplosiveAmmoUp5,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredCoyoteTalismanBulletAmmoUp50,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredCougarTalismanEnergyAmmoUp50,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredViperTalismanHealthMaxUp5,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredCooperativeTalisman, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredMinigameIcon,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredAssaultRifle, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredAssaultRifleRapidFireUpgrade,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredTekCrossBowSniperScope,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredGrenadeLauncher, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredGrenadeLauncherUpgrade,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredPlasmaRifle, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredPlasmaRifleScope,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredAcidSpitAttack, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredJumpClawAttack,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredRadioactiveFlareGun, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredRadioactiveFlareGunUpgrade,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredScorpionLauncher, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredScorpionLauncherMagnetUpgrade,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredFreezeGun, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredFreezeGunUpgrade,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredNapalmGel, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredMag60LaserSightUpgrade,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredChestburster, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredInflator,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredInflatorUpgrade, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredBoomerang,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredBoomerangUpgrade, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredMinigun,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredMinigunPersonalShieldUpgrade,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredShotgunStreetsweeperUpgrade,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredEmaciator, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredEmaciatorUpgrade,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAcquiredWarhammerRocketUpgrade,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textYouHaveUnlockedS, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMissionFailed,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textItemPreviouslyAcquired, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTeam,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textHit, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTags,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFlags, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textCongratulationsYouHaveCompletedFragFest,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textCongratulationsYouHaveCompletedTimeTrial,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textEnglish, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textPistolClip10Rounds,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textRifleClip10Rounds, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDifficultyEasy,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDifficultyNormal, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDifficultyHard,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textControlTypeExpert, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textControlTypeArcade,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textControlType, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textControlSideLeft,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textControlSideRight, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLookSpringOn,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLookSpringOff, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAutoAimOn,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAutoAimOff, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBloodColorOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBloodColorRed, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBloodColorGreen,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.text2PlyrLayoutHorz, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.text2PlyrLayoutVert,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textOpacityClear, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textOpacityOpaque,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textOpacity, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textControlStickHorzNorm,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textControlStickHorz, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textControlStickVertNorm,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textControlStickVert, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWeaponSelectQuick,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWeaponSelectNorm, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textResolutionLoRez,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textResolutionHiRez, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textResolutionHiRezLb,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textResolutionSmLoRez, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textResolutionLoRezLb,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBrightnessNorm, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBrightness,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLanguageEnglish, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textGoBack,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat2[0], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat2[1],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat2[2], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat2[3],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat2[4], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat2[5],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat2[6], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat2[7],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat2[8], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat2[9],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat2[10], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat2[11],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat2[12], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat2[13],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat2[14], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat2[15],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat2[16], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat2[17],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat2[18], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat2[19],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat2[20], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat2[21],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textChoose, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBlueBlood,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textRedBlood, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFinalScore,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBlueBloodScore, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textRedBloodScore,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textPleaseWait, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textPaused,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textResumeGame, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMissionStatus,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMissionObjectives, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textInventory,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLoad, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textOptions,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textCheats, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textQuit,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textInventory_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textOk,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textRageWars, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTurok2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.text51, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textNrwe,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[0], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[1],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[2], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[3],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[4], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[5],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[6], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[7],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[8], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[9],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[10], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[11],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[12], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[13],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[14], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[15],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[16], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[17],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[18], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[19],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[20], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[21],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[22], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[23],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[24], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[25],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[26], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[27],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[28], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textOtherGame,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat3[29], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat4[0],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat4[1], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat4[2],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat4[3], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat4[4],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat4[5], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat4[6],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat4[7], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat4[8],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat4[9], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat4[10],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat4[11], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat4[12],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat4[13], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat4[14],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat4[15], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textNoteInfo,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDeleteNote, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDifficultyEasy_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDifficultyNormal_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDifficultyHard_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textHealth, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLives,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTimeReadout, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textNoteInfo_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDeleteNote_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDeleteNote_repeat3,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textNameExt, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTimeCounter,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textName, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textType,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFrags, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textRank,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLoad_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDelete,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDelete_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textError,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textImportant, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textOk_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[0], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[1],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[2], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[3],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[4], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[5],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[6], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[7],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[8], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[9],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[10], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[11],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[12], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[13],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[14], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[15],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[16], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[17],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[18], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[19],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[20], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[21],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[22], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[23],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[24], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[25],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[26], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[27],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[28], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[29],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[30], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[31],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[32], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[33],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[34], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[35],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[36], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[37],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[38], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[39],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[40], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[41],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[42], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[43],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[44], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[45],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[46], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[47],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[48], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[49],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[50], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[51],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[52], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[53],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[54], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[55],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[56], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[57],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[58], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[59],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[60], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[61],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[62], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[63],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[64], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[65],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[66], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[67],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[68], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[69],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[70], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[71],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[72], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[73],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[74], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[75],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[76], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[77],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[78], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[79],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[80], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[81],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[82], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[83],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[84], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[85],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[86], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[87],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[88], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[89],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[90], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[91],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[92], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[93],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[94], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[95],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[96], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[97],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[98], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[99],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[100], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[101],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[102], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[103],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[104], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[105],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[106], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[107],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[108], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[109],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[110], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[111],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[112], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[113],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[114], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[115],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[116], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[117],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[118], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[119],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[120], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat5[121],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSave, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLoad_repeat3,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textHealth_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAmmo,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textGoBack_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat6[0],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat6[1], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat6[2],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat6[3], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat6[4],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat6[5], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat6[6],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat6[7], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat6[8],
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.emptyTextSlots_repeat6[9], (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textPmfShot,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBodyShot, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textHeadShot,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textArmShot, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textEdit,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.messageLinkWords_repeat4, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.messageLinkWords_repeat5,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.messageLinkWords_repeat6, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTaggedBy,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textYouTagged, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textKilledBy,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textYouKilled, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textYouKilledYourself,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textYouLostTheFlag, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textHeDroppedTheFlag,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAreYouSure, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textYouWantTo,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textYes_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textNo_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textCheats_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLoad_repeat4,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSave_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textEnterCheat,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textJoinNow, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWaiting,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textConnect, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textGoBack_repeat3,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textContinue, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textGameOver,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTimeXx, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDone,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textNewCheatEnabled, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textInvincibilityActivated,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textInfiniteLivesActivated, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAllWeaponsActivated,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textUnlimitedAmmoActivated, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAllKeysActivated,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBigHeadModeActivated, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTinyModeActivated,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textStickModeActivated, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBigHandsAndFeetModeActivated,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textPenAndInkModeActivated, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textGouraudModeActivated,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textJuansCheatActivated, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textZachAttackCheatActivated,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAllMapActivated, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBlackoutModeActivated,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMmmmTastyFrootyStripes, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarpLevel1Activated,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarpLevel2Activated, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarpLevel3Activated,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarpLevel4Activated, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarpLevel5Activated,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarpLevel6Activated, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarpQueenBossActivated,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarpBlindOneBossActivated, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarpMotherBossActivated,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarpPrimagenBossActivated, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarpCreditsActivated,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textInvincibilityOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textInvincibilityOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textInfiniteLivesOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textInfiniteLivesOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAllWeaponsOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAllWeaponsOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textUnlimitedAmmoOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textUnlimitedAmmoOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAllSpecialObjectsOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAllSpecialObjectsOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBigHeadModeOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBigHeadModeOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTinyModeOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTinyModeOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textStickModeOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textStickModeOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBigHandsFeetModeOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBigHandsFeetModeOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textPenAndInkModeOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textPenAndInkModeOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textGouraudModeOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textGouraudModeOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textJuansCheatOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textJuansCheatOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textZachAttackCheatOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textZachAttackCheatOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAllMapOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAllMapOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBlackoutOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBlackoutOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFrootyStripesOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFrootyStripesOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarpPortOfAdia, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarpRiverOfSouls,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarpDeathMarshes, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarpLairOfTheBlindOnes,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarpHiveOfTheMantids, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarpPrimagenSLightship,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarpQueenBoss, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarpBlindOneBoss,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarpMotherBoss, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarpPrimagenBoss,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textWarpCredits, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textYouFragged,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textYouTagged_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTotals,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textOne0000, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTwo0000,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textThree0000, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFour0000,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTags0000, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFrags0000,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDeaths0000, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSuicides0000,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textOne0000_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTwo0000_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textThree0000_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFour0000_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTags0000_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFrags0000_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDeaths0000_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSuicides0000_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textOne0000_repeat3, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTwo0000_repeat3,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textThree0000_repeat3, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFour0000_repeat3,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTags0000_repeat3, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFrags0000_repeat3,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDeaths0000_repeat3, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSuicides0000_repeat3,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textOne0000_repeat4, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTwo0000_repeat4,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textThree0000_repeat4, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFour0000_repeat4,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTags0000_repeat4, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFrags0000_repeat4,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDeaths0000_repeat4, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSuicides0000_repeat4,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textPlayer1, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textPlayer2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textPlayer3, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textPlayer4,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSingle, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textNewGame,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLoad_repeat5, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMulti,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDeathmatch, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSelectGameType,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBloodLust, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textBloodLust_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTimedGameNone, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFragLimitNone,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLevelRandom, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLevelExperimentata,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLevelMoonlitMayhem, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLevelCloseQuartered,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLevelVulcanSForge, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLevelTeleportastic,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLevelMirrororrim, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLevelFishInABarrel,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLevelH2Whoa, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLevelEscheria,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLevelMoshCrypt, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLevelSquaresCubed,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLevelCrazyEight, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLevelBullseye,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTextureSetCastle, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTextureSetSteelMill,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTextureSetOakFort, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTextureSetCatacombs,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTextureSetJailhouse, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTextureSetBigCity,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTextureSetRedDragon, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTextureSetPaintball,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTextureSetMrHappy, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textCrosshairsOn,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textCrosshairsOff, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textStartGame,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textGoBack_repeat4, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFragTag,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFragTag_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTagLimitNone,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLevelMadhouse, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLevelSnap,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLevelSneaksNLadders, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLevelPrimattica,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLevelCrossfire, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLevelYNGWTSF,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTeamBlood, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textCustomizeWeapons,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textChargeDartRifleOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textChargeDartRifleOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFirestormOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textFirestormOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAssaultRifleOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textAssaultRifleOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textPlasmaRifleOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textPlasmaRifleOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textCerebralBoreOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textCerebralBoreOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textGrenadeLauncherOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textGrenadeLauncherOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textScorpionLauncherOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textScorpionLauncherOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTorpedoLauncherOn, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTorpedoLauncherOff,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textTraining, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLevelRandom_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLevelArchery, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLevelShooting,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLevelDecathalon, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textNoOfLaps,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textStartGame_repeat2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textGoBack_repeat5,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLoad_repeat6, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textOptions_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textCheats_repeat3, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textCheckPoint,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSavePoint, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSoundOptions,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMusicVolumeOff, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMusicVolumeMax,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMusicVolumeNorm, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMusicVolume,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSfxVolumeOff, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSfxVolumeMax,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSfxVolumeNorm, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSfxVolume,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSpeechVolumeOff, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSpeechVolumeMax,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSpeechVolumeNorm, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSpeechVolume,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMusicNone, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMusic,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textIndexNone, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textSpeechNone,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMissionComplete, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textMissionFailed_repeat2,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDefendTheTotem, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textPlayerSpeed,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textPlayerSpeedDefault, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textDefault,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textLowHealth, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.textPunctuation32,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.text0, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.text1,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.text2, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.text3,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.text4, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.text5,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.text6, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.text7,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.text8, (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.text9,
         (void *)&s_SkyPostscaledscreenmessageFREEZEKLMOFormatText.resourceAddressWords }, { { { 65, 0, 0, 0 },
             (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[0].character },
         { { 66, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[1].character },
         { { 67, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[2].character },
         { { 68, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[3].character },
         { { 69, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[4].character },
         { { 70, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[5].character },
         { { 71, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[6].character },
         { { 72, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[7].character },
         { { 73, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[8].character },
         { { 74, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[9].character },
         { { 75, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[10].character },
         { { 76, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[11].character },
         { { 77, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[12].character },
         { { 78, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[13].character },
         { { 79, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[14].character },
         { { 80, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[15].character },
         { { 81, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[16].character },
         { { 82, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[17].character },
         { { 83, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[18].character },
         { { 84, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[19].character },
         { { 85, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[20].character },
         { { 86, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[21].character },
         { { 87, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[22].character },
         { { 88, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[23].character },
         { { 89, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[24].character },
         { { 90, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[25].character },
         { { 48, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[26].character },
         { { 49, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[27].character },
         { { 50, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[28].character },
         { { 51, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[29].character },
         { { 52, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[30].character },
         { { 53, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[31].character },
         { { 54, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[32].character },
         { { 55, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[33].character },
         { { 56, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[34].character },
         { { 57, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[35].character },
         { { 2, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[36].character },
         { { 3, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[37].character },
         { { 4, 0, 0, 0 }, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.characterEntries[38].character } },
     { 0, (void *)&g_pakAdjustownernotificationoptionDataConstantWords.references2[0], (void *)&s_fadeOutCinemaTextHint[20],
         0, 0, 0 }, 0x7175042E, { 101, 111, 115, 82, 0, 0, 0, 0 } };
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* Older build's rodata of C:/Projects/DM/n64/Source/fx.cpp. */
extern char g_fxSourcePath[36];
extern char g_fxAssertThisNotNull[8];
extern char g_fxAssertInfoNotNull[8];
extern char g_fxAssertInfoPointsNotNull[16];
extern char g_fxAssertInfoPointCountNonZero[16];
extern char g_fxAssertInfoStartHotPointsNotNull[24];
extern char g_fxAssertInfoEndHotPointsNotNull[20];
extern float g_fxSwooshHotPointConstants[7];
extern char g_fxAssertStartHotPointNotNull[16];
extern char g_fxAssertStartHotPointOnSwooshNode[56];
extern char g_fxAssertEndHotPointNotNull[16];
extern char g_fxAssertEndHotPointOnSwooshNode[56];
extern float g_fxSwooshEdgeConstants[28];
extern char g_fxAssertEdgeANotNull[8];
extern char g_fxAssertEdgeBNotNull[8];
extern char g_fxAssertCameraNotNull[8];
extern char g_fxAssertEdgesApart[68];
extern float g_fxEdgeSideSigns[3];
extern char g_fxAssertPrevEdgeNotNull[12];
extern char g_fxAssertEdgeNotNull[8];
extern float g_fxSwooshStretchConstants[2];
extern char g_fxAssertSwooshTextureStretched[68];
extern char g_fxAssertRomSwooshNotNull[12];
extern char g_fxAssertSwooshTextureSetValid[28];
extern char g_fxAssertSwooshHasEdgePair[40];
extern char g_fxAssertUnreachable[8];
extern char g_fxAssertEdge1NotNull[8];
extern char g_fxAssertEdge2NotNull[8];
extern char g_fxAssertMeTextureNotNull[12];
extern float g_fxTextureUnitScale[1];
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* Older build's rodata pool. */
extern unsigned int g_fxTextureSwitchCases[6];
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* Older build's rodata of C:/Projects/DM/n64/Source/fx.cpp. */
extern char g_fxAssertFreeVertsNonNegative[24];
extern char g_fxAssertSwooshNodeSet[40];
extern float g_fxSwooshNodeConstants[3];
extern char g_fxAssertParticleType[40];
extern char g_fxAssertParticleNotNull[12];
extern char g_fxAssertRomHotPointNotNull[16];
extern char g_fxAssertRomEndHotPointNotNull[16];
extern char g_fxAssertSeveralCamerasActive[40];
extern char g_fxAssertDisplayListGrows[28];
extern float g_fxDisplayListColorScale[3];
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* Older build's rodata pool. */
extern unsigned int g_fxDisplayListSwitchCases[9];
#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* Older build's rodata of C:/Projects/DM/n64/Source/fx.cpp. */
extern float g_fxImpactColorConstants[11];
extern char g_fxAssertImpactMaterialInRange[44];
#endif

/* Retained data for this translation unit. */

const float g_ribbonInitializationConstants[2] = {
    1.0f, -3.0f,
};

const float g_ribbonUpdateUnitConstant[1] = {
    1.0f,
};

const float g_linkedNodeTransformConstants[2] = {
    0.01f, 0.29257143f,
};

const float g_texturedRibbonDrawConstants[4] = {
    3.125f, 32.0f, 1.0f, 1.0f,
};

const float g_coloredRibbonWidthScaleFactor[1] = {
    3.125f,
};

const float g_Fx_DetachParticleSwooshesConstants[4] = {
    0.01f, 0.29257143f, 0.01f, 0.29257143f,
};

const float g_FxAddparticleribbonsamplesWords[2] = {
    0.01f, 0.29257143f,
};

const float k_fxSpawnimpactmarkDataFloatConstantWords[6] = {
    6.144f, 3.125f, 32.0f, 1.0f, 0.01f, 0.29257143f,
};

const float k_fxAppendattachedtransformDataFloatConstantWords[2] = {
    0.01f, 0.29257143f,
};
