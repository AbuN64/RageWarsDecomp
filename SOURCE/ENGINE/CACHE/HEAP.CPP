#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/ENTRYRECAT18V3.H"
#include "COMMON/S1.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/STATERECAT34.H"
#include "ENGINE/CACHE/HEAP.H"
#include <ultra64.h>

/* HEAP.CPP */
s32 Heap_AllocateAtAddress(s8 *arena, void *requestedAddress, s32 requestedBytes) {
    s32 alignedBlockBytes;
    s32 leadingFreeBytes;
    u32 followingFreeAddress;
    u32 unlinkSuccessorAddress;
    u32 candidateNextAddress;
    u32 replacementTailAddress;
    void *nextPhysicalBlock;
    void *previousFreeBlock;
    void *allocationEnd;
    void *freeSpanEnd;
    void *freeSpanStart;
    void *firstFreeBlock;
    void *allocationHeader;
    void *containingBlock;
    alignedBlockBytes = (requestedBytes + 47) & ~0xF;
    firstFreeBlock = ((struct HeapFirstFreeBlockView *)(arena))->value;
    if (firstFreeBlock != NULL) {
        containingBlock = firstFreeBlock;
        while (((struct HeapNextBlockAddressView *)(containingBlock))->value != 0) {
            candidateNextAddress = ((struct HeapNextBlockAddressView *)(containingBlock))->value;
            if (candidateNextAddress >= (u32) requestedAddress) {
                break;
            }
            containingBlock = (void *) candidateNextAddress;
        }
        freeSpanStart = containingBlock + ((struct RegionAllocatedBlockSizeView *)(containingBlock))->value;
        freeSpanEnd = freeSpanStart + ((struct RegionFreeBlockSizeView *)(containingBlock))->value;
        allocationHeader = requestedAddress - sizeof(HeapArenaBlock);
        allocationEnd = allocationHeader + alignedBlockBytes;
        if ((u32) allocationHeader >= (u32) freeSpanStart) {
            if ((u32) freeSpanEnd >= (u32) allocationEnd) {
                s32 trailingFreeBytes = freeSpanEnd - allocationEnd;
                ((struct RegionAllocatedBlockSizeView *)(allocationHeader))->value = alignedBlockBytes;
                ((struct RegionFreeBlockSizeView *)(allocationHeader))->value = trailingFreeBytes;
                if (trailingFreeBytes != 0) {
                    ((struct HeapAllocationOwnerHeader *)(requestedAddress))[-1].value = containingBlock;
                    followingFreeAddress = ((struct HeapNextBlockAddressView *)(containingBlock))->value;
                    ((struct HeapNextBlockAddressView *)(allocationHeader))->value = followingFreeAddress;
                    if (((struct HeapNextBlockAddressView *)(containingBlock))->value != 0) {
                        *(void **) followingFreeAddress = allocationHeader;
                    }
                    ((struct HeapNextBlockAddressView *)(containingBlock))->value = (u32) allocationHeader;
                    if (((struct HeapLastFreeBlockView *)(arena))->value == containingBlock) {
                        ((struct HeapLastFreeBlockView *)(arena))->value = allocationHeader;
                    }
                } else {
                    ((struct HeapAllocationOwnerHeader *)(requestedAddress))[-1].value = NULL;
                    ((struct HeapNextBlockAddressView *)(allocationHeader))->value = 0U;
                }
                leadingFreeBytes = allocationHeader - (containingBlock + ((struct RegionAllocatedBlockSizeView *)(containingBlock))->value);
                ((struct RegionFreeBlockSizeView *)(containingBlock))->value = leadingFreeBytes;
                if (leadingFreeBytes == 0) {
                    previousFreeBlock = ((struct HeapPreviousFreeLinkView *)(containingBlock))->value;
                    if (previousFreeBlock != NULL) {
                        ((struct HeapNextBlockAddressView *)(previousFreeBlock))->value = ((struct HeapNextBlockAddressView *)(containingBlock))->value;
                    }
                    unlinkSuccessorAddress = ((struct HeapNextBlockAddressView *)(containingBlock))->value;
                    if (unlinkSuccessorAddress != 0) {
                        *(void **) unlinkSuccessorAddress = ((struct HeapPreviousFreeLinkView *)(containingBlock))->value;
                    }
                    if (((struct HeapFirstFreeBlockView *)(arena))->value == containingBlock) {
                        ((struct HeapFirstFreeBlockView *)(arena))->value = ((struct HeapNextFreeLinkView *)(containingBlock))->value;
                    }
                    if (((struct HeapLastFreeBlockView *)(arena))->value == containingBlock) {
                        replacementTailAddress = ((struct HeapNextBlockAddressView *)(containingBlock))->value;
                        if (replacementTailAddress == 0) {
                            replacementTailAddress = (u32) ((struct HeapPreviousFreeLinkView *)(containingBlock))->value;
                        }
                        ((struct HeapLastFreeBlockView *)(arena))->value = (void *) replacementTailAddress;
                    }
                    ((struct HeapPreviousFreeLinkView *)(containingBlock))->value = NULL;
                    ((struct HeapNextBlockAddressView *)(containingBlock))->value = 0U;
                }
                ((struct HeapFirstFreeBlockView *)(allocationHeader))->value = containingBlock;
                nextPhysicalBlock = ((struct HeapLastFreeBlockView *)(containingBlock))->value;
                ((struct HeapLastFreeBlockView *)(allocationHeader))->value = nextPhysicalBlock;
                if (((struct HeapLastFreeBlockView *)(containingBlock))->value != NULL) {
                    ((struct HeapFirstFreeBlockView *)(nextPhysicalBlock))->value = allocationHeader;
                }
                ((struct HeapLastFreeBlockView *)(containingBlock))->value = allocationHeader;
                return (s32) requestedAddress;
            }
        }
    }
    return 0;
}

