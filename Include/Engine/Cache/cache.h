#ifndef ENGINE_CACHE_CACHE_H
#define ENGINE_CACHE_CACHE_H
#include "types.h"
struct IntrusiveList;
struct ResourceNodePair;
extern void Cache_ReleaseResourceCompletely(void *cacheContext, struct IntrusiveList *resource);
#include "types.h"
extern s32 Cache_RequestWordCountedResourcePinned(s32 unusedCache, void **handle, s32 resourceKey, void *loadTag);
#include "Audio/hashtable.h"
#include "Common/manager.h"
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "Common/osthread_s.h"
#include "Common/resourcelockstate.h"
#include "Common/small_records.h"

struct CacheResourceNode;
struct CachedResource;
struct Manager {
    OSMesgQueue requests;
    OSMesg requestMessages[64];
    u8 requestStorage[2348 - sizeof(OSMesgQueue) - 64 * sizeof(OSMesg)];
    IntrusiveList pending;
    IntrusiveList active;
    char padActive[0x20 - sizeof(IntrusiveList)];
    char lock[24];
    char reservedBytes[0x24];
    s32 mask;
};
struct CacheAllocationNodeView {
    int payload;
    int reservedWord;
    int reservedWord1;
    int reservedWord2;
};
struct ResourceNodePair {
    struct CacheResourceNode *first;
    struct CacheResourceNode *second;
};
/* Resource manager slot and its wait queue (g_resourceSlotLockState / g_resourceHeapLockQueue). */
typedef struct ResourceLockState {
    s32 slot;
    u8 reserved4[0xB98 - 4];
    OSMesgQueue waitQueue;
} ResourceLockState;
extern struct CachedResource *Cache_RequestPairedResource(s32 cacheContext, s32 key, struct CachedResource *first, struct CachedResource *second, s32 mode, void *owner, void *tag, void *spare, s32 async);

struct ResLink {
    s32 reservedWord0;
    s32 reservedWord4;
    s32 reservedWord8;
    s32 reservedWordC;
    s32 owner;
    s32 reservedWord14;
    s32 reservedWord18;
    s32 reservedWord1C;
    s32 reservedWord20;
    s32 nextLink;
    s32 prevLink;
};

struct ResMgr {
    struct CMemEntry *nodes;
    struct CMemEntry **slots;
    s32 reservedWord8;
    struct ResLink *links;
    IntrusiveList entries;
    IntrusiveList recent;
    s32 enabled0;
    s32 enabled1;
    s32 reservedWord40;
    s32 reservedWord44;
    s32 selected;
    u32 reservedWord4C;
    OSThread completionWorker; /* 0x50: osCreateThread destination */
    u8 reservedAfterCompletionWorker[0x398 - 0x50 - sizeof(OSThread)];
    u8 completionWorkerStack[0x800]; /* grows down toward freeLinks */
    IntrusiveList freeLinks;
    IntrusiveList activeRequests;
    IntrusiveList pendingRequests;
    s32 reservedWordBD4;
    s32 reservedWordBD8;
    s32 count;
    OSMesgQueue heapLockQueue; /* 0xBE0: g_resourceHeapLockQueue */
    OSMesg heapLockMessage;
    s32 heapLockUsers;
    OSMesgQueue lock;
    OSMesg lockSlot[1];
    ResourceManagerState activity; /* 0xC1C: active flag and use stamp */
};

extern void Cache_ClearCurrentResourceSlot(void);

extern void *Cache_AcquirePendingResourceEntry(s32 cacheContext, s32 requestFlags);

extern void *Cache_RetainResourceByKey(s32 cache, s32 resourceKey);

extern void Cache_CompactResourceHeap(s32, s32);

extern void Cache_RunResourceCompletionWorker(void *arg);
struct CacheResourceNode;
void Cache_ReplaceResourceBlock(s32 cacheContext, struct CacheResourceNode **handle, struct CacheResourceNode *replacement);
void **Cache_RequestPackSection(s32 unusedCache, void *handle, s32 sectionSelector, s32 resourceKey, void *world, void *resourceTag, void *loadTag);
extern struct Manager g_resourceRequestManager;
extern void Cache_DetachResourceRequest(void *cacheContext, void *resourceCacheEntry);
#include "Engine/Cache/heap.h"
extern void Cache_ReleasePendingResourceEntry(s32 cacheContext, s32 entryAddress);
extern s32 g_resourceRecencyList;
extern s32 g_resourceCacheFrameStamp;
extern OSMesgQueue g_resourceHeapLockQueue;

extern void Cache_TouchResourceByKey(s32 unusedCache, s32 resourceKey);

extern s32 g_resourceFreeNodeCount;
extern int g_resourceSlotLockState;
extern int g_resourceHeapLockUsers;
extern int g_resourceSlotProtected[];
extern void Cache_WaitForResourceSlotRelease(s32 slot);
extern struct CacheResourceNode *Cache_AllocateResourceNodeStorage(s32 pool, s32 byteCount, u32 allocationFlags, void *evicted);
extern void Cache_ReplaceResourcePairFirst(s32 unusedCache, struct ResourceNodePair *resourcePair, struct CacheResourceNode *replacementResource);
#endif
