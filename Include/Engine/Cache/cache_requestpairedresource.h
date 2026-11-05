#ifndef ENGINE_CACHE_CACHE_REQUESTPAIREDRESOURCE_H
#define ENGINE_CACHE_CACHE_REQUESTPAIREDRESOURCE_H
#include "Audio/hashtable.h"
#include "Common/manager.h"
#include "Common/Lone/resource_request_queue.h"
#include "Common/Lone/runtime_heap.h"
#include "Common/heap_arena_entry.h"
#include "Common/boot_memory_and_thread_boundaries.h"
#include "types.h"
#include "Engine/Cache/cache.h"
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "Texture/cache_recycleloadrequest.h"
#include "Engine/Cache/list.h"
#include "Engine/Cache/list.h"
#include "Engine/Cache/decmprsr.h"
#include "Common/heap_arena.h"
struct Manager;
struct ResourceLoadRequest;
extern s32 g_resourceRecencyList;
extern void *Cache_AcquireLoadRequestWithEviction(s32 cacheContext, s32 flags);
extern struct ResourceLoadRequest *Cache_FinalizeResourceLoad(s32 cacheContext, struct ResourceLoadRequest *request, s32 dropReference);
extern void Cache_AcknowledgeResourceSlotRelease(s32 cacheContext, s32 request);
extern void Cache_DetachResourceRequest(void *cacheContext, void *resourceCacheEntry);
extern void Cache_ReleasePendingResourceEntry(s32 cacheContext, s32 entryAddress);
extern struct Manager g_resourceRequestManager;
#endif
