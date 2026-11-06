#include "include_asm.h"
#include "Common/world.h"
#include "Common/track_spline.h"
#include "types.h"
#include "Menu/menu_processtrackitemevents.h"
#include "Render/setn64_getpacksection.h"
#include "Link/link_dispatchmatchingtriggers.h"
#include "Menu/Items/Scene/scene_setlevelactorstatebit.h"
#include "Track/track_drawtrackoverlay.h"
#include "Common/viewflags.h"
#include "Common/shared_optionsscreen.h"
#include "Common/aiprofile.h"
#include "Common/track_transform_keys.h"
#include "Common/gameplay_transition.h"
#include "Common/sharedplayer.h"
#include <platform_sdk.h>
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Common/approachlocation.h"
#include "Menu/track_loadtracksequence.h"
#include "Common/sharedtrackobjectprefix.h"
#include "Common/ballisticparams.h"
#include "Common/track_requesttrackbykey.h"
#include "Common/runtime_declarations.h"
#include "Common/note_state.h"
#include "Menu/pak_directory_views.h"
#include "Menu/Pak/menu_istrackrequestitem.h"
#include "Scene/cache_requestresource.h"
#include "Engine/session.h"
#include "Menu/g_cinemadirectorytext.h"
#include "Menu/track_angles.h"



/* Releases the current record's track-2 timed items whose time has come (or all live ones once the
   record's end time has passed): special items (kind and subkind 1 and 5, 9 and 4, 10 and 3) go to
   Track_RequestTrackByIds_MenuProcesstrackitemevents and clear the record's pending flag, others to Link_ActivateTrigger, then each entry is
   marked spent and its item is flagged and refreshed through Scene_SetTriggerStateBit. */
void Menu_ProcessTrackItemEvents(void) {
    f32 time;
    s32 late;
    s32 *track;
    TrackTimedItemEvent *entry;
    Shared_World *tables;
    TriggerStateBitDescriptor *item;
    s32 n;
    s32 i;
    s32 hit;

    time = g_cinemaSequenceState->time;
    late = 0;
    if (Cinema_IsSequenceActive() == 0) {
        return;
    }
    if (g_cinemaSequenceState->sequenceAdvanceRequested == 0) {
        return;
    }
    track = SetN64_GetPackSection(g_cinemaSequenceState->resource, 2);
    n = track[1];
    entry = (TrackTimedItemEvent *)(track + 2);
    if (n == 0) {
        return;
    }
    if (g_cinemaSequenceState->end <= time) {
        late = 1;
    }
    for (i = 0; i < n; i++) {
        tables = &g_world;
        if (entry[i].time <= -10000.0f) {
            continue;
        }
        if (time < entry[i].time && late == 0) {
            continue;
        }
        if (entry[i].side == 0) {
            item = &((TriggerStateBitDescriptor *)tables->recordArray)[entry[i].index];
        } else {
            item = &((TriggerStateBitDescriptor *)tables->alternateRecordArray)[entry[i].index];
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
            Track_RequestTrackByIds(0, item);
            g_cinemaSequenceState->pendingTrackId = 0;
        } else {
            Link_ActivateTrigger(item);
        }
        entry[i].time = -20000.0f;
        item->flags = (item->flags | 1) & 0xEF;
        Scene_SetTriggerStateBit(&g_world, item, 0);
    }
}

/* First point of the current track's camera path (pack section 0 of section 0 of the resource), or the origin with no track. */
static inline CVector3 TrackStartEye_trackAngles(void) {
    CVector3 point;
    CVector3 origin;
    StridedTable *path;
    if (g_cinemaSequenceState->active == 0) {
        origin.x = 0.0f;
        origin.y = 0.0f;
        origin.z = 0.0f;
        return origin;
    }
    path = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(g_cinemaSequenceState->resource, 0), 0), 0);
    point = Track_EvaluateCameraSpline((SplineNode *)path->data, path->count, 0.0f);
    return point;
}

/* First point of the current track's target path (pack section 1), or 10 units along x with no track. */
static inline CVector3 TrackStartTarget_trackAngles(void) {
    CVector3 point;
    CVector3 fallback;
    StridedTable *path;
    if (g_cinemaSequenceState->active == 0) {
        fallback.y = 0.0f;
        fallback.z = 0.0f;
        fallback.x = 10.0f;
        return fallback;
    }
    path = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(g_cinemaSequenceState->resource, 0), 0), 1);
    point = Track_EvaluateCameraSpline((SplineNode *)path->data, path->count, 0.0f);
    return point;
}

