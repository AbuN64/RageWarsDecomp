#include "Engine/cache.h"
#include "thread_queue.h"
#include "include_asm.h"
#include "Common/manager.h"
#include "Common/effectrender.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Common/runtime_declarations.h"
#include "types.h"
#include "Common/heap_arena_entry.h"
#include "Common/boot_memory_and_thread_boundaries.h"
#include "Engine/Cache/cache.h"
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "Engine/Cache/list.h"
#include "Common/heap_arena.h"
#include "Ui/X_files/x_plus.h"
#include "Common/os_timer_interrupt_internals.h"
#include "Engine/Cache/heap.h"
#include "Engine/Cache/mutex.h"
#include "Engine/defs.h"
#include "Audio/hashtable.h"
#include "Common/Lone/runtime_heap.h"
#include "Common/triple.h"
#include "Engine/Cache/cache_initializeresourcecache.h"
#include "Common/Lone/resource_request_queue.h"
#include "Common/cartridgereadworker.h"
#include "Common/trigger_and_float_value_operations.h"
#include "Common/controller_motor_state.h"
#include "Texture/cache_recycleloadrequest.h"
#include "Engine/Cache/decmprsr.h"
#include "Engine/Cache/loader.h"
#include "Engine/Cache/cache_requestresource.h"
#include "Engine/Cache/cache_requestpairedresource.h"
#include "PR/R4300.h"
#include "Common/vector4f.h"
#include "Common/externs.h"
#include "Engine/Cache/cache_drawmemoryusage.h"
#include "Engine/Cache/cache_allocateheapwitheviction.h"
#include <PR/gbi.h>
#include "Common/sessionhandlerrow.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Scene/cache_allocatememory.h"
#include "Engine/Cache/cache_runcompactionpasses.h"
#include "Common/resourcelockstate.h"
#include "Scene/cache_allocateresourceat.h"
#include "Engine/Cache/cache_allocresourceblock.h"
#include "Scene/cache_requestresource.h"
#include "Engine/session.h"
#include "Scene/cache_freememory.h"
#include "Engine/Cache/cache_acquireloadrequestwitheviction.h"

/* CACHE_INITIALIZERESOURCECACHE.CPP */


/* The resource manager record at g_resourceCacheManager: node array, free-slot stack, link records, lists and its lock queue.
 * count and stamp are the Pool fields used by Cache_AcquirePendingResourceEntry. */

void Cache_InitializeResourceCache(s32 cacheContext, s32 count) {
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
    g_resourceCacheManager.activity.active = 0;
#else
    g_resourceCacheManager.activity.active = 1;
#endif
    g_resourceCacheManager.activity.count = 0;
    List_InitializeIntrusive(&g_resourceCacheManager.freeLinks, 40, 36);
    List_InitializeIntrusive(&g_resourceCacheManager.activeRequests, 40, 36);
    List_InitializeIntrusive(&g_resourceCacheManager.pendingRequests, 40, 36);
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
/* The completion worker thread record and its stack are members of the resource manager. */
    XPlus_FillMemory(g_resourceCacheManager.completionWorkerStack, count, sizeof(g_resourceCacheManager.completionWorkerStack));
    thread = &g_resourceCacheManager.completionWorker;
    osCreateThread(thread, count, &addrLow_Cache_RunResourceCompletionWorker, 0, g_resourceCacheManager.completionWorkerStack + sizeof(g_resourceCacheManager.completionWorkerStack), g_resourceCompletionWorkerPriority);
    osStartThread(thread);
}

/* Reclaims one pool node: finds the first unlocked node (none of flags 0x702) in the g_resourceCompactionEntries list that
 * was last used five or more frames ago, falling back unless keep_recent is set to the first unlocked node
 * even if recent; the node's resource is released through Cache_DetachResourceRequest and Heap_FreeAllocation, it is unlinked
 * from its lists, cleared, and pushed back on the free stack, returning Heap_FreeAllocation's result (0 when no
 * node could be reclaimed). */

static inline CMemEntry *find_stale(CMemEntry **recent) {
    CMemEntry *node;

    for (node = g_resourceCompactionEntries; node != 0; node = node->next) {
        if (!(node->flags & 0x702)) {
            if ((u32)(g_resourceCacheManager.activity.count - node->lastUsed) >= 5) {
                return node;
            }
            *recent = node;
            break;
        }
    }
    for (; node != 0; node = node->next) {
        if (!(node->flags & 0x702) && (u32)(g_resourceCacheManager.activity.count - node->lastUsed) >= 5) {
            return node;
        }
    }
    return 0;
}

/* Allocates a node from the free pool g_resourceCacheManager.count (as Cache_AcquirePendingResourceEntry does: pops it, resets its fields,
 * stamps the current frame and links it through List_PrependIntrusive with the caller's 0xC flags); when the pool
 * is empty it runs the collector Cache_EvictResource (keeping the 0x10-flagged kind) and retries once, returning
 * 0 when nothing could be freed. Adapted by inlining Cache_AcquirePendingResourceEntry as a static helper. */

static inline void *pool_alloc(s32 byteCount) {
    struct CMemEntry *cacheEntry;

    if (g_resourceCacheManager.count == 0) {
        return 0;
    }
    g_resourceCacheManager.count -= 1;
    cacheEntry = g_resourceCacheManager.slots[g_resourceCacheManager.count];
    cacheEntry->flags = 0x800;
    cacheEntry->references = 0;
    cacheEntry->resource = 0;
    cacheEntry->callback = 0;
    cacheEntry->pending = 0;
    cacheEntry->owner = 0;
    cacheEntry->lastUsed = g_resourceCacheManager.activity.count;
    List_PrependIntrusive(&g_resourceCacheManager.entries, cacheEntry);
    cacheEntry->flags |= (byteCount & 0xC);
    return cacheEntry;
}

/* Looks up a key in the hash table under the queue lock and, if found, bumps the object's reference count, flags it, stamps it and passes it to List_MoveIntrusiveToHead, returning the object. */

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

s32 Cache_EvictResource(s32 cacheContext, s32 evictionMode, s32 keep_recent) {
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
        List_RemoveIntrusive(&g_resourceCacheManager.entries, node);
        if (node->flags & 0x1000) {
            List_RemoveIntrusive(&g_resourcesByAddress, node);
        }
        if (g_resourceAllocationCandidate == node) {
            g_resourceAllocationCandidate = 0;
            node->flags = 0;
        } else {
            node->flags = 0;
        }
        g_resourceCacheManager.slots[g_resourceCacheManager.count] = node;
        g_resourceCacheManager.count++;
        return result;
    }
    return 0;
}

void *Cache_AcquireResourceNodeWithEviction(s32 cacheContext, s32 flags) {
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

/* g_resourceCacheManager from reservedWord8 (g_resourceAllocationCandidate) on: the compaction cursor, the
 * link records, the entries list and the recent list it walks. */
typedef struct ResourceCompaction {
    CacheEvictionNode *cursor;
    struct ResLink *links;
    IntrusiveList entries;
    IntrusiveList recent;
} ResourceCompaction;

void Cache_CompactResourceHeap(s32 cacheContext, s32 compactAll) {
    IntrusiveList queue;
    CacheEvictionNode *node;
    CacheEvictionNode *next;
    CacheEvictionNode *scan;
    u32 split;
    s32 *arena_end;
    s32 *arena;
    ResourceCompaction *pool;

    List_InitializeIntrusive(&queue, 32, 36);
    if (compactAll != 0 || ((ResourceCompaction *)&g_resourceAllocationCandidate)->cursor == 0) {
        ((ResourceCompaction *)&g_resourceAllocationCandidate)->cursor = (CacheEvictionNode *)((ResourceCompaction *)&g_resourceAllocationCandidate)->recent.head;
        if (((ResourceCompaction *)&g_resourceAllocationCandidate)->recent.head == 0) {
            goto drain;
        }
    }

    pool = (ResourceCompaction *)&g_resourceAllocationCandidate;
    arena_end = ((s32 *)&g_runtimeHeap) + 2;
    arena = arena_end - 2;
    do {
        node = pool->cursor;
        pool->cursor = node->next;
        if (!(node->flags & 0x701) && (u32)(*arena_end + 32) < node->start) {
            Heap_FreeAllocation(arena, node->start);
            split = Heap_AllocateFromFront(arena, node->end);
            if (split < node->start) {
                Defs_MoveMemory(split, node->start, node->end);
                node->start = split;
                List_RemoveIntrusive(&pool->recent, node);
                List_AppendIntrusive(&queue, node);
            }
            if (compactAll == 0) {
                break;
            }
        }
    } while (((ResourceCompaction *)&g_resourceAllocationCandidate)->cursor != 0);

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
        ((u32)resourceKey >> 17)) & g_resourceHashEvenIndexMask) * 16));
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
        object->count = g_resourceCacheManager.activity.count;
        List_MoveIntrusiveToHead(&g_resourceCacheManager.entries, object);
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

/* CACHE_REQUESTRESOURCE.CPP */

