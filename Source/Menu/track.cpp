#include "Common/output.h"
#include "Rsp/random_direction_and_affine_math.h"
#include "Common/track_spline.h"
#include "Common/sharedplayer.h"
#include "types.h"
#include "Scene/cache_freememory.h"
#include "Common/selectionscreenstate.h"
#include "Common/approachlocation.h"
#include "Menu/track_buildweightedspline.h"
#include "include_asm.h"
#include "Common/runtime_declarations.h"
#include "Common/resident_event_handler.h"
#include "Common/sharedtrackobjectprefix.h"
#include "Common/ballisticparams.h"
#include "Common/shared_optionsscreen.h"
#include "Common/ppdecom_unpackresource.h"
#include "Common/texture_request.h"
#include "Menu/track_tables.h"
#include "Common/world.h"
#include "Common/access_s8_10f.h"
#include "Common/localdecoderange.h"
#include "Common/triple.h"
#include "Menu/track_loadtracksequence.h"
#include "Scene/cache_requestresource.h"
#include "Render/setn64_getpacksection.h"
#include "Engine/Cache/cache.h"
#include "Engine/session.h"
#include "Engine/cache_allocresourceblock.h"
#include "Menu/g_cinemadirectorytext.h"
#include "Scene/cache_allocateresourceat.h"
#include "Common/aiprofile.h"
#include "Menu/track_evaluatetrackcolor.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Common/Lone/hud_reference_viewport_height.h"
#include <platform_sdk.h>
#include <PR/gbi.h>
#include "Common/sessionhandlerrow.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Common/geometry_blend_and_instance_views.h"
#include "Menu/track_evaluatetrackopacity.h"
#include "Menu/track_drawletterboxbands.h"
#include "Common/game_session.h"
#include "Setn64/setn64_drawcolorrectangle.h"
#include "Track/track_drawtrackoverlay.h"
#include "Menu/track_types.h"
#include "Menu/Track/track_evaluatetrackopacity_symbols.h"
#include "Common/scene_frame_and_effect_updates.h"
#include "Engine/particle.h"
#include "Menu/track_updatetrackcamera.h"
#include "Engine/ccinema_drawmessages.h"
#include "Menu/track.h"
#include "Menu/track_gettracktargetposition.h"
#include "Camera/collision_sweep_views.h"
#include "Menu/Track/track_updatetrackcamera_symbols.h"
#include "Menu/Items/Scene/scene_buildcachedgeometry.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Ai/Player/player_model_and_held_weapon_rendering.h"

/* Computes the second derivatives of a natural cubic spline through n points (ys over xs) into out: builds the tridiagonal diagonal, interval widths and right-hand side in three scratch arrays from Cache_AllocateMemory, eliminates forward, zeroes out and back-substitutes unless a zero diagonal or width was replaced by one, then frees the arrays through Cache_FreeMemory. */
void Track_SolveSplineSecondDerivatives(s32 n, f32 *ys, f32 *xs, f32 *out) {
    f32 *diagonal;
    f32 *rhs;
    f32 *width;
    s32 singular;
    s32 i;

    singular = 0;
    if (n == 1) {
        out[0] = 0;
        return;
    }
    diagonal = Cache_AllocateMemory(n * 4);
    rhs = Cache_AllocateMemory(n * 4);
    width = Cache_AllocateMemory(n * 4);
    for (i = 1; i < n - 1; i++) {
        diagonal[i] = 2.0f * (xs[i + 1] - xs[i - 1]);
        if (diagonal[i] == 0.0f) {
            diagonal[i] = 1.0f;
            singular = 1;
        }
    }
    for (i = 0; i < n - 1; i++) {
        width[i] = xs[i + 1] - xs[i];
        if (width[i] == 0.0f) {
            width[i] = 1.0f;
            singular = 1;
        }
    }
    for (i = 1; i < n - 1; i++) {
        rhs[i] = ((ys[i + 1] - ys[i]) / width[i] - (ys[i] - ys[i - 1]) / width[i - 1]) * 6.0f;
    }
    for (i = 1; i < n - 2; i++) {
        rhs[i + 1] -= rhs[i] * width[i] / diagonal[i];
        diagonal[i + 1] -= width[i] * width[i] / diagonal[i];
    }
    for (i = 0; i < n; i++) {
        out[i] = 0;
    }
    if (!singular) {
        for (i = n - 2; i > 0; i--) {
            out[i] = (rhs[i] - width[i] * out[i + 1]) / diagonal[i];
        }
    }
    Cache_FreeMemory(diagonal);
    Cache_FreeMemory(rhs);
    Cache_FreeMemory(width);
}

