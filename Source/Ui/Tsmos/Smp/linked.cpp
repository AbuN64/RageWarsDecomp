#include "Engine/graphics_math.h"
#include "Cache/cache_allocateresourceat.h"
#include "Anim/animation_frame.h"
#include "include_asm.h"
#include "Common/effectcontribution.h"
#include "Render/animation_frame_and_ribbon_views.h"
#include "types.h"
#include "Common/sharedplayer.h"
#include "Common/runtime_declarations.h"
#include "Common/weapon_screen_message_operations.h"
#include "Common/gameplay_camera.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Common/propgeometry.h"
#include "Common/hud_effects.h"
#include "Fx/normalize_vector.h"
#include <PR/gbi.h>
#include "Common/sessionhandlerrow.h"
#include "Common/residentstate.h"
#include "Render/ribbon_draw.h"
#include "Fx/fx_drawboundedparticlequads.h"
#include "Fx/fx_spawnimpactmark.h"
#include "Game/builddirectionmatrix.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Graphu64/graphu64_packfixedmatrix.h"
#include "Textload/textload_readtextureanimationinfo.h"
#include "Textload/textload_requesttexturevariationsync.h"
#include "Texture/textload_loadtextureframe.h"
#include "Texture/textload_loadtextureframetiles.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Common/approachlocation.h"
#include "Common/graphics_matrix_and_vector_math.h"
#include "Rsp/random_direction_and_affine_math.h"
#include "Common/triple.h"
#include "Engine/graphu64_packfixedmatrix.h"

/* Interpolates morph vertex positions and shades between two key frames. */

/* Rebuilds one morphing mesh's vertices from its two key frames. The blend weight eases in and out
   of the clock's position in the actor's track, and again of the actor's own position in it while
   that is still inside the track; every vertex is then the first frame's position carried that far
   toward the second's, its two texture coordinates are the mesh's own scales times the caller's
   scale and times a fade that steps once a vertex, and its shade is the blend of the vertex's two
   shades. While Geometry_GetViewEffect holds, the shade is instead greyed: red and green are cleared and
   blue carries the blended sum of the three channels over three, as an unsigned divide. */
























extern void Graphu64_SubtractVectors(CVector3 *, CVector3 *, CVector3 *);










extern void Linked_BuildRibbonSegmentMatrix(RibbonSegment *, RibbonSegment *, struct GameplayCamera *, void *);



void *Linked_AppendRibbonSegment(void *effectSystem, void *ribbon, void *local) {
    CVector3 segmentDelta;
    f32 segmentDistance;
    f32 previousSegmentDistance;
    f32 accumulatedDistance;
    void *previousSegment;
    char *segment;
    char *ribbonSegmentResult;

    ribbonSegmentResult = Fx_AllocateRibbonSegment(effectSystem, (s32)ribbon);
    segment = ribbonSegmentResult;
    if (ribbonSegmentResult != 0) {
        ((RibbonActor *)(ribbon))->retries = 0;
        ((RibbonSegment *)(segment))->remainingLifetime = ((struct CROMSwoosh_t *) ((RibbonActor *) ribbon)->track)->segmentLifetime;
        ((RibbonSegment *)(segment))->attachedEntity = 0;
        Graphu64_GetMatrixTranslation(local, &((RibbonSegment *)(segment))->position.x);
        if (((RibbonActor *)(ribbon))->flags & 4) {
            Graphu64_GetMatrixScale(local, &((RibbonSegment *)(segment))->scale);
        } else {
            Graphu64_ConvertMatrixToFixed(local, &((RibbonSegment *)(segment))->matrices[0]);
            Graphu64_ConvertMatrixToFixed(local, &((RibbonSegment *)(segment))->matrices[1]);
        }
        previousSegment = *(void **)segment;
        ((RibbonSegment *)(segment))->lengthWord = 0;
        ((RibbonSegment *)(segment))->fraction = 0.0f;
        if (previousSegment != 0) {
            Graphu64_SubtractVectors(&segmentDelta, &((RibbonSegment *)(segment))->position, &((RibbonSegment *)(previousSegment))->position);
            segmentDistance = Gu_Sqrtf((segmentDelta.x * segmentDelta.x) + (segmentDelta.y * segmentDelta.y) + (segmentDelta.z * segmentDelta.z));
            ((RibbonSegment *)(previousSegment))->length = segmentDistance;
            ((RibbonActor *)(ribbon))->length += segmentDistance;
        }
        if (((struct CROMSwoosh_t *) ((RibbonActor *) ribbon)->track)->kind == 0) {
            if (((RibbonActor *)(ribbon))->length > 0.0f) {
                accumulatedDistance = 0.0f;
                segment = (char *)((RibbonActor *)(ribbon))->tail;
                if (segment != 0) {
                    do {
                        ((RibbonSegment *)(segment))->fraction = accumulatedDistance / ((RibbonActor *)(ribbon))->length;
                        previousSegmentDistance = ((RibbonSegment *)(segment))->length;
                        segment = (char *)((RibbonSegment *)(segment))->next;
                        accumulatedDistance += previousSegmentDistance;
                    } while (segment != 0);
                }
            }
        } else {
            if (previousSegment != 0) {
                ((RibbonActor *)(ribbon))->phase += ((RibbonSegment *)(previousSegment))->length * g_ribbonDistancePhaseScale;
            }
            ((RibbonSegment *)(segment))->fraction = ((RibbonActor *)(ribbon))->phase;
        }
    }
    return ribbonSegmentResult;
}

