#include "../../../../sdk/include/thread_queue.h"
#include "include_asm.h"
#include "COMMON/MANAGER.H"
#include "SCENE/RESOURCE_BINDING_AND_FADE_VIEWS.H"
#include "COMMON/EFFECTRENDER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"
#include "COMMON/S1.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "TYPES.H"
#include "ENGINE/CACHE/CACHE.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "ENGINE/CACHE/LIST.H"
#include "ENGINE/CACHE/LIST.H"
#include "COMMON/ENTRYRECAT18V3.H"
#include "UI/X_FILES/X_PLUS.H"

/* One declaration per symbol for the whole unit; the functions below used to redeclare them locally with
 * conflicting types, which only the MIPS compiler accepted. */
extern struct MemoryUsageStats g_resourceCacheFrameStamp;
extern OSMesgQueue g_resourceHeapLockQueue;
extern CMemEntry **g_resourceFreeNodeStack;
extern s32 Heap_FreeAllocation(void *, s32);
extern s32 g_runtimeHeap[3];
extern char g_resourceRecencyList;
extern CMemEntry *g_resourceAllocationCandidate;
#include "COMMON/OS_TIMER_INTERRUPT_INTERNALS.H"

#include "COMMON/ENTRYRECAT18V3.H"
/* The resource manager record at g_resourceCacheManager: node array, free-slot stack, link records, lists and its lock queue.
 * count (0xBDC) and stamp (0xC20) are the Pool fields used by Cache_AcquirePendingResourceEntry. */
extern s32 Heap_AllocateFromFront(void *, s32);
extern s32 Mutex_InitializeQueueLock(OSMesgQueue *);
extern u32 Defs_GetMemorySize(void);

extern void HashTable_InitializeResourceTable(s32);
extern s32 g_Cache_RunResourceCompletionWorkerPackedAddress24;
extern s32 g_resourceCompletionWorkerPriority;
extern s32 g_resourceCompletionWorkerStack;
extern int g_resourceCacheNodeCapacity;
extern Manager g_resourceRequestManager;
extern struct ResMgr g_resourceCacheManager;

void Cache_InitializeResourceCache(s32 unused, s32 count) {
    u32 mask;
    u32 unlockMask;
    u32 i;
    void *thread;
    Mutex_InitializeQueueLock(&g_resourceHeapLockQueue);
    mask = __osDisableInt();
    g_resourceHeapLockUsers += 1;
    if (g_resourceHeapLockUsers != 1) {
        __osRestoreInt(mask);
        osRecvMesg(&g_resourceHeapLockQueue, 0, 1);
    } else {
        __osRestoreInt(mask);
    }
    g_resourceCacheNodeCapacity = 1024;
    if (Defs_GetMemorySize() > 0x400000) {
        g_resourceCacheNodeCapacity *= 2;
    }
    g_resourceCacheManager.nodes = (struct CMemEntry *)Heap_AllocateFromFront(&g_runtimeHeap, g_resourceCacheNodeCapacity * sizeof(struct CMemEntry));
    g_resourceCacheManager.slots = (struct CMemEntry **)Heap_AllocateFromFront(&g_runtimeHeap, g_resourceCacheNodeCapacity * sizeof(void *));
    g_resourceCacheManager.links = (struct ResLink *)Heap_AllocateFromFront(&g_runtimeHeap, g_resourceCacheNodeCapacity * 44);
    osCreateMesgQueue(&g_resourceCacheManager.lock, g_resourceCacheManager.lockSlot, 1);
    g_resourceCacheManager.reservedWord44 = 0;
    g_resourceCacheManager.reservedWord40 = 0;
    List_InitializeIntrusive(&g_resourceCacheManager.entries, 24, 28);
    List_InitializeIntrusive(&g_resourceCacheManager.recent, 32, 36);
    g_resourceCacheManager.count = 0;
    for (i = 0; i < g_resourceCacheNodeCapacity; i++) {
        struct CMemEntry *node = &g_resourceCacheManager.nodes[i];
        node->flags = 0;
        g_resourceCacheManager.slots[i] = node;
        g_resourceCacheManager.count += 1;
    }
    g_resourceCacheManager.enabled0 = g_resourceCacheManager.enabled1 = 1;
    g_resourceCacheManager.selected = -1;
    g_resourceCacheManager.reservedWordBD4 = 0;
    g_resourceCacheManager.reservedWordBD8 = 0;
    g_resourceCacheManager.reservedWord8 = 0;
#if defined(VERSION_US)
    g_resourceCacheManager.reservedWordC1C = 0;
#else
    g_resourceCacheManager.reservedWordC1C = 1;
#endif
    g_resourceCacheManager.stamp = 0;
    List_InitializeIntrusive(&g_resourceCacheManager.freeLinks, 40, 36);
    List_InitializeIntrusive(&g_resourceCacheManager.listBAC, 40, 36);
    List_InitializeIntrusive(&g_resourceCacheManager.listBC0, 40, 36);
    for (i = 0; i < g_resourceCacheNodeCapacity; i++) {
        struct ResLink *link = &g_resourceCacheManager.links[i];
        link->owner = 0;
        List_AppendIntrusive(&g_resourceCacheManager.freeLinks, link);
    }
    HashTable_InitializeResourceTable(g_resourceCacheNodeCapacity);
    osCreateMesgQueue(&g_resourceRequestManager.requests, g_resourceRequestManager.requestMessages, 64);
    unlockMask = __osDisableInt();
    g_resourceHeapLockUsers -= 1;
    if (g_resourceHeapLockUsers != 0) {
        __osRestoreInt(unlockMask);
        osSendMesg((OSMesgQueue *)g_resourceRequestManager.lock, 0, 1);
    } else {
        __osRestoreInt(unlockMask);
    }
    /* thread block g_resourceCompletionWorkerStack - 0x348 followed by its 0x800-byte stack at g_resourceCompletionWorkerStack */
    XPlus_FillMemory(&g_resourceCompletionWorkerStack, count, 0x800);
    thread = (char *)&g_resourceCompletionWorkerStack - (((char *)&((struct ResMgr *)0)->completionWorkerStack - (char *)0) - ((char *)&((struct ResMgr *)0)->completionWorker - (char *)0));
    osCreateThread(thread, count, &g_Cache_RunResourceCompletionWorkerPackedAddress24, 0, (char *)&g_resourceCompletionWorkerStack + sizeof(((struct ResMgr *)0)->completionWorkerStack), g_resourceCompletionWorkerPriority);
    osStartThread(thread);
}





