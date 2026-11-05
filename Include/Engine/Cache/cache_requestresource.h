#ifndef ENGINE_CACHE_CACHE_REQUESTRESOURCE_H
#define ENGINE_CACHE_CACHE_REQUESTRESOURCE_H
#include "Engine/Cache/cache.h"
#include "Audio/hashtable.h"
#include "Common/boot_memory_and_thread_boundaries.h"
#include "Common/Lone/resource_request_queue.h"
#include "Common/manager.h"
#include "Common/cartridgereadworker.h"
#include "Common/trigger_and_float_value_operations.h"
#include "Common/controller_motor_state.h"
#include "Common/os_timer_interrupt_internals.h"
#include "Common/heap_arena_entry.h"
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "Texture/cache_recycleloadrequest.h"
#include "Engine/Cache/list.h"
#include "Engine/Cache/decmprsr.h"
#include "Engine/Cache/loader.h"
#include "Common/heap_arena.h"
struct Manager;
struct ResourceLoadRequest;
extern struct Manager g_resourceRequestManager;
extern s32 g_resourceRecencyList;
extern struct CartridgeReadWorker g_cartridgeReadWorker;
extern void *Cache_AcquireLoadRequestWithEviction(s32, s32);
extern void *Cache_AcquireResourceNodeWithEviction(s32, s32);
extern void Cache_ReleasePendingResourceEntry(s32 cacheContext, s32 entryAddress);
extern void Cache_InsertResourceByAddress(s32 cacheContext, void *object);
extern struct ResourceLoadRequest *Cache_FinalizeResourceLoad(s32 cacheContext, struct ResourceLoadRequest *request, s32 dropReference);
#endif
