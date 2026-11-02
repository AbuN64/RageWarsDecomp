#include "ENGINE/CACHE/CACHE.H"
#include "include_asm.h"
#include "COMMON/ENTRYRECAT18V3.H"
extern s32 g_resourceCacheManager;
#include "TEXTURE/CACHE_RECYCLELOADREQUEST.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/MANAGER.H"
#include "COMMON/TRIPLE.H"
#include <ultra64.h>
#include "TYPES.H"
#include "COMMON/EXTERNS.H"
#include "AUDIO/HASHTABLE.H"
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "ENGINE/CACHE/LIST.H"
#include "ENGINE/CACHE/LIST.H"

extern void List_MoveIntrusiveToHead(void *list, s32 nodeToMove);
extern s32 g_resourceCacheFrameStamp[];


/* Obtains a free node, marks it active and moves it to the active list, retrying while processing permits. */


static inline AnimationResourceHandleView *take(s32 active) {
 AnimationResourceHandleView *node=g_resourceAvailableRequests.head;
 if(node) {List_RemoveIntrusive(&g_resourceAvailableRequests,node); node->resourceHandle=active;List_PrependIntrusive(&g_resourcePendingRequests,node);}
 return node;
}



/* Finds an evictable entry of a list: skips entries flagged 0x702 and returns the first one untouched for at least five ticks of g_resourceCacheFrameStamp, remembering the first recently used candidate in *recent when that slot is still empty; returns null when none qualifies. */







void Cache_ClearResourceSlotProtection(s32 unusedCache, s32 resourceSlot)
{
  s32 mask;
  u32 count;
  int lockUsers;
  u32 nodeLimit;
  s32 offset;
  u32 limit;
  mask = -0x201;
  if (resourceSlot != 0)
  {
    mask = -0x401;
  }
 do { count = 0; limit = g_resourceCacheNodeCapacity; } while (0);
  nodeLimit = limit;
  if (limit != 0)
  {
    offset = count;
    do
    {
      lockUsers = offset + g_resourceCacheManager;
      count += 1;
      *((s32 *) (lockUsers + 12)) &= mask;
      offset += 40;
    }
    while (count < nodeLimit);
  }
  g_resourceSlotActivity[resourceSlot] = 0;
}

void Cache_TouchResource(void *unused0, void *resource) {
    AnimationResourceHandleView *animationResource = resource;
    s32 *p = g_resourceCacheFrameStamp;
    animationResource->resourceHandle = *p;
    List_MoveIntrusiveToHead((char *)p - (((char *)&((struct ResMgr *)0)->stamp - (char *)0) - ((char *)&((struct ResMgr *)0)->entries - (char *)0)), (s32)resource);
}

void Cache_DetachResourceRequest(void *unused0, void *resourceCacheEntry) {
    void *ownerRequest;
    void *requestToRecycle;

    ownerRequest = ((CMemEntry *)resourceCacheEntry)->owner;
    if (ownerRequest != 0) {
        HashTable_RemoveResourceByKey(((ResourceLoadRequest *)ownerRequest)->key);
        requestToRecycle = ((CMemEntry *)resourceCacheEntry)->owner;
        List_RemoveIntrusive(&g_resourcePendingRequests, requestToRecycle);
        ((ResourceLoadRequest *)requestToRecycle)->flags = 0;
        List_PrependIntrusive(&g_resourceAvailableRequests, requestToRecycle);
    }
}

void *Cache_AcquireLoadRequest(void) {
    IntrusiveList *p = &g_resourceAvailableRequests;
    void *head = p->head;
    if (head != 0) {
        List_RemoveIntrusive(p, head);
        ((ResourceLoadRequest *)head)->flags = 1;
        List_PrependIntrusive(((char *)p + sizeof(IntrusiveList)), head);
    }
    return head;
}

void Cache_RecycleLoadRequest(s32 unused0, void *request) {
    List_RemoveIntrusive(&g_resourcePendingRequests, request);
    ((RequestCacheRunResourceCompletionWorker *)request)->flags = 0;
    List_PrependIntrusive((char *)&g_resourcePendingRequests - (((char *)&((struct ResMgr *)0)->listBAC - (char *)0) - ((char *)&((struct ResMgr *)0)->freeLinks - (char *)0)), request);
}

void *Cache_AcquireLoadRequestWithEviction(s32 unused,s32 flags) {
 AnimationResourceHandleView *node=take(1);
 if (!node) {
  s32 active=1;
  flags &= 0x10;
  while(Cache_EvictResource(0,2,flags==0)) {node=take(active);if(node)break;}
 }
 return node;
}

void Cache_AcknowledgeResourceSlotRelease(s32 unused, s32 request) {
    s32 mask;
    u32 count;
    s32 lockUsers;
    u32 nodeLimit;
    s32 offset;
    u32 limit;

    if (g_resourceSlotOwners[request] != 0) {
        g_resourceSlotOwners[request] = 0;
        osSendMesg(&g_resourceCompletionWakeQueue, 0, 1);
    }
    mask = -0x201;
    if (request != 0) {
        mask = -0x401;
    }
    do { count = 0; limit = g_resourceCacheNodeCapacity; } while (0);
    nodeLimit = limit;
    if (limit != 0) {
        offset = count;
        do {
            lockUsers = offset + g_resourceCacheManager;
            count += 1;
            *(s32 *)&((CacheEvictionNode *)lockUsers)->flags &= mask;
            offset += 40;
        } while (count < nodeLimit);
    }
    do { g_resourceSlotActivity[request] = 0; } while (0);
}

CacheEvictionEntry *Cache_FindEvictableResource(s32 unused, EntryList *list, CacheEvictionEntry **recent)
{
    CacheEvictionEntry *e = list->first;

    if (*recent == 0) {
        for (; e != 0; e = e->next) {
            if (!(e->flags & 0x702)) {
                if ((u32)(g_resourceCacheFrameStamp[0] - e->stamp) >= 5) {
                    return e;
                }
                *recent = e;
                break;
            }
        }
    }
    for (; e != 0; e = e->next) {
        if (!(e->flags & 0x702) && (u32)(g_resourceCacheFrameStamp[0] - e->stamp) >= 5) {
            return e;
        }
    }
    return 0;
}

#if defined(VERSION_US)
/* Alignment fill to the next 16-byte object boundary. */
unsigned int g_CacheAcquireloadrequestwithevictionObjectAlignmentPadUs1[1] = {
    0x00000000,
};
#endif