/* Reclaims one pool node: finds the first unlocked node (none of flags 0x702) in the g_resourceCompactionEntries list that
 * was last used five or more frames ago, falling back unless keep_recent is set to the first unlocked node
 * even if recent; the node's resource is released through Cache_DetachResourceRequest and Heap_FreeAllocation, it is unlinked
 * from its lists, cleared, and pushed back on the free stack, returning Heap_FreeAllocation's result (0 when no
 * node could be reclaimed). */




extern void Cache_DetachResourceRequest(void *, CMemEntry *);

static inline CMemEntry *find_stale(CMemEntry **recent) {
    CMemEntry *node;

    for (node = g_resourceCompactionEntries; node != 0; node = node->next) {
        if (!(node->flags & 0x702)) {
            if ((u32)(g_resourceCacheFrameStamp.value - node->lastUsed) >= 5) {
                return node;
            }
            *recent = node;
            break;
        }
    }
    for (; node != 0; node = node->next) {
        if (!(node->flags & 0x702) && (u32)(g_resourceCacheFrameStamp.value - node->lastUsed) >= 5) {
            return node;
        }
    }
    return 0;
}

/* Allocates a node from the free pool g_resourceFreeNodeCount (as Cache_AcquirePendingResourceEntry does: pops it, resets its fields,
 * stamps the current frame and links it through List_PrependIntrusive with the caller's 0xC flags); when the pool
 * is empty it runs the collector Cache_EvictResource (keeping the 0x10-flagged kind) and retries once, returning
 * 0 when nothing could be freed. Adapted by inlining Cache_AcquirePendingResourceEntry as a static helper. */






