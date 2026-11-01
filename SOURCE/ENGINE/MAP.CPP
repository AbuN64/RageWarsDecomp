#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "ENGINE/MAP.H"
#include "COMMON/ENTRYRECAT18V3.H"
#include "COMMON/S1.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/STATERECAT34.H"
#include "COMMON/LISTHEADER.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"

/* MAP.CPP */
void Map_ResetFramePool(void *batch) {
    s32 *p = (s32 *)batch;
    p[2] = p[1];
    p[3] = p[0] + ((p[1] * g_lightingBufferIndex) << 6);
}

s32 Map_ReserveEntries(void *map, s32 entryCount) {
    s32 firstReservedEntry;
    firstReservedEntry = 0;
    if ((((struct MapBlockAllocatorView *) ((s8 *) map))->remainingBlocks) >= entryCount) {
        firstReservedEntry = (((struct MapBlockAllocatorView *) ((s8 *) map))->nextBlockAddress);
        (((struct MapBlockAllocatorView *) ((s8 *) map))->nextBlockAddress) = (s32) (firstReservedEntry + (entryCount << 6));
        (((struct MapBlockAllocatorView *) ((s8 *) map))->remainingBlocks) = (s32) ((((struct MapBlockAllocatorView *) ((s8 *) map))->remainingBlocks) - entryCount);
    }
    return firstReservedEntry;
}
