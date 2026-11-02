#include "ANIM/ANIMATION_FRAME.H"
#include "include_asm.h"
#include "COMMON/EFFECTCONTRIBUTION.H"
#include "RENDER/LINKED_DRAWTEXTUREDRIBBON.H"
#include "RENDER/ANIMATION_FRAME_AND_RIBBON_VIEWS.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "COMMON/PROPGEOMETRY.H"
#include "COMMON/OBJRECAT18V6.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include <PR/gbi.h>
#include "COMMON/SESSIONHANDLERROW.H"
#include "COMMON/RESIDENTSTATE.H"
#include "RENDER/RIBBON_DRAW.H"

extern void *Fx_AllocateRibbonSegment(void *effectSystem, s32 ribbonAddress);

extern void Graphu64_GetMatrixTranslation(char *object, f32 *output);

extern void Graphu64_GetMatrixScale(void *matrix, f32 *scaleOut);

extern void Graphu64_SubtractVectors(CVector3 *difference, CVector3 *leftVector, CVector3 *rightVector);

extern f32 Gu_Sqrtf(f32);

/* Interpolates morph vertex positions and shades between two key frames. */




















/* Rebuilds one morphing mesh's vertices from its two key frames. The blend weight eases in and out
   of the clock's position in the actor's track, and again of the actor's own position in it while
   that is still inside the track; every vertex is then the first frame's position carried that far
   toward the second's, its two texture coordinates are the mesh's own scales times the caller's
   scale and times a fade that steps once a vertex, and its shade is the blend of the vertex's two
   shades. While Geometry_GetViewEffect holds, the shade is instead greyed: red and green are cleared and
   blue carries the blended sum of the three channels over three, as an unsigned divide. Written
   from the assembly: the second frame's key is taken before the first frame's sample is read so
   that it lives across that call, and the first shade is reached through its own pointer, which is
   what keeps the blend cursor itself in a register rather than the whole record being addressed
   four bytes on. */




















extern void Fx_FreeRibbonSegment(s32, StateSmpUpdateRibbonLifetime *, Nodes *);

extern void Fx_DetachEffectObject(StateSmpUpdateRibbonLifetime *);

extern void Graphu64_SubtractVectors(CVector3 *, CVector3 *, CVector3 *);


extern void Graphu64_TransformDirection(void *, void *, void *);

extern void Graphu64_CrossVectors(CVector3 *, CVector3 *, CVector3 *);

extern void Graphu64_IdentityMatrix(void *);

extern void Graphu64_BuildScaleMatrix(void *, f32, f32, f32);