void Linked_BuildColoredRibbonVertices(RibbonActor *actor, RibbonSegment *clock, Vtx *out, Morph *morph) {
    f32 a[3];
    f32 b[3];
    f32 weight;
    f32 t;
    Blend *blend;
    Shade *from;
    Key *key;
    s32 count;
    u32 grey;
    s32 red;
    s32 green;
    s32 blue;

    weight = 0.5f - Math_Cosf(clock->remainingLifetime / actor->track->segmentLifetime * 3.1415927f) * 0.5f;
    if (actor->time <= actor->track->minimumLifetime) {
        weight = weight * (0.5f - Math_Cosf(actor->time / actor->track->minimumLifetime * 3.1415927f) * 0.5f);
    }
    count = morph->count;
    blend = morph->blends;
    t = 1.0f - weight;
    while (--count != -1) {
        key = &morph->second[blend->second];
        Graphu64_ScaleVector(a, &morph->first[blend->first], morph->firstFrame);
        Graphu64_ScaleVector(b, key, morph->secondFrame);
        out->v.ob[0] = (s16) (a[0] + t * (b[0] - a[0]));
        out->v.ob[1] = (s16) (a[1] + t * (b[1] - a[1]));
        out->v.ob[2] = (s16) (a[2] + t * (b[2] - a[2]));
        from = &blend->from;
        if (Geometry_GetViewEffect() != 0) {
            blue = blend->from.b;
            green = blend->from.g;
            red = blend->from.r;
            grey = (f32) (blue + green + red)
                 + t * (f32) ((blend->to.b - blue) + (blend->to.g - green) + (blend->to.r - red));
            out->v.cn[0] = 0;
            out->v.cn[1] = 0;
            out->v.cn[2] = grey / 3;
            out->v.cn[3] = (u32) ((f32) from->a + t * (f32) (blend->to.a - from->a));
        } else {
            out->v.cn[0] = (u32) ((f32) blend->from.r + t * (f32) (blend->to.r - blend->from.r));
            out->v.cn[1] = (u32) ((f32) blend->from.g + t * (f32) (blend->to.g - blend->from.g));
            out->v.cn[2] = (u32) ((f32) blend->from.b + t * (f32) (blend->to.b - blend->from.b));
            out->v.cn[3] = (u32) ((f32) from->a + t * (f32) (blend->to.a - from->a));
        }
        blend++;
        out++;
    }
}

