#ifndef SCENE_CACHE_ALLOCATERESOURCEAT_H
#define SCENE_CACHE_ALLOCATERESOURCEAT_H
#include "Cache/cache_allocateresourceat.h"
#include "Common/resourcelockstate.h"
extern s32 Cache_FinishResourceSlot();
struct CacheResourceNode;
extern void Cache_MarkResourceInUse(s32 heap, struct CacheResourceNode *resource);
#include "Engine/Cache/cache.h"
extern void *Cache_AcquireResourceNodeWithEviction(s32 cacheContext, s32 flags);
extern s32 Heap_AllocateAtAddress(s8 *, void *, s32);
extern void Cache_InsertResourceByAddress(s32 cacheContext, void *object);
extern void Cache_ReleasePendingResourceEntry(s32 cacheContext, s32 entryAddress);
extern void Cache_TouchResource(void *cacheContext, void *resource);

extern s32 Cache_SelectAllocationCandidate(s32, s32, s32);
extern OSMesgQueue g_resourceHeapLockQueue;
#endif