/* Coalesces every block that physically follows a pool's anchor block at 0x10 into its physical
   predecessor: first puts an empty predecessor on the free list (after the next non-empty block, or
   at the head), then grows it by the block's header and size, unlinks the block from the physical
   chain and, when it was free, from the free list. Written like Heap_FreeAllocation, which absorbs one block. */

void Heap_CoalesceEmptyPhysicalBlocks(HeapArena_Heap *arena)
{
    HeapArenaBlock *block;
    HeapArenaBlock *header;
    HeapArenaBlock *other;
    HeapArenaBlock *scan;
    HeapArenaBlock *next;

    while (arena->anchor->next_phys != 0) {
        header = arena->anchor->next_phys;
        block = header->prev_phys;
        if (block->size == 0) {
            other = header->prev;
            if (other != 0) {
                block->prev = other;
            } else {
                scan = block;
                while (scan != 0) {
                    if (scan->size != 0) {
                        break;
                    }
                    scan = scan->prev_phys;
                }
                if (scan != 0) {
                    block->prev = scan;
                } else {
                    goto insert_head;
                }
                other = scan;
            }
            next = other->next;
            block->next = next;
            if (other->next != 0) {
                next->prev = block;
            }
            other->next = block;
            if (arena->tail == other) {
                arena->tail = block;
            }
            goto merge;
insert_head:
            block->next = arena->head;
            if (arena->head != 0) {
                arena->head->prev = block;
            } else {
                arena->tail = block;
            }
            arena->head = block;
        }

merge:
        block->size += header->offset + header->size;
        if (header->next_phys != 0) {
            header->next_phys->prev_phys = header->prev_phys;
        }
        header->prev_phys->next_phys = header->next_phys;

        if (header->size != 0) {
            if (header->prev != 0) {
                header->prev->next = header->next;
            }
            if (header->next != 0) {
                header->next->prev = header->prev;
            }
            if (arena->tail == header) {
                arena->tail = header->prev;
            }
        }
    }
}

/* Initialises a heap over a memory range: records its start and unrounded end, places one free block at the
   first 16-byte boundary covering the rest rounded down to 16 bytes, less a 0x20-byte header, and
   points the free list at that block when it has room. */

void Heap_InitializeArena(struct Heap *heap, char *start, s32 size) {
    struct HeapAllocationBlock *block;

    heap->start = start;
    heap->end = start + size;
    block = (struct HeapAllocationBlock *) (((u32) start + 15) & ~15);
    size -= (char *) block - start;
    size &= ~15;
    block->nextFree = 0;
    block->prevFree = 0;
    block->next = 0;
    block->prev = 0;
    block->size = 32;
    block->free = size - 32;
    heap->first = block;
    if (block->free != 0) {
        heap->last = block;
        heap->free = block;
    } else {
        heap->last = 0;
        heap->free = 0;
    }
}

/* Allocates from a heap with a first-fit search of its free list: the request plus the 0x20-byte header is
 * rounded up to 16 bytes, a block after the found block's used part takes that size and inherits the
 * remaining free space in the free list (replacing the found block), the found block leaves the free list,
 * the new block is linked after it in address order, and its data pointer is returned (0 when nothing
 * fits). */

void *Heap_AllocateFromFront(HeapFreeBlockList *heap, s32 request) {
    HeapAllocationBlock *block;
    HeapAllocationBlock *split;
    u32 size;

    size = (request + 47) & ~0xF;
    for (block = heap->head; block != 0; block = block->nextFree) {
        if (block->free >= size) {
            { u8 *cursor = (u8 *)block; cursor += block->size; split = (HeapAllocationBlock *)cursor; }
            split->size = size;
            split->free = block->free - size;
            if (split->free != 0) {
                split->prevFree = block;
                split->nextFree = block->nextFree;
                if (block->nextFree != 0) {
                    split->nextFree->prevFree = split;
                }
                block->nextFree = split;
                if (heap->tail == block) {
                    heap->tail = split;
                }
            } else {
                split->prevFree = 0;
                split->nextFree = 0;
            }
            block->free = 0;
            if (block->prevFree != 0) {
                block->prevFree->nextFree = block->nextFree;
            }
            if (block->nextFree != 0) {
                block->nextFree->prevFree = block->prevFree;
            }
            if (heap->head == block) {
                heap->head = block->nextFree;
            }
            if (heap->tail == block) {
                heap->tail = block->nextFree != 0 ? block->nextFree : block->prevFree;
            }
            block->prevFree = 0;
            block->nextFree = 0;
            split->prev = block;
            split->next = block->next;
            if (block->next != 0) {
                split->next->prev = split;
            }
            block->next = split;
            return split->data;
        }
    }
    return 0;
}

