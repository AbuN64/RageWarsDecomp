#include "include_asm.h"
#include "COMMON/DESCRIPTORRECAT29.H"
#include "SCHED/SKY_POSTSCREENMESSAGE.H"
#include "COMMON/RESIDENTSTATE.H"
#include <ultra64.h>
#include <PR/gbi.h>
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/APPROACHLOCATION.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "COMMON/SESSIONHANDLERROW.H"
#include "COMMON/GAMEPLAY_REACTIONS.H"
#include "COMMON/FRUSTUM.H"
#include "TEXTURE/TEXTLOAD_LOADTEXTUREFRAME.H"
#include "TEXTURE/TEXTLOAD_LOADTEXTUREFRAMETILES.H"
#include "TEXTURE/TEXTLOAD_REQUESTTEXTUREVARIATION.H"
#include "COMMON/WORLD.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/S1.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "ENGINE/CACHE/LIST.H"
#include "GSKY/SKY.H"
#include "COMMON/GAMEPLAY_CAMERA.H"
#include "ENGINE/GREGION.H"
#include "ENGINE/SCENE_DRAWOPAQUEACTORS.H"
#include "GRAPHU64/GRAPHU64_GETANGLEDISTANCE.H"
#include "GSKY/GSKY_GETOBJECTPOSITIONAT260.H"
#include "PPDECOM/PPDECOM_QUICKSORTRECORDS.H"
#include "TEXTLOAD/TEXTLOAD_LOCATETEXTURERESOURCE.H"
#include "TEXTLOAD/TEXTLOAD_READTEXTUREANIMATIONINFO.H"
#include "TEXTLOAD/TEXTLOAD_REQUESTTEXTUREVARIATIONSYNC.H"

/* SKY.CPP */
/* 8023A284_4.CPP */
extern void Cache_UnlockResource(void *, CacheResourceNode *);


