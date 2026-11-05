#ifndef ENGINE_CACHE_CACHE_ALLOCATEHEAPWITHEVICTION_H
#define ENGINE_CACHE_CACHE_ALLOCATEHEAPWITHEVICTION_H
#include "Engine/Cache/cache_initializeresourcecache.h"
#include "Engine/Cache/cache.h"
#include "Common/manager.h"
#include "Common/Lone/runtime_heap.h"
#include "Common/vector4f.h"
#include "Common/runtime_declarations.h"
#include "types.h"
#include "Common/resourcelockstate.h"
#include "Common/heap_arena_entry.h"
#include "types.h"
#include "Engine/Cache/list.h"
#include "Engine/Cache/list.h"
#include "Engine/Cache/heap.h"
extern void Cache_DetachResourceRequest(void *cacheContext, void *resourceCacheEntry);
extern void Cache_ReleasePendingResourceEntry(s32 unusedCache, s32 entryAddress);
extern s32 g_resourceRecencyList;
#endif
