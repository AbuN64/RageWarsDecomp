#ifndef ENGINE_CACHE_H
#define ENGINE_CACHE_H
#include "Cache/cache_allocresourceblock.h"
#include "types.h"

struct HashNode {
    s32 key;
    void *value;
    s32 reservedWord1;
    struct HashNode *next;
};
typedef struct HashNode HashNode;



struct CacheResourceNode;
extern void Cache_LockResource(void *cacheContext, struct CacheResourceNode *resource);
extern void Cache_DrainAndCompactResources(s32 unusedHeap);
#endif
