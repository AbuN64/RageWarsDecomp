#include "COMMON/RESOURCELOCKSTATE.H"
#include "TYPES.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "COMMON/MANAGER.H"
#include "COMMON/LONE/RUNTIME_HEAP.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "SCENE/RESOURCE_BINDING_AND_FADE_VIEWS.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "SCENE/CACHE_REQUESTRESOURCE.H"

/* 802508E0_10.CPP */
extern s32 g_resourceRequestManager;
void Cache_SendCompletionMessage(s32 unusedCache, s32 message)
{
  osSendMesg(&g_resourceRequestManager, message, 1);
}

/* 802508E0_11.CPP */
extern void Cache_DetachResourceRequest(void *unused0, void *resourceCacheEntry);

extern void Heap_FreeAllocation(void *arena, s32 dataToFree);

extern void Cache_ReleasePendingResourceEntry(s32 unused0, s32 entryAddress);

extern s32 g_resourceRecencyList;

extern s32 g_resourceCacheFrameStamp;

extern s32 g_resourceHashEvenIndexMask;

extern s32 g_resourceHashBuckets;

extern void List_MoveIntrusiveToHead(void *, s32);

extern void Cache_ReleaseResourceCompletely(void *, void *);

extern const char s_headerText[];

/* Allocates a four-byte probe from Cache_RequestResource to read a count, frees it under the g_resourceHeapLockUsers lock, then allocates count*4+15 rounded to eight bytes and stores its first word through handle, returning the allocation. Adapted from Cache_RequestWordCountedResource with the null checks removed, tag 0x1B and flag 1 passed as the fifth and ninth arguments, and the constant 1 held in a local changed. */

extern s32 SetN64_LocatePackSection(void *directory, s32 bankOffset, s32 sectionIndex, s32 *sectionSizeOut);

void Cache_ReplaceResourceBlock(s32 unused, struct CacheResourceBlockView **handle, struct CacheResourceBlockView *replacement) {
    extern OSMesgQueue g_resourceHeapLockQueue;
    s32 counter;
    s32 counter2;
    s32 count;
    struct CacheResourceBlockView *node;
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
    node->fourth &= ~2;
    if (node->third != 0) {
    loop_1:
        do {
            count = node->third - 1;
            node->third = count;
            if (count != 0) {
                goto loop_1;
            }
            node->fourth &= ~0x100;
        } while (node->third != 0);
    }
    if (!(node->fourth & 0x702)) {
        Cache_DetachResourceRequest(0, node);
        Heap_FreeAllocation(&g_runtimeHeap, node->first);
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
    extern OSMesgQueue g_resourceHeapLockQueue;
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
    extern OSMesgQueue g_resourceHeapLockQueue;
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
        ((CachedResource *)object)->stamp = g_resourceCacheFrameStamp;
        List_MoveIntrusiveToHead(&g_resourceRecencyList, object);
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
    extern OSMesgQueue g_resourceHeapLockQueue;
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
    extern OSMesgQueue g_resourceHeapLockQueue;
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
