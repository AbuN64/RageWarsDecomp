#include "include_asm.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Ui/Tsmos/Screens/pakinterfacescreen.h"
#include "Engine/map.h"
#include "Common/heap_arena.h"
#include "Common/heap_arena_entry.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "Common/music_track_volume.h"
#include "Common/listheader.h"
#include "Common/weapon_marker_and_profile_views.h"

/* MAP.CPP */

void Map_ResetFramePool(void *batch) {
    s32 *p = (s32 *)batch;
    p[2] = p[1];
    p[3] = p[0] + ((p[1] * g_lightingBufferIndex) << 6);
}

s32 Map_ReserveEntries(struct MapBlockAllocatorView *map, s32 entryCount) {
    s32 firstReservedEntry;
    firstReservedEntry = 0;
    if ((((struct MapBlockAllocatorView *) ((s8 *) map))->remainingBlocks) >= entryCount) {
        firstReservedEntry = (((struct MapBlockAllocatorView *) ((s8 *) map))->nextBlockAddress);
        (((struct MapBlockAllocatorView *) ((s8 *) map))->nextBlockAddress) = (s32) (firstReservedEntry + (entryCount << 6));
        (((struct MapBlockAllocatorView *) ((s8 *) map))->remainingBlocks) = (s32) ((((struct MapBlockAllocatorView *) ((s8 *) map))->remainingBlocks) - entryCount);
    }
    return firstReservedEntry;
}
