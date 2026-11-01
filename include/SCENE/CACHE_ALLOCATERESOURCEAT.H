#ifndef SCENE_CACHE_ALLOCATERESOURCEAT_H
#define SCENE_CACHE_ALLOCATERESOURCEAT_H
#include "COMMON/RESOURCELOCKSTATE.H"
extern s32 Cache_FinishResourceSlot();
struct CacheResourceNode;
extern void Cache_UnlockResource(void *heap, struct CacheResourceNode *resource);
extern void Cache_MarkResourceInUse(s32 heap, struct CacheResourceNode *resource);
#endif