void Linked_BuildTexturedRibbonVertices(RibbonActor *actor, RibbonSegment *clock, Vtx *out, f32 scale, Morph *morph) {
    f32 a[3];
    f32 b[3];
    f32 weight;
    f32 t;
    f32 fade;
    Blend *blend;
    Shade *from;
    Key *key;
    s32 count;
    u32 grey;
    s32 red;
    s32 green;
    s32 blue;

    weight = 0.5f - Math_Cosf(clock->remainingLifetime / actor->track->segmentLifetime * 3.1415927f) * 0.5f;
    if (actor->time <= actor->track->minimumLifetime) {
        weight = weight * (0.5f - Math_Cosf(actor->time / actor->track->minimumLifetime * 3.1415927f) * 0.5f);
    }
    fade = 0.0f;
    count = morph->count;
    blend = morph->blends;
    t = 1.0f - weight;
    while (--count != -1) {
        key = &morph->second[blend->second];
        Graphu64_ScaleVector(a, &morph->first[blend->first], morph->firstFrame);
        Graphu64_ScaleVector(b, key, morph->secondFrame);
        out->v.ob[0] = (s16) (a[0] + t * (b[0] - a[0]));
        out->v.ob[1] = (s16) (a[1] + t * (b[1] - a[1]));
        out->v.ob[2] = (s16) (a[2] + t * (b[2] - a[2]));
        out->v.tc[0] = (s16) (morph->textureScaleS * scale);
        out->v.tc[1] = (s16) (morph->textureScaleT * fade);
        from = &blend->from;
        if (Geometry_GetViewEffect() != 0) {
            blue = blend->from.b;
            green = blend->from.g;
            red = blend->from.r;
            grey = (f32) (blue + green + red)
                 + t * (f32) ((blend->to.b - blue) + (blend->to.g - green) + (blend->to.r - red));
            out->v.cn[0] = 0;
            out->v.cn[1] = 0;
            out->v.cn[2] = grey / 3;
            out->v.cn[3] = (u32) ((f32) from->a + t * (f32) (blend->to.a - from->a));
        } else {
            out->v.cn[0] = (u32) ((f32) blend->from.r + t * (f32) (blend->to.r - blend->from.r));
            out->v.cn[1] = (u32) ((f32) blend->from.g + t * (f32) (blend->to.g - blend->from.g));
            out->v.cn[2] = (u32) ((f32) blend->from.b + t * (f32) (blend->to.b - blend->from.b));
            out->v.cn[3] = (u32) ((f32) from->a + t * (f32) (blend->to.a - from->a));
        }
        blend++;
        out++;
        fade = fade + morph->step;
    }
}

s32 Linked_UpdateRibbonLifetime(s32 owner, RibbonActor *state) {
    LevelActor *object;
    RibbonSegment *node;
    RibbonSegment *next;
    f32 saved_step;
    f32 zero;
    f32 decay;
    f32 cutoff;
    f32 value;
    f32 updated;

    saved_step = g_frameElapsedTime;
    if (state->flags & 2) {
        g_frameElapsedTime = saved_step * g_particleSimulationTimeScale;
    }
    if (state->flags & 1) {
        g_frameElapsedTime *= (&g_frameElapsedTime)[1];
    }
    if (state->flags & 8) {
        state->retries++;
        if (state->retries >= 3) {
            state->object = 0;
        }
    }

    if (state->endpoint >= 0.0f) {
        state->frame += g_frameElapsedTime;
    }
    state->time -= g_frameElapsedTime;
    if (state->time < 0.0f) {
        state->time = 0.0f;
    }

    node = state->tail;
    if (node != 0) {
        zero = 0.0f;
        decay = g_ribbonNodeTransformDecayConstants[1];
        cutoff = g_ribbonNodeTransformCutoffConstants[0];
        do {
            next = node->next;
            if (state->time <= zero && node->remainingLifetime > zero) {
                node->remainingLifetime = zero;
            }
            value = node->remainingLifetime;
            if (value <= zero) {
                updated = value - decay;
                node->remainingLifetime = updated;
                if (updated < cutoff) {
                    Fx_FreeRibbonSegment(owner, state, node);
                }
            } else {
                updated = value - g_frameElapsedTime;
                node->remainingLifetime = updated;
                if (updated < zero) {
                    node->remainingLifetime = zero;
                }
            }
            node = next;
        } while (node != 0);
    }

    object = (LevelActor *)state->object;
    if (state->object != 0 && (state->flags & 1) &&
        !(object->flags & 0x200)) {
        Fx_DetachEffectObject(state);
    }
    g_frameElapsedTime = saved_step;

    if (state->pointCount == 0) {
        if (state->time != 0.0f) {
            if (state->object == 0) {
                return 0;
            }
        } else {
            return 0;
        }
    }
    return 1;
}

