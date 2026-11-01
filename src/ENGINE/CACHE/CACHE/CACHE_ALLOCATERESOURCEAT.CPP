#include "COMMON/MANAGER.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RESOURCELOCKSTATE.H"
#include "SCENE/RESOURCE_BINDING_AND_FADE_VIEWS.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "TYPES.H"
#include "ENGINE/CACHE/CACHE.H"
#include "SCENE/CACHE_ALLOCATERESOURCEAT.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>



extern struct CacheResourceBlockView *Cache_AllocateResourceNodeStorage(s32, s32, u32, void *);

extern s8 g_runtimeHeap;

extern struct CacheResourceBlockView *Cache_AcquireResourceNodeWithEviction(s32, u32);

extern s32 Heap_AllocateAtAddress(s8 *, void *, s32);

extern void Cache_InsertResourceByAddress(s32 unused, void *object);

extern void Cache_ReleasePendingResourceEntry(s32 unused0, s32 entryAddress);

extern void Cache_TouchResource(void *, CacheResourceNode *);

extern void Cache_ReleaseResourceCompletely(void *, void *);

extern void Cache_WaitForResourceSlotRelease(s32);

extern s32 Cache_SelectAllocationCandidate(s32, s32, s32);



extern s32 g_resourceSlotActivity[];

struct CacheResourceBlockView *Cache_AllocateResource(s32 unusedCache, s32 byteCount, u32 allocationFlags, void *context) {
    extern OSMesgQueue g_resourceHeapLockQueue;
    struct CacheResourceBlockView *resource;
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
    resource = Cache_AllocateResourceNodeStorage(0, requestedBytes, requestedFlags, evictedResource);
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

struct CacheResourceBlockView *Cache_AllocateResourceAt(void *address, void *requestedAddress, s32 byteCount, char *name) {
    extern OSMesgQueue g_resourceHeapLockQueue;
    struct CacheResourceBlockView *allocatedResource;
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
        allocatedResource->first = allocatedAddress;
        if (allocatedAddress != 0) {
            allocatedResource->second = byteCount;
            allocatedResource->fourth |= 3;
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
    extern OSMesgQueue g_resourceHeapLockQueue;
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
    extern OSMesgQueue g_resourceHeapLockQueue;
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
    extern OSMesgQueue g_resourceHeapLockQueue;
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
    extern OSMesgQueue g_resourceHeapLockQueue;
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
    Cache_WaitForResourceSlotRelease(0);
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

void Cache_SelectResourceSlot(s32 unused, s32 resourceSlot) {
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
    result = *(s32 *)((char *)g_resourceSlotProtected + (*base << 2));
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

void Cache_MarkResourceInUse(s32 unused0, CacheResourceNode *resource) {
    extern OSMesgQueue g_resourceHeapLockQueue;
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
