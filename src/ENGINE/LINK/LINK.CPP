#include "include_asm.h"
#include "GAMECORE/EXTERNS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/LIGHT_VOLUME_AND_TRIGGER_VIEWS.H"
#include "ENGINE/LINK.H"
#include "COMMON/EFFECTCONTRIBUTION.H"
#include "TYPES.H"
#include "COMMON/MATH_HELPERS.H"
#include "COMMON/WORLD.H"
#include "COMMON/SHAREDPLAYER.H"
#include "ENGINE/LINK.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

extern s32 g_gameFrameCounter;



f32 Link_GetLightAnimationOffset(void *link)
{
  SceneLightVolume *volume = link;
  u32 animationSeedValue;
  s32 idx;
  animationSeedValue = volume->animationSeed;
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
   Adapted from alEvtqNew with the loop over the global entry table and the accumulated return changed. */






/* Adds packed per-axis byte offsets to each entry of a vertex list. */







s32 Link_SumWorldSectionCounts(void) {
    s32 total = 0;
    s32 i;
    char *base = (char *)&g_world;

    for (i = 0; i < ((WorldSectionCountView *)(base))->sectorCount; i++) {
        total += ((struct ActorAnimationEventTable *)SetN64_GetPackSection(*((struct WorldSectionResourceView *) (base + (i * sizeof(((Shared_World *)0)->sectors[0]))))->resource, 2))->entryCount;
    }
    return total;
}

void Link_ApplyPackedVertexDeltas(s32 table, s32 count, CVector3 *vtx) {
    Table *t;
    s32 zero;
    s32 i;
    char *base = (char *)&g_world;
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