/* Pitch and heading from the track's start point toward its end point (roll 0); all zero with no active track. */
CVector3 Menu_GetTrackStartAngles(void) {
    CVector3 eye, target, direction, angles;
    if (g_cinemaSequenceState->active == 0) {
        angles.x = 0.0f;
        angles.y = 0.0f;
        angles.z = 0.0f;
        return angles;
    } else {
        eye = TrackStartEye_trackAngles();
        target = TrackStartTarget_trackAngles();
        Graphu64_SubtractVectors(&direction, &target, &eye);
        angles.x = -Graphu64_GetVerticalAngle(&direction);
        angles.y = Graphu64_GetHorizontalAngle(&direction);
        angles.z = 0.0f;
        return angles;
    }
}

/* Returns the initial track vector or the configured fallback when no track is active. */

void Track_RequestCameraRefresh(void) {
    g_cinemaSequenceState->sequenceEndRequested = 1;
}

/* Track events 601 to 606 play once per actor. The first byte holds their low-to-high bits;
   the first trigger sets its bit and later triggers are ignored. */
/* Tests bit index of a byte-packed bit array. */
static inline int Track_TestEventBit(unsigned char *bits, int index) {
    int offset = index >> 3;
    int mask;
    index &= 7;
    mask = 1;
    bits += offset;
    return *bits & (mask << index);
}

/* Sets bit index of a byte-packed bit array. */
static inline void Track_SetEventBit(unsigned char *bits, int index) {
    int offset = index >> 3;
    int mask;
    index &= 7;
    mask = 1;
    bits += offset;
    *bits |= mask << index;
}

void Menu_TriggerTrackEvent(int event) {
    Player *actor = (Player *)g_transientPlayerList.actorList;
    int index;
    if (g_cinemaPlaybackFlag != 0) {
        index = event - 601;
        if ((unsigned int)index < 6 && actor != 0) {
            if (Track_TestEventBit((u8 *)&actor->trackEventBits, index)) return;
            Track_SetEventBit((u8 *)&actor->trackEventBits, index);
        }
        Track_RequestTrackByKey(event);
    }
}

CVector3 Menu_GetTrackStartEye(void) {
    CVector3 splinePoint;
    CVector3 fallback;
    StridedTable *table;
    if (g_cinemaSequenceState->active == 0) {
        fallback.x = 0;
        fallback.y = 0;
        fallback.z = 0;
        return fallback;
    }
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(g_cinemaSequenceState->resource, 0), 0), 0);
    splinePoint = Track_EvaluateCameraSpline((SplineNode *)table->data, table->count, 0.0f);
    return splinePoint;
}

CVector3 Menu_GetTrackStartTarget(void) {
    CVector3 splinePoint;
    CVector3 fallback;
    StridedTable *table;
    if (g_cinemaSequenceState->active == 0) {
        fallback.y = 0;
        fallback.z = 0;
        fallback.x = g_trackStartTargetFallbackX;
        return fallback;
    }
    table = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(g_cinemaSequenceState->resource, 0), 0), 1);
    splinePoint = Track_EvaluateCameraSpline((SplineNode *)table->data, table->count, 0.0f);
    return splinePoint;
}

f32 Menu_GetTrackDuration(void) {
    f32 clipDuration;
    f32 result;
    s32 *finalKey;
    s32 index;

    result = 0.0f;
    index = 0;
    while (index < *((s32 *)SetN64_GetPackSection(g_cinemaSequenceState->resource, 0))) {
        finalKey = SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(g_cinemaSequenceState->resource, 0), index), 0);
        finalKey = (s32 *)((char *)finalKey + finalKey[1] * sizeof(TrackTransformKey));
        clipDuration = *(f32 *)finalKey;
        index += 1;
        result += clipDuration;
    }
    return result;
}

s32 Menu_GetTrackClipCount(void) {
    return *((s32 *)SetN64_GetPackSection(g_cinemaSequenceState->resource, 0));
}

void *Menu_GetTrackClip(s32 key) {
    return SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(g_cinemaSequenceState->resource, 0), key), 0);
}