/* Takes the heap lock: the first user passes straight through, later users wait on the manager's lock queue. */
static inline void Cache_LockHeap(void) {
    u32 token = __osDisableInt();
    s32 count = g_resourceHeapLockUsers + 1;

    g_resourceHeapLockUsers = count;
    if (count != 1) {
        __osRestoreInt(token);
        osRecvMesg(g_resourceRequestManager.lock, 0, 1);
    } else {
        __osRestoreInt(token);
    }
}

/* Drops the heap lock and wakes the next waiting user, if any. */
static inline void Cache_UnlockHeap(void) {
    u32 token = __osDisableInt();
    s32 count = g_resourceHeapLockUsers - 1;

    g_resourceHeapLockUsers = count;
    if (count != 0) {
        __osRestoreInt(token);
        osSendMesg(g_resourceRequestManager.lock, 0, 1);
    } else {
        __osRestoreInt(token);
    }
}

/* Looks up the load request registered under a key: hashes to the home bucket, then follows its collision chain. */
static inline void Cache_FindRequestByKey(u32 key, ResourceLoadRequest **out) {
    ResourceHashEntry *node = g_resourceHashBuckets + (((key << 5) ^ (key >> 1) ^ (key >> 9) ^ (key >> 17)) & g_resourceHashEvenIndexMask);

    *out = 0;
    for (; node != 0; node = node->next) {
        if (node->key == key) {
            *out = node->value;
            return;
        }
    }
}

/* Adds one reference to a cached resource and marks it referenced. */
static inline void Cache_AddResourceReference(CachedResource *node) {
    node->count++;
    node->flags |= 0x100;
}

/* Records the current frame stamp on a resource and moves it to the head of the recency list. */
static inline void Cache_StampResource(CachedResource *node) {
    node->stamp = g_resourceCacheManager.activity.count;
    List_MoveIntrusiveToHead(&g_resourceCacheManager.entries, (s32)node);
}

/* Takes a resource node and a heap block of the requested size for it; gives the node back and returns 0 when the heap has no room. */
static inline CachedResource *Cache_AllocateResourceNode(u32 size, u32 flags) {
    CachedResource *node = Cache_AcquireResourceNodeWithEviction(0, flags);

    if (node == 0) {
        return node;
    }
    Cache_AddResourceReference(node);
    node->data = Cache_AllocateHeapWithEviction(0, size, (flags >> 5) & 1, flags);
    if (node->data != 0) {
        node->dataSize = size;
        node->flags |= flags;
        Cache_InsertResourceByAddress(0, node);
        return node;
    }
    node->count--;
    if (node->count == 0) {
        node->flags &= ~0x100;
    }
    Cache_ReleasePendingResourceEntry(0, (s32)node);
    return 0;
}

/* Requests a resource by key. A resource already registered with enough priority is returned at once. Otherwise a node and
 * heap block are allocated and the data is read from the cartridge: synchronously when the request is direct, else queued
 * to the read worker with a null return. Returns the cached resource node, or 0 when it is not available yet. */
void *Cache_RequestResource(s32 cacheContext, u32 key, u32 source, u32 size,
    u32 mode, s32 owner, void *tag, const char *spare, u32 direct) {
    ResourceLoadRequest *request;
    ResourceLoadRequest *activeRequest;
    ResourceLoadRequest *resolved;
    CachedResource *node;
    u32 flags;
    u32 requestFlags;
    s32 alreadyRequested;

    Cache_LockHeap();
    Cache_FindRequestByKey(key, &request);
    if (request != 0 && (u32)request->priority <= size) {
        Cache_AddResourceReference(request->node);
        Cache_StampResource(request->node);
        Cache_UnlockHeap();
        return request->node;
    }
    direct |= g_resourceRequestManager.mask;
    alreadyRequested = 0;
    if (direct == 0) {
        for (activeRequest = g_resourceRequestManager.active.head; activeRequest != 0; activeRequest = activeRequest->next) {
            if (activeRequest->key == key && size <= (u32)activeRequest->priority) {
                alreadyRequested = 1;
                break;
            }
        }
        if (alreadyRequested) {
            Cache_UnlockHeap();
            return 0;
        }
    }
    request = Cache_AcquireLoadRequestWithEviction(0, mode);
    if (request != 0) {
        if (tag != 0) {
            flags = (mode & 0x1C) | 0x22;
        } else {
            flags = mode;
        }
        request->extra = 0;
        node = Cache_AllocateResourceNode(size, flags);
        request->node = node;
        if (request->node != 0) {
            if (size & 1) {
                size++;
            }
            request->key = key;
            request->priority = size;
            request->owner = owner;
            request->tag = tag;
            request->mode = mode;
            List_RemoveIntrusive(&g_resourceRequestManager.pending, request);
            List_AppendIntrusive(&g_resourceRequestManager.active, request);
            if (direct != 0) {
                if (tag != 0) {
                    request->flags |= 4;
                }
                Cache_UnlockHeap();
                Cartridge_ReadChunksAndWait(&g_cartridgeReadWorker, source, size, request->node->data);
                if (tag != 0) {
                    Cache_SubmitResourceLoadAndWait(&g_resourceCacheWorker, request);
                }
                Cache_LockHeap();
                if (tag != 0) {
                    request->flags &= ~4;
                }
                resolved = Cache_FinalizeResourceLoad(0, request, 0);
                if (resolved != 0 && resolved != request) {
                    Cache_AddResourceReference(resolved->node);
                }
                Cache_UnlockHeap();
                if (resolved != 0) {
                    return resolved->node;
                }
                return 0;
            }
            requestFlags = request->flags;
            request->flags = requestFlags | 2;
            if (tag != 0) {
                request->flags = requestFlags | 0xE;
            }
            Cache_UnlockHeap();
            Cartridge_SubmitReadChunks(&g_cartridgeReadWorker, source, size, request->node->data, &g_resourceRequestManager, (s32)request, 0);
            return 0;
        }
        Cache_RecycleLoadRequest(0, request);
    }
    Cache_UnlockHeap();
    return 0;
}

/* CACHE_REQUESTPAIREDRESOURCE.CPP */

/* Looks a key up in the request hash table under the manager lock: an existing request bumps its
   node's reference count and flags, stamps it and hands the node to List_MoveIntrusiveToHead; otherwise, unless
   a request for the key is already active, a fresh request is taken, filled in from the arguments,
   given a reference on each of the two nodes and moved to the active list. Outside the lock the
   request is then either started asynchronously through Cache_SubmitResourceLoadAndWait and Cache_FinalizeResourceLoad, or run
   synchronously through Cache_TrySubmitResourceLoad, whose failure gives the two references back and finishes the
   request. The lock, the hash lookup and the reference bump are the inline forms of Cache_RunResourceCompletionWorker,
   Cache_RetainResourceByKey and Cache_FinalizeResourceLoad. The eighth argument is never read.

   Manager is one object, which is what lets the compiler reach its lock queue from whichever of its
   members is already in a base register; g_resourceHeapLockUsers is a separate symbol although it lies past the
   members named here, because every reference to it materialises its own address. */

static inline void addref(CachedResource *node) {
    node->count += 1;
    node->flags |= 0x100;
}

static inline void stamp(CachedResource *node) {
    node->stamp = g_resourceCacheManager.activity.count;
    List_MoveIntrusiveToHead(&g_resourceCacheManager.entries, node);
}

static inline void unref(CachedResource *node) {
    if (--node->count == 0) {
        node->flags &= ~0x100;
    }
}

static inline void acquire(void) {
    u32 token = __osDisableInt();
    s32 counter = g_resourceHeapLockUsers + 1;

    g_resourceHeapLockUsers = counter;
    if (counter != 1) {
        __osRestoreInt(token);
        osRecvMesg(g_resourceRequestManager.lock, 0, 1);
    } else {
        __osRestoreInt(token);
    }
}

static inline void release(void) {
    u32 token = __osDisableInt();
    s32 counter = g_resourceHeapLockUsers - 1;

    g_resourceHeapLockUsers = counter;
    if (counter != 0) {
        __osRestoreInt(token);
        osSendMesg(g_resourceRequestManager.lock, 0, 1);
    } else {
        __osRestoreInt(token);
    }
}

/* Runs the resource manager thread: waits for messages on its queue g_resourceRequestManager and, under the manager lock, frees the heap for messages 0 and 1, retries or completes a pending load request (flag 8) by unlinking it, draining its node's reference count, releasing an unreferenced node's data and handle, and finishing the request, or otherwise (flag 4) starts it through Cache_FinalizeResourceLoad. The flag 8 path clears its reference loop with an inner do-while, and each branch unlocks itself. */

static inline void lock(void) {
    u32 token = __osDisableInt();
    s32 counter = g_resourceHeapLockUsers + 1;

    g_resourceHeapLockUsers = counter;
    if (counter != 1) {
        __osRestoreInt(token);
        osRecvMesg(g_resourceRequestManager.lock, 0, 1);
    } else {
        __osRestoreInt(token);
    }
}