void Track_BuildWeightedSpline(s32 count, CVector3 *points, f32 *weights, Spline *spline) {
    CVector3 delta;
    f32 *ys;
    f32 *xs;
    f32 *d2;
    SplineNode *nodes;
    f32 length;
    s32 i;

    ys = Cache_AllocateMemory(count * 4);
    xs = Cache_AllocateMemory(count * 4);
    d2 = Cache_AllocateMemory(count * 4);
    nodes = spline->nodes;
    length = 0.0f;
    spline->nodeSize = 36;
    spline->count = count;
    if (count == 1) {
        spline->nodes[0].p.x = points->x;
        nodes->p.y = points->y;
        nodes->p.z = points->z;
        nodes->d2p.x = 0.0f;
        nodes->d2p.y = 0.0f;
        nodes->d2p.z = 0.0f;
        nodes->d2s = 0.0f;
        nodes->w = 0.0f;
        return;
    }
    for (i = 0; i < count; i++) {
        nodes[i].p.x = points[i].x;
        nodes[i].p.y = points[i].y;
        nodes[i].p.z = points[i].z;
        nodes[i].w = weights[i];
    }
    for (i = 0; i < count; i++) {
        nodes[i].s = length;
        if (i == count - 1) {
            break;
        }
        Graphu64_SubtractVectors(&delta, &nodes[i].p, &nodes[i + 1].p);
        length += Gu_Sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
    }
    for (i = 0; i < count; i++) {
        ys[i] = nodes[i].p.x;
        xs[i] = nodes[i].s;
    }
    Track_SolveSplineSecondDerivatives(count, ys, xs, d2);
    for (i = 0; i < count; i++) {
        nodes[i].d2p.x = d2[i];
    }
    for (i = 0; i < count; i++) {
        ys[i] = nodes[i].p.y;
        xs[i] = nodes[i].s;
    }
    Track_SolveSplineSecondDerivatives(count, ys, xs, d2);
    for (i = 0; i < count; i++) {
        nodes[i].d2p.y = d2[i];
    }
    for (i = 0; i < count; i++) {
        ys[i] = nodes[i].p.z;
        xs[i] = nodes[i].s;
    }
    Track_SolveSplineSecondDerivatives(count, ys, xs, d2);
    for (i = 0; i < count; i++) {
        nodes[i].d2p.z = d2[i];
    }
    for (i = 0; i < count; i++) {
        ys[i] = nodes[i].s;
        xs[i] = nodes[i].w;
    }
    Track_SolveSplineSecondDerivatives(count, ys, xs, d2);
    for (i = 0; i < count; i++) {
        nodes[i].d2s = d2[i];
    }
    Cache_FreeMemory(ys);
    Cache_FreeMemory(xs);
    Cache_FreeMemory(d2);
}

extern const char g_cinemaDirectoryText[17];

#if !(defined(VERSION_US_REV1))
extern const char s_cinemaText[7];
#endif

#if defined(VERSION_US_REV1)

#endif

/* A nonnull source is copied into the new pack section; null reserves it. */
static inline char *packAppend_trackLoadtracksequence(Pack *pack,const void *source,s32 size) { return Polytrak2_AppendOutputPackSection(pack,source,size); }

static inline s32 splineRecordSize_trackLoadtracksequence(s32 left,s32 right) { s32 a=left*9,b=right*9; return (b+a)*4+48; }

static inline void minTime_trackLoadtracksequence(f32 *dest,f32 *src) {
    if(*dest>*src)*dest=*src;
}

static inline void maxTime_trackLoadtracksequence(f32 *dest,f32 *src) {
    if(*dest<*src)*dest=*src;
}

static inline void setTimes_trackLoadtracksequence(f32 *a,f32 *b,f32 *c,f32 *t) {
    *a=*t;
    *b=*t;
    *c=*t;
}

void Track_BuildTrackResourceSplines(s32 requestOwner, struct CacheResourceNode **handle) {
    struct CacheResourceNode *output;
    void *source, *a, *b, *c, *part, *extra;
    Pack *pack, *dest;
    SplineTable *parts;
    Pack *table;
    SplineSourceCursor p,q,r,s;
    s32 count, i, size, sa, sb, sc, np, nr, byteP, byteR;
    void *dp, *dr;
    if (!Ppdecom_UnpackResource((void **)handle, 1)) return;
    source = (*handle)->data;
    parts = SetN64_GetPackSection(source, 0);
    a = SetN64_GetPackSection(source, 1);
    b = SetN64_GetPackSection(source, 2);
    c = SetN64_GetPackSection(source, 3);
    count = parts->count;
    size = (count * 4 + 15) & ~7;
    for (i = 0; i < parts->count; i++) {
        SplineSource *firstP,*firstR;
        void *firstPart;
        s32 byteP,byteR;
        firstPart = SetN64_GetPackSection(parts, i);
        firstP = SetN64_GetPackSection(firstPart, 0);
        firstR = SetN64_GetPackSection(firstPart, 2);
        size += splineRecordSize_trackLoadtracksequence(firstP->count,firstR->count);
    }
    sc = SetN64_GetRecordBlockSize(c);
    sa = SetN64_GetRecordBlockSize(a);
    sb = SetN64_GetRecordBlockSize(b);
    output = Cache_AllocResourceBlock(0, handle, size + sa + sb + sc + 24);
    if (output == 0) return;
    pack = output->data;
    Polytrak2_InitializeOutputPack(pack, 4);
    table = (void *)packAppend_trackLoadtracksequence(pack, 0, size);
    packAppend_trackLoadtracksequence(pack, a, sa);
    packAppend_trackLoadtracksequence(pack, b, sb);
    packAppend_trackLoadtracksequence(pack, c, sc);
    Polytrak2_InitializeOutputPack(table, count);
    for (i = 0; i < count; i++) {
        s32 byteP,byteR;
        SplineSource *sizeP,*sizeR;
        part = SetN64_GetPackSection(parts, i);
        sizeP = SetN64_GetPackSection(part, 0);
        sizeR = SetN64_GetPackSection(part, 2);
        byteP = sizeP->count * 9;
        byteR = sizeR->count * 9;
        dest = (void *)packAppend_trackLoadtracksequence(table, 0, (byteR + byteP)*4 + 48);
        Polytrak2_InitializeOutputPack(dest, 3);
        p.header = SetN64_GetPackSection(part, 0);
        q.header = SetN64_GetPackSection(part, 1);
        r.header = SetN64_GetPackSection(part, 2);
        s.header = SetN64_GetPackSection(part, 3);
        extra = SetN64_GetPackSection(part, 4);
        np = p.header->count;
        nr = r.header->count;
        { s32 pointBytes,otherBytes;
        pointBytes = np * 36 + 8;
        otherBytes = nr * 36 + 8;
        dp = packAppend_trackLoadtracksequence(dest, 0, pointBytes);
        dr = packAppend_trackLoadtracksequence(dest, 0, otherBytes);
        }
        p.points = p.header->points;
        q.weights = q.header->weights;
        r.points = r.header->points;
        s.weights = s.header->weights;
        packAppend_trackLoadtracksequence(dest, extra, 8);
        Track_BuildWeightedSpline(np, p.points, q.weights, dp);
        Track_BuildWeightedSpline(nr, r.points, s.weights, dr);
    }
    Cache_ReplaceResourceBlock(0, handle, output);
}