extern void Linked_BuildRibbonSegmentMatrix(Node438C *, Node438C *, struct GameplayCamera *, void *);
extern void Graphu64_ScaleVector(struct CVector3_t *,struct CVector3_t *,f32);
extern void Graphu64_ConvertMatrixToFixed(void *, f32 *);

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
        ((TexturedRibbonOwnerView *)(ribbon))->clearedWord = 0;
        ((TexturedRibbonStateView *)(segment))->value = ((struct TexturedRibbonResourceView *) ((TexturedRibbonOwnerView *) ribbon)->track)->total;
        ((TexturedRibbonStateView *)(segment))->clearedWord = 0;
        Graphu64_GetMatrixTranslation(local, &((TexturedRibbonStateView *)(segment))->position.scalar);
        if (((TexturedRibbonOwnerView *)(ribbon))->flags & 4) {
            Graphu64_GetMatrixScale(local, &((TexturedRibbonStateView *)(segment))->scale);
        } else {
            Graphu64_ConvertMatrixToFixed(local, &((TexturedRibbonStateView *)(segment))->fixedMatrixFirst);
            Graphu64_ConvertMatrixToFixed(local, &((TexturedRibbonStateView *)(segment))->fixedMatrixSecond);
        }
        previousSegment = *(void **)segment;
        ((TexturedRibbonStateView *)(segment))->segmentLength.word = 0;
        ((TexturedRibbonStateView *)(segment))->phase = 0.0f;
        if (previousSegment != 0) {
            Graphu64_SubtractVectors(&segmentDelta, &((TexturedRibbonStateView *)(segment))->position.vector, &((TexturedRibbonSegmentView *)(previousSegment))->position);
            segmentDistance = Gu_Sqrtf((segmentDelta.x * segmentDelta.x) + (segmentDelta.y * segmentDelta.y) + (segmentDelta.z * segmentDelta.z));
            ((TexturedRibbonSegmentView *)(previousSegment))->segmentLength = segmentDistance;
            ((TexturedRibbonOwnerView *)(ribbon))->length += segmentDistance;
        }
        if (((struct TexturedRibbonResourceView *) ((TexturedRibbonOwnerView *) ribbon)->track)->kind == 0) {
            if (((TexturedRibbonOwnerView *)(ribbon))->length > 0.0f) {
                accumulatedDistance = 0.0f;
                segment = ((TexturedRibbonOwnerView *)(ribbon))->firstSegment;
                if (segment != 0) {
                    do {
                        ((TexturedRibbonStateView *)(segment))->phase = accumulatedDistance / ((TexturedRibbonOwnerView *)(ribbon))->length;
                        previousSegmentDistance = ((TexturedRibbonStateView *)(segment))->segmentLength.value;
                        segment = ((TexturedRibbonStateView *)(segment))->next;
                        accumulatedDistance += previousSegmentDistance;
                    } while (segment != 0);
                }
            }
        } else {
            if (previousSegment != 0) {
                ((TexturedRibbonOwnerView *)(ribbon))->phase += ((TexturedRibbonSegmentView *)(previousSegment))->segmentLength * g_ribbonDistancePhaseScale;
            }
            ((TexturedRibbonStateView *)(segment))->phase = ((TexturedRibbonOwnerView *)(ribbon))->phase;
        }
    }
    return ribbonSegmentResult;
}