static inline void unlock(void) {
    u32 token = __osDisableInt();
    s32 counter = g_resourceHeapLockUsers - 1;

    g_resourceHeapLockUsers = counter;
    if (counter != 0) {
        __osRestoreInt(token);
        osSendMesg(g_resourceRequestManager.lock, 0, 1);
    } else {
        __osRestoreInt(token);
    }
}

CachedResource *Cache_RequestPairedResource(s32 cacheContext, s32 key, CachedResource *first, CachedResource *second, s32 mode, void *owner,
    void *tag, void *spare, s32 async) {
    ResourceHashEntry *node;
    ResourceLoadRequest *found;
    ResourceLoadRequest **out;
    ResourceLoadRequest *scan;
    s32 busy;

    acquire();

    out = &found;
    node = (ResourceHashEntry *)((s32)g_resourceHashBuckets +
        ((((key << 5) ^ ((u32)key >> 1) ^ ((u32)key >> 9) ^
        ((u32)key >> 17)) & g_resourceHashEvenIndexMask) * 16));
    if (node->key != key) {
        goto not_initial;
    }
    found = node->value;
    goto done;
    loop_found:
    *out = node->value;
    goto done;
    not_initial:
    found = 0;
    if (node == 0) {
        goto done;
    }
    loop:
    if (node->key == key) {
        goto loop_found;
    }
    node = node->next;
    if (node != 0) {
        goto loop;
    }
    done:

    busy = 0;
    if (found != 0) {
        addref(found->node);
        stamp(found->node);
        release();
        return found->node;
    }

    async |= g_resourceRequestManager.mask;
    scan = g_resourceRequestManager.active.head;
    while (scan != 0) {
        if (scan->key == key) {
            busy = 1;
            break;
        }
        scan = scan->next;
    }
    if (busy == 0) {
        found = Cache_AcquireLoadRequestWithEviction(0, mode);
        if (found != 0) {
            found->key = key;
            found->priority = 0;
            found->owner = (s32)owner;
            found->tag = tag;
            found->mode = mode;
            found->node = first;
            found->extra = second;

            if (first != 0) {
                addref(first);
            }
            if (second != 0) {
                addref(second);
            }

            List_RemoveIntrusive(&g_resourceRequestManager.pending, found);
            List_AppendIntrusive(&g_resourceRequestManager.active, found);
            release();

            if (async != 0) {
                found->flags &= ~0xE;
                Cache_SubmitResourceLoadAndWait(&g_resourceCacheWorker, found);
                acquire();
                found = Cache_FinalizeResourceLoad(0, found, 0);
                release();
                if (found != 0) {
                    return found->node;
                }
                return 0;
            }

            if (Cache_TrySubmitResourceLoad(&g_resourceCacheWorker, found, &g_resourceRequestManager) == 0) {
                acquire();
                if (first != 0) {
                    unref(first);
                }
                if (second != 0) {
                    unref(second);
                }
                List_RemoveIntrusive(&g_resourceRequestManager.active, found);
                List_PrependIntrusive(&g_resourceRequestManager.pending, found);
                Cache_RecycleLoadRequest(0, found);
                release();
            }
            return 0;
        }
    }
    release();
    return 0;
}

void Cache_RunResourceCompletionWorker(void *arg) {
    RequestCacheRunResourceCompletionWorker *request;
    NodeCacheRunResourceCompletionWorker *node;
    s32 flags;

    for (;;) {
        osRecvMesg(&g_resourceRequestManager, &request, 1);
        if ((u32)request < 2) {
            lock();
            Cache_AcknowledgeResourceSlotRelease(0, request);
            unlock();
        } else {
            request->flags &= ~2;
            flags = request->flags;
            if (flags & 8) {
                request->flags = flags & ~8;
                if (Cache_TrySubmitResourceLoad(&g_resourceCacheWorker, request, &g_resourceRequestManager) == 0) {
                    lock();
                    List_RemoveIntrusive(&g_resourceRequestManager.active, request);
                    List_PrependIntrusive(&g_resourceRequestManager.pending, request);
                    node = request->node;
                    node->flags &= ~2;
                    while (node->count != 0) {
                        do {
                        } while (--node->count != 0);
                        node->flags &= ~0x100;
                    }
                    if (!(node->flags & 0x702)) {
                        Cache_DetachResourceRequest(0, node);
                        Heap_FreeAllocation(&g_runtimeHeap, node->data);
                        Cache_ReleasePendingResourceEntry(0, node);
                    }
                    Cache_RecycleLoadRequest(0, request);
                    unlock();
                }
            } else {
                request->flags = flags & ~4;
                lock();
                Cache_FinalizeResourceLoad(0, request, 1);
                unlock();
            }
        }
    }
}

/* CACHE_DRAWMEMORYUSAGE.CPP */

/* Activates a load request: moves it from the pending to the active list and, when its node is set, looks its key up in the request hash table; an existing request with lower priority is removed from the table and finished, releasing its node's data and node when nothing else holds them, while an existing request with at least the same priority wins and this request's node is released and the request finished, returning the existing one; otherwise, or after replacing, the request is inserted, owns its node and optionally drops the node's pending reference. The hash lookup and node release are the inline forms of Cache_RetainResourceByKey's lookup and Cache_ReleasePendingResourceEntry. */

static inline void find(s32 key, ResourceLoadRequest **out) {
    CacheHashEntry *node = g_resourceHashBuckets + (((key << 5) ^ ((u32)key >> 1) ^ ((u32)key >> 9) ^ ((u32)key >> 17)) & g_resourceHashEvenIndexMask);

    if (node->key == key) {
        *out = node->value;
        return;
    }
    *out = 0;
    while (node != 0) {
        if (node->key == key) {
            *out = node->value;
            return;
        }
        node = node->next;
    }
}

static inline void release_cache_drawmemoryusage(s32 node) {
    List_RemoveIntrusive(&g_resourceCacheManager.entries, (void *)node);
    if (((CachedResource *)node)->flags & 0x1000) {
        List_RemoveIntrusive(&g_resourceCacheManager.recent, (void *)node);
    }
    if (g_resourceCacheManager.reservedWord8 == node) {
        g_resourceCacheManager.reservedWord8 = 0;
    }
    ((CachedResource *)node)->flags = 0;
    g_resourceCacheManager.slots[g_resourceCacheManager.count] = (void *)node;
    g_resourceCacheManager.count += 1;
}

ResourceLoadRequest *Cache_FinalizeResourceLoad(s32 cacheContext, ResourceLoadRequest *request, s32 dropReference) {
    ResourceLoadRequest *existing;
    CachedResource *node;

    List_RemoveIntrusive(&g_resourceCacheManager.pendingRequests, request);
    List_PrependIntrusive(&g_resourceCacheManager.activeRequests, request);
    if (request->node != 0) {
        find(request->key, &existing);
        if (existing != 0) {
            if (existing->priority < request->priority) {
                HashTable_RemoveResourceByKey(existing->key);
                existing->node->owner = 0;
                if (!(existing->node->flags & 0x702)) {
                    Heap_FreeAllocation(&g_runtimeHeap, existing->node->data);
                    release_cache_drawmemoryusage((s32)existing->node);
                }
                Cache_RecycleLoadRequest(0, existing);
            } else {
                Heap_FreeAllocation(&g_runtimeHeap, request->node->data);
                release_cache_drawmemoryusage((s32)request->node);
                Cache_RecycleLoadRequest(0, request);
                return existing;
            }
        }
        HashTable_SetResourceByKey(request->key, request);
        request->node->owner = request;
        if (dropReference != 0) {
            node = request->node;
            if (--node->count == 0) {
                node->flags &= ~0x100;
            }
        }
        return request;
    }
    Cache_RecycleLoadRequest(0, request);
    return 0;
}


/* The main heap (its other users declare g_runtimeHeap as a plain byte); its block list is read through this view. */
static inline struct Heap *mainHeap(void) {
    return (struct Heap *)&g_runtimeHeap;
}

/* Band edge shades: half (darker) and one and a half (brighter) of a colour channel, clamped to 255. */
#define DARKEN(c) ((s32)((u32)(c) >> 1) < 0x100 ? (s32)((u32)(c) >> 1) : 0xFF)
#define BRIGHTEN(c) ((((c) * 3) >> 1) > 0xFF ? 0xFF : (((c) * 3) >> 1))

static inline void lock_cache_drawmemoryusage(void) {
    u32 token = __osDisableInt();
    s32 counter = g_resourceHeapLockUsers + 1;

    g_resourceHeapLockUsers = counter;
    if (counter != 1) {
        __osRestoreInt(token);
        osRecvMesg(g_resourceRequestManager.lock, 0, 1);
    } else {
        __osRestoreInt(token);
    }
}

static inline void unlock_cache_drawmemoryusage(void) {
    u32 token = __osDisableInt();
    s32 counter = g_resourceHeapLockUsers - 1;

    g_resourceHeapLockUsers = counter;
    if (counter != 0) {
        __osRestoreInt(token);
        osSendMesg(g_resourceRequestManager.lock, 0, 1);
    } else {
        __osRestoreInt(token);
    }
}

