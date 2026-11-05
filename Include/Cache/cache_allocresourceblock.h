#ifndef CACHE_CACHE_ALLOCRESOURCEBLOCK_H
#define CACHE_CACHE_ALLOCRESOURCEBLOCK_H
#include "types.h"
struct Pack;
/* A cache resource node: its heap allocation, byte size, lock count and state flags. */
struct CacheResourceNode {
    void *data;
    s32 size;
    s32 references;
    u32 flags;
};
typedef struct CacheResourceNode CacheResourceNode;
extern void Cache_SetResourceActivityState(unsigned int value);
extern struct CacheResourceNode *Cache_AllocResourceBlock(s32 cache, void *handle, s32 total);
extern s32 Cache_GetResourceActivityState(void);
#endif