s32 Track_LoadTrackSequence(s32 index) {
    s32 size,size2,i,count,previous,pending,loaded;
    SharedTrackObject *captured;
    Shared_World *resources;
    void **owner,**table;
    Shared_TrackCues *cues;
    PositionKey *cue;
    Shared_TrackClip *clip;
    Shared_MenuContext *context,*scanContext;
    f32 total;
    captured=g_transientPlayerList.actorList;
    pending=g_cinemaSequenceState->pendingTrackId;
    resources=&g_world;
    if(resources->trackLookup==0 || resources->trackBundle==0) {
        failed:
        return 0;
    }
    else {
        if(g_cinemaSequenceState->active!=0)Cinema_ReleaseSequenceContext();
        loaded=SetN64_LocatePackSection(resources->trackBundle,resources->trackLookup,index+1,&size);
        owner=Cache_RequestResource(0,loaded,loaded,size,51,0,g_Track_BuildTrackResourceSplinesAddress,s_cinemaText,1);
        if(owner==0)goto failed;
        g_cinemaSequenceState->owner=owner;
        g_cinemaSequenceState->resource=*owner;
        cues=Menu_GetTrackCues();
        cue=cues->cues;
        count=cues->count;
        total=0.0f;
        for(i=0;i<Menu_GetTrackClipCount();i++) {
            clip=Menu_GetTrackClip(i);
             {
                s32 n=clip->count;
                TrackTransformKey *base=clip->keys;
                if(n>0) {
                    total+=base[n-1].time;
                }
            }
        }
        g_cinemaSequenceState->start=0.0f;
        g_cinemaSequenceState->end=total;
        g_cinemaSequenceState->clipStart=0.0f;
        g_cinemaSequenceState->clipEnd=total;
        i=0;
        if(count>0) {
            scanContext=g_cinemaSequenceState;
            do {
                PositionKey *c=&cue[i];
                minTime_trackLoadtracksequence(&scanContext->clipStart,&c->time);
                maxTime_trackLoadtracksequence(&scanContext->clipEnd,&c->time);
                i++;
            }
            while(i<count);
        }
        setTimes_trackLoadtracksequence(&g_cinemaSequenceState->time,&g_cinemaSequenceState->time20,&g_cinemaSequenceState->time24,&g_cinemaSequenceState->clipStart);
        previous=g_cinemaSequenceState->spec.id8;
        loaded=SetN64_LocatePackSection(g_trackResourceDirectory,g_trackResourceDirectoryKey,0,&size2);
        if(loaded==0)table=0;
        else table=Cache_RequestResource(0,loaded,loaded,size2,51,0,0,g_cinemaDirectoryText,1);
         {
            Shared_TrackTable *entries=*table;
            TrackResourceEntry *base=entries->entries;
            g_cinemaSequenceState->pending=pending;
            g_cinemaSequenceState->active=1;
            g_cinemaSequenceState->spec=base[index];
        }
        g_cinemaSequenceState->sequenceAdvanceRequested=0;
        g_cinemaSequenceState->sequenceStarted=0;
        g_cinemaSequenceState->initialized44=0;
        g_cinemaSequenceState->closed=0;
        g_cinemaSequenceState->requestE0=g_cinemaSequenceState->spec.id8;
        if((g_cinemaSequenceState->spec.flags&1) && g_cinemaSequenceState->target!=0) {
            g_cinemaSequenceState->position=g_cinemaSequenceState->target->prefix.position;
            g_cinemaSequenceState->yaw=g_cinemaSequenceState->target->yaw+g_trackInitialYawOffset;
        }
        if(g_cinemaSequenceState->spec.flags&2) {
            if(captured!=0) {
                g_cinemaSequenceState->position=captured->prefix.position;
                g_cinemaSequenceState->yaw=captured->yaw;
            }
            else {
                g_cinemaSequenceState->position.x=0.0f;
                g_cinemaSequenceState->position.y=0.0f;
                g_cinemaSequenceState->position.z=0.0f;
                g_cinemaSequenceState->yaw=0.0f;
            }
        }
        Cache_UnlockResource(0,(void *)table);
        if(pending) {
            void (*first)();
            Shared_MenuVoidCallback second;
            context=g_cinemaSequenceState;
            first=context->callbackE4;
            second=context->callbackE8;
            context->pending=1;
            context->pendingStartFlag=0;
            context->callbackE4=0;
            context->callbackE8=0;
            context->mode=context->spec.flags&8;
            context->onClose=first;
            context->callback10=second;
            if(context->requestE0-10U<71U)context->mode=0;
            if(g_cinemaSequenceState->requestE0-400U<4U)g_cinemaSequenceState->mode=0;
        }
        else {
            if(g_cinemaSequenceState->spec.id8<3)g_cinemaSequenceState->requestE0=previous;
            g_cinemaSequenceState->pending=0;
            g_cinemaSequenceState->time=g_cinemaSequenceState->start;
        }
        if(g_cinemaSequenceState->spec.id8==159)g_cinemaSequenceState->mode=0;
        return 1;
    }
}