/* Debug heap map inside a grey frame: the bar is scaled to the heap's extent (bytes from the start of RAM to its first
 * block plus every block's used and free size); the part below the first block is olive, then each cache entry is a
 * band (yellow, red, blue or green by its flags) with a darker bottom edge, entries outside the locked set in the
 * first pass and locked ones in the second; an entry that is not locked or loading and was untouched for 5+ frames
 * also gets a white inset band. Runs under the resource lock. */
void Cache_DrawMemoryUsage(s32 cacheContext, s32 left, s32 top, s32 right, s32 bottom) {
    struct HeapAllocationBlock *span;
    CacheEvictionNode *node;
    u32 total;
    s32 pass;
    s32 select;
    s32 lo;
    s32 hi;
    s32 r;
    s32 g;
    s32 b;
    u32 base;

    gDPPipeSync(g_displayListCursor++);
    gDPSetCycleType(g_displayListCursor++, G_CYC_1CYCLE);
    Geometry_SetCombineMode(25);
    Geometry_SetModePreset(21);
    gDPSetPrimColor(g_displayListCursor++, 0, 0, 0xA0, 0xA0, 0xA0, 0x00);
    gDPFillRectangle(g_displayListCursor++, left - 1, top - 1, right + 1, bottom + 1);
    Geometry_SetModePreset(27);
    gDPSetPrimColor(g_displayListCursor++, 0, 0, 0xA0, 0xA0, 0xA0, 0xFF);
    gDPFillRectangle(g_displayListCursor++, left, top, right, bottom);

    lock_cache_drawmemoryusage();

    base = K0BASE;
    span = mainHeap()->first;
    total = (u32)span - base;
    for (; span != 0; span = span->next) {
        total += span->size + span->free;
    }

    gDPSetPrimColor(g_displayListCursor++, 0, 0, 0x64, 0x64, 0x00, 0xFF);
    hi = bottom - ((u32)(((u32)mainHeap()->first - base) * (bottom - top)) / total) - 1;
    gDPFillRectangle(g_displayListCursor++, left, hi, right, bottom + 1);

    for (pass = 0; pass < 2; pass++) {
        for (node = g_resourcesByAddress.head; node != 0; node = node->next) {
            if (pass != 0) {
                select = (node->flags & 0x101) == 0x100;
            } else {
                select = (node->flags & 0x101) != 0x100;
            }
            if (select == 0) {
                continue;
            }

            if (node->flags & 1) { r = 255; g = 255; b = 0; }
            else if (node->flags & 0x100) { r = 255; g = 0; b = 0; }
            else if (node->flags & 0x600) { r = 0; g = 0; b = 255; }
            else { r = 0; g = 255; b = 0; }

            gDPSetPrimColor(g_displayListCursor++, 0, 0, r, g, b, 0xFF);
            hi = bottom - ((u32)(((node->start + node->end) - base) * (bottom - top)) / total) - 1;
            lo = bottom - ((u32)(((node->start - base) - 32) * (bottom - top)) / total) - 1;
            if (hi < lo) {
                gDPFillRectangle(g_displayListCursor++, left, hi, right, lo);
            }
            gDPSetPrimColor(g_displayListCursor++, 0, 0, DARKEN(r), DARKEN(g), DARKEN(b), 0xFF);
            gDPFillRectangle(g_displayListCursor++, left, lo - 1, right, lo);

            if (!(node->flags & 0x702)) {
                r = g = b = 0xFF;
                if ((u32)(g_resourceCacheManager.activity.count - node->stamp) >= 5U) {
                    gDPSetPrimColor(g_displayListCursor++, 0, 0, r, g, b, 255);
                    if (hi < lo) {
                        gDPFillRectangle(g_displayListCursor++, left + 8, hi, right, lo);
                    }
                    gDPSetPrimColor(g_displayListCursor++, 0, 0, BRIGHTEN(r), BRIGHTEN(g), BRIGHTEN(b), 255);
                    gDPFillRectangle(g_displayListCursor++, left + 8, lo - 1, right, lo);
                }
            }
        }
    }

    unlock_cache_drawmemoryusage();
}

/* Keep this source unit's macros local to its body. */
#undef BRIGHTEN
#undef DARKEN

/* CACHE_ALLOCATEMEMORY.CPP */

/* Allocates size bytes (plus a 16-byte heap header) from the scene heap under the heap lock; when the
   heap is full it purges unreferenced resources and retries. The game uses it as its malloc. */
struct Record *Cache_AllocateMemory(s32 size) {
    struct CacheAllocationNodeView *node;
    struct CacheAllocationNodeView *current;
    s32 allocation_size;
    s32 counter;
    s32 counter2;
    s32 counter3;
    s32 counter4;
    s32 payload;
    struct Record *result;
    u32 token;
    u32 token2;
    u32 token3;
    u32 token4;

    allocation_size = size + 16;
    token = __osDisableInt();
    counter = g_resourceHeapLockUsers + 1;
    g_resourceHeapLockUsers = counter;
    if (counter != 1) {
        __osRestoreInt(token);
        osRecvMesg(&g_resourceHeapLockQueue, 0, 1);
    } else {
        __osRestoreInt(token);
    }
    node = Cache_AllocateResourceNodeStorage(0, allocation_size, 51U);
    token2 = __osDisableInt();
    counter2 = g_resourceHeapLockUsers - 1;
    g_resourceHeapLockUsers = counter2;
    if (counter2 != 0) {
        __osRestoreInt(token2);
        osSendMesg(&g_resourceHeapLockQueue, 0, 1);
        current = node;
    } else {
        __osRestoreInt(token2);
        current = node;
    }
    if (current == 0) {
        token3 = __osDisableInt();
        counter3 = g_resourceHeapLockUsers + 1;
        g_resourceHeapLockUsers = counter3;
        if (counter3 != 1) {
            __osRestoreInt(token3);
            osRecvMesg(&g_resourceHeapLockQueue, 0, 1);
        } else {
            __osRestoreInt(token3);
        }
        Cache_WaitForResourceSlotRelease();
        do {
        } while (Cache_SelectAllocationCandidate(0, 0, 0) != 0);
        Cache_CompactResourceHeap(0, 1);
        token4 = __osDisableInt();
        counter4 = g_resourceHeapLockUsers - 1;
        g_resourceHeapLockUsers = counter4;
        if (counter4 != 0) {
            __osRestoreInt(token4);
            osSendMesg(&g_resourceHeapLockQueue, 0, 1);
        } else {
            __osRestoreInt(token4);
        }
        token3 = __osDisableInt();
        counter3 = g_resourceHeapLockUsers + 1;
        g_resourceHeapLockUsers = counter3;
        if (counter3 != 1) {
            __osRestoreInt(token3);
            osRecvMesg(&g_resourceHeapLockQueue, 0, 1);
        } else {
            __osRestoreInt(token3);
        }
        node = Cache_AllocateResourceNodeStorage(0, allocation_size, 51U);
        token2 = __osDisableInt();
        counter2 = g_resourceHeapLockUsers - 1;
        g_resourceHeapLockUsers = counter2;
        if (counter2 != 0) {
            __osRestoreInt(token2);
            osSendMesg(&g_resourceHeapLockQueue, 0, 1);
            current = node;
        } else {
            __osRestoreInt(token2);
            current = node;
        }
    }
    if (current != 0) {
        payload = current->payload;
        result = (struct Record *)(payload + 16);
        *(struct CacheAllocationNodeView **)payload = current;
        return result;
    }
    return 0;
}

int Cache_IsResourceRetained(void *resource) {
    return ((CacheResourceNode *)resource)->flags & 0x100;
}

void Cache_RetainResource(CacheResourceNode *resource) {
    resource->references = resource->references + 1;
    resource->flags = resource->flags | 0x100;
}

void Cache_ReleaseResourceReference(CacheResourceNode *resource) {
    s32 remainingReferences;
    remainingReferences = resource->references - 1;
    resource->references = remainingReferences;
    if (remainingReferences == 0) {
        resource->flags = (s32) (resource->flags & ~0x100);
    }
}

/* CACHE_RUNCOMPACTIONPASSES.CPP */