static inline void *pool_alloc(s32 byteCount) {
    struct CMemEntry *cacheEntry;

    if (((struct Pool *)&g_resourceFreeNodeCount)->count == 0) {
        return 0;
    }
    ((struct Pool *)&g_resourceFreeNodeCount)->count -= 1;
    cacheEntry = g_resourceFreeNodeStack[((struct Pool *)&g_resourceFreeNodeCount)->count];
    cacheEntry->flags = 0x800;
    cacheEntry->references = 0;
    cacheEntry->resource = 0;
    cacheEntry->callback = 0;
    cacheEntry->pending = 0;
    cacheEntry->owner = 0;
    cacheEntry->lastUsed = ((struct Pool *)&g_resourceFreeNodeCount)->useCounter;
    List_PrependIntrusive((char *)&g_resourceFreeNodeCount - (((char *)&((struct ResMgr *)0)->count - (char *)0) - ((char *)&((struct ResMgr *)0)->entries - (char *)0)), cacheEntry);
    cacheEntry->flags |= (byteCount & 0xC);
    return cacheEntry;
}


extern void Defs_MoveMemory(u32, u32, s32);

extern void List_InsertBeforeIntrusive(void *, s32, s32);

/* Looks up a key in the hash table under the queue lock and, if found, bumps the object's reference count, flags it, stamps it and passes it to List_MoveIntrusiveToHead, returning the object. Adapted from Cache_TouchResourceByKey, with the count/flag updates added and the object returned. */







extern struct MemoryUsageStats g_resourceHashEvenIndexMask;


extern void List_MoveIntrusiveToHead(void *, s32);

void Cache_WaitForResourceSlotRelease(void) {
    s32 lockReleaseCount;
    s32 lockClaimCount;
    s32 slotCursor;
    s32 i;
    s32 pendingReleaseCount;
    u32 reacquireInterruptMask;
    u32 mask;

    pendingReleaseCount = 0;
    slotCursor = 0;
    do {
        if (g_resourceSlotActivity[slotCursor] != 0) {
            if (g_resourceSlotLockState != slotCursor) {
                pendingReleaseCount += 1;
                g_resourceSlotOwners[slotCursor] = 1;
                goto block_7;
            }
            g_resourceSlotProtected[slotCursor] = 0;
            Cache_ClearResourceSlotProtection(0, slotCursor);
            slotCursor += 1;
        } else {
block_7:
            slotCursor += 1;
        }
    } while (slotCursor < 2);
    if (pendingReleaseCount != 0) {
        mask = __osDisableInt();
        lockReleaseCount = g_resourceHeapLockUsers - 1;
        g_resourceHeapLockUsers = lockReleaseCount;
        if (lockReleaseCount != 0) {
            __osRestoreInt(mask);
            osSendMesg(&g_resourceHeapLockQueue, 0, 1);
            i = 0;
        } else {
            __osRestoreInt(mask);
            i = 0;
        }
        if (pendingReleaseCount > 0) {
            do {
                osRecvMesg(&g_resourceCompletionWakeQueue, 0, 1);
                i += 1;
            } while (i < pendingReleaseCount);
        }
        reacquireInterruptMask = __osDisableInt();
        lockClaimCount = g_resourceHeapLockUsers + 1;
        g_resourceHeapLockUsers = lockClaimCount;
        if (lockClaimCount != 1) {
            __osRestoreInt(reacquireInterruptMask);
            osRecvMesg(&g_resourceHeapLockQueue, 0, 1);
            return;
        }
        __osRestoreInt(reacquireInterruptMask);
    }
}

s32 Cache_EvictResource(s32 unused0, s32 unused1, s32 keep_recent) {
    CMemEntry *recent;
    CMemEntry *node;
    s32 result;

    recent = 0;
    node = find_stale(&recent);
    if (node == 0) {
        if (keep_recent == 0) {
            node = recent;
        }
    }
    if (node != 0) {
        Cache_DetachResourceRequest(0, node);
        result = Heap_FreeAllocation(&g_runtimeHeap, node->resource);
        List_RemoveIntrusive(&g_resourceRecencyList, node);
        if (node->flags & 0x1000) {
            List_RemoveIntrusive(&g_resourcesByAddress, node);
        }
        if (g_resourceAllocationCandidate == node) {
            g_resourceAllocationCandidate = 0;
            node->flags = 0;
        } else {
            node->flags = 0;
        }
        *(CMemEntry **)(g_resourceFreeNodeCount * 4 + (char *)g_resourceFreeNodeStack) = node;
        g_resourceFreeNodeCount++;
        return result;
    }
    return 0;
}

void *Cache_AcquireResourceNodeWithEviction(s32 unused0, s32 flags) {
    void *node;

    node = pool_alloc(flags);
    if (node == 0) {
        s32 keep = flags & 0x10;

        if (Cache_EvictResource(0, 2, keep == 0) != 0) {
            node = pool_alloc(flags);
        }
    }
    return node;
}

