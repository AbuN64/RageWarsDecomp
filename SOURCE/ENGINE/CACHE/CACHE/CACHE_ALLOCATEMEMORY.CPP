#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/MANAGER.H"
#include "SCENE/RESOURCE_BINDING_AND_FADE_VIEWS.H"
#include "TYPES.H"
#include "ENGINE/CACHE/CACHE.H"
#include "SCENE/CACHE_ALLOCATEMEMORY.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

extern OSMesgQueue g_resourceHeapLockQueue;
extern const char s_allocText[];

extern struct CacheAllocationNodeView *Cache_AllocateResourceNodeStorage(s32, s32, u32, s32 *);
extern void Cache_WaitForResourceSlotRelease(s32);
extern s32 Cache_SelectAllocationCandidate(s32, s32, s32);

/* Allocates size bytes (plus a 16-byte heap header) from the scene heap under the heap lock; when the
   heap is full it purges unused resources and retries. The game uses it as its malloc. */
Record *Cache_AllocateMemory(s32 size) {
    struct CacheAllocationNodeView *node;
    struct CacheAllocationNodeView *current;
    s32 allocation_size;
    s32 counter;
    s32 counter2;
    s32 counter3;
    s32 counter4;
    s32 payload;
    Record *result;
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
    node = Cache_AllocateResourceNodeStorage(0, allocation_size, 51U, &s_allocText);
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
        Cache_WaitForResourceSlotRelease(0);
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
        node = Cache_AllocateResourceNodeStorage(0, allocation_size, 51U, &s_allocText);
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
        result = (Record *)(payload + 16);
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