void Cache_RunCompactionPasses(s32 cacheContext) {
    s32 pendingPasses;
    s32 remainingPasses;
    u32 mask;
    u32 interruptMask;
    s32 passIndex;
    ResourceManagerState *resourceManager;
    void *queueAddress;
    OSMesgQueue *receive;
    OSMesgQueue *send;

    resourceManager = &g_resourceCacheManager.activity;
#if defined(VERSION_US)
    if (resourceManager->active != 0) {
        resourceManager->active--;
    }
    resourceManager->count++;
    mask = __osDisableInt();
    pendingPasses = g_resourceHeapLockUsers + 1;
    g_resourceHeapLockUsers = pendingPasses;
    if (pendingPasses != 1) {
        __osRestoreInt(mask);
        queueAddress = &g_resourceCacheManager.heapLockQueue;
        receive = queueAddress;
        osRecvMesg(receive, 0, 1);
#else
        passIndex = 1;
        resourceManager->active = passIndex;
        resourceManager->count += passIndex;
        mask = __osDisableInt();
        pendingPasses = g_resourceHeapLockUsers + passIndex;
        g_resourceHeapLockUsers = pendingPasses;
        if (pendingPasses != passIndex) {
            __osRestoreInt(mask);
            queueAddress = &g_resourceCacheManager.heapLockQueue;
            receive = queueAddress;
            osRecvMesg(receive, 0, passIndex);
#endif
            passIndex = 0;
        } else {
            __osRestoreInt(mask);
            passIndex = 0;
        }
        do {
            Cache_CompactResourceHeap(0, 0);
            passIndex++;
        } while (passIndex < 10);
        interruptMask = __osDisableInt();
        remainingPasses = g_resourceHeapLockUsers - 1;
        g_resourceHeapLockUsers = remainingPasses;
        if (remainingPasses != 0) {
            __osRestoreInt(interruptMask);
            queueAddress = &g_resourceHeapLockQueue;
            send = queueAddress;
            osSendMesg(send, 0, 1);
        } else {
            __osRestoreInt(interruptMask);
        }
    }

/* CACHE_ALLOCATERESOURCEAT.CPP */

struct CacheResourceNode *Cache_AllocateResource(s32 unusedCache, s32 byteCount, u32 allocationFlags, void *context) {
    struct CacheResourceNode *resource;
    s32 lockUsers;
    s32 remainingLockUsers;
    u32 mask;
    u32 unlockInterruptMask;
    s32 requestedBytes;
    u32 requestedFlags;
    void *evictedResource;

    requestedBytes = byteCount;
    requestedFlags = allocationFlags;
    evictedResource = context;
    mask = __osDisableInt();
    lockUsers = g_resourceHeapLockUsers + 1;
    g_resourceHeapLockUsers = lockUsers;
    if (lockUsers != 1) {
        __osRestoreInt(mask);
        osRecvMesg(&g_resourceHeapLockQueue, 0, 1);
    } else {
        __osRestoreInt(mask);
    }
    resource = Cache_AllocateResourceNodeStorage(0, requestedBytes, requestedFlags);
    unlockInterruptMask = __osDisableInt();
    remainingLockUsers = g_resourceHeapLockUsers - 1;
    g_resourceHeapLockUsers = remainingLockUsers;
    if (remainingLockUsers != 0) {
        __osRestoreInt(unlockInterruptMask);
        osSendMesg(&g_resourceHeapLockQueue, 0, 1);
    } else {
        __osRestoreInt(unlockInterruptMask);
    }
    return resource;
}

struct CacheResourceNode *Cache_AllocateResourceAt(void *address, void *requestedAddress, s32 byteCount, char *name) {
    struct CacheResourceNode *allocatedResource;
    s32 allocatedAddress;
    s32 lockClaimCount;
    s32 lockReleaseCount;
    u32 mask;
    u32 releaseInterruptMask;

    mask = __osDisableInt();
    lockClaimCount = g_resourceHeapLockUsers + 1;
    g_resourceHeapLockUsers = lockClaimCount;
    if (lockClaimCount != 1) {
        __osRestoreInt(mask);
        osRecvMesg(&g_resourceHeapLockQueue, 0, 1);
    } else {
        __osRestoreInt(mask);
    }
    allocatedResource = Cache_AcquireResourceNodeWithEviction(0, 0U);
    if (allocatedResource != 0) {
        allocatedAddress = Heap_AllocateAtAddress(&g_runtimeHeap, requestedAddress, byteCount);
        allocatedResource->data = allocatedAddress;
        if (allocatedAddress != 0) {
            allocatedResource->size = byteCount;
            allocatedResource->flags |= 3;
            Cache_InsertResourceByAddress(0, allocatedResource);
        } else {
            Cache_ReleasePendingResourceEntry(0, allocatedResource);
            allocatedResource = 0;
        }
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
    return allocatedResource;
}

void Cache_LockResource(void *cacheContext, CacheResourceNode *resource) {
    s32 lockUsers;
    s32 remainingLockUsers;
    u32 mask;
    u32 unlockInterruptMask;
    CacheResourceNode *resourceNode;

    resourceNode = resource;
    mask = __osDisableInt();
    lockUsers = g_resourceHeapLockUsers + 1;
    g_resourceHeapLockUsers = lockUsers;
    if (lockUsers != 1) {
        __osRestoreInt(mask);
        osRecvMesg(&g_resourceHeapLockQueue, 0, 1);
    } else {
        __osRestoreInt(mask);
    }
    Cache_TouchResource(0, resourceNode);
    resourceNode->references += 1;
    resourceNode->flags |= 0x100;
    unlockInterruptMask = __osDisableInt();
    remainingLockUsers = g_resourceHeapLockUsers - 1;
    g_resourceHeapLockUsers = remainingLockUsers;
    if (remainingLockUsers != 0) {
        __osRestoreInt(unlockInterruptMask);
        osSendMesg(&g_resourceHeapLockQueue, 0, 1);
        return;
    }
    __osRestoreInt(unlockInterruptMask);
}

void Cache_UnlockResource(void *cacheContext, CacheResourceNode *resource) {
    s32 lockUsers;
    s32 remainingLockUsers;
    u32 mask;
    u32 unlockInterruptMask;
    CacheResourceNode *resourceNode;

    resourceNode = resource;
    mask = __osDisableInt();
    lockUsers = g_resourceHeapLockUsers + 1;
    g_resourceHeapLockUsers = lockUsers;
    if (lockUsers != 1) {
        __osRestoreInt(mask);
        osRecvMesg(&g_resourceHeapLockQueue, 0, 1);
    } else {
        __osRestoreInt(mask);
    }
    resourceNode->references -= 1;
    if (resourceNode->references == 0) {
        resourceNode->flags &= ~0x100;
    }
    unlockInterruptMask = __osDisableInt();
    remainingLockUsers = g_resourceHeapLockUsers - 1;
    g_resourceHeapLockUsers = remainingLockUsers;
    if (remainingLockUsers != 0) {
        __osRestoreInt(unlockInterruptMask);
        osSendMesg(&g_resourceHeapLockQueue, 0, 1);
        return;
    }
    __osRestoreInt(unlockInterruptMask);
}

void Cache_ReleaseResource(void *cacheContext, void *resource) {
    s32 lockUsers;
    s32 remainingLockUsers;
    u32 mask;
    u32 unlockInterruptMask;

    mask = __osDisableInt();
    lockUsers = g_resourceHeapLockUsers + 1;
    g_resourceHeapLockUsers = lockUsers;
    if (lockUsers != 1) {
        __osRestoreInt(mask);
        osRecvMesg(&g_resourceHeapLockQueue, 0, 1);
    } else {
        __osRestoreInt(mask);
    }
    Cache_ReleaseResourceCompletely(0, resource);
    unlockInterruptMask = __osDisableInt();
    remainingLockUsers = g_resourceHeapLockUsers - 1;
    g_resourceHeapLockUsers = remainingLockUsers;
    if (remainingLockUsers != 0) {
        __osRestoreInt(unlockInterruptMask);
        osSendMesg(&g_resourceHeapLockQueue, 0, 1);
        return;
    }
    __osRestoreInt(unlockInterruptMask);
}

void Cache_DrainAndCompactResources(s32 unusedHeap) {
    s32 lockUsers;
    s32 remainingLockUsers;
    u32 mask;
    u32 unlockInterruptMask;

    mask = __osDisableInt();
    lockUsers = g_resourceHeapLockUsers + 1;
    g_resourceHeapLockUsers = lockUsers;
    if (lockUsers != 1) {
        __osRestoreInt(mask);
        osRecvMesg(&g_resourceHeapLockQueue, 0, 1);
    } else {
        __osRestoreInt(mask);
    }
    Cache_WaitForResourceSlotRelease();
    while (Cache_SelectAllocationCandidate(0, 0, 0) != 0) {
    }
    Cache_CompactResourceHeap(0, 1);
    unlockInterruptMask = __osDisableInt();
    remainingLockUsers = g_resourceHeapLockUsers - 1;
    g_resourceHeapLockUsers = remainingLockUsers;
    if (remainingLockUsers != 0) {
        __osRestoreInt(unlockInterruptMask);
        osSendMesg(&g_resourceHeapLockQueue, 0, 1);
        return;
    }
    __osRestoreInt(unlockInterruptMask);
}

void Cache_SelectResourceSlot(s32 cacheContext, s32 resourceSlot) {
    s32 lockClaimCount;
    s32 lockReleaseCount;
    ResourceLockState *base;
    u32 mask;
    u32 releaseInterruptMask;

    mask = __osDisableInt();
    lockClaimCount = g_resourceHeapLockUsers + 1;
    g_resourceHeapLockUsers = lockClaimCount;
    if (lockClaimCount != 1) {
        __osRestoreInt(mask);
        osRecvMesg(&((ResourceLockState *)&g_resourceSlotLockState)->waitQueue, 0, 1);
    } else {
        __osRestoreInt(mask);
    }
    base = (ResourceLockState *)&g_resourceSlotLockState;
    base->slot = resourceSlot;
    g_resourceSlotProtected[resourceSlot] = 1;
    releaseInterruptMask = __osDisableInt();
    lockReleaseCount = g_resourceHeapLockUsers - 1;
    g_resourceHeapLockUsers = lockReleaseCount;
    if (lockReleaseCount != 0) {
        __osRestoreInt(releaseInterruptMask);
        osSendMesg(&base->waitQueue, 0, 1);
        return;
    }
    __osRestoreInt(releaseInterruptMask);
}

s32 Cache_FinishResourceSlot(void) {
    s32 lockClaimCount;
    s32 lockReleaseCount;
    s32 *base;
    u32 mask;
    u32 releaseInterruptMask;
    s32 result;
    int *slot;

    mask = __osDisableInt();
    lockClaimCount = g_resourceHeapLockUsers + 1;
    g_resourceHeapLockUsers = lockClaimCount;
    if (lockClaimCount != 1) {
        __osRestoreInt(mask);
        osRecvMesg((&((ResourceLockState *)&g_resourceSlotLockState)->waitQueue), 0, 1);
    } else {
        __osRestoreInt(mask);
    }
    base = &g_resourceSlotLockState;
    slot = &g_resourceSlotProtected[*base];
    result = *slot;
    *base = -1;
    releaseInterruptMask = __osDisableInt();
    lockReleaseCount = g_resourceHeapLockUsers - 1;
    g_resourceHeapLockUsers = lockReleaseCount;
    if (lockReleaseCount != 0) {
        __osRestoreInt(releaseInterruptMask);
        osSendMesg(&((ResourceLockState *)base)->waitQueue, 0, 1);
    } else {
        __osRestoreInt(releaseInterruptMask);
    }
    return result;
}

void Cache_MarkResourceInUse(s32 cacheContext, CacheResourceNode *resource) {
    s32 index;
    s32 mask;
    s32 flags;
    s32 counter;
    s32 counter2;
    s32 *base;
    u32 token;
    u32 token2;

    base = &g_resourceSlotLockState;
    index = *base;
    token = __osDisableInt();
    counter = g_resourceHeapLockUsers + 1;
    g_resourceHeapLockUsers = counter;
    if (counter != 1) {
        __osRestoreInt(token);
        osRecvMesg((&((ResourceLockState *)base)->waitQueue), 0, 1);
    } else {
        __osRestoreInt(token);
    }

    if (g_resourceSlotProtected[index] != 0) {
        mask = 0x200;
        if (index != 0) {
            mask = 0x400;
        }
        flags = resource->flags;
        if (!(flags & mask)) {
            resource->flags = flags | mask;
            g_resourceSlotActivity[index]++;
        }
    }

    token2 = __osDisableInt();
    counter2 = g_resourceHeapLockUsers - 1;
    g_resourceHeapLockUsers = counter2;
    if (counter2 != 0) {
        __osRestoreInt(token2);
        osSendMesg(&g_resourceHeapLockQueue, 0, 1);
        return;
    }
    __osRestoreInt(token2);
}

/* CACHE.CPP */

void Cache_SendCompletionMessage(s32 unusedCache, s32 message)
{
    osSendMesg(&(*(int *)&g_resourceRequestManager), message, 1);
}

/* Allocates a four-byte probe from Cache_RequestResource to read a count, frees it under the g_resourceHeapLockUsers lock, then allocates count*4+15 rounded to eight bytes and stores its first word through handle, returning the allocation. */

void Cache_ReplaceResourceBlock(s32 cacheContext, struct CacheResourceNode **handle, struct CacheResourceNode *replacement) {
    s32 counter;
    s32 counter2;
    s32 count;
    struct CacheResourceNode *node;
    u32 token;
    u32 token2;

    token = __osDisableInt();
    counter = g_resourceHeapLockUsers + 1;
    g_resourceHeapLockUsers = counter;
    if (counter != 1) {
        __osRestoreInt(token);
        osRecvMesg(&g_resourceHeapLockQueue, 0, 1);
    } else {
        __osRestoreInt(token);
    }

    node = *handle;
    node->flags &= ~2;
    if (node->references != 0) {
        loop_1:
        do {
            count = node->references - 1;
            node->references = count;
            if (count != 0) {
                goto loop_1;
            }
            node->flags &= ~0x100;
        } while (node->references != 0);
    }
    if (!(node->flags & 0x702)) {
        Cache_DetachResourceRequest(0, node);
        Heap_FreeAllocation(&g_runtimeHeap, node->data);
        Cache_ReleasePendingResourceEntry(0, node);
    }
    *handle = replacement;

    token2 = __osDisableInt();
    counter2 = g_resourceHeapLockUsers - 1;
    g_resourceHeapLockUsers = counter2;
    if (counter2 != 0) {
        __osRestoreInt(token2);
        osSendMesg(&g_resourceHeapLockQueue, 0, 1);
        return;
    }
    __osRestoreInt(token2);
}

void Cache_ReplaceResourcePairFirst(s32 unusedCache, ResourceNodePair *resourcePair, CacheResourceNode *replacementResource) {
    s32 lockClaimCount;
    s32 lockReleaseCount;
    u32 mask;
    u32 releaseInterruptMask;
    ResourceNodePair *pairToUpdate;
    CacheResourceNode *newFirstResource;
    CacheResourceNode *node;

    pairToUpdate = resourcePair;
    newFirstResource = replacementResource;
    mask = __osDisableInt();
    lockClaimCount = g_resourceHeapLockUsers + 1;
    g_resourceHeapLockUsers = lockClaimCount;
    if (lockClaimCount != 1) {
        __osRestoreInt(mask);
        osRecvMesg(&g_resourceHeapLockQueue, 0, 1);
    } else {
        __osRestoreInt(mask);
    }

    node = pairToUpdate->first;
    if (node != 0) {
        node->references -= 1;
        if (node->references == 0) {
            node->flags &= ~0x100;
        }
    }
    node = pairToUpdate->second;
    if (node != 0) {
        node->references -= 1;
        if (node->references == 0) {
            node->flags &= ~0x100;
        }
    }
    pairToUpdate->first = newFirstResource;

    releaseInterruptMask = __osDisableInt();
    lockReleaseCount = g_resourceHeapLockUsers - 1;
    g_resourceHeapLockUsers = lockReleaseCount;
    if (lockReleaseCount != 0) {
        __osRestoreInt(releaseInterruptMask);
        osSendMesg(&g_resourceHeapLockQueue, 0, 1);
        return;
    }
    __osRestoreInt(releaseInterruptMask);
}

void Cache_TouchResourceByKey(s32 unusedCache, s32 resourceKey) {
    s32 lockClaimCount;
    s32 lockReleaseCount;
    u32 mask;
    u32 releaseInterruptMask;
    HashNode *node;
    void *value;
    void **out;

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
        ((u32)resourceKey >> 17)) & g_resourceHashEvenIndexMask) * 16));
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

    if (value != 0) {
        void *object = *(void **)value;
        ((CachedResource *)object)->stamp = g_resourceCacheManager.activity.count;
        List_MoveIntrusiveToHead(&g_resourceCacheManager.entries, object);
    }

    releaseInterruptMask = __osDisableInt();
    lockReleaseCount = g_resourceHeapLockUsers - 1;
    g_resourceHeapLockUsers = lockReleaseCount;
    if (lockReleaseCount != 0) {
        __osRestoreInt(releaseInterruptMask);
        osSendMesg(&g_resourceHeapLockQueue, 0, 1);
        return;
    }
    __osRestoreInt(releaseInterruptMask);
}

