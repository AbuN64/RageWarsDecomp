#ifndef ENGINE_CACHE_CACHE_ALLOCRESOURCEBLOCK_H
#define ENGINE_CACHE_CACHE_ALLOCRESOURCEBLOCK_H
#include "Engine/Cache/cache.h"
#include "Engine/Cache/cache_runcompactionpasses.h"
#include "Cache/cache_allocresourceblock.h"
#include "Common/manager.h"
#include "Common/runtime_declarations.h"
#include "Common/sharedplayer.h"
#include "Common/resourcelockstate.h"
#include "Common/boot_memory_and_thread_boundaries.h"
#include "types.h"
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "Scene/cache_freememory.h"
extern OSMesgQueue g_resourceHeapLockQueue;
extern void *Cache_AcquireResourceNodeWithEviction(s32 cacheContext, s32 flags);
extern void Cache_InsertResourceByAddress(s32 cacheContext, void *object);
extern void Cache_ReleasePendingResourceEntry(s32 cacheContext, s32 entryAddress);


struct CacheResourceNode;
extern struct CacheResourceNode *Cache_AllocatePinnedResourceBlock(s32 unusedFirst, s32 unusedSecond, s32 byteCount);
#endif
