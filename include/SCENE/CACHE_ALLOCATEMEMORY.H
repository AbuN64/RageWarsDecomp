#ifndef SCENE_CACHE_ALLOCATEMEMORY_H
#define SCENE_CACHE_ALLOCATEMEMORY_H
#include "COMMON/MANAGER.H"
extern int Cache_IsResourceRetained(void *resource);
extern void Cache_RetainResource(CacheResourceNode *resource);
extern void Cache_ReleaseResourceReference(CacheResourceNode *resource);
#endif
