#ifndef ENGINE_CACHE_CACHE_H
#define ENGINE_CACHE_CACHE_H
#include "COMMON/MANAGER.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "COMMON/OSTHREAD_S.H"
#include "COMMON/RESOURCELOCKSTATE.H"

struct ResLink {
    s32 reservedWord0;
    s32 reservedWord4;
    s32 reservedWord8;
    s32 reservedWordC;
    s32 owner;
    s32 reservedWord14;
    s32 reservedWord18;
    s32 reservedWord1C;
    s32 reservedWord20;
    s32 nextLink;
    s32 prevLink;
};

struct ResMgr {
    struct CMemEntry *nodes;
    struct CMemEntry **slots;
    s32 reservedWord8;
    struct ResLink *links;
    IntrusiveList entries;
    IntrusiveList recent;
    s32 enabled0;
    s32 enabled1;
    s32 reservedWord40;
    s32 reservedWord44;
    s32 selected;
    u32 reservedWord4C;
    OSThread completionWorker; /* 0x50: osCreateThread destination */
    u8 reservedAfterCompletionWorker[0x398 - 0x50 - sizeof(OSThread)];
    u8 completionWorkerStack[0x800]; /* top at freeLinks, +0xB98 */
    IntrusiveList freeLinks;
    IntrusiveList listBAC;
    IntrusiveList listBC0;
    s32 reservedWordBD4;
    s32 reservedWordBD8;
    s32 count;
    OSMesgQueue heapLockQueue; /* 0xBE0: g_resourceHeapLockQueue */
    OSMesg heapLockMessage;
    s32 heapLockUsers;
    OSMesgQueue lock;
    OSMesg lockSlot[1];
    s32 reservedWordC1C;
    s32 stamp;
};

extern void Cache_ClearCurrentResourceSlot(void);

extern void *Cache_AcquirePendingResourceEntry(s32 unused0, s32 requestFlags);

extern void *Cache_RetainResourceByKey(s32 cache, s32 resourceKey);

extern void Cache_CompactResourceHeap(s32, s32);

extern void Cache_RunResourceCompletionWorker(void *arg);
#endif