void Linked_BuildRibbonSegmentMatrix(RibbonSegment *firstSegment, RibbonSegment *secondSegment, GameplayCamera *camera, void *matrix) {
    f32 setup[4];
    CVector3 first;
    CVector3 basis;
    CVector3 cross;
    CVector3 result;
    f32 neg_y;
    f32 neg_z;

    Graphu64_SubtractVectors(&first, &firstSegment->position,
                  &secondSegment->position);
    Graphu64_NormalizeVec3(&first);
    setup[0] = 0;
    setup[1] = 0;
    setup[2] = g_ribbonNodeTransformCutoffConstants[1];
    Graphu64_TransformDirection(camera->inverseViewOrient, setup, &basis);
    neg_y = -basis.y;
    neg_z = -basis.z;
    basis.y = neg_y;
    basis.z = neg_z;
    Graphu64_ScaleVector(&cross, &basis,
                  basis.x * first.x + neg_y * first.y + neg_z * first.z);
    Graphu64_SubtractVectors(&cross, &first, &cross);
    Graphu64_NormalizeVec3(&cross);
    Graphu64_CrossVectors(&result, &basis, &cross);
    Graphu64_NormalizeVec3(&result);
    Graphu64_ScaleVector(&result, &result, firstSegment->scale.x);
    Graphu64_ScaleVector(&cross, &cross, firstSegment->scale.y);
    Graphu64_ScaleVector(&basis, &basis, firstSegment->scale.z);
    Graphu64_IdentityMatrix(matrix);
    ((Matrix *)matrix)->m[0] = result.x;
    ((Matrix *)matrix)->m[1] = result.y;
    ((Matrix *)matrix)->m[2] = result.z;
    ((Matrix *)matrix)->m[4] = cross.x;
    ((Matrix *)matrix)->m[5] = cross.y;
    ((Matrix *)matrix)->m[6] = cross.z;
    ((Matrix *)matrix)->m[8] = basis.x;
    ((Matrix *)matrix)->m[9] = basis.y;
    ((Matrix *)matrix)->m[10] = basis.z;
    ((Matrix *)matrix)->m[12] = firstSegment->position.x;
    ((Matrix *)matrix)->m[13] = firstSegment->position.y;
    ((Matrix *)matrix)->m[14] = firstSegment->position.z;
}

struct GameplayCamera;

void Linked_UpdateRibbonMatrices(void *ribbon, void *camera) {
    f32 matrix[16];
    RibbonSegment *first;
    RibbonSegment *next;
    RibbonActor *state = ribbon;

    if (state->pointCount < 2) {
        return;
    }

    first = state->tail;
    next = first->next;
    if (first != 0) {
        Graphu64_BuildScaleMatrix(matrix, first->scale.x, first->scale.y, first->scale.z);
    } else {
        Graphu64_IdentityMatrix(matrix);
    }

    while (first != 0) {
        RibbonSegment *a;
        RibbonSegment *b;

        if (next == 0) {
            break;
        }
        a = first;
        b = next;
        if (first == 0) {
            goto no_pair;
        }
        if (first->position.x != next->position.x || first->position.y != next->position.y) {
            goto boundary;
        }
z_test:
        if (a->position.z != b->position.z) {
            goto boundary;
        }
        a = b;
        b = b->next;
        if (a == 0) {
            goto no_pair;
        }
        if (b == 0 || a->position.x != b->position.x || a->position.y != b->position.y) {
            goto boundary;
        }
        goto z_test;
boundary:
        if (a != 0 && b != 0) {
            Linked_BuildRibbonSegmentMatrix(a, b, camera, matrix);
            goto apply;
        }
no_pair:
        {
            matrix[12] = first->position.x;
            matrix[13] = first->position.y;
            matrix[14] = first->position.z;
        }
apply:
        Graphu64_ConvertMatrixToFixed(matrix, first->matrices[g_lightingBufferIndex].m);
        first = next;
        next = first->next;
    }

    matrix[12] = first->position.x;
    matrix[13] = first->position.y;
    matrix[14] = first->position.z;
    Graphu64_ConvertMatrixToFixed(matrix, first->matrices[g_lightingBufferIndex].m);
}