/* Evaluates a spline built by Track_BuildWeightedSpline at weight w, returning the position: zero for no nodes, the first or last node's position outside the weight range, and otherwise locates the weight segment, eases the arc length across it with a cubic blend of the neighbouring arc-length spacings, locates the arc-length segment and interpolates the position with the stored second derivatives. */
CVector3 Track_EvaluateCameraSpline(SplineNode *nodes, s32 count, f32 w) {
    CVector3 out;
    SplineNode *a;
    SplineNode *b;
    s32 i;
    f32 before;
    f32 across;
    f32 after;
    f32 inSlope;
    f32 outSlope;
    f32 u;
    f32 aw;
    f32 bw;
    f32 as;
    f32 bs;
    f32 s;
    f32 start;
    f32 h;
    f32 hi;
    f32 lo;
    f32 h2;

    a = 0;
    b = 0;
    if (count == 0) {
        out.x = 0.0f;
        out.y = 0.0f;
        out.z = 0.0f;
    } else if (count == 1 || w <= nodes[0].w) {
        out.x = nodes[0].p.x;
        out.y = nodes[0].p.y;
        out.z = nodes[0].p.z;
    } else if (nodes[count - 1].w <= w) {
        out.x = nodes[count - 1].p.x;
        out.y = nodes[count - 1].p.y;
        out.z = nodes[count - 1].p.z;
    } else {
        for (i = 0; i < count - 1; i++) {
            a = &nodes[i];
            b = &nodes[i + 1];
            if (a->w <= w && w < b->w) {
                break;
            }
        }
        across = 0.0f;
        before = 0.0f;
        after = 0.0f;
        if (i > 0) {
            before = nodes[i].s - nodes[i - 1].s;
        }
        if (i < count - 1) {
            across = nodes[i + 1].s - nodes[i].s;
        }
        if (i < count - 2) {
            after = nodes[i + 2].s - nodes[i + 1].s;
        }
        inSlope = across;
        if (!(inSlope <= before)) {
            inSlope = before;
        }
        outSlope = after;
        if (!(outSlope <= across)) {
            outSlope = across;
        }
        aw = a->w;
        bw = b->w;
        as = a->s;
        bs = b->s;
        if (aw != bw) {
            u = (w - aw) / (bw - aw);
        } else {
            u = 0.0f;
        }
        s = as * (1.0f - u) + bs * u + (inSlope - (bs - as)) * (u - (u + u) * u + u * u * u) + (outSlope - (bs - as)) * (u * u * u - u * u);
        for (i = 0; i < count - 1; i++) {
            a = &nodes[i];
            b = &nodes[i + 1];
            if (a->s <= s && s < b->s) {
                break;
            }
        }
        start = a->s;
        h = b->s - start;
        hi = 0.0f;
        if (h != 0.0f) {
            hi = (s - start) / h;
        }
        h2 = h * h;
        lo = 1.0f - hi;
        out.x = a->p.x * lo + b->p.x * hi + (a->d2p.x * (lo * lo * lo - lo) + b->d2p.x * (hi * hi * hi - hi)) * h2 * 0.16666667f;
        out.y = a->p.y * lo + b->p.y * hi + (a->d2p.y * (lo * lo * lo - lo) + b->d2p.y * (hi * hi * hi - hi)) * h2 * 0.16666667f;
        out.z = a->p.z * lo + b->p.z * hi + (a->d2p.z * (lo * lo * lo - lo) + b->d2p.z * (hi * hi * hi - hi)) * h2 * 0.16666667f;
    }
    return out;
}

/* Evaluates the position keyframe track 1 of the current record's resource at time t: holds the
   first or last key's position outside the track, is zero when the track is empty, and otherwise
   blends the surrounding keys' positions linearly with the vector scale and add helpers. Vector
   counterpart of Track_EvaluateTrackOpacity. */
CVector3 Track_EvaluateTrackColor(f32 t) {
    s32 *track;
    PositionKey *key;
    s32 count;
    f32 u;
    CVector3 result;
    CVector3 a;
    CVector3 b;

    track = SetN64_GetPackSection(g_cinemaSequenceState->resource, 1);
    count = track[1];
    key = (PositionKey *)(track + 2);
    if (count == 0) {
        result.x = 0.0f;
        result.y = 0.0f;
        result.z = 0.0f;
        return result;
    } else if (t <= key[0].time) {
        result.x = key[0].x;
        result.y = key[0].y;
        result.z = key[0].z;
        return result;
    } else if (key[count - 1].time <= t) {
        result.x = key[count - 1].x;
        result.y = key[count - 1].y;
        result.z = key[count - 1].z;
        return result;
    } else {
        while (key->time < t) {
            key++;
        }
        u = (t - key[-1].time) / (key->time - key[-1].time);
        a.x = key[-1].x;
        a.y = key[-1].y;
        a.z = key[-1].z;
        b.x = key->x;
        b.y = key->y;
        b.z = key->z;
        Graphu64_ScaleVector(&a, &a, (1.0f) - u);
        Graphu64_ScaleVector(&b, &b, u);
        Graphu64_AddVec3(&result, &a, &b);
    }
    return result;
}

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)

#endif

/* Draw the inset viewport border with black bands and a one-pixel outline. */

void Track_DrawLetterboxBorder(s32 inset) {
    f32 left;
    f32 top;
    f32 width;
    f32 height;
    Geometry_InvalidateMaterialKeys();
    left = 0.0f;
    top = (f32)inset;
    gDPPipeSync(g_displayListCursor++);
    gDPSetCycleType(g_displayListCursor++, G_CYC_1CYCLE);
    gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE);
    gDPSetRenderMode(g_displayListCursor++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    width = (f32)g_hudReferenceViewportWidth;
    gDPSetPrimColor(g_displayListCursor++, 0, 0, 0, 0, 0, 0);
    height = (f32)(g_hudReferenceViewportHeight - inset * 2);
    gDPFillRectangle(g_displayListCursor++, left, top, (width - 1.0f), (top + (2.0f)));
    gDPFillRectangle(g_displayListCursor++, left, ((top + height) - (2.0f)), ((left + width) - (1.0f)), ((top + height) - (1.0f)));
    gDPFillRectangle(g_displayListCursor++, left, top, (left + (2.0f)), ((top + height) - 1.0f));
    gDPFillRectangle(g_displayListCursor++, ((left + width) - (2.0f)), top, ((left + width) - (1.0f)), ((top + height) - (1.0f)));
    gDPPipeSync(g_displayListCursor++);
    gDPSetCycleType(g_displayListCursor++, G_CYC_FILL);
    gDPSetCombineLERP(g_displayListCursor++, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE);
    gDPSetRenderMode(g_displayListCursor++, 0, 0);
    gDPSetFillColor(g_displayListCursor++, 0x10001);
    gDPFillRectangle(g_displayListCursor++, left, top, ((left + width) - 1.0f), top);
    gDPFillRectangle(g_displayListCursor++, left, ((top + height) - (1.0f)), ((left + width) - (1.0f)), ((top + height) - (1.0f)));
    gDPFillRectangle(g_displayListCursor++, left, top, left, ((top + height) - (1.0f)));
    gDPFillRectangle(g_displayListCursor++, ((left + width) - (1.0f)), top, (left + width), ((top + height) - (1.0f)));
}


