#include "COMMON/WORLD.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "include_asm.h"
#include "COMMON/ENTRYRECAT0V3.H"
#include "MENU/PAK_DIRECTORY_VIEWS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHARED_OPTIONSSCREEN.H"
#include "TYPES.H"
#include "MENU/PAK/MENU_ISTRACKREQUESTITEM.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

/* Returns one less than the word g_trackResourceDirectory points to. */

/* Looks up the current menu resource through SetN64_LocatePackSection from the fields at 0x74 and 0x34 of
   g_world_AchieveUpdateresultsscreen and, when found, opens it through Cache_RequestResource as widget 0x33 with the handler table
   g_cinemaDirectoryText; returns the result, or 0 when there is no resource. Matched through a local pointer to the menu. */


extern const char g_cinemaDirectoryText[];

extern void *SetN64_LocatePackSection(int, int, int, int *);


/* Blends two values with cubic weights: with u the pooled constant k_MenuBlendUnitConstants[0] less t, from is
   weighted by u cubed less u and to by t cubed less t. The constant lives in a shared literal
   pool outside this object, so it is read by name. */

/* Looks up the object at offset 4 of the structure g_cinemaSequenceState points to through SetN64_GetPackSection
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

/* Returns whether a record's subtype at 0x12 is the one its kind at 0x11 requires: 5 for kind 1, 4 for
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

