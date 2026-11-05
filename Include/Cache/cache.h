#ifndef CACHE_CACHE_H
#define CACHE_CACHE_H
#include "Engine/Cache/cache.h"
#include "types.h"
struct ResourceNodePair; struct CacheResourceNode;
void Cache_ReplaceResourcePairFirst(s32 unusedCache, struct ResourceNodePair *resourcePair, struct CacheResourceNode *replacementResource);


#endif
