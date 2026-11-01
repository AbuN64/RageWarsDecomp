#ifndef ENGINE_CACHE_HEAP_H
#define ENGINE_CACHE_HEAP_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/ENTRYRECAT18V3.H"
#include "COMMON/S1.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/STATERECAT34.H"
#include "COMMON/MEASURED_STORAGE.H"

/* Measured 4-byte access at 8; storage view, complete object unknown. */
struct HeapFirstFreeBlockView { unsigned char padding[8]; void * value; };

/* Measured 4-byte access at 4; storage view, complete object unknown. */
struct HeapNextBlockAddressView { unsigned char padding[4]; u32 value; };

/* Measured 4-byte access at -0x20; storage view, complete object unknown. */
struct HeapAllocationOwnerHeader { void * value; unsigned char trailing[28]; };

/* Measured 4-byte access at 0xC; storage view, complete object unknown. */
struct HeapLastFreeBlockView { unsigned char padding[12]; void * value; };

/* Measured 4-byte access at 0; storage view, complete object unknown. */
struct HeapPreviousFreeLinkView { void * value; };

/* Measured 4-byte access at 4; storage view, complete object unknown. */
struct HeapNextFreeLinkView { unsigned char padding[4]; void * value; };

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
extern void Heap_CoalesceEmptyPhysicalBlocks(HeapArena_Heap *arena);
extern void Heap_GetFreeByteCounts(struct HeapArena_Entryrecat18v3 *arena, s32 *totalBytesOut, u32 *largestBlockBytesOut);
#endif