#define MENU_CLAMP_PIXEL(value) \
    ({ s32 edge = (value); if (edge < 0) edge = 0; edge; })
#define MENU_CLAMP_HEIGHT(value) \
    ({ f32 edge = (value); if (!(edge >= 0.0f)) edge = 0.0f; edge; })

/* Fade letterbox bands around the active track and draw the viewport border. */
void Track_DrawLetterboxBands(void) {
    f32 fade = 1.0f;
    f32 height, span;
    height = ((f32)g_hudReferenceViewportHeight - (f32)g_hudReferenceViewportWidth / g_cinemaSequenceState->spec.aspectRatio) * 0.5f;
    span = 0.3f;
    if (g_cinemaSequenceState->time < g_cinemaSequenceState->start) {
        fade = g_cinemaSequenceState->start - g_cinemaSequenceState->time;
        fade /= span;
        if (1.0f < fade) fade = 1.0f;
        fade = 1.0f - fade;
    }
    if (g_cinemaSequenceState->time > g_cinemaSequenceState->end) {
        fade = g_cinemaSequenceState->time - g_cinemaSequenceState->end;
        fade /= span;
        if (1.0f < fade) fade = 1.0f;
        fade = 1.0f - fade;
    }
    height = height * fade;
    gDPPipeSync(g_displayListCursor++);
    gDPSetCycleType(g_displayListCursor++, G_CYC_1CYCLE);
    Geometry_SetModePreset(19);
    Geometry_SetCombineMode(25);
    gDPSetPrimColor(g_displayListCursor++, 255, 255, 0, 0, 0, 255);
    gDPFillRectangle(g_displayListCursor++, 0, 0, MENU_CLAMP_PIXEL(g_hudReferenceViewportWidth), MENU_CLAMP_PIXEL((s32)height));
    gDPFillRectangle(g_displayListCursor++, 0, (u32)MENU_CLAMP_HEIGHT((f32)g_hudReferenceViewportHeight - height), MENU_CLAMP_PIXEL(g_hudReferenceViewportWidth), MENU_CLAMP_PIXEL(g_hudReferenceViewportHeight));
    Track_DrawLetterboxBorder((s32)height);
}

#undef MENU_CLAMP_PIXEL
#undef MENU_CLAMP_HEIGHT
#undef MENU_CLAMP_PIXEL
#undef MENU_CLAMP_HEIGHT

static inline u32 toUnsigned_trackDrawtrackoverlay(f32 v,f32 limit) { u32 result; if(!(limit<=v)) result=(u32)(s32)v; else { v-=limit; result=(u32)(s32)v; result|=0x80000000U; } return result; }
static inline f32 unsignedWidth_trackDrawtrackoverlay(u32 v) { f64 d=(s32)v; if((s32)v<0)d+=g_trackOverlayWidthUnsignedBias; return (f32)d; }
static inline f32 unsignedHeight_trackDrawtrackoverlay(u32 v) { f64 d=(s32)v; if((s32)v<0)d+=g_trackOverlayHeightUnsignedBias; return (f32)d; }
void Track_DrawTrackOverlay(ScreenRectangle *rectangle) {
    CVector3 color,baseColor;
    u8 rgba[4];
    u32 width,height,right,bottom;
    f32 alpha,scale,value;
    if(g_cinemaSequenceState->active) {
        value=rectangle->width;
        if(!(((f32 *)&g_trackOverlayHeightUnsignedThreshold)[-1]<=value)) width=(u32)(s32)value;
        else {value-=((f32 *)&g_trackOverlayHeightUnsignedThreshold)[-1]; width=(u32)(s32)value; width|=0x80000000U;}
        value=rectangle->height;
        if(!(g_trackOverlayHeightUnsignedThreshold<=value)) height=(u32)(s32)value;
        else {value-=g_trackOverlayHeightUnsignedThreshold; height=(u32)(s32)value; height|=0x80000000U;}
        value=unsignedWidth_trackDrawtrackoverlay(width)+rectangle->x;
        if(!(((f32 *)&g_trackOverlayWidthUnsignedBias)[2]<=value)) right=(u32)(s32)value;
        else {value-=((f32 *)&g_trackOverlayWidthUnsignedBias)[2]; right=(u32)(s32)value; right|=0x80000000U;}
        value=unsignedHeight_trackDrawtrackoverlay(height)+rectangle->y;
        if(!(g_trackOverlayBottomUnsignedThreshold<=value)) bottom=(u32)(s32)value;
        else {value-=g_trackOverlayBottomUnsignedThreshold; bottom=(u32)(s32)value; bottom|=0x80000000U;}
        baseColor=Track_EvaluateTrackColor(g_cinemaSequenceState->time);
        alpha=Track_EvaluateTrackOpacity(g_cinemaSequenceState->time);
        color=baseColor;
        if(g_cinemaSequenceState->fadeRequested) {
            scale=g_cinemaSequenceState->fade;
            if(scale<0.0f)scale=0.0f;
            color.x=baseColor.x*scale;
            color.y=baseColor.y*scale;
            color.z=baseColor.z*scale;
            alpha+=g_trackOverlayAlphaAndColorScales-scale;
        }
        value=color.x*((f32 *)&g_trackOverlayAlphaAndColorScales)[1];
        if(!(value<=((f32 *)&g_trackOverlayAlphaAndColorScales)[1]))value=((f32 *)&g_trackOverlayAlphaAndColorScales)[1];
        if(!(0.0f<=value))value=0.0f;
        rgba[0]=(u8)toUnsigned_trackDrawtrackoverlay(value,((f32 *)&g_trackOverlayGreenScale)[-1]);
        value=color.y*g_trackOverlayGreenScale;
        if(!(value<=g_trackOverlayGreenScale))value=g_trackOverlayGreenScale;
        if(!(0.0f<=value))value=0.0f;
        rgba[1]=(u8)toUnsigned_trackDrawtrackoverlay(value,((f32 *)&g_trackOverlayGreenScale)[1]);
        value=color.z*g_trackOverlayBlueAndAlphaScales;
        if(!(value<=g_trackOverlayBlueAndAlphaScales))value=g_trackOverlayBlueAndAlphaScales;
        if(!(0.0f<=value))value=0.0f;
        rgba[2]=(u8)toUnsigned_trackDrawtrackoverlay(value,((f32 *)&g_trackOverlayBlueAndAlphaScales)[1]);
        value=alpha*((f32 *)&g_trackOverlayBlueAndAlphaScales)[2];
        if(!(value<=((f32 *)&g_trackOverlayBlueAndAlphaScales)[2]))value=((f32 *)&g_trackOverlayBlueAndAlphaScales)[2];
        if(!(0.0f<=value))value=0.0f;
        rgba[3]=(u8)toUnsigned_trackDrawtrackoverlay(value,((f32 *)&g_trackOverlayAlphaAndColorScales)[8]);
        value=0.0f;
        SetN64_DrawColorRectangle(&g_gameSession,rgba,width,height,right,bottom);
    }
    if(g_cinemaLetterboxEnabled)Track_DrawLetterboxBands();
}

