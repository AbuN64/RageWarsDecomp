#include "ENGINE/CACHE/CACHE.H"
#include "COMMON/MANAGER.H"
#include "COMMON/LONE/RUNTIME_HEAP.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"
#include "COMMON/RESOURCELOCKSTATE.H"
#include "COMMON/S1.H"
#include "TYPES.H"
#include "ENGINE/CACHE/LIST.H"
#include "ENGINE/CACHE/LIST.H"


extern void Cache_DetachResourceRequest(void *unused0, struct IntrusiveList *resourceCacheEntry);

extern void Heap_FreeAllocation(void *arena, s32 dataToFree);

extern void Cache_ReleasePendingResourceEntry(s32 unusedCache, s32 entryAddress);


extern s32 g_resourceRecencyList;


extern void *Heap_AllocateFromBack(void *heap, s32 request);

extern void *Heap_AllocateFromFront(void *, s32);

extern void List_InsertBeforeIntrusive(void *, s32, s32);

void Cache_ReleaseResourceCompletely(void *unused, struct IntrusiveList *resource) {
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

void *Cache_AcquirePendingResourceEntry(s32 unused0, s32 requestFlags) {
    extern void **g_resourceFreeNodeStack;
    struct CMemEntry *cacheEntry;
    struct Pool *pool = (struct Pool *)&g_resourceFreeNodeCount;

    if (pool->count == 0) {
        return 0;
    }
    pool->count -= 1;
    cacheEntry = g_resourceFreeNodeStack[g_resourceFreeNodeCount];
    cacheEntry->flags = 0x800;
    cacheEntry->references = 0;
    cacheEntry->resource = 0;
    cacheEntry->callback = 0;
    cacheEntry->pending = 0;
    cacheEntry->owner = 0;
    cacheEntry->lastUsed = pool->useCounter;
    List_PrependIntrusive((char *)pool - (((char *)&((struct ResMgr *)0)->count - (char *)0) - ((char *)&((struct ResMgr *)0)->entries - (char *)0)), cacheEntry);
    cacheEntry->flags |= (requestFlags & 0xC);
    return cacheEntry;
}

void Cache_ReleasePendingResourceEntry(s32 unused0, s32 entryAddress) {
    extern void **g_resourceFreeNodeStack;
    List_RemoveIntrusive((void *)&g_resourceRecencyList, entryAddress);
    if (((CachedResource *)entryAddress)->flags & 0x1000) {
        List_RemoveIntrusive(&((IntrusiveList *)&g_resourceRecencyList)[1], entryAddress);
    }
    if (*(&g_resourceRecencyList - 2) == entryAddress) {
        *(&g_resourceRecencyList - 2) = 0;
    }
    ((CachedResource *)entryAddress)->flags = 0;
    g_resourceFreeNodeStack[((struct Pool *)&g_resourceFreeNodeCount)->count] = (void *)entryAddress;
    *(&g_resourceRecencyList + (((char *)&((struct ResMgr *)0)->count - (char *)0) - ((char *)&((struct ResMgr *)0)->entries - (char *)0)) / sizeof(s32)) += 1;
}

int Cache_SelectAllocationCandidate(int unused, int keepRecent, int allocationFlags) {
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

void Cache_InsertResourceByAddress(s32 unused, void *object) {
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