void Linked_BuildColoredRibbonVertices(RibbonActor *actor, RibbonClockNode *clock, Vtx *out, Morph *morph) {
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

    weight = 0.5f - Math_Cosf(clock->time / actor->track->total * 3.1415927f) * 0.5f;
    if (actor->time <= actor->track->span) {
        weight = weight * (0.5f - Math_Cosf(actor->time / actor->track->span * 3.1415927f) * 0.5f);
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

void Linked_BuildTexturedRibbonVertices(RibbonActor *actor, RibbonClockNode *clock, Vtx *out, f32 scale, Morph *morph) {
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

    weight = 0.5f - Math_Cosf(clock->time / actor->track->total * 3.1415927f) * 0.5f;
    if (actor->time <= actor->track->span) {
        weight = weight * (0.5f - Math_Cosf(actor->time / actor->track->span * 3.1415927f) * 0.5f);
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

s32 Linked_UpdateRibbonLifetime(s32 owner, StateSmpUpdateRibbonLifetime *state) {
    LevelActor *object;
    Nodes *node;
    Nodes *next;
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

    if (state->count_up >= 0.0f) {
        state->total += g_frameElapsedTime;
    }
    state->timer -= g_frameElapsedTime;
    if (state->timer < 0.0f) {
        state->timer = 0.0f;
    }

    node = state->nodes;
    if (node != 0) {
        zero = 0.0f;
        decay = g_ribbonNodeTransformDecayConstants[1];
        cutoff = g_ribbonNodeTransformCutoffConstants[0];
        do {
            next = node->next;
            if (state->timer <= zero && node->value > zero) {
                node->value = zero;
            }
            value = node->value;
            if (value <= zero) {
                updated = value - decay;
                node->value = updated;
                if (updated < cutoff) {
                    Fx_FreeRibbonSegment(owner, state, node);
                }
            } else {
                updated = value - g_frameElapsedTime;
                node->value = updated;
                if (updated < zero) {
                    node->value = zero;
                }
            }
            node = next;
        } while (node != 0);
    }

    object = state->object;
    if (state->object != 0 && (state->flags & 1) &&
        !(object->flags & 0x200)) {
        Fx_DetachEffectObject(state);
    }
    g_frameElapsedTime = saved_step;

    if (state->active == 0) {
        if (state->timer != 0.0f) {
            if (state->object == 0) {
                return 0;
            }
        } else {
            return 0;
        }
    }
    return 1;
}

void Linked_BuildRibbonSegmentMatrix(Node438C *firstSegment, Node438C *secondSegment, GameplayCamera *camera, void *matrix) {
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
    Graphu64_ScaleVector(&result, &result, firstSegment->a);
    Graphu64_ScaleVector(&cross, &cross, firstSegment->b);
    Graphu64_ScaleVector(&basis, &basis, firstSegment->c);
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
    Node438C *first;
    Node438C *next;
    ItemMenuRenderNode *state = ribbon;

    if (state->vertexCount < 2) {
        return;
    }

    first = state->vertices;
    next = first->next;
    if (first != 0) {
        Graphu64_BuildScaleMatrix(matrix, first->a, first->b, first->c);
    } else {
        Graphu64_IdentityMatrix(matrix);
    }

    while (first != 0) {
        Node438C *a;
        Node438C *b;

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
        Graphu64_ConvertMatrixToFixed(matrix, first->matrices[g_lightingBufferIndex]);
        first = next;
        next = first->next;
    }

    matrix[12] = first->position.x;
    matrix[13] = first->position.y;
    matrix[14] = first->position.z;
    Graphu64_ConvertMatrixToFixed(matrix, first->matrices[g_lightingBufferIndex]);
}

extern f32 g_ribbonPositiveLayerScale, g_ribbonNegativeLayerScale;
extern void Graphu64_ConvertMatrixToFloat(void *, void *);
extern void ScaleMatrixLocal(void *, f32, f32, f32);
extern void Graphu64_ClampMatrixToFixedRange(void *);
typedef struct LinkNode802A {
    struct LinkNode802A *parent; /* 0x00 */
    struct LinkNode802A *next;   /* 0x04 */
    f32 value;                   /* 0x08 */
    char padC[4];
    CVector3 pos;                /* 0x10 */
    CVector3 scale; /* 0x1C: Graphu64_GetMatrixScale output */
    Matrix matrices[2];         /* 0x28, double buffered */
    char pad_A8[4];
    f32 length;                  /* 0xAC */
    void *source;                /* 0xB0: -1 = copy the other buffer, else the node to follow */
} LinkNode802A;
typedef struct LinkOwner802A {
    char pad0[8];
    f32 *range;      /* 0x08 */
    char pad0C[0x18];
    f32 rangeAtChange; /* 0x24: range[0] as of the last source transform change */
    char pad28[0x14];
    u32 flags;        /* 0x3C */
    LinkNode802A *head; /* 0x40 */
    char pad44[8];
    f32 totalLength;  /* 0x4C */
} LinkOwner802A;
/* Updates a chain of linked nodes: nodes following a source take its matrix (scaled by a size flag) or copy the
 * other matrix buffer, then each node's distance to its parent is measured and summed into the owner's total. */
static inline void Render_UpdateLinkedSource(LinkOwner802A *owner, LinkNode802A *node, struct EffectActor *source) {
    f32 matrix[16];
    f32 scale;
    Graphu64_ConvertMatrixToFloat(matrix, &source->u60.matrices[g_lightingBufferIndex]);
    scale = g_ribbonPositiveLayerScale;
    if (source->model->scaleModeFlag != 0) {
        scale = g_ribbonNegativeLayerScale;
    }
    ScaleMatrixLocal(matrix, scale, scale, scale);
    Graphu64_ClampMatrixToFixedRange(matrix);
    Graphu64_GetMatrixTranslation((char *)matrix, &node->pos.x);
    if (owner->flags & 4) {
        Graphu64_GetMatrixScale(matrix, &node->scale.x);
    } else {
        Graphu64_ConvertMatrixToFixed(matrix, node->matrices[g_lightingBufferIndex].m);
    }
}
void Linked_UpdateLinkedNodeTransforms(LinkOwner802A *owner) {
    LinkNode802A *node;
    LinkNode802A *parent;
    void *source;
    s32 changed = 0;
    f32 delta[3];
    owner->totalLength = 0.0f;
    for (node = owner->head; node != 0; node = node->next) {
        source = node->source;
        if (source != 0) {
            if (source == (void *)-1) {
                node->matrices[g_lightingBufferIndex] = node->matrices[g_lightingBufferIndex ^ 1];
                node->source = 0;
            } else {
                Render_UpdateLinkedSource(owner, node, source);
            }
            changed = 1;
            node->value = owner->range[2];
        }
        parent = node->parent;
        if (parent != 0) {
            f32 length;
            Graphu64_SubtractVectors((CVector3 *)delta, &node->pos, &parent->pos);
            length = Gu_Sqrtf(delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2]);
            parent->length = length;
            owner->totalLength += length;
        }
    }
    if (changed) {
        owner->rangeAtChange = owner->range[0];
    }
}

extern float g_texturedRibbonTextureCoordinateScale, g_ribbonTextureCoordinateOffset, g_ribbonInterpolationUnit, g_ribbonTexturePeriod;

void *Textload_RequestTextureVariation(s32 *, s32);
void Textload_ReadTextureAnimationInfo(void *, struct Shared_AnimInfo *);
#if defined(VERSION_US_REV1)
void Textload_LoadTextureFrameTiles(s32 *, void *, s32, s32, s32, s32, s32, s32, s32);
#else
void Textload_LoadTextureFrame(s32 *, void *, s32, s32, s32, s32, s32, s32, s32);
#endif
void Cache_UnlockResource(s32, void *);
s32 Fx_SelectAnimationFrame(AnimationFrameState *state, AnimationFrameDefinition *definition, s32 *frame_count);
/* Draws a textured ribbon: spaces the texture along the tail by length, picks the animation frame, sets the
 * combiner and colours (greyscale on a monochrome camera), then emits two vertex rows per clock node and the
 * triangle strip between them. */
void Linked_DrawTexturedRibbon(VertexArena *pool, RibbonActor *actor, GameplayCamera *camera) {
    struct Shared_AnimInfo info;
    Morph storage;
    struct Shared_AnimInfo *anim;
    void *model;
    struct CROMSwoosh_t *track;
    RibbonClockNode *clock, *next, *node;
    Vtx *vertices;
    f32 offset;
    f32 period;
    u32 grey;
    s32 count, edges, i, used, frame;

    track = actor->track;
    used = 0;
    if (track->kind == 2 && 0.0f < actor->length) {
        offset = 0.0f;
        for (node = actor->tail; node != 0; node = node->prev) {
            node->offset = offset / actor->length;
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
    next = clock->next;
    frame = Fx_SelectAnimationFrame((AnimationFrameState *)actor, (AnimationFrameDefinition *)track, &info.count);
#if defined(VERSION_US_REV1)
    Textload_LoadTextureFrameTiles(&actor->model, model, frame, 0, 0xFFFF, 0xFFFF, 0, 0, 0);
#else
    Textload_LoadTextureFrame(&actor->model, model, frame, 0, 0xFFFF, 0xFFFF, 0, 0, 0);
#endif
    edges = count - 1;
    gSPMatrix(g_displayListCursor++, &clock->matrix[g_lightingBufferIndex], G_MTX_LOAD);
    while (clock != 0 && next != 0 && 0.0f < clock->time && 0.0f < next->time && used + count * 2 < 32) {
        f32 scale;
        vertices = Fx_AllocateRibbonVertices(pool, count);
        if (vertices == 0) break;
        Linked_BuildTexturedRibbonVertices(actor, clock, vertices, clock->offset, &storage);
        used += count;
        gSPVertex(g_displayListCursor++, vertices, count, 0);
        gSPMatrix(g_displayListCursor++, &next->matrix[g_lightingBufferIndex], G_MTX_LOAD);
        vertices = Fx_AllocateRibbonVertices(pool, count);
        if (vertices == 0) break;
        scale = next->offset;
        while (clock->offset < scale) scale -= period;
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
        next = clock->next;
    }
    Cache_UnlockResource(0, model);
}