/* Clip and draw a textured translucent fan at the object's depth. */
void Sky_DrawClippedEffectFan(SkyLayerRuntimeView *object, ClipView *view) {
    AnimationInfo animation;
    CVector3 points[5];
    f32 red[5], green[5], blue[5], alpha[5];
    CVector3 triangle[3];
    CVector3 texcoord[3];
    f32 triRed[3], triGreen[3], triBlue[3], triAlpha[3];
    CVector3 edge0, edge1, normal;
    u8 center[3], rim[3];
    s32 below;
    void *resource;
    CROMSkyLayer *descriptor;
    s32 frameIndex, scaleS, scaleT;
    u8 *frame;
    f32 phase, fadeRange, fadeOffset;
    s32 format;
    s32 i, face, first, second, third;
    f32 scale, texturePeriod, wrapPeriod, distance, fade, depth, t;
    f32 maxS, minS, maxT, minT, shiftS, shiftT, factor;
    UnitVtx *vertex;

    resource = Textload_RequestTextureVariation(object->texture, -1);
    if (resource != 0) {
        Textload_ReadTextureAnimationInfo(resource, &animation);
        if (animation.frameCount != 0) {
            descriptor = object->descriptor;
            frame = animation.frames;
            phase = object->phase / frame[1];
            scale = descriptor->textureScale * (object->textureScale * 768.0f);
            scaleS = (s32)((1 << frame[2]) * scale);
            scaleT = (s32)((1 << frame[3]) * scale);
            gDPPipeSync(g_displayListCursor++);
            frameIndex = (s32)phase % animation.frameCount;
#if defined(VERSION_US_REV1)
            Textload_LoadTextureFrameTiles(object->texture, resource,
#else
            Textload_LoadTextureFrame(object->texture, resource,
#endif
                frameIndex, 0,
                scaleS, scaleT, 0, 0, 15);
            texturePeriod = 5120.0f;
            wrapPeriod = 10240.0f;
            frame = animation.frames;
            format = frame[0];
            switch (format) {
            case 2:
            default:
                Geometry_SetCombineMode(32);
                gDPSetEnvColor(g_displayListCursor++, descriptor->envRed, descriptor->envGreen, descriptor->envBlue, 255);
                center[0] = descriptor->red;
                center[1] = descriptor->green;
                center[2] = descriptor->blue;
                rim[0] = descriptor->red;
                rim[1] = descriptor->green;
                rim[2] = descriptor->blue;
                break;
            case 0: case 1:
                Geometry_SetCombineMode(33);
                center[0] = 255; center[1] = 255; center[2] = 255;
                rim[0] = 255; rim[1] = 255; rim[2] = 255;
                break;
            }
            below = 1;
            depth = object->depth;
            if (!(view->fan[0].y < (view->fan[1].y + view->fan[2].y + view->fan[3].y + view->fan[4].y) * 0.25f)) below = 0;
            distance = view->fan[0].y - depth;
            fade = descriptor->alpha;
            if (distance < 0.0f) distance = -distance;
            if (distance < descriptor->fadeDepth) {
                fadeOffset = distance - descriptor->fadeDepth * 0.25f;
                fadeRange = descriptor->fadeDepth * 0.75f;
                if (fadeOffset < 0.0f) fade = 0.0f;
                else fade = fadeOffset * fade / fadeRange;
            }
            fade *= object->throttle * object->opacity;
            for (i = 0; i < 5; i++) {
                points[i].x = view->fan[i].x;
                points[i].y = depth;
                points[i].z = view->fan[i].z;
                red[i] = i == 0 ? center[0] : rim[0];
                green[i] = i == 0 ? center[1] : rim[1];
                blue[i] = i == 0 ? center[2] : rim[2];
                alpha[i] = i == 0 ? fade : 0.0f;
            }
            for (i = 1; i < 5; i++) {
                t = Visdata_GetPlaneSegmentFraction(view->clipPlane, &points[0].x, &points[i].x);
                if (t >= 0.0f && t < 1.0f) {
                    points[i].x = points[0].x + t * (points[i].x - points[0].x);
                    points[i].z = points[0].z + t * (points[i].z - points[0].z);
                }
            }
            for (face = 0; face < 4; face++) {
                switch (face) {
                case 0:
                default: first = 0; second = 1; third = 3; break;
                case 1: first = 0; second = 3; third = 4; break;
                case 2: first = 0; second = 4; third = 2; break;
                case 3: first = 0; second = 2; third = 1; break;
                }
                triangle[0] = points[first];
                triangle[1] = points[second];
                triangle[2] = points[third];
                Graphu64_SubtractVectors(&edge0, &triangle[1], &triangle[0]);
                Graphu64_SubtractVectors(&edge1, &triangle[2], &triangle[1]);
                Graphu64_CrossVectors(&normal, &edge0, &edge1);
                if (normal.y <= 0.0f) {
                    if (below != 1) goto draw_face;
                } else {
                    if (below != 0) {
draw_face:
                        triRed[0] = red[first]; triRed[1] = red[second]; triRed[2] = red[third];
                        triGreen[0] = green[first]; triGreen[1] = green[second]; triGreen[2] = green[third];
                        triBlue[0] = blue[first]; triBlue[1] = blue[second]; triBlue[2] = blue[third];
                        triAlpha[0] = alpha[first]; triAlpha[1] = alpha[second]; triAlpha[2] = alpha[third];
                        texcoord[0] = points[first];
                        texcoord[1] = points[second];
                        texcoord[2] = points[third];
                        for (i = 0; i < 3; i++) {
                            texcoord[i].x -= triangle[0].x * 0.5f;
                            texcoord[i].z -= triangle[0].z * 0.5f;
                            texcoord[i].x += object->offsetS;
                            texcoord[i].z += object->offsetT;
                        }
                        maxS = texcoord[2].x;
                        if (!(texcoord[1].x <= maxS)) maxS = texcoord[1].x;
                        if (!(texcoord[0].x <= maxS)) maxS = texcoord[0].x;
                        minS = texcoord[2].x;
                        if (!(minS <= texcoord[1].x)) minS = texcoord[1].x;
                        if (!(minS <= texcoord[0].x)) minS = texcoord[0].x;
                        maxT = texcoord[2].z;
                        if (!(texcoord[1].z <= maxT)) maxT = texcoord[1].z;
                        if (!(texcoord[0].z <= maxT)) maxT = texcoord[0].z;
                        minT = texcoord[2].z;
                        if (!(minT <= texcoord[1].z)) minT = texcoord[1].z;
                        if (!(minT <= texcoord[0].z)) minT = texcoord[0].z;
                        if (wrapPeriod <= maxS) shiftS = (s32)(maxS / wrapPeriod) * -wrapPeriod;
                        else if (minS <= -wrapPeriod) shiftS = (s32)(minS / wrapPeriod) * wrapPeriod;
                        else shiftS = 0.0f;
                        if (wrapPeriod <= maxT) shiftT = (s32)(maxT / wrapPeriod) * -wrapPeriod;
                        else if (minT <= -wrapPeriod) shiftT = (s32)(minT / wrapPeriod) * wrapPeriod;
                        else shiftT = 0.0f;
                        for (i = 0; i < 3; i++) {
                            vertex = i + &object->vertices[g_lightingBufferIndex][face * 3];
                            vertex->flag = 0;
                            vertex->x = (s32)triangle[i].x;
                            vertex->y = (s32)triangle[i].y;
                            vertex->z = (s32)triangle[i].z;
                            factor = 16384.0f / texturePeriod;
                            vertex->s = (s32)((texcoord[i].x + shiftS) * factor);
                            vertex->t = (s32)((texcoord[i].z + shiftT) * factor);
                            vertex->r = (u32)triRed[i];
                            vertex->g = (u32)triGreen[i];
                            vertex->b = (u32)triBlue[i];
                            vertex->a = (u32)triAlpha[i];
                        }
                        gSPVertex(g_displayListCursor++, &object->vertices[g_lightingBufferIndex][face * 3], 3, 0);
                        gSP1Triangle(g_displayListCursor++, 0, 1, 2, 0);
                    }
                }
            }
        }
        Cache_UnlockResource(0, resource);
    }
}

/* Updates the scene's effect objects for one host: spawns an object for every enabled effect
 * descriptor bit that has none yet, then fades each active object up or down, advances its phase and
 * texture scroll, sets its depth from the host, and returns objects that have faded out to the free list. */
extern s32 g_skyLayerDescriptorCount;
extern f32 g_frameElapsedTime;




extern void List_RemoveIntrusive(void *, void *);
extern void List_PrependIntrusive(void *, void *);
static inline SkyLayerRuntimeView *allocateSceneEffect(Scene *scene) {
    SkyLayerRuntimeView *object = (SkyLayerRuntimeView *)scene->freeObjects.head;
    if (object != 0) {
        List_RemoveIntrusive(&scene->freeObjects, object);
        List_AppendIntrusive(&scene->activeObjects, object);
    }
    return object;
}

static inline s32 updateSceneEffect(SkyLayerRuntimeView *object, GameplayCamera *host, u16 mask, s32 below, f32 hostDepth, f32 limit) {
    CROMSkyLayer *descriptor = object->descriptor;
    f32 value, step, depth, wrapPeriod, fadeStep;
    if (object->mask & mask) {
        value = object->throttle;
        fadeStep = descriptor->throttleRate * g_frameElapsedTime;
        value += fadeStep;
        if (1.0f < value) {
            value = 1.0f;
        }
        object->throttle = value;
    } else if (object->throttle == 0.0f) {
        return 1;
    } else {
        value = object->throttle - descriptor->throttleRate * g_frameElapsedTime;
        if (value < 0.0f) {
            value = 0.0f;
        }
        object->throttle = value;
    }
    object->phase = object->phase + g_frameElapsedTime * descriptor->phaseRate * object->phaseScale;
    step = g_frameElapsedTime * g_skyRotorSpinScale * descriptor->spinRate;
    value = object->offsetS + step * 1.536f;
    wrapPeriod = 20480.0f;
    object->offsetS = value;
    if (wrapPeriod < value) {
        object->offsetS = value - wrapPeriod;
    }
    value = object->offsetT + step * 3.072f;
    object->offsetT = value;
    if (wrapPeriod < value) {
        object->offsetT = value - wrapPeriod;
    }
    depth = descriptor->baseSpeed + object->trim;
    if (below && host->bobSuppressed == 0) {
        depth += hostDepth;
    } else if (descriptor->flags & 1) {
        depth += host->position.y * descriptor->hostScale;
    } else if (descriptor->flags & 2) {
        depth += limit;
    }
    object->depth = depth;
    return 0;
}

void Sky_UpdateSceneEffects(Scene *scene, GameplayCamera *host) {
    CVector3 anchor;
    CVector3 probe;
    Shared_ReactionFlags *entry;
    CROMSkyLayer *descriptor;
    SkyLayerRuntimeView *object;
    SkyLayerRuntimeView *next;
    void *resource;
    f32 hostDepth, limit, fadeLimit, value;
    s32 below;
    s32 count;
    u16 mask;
    u32 bit;

    if (g_world.frozen != 0) {
        return;
    }
    resource = host->floorPoly;
    if (resource == 0) {
        return;
    }
    entry = Scene_GetModelRecordByIndexPointer(&g_world, resource);
    if (entry == 0) {
        return;
    }
    hostDepth = 0.0f;
    limit = Region_GetPolygonHeight(resource, host->floorSampleX, host->floorSampleZ);
    below = 0;
    if (entry->flags & 1) {
        Gsky_GetObjectPositionAt260(&anchor, host);
        fadeLimit = 0.5f;
        value = (entry->height - anchor.y) * fadeLimit;
        if (20.48f < value) {
            fadeLimit = 20.48f;
        } else {
            Gsky_GetObjectPositionAt260(&probe, host);
            fadeLimit = (entry->height - probe.y) * fadeLimit;
        }
        Gsky_GetObjectPositionAt260(&anchor, host);
        if (!(anchor.y < entry->height)) {
            below = 0;
        } else {
            below = 1;
        }
        hostDepth = entry->height - fadeLimit;
    }
    mask = entry->mask;
    count = g_skyLayerDescriptorCount;
    descriptor = (CROMSkyLayer *)g_skyLayerDescriptors;
    bit = 1;
    while (--count != -1) {
        if ((u16)(mask & bit) && descriptor->texture != 0 && !(scene->effectMask & bit)) {
            object = allocateSceneEffect(scene);
            if (object != 0) {
                object->descriptor = descriptor;
                object->mask = bit;
                Textload_LocateTextureResource(object->texture, descriptor->texture);
                object->offsetS = 0.0f;
                object->offsetT = 0.0f;
                object->throttle = 0.0f;
                object->phase = 0.0f;
                object->phaseScale = 1.0f;
                object->textureScale = 1.0f;
                object->trim = 0.0f;
                object->opacity = 1.0f;
                scene->effectMask |= bit;
            }
        }
        descriptor++;
        bit <<= 1;
    }
    if ((u16)mask == 0) {
        return;
    }
    object = scene->activeObjects.head;
    if (object == 0) {
        return;
    }
    do {
        next = object->next;
        if (updateSceneEffect(object, host, mask, below, hostDepth, limit)) {
            scene->effectMask &= ~object->mask;
            List_RemoveIntrusive(&scene->activeObjects, object);
            List_PrependIntrusive(&scene->freeObjects, object);
        }
        object = next;
    } while (object != 0);
}

/* 8023A284_7.CPP */
/* Sorts and draws scene translucent objects in two groups around the view depth. */





/* Updates a rotor: while the control mask bit is held its throttle at 0x208 rises by the descriptor rate up
 * to g_skyRotorMaximumThrottle, otherwise it falls to zero (returning 1 once idle); the value phase advances, the two wrap
 * angles at 0x1C and 0x20 advance and wrap at g_skyRotorAngleWrap, and the speed at 0x210 becomes the descriptor
 * base plus trim, plus the boost when requested and the host is not stalled, or else the host's speed
 * scaled by the descriptor (flag 1) or the fallback speed (flag 2). Returns 0 while active. */

void Sky_DrawDepthSortedSceneEffects(Scene *scene, ClipView *view) {
    SkyLayerRuntimeView *near[4];
    SkyLayerRuntimeView *far[4];
    SkyLayerRuntimeView *object;
    s32 nearCount;
    s32 farCount;
    s32 i;

    if (scene->activeObjects.count == 0 || view->hidden != 0) {
        return;
    }
    gDPPipeSync(g_displayListCursor++);
    gSPMatrix(g_displayListCursor++, (u32)(((uintptr_t)&g_skyEffectProjectionMatrix)), G_MTX_LOAD);
    gMoveWd(g_displayListCursor++, G_MW_CLIP, 4, (u32)((2)));
    gMoveWd(g_displayListCursor++, G_MW_CLIP, 12, (u32)((2)));
    gMoveWd(g_displayListCursor++, G_MW_CLIP, 20, (u32)((0xFFFE)));
    gMoveWd(g_displayListCursor++, G_MW_CLIP, 28, (u32)((0xFFFE)));
    gSPGeometryMode(g_displayListCursor++, G_FOG, 0);
    gDPSetCycleType(g_displayListCursor++, G_CYC_1CYCLE);
    Geometry_SetModePreset(13);
    gSPGeometryMode(g_displayListCursor++, G_CULL_BACK | G_LIGHTING | G_TEXTURE_GEN, 0);
    gSPGeometryMode(g_displayListCursor++, 0, G_SHADE | G_SHADING_SMOOTH);
    gDPSetTexturePersp(g_displayListCursor++, G_TP_PERSP);
    gDPSetTextureFilter(g_displayListCursor++, G_TF_BILERP);
    nearCount = 0;
    farCount = 0;
    for (object = scene->activeObjects.head; object != 0; object = object->next) {
        if (object->depth > view->depth) {
            near[nearCount++] = object;
        } else {
            far[farCount++] = object;
        }
    }
    PpDecom_QuickSortRecords((char *)near, nearCount, 4, Sky_CompareRotorSpeedsDescendingCallback, Sky_SwapEntryCallback);
    PpDecom_QuickSortRecords((char *)far, farCount, 4, Sky_CompareRotorSpeedsAscendingCallback, Sky_SwapEntryCallback);
    for (i = 0; i < nearCount; i++) {
        Sky_DrawClippedEffectFan(near[i], view);
    }
    for (i = 0; i < farCount; i++) {
        Sky_DrawClippedEffectFan(far[i], view);
    }
}

void Sky_InitializeEffect(Effect *effect, s16 *definition, s16 mask, f32 scale,
                   f32 offset0, f32 offset1, f32 offset2) {
    effect->definition = definition;
    effect->mask = mask;
    Textload_LocateTextureResource(&effect->resource, *definition);
    effect->angle0 = 0;
    effect->angle1 = 0;
    effect->timer = 0;
    effect->velocity = 0;
    effect->scale = scale;
    effect->offset0 = offset0;
    effect->offset1 = offset1;
    effect->offset2 = offset2;
}

s32 Sky_UpdateRotor(Rotor *rotor, s32 mask, f32 fallback, s32 boosting, f32 boost, Host *host) {
    CROMSkyLayer *descriptor;
    f32 throttle;
    f32 value;
    f32 angle;
    f32 speed;
    f32 lowered;
    f32 zero;
    f32 wrap;

    descriptor = rotor->descriptor;
    if (rotor->mask & mask) {
        throttle = rotor->throttle + descriptor->throttleRate * g_frameElapsedTime;
        if (g_skyRotorMaximumThrottle < throttle) {
            throttle = g_skyRotorMaximumThrottle;
        }
        rotor->throttle = throttle;
    } else {
        zero = 0.0f;
        value = rotor->throttle;
        if (value == zero) {
            return 1;
        }
        lowered = value - descriptor->throttleRate * g_frameElapsedTime;
        if (lowered < zero) {
            lowered = zero;
        }
        rotor->throttle = lowered;
    }
    rotor->phase += g_frameElapsedTime * descriptor->phaseRate * rotor->phaseScale;
    value = g_frameElapsedTime * g_skyRotorSpinScale * descriptor->spinRate;
    angle = rotor->angleA + value * g_skyRotorAngleAScale;
    wrap = g_skyRotorAngleWrap;
    rotor->angleA = angle;
    if (wrap < angle) {
        rotor->angleA = angle - wrap;
    }
    angle = rotor->angleB + value * g_skyRotorAngleBScale;
    rotor->angleB = angle;
    if (wrap < angle) {
        rotor->angleB = angle - wrap;
    }
    speed = descriptor->baseSpeed + rotor->trim;
    if (boosting != 0 && host->stalled == 0) {
        speed += boost;
    } else if (descriptor->flags & 1) {
        speed += host->speed * descriptor->hostScale;
    } else if (descriptor->flags & 2) {
        speed += fallback;
    }
    rotor->speed = speed;
    return 0;
}

void *Sky_AllocateEffectNode(struct Scene *sceneOwner) {
    void *head;

    head = sceneOwner->freeObjects.head;
    if (head != 0) {
        List_RemoveIntrusive(&sceneOwner->freeObjects, head);
        List_AppendIntrusive(&sceneOwner->activeObjects, head);
    }
    return head;
}

/* 8023A284_8.CPP */
void Sky_ReleaseEffectNode(s32 sceneAddress, s32 effectNode) {
    List_RemoveIntrusive(&((struct Scene *)sceneAddress)->activeObjects, effectNode);
    List_PrependIntrusive(&((struct Scene *)sceneAddress)->freeObjects, effectNode);
}

/** Swap the two words pointed to by leftEntry and rightEntry. */
void Sky_SwapEntries(int *leftEntry, int *rightEntry) {
    int savedEntry;

    savedEntry = *leftEntry;
    *leftEntry = *rightEntry;
    *rightEntry = savedEntry;
}

s32 Sky_CompareRotorSpeedsDescending(void **leftEntry, void **rightEntry)
{
  f32 leftSortValue;
  int comparisonMagnitude;
  s32 comparisonResult;
  comparisonResult = 1;
  leftSortValue = ((struct SkyEffectSortValueView *) ((s8 *) (*leftEntry)))->sortValue;
  if ((((struct SkyEffectSortValueView *) ((s8 *) (*rightEntry)))->sortValue) < leftSortValue)
  {
    comparisonMagnitude = 1;
    comparisonResult = -comparisonMagnitude;
  }
  return comparisonResult;
}

/** Compare two records by the float at nested offset 0x210. */
int Sky_CompareRotorSpeeds(void *first, void *second) {
    Rotor *left = *(void **)first;
    Rotor *right = *(void **)second;
    int result = 1;
    if (left->speed <
        right->speed) {
        result = -1;
    }
    return result;
}

/* 800C86E0.CPP */
const float g_skyRotorUpdateConstantsUsRev1[4] = {
    1.0f, 1.536f, 2.048e+04f, 3.072f,
};
