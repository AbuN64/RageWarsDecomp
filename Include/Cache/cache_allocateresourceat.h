#ifndef CACHE_CACHE_ALLOCATERESOURCEAT_H
#define CACHE_CACHE_ALLOCATERESOURCEAT_H
#include "types.h"
struct CacheResourceNode;
extern void Cache_UnlockResource(void *cacheContext, struct CacheResourceNode *resource);
#include "types.h"
struct CacheResourceNode;

#include "types.h"
#include "Common/runtime_declarations.h"
struct CacheResourceNode;
extern void Cache_DrainAndCompactResources(s32 a);

extern void Cache_ReleaseResource(void *cache, void *resource);
extern void Cache_DrainAndCompactResources(s32);
extern void Cache_ReleaseResource(void *, void *);
#endif