/* Allocates from the top of a heap's free space with a first-fit search of its free list: the request plus the 0x20-byte header is rounded up to 16 bytes and carved from the end of the found block's free space; the found block leaves the free list once its free space is used up, the new block is linked after it in address order, and its data pointer is returned (0 when nothing fits). */

void *Heap_AllocateFromBack(HeapFreeBlockList *heap, s32 request)
{
    HeapAllocationBlock *block;
    HeapAllocationBlock *split;
    u32 size;

    size = (request + 47) & ~0xF;
    for (block = heap->tail; block != 0; block = block->prevFree) {
        if (block->free >= size) {
            { u8 *cursor = (u8 *)block; cursor += block->size; cursor += block->free; cursor -= size; split = (HeapAllocationBlock *)cursor; }
            split->size = size;
            split->free = 0;
            block->free -= size;
            split->nextFree = 0;
            split->prevFree = 0;
            if (block->free == 0) {
                if (block->prevFree != 0) {
                    block->prevFree->nextFree = block->nextFree;
                }
                if (block->nextFree != 0) {
                    block->nextFree->prevFree = block->prevFree;
                }
                if (heap->head == block) {
                    heap->head = block->nextFree;
                }
                if (heap->tail == block) {
                    heap->tail = block->nextFree != 0 ? block->nextFree : block->prevFree;
                }
                block->prevFree = 0;
                block->nextFree = 0;
            }
            split->prev = block;
            split->next = block->next;
            if (block->next != 0) {
                split->next->prev = split;
            }
            block->next = split;
            return split->data;
        }
    }
    return 0;
}

s32 Heap_FreeAllocation(HeapArena_Entryrecat18v3 *arena, char *dataToFree) {
    HeapArenaBlock *block;
    HeapArenaBlock *header;
    HeapArenaBlock *other;
    HeapArenaBlock *scan;
    u32 next;

    header = (HeapArenaBlock *)(dataToFree - sizeof(HeapArenaBlock));
    block = header->prev_phys;
    if (block->size == 0) {
        other = header->prev;
        if (other != 0) {
            block->prev = other;
        } else {
            scan = block;
            while (scan != 0) {
                if (scan->size != 0) {
                    break;
                }
                scan = scan->prev_phys;
            }
            if (scan != 0) {
                block->prev = scan;
            } else {
                goto insert_head;
            }
            other = scan;
        }
        next = (u32)other->next;
        block->next = (HeapArenaBlock *)next;
        if (other->next != 0) {
            *(HeapArenaBlock **)next = block;
        }
        other->next = block;
        if (arena->tail == other) {
            arena->tail = block;
        }
        goto merge;
insert_head:
        block->next = arena->head;
        if (arena->head != 0) {
            arena->head->prev = block;
        } else {
            arena->tail = block;
        }
        arena->head = block;
    }

merge:
    block->size += header->offset + header->size;
    if (header->next_phys != 0) {
        header->next_phys->prev_phys = header->prev_phys;
    }
    header->prev_phys->next_phys = header->next_phys;

    if (header->size != 0) {
        if (header->prev != 0) {
            header->prev->next = header->next;
        }
        if (header->next != 0) {
            header->next->prev = header->prev;
        }
        if (arena->tail == header) {
            arena->tail = header->prev;
        }
    }
    return block->size - 32;
}

void Heap_GetFreeByteCounts(HeapArena_Entryrecat18v3 *arena, s32 *totalBytesOut, u32 *largestBlockBytesOut) {
    u32 previousLargestBytes;
    u32 largestBytes;
    void *freeBlockCursor;

    *totalBytesOut = 0;
    *largestBlockBytesOut = 0;
    freeBlockCursor = arena->head;
    if (freeBlockCursor != 0) {
        do {
            *totalBytesOut += (u32)((HeapArenaBlock *)freeBlockCursor)->size;
            largestBytes = (u32)((HeapArenaBlock *)freeBlockCursor)->size;
            previousLargestBytes = *largestBlockBytesOut;
            if (largestBytes < previousLargestBytes) {
                largestBytes = previousLargestBytes;
            }
            *largestBlockBytesOut = largestBytes;
            freeBlockCursor = ((HeapArenaBlock *)freeBlockCursor)->next;
        } while (freeBlockCursor != 0);
    }
}
