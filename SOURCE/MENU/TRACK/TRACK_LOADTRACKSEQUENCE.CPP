#include "COMMON/ENTRYRECAT8V4.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
#include "COMMON/BALLISTICPARAMS.H"
#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "COMMON/PPDECOM_UNPACKRESOURCE.H"
#include "COMMON/TEXTURE_REQUEST.H"
#include "MENU/TRACK_TABLES.H"
#include "COMMON/WORLD.H"
#include "COMMON/ACCESS_S8_10F.H"
#include "COMMON/LOCALDECODERANGE.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "MENU/TRACK_LOADTRACKSEQUENCE.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

extern struct CacheResourceBlockView *Cache_AllocResourceBlock(s32,void *,s32);

extern void Track_BuildWeightedSpline(s32,CVector3 *,f32 *,Spline *);

extern void Cache_ReplaceResourceBlock(s32,struct CacheResourceBlockView **,struct CacheResourceBlockView *);

/* A nonnull source is copied into the new pack section; null reserves it. */
static inline char *packAppend(Pack *pack,const void *source,s32 size) { return Polytrak2_AppendOutputPackSection(pack,source,size); }

static inline s32 splineRecordSize(s32 left,s32 right) { s32 a=left*9,b=right*9; return (b+a)*4+48; }

extern const char g_cinemaDirectoryText[];

extern s32 SetN64_LocatePackSection(void *,s32,s32,s32 *);

extern void Cache_UnlockResource(void *,CacheResourceNode *);

static inline void minTime(f32 *dest,f32 *src) {
    if(*dest>*src)*dest=*src;
}

static inline void maxTime(f32 *dest,f32 *src) {
    if(*dest<*src)*dest=*src;
}

static inline void setTimes(f32 *a,f32 *b,f32 *c,f32 *t) {
    *a=*t;
    *b=*t;
    *c=*t;
}

void Track_BuildTrackResourceSplines(s32 unused, struct CacheResourceBlockView **handle) {
    struct CacheResourceBlockView *output;
    void *source, *a, *b, *c, *part, *extra;
    Pack *pack, *dest;
    SplineTable *parts;
    Pack *table;
    SplineSourceCursor p,q,r,s;
    s32 count, i, size, sa, sb, sc, np, nr, byteP, byteR;
    void *dp, *dr;
    if (!Ppdecom_UnpackResource((void **)handle, 1)) return;
    source = (*handle)->pack;
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
        size += splineRecordSize(firstP->count,firstR->count);
    }
    sc = SetN64_GetRecordBlockSize(c);
    sa = SetN64_GetRecordBlockSize(a);
    sb = SetN64_GetRecordBlockSize(b);
    output = Cache_AllocResourceBlock(0, handle, size + sa + sb + sc + 24);
    if (output == 0) return;
    pack = output->pack;
    Polytrak2_InitializeOutputPack(pack, 4);
    table = (void *)packAppend(pack, 0, size);
    packAppend(pack, a, sa);
    packAppend(pack, b, sb);
    packAppend(pack, c, sc);
    Polytrak2_InitializeOutputPack(table, count);
    for (i = 0; i < count; i++) {
        s32 byteP,byteR;
        SplineSource *sizeP,*sizeR;
        part = SetN64_GetPackSection(parts, i);
        sizeP = SetN64_GetPackSection(part, 0);
        sizeR = SetN64_GetPackSection(part, 2);
        byteP = sizeP->count * 9;
        byteR = sizeR->count * 9;
        dest = (void *)packAppend(table, 0, (byteR + byteP)*4 + 48);
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
        dp = packAppend(dest, 0, pointBytes);
        dr = packAppend(dest, 0, otherBytes);
        }
        p.points = p.header->points;
        q.weights = q.header->weights;
        r.points = r.header->points;
        s.weights = s.header->weights;
        packAppend(dest, extra, 8);
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
                minTime(&scanContext->clipStart,&c->time);
                maxTime(&scanContext->clipEnd,&c->time);
                i++;
            }
            while(i<count);
        }
        setTimes(&g_cinemaSequenceState->time,&g_cinemaSequenceState->time20,&g_cinemaSequenceState->time24,&g_cinemaSequenceState->clipStart);
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
