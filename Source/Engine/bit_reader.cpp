#include "Common/world.h"
#include "Common/Lone/screen_image_resources_enabled.h"
#include "Common/Lone/g_defaultcamerasurfacetype.h"
#include "Common/sharedplayer.h"
#include "Common/animation_pool.h"
#include "Common/version_calls.h"
#include "types.h"
#include "Scene/cache_requestresource.h"
#include "Scene/cache_allocateresourceat.h"
#include "Engine/Cache/list.h"
#include "Render/setn64_getpacksection.h"
#include "Engine/scene_drawopaqueactors.h"
#include "Engine/scene_drawtransitioncoloroverlay.h"
#include "Engine/session.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "common.h"
#include "Engine/scene.h"
#include "Engine/Instance/gobjinst.h"
#include "Common/heap_arena_entry.h"
#include "Animpool/animpool_spawndescribedsceneeffect.h"
#include "Common/runtime_declarations.h"
#include "Common/vector4f.h"
#include "Animpool/animpool_readsignedbits.h"
#include "include_asm.h"
#include "Data/rest_source_records.h"

/* ANIMPOOL_READSIGNEDBITS.CPP */

/* Two-word value setter; live Barrel_FillWordPair uses the same word-array representation. */
void AnimPool_InitializeBitReader(s32 *value, s32 word) {
    value[0] = word;
    value[1] = 0;
}

s32 CBitReader_ReadBits(BitReader *reader, s32 bitCount);

s32 AnimPool_ReadSignedBits(BitReader *reader, s32 bitCount) {
    s32 signedValue;
    s32 i;
    s32 mask;

    signedValue = CBitReader_ReadBits(reader, bitCount);
    mask = 1 << (bitCount - 1);
    if (signedValue & mask) {
        i = bitCount;
        if (bitCount < 32) {
            do {
                signedValue |= 1 << i;
                i += 1;
            } while (i < 32);
        }
    }
    return signedValue;
}

/** Reads bitCount bits (LSB first) from the bitstream at reader, advancing its bit position. */
s32 CBitReader_ReadBits(BitReader *reader, s32 bitCount) {
    s32 bitPos;
    s32 i;
    s32 result;

    i = 0;
    result = 0;
    if (bitCount > 0) {
        do {
            bitPos = reader->bitPos;
            result |= (((s32) *(reader->data + (bitPos >> 3)) >> (bitPos & 7)) & 1) << i;
            i += 1;
            reader->bitPos = (s32) (bitPos + 1);
        } while (i < bitCount);
    }
    return result;
}