void **Cache_RequestWordCountedResource(s32 unusedCache, void **resourceHandle, s32 resourceKey, void *loadTag, s32 direct) {
    void **resource;
    s32 size;
    s32 counter;
    s32 counter2;
    u32 token;
    u32 token2;

    resource = Cache_RequestResource(0, resourceKey, resourceKey, 4, 0, 0, 0, &s_headerText, direct);
    if (resource != 0) {
        size = **(s32 **)resource;
        token = __osDisableInt();
        counter = g_resourceHeapLockUsers + 1;
        g_resourceHeapLockUsers = counter;
        if (counter != 1) {
            __osRestoreInt(token);
            osRecvMesg(&g_resourceHeapLockQueue, 0, 1);
        } else {
            __osRestoreInt(token);
        }
        Cache_ReleaseResourceCompletely(0, resource);
        token2 = __osDisableInt();
        counter2 = g_resourceHeapLockUsers - 1;
        g_resourceHeapLockUsers = counter2;
        if (counter2 != 0) {
            __osRestoreInt(token2);
            osSendMesg(&g_resourceHeapLockQueue, 0, 1);
        } else {
            __osRestoreInt(token2);
        }
        resource = Cache_RequestResource(0, resourceKey, resourceKey, ((size * 4) + 15) & ~7,
            0, 0, 0, loadTag, direct);
        if (resource != 0) {
            *resourceHandle = *resource;
            return resource;
        }
    }
    return 0;
}