/* Returns 1 unless one of the current record's track-2 references names an item, in the first or
   second item table of g_world_AchieveUpdateresultsscreen by its side flag, whose kind and subkind are 1 and 5, 9 and 4,
   or 10 and 3. */
void Track_RequestTrackByIds(struct SharedTrackObject *owner, TrackRequestIds *obj) {
    s32 size;
    s32 **table;
    s32 key;
    s32 found;
    s32 i;
    s32 n;
    TrackOverlayIdEntry *entry;
    s32 id4;
    s32 idA;

    found = -1;
    if (g_cinemaPlaybackFlag != 0) {
        id4 = obj->trackId;
        idA = obj->variantId;
        key = SetN64_LocatePackSection(g_trackResourceDirectory, g_trackResourceDirectoryKey, 0, &size);
        if (key == 0) {
            table = 0;
        } else {
            table = Cache_RequestResource(0, key, key, size, 51, 0, 0, g_cinemaDirectoryText, 1);
        }
        n = *g_trackResourceDirectory - 1;
        entry = (TrackOverlayIdEntry *)(*table + 2);
        for (i = 0; i < n; i++, entry++) {
            if (entry->id4 == id4 && entry->id0 == idA) {
                found = i;
            }
        }
        if (found != -1) {
            g_cinemaSequenceState->target = owner;
            g_cinemaSequenceState->targetD8 = idA;
            g_cinemaSequenceState->resourceDC = found;
            g_cinemaSequenceState->pendingTrackId = 1;
        }
        Cache_UnlockResource(0, table);
    }
}

s32 Track_RequestTrackByKey(s32 key) {
    s32 size;
    s32 **table;
    s32 loaded;
    s32 i;
    s32 n;
    TrackResourceEntry *entries;

    if (g_cinemaPlaybackFlag == 0) {
        return 0;
    }
    loaded = SetN64_LocatePackSection(g_trackResourceDirectory, g_trackResourceDirectoryKey, 0, &size);
    if (loaded == 0) {
        table = 0;
    } else {
        table = Cache_RequestResource(0, loaded, loaded, size, 51, 0, 0, g_cinemaDirectoryText, 1);
    }
    i = 0;
    entries = (TrackResourceEntry *)(*table + 2);
    n = *g_trackResourceDirectory - 1;
    for (; i < n; i++) {
        if (entries[i].id8 == key) {
            if ((entries[i].flags & 3) == 0) {
                g_cinemaSequenceState->targetD8 = entries[i].id0;
            }
            g_cinemaSequenceState->requestE0 = key;
            g_cinemaSequenceState->resourceDC = i;
            g_cinemaSequenceState->pendingTrackId = 1;
            break;
        }
    }
    Cache_UnlockResource(0, table);
    Cinema_ClearMessageCount();
    return g_cinemaSequenceState->targetD8;
}

void Track_RequestTrackByName(char *name) {
    s32 size;
    s32 **table;
    s32 loaded;
    s32 i;
    s32 id;
    s32 n;
    TrackOverlayNamedEntry *entries;

    if (g_cinemaPlaybackFlag != 0) {
        loaded = SetN64_LocatePackSection(g_trackResourceDirectory, g_trackResourceDirectoryKey, 0, &size);
        if (loaded == 0) {
            table = 0;
        } else {
            table = Cache_RequestResource(0, loaded, loaded, size, 51, 0, 0, g_cinemaDirectoryText, 1);
        }
        i = 0;
        entries = (TrackOverlayNamedEntry *)(*table + 2);
        n = *g_trackResourceDirectory - 1;
        for (; i < n; i++) {
            if (((s32 (*)(char *, char *))SetN64_CompareByteStrings)(name, entries[i].name) == 0) {
                g_cinemaSequenceState->requestE0 = entries[i].id8;
                id = entries[i].id0;
                g_cinemaSequenceState->resourceDC = i;
                g_cinemaSequenceState->pendingTrackId = 1;
                g_cinemaSequenceState->targetD8 = id;
                break;
            }
        }
        Cache_UnlockResource(0, table);
    }
}