void Cache_CompactResourceHeap(s32 unused, s32 compactAll) {
    IntrusiveList queue;
    CacheEvictionNode *node;
    CacheEvictionNode *next;
    CacheEvictionNode *scan;
    u32 split;
    s32 *arena_end;
    s32 *arena;
    s32 *pool;

    List_InitializeIntrusive(&queue, 32, 36);
    if (compactAll != 0 || ((s32 *)&g_resourceAllocationCandidate)[0] == 0) {
        ((s32 *)&g_resourceAllocationCandidate)[0] = ((s32 *)&g_resourceAllocationCandidate)[7];
        if (((s32 *)&g_resourceAllocationCandidate)[7] == 0) {
            goto drain;
        }
    }

    pool = (s32 *)&g_resourceAllocationCandidate;
    arena_end = &g_runtimeHeap[2];
    arena = arena_end - 2;
    do {
        node = (CacheEvictionNode *)pool[0];
        pool[0] = *(s32 *)&node->next;
        if (!(*(s32 *)&node->flags & 0x701) && (u32)(*arena_end + 32) < node->start) {
            Heap_FreeAllocation(arena, node->start);
            split = Heap_AllocateFromFront(arena, node->end);
            if (split < node->start) {
                Defs_MoveMemory(split, node->start, node->end);
                node->start = split;
                List_RemoveIntrusive(&pool[7], node);
                List_AppendIntrusive(&queue, node);
            }
            if (compactAll == 0) {
                break;
            }
        }
    } while (((s32 *)&g_resourceAllocationCandidate)[0] != 0);

drain:
    node = queue.head;
    while (node != 0) {
        next = node->next;
        List_DropIntrusiveHead(&queue);
        scan = g_resourcesByAddress.head;
        while (scan != 0) {
            if (scan->start > node->start) {
                List_InsertBeforeIntrusive(&g_resourcesByAddress, (s32)scan, (s32)node);
                break;
            }
            scan = scan->next;
        }
        if (scan == 0) {
            List_AppendIntrusive(&g_resourcesByAddress, node);
        }
        node->flags |= 0x1000;
        node = next;
    }
}

void *Cache_RetainResourceByKey(s32 unusedCache, s32 resourceKey) {
    s32 lockClaimCount;
    s32 lockReleaseCount;
    u32 mask;
    u32 releaseInterruptMask;
    HashNode *node;
    void *value;
    void **out;
    struct IntrusiveList *object;

    mask = __osDisableInt();
    lockClaimCount = g_resourceHeapLockUsers + 1;
    g_resourceHeapLockUsers = lockClaimCount;
    if (lockClaimCount != 1) {
        __osRestoreInt(mask);
        osRecvMesg(&g_resourceHeapLockQueue, 0, 1);
    } else {
        __osRestoreInt(mask);
    }

    out = &value;
    node = (HashNode *)((s32)g_resourceHashBuckets +
        ((((resourceKey << 5) ^ ((u32)resourceKey >> 1) ^ ((u32)resourceKey >> 9) ^
           ((u32)resourceKey >> 17)) & g_resourceHashEvenIndexMask.value) * 16));
    if (node->key != resourceKey) {
        goto not_initial;
    }
    value = node->value;
    goto found;
loop_found:
    *out = node->value;
    goto found;
not_initial:
    value = 0;
    if (node == 0) {
        goto found;
    }
loop:
    if (node->key == resourceKey) {
        goto loop_found;
    }
    node = node->next;
    if (node != 0) {
        goto loop;
    }
found:

    object = 0;
    if (value != 0) {
        object = *(void **)value;
        object->prevOffset += 1;
        object->nextOffset |= 0x100;
        object->count = g_resourceCacheFrameStamp.value;
        List_MoveIntrusiveToHead(&g_resourceRecencyList, object);
    }

    releaseInterruptMask = __osDisableInt();
    lockReleaseCount = g_resourceHeapLockUsers - 1;
    g_resourceHeapLockUsers = lockReleaseCount;
    if (lockReleaseCount != 0) {
        __osRestoreInt(releaseInterruptMask);
        osSendMesg(&g_resourceHeapLockQueue, 0, 1);
    } else {
        __osRestoreInt(releaseInterruptMask);
    }
    return object;
}