void *Menu_GetTrackCues(void) {
    return SetN64_GetPackSection(g_cinemaSequenceState->resource, 1);
}

/** Advance a byte pointer by eight bytes. */
void *CTrackResource_GetRecordPayload(void *value) {
    TrackAngleKindView *record = value;
    return &record->kind;
}

/** Return the selected bit from a packed byte array. */
u32 Menu_TestBit(u8 *actor, s32 index)
{
    s32 byte = index >> 3;
    u32 mask;

    index &= 7;
    mask = 1;
    actor += byte;
    return *actor & (mask << index);
}

/* Sets or clears bit n of a bitmap according to the third argument. */
void Menu_AssignBit(u8 *actor, s32 n, s32 set) {
    s32 index = n >> 3;
    s32 mask = 1 << (n & 7);

    if (set) {
        actor[index] |= mask;
    } else {
        actor[index] &= ~mask;
    }
}

s32 Menu_GetTrackSplineStorageSize(void *object) {
    struct IntPair *first = SetN64_GetPackSection(object, 0);
    struct IntPair *second = SetN64_GetPackSection(object, 2);
    s32 size = first->second * 36;

    return size + second->second * 36 + 48;
}





/* Looks up the cinema sequence's second resource through SetN64_GetPackSection
   with zero, then looks up the result again with the argument, and returns that. */
s32 Menu_GetCinemaSequenceCount(void) {
    return *g_trackResourceDirectory - 1;
}

int Menu_RequestTrackBundle(void) {
    int size;
    void *res;
    Shared_World *menu = &g_world;

    res = SetN64_LocatePackSection((int)menu->trackBundle, menu->trackLookup, 0, &size);
    if (res == 0) {
        return 0;
    }
    return Cache_RequestResource(0, res, res, size, 51, 0, 0, g_cinemaDirectoryText, 1);
}

f32 Menu_BlendCubic(f32 from, f32 to, f32 t) {
    f32 u = k_MenuBlendUnitConstants[0] - t;

    return from * (u * u * u - u) + to * (t * t * t - t);
}

f32 Menu_BlendLinear(f32 from, f32 to, f32 weight) {
    return from * (k_MenuBlendUnitConstants[1] - weight) + to * weight;
}

void *Menu_GetPackEntry(s32 key) {
    return SetN64_GetPackSection(SetN64_GetPackSection(g_cinemaSequenceState->resource, 0), key);
}

s32 Menu_GetTrackEyeHoldFlag(s32 key) {
    return ((s32 *) SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(g_cinemaSequenceState->resource, 0), key), 2))[0];
}

s32 Menu_GetTrackTargetHoldFlag(s32 key) {
    return ((s32 *) SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(g_cinemaSequenceState->resource, 0), key), 2))[1];
}

void *Menu_GetTrackTargetClip(s32 key) {
    return SetN64_GetPackSection(SetN64_GetPackSection(SetN64_GetPackSection(g_cinemaSequenceState->resource, 0), key), 1);
}

void CTrackResource_AccessResourceSection(void) {
    SetN64_GetPackSection(g_cinemaSequenceState->resource, 3);
}

/* Returns whether a directory entry's subtype is the one its kind requires: 5 for kind 1, 4 for
   kind 9 and 3 for kind 10; other kinds give 0. */
int Menu_IsTrackRequestItem(PakDirectoryEntryKindView *rec) {
    int result = 0;

    switch (rec->kind) {
    case 1:
        if (rec->subtype == 5) {
            result = 1;
        }
        break;
    case 9:
        if (rec->subtype == 4) {
            result = 1;
        }
        break;
    case 10:
        if (rec->subtype == 3) {
            result = 1;
        }
        break;
    default:
        result = 0;
        break;
    }
    return result;
}

/* Retained data for this translation unit. */

const float k_TrackDrawtrackoverlayEncodedWords[12] = {
    30.0f, 0.0f, 2147483648.0f, 1.0f, 255.0f, 2147483648.0f, 255.0f, 2147483648.0f, 255.0f,
    2147483648.0f, 255.0f, 2147483648.0f,
};

const float k_menuGetTrackStartTargetScale[1] = {
    10.0f,
};

const float k_menuGetTrackStartTargetUnit[1] = {
    1.0f,
};