s32 Cache_RequestWordCountedResourcePinned(s32 unusedCache, void **handle, s32 resourceKey, void *loadTag) {
    void **resource;
    s32 size;
    s32 counter;
    s32 counter2;
    u32 token;
    u32 token2;
    s32 one = 1;

    resource = Cache_RequestResource(0, resourceKey, resourceKey, 4, 27, 0, 0, &s_headerText, one);
    size = **(s32 **)resource;
    token = __osDisableInt();
    counter = g_resourceHeapLockUsers + one;
    g_resourceHeapLockUsers = counter;
    if (counter != one) {
        __osRestoreInt(token);
        osRecvMesg(&g_resourceHeapLockQueue, 0, one);
    } else {
        __osRestoreInt(token);
    }
    Cache_ReleaseResourceCompletely(0, resource);
    token2 = __osDisableInt();
    counter2 = g_resourceHeapLockUsers - 1;
    g_resourceHeapLockUsers = counter2;
    if (counter2 != 0) {
        __osRestoreInt(token2);
        osSendMesg(&g_resourceHeapLockQueue, 0, 1);
    } else {
        __osRestoreInt(token2);
    }
    resource = Cache_RequestResource(0, resourceKey, resourceKey, ((size * 4) + 15) & ~7, 27, 0, 0, loadTag, 1);
    *handle = *resource;
    return (s32)resource;
}

void **Cache_RequestPackSection(s32 unusedCache, void *handle, s32 sectionSelector, s32 resourceKey, void *world, void *resourceTag, void *loadTag) {
    s32 sectionByteCount;
    s32 sectionSource;

    sectionSource = SetN64_LocatePackSection(handle, resourceKey, sectionSelector, &sectionByteCount);
    return (void **)Cache_RequestResource(0, sectionSource, sectionSource, sectionByteCount, 27, world, resourceTag, loadTag, 1);
}

/* CACHE_ALLOCRESOURCEBLOCK.CPP */

struct CacheResourceNode *Cache_AllocResourceBlock(s32 unusedCache, void *handle, s32 total) {
    struct CacheResourceNode *node;
    s32 result;
    s32 counter;
    s32 counter2;
    u32 token;
    u32 token2;
    u32 flags;

    token = __osDisableInt();
    counter = g_resourceHeapLockUsers + 1;
    g_resourceHeapLockUsers = counter;
    if (counter != 1) {
        __osRestoreInt(token);
        osRecvMesg(&g_resourceHeapLockQueue, 0, 1);
    } else {
        __osRestoreInt(token);
    }
    flags = ((ResourceLoadRequest *)handle)->mode;
    node = Cache_AcquireResourceNodeWithEviction(0, flags);
    if (node != 0) {
        node->references++;
        node->flags |= 0x100;
        result = ((s32 (*)(s32, s32, s32, u32))Cache_AllocateHeapWithEviction)(0, total, (flags >> 5) & 1, flags);
        node->data = result;
        if (result != 0) {
            node->size = total;
            node->flags |= flags;
            Cache_InsertResourceByAddress(0, node);
        } else {
            node->references--;
            if (node->references == 0) {
                node->flags &= ~0x100;
            }
            Cache_ReleasePendingResourceEntry(0, node);
            node = 0;
        }
    }
    token2 = __osDisableInt();
    counter2 = g_resourceHeapLockUsers - 1;
    g_resourceHeapLockUsers = counter2;
    if (counter2 != 0) {
        __osRestoreInt(token2);
        osSendMesg(&g_resourceHeapLockQueue, 0, 1);
    } else {
        __osRestoreInt(token2);
    }
    return node;
}

struct CacheResourceNode *Cache_AllocatePinnedResourceBlock(s32 cacheContext, s32 handle, s32 byteCount) {
    struct CacheResourceNode *node;
    s32 result;
    s32 counter;
    s32 counter2;
    u32 token;
    u32 token2;

    token = __osDisableInt();
    counter = g_resourceHeapLockUsers + 1;
    g_resourceHeapLockUsers = counter;
    if (counter != 1) {
        __osRestoreInt(token);
        osRecvMesg(&g_resourceHeapLockQueue, 0, 1);
    } else {
        __osRestoreInt(token);
    }
    node = Cache_AcquireResourceNodeWithEviction(0, 34U);
    if (node != 0) {
        node->references++;
        node->flags |= 0x100;
        result = ((s32 (*)(s32, s32, s32, u32))Cache_AllocateHeapWithEviction)(0, byteCount, 1, 34U);
        node->data = result;
        if (result != 0) {
            node->size = byteCount;
            node->flags |= 0x22;
            Cache_InsertResourceByAddress(0, node);
        } else {
            node->references--;
            if (node->references == 0) {
                node->flags &= ~0x100;
            }
            Cache_ReleasePendingResourceEntry(0, node);
            node = 0;
        }
    }
    token2 = __osDisableInt();
    counter2 = g_resourceHeapLockUsers - 1;
    g_resourceHeapLockUsers = counter2;
    if (counter2 != 0) {
        __osRestoreInt(token2);
        osSendMesg(&g_resourceHeapLockQueue, 0, 1);
    } else {
        __osRestoreInt(token2);
    }
    return node;
}

/** Set the global resource activity state. */
void Cache_SetResourceActivityState(unsigned int value) {
    g_resourceCacheManager.activity.active = value;
}

int Cache_GetResourceActivityState(void) {
    return g_resourceCacheManager.activity.active;
}

/** Return how many resource requests are still pending. */

int Cache_GetPendingRequestCount(void) {
    return g_resourcePendingRequestCount;
}

int Cache_GetFreeResourceNodeCount(void) {
    return g_resourceCacheManager.count;
}

/** Return the global word at g_resourceEntryCount. */

int Cache_GetResourceEntryCount(void) {
    return g_resourceEntryCount;
}

/** Return how many resource entries are in the cache. */

int Cache_ReadResourceEntryCount(void) {
    return g_resourceEntryCount;
}

int Cache_QueryResourceEntryCount(void) {
    return g_resourceEntryCount;
}

int Cache_ReturnZero(void) {
    return 0;
}

/* Frees a block from Cache_AllocateMemory: releases the heap node stored 16 bytes before it under the heap lock. */
void Cache_FreeMemory(void *allocation) {
    s32 lockUsers;
    s32 remainingLockUsers;
    u32 mask;
    u32 unlockInterruptMask;
    void *resource;

    resource = ((void **)allocation)[-4];
    mask = __osDisableInt();
    lockUsers = g_resourceHeapLockUsers + 1;
    g_resourceHeapLockUsers = lockUsers;
    if (lockUsers != 1) {
        __osRestoreInt(mask);
        osRecvMesg(&g_resourceHeapLockQueue, 0, 1);
    } else {
        __osRestoreInt(mask);
    }
    Cache_ReleaseResourceCompletely(0, resource);
    unlockInterruptMask = __osDisableInt();
    remainingLockUsers = g_resourceHeapLockUsers - 1;
    g_resourceHeapLockUsers = remainingLockUsers;
    if (remainingLockUsers != 0) {
        __osRestoreInt(unlockInterruptMask);
        osSendMesg(&g_resourceHeapLockQueue, 0, 1);
        return;
    }
    __osRestoreInt(unlockInterruptMask);
}

struct CacheResourceNode *Cache_AllocateResourceNodeStorage(s32 arg0_unused, s32 byteCount, u32 allocationFlags) {
    struct CacheResourceNode *node;
    s32 result;

    node = Cache_AcquireResourceNodeWithEviction(0, allocationFlags);
    if (node != 0) {
        node->references++;
        node->flags |= 0x100;
        result = ((s32 (*)(s32, s32, s32, u32))Cache_AllocateHeapWithEviction)(0, byteCount, (allocationFlags >> 5) & 1, allocationFlags);
        node->data = result;
        if (result != 0) {
            node->size = byteCount;
            node->flags |= allocationFlags;
            Cache_InsertResourceByAddress(0, node);
            return node;
        }
        node->references--;
        if (node->references == 0) {
            node->flags &= ~0x100;
        }
        Cache_ReleasePendingResourceEntry(0, node);
        node = 0;
    }
    return node;
}

/* CACHE_ALLOCATEHEAPWITHEVICTION.CPP */

void Cache_ReleaseResourceCompletely(void *cacheContext, struct IntrusiveList *resource) {
    s32 remainingReferences;

    resource->nextOffset = resource->nextOffset & ~2;
    if (resource->prevOffset != 0) {
        loop_1:
        do {
            remainingReferences = resource->prevOffset - 1;
            resource->prevOffset = remainingReferences;
            if (remainingReferences != 0) {
                goto loop_1;
            }
            resource->nextOffset = resource->nextOffset & ~0x100;
        } while (resource->prevOffset != 0);
    }
    if (!(resource->nextOffset & 0x702)) {
        Cache_DetachResourceRequest(0, resource);
        Heap_FreeAllocation(&g_runtimeHeap, *(s32 *) resource);
        Cache_ReleasePendingResourceEntry(0, resource);
    }
}

