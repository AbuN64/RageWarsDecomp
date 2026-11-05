#ifndef ENGINE_MAP_H
#define ENGINE_MAP_H
#include "types.h"
#include "Batch/batch.h"
/* Batch_InitEntryBatch supplies the entries and half-count; Map_ResetFramePool
 * resets the remaining count and selects a frame's 0x40-byte entry range.
 * g_actorMatrixPool is this 0x10-byte object at g_world + 0x128. */
struct MapBlockAllocatorView {
    s32 *entries;
    s32 blocksPerFrame;
    s32 remainingBlocks;
    s32 nextBlockAddress;
};
extern s32 Map_ReserveEntries(struct MapBlockAllocatorView *map, s32 entryCount);
#endif