extern f32 g_ribbonPositiveLayerScale, g_ribbonNegativeLayerScale;

/* Updates a chain of linked nodes: nodes following a source take its matrix (scaled by a size flag) or copy the
 * other matrix buffer, then each node's distance to its parent is measured and summed into the owner's total. */
static inline void Render_UpdateLinkedSource(RibbonActor *owner, RibbonSegment *node, Shared_Particle *source) {
    f32 matrix[16];
    f32 scale;
    Graphu64_ConvertMatrixToFloat(matrix, &source->mtx[g_lightingBufferIndex]);
    scale = g_ribbonPositiveLayerScale;
    if (source->desc->renderModel != 0) {
        scale = g_ribbonNegativeLayerScale;
    }
    ScaleMatrixLocal(matrix, scale, scale, scale);
    Graphu64_ClampMatrixToFixedRange(matrix);
    Graphu64_GetMatrixTranslation((char *)matrix, &node->position.x);
    if (owner->flags & 4) {
        Graphu64_GetMatrixScale(matrix, &node->scale.x);
    } else {
        Graphu64_ConvertMatrixToFixed(matrix, node->matrices[g_lightingBufferIndex].m);
    }
}
void Linked_UpdateLinkedNodeTransforms(RibbonActor *owner) {
    RibbonSegment *node;
    RibbonSegment *parent;
    void *source;
    s32 changed = 0;
    f32 delta[3];
    owner->length = 0.0f;
    for (node = owner->tail; node != 0; node = node->next) {
        source = node->attachedEntity;
        if (source != 0) {
            if (source == (void *)-1) {
                node->matrices[g_lightingBufferIndex] = node->matrices[g_lightingBufferIndex ^ 1];
                node->attachedEntity = 0;
            } else {
                Render_UpdateLinkedSource(owner, node, source);
            }
            changed = 1;
            node->remainingLifetime = owner->track->segmentLifetime;
        }
        parent = node->previous;
        if (parent != 0) {
            f32 length;
            Graphu64_SubtractVectors((CVector3 *)delta, &node->position, &parent->position);
            length = Gu_Sqrtf(delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2]);
            parent->length = length;
            owner->length += length;
        }
    }
    if (changed) {
        owner->time = owner->track->initialLifetime;
    }
}


s32 Fx_SelectAnimationFrame(RibbonActor *state, struct CROMSwoosh_t *definition, s32 *frame_count);
/* Draws a textured ribbon: spaces the texture along the tail by length, picks the animation frame, sets the
 * combiner and colours (greyscale on a monochrome camera), then emits two vertex rows per clock node and the
 * triangle strip between them. */
