#ifndef ENGINE_CACHE_ALLOCATERESOURCEAT_H
#define ENGINE_CACHE_ALLOCATERESOURCEAT_H
#include "types.h"
struct CacheResourceNode;
extern struct CacheResourceNode *Cache_AllocateResourceAt(void *address, void *requestedAddress, s32 byteCount, char *name);
#endif