s32 Track_HasNoTrackRequestItems(void) {
    s32 found;
    s32 *track;
    Triple *refs;
    TriggerStateBitDescriptor *item;
    s32 i;
    s32 n;
    s32 hit;

    Shared_World *tables;
    found = 0;
    track = SetN64_GetPackSection(g_cinemaSequenceState->resource, 2);
    n = track[1];
    refs = (Triple *)(track + 2);
    for (i = 0; i < n; i++) {
        tables = &g_world;
        if (refs[i].y == 0) {
            item = &((TriggerStateBitDescriptor *)tables->recordArray)[refs[i].z];
        } else {
            item = &((TriggerStateBitDescriptor *)tables->alternateRecordArray)[refs[i].z];
        }
        hit = 0;
        switch (item->kind) {
            case 1:
                if (item->subkind == 5) {
                    hit = 1;
                }
                break;
            case 9:
                if (item->subkind == 4) {
                    hit = 1;
                }
                break;
            case 10:
                if (item->subkind == 3) {
                    hit = 1;
                }
                break;
            default:
                hit = 0;
                break;
        }
        if (hit) {
            found = 1;
        }
    }
    return found ^ 1;
}

#if defined(VERSION_US_REV1)

#endif

/* Samples the current record's clip sequence at time t: walks clip list 0 accumulating each
   clip's end time (the time of its last 0x24-byte key) until the clip spanning t is found or the
   ends are passed, then evaluates that clip's keys through Track_EvaluateCameraSpline at the time into the
   clip, frozen at the clip start when the clip's flag word is set. */
CVector3 Track_GetTrackEyePosition(f32 t) {
    s32 i;
    s32 idx;
    s32 count;
    TrackTransformKey *keys;
    s32 *clip;
    f32 start;
    f32 end;

    start = 0.0f;
    count = 0;
    keys = 0;
    idx = 0;
    i = 0;
    end = start;
    while (i < *((s32 *)SetN64_GetPackSection(g_cinemaSequenceState->resource, 0))) {
        idx = i;
        clip = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(g_cinemaSequenceState->resource, 0), idx), 0);
        count = clip[1];
        keys = (TrackTransformKey *)(clip + 2);
        start = end;
        end = start + keys[count - 1].time;
        if (idx == 0 && t <= start) {
            break;
        }
        if (idx == *((s32 *)SetN64_GetPackSection(g_cinemaSequenceState->resource, 0)) - 1 && end < t) {
            break;
        }
        i = idx + 1;
        if (start <= t && t <= end) {
            break;
        }
    }
    if (*((s32 *)SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(g_cinemaSequenceState->resource, 0), idx), 2)) != 0) {
        t = start;
    }
    return Track_EvaluateCameraSpline((SplineNode *)keys, count, t - start);
}

/* Samples the current record's clip sequence at time t: walks clip list 0 accumulating each
   clip's end time (the time of its last 0x24-byte key) until the clip spanning t is found or the
   ends are passed, then evaluates that clip's keys through Track_EvaluateCameraSpline at the time into the
   clip, frozen at the clip start when the clip's second flag word is set; the track-1 counterpart of Track_GetTrackEyePosition, matched the same way. */
CVector3 Track_GetTrackTargetPosition(f32 t) {
    s32 i;
    s32 idx;
    s32 count;
    TrackTransformKey *keys;
    s32 *clip;
    f32 start;
    f32 end;

    start = 0.0f;
    count = 0;
    keys = 0;
    idx = 0;
    i = 0;
    end = start;
    while (i < *((s32 *)SetN64_GetPackSection(g_cinemaSequenceState->resource, 0))) {
        idx = i;
        clip = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(g_cinemaSequenceState->resource, 0), idx), 1);
        count = clip[1];
        keys = (TrackTransformKey *)(clip + 2);
        start = end;
        end = start + keys[count - 1].time;
        if (idx == 0 && t <= start) {
            break;
        }
        if (idx == *((s32 *)SetN64_GetPackSection(g_cinemaSequenceState->resource, 0)) - 1 && end < t) {
            break;
        }
        i = idx + 1;
        if (start <= t && t <= end) {
            break;
        }
    }
    if (((s32 *)SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(g_cinemaSequenceState->resource, 0), idx), 2))[1] != 0) {
        t = start;
    }
    return Track_EvaluateCameraSpline((SplineNode *)keys, count, t - start);
}

/* The copied prefix is exactly 0x50 bytes. */

/* The two adjacent track constants are consumed at base and base+4. */

f32 Track_EvaluateTrackOpacity(f32 t) {
    s32 *track;
    TrackOpacityKey *key;
    s32 count;
    f32 u;
    f32 v;

    track = SetN64_GetPackSection(g_cinemaSequenceState->resource, 1);
    count = track[1];
    key = (TrackOpacityKey *)(track + 2);
    if (count == 0) {
        v = 0.0f;
    } else if (t <= key[0].time) {
        v = key[0].value;
    } else if (key[count - 1].time <= t) {
        v = key[count - 1].value;
    } else {
        while (key->time < t) {
            key++;
        }
        u = (t - key[-1].time) / (key->time - key[-1].time);
        v = key[-1].value * ((*(&g_trackLinearInterpolationConstants + 1)) - u) + key->value * u;
    }
    v *= 2.0f * g_trackSplineRangeScale + g_trackSplineOutputBounds[0];
    v -= g_trackSplineRangeScale;
    if (g_trackSplineOutputBounds[0] < v) {
        v = g_trackSplineOutputBounds[0];
    }
    if (v < 0.0f) {
        v = 0.0f;
    }
    return v;
}



