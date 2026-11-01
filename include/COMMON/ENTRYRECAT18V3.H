#ifndef COMMON_ENTRYRECAT18V3_H
#define COMMON_ENTRYRECAT18V3_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"

struct CacheEvictionEntry;
struct CacheEvictionEntry {
    char pad0[0xC];
    s32 flags;
    s32 stamp;
    s32 pad14;
    struct CacheEvictionEntry *next;
};

struct EntryList;
struct CacheEvictionEntry;

struct HeapArena_Heap;
typedef struct HeapArena_Heap HeapArena_Heap;

struct EntryList;
typedef struct EntryList EntryList;


struct CacheHashEntry;
typedef struct CacheHashEntry CacheHashEntry;

struct HeapArenaBlock;
struct HeapArenaBlock {
    struct HeapArenaBlock *prev;
    struct HeapArenaBlock *next;
    struct HeapArenaBlock *prev_phys;
    struct HeapArenaBlock *next_phys;
    s32 offset;
    s32 size;
    u8 allocationPadding[8];
};

struct HeapArenaBlock;
typedef struct HeapArenaBlock HeapArenaBlock;

struct HeapArena_Entryrecat18v3;
struct HeapArena_Entryrecat18v3 {
    s32 reservedWord0;
    s32 reservedWord4;
    HeapArenaBlock *head;
    HeapArenaBlock *tail;
};

struct CacheHashEntry;
struct CacheHashEntry {
    u32 key;
    struct ResourceLoadRequest *value;
    s32 index;
    struct CacheHashEntry *next;
};




struct HeapFreeBlockList;
typedef struct HeapFreeBlockList HeapFreeBlockList;


struct HeapAllocationBlock;
struct HeapAllocationBlock {
    struct HeapAllocationBlock *prevFree;
    struct HeapAllocationBlock *nextFree;
    struct HeapAllocationBlock *prev;
    struct HeapAllocationBlock *next;
    u32 size;
    u32 free;
    u8 reserved18[8];
    u8 data[1]; /* +0x20: allocation payload */
};

struct CacheEvictionEntry;
typedef struct CacheEvictionEntry CacheEvictionEntry;


struct HeapArenaBlock;
struct HeapArena_Heap;





struct Heap;


struct HeapAllocationBlock;
struct HeapFreeBlockList;


struct HeapArena_Entryrecat18v3;
typedef struct HeapArena_Entryrecat18v3 HeapArena_Entryrecat18v3;



struct HeapAllocationBlock;
typedef struct HeapAllocationBlock HeapAllocationBlock;








extern s32 g_resourceLoadIdlePriority;
extern s32 g_resourceLoadPriorityBoost;
extern s32 g_resourceLoadIdlePriority;

extern s32 g_resourceHashIndexMask;
extern CacheHashEntry *g_resourceHashBuckets;
extern s32 g_resourceHashInitialized;
#endif
