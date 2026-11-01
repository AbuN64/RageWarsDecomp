#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/SHAREDTRACKOBJECTPREFIX.H"
#include "COMMON/ACCESS_S8_10F.H"
#include "COMMON/ENTRYRECAT8V4.H"
#include "COMMON/TRIPLE.H"
#include "MENU/TRACK_EVALUATETRACKOPACITY.H"
#include "MENU/TRACK_EVALUATETRACKCOLOR.H"
#include "MENU/TRACK_DRAWLETTERBOXBANDS.H"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/WORLD.H"
#include "SCENE/CACHE_ALLOCATERESOURCEAT.H"
#include "COMMON/AIPROFILE.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

extern void SetN64_DrawColorRectangle(void *,u8 *,s32,s32,s32,s32);
static inline u32 toUnsigned(f32 v,f32 limit) { u32 result; if(!(limit<=v)) result=(u32)(s32)v; else { v-=limit; result=(u32)(s32)v; result|=0x80000000; } return result; }
static inline f32 unsignedWidth(u32 v) { f64 d=(s32)v; if((s32)v<0)d+=g_trackOverlayWidthUnsignedBias; return (f32)d; }
static inline f32 unsignedHeight(u32 v) { f64 d=(s32)v; if((s32)v<0)d+=g_trackOverlayHeightUnsignedBias; return (f32)d; }
void Track_DrawTrackOverlay(ScreenRectangle *rectangle) {
    CVector3 color,baseColor;
    u8 rgba[4];
    u32 width,height,right,bottom;
    f32 alpha,scale,value;
    if(g_cinemaSequenceState->active) {
        value=rectangle->width;
        if(!(((f32 *)&g_trackOverlayHeightUnsignedThreshold)[-1]<=value)) width=(u32)(s32)value;
        else {value-=((f32 *)&g_trackOverlayHeightUnsignedThreshold)[-1]; width=(u32)(s32)value; width|=0x80000000;}
        value=rectangle->height;
        if(!(g_trackOverlayHeightUnsignedThreshold<=value)) height=(u32)(s32)value;
        else {value-=g_trackOverlayHeightUnsignedThreshold; height=(u32)(s32)value; height|=0x80000000;}
        value=unsignedWidth(width)+rectangle->x;
        if(!(((f32 *)&g_trackOverlayWidthUnsignedBias)[2]<=value)) right=(u32)(s32)value;
        else {value-=((f32 *)&g_trackOverlayWidthUnsignedBias)[2]; right=(u32)(s32)value; right|=0x80000000;}
        value=unsignedHeight(height)+rectangle->y;
        if(!(g_trackOverlayBottomUnsignedThreshold<=value)) bottom=(u32)(s32)value;
        else {value-=g_trackOverlayBottomUnsignedThreshold; bottom=(u32)(s32)value; bottom|=0x80000000;}
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
        rgba[0]=(u8)toUnsigned(value,((f32 *)&g_trackOverlayGreenScale)[-1]);
        value=color.y*g_trackOverlayGreenScale;
        if(!(value<=g_trackOverlayGreenScale))value=g_trackOverlayGreenScale;
        if(!(0.0f<=value))value=0.0f;
        rgba[1]=(u8)toUnsigned(value,((f32 *)&g_trackOverlayGreenScale)[1]);
        value=color.z*g_trackOverlayBlueAndAlphaScales;
        if(!(value<=g_trackOverlayBlueAndAlphaScales))value=g_trackOverlayBlueAndAlphaScales;
        if(!(0.0f<=value))value=0.0f;
        rgba[2]=(u8)toUnsigned(value,((f32 *)&g_trackOverlayBlueAndAlphaScales)[1]);
        value=alpha*((f32 *)&g_trackOverlayBlueAndAlphaScales)[2];
        if(!(value<=((f32 *)&g_trackOverlayBlueAndAlphaScales)[2]))value=((f32 *)&g_trackOverlayBlueAndAlphaScales)[2];
        if(!(0.0f<=value))value=0.0f;
        rgba[3]=(u8)toUnsigned(value,((f32 *)&g_trackOverlayAlphaAndColorScales)[8]);
        value=0.0f;
        SetN64_DrawColorRectangle(&g_gameSession,rgba,width,height,right,bottom);
    }
    if(g_cinemaLetterboxEnabled)Track_DrawLetterboxBands();
}

/* When the entry table is available, loads it through SetN64_LocatePackSection and Cache_RequestResource, finds the
   last 0x4C-byte entry whose ids match the object's u16 ids at 4 and 0xA, and on a match records
   the owner, the id, the entry index and a pending flag in the current record; the loaded table
   is then released through Cache_UnlockResource. */










extern const char g_cinemaDirectoryText[];

extern s32 SetN64_LocatePackSection(s32 *, s32, s32, s32 *);



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
/* ROM-grounded data: src/k_trackOverlayThresholdPool_us_rev1.c */
const float g_trackOverlayUnsignedThresholdsUsRev1[2] = {
    2147483648.0f, 2147483648.0f,
};
#endif
