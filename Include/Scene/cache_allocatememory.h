#ifndef SCENE_CACHE_ALLOCATEMEMORY_H
#define SCENE_CACHE_ALLOCATEMEMORY_H
#include "Common/manager.h"
struct CacheResourceNode;
extern int Cache_IsResourceRetained(void *resource);
extern void Cache_RetainResource(struct CacheResourceNode *resource);
extern void Cache_ReleaseResourceReference(struct CacheResourceNode *resource);
extern OSMesgQueue g_resourceHeapLockQueue;
#include "Engine/Cache/cache.h"

extern s32 Cache_SelectAllocationCandidate(s32, s32, s32);
#endif
