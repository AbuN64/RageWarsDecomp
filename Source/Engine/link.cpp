#include "Engine/cache.h"
#include "Engine/Instance/gobjinst.h"
#include "include_asm.h"
#include "Gamecore/externs.h"
#include "Common/runtime_declarations.h"
#include "Engine/link.h"
#include "Common/effectcontribution.h"
#include "types.h"
#include "Common/math_helpers.h"
#include "Common/world.h"
#include "Common/sharedplayer.h"
#include "Render/setn64_getpacksection.h"
#include "Actors/vertex_light_and_actor_views.h"
#include "Common/vector4f.h"
#include "Common/level_actor.h"
#include "Common/listheader.h"
#include "Common/trigger_and_float_value_operations.h"
#include "System/sound_context_music_and_voice_control.h"
#include "Common/navigation_node_and_route_views.h"
#include "Common/Lone/g_languageindex.h"
#include "Common/gameplay_sound_table.h"
#include "Render/soundelement_playflatsound.h"
#include "Engine/Audio/T2SoundElement.h"
#include "Engine/geometry.h"
#include "Common/triple.h"
#include "Common/menu_match_globals.h"
#include "Actionai/action_updatebreakableproximity.h"
#include "Animpool/animpool_spawndescribedsceneeffect.h"
#include "Cbarrel/barrel_spawnflaggedeffects.h"
#include "Gsky/sky_posttargetedscreenmessage.h"
#include "Link/link_dispatchmatchingtriggers.h"
#include "Menu/Items/Scene/scene_findactortriggerrange.h"
#include "Menu/Items/Scene/scene_registeractorinscenelists.h"
#include "Menu/Items/Scene/scene_setlevelactorstatebit.h"
#include "Track/track_drawtrackoverlay.h"
#include "Common/track_requesttrackbykey.h"
#include "Render/timed_session_transitions.h"
#include "Engine/scene.h"
#include "Data/rest_source_records.h"
#include "libultra/ACTOR_STATE_TABLE_END_DATA.H"
#include "Engine/particle.h"
#include "Engine/lighting.h"

/* LINK.CPP */

f32 Link_GetLightAnimationOffset(SceneLightVolume *link)
{
  u32 animationSeedValue;
  s32 idx;
  animationSeedValue = link->animationSeed;
  idx = g_gameFrameCounter + ((((animationSeedValue % 7) & 0xFF) + 1) * 16);
  idx = idx % 90;
  return (f32) g_lightAnimationOffsetTable[idx];
}

void Link_AnimateVertexColors(VertexColorMeshView *object, u8 *colors) {
    s32 state;
    s32 i;
    Vtx *record;
    Vtx *end;

    state = g_gameFrameCounter;
    i = 0;
    if (!(state & 1)) {
        record = (void *)object->records;
        end = record + object->count;
        if (record != end) {
            do {
                u16 flags = (u16)record->v.flag;
                s32 amount;
                s32 value;
                u8 *color;

                if (flags & 0x70) {
                    amount = g_lightAnimationOffsetTable[(state + ((flags & 0x70) >> 2)) & 0x3F];
                    amount >>= (flags & 0xC) >> 2;
                    color = colors + i * 4;

                    value = amount + color[0];
                    if (value >= 256) value = 0xFF;
                    if (value < 0) value = 0;
                    record->v.cn[0] = value;

                    value = amount + color[1];
                    if (value >= 256) value = 0xFF;
                    if (value < 0) value = 0;
                    record->v.cn[1] = value;

                    value = amount + color[2];
                    if (value >= 256) value = 0xFF;
                    if (value < 0) value = 0;
                    record->v.cn[2] = value;
                }
                record++;
                i++;
            } while (record != end);
        }
    }
}

/* Saves each vertex's base colour for the colour pulse (Link_AnimateVertexColors): copies the r, g, b of every
   vertex of the object into colors (4 bytes per vertex), clamped to 30..225. */
void Link_CaptureVertexColors(VertexColorMeshView *object, u8 *colors) {
    s32 i, count;
    Vtx *records;
    Vtx *record;
    u8 *color;
    u8 t;

    i = 0;
    count = object->count;
    records = (void *)object->records;
    if (count > 0) {
        do {
            record = &records[i];
            color = colors;
            colors += 4;
            t = RW_MAX_GT(RW_MIN_LT(record->v.cn[0], 225), 30);
            color[0] = t;
            t = RW_MAX_GT(RW_MIN_LT(record->v.cn[1], 225), 30);
            color[1] = t;
            t = RW_MAX_GT(RW_MIN_LT(record->v.cn[2], 225), 30);
            color[2] = t;
            i++;
        } while (i < count);
    }
}

/* Sums the size field of the record SetN64_GetPackSection returns for each entry of the g_world_AchieveUpdateresultsscreen table and returns the total.
 */

/* Adds packed per-axis byte offsets to each entry of a vertex list. */

s32 Link_SumWorldSectionCounts(void) {
    s32 total = 0;
    s32 i;

    for (i = 0; i < g_world.sectorEntryCount; i++) {
        total += ((struct ActorAnimationEventTable *)SetN64_GetPackSection(g_world.sectors[i].resource->data, 2))->entryCount;
    }
    return total;
}

void Link_ApplyPackedVertexDeltas(s32 table, s32 count, CVector3 *vtx) {
    Table *t;
    s32 zero;
    s32 i;
    s32 *d;
    s32 w;
    s32 dx;
    s32 dy;
    s32 dz;

    t = SetN64_GetPackSection(table, 1);
    if (t->count != 0) {
        zero = 0;
        i = zero;
        d = t->deltas;
        if (count > zero) {
            do {
                w = d[i];
                dx = ((w & 0xFF0000) << 8) >> 23;
                dy = ((w << 16) >> 24) * 2;
                dz = (w << 24) >> 23;
                vtx[i].x += (f32)dx;
                vtx[i].y += (f32)dy;
                vtx[i].z += (f32)dz;
                i++;
            } while (i < count);
        }
    }
}

const float g_linkDispatchmatchingtriggers[1] = {
    4.0f,
};

#if defined(VERSION_DE)
float g_linkTriggerScaleTriple[3] = {
    1.0f, 1.0f, 7.0f,
};
#endif

/* CONTROL_THREAD_LABELS_EUROPEAN_X.CPP */
#if defined(VERSION_US)

char g_controlThreadLabelsEuropeanXBytes[12] = "wport_tR";
#endif

/* G_ENGINELINKUNITSCALEFLOATS.CPP */

#if defined(VERSION_US_REV1)
extern float g_engineLinkUnitScaleFloats[3];
#endif

/* G_MINIGUNTEXT.CPP */

#if defined(VERSION_US_REV1)

extern s32 g_GMiniguntextWords[1];

extern u16 g_colorJitterSignedBytePairs[46];
#endif
