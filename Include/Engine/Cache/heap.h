#ifndef ENGINE_CACHE_HEAP_H
#define ENGINE_CACHE_HEAP_H
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/heap_arena.h"
#include "Common/heap_arena_entry.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "Common/music_track_volume.h"
#include "Common/measured_storage.h"

struct HeapArena_Heap;
struct HeapArena_Heap {
    s32 reservedWord0;
    s32 reservedWord4;
    struct HeapArenaBlock *head;
    struct HeapArenaBlock *tail;
    struct HeapArenaBlock *anchor;
};
/* A first-fit heap: its byte range, the free-block list (head and tail) and the address-ordered list of all
   blocks; g_runtimeHeap is the game's main heap. */
struct Heap {
    char *start;
    char *end;
    struct HeapAllocationBlock *free;
    struct HeapAllocationBlock *last;
    struct HeapAllocationBlock *first;
};
struct HeapFreeBlockList {
    char pad0[8];
    struct HeapAllocationBlock *head;
    struct HeapAllocationBlock *tail;
};
extern void Heap_CoalesceEmptyPhysicalBlocks(struct HeapArena_Heap *arena);
extern void Heap_GetFreeByteCounts(struct HeapArena_Entryrecat18v3 *arena, s32 *totalBytesOut, u32 *largestBlockBytesOut);
struct HeapFreeBlockList;
void *Heap_AllocateFromBack(struct HeapFreeBlockList *heap, s32 request);
void *Heap_AllocateFromFront(struct HeapFreeBlockList *heap, s32 request);
struct Heap;
void Heap_InitializeArena(struct Heap *heap, char *start, s32 size);
extern s32 Heap_FreeAllocation(struct HeapArena_Entryrecat18v3 *arena, char *dataToFree);
#endif