/* Evaluates keyframe track 3 of the current record's resource at time t: before the first key or
   after the last it holds that key's value, otherwise it finds the surrounding keys and blends
   their values with the smoothstep weight 3u^2 - 2u^3; an empty track yields g_trackSplineOutputBounds[1]. */
f32 Track_EvaluateTrackScalar(f32 t) {
    s32 *track;
    ScalarPair *key;
    s32 count;
    s32 i;
    f32 u;
    track = SetN64_GetPackSection(g_cinemaSequenceState->resource, 3);
    key = (ScalarPair *)(track + 2);
    count = track[1];
    for (i = 0; i < count; i++) {
    }
    if (count == 0) {
        return g_trackSplineOutputBounds[1];
    }
    if (t <= key[0].second) {
        return key[0].first;
    }
    if (key[count - 1].second <= t) {
        return key[count - 1].first;
    }
    while (key->second < t) {
        key++;
    }
    u = (t - key[-1].second) / (key->second - key[-1].second);
    u = u * (u * g_trackSmoothInterpolationConstants) - 2.0f * u * u * u;
    return key[-1].first * ((*(&g_trackSmoothInterpolationConstants + 1)) - u) + key->first * u;
}


/* Follow the keyframe camera and keep the collision result across world cleanup. */
void Track_UpdateTrackCamera(SharedTrackCamera *camera) {
    CVector3 eye;
    CVector3 target;
    CVector3 delta;
    SharedTrackObjectPrefix saved;
    f32 matrix[16];
    CVector3 rotated;
    SharedTrackObject *actor;
    s32 collisionHit;
    f32 yaw;
    f32 pitch;
    f32 scale;

    if (g_cinemaSequenceState->active == 0) {
        return;
    }
    if (Cinema_IsSequenceInWindow() == 0) {
        return;
    }
    if (g_cinemaSequenceState->time < g_cinemaSequenceState->start || g_cinemaSequenceState->end < g_cinemaSequenceState->time) {
        return;
    }
    if (g_cinemaSequenceState->messageCount > 0) {
        CCinema_DrawMessages();
    }
    eye = Track_GetTrackEyePosition(g_cinemaSequenceState->time);
    target = Track_GetTrackTargetPosition(g_cinemaSequenceState->time);
    scale = g_trackCameraScaleAndYawOffset[0];
    Graphu64_ScaleVector(&eye, &eye, scale);
    Graphu64_ScaleVector(&target, &target, scale);
    camera->distance = 0.0f;
    Graphu64_SubtractVectors(&delta, &target, &eye);
    if (((g_cinemaSequenceState->spec.flags & 1) && g_cinemaSequenceState->target != 0) || (g_cinemaSequenceState->spec.flags & 2)) {
        actor = g_transientPlayerList.actorList;
        if ((g_cinemaSequenceState->spec.flags & 1) && g_cinemaSequenceState->target != 0) {
            g_cinemaSequenceState->position = g_cinemaSequenceState->target->prefix.position;
            g_cinemaSequenceState->yaw = g_cinemaSequenceState->target->yaw + g_trackCameraScaleAndYawOffset[1];
        }
        if (g_cinemaSequenceState->spec.flags & 2) {
            if (actor != 0) {
                g_cinemaSequenceState->position = actor->prefix.position;
                g_cinemaSequenceState->yaw = actor->yaw;
            } else {
                g_cinemaSequenceState->position.x = 0.0f;
                g_cinemaSequenceState->position.y = 0.0f;
                g_cinemaSequenceState->position.z = 0.0f;
                g_cinemaSequenceState->yaw = 0.0f;
            }
        }
        Graphu64_IdentityMatrix(matrix);
        Graphu64_MatrixFromEulerXYZ(matrix, 0.0f, g_cinemaSequenceState->yaw, 0.0f);
        Graphu64_TransformPoint(matrix, &target, &rotated);
        target = rotated;
        Graphu64_TransformPoint(matrix, &eye, &rotated);
        eye = rotated;
        Graphu64_AddVec3(&target, &target, &g_cinemaSequenceState->position);
        Graphu64_AddVec3(&eye, &eye, &g_cinemaSequenceState->position);
        Graphu64_SubtractVectors(&delta, &target, &eye);
        if (actor != 0) {
            saved = actor->prefix;
            actor->prefix.position = target;
            Scene_RequestVisibleGridSections(&g_world);
            collisionHit = Unicol_MoveActorWithCollision(actor, eye, (u32 *)&g_defaultProbeMotionSettings);
            Scene_UnlockActiveSectionResources(&g_world);
            actor->prefix = saved;
            if (collisionHit != 0) {
                __builtin_memcpy(&eye, &((CCollisionResults *)&g_currentActorInstance)->vec8, sizeof(eye));
            }
        }
    }
    yaw = Graphu64_GetHorizontalAngle(&delta);
    pitch = Graphu64_GetVerticalAngle(&delta);
    camera->distance += yaw;
    camera->pitch = -pitch;
    camera->position = eye;
}

/* Retained data for this translation unit. */
#if defined(VERSION_US_REV1)
const char s_cinemaResourceTagUsRev1[7] =
    "Cinema";
#endif
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
const float g_trackCameraInterpolationUnitConstantsDe[2] = {
    1.0f, 1.0f,
};
#endif
#if defined(VERSION_US_REV1)
const float g_trackOverlayUnsignedThresholdsUsRev1[2] = {
    2147483648.0f, 2147483648.0f,
};
#endif

const char g_cinemaDirectoryText[17] =
    "Cinema Directory";
#if !(defined(VERSION_US_REV1))
const char s_cinemaText[7] =
    "Cinema";
#endif

#if !defined(VERSION_US)
float g_trackInitialYawOffset = 1.57079637f;
#endif
