#include "COMMON/MANAGER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RESOURCELOCKSTATE.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "TYPES.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "SCENE/CACHE_FREEMEMORY.H"

/* 802508E0_12.CPP */
extern OSMesgQueue g_resourceHeapLockQueue;

extern struct CacheResourceBlockView *Cache_AcquireResourceNodeWithEviction(s32, u32);

extern void Cache_InsertResourceByAddress(s32 unused, void *object);

extern void Cache_ReleasePendingResourceEntry(s32 unused0, s32 entryAddress);

/** Read the global word at VRAM 0x8010517C. */

/** Read the global word at VRAM 0x8010513C. */

struct CacheResourceBlockView *Cache_AllocResourceBlock(s32 unusedCache, void *handle, s32 total) {
    struct CacheResourceBlockView *node;
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
        node->third++;
        node->fourth |= 0x100;
        result = ((s32 (*)(s32, s32, s32, u32))Cache_AllocateHeapWithEviction)(0, total, (flags >> 5) & 1, flags);
        node->first = result;
        if (result != 0) {
            node->second = total;
            node->fourth |= flags;
            Cache_InsertResourceByAddress(0, node);
        } else {
            node->third--;
            if (node->third == 0) {
                node->fourth &= ~0x100;
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

struct CacheResourceBlockView *Cache_AllocatePinnedResourceBlock(s32 unused0, s32 unused1, s32 byteCount) {
    struct CacheResourceBlockView *node;
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
        node->third++;
        node->fourth |= 0x100;
        result = ((s32 (*)(s32, s32, s32, u32))Cache_AllocateHeapWithEviction)(0, byteCount, 1, 34U);
        node->first = result;
        if (result != 0) {
            node->second = byteCount;
            node->fourth |= 0x22;
            Cache_InsertResourceByAddress(0, node);
        } else {
            node->third--;
            if (node->third == 0) {
                node->fourth &= ~0x100;
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

/** Replace the global object word. */
void Cache_SetResourceActivityState(unsigned int value) {
    extern unsigned int g_resourceActivityState;
    g_resourceActivityState = value;
}

int Cache_GetResourceActivityState(void) {
    extern unsigned int g_resourceActivityState;
    return g_resourceActivityState;
}

/** Read the global word at VRAM 0x80105108. */

int Cache_GetPendingRequestCount(void) {
    return g_resourcePendingRequestCount;
}

int Cache_GetFreeResourceNodeCount(void) {
    return g_resourceFreeNodeCount;
}

/** Return the global word at g_resourceEntryCount. */

int Cache_GetResourceEntryCount(void) {
    return g_resourceEntryCount;
}

/** Read the global word at VRAM 0x80104580. */

int Cache_ReadResourceEntryCount(void) {
    return g_resourceEntryCount;
}

int Cache_QueryResourceEntryCount(void) {
    return g_resourceEntryCount;
}

int Cache_ReturnZero(void) {
    return 0;
}

/* 802508E0_13.CPP */
extern void Cache_ReleaseResourceCompletely(void *, void *);

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

struct CacheResourceBlockView *Cache_AllocateResourceNodeStorage(s32 arg0_unused, s32 byteCount, u32 allocationFlags) {
    struct CacheResourceBlockView *node;
    s32 result;

    node = Cache_AcquireResourceNodeWithEviction(0, allocationFlags);
    if (node != 0) {
        node->third++;
        node->fourth |= 0x100;
        result = ((s32 (*)(s32, s32, s32, u32))Cache_AllocateHeapWithEviction)(0, byteCount, (allocationFlags >> 5) & 1, allocationFlags);
        node->first = result;
        if (result != 0) {
            node->second = byteCount;
            node->fourth |= allocationFlags;
            Cache_InsertResourceByAddress(0, node);
            return node;
        }
        node->third--;
        if (node->third == 0) {
            node->fourth &= ~0x100;
        }
        Cache_ReleasePendingResourceEntry(0, node);
        node = 0;
    }
    return node;
}