void Linked_DrawTexturedRibbon(RibbonWorld *pool, RibbonActor *actor, GameplayCamera *camera) {
    struct Shared_AnimInfo info;
    Morph storage;
    struct Shared_AnimInfo *anim;
    void *model;
    struct CROMSwoosh_t *track;
    RibbonSegment *clock, *next, *node;
    Vtx *vertices;
    f32 offset;
    f32 period;
    u32 grey;
    s32 count, edges, i, used, frame;

    track = actor->track;
    used = 0;
    if (track->kind == 2 && 0.0f < actor->length) {
        offset = 0.0f;
        for (node = actor->tail; node != 0; node = node->next) {
            node->fraction = offset / actor->length;
            offset += node->length;
        }
    }
    model = Textload_RequestTextureVariation(&actor->model, -1);
    if (model == 0) return;
    Textload_ReadTextureAnimationInfo(model, &info);
    anim = &info;
    storage.blends = actor->track->blends;
    storage.count = actor->track->count;
    if (actor->flags & 2) { storage.first = actor->first; storage.second = actor->second; }
    else { storage.first = actor->first; storage.second = actor->first; }
    storage.scaleS = actor->track->scaleS * g_texturedRibbonTextureCoordinateScale;
    storage.scaleT = actor->track->scaleT * g_texturedRibbonTextureCoordinateScale;
    if (anim != 0) {
        storage.textureScaleS = 1 << (anim->frame->shiftS + 5);
        storage.textureScaleS = storage.textureScaleS * actor->track->textureScale - g_ribbonTextureCoordinateOffset;
        storage.textureScaleT = 1 << (anim->frame->shiftT + 5);
        storage.step = g_ribbonInterpolationUnit / (storage.count - g_ribbonInterpolationUnit);
    }
    period = g_ribbonTexturePeriod;
    while (actor->phase >= period) actor->phase -= period;
    gDPPipeSync(g_displayListCursor++);
    switch (info.frame->kind) {
    case 3:
        Geometry_SetCombineMode(41);
        if (camera->monochrome) {
            grey = track->env[0] + track->env[1] + track->env[2];
            gDPSetEnvColor(g_displayListCursor++, 0, 0, grey / 3, 255);
            grey = track->prim[0] + track->prim[1] + track->prim[2];
            gDPSetPrimColor(g_displayListCursor++, 0, 0, 0, 0, grey / 3, 255);
        } else {
            gDPSetEnvColor(g_displayListCursor++, track->env[0], track->env[1], track->env[2], 255);
            gDPSetPrimColor(g_displayListCursor++, 0, 0, track->prim[0], track->prim[1], track->prim[2], 255);
        }
        break;
    case 0:
    case 1:
        Geometry_SetCombineMode(40);
        break;
    }
    Geometry_SetModePreset(13);
    clock = actor->clock;
    count = track->count;
    next = clock->previous;
    frame = Fx_SelectAnimationFrame((RibbonActor *)actor, (struct CROMSwoosh_t *)track, &info.count);
#if defined(VERSION_US_REV1)
    Textload_LoadTextureFrameTiles(&actor->model, model, frame, 0, 0xFFFF, 0xFFFF, 0, 0, 0);
#else
    Textload_LoadTextureFrame(&actor->model, model, frame, 0, 0xFFFF, 0xFFFF, 0, 0, 0);
#endif
    edges = count - 1;
    gSPMatrix(g_displayListCursor++, &clock->matrices[g_lightingBufferIndex], G_MTX_LOAD);
    while (clock != 0 && next != 0 && 0.0f < clock->remainingLifetime && 0.0f < next->remainingLifetime && used + count * 2 < 32) {
        f32 scale;
        vertices = Fx_AllocateRibbonVertices(pool, count);
        if (vertices == 0) break;
        Linked_BuildTexturedRibbonVertices(actor, clock, vertices, clock->fraction, &storage);
        used += count;
        gSPVertex(g_displayListCursor++, vertices, count, 0);
        gSPMatrix(g_displayListCursor++, &next->matrices[g_lightingBufferIndex], G_MTX_LOAD);
        vertices = Fx_AllocateRibbonVertices(pool, count);
        if (vertices == 0) break;
        scale = next->fraction;
        while (clock->fraction < scale) scale -= period;
        Linked_BuildTexturedRibbonVertices(actor, next, vertices, scale, &storage);
        used += count;
        gSPVertex(g_displayListCursor++, vertices, count, count);
        for (i = 0; i < edges; i++) {
            Gfx *cmd = g_displayListCursor++;
            cmd->words.w0 = (((i * 2 & 255) << 16) | (((count + i) * 2 & 255) << 8) | ((count + i + 1) * 2 & 255)) | (G_TRI2 << 24);
            cmd->words.w1 = ((i * 2 & 255) << 16) | (((count + i + 1) * 2 & 255) << 8) | ((i + 1) * 2 & 255);
        }
        if (actor->track->closed) {
            Gfx *cmd = g_displayListCursor++;
            cmd->words.w0 = (((i * 2 & 255) << 16) | (((count + i) * 2 & 255) << 8) | (count * 2 & 255)) | (G_TRI2 << 24);
            cmd->words.w1 = ((i * 2 & 255) << 16) | ((count * 2 & 255) << 8);
        }
        clock = next;
        next = clock->previous;
    }
    Cache_UnlockResource(0, model);
}

const float g_ribbonAppendDistanceScale[1] = {
    0.005f,
};