void *Cache_AcquirePendingResourceEntry(s32 cacheContext, s32 requestFlags) {
    struct CMemEntry *cacheEntry;

    if (g_resourceCacheManager.count == 0) {
        return 0;
    }
    g_resourceCacheManager.count -= 1;
    cacheEntry = g_resourceCacheManager.slots[g_resourceCacheManager.count];
    cacheEntry->flags = 0x800;
    cacheEntry->references = 0;
    cacheEntry->resource = 0;
    cacheEntry->callback = 0;
    cacheEntry->pending = 0;
    cacheEntry->owner = 0;
    cacheEntry->lastUsed = g_resourceCacheManager.activity.count;
    List_PrependIntrusive(&g_resourceCacheManager.entries, cacheEntry);
    cacheEntry->flags |= (requestFlags & 0xC);
    return cacheEntry;
}

void Cache_ReleasePendingResourceEntry(s32 cacheContext, s32 entryAddress) {
    List_RemoveIntrusive(&g_resourceCacheManager.entries, entryAddress);
    if (((CachedResource *)entryAddress)->flags & 0x1000) {
        List_RemoveIntrusive(&g_resourceCacheManager.recent, entryAddress);
    }
    if (g_resourceCacheManager.reservedWord8 == entryAddress) {
        g_resourceCacheManager.reservedWord8 = 0;
    }
    ((CachedResource *)entryAddress)->flags = 0;
    g_resourceCacheManager.slots[g_resourceCacheManager.count] = (void *)entryAddress;
    g_resourceCacheManager.count += 1;
}

int Cache_SelectAllocationCandidate(int cacheContext, int keepRecent, int allocationFlags) {
    int effectiveKeepRecent = keepRecent;
    if (allocationFlags & 0x10) {
        effectiveKeepRecent = 0;
    }
    return Cache_EvictResource(0, 2, effectiveKeepRecent);
}

void *Cache_AllocateHeapWithEviction(s32 unusedCache, u32 byteCount, s32 allocatorSelection, u32 evictionFlags)
{
    void *result;
    s32 value;
    if (allocatorSelection != 0)
    {
        result = Heap_AllocateFromBack(&g_runtimeHeap, byteCount);
    }
    else
    if (value)
    {
        result = Heap_AllocateFromFront(&g_runtimeHeap, byteCount);
    }
    else
    {
        result = Heap_AllocateFromFront(&g_runtimeHeap, byteCount);
    }
    if (result == 0)
    {
        evictionFlags &= 0x10;
        do
        {
            value = Cache_EvictResource(0, 2, evictionFlags == 0);
        }
        while ((value != 0) && (value < byteCount));
        if (value >= byteCount)
        {
            if (allocatorSelection != 0)
            {
                result = Heap_AllocateFromBack(&g_runtimeHeap, byteCount);
            }
            else
            {
                result = Heap_AllocateFromFront(&g_runtimeHeap, byteCount);
            }
        }
    }
    return result;
}

void Cache_InsertResourceByAddress(s32 cacheContext, void *object) {
    CacheEvictionNode *node = object;
    CacheEvictionNode *scan;

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
}

void Cache_ClearCurrentResourceSlot(void) {
    s32 *p = &g_resourceSlotLockState;
    Cache_ClearResourceSlotProtection(0, *p);
    g_resourceSlotProtected[*p] = 0;
}

/* CACHE_ACQUIRELOADREQUESTWITHEVICTION.CPP */

/* Obtains a free node, marks it active and moves it to the active list, retrying while processing permits. */

static inline ResourceLoadRequest *take(s32 active) {
 ResourceLoadRequest *node=g_resourceAvailableRequests.head;
 if(node) {List_RemoveIntrusive(&g_resourceAvailableRequests,node); node->flags=active;List_PrependIntrusive(&g_resourcePendingRequests,node);}
 return node;
}

/* Finds an evictable entry of a list: skips entries flagged 0x702 and returns the first one untouched for at least five ticks of g_resourceCacheManager.activity.count, remembering the first recently used candidate in *recent when that slot is still empty; returns null when none qualifies. */

void Cache_ClearResourceSlotProtection(s32 unusedCache, s32 resourceSlot)
{
    s32 mask;
    u32 count;
    u32 nodeLimit;

    mask = -0x201;
    if (resourceSlot != 0) {
        mask = -0x401;
    }
    nodeLimit = g_resourceCacheNodeCapacity;
    for (count = 0; count < nodeLimit; count++) {
        ((CacheEvictionNode *)g_resourceCacheManager.nodes)[count].flags &= mask;
    }
    g_resourceSlotActivity[resourceSlot] = 0;
}

void Cache_TouchResource(void *cacheContext, void *resource) {
    CMemEntry *animationResource = resource;
    s32 *p = g_resourceCacheFrameStamp;
    animationResource->lastUsed = *p;
    List_MoveIntrusiveToHead((char *)p - (((char *)&((struct ResMgr *)0)->activity.count - (char *)0) - ((char *)&((struct ResMgr *)0)->entries - (char *)0)), (s32)resource);
}

/* Releases the load request owning a cache entry. One pointer walks from the entry to its owner request, so the
 * entry's register is reused for the request once the hash key is dropped. */
void Cache_DetachResourceRequest(void *cacheContext, void *resourceCacheEntry) {
    void *link = resourceCacheEntry;

    if (((CMemEntry *)link)->owner != 0) {
        HashTable_RemoveResourceByKey(((ResourceLoadRequest *)((CMemEntry *)link)->owner)->key);
        link = ((CMemEntry *)link)->owner;
        List_RemoveIntrusive(&g_resourceCacheManager.activeRequests, link);
        ((ResourceLoadRequest *)link)->flags = 0;
        List_PrependIntrusive(&g_resourceCacheManager.freeLinks, link);
    }
}

void *Cache_AcquireLoadRequest(void) {
    IntrusiveList *p = &g_resourceCacheManager.freeLinks;
    void *head = p->head;
    if (head != 0) {
        List_RemoveIntrusive(p, head);
        ((ResourceLoadRequest *)head)->flags = 1;
        List_PrependIntrusive(&g_resourceCacheManager.activeRequests, head);
    }
    return head;
}

void Cache_RecycleLoadRequest(s32 cacheContext, void *request) {
    List_RemoveIntrusive(&g_resourceCacheManager.activeRequests, request);
    ((RequestCacheRunResourceCompletionWorker *)request)->flags = 0;
    List_PrependIntrusive(&g_resourceCacheManager.freeLinks, request);
}

void *Cache_AcquireLoadRequestWithEviction(s32 cacheContext,s32 flags) {
 ResourceLoadRequest *node=take(1);
 if (!node) {
  s32 active=1;
  flags &= 0x10;
  while(Cache_EvictResource(0,2,flags==0)) {node=take(active);if(node)break;}
 }
 return node;
}

void Cache_AcknowledgeResourceSlotRelease(s32 cacheContext, s32 request) {
    s32 mask;
    u32 count;
    u32 nodeLimit;

    if (g_resourceSlotOwners[request] != 0) {
        g_resourceSlotOwners[request] = 0;
        osSendMesg(&g_resourceCompletionWakeQueue, 0, 1);
    }
    mask = -0x201;
    if (request != 0) {
        mask = -0x401;
    }
    nodeLimit = g_resourceCacheNodeCapacity;
    for (count = 0; count < nodeLimit; count++) {
        ((CacheEvictionNode *)g_resourceCacheManager.nodes)[count].flags &= mask;
    }
    do { g_resourceSlotActivity[request] = 0; } while (0);
}

CacheEvictionEntry *Cache_FindEvictableResource(s32 cacheContext, EntryList *list, CacheEvictionEntry **recent)
{
    CacheEvictionEntry *e = list->first;

    if (*recent == 0) {
        for (; e != 0; e = e->next) {
            if (!(e->flags & 0x702)) {
                if ((u32)(g_resourceCacheManager.activity.count - e->stamp) >= 5) {
                    return e;
                }
                *recent = e;
                break;
            }
        }
    }
    for (; e != 0; e = e->next) {
        if (!(e->flags & 0x702) && (u32)(g_resourceCacheManager.activity.count - e->stamp) >= 5) {
            return e;
        }
    }
    return 0;
}

#if defined(VERSION_US)
/* Bytes the original holds up to the next 16-byte object boundary; no instruction reads them. */
unsigned int g_cacheAcquireLoadRequestWithEvictionZeroTail[1] = {
    0x00000000,
};
#endif

/* CACHE_REPLACERESOURCEBLOCK.CPP */

const char s_headerText[7] = "header\000";

/* CACHE_ALLOCATEMEMORY.CPP */

#if defined(VERSION_DE) || defined(VERSION_EU_X) || defined(VERSION_US)
const char g_allocText[6] = "alloc\000";
#endif

#if defined(VERSION_EU)
const char g_allocText[8] =
    "alloc\000\000\000";
#endif

#if defined(VERSION_US_REV1)
const char s_allocText[6] = "alloc";
#endif

/* G_OVERLAYTWORESOURCEHALFWORD.CPP */

#if defined(VERSION_US_REV1)
unsigned short g_cacheResourceHalfword[1] __attribute__((aligned(2))) = { 0x4461 };
#endif
