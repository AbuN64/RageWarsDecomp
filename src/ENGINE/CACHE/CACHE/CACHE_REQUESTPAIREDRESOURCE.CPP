#include "COMMON/MANAGER.H"
#include "COMMON/LONE/RESOURCE_REQUEST_QUEUE.H"
#include "COMMON/LONE/RUNTIME_HEAP.H"
#include "SCENE/RESOURCE_BINDING_AND_FADE_VIEWS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/S1.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "TYPES.H"
#include "ENGINE/CACHE/CACHE.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "TEXTURE/CACHE_RECYCLELOADREQUEST.H"
#include "ENGINE/CACHE/LIST.H"
#include "ENGINE/CACHE/LIST.H"

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











extern s32 g_resourceRecencyList;

extern s32 g_resourceCacheFrameStamp;

extern s32 g_resourceHashEvenIndexMask;

extern s32 g_resourceHashBuckets;




extern ResourceLoadRequest *Cache_AcquireLoadRequestWithEviction(s32, s32);

extern void Cache_SubmitResourceLoadAndWait(s32 *, ResourceLoadRequest *);

extern void List_MoveIntrusiveToHead(void *, CachedResource *);

extern ResourceLoadRequest *Cache_FinalizeResourceLoad(s32 unused, ResourceLoadRequest *request, s32 dropReference);

static inline void addref(CachedResource *node) {
    node->count += 1;
    node->flags |= 0x100;
}

static inline void stamp(CachedResource *node) {
    node->stamp = g_resourceCacheFrameStamp;
    List_MoveIntrusiveToHead(&g_resourceRecencyList, node);
}

static inline void unref(CachedResource *node) {
    if (--node->count == 0) {
        node->flags &= ~0x100;
    }
}

static inline void acquire(void) {
    extern Manager g_resourceRequestManager;
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
    extern Manager g_resourceRequestManager;
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

/* Runs the resource manager thread: waits for messages on its queue g_resourceRequestManager and, under the manager lock, frees the heap for messages 0 and 1, retries or completes a pending load request (flag 8) by unlinking it, draining its node's reference count, releasing an unused node's data and handle, and finishing the request, or otherwise (flag 4) starts it through Cache_FinalizeResourceLoad. The flag 8 path clears its reference loop with an inner do-while, and each branch unlocks itself. */










extern void Cache_AcknowledgeResourceSlotRelease(s32, RequestCacheRunResourceCompletionWorker *);
extern s32 Cache_TrySubmitResourceLoad(void *, void *, Manager *);

extern void Cache_DetachResourceRequest(s32, NodeCacheRunResourceCompletionWorker *);

extern void Heap_FreeAllocation(void *, void *);

extern void Cache_ReleasePendingResourceEntry(s32 unused0, s32 entryAddress);

static inline void lock(void) {
    extern Manager g_resourceRequestManager;
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
    extern Manager g_resourceRequestManager;
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

CachedResource *Cache_RequestPairedResource(s32 unused, s32 key, CachedResource *first, CachedResource *second, s32 mode, void *owner,
                    void *tag, void *spare, s32 async) {
    extern Manager g_resourceRequestManager;
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
    extern Manager g_resourceRequestManager;
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
