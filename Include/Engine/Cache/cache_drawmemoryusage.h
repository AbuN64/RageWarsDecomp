#ifndef ENGINE_CACHE_CACHE_DRAWMEMORYUSAGE_H
#define ENGINE_CACHE_CACHE_DRAWMEMORYUSAGE_H
#include "Engine/Cache/cache.h"
#include "Common/Lone/runtime_heap.h"
#include "Common/vector4f.h"
#include "Common/manager.h"
#include "Common/heap_arena.h"
#include "types.h"
#include "Common/externs.h"
#include "Audio/hashtable.h"
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "Texture/cache_recycleloadrequest.h"
#include "Engine/Cache/list.h"
#include "Engine/Cache/list.h"
struct Manager;
extern s32 g_resourceRecencyList;
extern struct Manager g_resourceRequestManager;
#endif
