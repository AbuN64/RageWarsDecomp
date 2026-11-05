#ifndef ENGINE_CACHE_CACHE_INITIALIZERESOURCECACHE_H
#define ENGINE_CACHE_CACHE_INITIALIZERESOURCECACHE_H
#include "Audio/hashtable.h"
#include "Defs/defs.h"
#include "../../../sdk/include/thread_queue.h"
#include "Common/manager.h"
#include "Common/effectrender.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Common/runtime_declarations.h"
#include "types.h"
#include "Common/heap_arena_entry.h"
#include "Common/boot_memory_and_thread_boundaries.h"
#include "types.h"
#include "Engine/Cache/cache.h"
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "Engine/Cache/list.h"
#include "Engine/Cache/list.h"
#include "Common/heap_arena.h"
#include "Ui/X_files/x_plus.h"
struct Manager;
struct CMemEntry;
extern OSMesgQueue g_resourceHeapLockQueue;
extern struct CMemEntry **g_resourceFreeNodeStack;
extern s32 g_resourceRecencyList;
extern struct CMemEntry *g_resourceAllocationCandidate;
extern s32 g_Cache_RunResourceCompletionWorkerPackedAddress;
extern s32 addrLow_Cache_RunResourceCompletionWorker;
extern s32 g_resourceCompletionWorkerPriority;
extern s32 g_resourceCompletionWorkerStack;
extern struct Manager g_resourceRequestManager;
extern struct ResMgr g_resourceCacheManager;
extern void Cache_DetachResourceRequest(void *cacheContext, void *resourceCacheEntry);
#endif
