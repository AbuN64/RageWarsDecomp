#include "thread_queue.h"
#include "COMMON/OWNERRECAT8V2.H"
#include "SCHED/SKY_POSTSCREENMESSAGE.H"
#include "COMMON/LLDIVRESULT.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "UI/X_FILES/X_PLUS.H"
#include "ENGINE/VIRTUAL/VHANDLER.H"
#include "include_asm.h"
#include "COMMON/DESCRIPTORRECAT29.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "libultra/os/getthreadid.h"
#include "COMMON/VECTOR4F.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "COMMON/CACHE_RELEASERESOURCE.H"
#include "ENGINE/VIRTUAL/VIRTUAL_REGION_AND_PAGER_OPERATIONS.H"
#include "IO/DEBUG_MEMORY.H"
#include "DATA/REST_SOURCE_RECORDS.H"

/* VHANDLER.C */
/* VHANDLER.CPP */
/* Initializes the game state: clears the whole state block and fills its slot and lookup tables
   with 0xFF, resets the 24 player entries and queue slots, sets up the three lists and the stream
   descriptor for the ROM data at g_pagerCartridgeData_Vhandler, loads the expansion-pak data when more memory is present,
   and builds the eight channels, the message pool and the sprite queue. */

extern char g_cartridgeReadWorker[];

extern void Cartridge_ReadChunksAndWait(void *dst, void *rom, void *size, u32 extra);
extern u32 Defs_GetMemorySize(void);

static inline void fill(void *dst, u8 value, s32 n) {
    u8 *p = dst;

    while (n--) {
        *p++ = value;
    }
}

void Vhandler_InitializePagerEuroExtended(void) {
    u32 extra;
    u32 i;

    extra = Defs_GetMemorySize() + 0x80000000;
    if (extra <= 0x80400000) {
        extra = 0;
    }
    fill(&g_resourcePager, 0, sizeof(PagerState));
    fill(g_resourcePager.lookup, 0xFF, sizeof(g_resourcePager.lookup));
    fill(g_resourcePager.slots, 0xFF, sizeof(g_resourcePager.slots));
    osUnmapTLBAll();
    for (i = 0; i < 24; i++) {
        g_resourcePager.entries[i].id = 0xFFFF;
        g_resourcePager.entries[i].team = 0xFF;
        g_resourcePager.entries[i].slot = 0xFF;
    }
    g_resourcePager.fBF4 = 0;
    g_resourcePager.head = 0;
    for (i = 0; i < 24; i++) {
        g_resourcePager.slots[i].a = 0;
        g_resourcePager.slots[i].b = 0;
        Virtual_AppendPageChainNode((Field_void_4 *)&g_resourcePager.head, &g_resourcePager.slots[i]);
        g_resourcePager.slots[i].index = i;
    }
    osCreateMesgQueue(&g_resourcePager.completion, g_resourcePager.list0Data, 33);
    osCreateMesgQueue(&g_resourcePager.jobs, g_resourcePager.list1Data, 8);
    osCreateMesgQueue(&g_resourcePager.pending, g_resourcePager.list2Data, 8);
    g_resourcePager.regions.start = 0x400;
    g_resourcePager.regions.pages = 256;
    g_resourcePager.regions.map = g_resourcePager.lookup;
    g_resourcePager.regions.next = 0;
    g_resourcePager.regions.source = (u8 (*)[4096])((u32) g_pagerCartridgeData | 0xB0000000);
    g_resourcePager.fD72 = 0;
    if (Defs_GetMemorySize() > 5242879) {
        Cartridge_ReadChunksAndWait(g_cartridgeReadWorker, g_pagerCartridgeData, g_pagerExpansionDataSize, extra);
    }
    if (extra != 0) {
        osMapTLB(0, 0x1FE000, 0x400000, extra + 0x80000000, -1, 7);
        g_resourcePager.fD70 = 1;
        g_resourcePager.fD72 = 1;
    }
    for (i = 0; i < 8; i++) {
        osSendMesg(&g_resourcePager.jobs, &g_resourcePager.channels[i], 1);
    }
    g_resourcePager.f20 = 0;
    osSetEventMesg(12, &g_resourcePager.completion, &g_resourcePager.f20);
    XPlus_FillMemory(g_resourcePager.pool, 99, 0x200);
    osCreateThread(g_resourcePager.queue, 99, g_pagerWorkerRomEntry, 0, g_resourcePager.queueData, 147);
    osStartThread(g_resourcePager.queue);
}

/* VHANDLER_2.CPP */
/* Array views share measured storage: FF F2A - FF B5B = 0x3CF;
 * the two four-byte-stride index streams occupy adjacent bytes. */

extern ResourcePageMapping *g_pagerLruHead;

static __inline__ ResourcePageMapping *readLink(ResourcePageMapping **value) { return *value; }

static __inline__ void writeLink(ResourcePageMapping **where, ResourcePageMapping *value) { *where = value; }

/* Releases one page of a resource's TLB slot: clears the odd (flag 1) or even page of the slot's entry in
 * g_pagerTlbSlots and, when the other page is still in use, remaps the slot with only that page through
 * osMapTLB; otherwise it unmaps the slot through osUnmapTLB and frees its virtual page. The
 * resource then has no slot. */

int Vhandler_RecycleTlbSlot(void) {
    u16 previous;
    s16 index;
    previous = g_pagerPageCounters[0];
    g_pagerPageCounters[0] = previous + 1;
    if ((s16)(previous + 1) >= 24) {
        g_pagerPageCounters[0] = g_pagerPageCounters[1];
    }
    index = (s16)previous;
    if (g_pagerSlotLookupStorage.first.indices[index * 4] != 0xFF) {
        g_pagerSlotLookupStorage.marks[g_pagerSlotLookupStorage.first.indices[index * 4] << 4] = 0xFF;
        g_pagerSlotLookupStorage.first.indices[index * 4] = 0xFF;
    }
    if (g_pagerSlotLookupStorage.second.indices[index * 4] != 0xFF) {
        g_pagerSlotLookupStorage.marks[g_pagerSlotLookupStorage.second.indices[index * 4] << 4] = 0xFF;
        g_pagerSlotLookupStorage.second.indices[index * 4] = 0xFF;
    }
    return index;
}

void Vhandler_MapResourcePage(s16 flags, ResourcePageMapping *item, s32 unused, u8 *out) {
    u8 *pair;
    s32 mapped;
    s32 slot;
    ResourcePageMapping *entry;
    u32 first;
    s32 second;
    pair = out;
    if (flags & 1) pair = out - 1;
    if (pair[0] != 0xFF && g_pagerSlotLookupStorage.marks[pair[0] * 16] != 0xFF) {
        slot = g_pagerSlotLookupStorage.marks[pair[0] * 16];
        g_pagerTlbSlots[(s16)slot].slot = item->index;
    } else if (pair[1] != 0xFF && g_pagerSlotLookupStorage.marks[pair[1] * 16] != 0xFF) {
        slot = g_pagerSlotLookupStorage.marks[pair[1] * 16];
        g_pagerTlbSlots[(s16)slot].team = item->index;
    } else {
        slot = Vhandler_RecycleTlbSlot();
        if (flags & 1) {
            g_pagerTlbSlots[(s16)slot].slot = item->index;
            if (pair[0] != 0xFF) {
                entry = &g_resourcePager.slots[pair[0]].chain;
                g_pagerTlbSlots[(s16)slot].team = entry->index;
                entry->slot = slot;
                if (readLink(&entry->prev) != 0) readLink(&entry->prev)->next = readLink(&entry->next);
                else { g_pagerLruHead = readLink(&entry->next); readLink(&entry->next)->prev = 0; }
                if (readLink(&entry->next) != 0) readLink(&entry->next)->prev = readLink(&entry->prev);
                else { g_pagerLruTail = readLink(&entry->prev); readLink(&entry->prev)->next = 0; }
                writeLink(&entry->next, 0);
                writeLink(&entry->prev, g_resourcePager.tail);
                if (g_resourcePager.tail != 0) g_resourcePager.tail->next = entry;
                g_pagerLruTail = entry;
                if (g_pagerLruHead == 0) g_pagerLruHead = entry;
            }
        } else {
            g_pagerTlbSlots[(s16)slot].team = item->index;
            if (pair[1] != 0xFF) {
                entry = &g_resourcePager.slots[pair[1]].chain;
                g_pagerTlbSlots[(s16)slot].slot = entry->index;
                entry->slot = slot;
                if (readLink(&entry->prev) != 0) readLink(&entry->prev)->next = readLink(&entry->next);
                else { g_pagerLruHead = readLink(&entry->next); readLink(&entry->next)->prev = 0; }
                if (readLink(&entry->next) != 0) readLink(&entry->next)->prev = readLink(&entry->prev);
                else { g_pagerLruTail = readLink(&entry->prev); readLink(&entry->prev)->next = 0; }
                writeLink(&entry->next, 0);
                writeLink(&entry->prev, g_resourcePager.tail);
                if (g_resourcePager.tail != 0) g_resourcePager.tail->next = entry;
                g_pagerLruTail = entry;
                if (g_pagerLruHead == 0) g_pagerLruHead = entry;
            }
        }
        g_pagerTlbSlots[(s16)slot].id = flags & 0xFFFE;
    }
    item->id = flags;
    item->slot = slot;
    *out = item->index;
    mapped = (s16)slot;
    unused = g_pagerTlbSlots[mapped].id << 12;
    if (g_pagerTlbSlots[mapped].team != 0xFF)
        first = ((uintptr_t)&g_pagerPageStorage & 0x3FFFFFF) + (g_pagerTlbSlots[mapped].team << 12);
    else first = -1;
    osMapTLB(mapped, 0, unused, first,
        g_pagerTlbSlots[(s16)slot].slot != 0xFF ? ((uintptr_t)&g_pagerPageStorage & 0x3FFFFFF) + (g_pagerTlbSlots[(s16)slot].slot << 12) : -1, 7);
}

void Vhandler_UnmapResourcePage(ResourcePageMapping *mapping) {
    s32 slot;

    if (mapping->slot == 0xFF) {
        return;
    }
    if (mapping->id & 1) {
        g_pagerTlbSlots[mapping->slot].slot = 0xFF;
        slot = mapping->slot;
        if (g_pagerTlbSlots[slot].team == 0xFF) {
            goto unmap;
        }
        osMapTLB(slot, 0, g_pagerTlbSlots[slot].id << 12,
                      ((intptr_t)&g_pagerPageStorage & 0x3FFFFFF) + (g_pagerTlbSlots[slot].team << 12), -1, 7);
    } else {
        g_pagerTlbSlots[mapping->slot].team = 0xFF;
        slot = mapping->slot;
        if (g_pagerTlbSlots[slot].slot == 0xFF) {
        unmap:
            osUnmapTLB(slot);
            g_pagerTlbSlots[mapping->slot].id = 0xFFFF;
        } else {
            osMapTLB(slot, 0, g_pagerTlbSlots[slot].id << 12, -1,
                          ((intptr_t)&g_pagerPageStorage & 0x3FFFFFF) + (g_pagerTlbSlots[slot].slot << 12), 7);
        }
    }
    mapping->slot = 0xFF;
}

static __inline__ void detachPage(ResourcePageMapping *mapping) {
    if (readLink(&mapping->prev)) readLink(&mapping->prev)->next = readLink(&mapping->next);
    else {
        g_pagerLruHead = readLink(&mapping->next);
        readLink(&mapping->next)->prev = 0;
    }
    if (readLink(&mapping->next)) readLink(&mapping->next)->prev = readLink(&mapping->prev);
    else {
        g_pagerLruTail = readLink(&mapping->prev);
        readLink(&mapping->prev)->next = 0;
    }
}
/* The pager uses the same two-pointer list operations as its worker. */
/* The LRU list as the pager helpers see it: head g_pagerLruHead, tail g_pagerLruTail, reached through a list pointer. */
typedef struct PageList { ResourcePageMapping *head, *tail; } PageList;
static __inline__ ResourcePageMapping *oldestPage(PageList *list) {
    return list->head;
}
static __inline__ void appendPage(Field_void_4 *list, void *node) {
    void *tail;
    *(void **)node = 0;
    ((Field_void_4 *)node)->value = list->value;
    tail = list->value;
    if (tail) *(void **)tail = node;
    list->value = node;
    if (!*(void **)list) *(void **)list = node;
}
static __inline__ Region *findPageRegion(u32 page) {
    Region *region;
    for (region = &g_resourcePager.regions; region != 0; region = region->next) {
        if (page >= region->start && page < region->start + region->pages) break;
    }
    return region;
}
void Vhandler_HandleResourcePageRequest(void) {
    ResourcePageThread *thread;
    Region *region;
    ResourcePageMapping *mapping;
    ResourcePageJob *job;
    u8 *slot;
    u32 page, kind;
    u64 start, elapsed;
    f32 duration;
    f32 scale;
    f32 limit;
    thread = __osGetCurrFaultedThread();
    kind = thread->message & 0x7C;
    if (kind == 4 || kind == 8) {
        g_resourcePager.counters.requests++;
        page = thread->address >> 12;
        region = findPageRegion(page);
        if (region) {
            g_resourcePager.counters.lastAddress = thread->address;
            slot = &region->map[page - region->start];
            if (*slot != 0xFF) {
                mapping = &g_resourcePager.slots[*slot].chain;
                if (mapping->slot == 0xFF) {
                    detachPage(mapping);
                    Vhandler_MapResourcePage(page, mapping, thread->slot, slot);
                    appendPage((Field_void_4 *)&g_pagerLruHead, mapping);
                }
                thread->state = 2;
                osStartThread(thread);
                return;
            }
            osRecvMesg(&g_resourcePager.jobs, (void **)&job, 1);
            g_resourcePager.counters.misses++;
            job->source = region->source[page - region->start];
            job->size = 4096;
            mapping = oldestPage((PageList *)&g_pagerLruHead);
            detachPage(mapping);
            Vhandler_UnmapResourcePage(mapping);
            if (mapping->id != 0xFFFF) {
                Region *previousRegion = Virtual_FindRegionForPage(mapping->id);
                previousRegion->map[mapping->id - previousRegion->start] = 0xFF;
                mapping->id = 0xFFFF;
            }
            mapping->age = 0;
            job->mapping = mapping;
            job->page = page;
            job->slot = slot;
            job->thread = thread;
            osSendMesg(&g_resourcePager.pending, job, 1);
            return;
        }
        start = osGetTime();
        scale = k_pagerRequestStatisticScale;
        limit = k_pagerRequestStatisticLimit;
        do {
            elapsed = ((osGetTime() - start) << 6) / 3000;
            duration = elapsed;
        } while (duration * scale < limit);
    } else {
        start = osGetTime();
        scale = k_pagerMissStatisticScale;
        limit = k_pagerMissStatisticLimit;
        do {
            elapsed = ((osGetTime() - start) << 6) / 3000;
            duration = elapsed;
        } while (duration * scale < limit);
    }
    osWritebackDCacheAll();
    osSetIntMask(1);
    ((void (*)(void))0x80000400)();
    g_pagerLastMappedSlot = -1;
    thread->state = 2;
    osStartThread(thread);
}

/* VHANDLER_3.CPP */
extern Region g_pagerFirstRegion;

void **Cache_AllocateResource(s32, s32, s32, char *);

void Vhandler_UpdatePagerStatistics(void) {
    u32 maximumAge;
    u32 minimumAge;
    s32 slotIndex;
    u32 *slotAge;
    u32 age;
    Region *region;
    s32 allocatedBytes;
    u16 pagesValue;
    s32 *out;
    s32 *ordered;

    maximumAge = 0;
    minimumAge = 0x80000000;
    slotIndex = 0;
    slotAge = &g_pagerFirstSlotAge;
    do {
        age = *slotAge;
        if (maximumAge < age) {
            maximumAge = age;
        }
        if (age < minimumAge) {
            minimumAge = age;
        }
        *slotAge = age + 1;
        slotIndex += 1;
        slotAge += 4;
    } while (slotIndex < 24);

    region = &g_pagerFirstRegion;
    allocatedBytes = 0;
    if (&g_pagerFirstRegion != 0) {
        do {
            pagesValue = region->pages;
            region = region->next;
            allocatedBytes += pagesValue << 12;
        } while (region != 0);
    }

    out = g_pagerStatisticBuffer;
    ordered = out;
    *ordered = allocatedBytes;
    ordered[-3] = maximumAge;
    ordered[-2] = minimumAge;
    __builtin_memcpy(&out[-1], &((CompactOptionsPageView *)g_pagerLruHead)->flagWord, sizeof(s32));
}

void Vhandler_MapBootstrapAddressRange(void) {
    osMapTLB(31, 0x1FE000, 0x200000, 0, 0x100000, 7);
}

void *Vhandler_AllocateVirtualRegion(s32 sourceAddress, s32 unusedArgument, s32 regionLabel)
{
  char completionQueueStorage[24];
  int pageTableBytes;
  Block10 blk;
  s32 completionMessage;
  u32 pageCount;
  void *unusedPointer;
  u32 rounded;
  void **resourceResult;
  Draw *regionAllocation;
  int evenPageCount;
  pageCount = ((u32) (sourceAddress + 0xFFF)) >> 12;
  evenPageCount = (pageCount + 1) & (~1);
  if (1)
  {
    osCreateMesgQueue(completionQueueStorage, (s32) (&completionMessage), 1);
    blk.f28 = 3;
    blk.f2C = sourceAddress;
    blk.f34 = (void **) completionQueueStorage;
    pageTableBytes = pageCount * 4;
    rounded = evenPageCount + 24;
    resourceResult = Cache_AllocateResource(0, pageTableBytes + rounded, 3, &s_virtualRegionText);
    regionAllocation = *resourceResult;
    blk.f30 = regionAllocation;
    regionAllocation->model = resourceResult;
  }
  ((Draw *)blk.f30)->allocationMode = regionLabel;
  osSendMesg(&g_resourcePager.completion, &blk.f28, 1);
  osRecvMesg(completionQueueStorage, &unusedPointer, 1);
  return unusedPointer;
}

void Vhandler_FreeVirtualRegion(s32 regionHandle) {
    char completionQueueStorage[24];
    BlockVirtualFreeVirtualRegion block;
    s32 completionMessage;
    void *unusedPointer;

    osCreateMesgQueue(completionQueueStorage, (intptr_t)&completionMessage, 1);
    block.type = 2;
    block.value = regionHandle;
    block.data = completionQueueStorage;
    osSendMesg(&g_resourcePager.completion, &block, 1);
    osRecvMesg(completionQueueStorage, &unusedPointer, 1);
    Cache_ReleaseResource(0, ((Draw *)(unusedPointer))->model);
}

void Vhandler_GetPagerCounters(struct PagerCounters *outCounters) {
    *outCounters = g_resourcePager.counters;
}

/* Resource manager thread setup and loop: fills a 0x200-byte stack with a marker, creates and starts the
 * thread object at g_resourcePagerDispatcherThread (entry g_pagerDispatcherRomEntry, stack top g_pagerPageMappings), then forever receives request
 * messages and dispatches on the request type to Vhandler_HandleResourcePageRequest, Virtual_FinishPageJob, Virtual_ReleaseVirtualRegion or
 * Virtual_AssignVirtualRegion. */
extern char g_pagerDispatcherRomEntry[];

void Vhandler_RunPagerDispatcher(void) {
    OSMesg request;

    XPlus_FillMemory(g_resourcePager.pool2, 98, sizeof(g_resourcePager.pool2));
    osCreateThread(g_resourcePager.queueData, 98, g_pagerDispatcherRomEntry, 0, g_resourcePager.pool2 + sizeof(g_resourcePager.pool2), 148);
    osStartThread(g_resourcePager.queueData);
    for (;;) {
        osRecvMesg(&g_resourcePager.completion, &request, 1);
        switch (((Request *)request)->type) {
        case 0:
            Vhandler_HandleResourcePageRequest();
            break;
        case 1:
            Virtual_FinishPageJob(request);
            break;
        case 3:
            Virtual_AssignVirtualRegion(request);
            break;
        case 2:
            Virtual_ReleaseVirtualRegion(request);
            break;
        }
    }
}

extern void osInvalDCache(void *addr, s32 size);
extern void osInvalICache(void *addr, s32 size);

/* Resource page reader thread: takes page jobs from the pending queue, reads the page from the cartridge
 * into its slot of the page array, writes the data cache back and invalidates the instruction cache, then
 * returns the job to the manager. */
void Vhandler_RunPageLoadWorker(void *unused) {
    OSMesgQueue queue;
    OSMesg queueMessage;
    OSMesg message;

    osCreateMesgQueue(&queue, &queueMessage, 1);
    for (;;) {
        osRecvMesg(&g_resourcePager.pending, &message, 1);
        if (*((ResourcePageJob *)message)->slot == 0xFF) {
            Cartridge_ReadChunksAndWait(g_cartridgeReadWorker, ((ResourcePageJob *)message)->source, (void *)((((ResourcePageJob *)message)->size + 1) & ~1),
                             (uintptr_t)&g_pagerPageStorage + (((ResourcePageJob *)message)->mapping->index << 12));
            osInvalDCache(&g_pagerPageStorage + (((ResourcePageJob *)message)->mapping->index << 12), 0x1000);
            osInvalICache(&g_pagerPageStorage + (((ResourcePageJob *)message)->mapping->index << 12), 0x1000);
        }
        ((Request *)message)->type = 1;
        osSendMesg(&g_resourcePager.completion, message, 1);
    }
}

typedef struct PageChain {
    ResourcePageMapping *head;
    ResourcePageMapping *tail;
} PageChain;

/* Unlinks a mapping from a doubly linked chain. */
void Vhandler_RemovePageChainNode(PageChain *list, ResourcePageMapping *node) {
    if (node->prev != 0) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
        node->next->prev = 0;
    }
    if (node->next != 0) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
        node->prev->next = 0;
    }
}

/* VHANDLER_5.CPP */
/* VHANDLER_4.CPP */

void Virtual_AppendPageChainNode(Field_void_4 *pageChain, void *pageNode) {
    void *previousTail;

    *(void **)pageNode = 0;
    ((Field_void_4 *)(pageNode))->value = pageChain->value;
    previousTail = pageChain->value;
    if (previousTail != 0) {
        *(void **)previousTail = pageNode;
    }
    pageChain->value = pageNode;
    if (*(void **)pageChain == 0) {
        *(void **)pageChain = pageNode;
    }
}

void Virtual_PrependPageChainNode(Field_void_4 *pageChain, Field_void_4 *pageNode) {
    void *previousHead;

    pageNode->value = 0;
    *(void **)pageNode = *(void **)pageChain;
    previousHead = *(void **)pageChain;
    if (previousHead != 0) {
        ((Field_void_4 *)(previousHead))->value = pageNode;
    }
    *(void **)pageChain = pageNode;
    if (pageChain->value == 0) {
        pageChain->value = pageNode;
    }
}

void *Virtual_FindRegionForPage(u32 virtualPage) {
    NodeVirtualFindRegionForPage *region;
    u16 firstPage;

    region = (NodeVirtualFindRegionForPage *)&g_pagerFirstRegion;
    if (&g_pagerFirstRegion != 0) {
    loop_1:
        firstPage = region->f4;
        if ((virtualPage < firstPage) || (virtualPage >= (u32)(firstPage + region->f6))) {
            region = region->next;
            if (region != 0) {
                goto loop_1;
            }
        }
    }
    return region;
}

/* VHANDLER_5.CPP */

/* Releases the resource node whose id matches the handle's upper bits: unlinks it from the g_pagerFirstRegion
 * list, frees each slot it holds through Vhandler_UnmapResourcePage and marks the slot unused, then posts the node
 * back to the handle's message queue. */

/* Registers a memory region: rounds its size to whole pages, places it after the last region of the chain at g_pagerFirstRegion on an even page at or above 0x800, marks every page of its map as free, and maps it through osSendMesg_Mutex. */

ResourcePageMapping *Virtual_AcquireRecycledPage(void) {
    ResourcePageMapping *entry;
    NodeVirtualAcquireRecycledPage *node;

    entry = g_pagerLruHead;
    if (entry->prev != 0) {
        entry->prev->next = *(ResourcePageMapping * volatile *)&entry->next;
    } else {
        g_pagerLruHead = entry->next;
        (*(ResourcePageMapping * volatile *)&entry->next)->prev = 0;
    }
    if (entry->next != 0) {
        entry->next->prev = *(ResourcePageMapping * volatile *)&entry->prev;
    } else {
        g_pagerLruTail = entry->prev;
        (*(ResourcePageMapping * volatile *)&entry->prev)->next = 0;
    }

    Vhandler_UnmapResourcePage(entry);
    if (entry->id != 0xFFFF) {
        node = Virtual_FindRegionForPage(entry->id);
        node->data[entry->id - node->start] = 0xFF;
        entry->id = 0xFFFF;
    }
    entry->age = 0;
    return entry;
}

void Virtual_ReleaseVirtualRegion(VirtualRegionOwnerState *allocation) {
    Region *node;
    Region *prev;
    u8 *slot;
    s32 i;
    u32 key;

    node = &g_pagerFirstRegion;
    key = allocation->handle >> 12;
    prev = 0;
    while (node != 0) {
        if (node->start == key) {
            break;
        }
        prev = node;
        node = node->next;
    }
    prev->next = node->next;
    slot = node->map;
    for (i = 0; i < node->pages; i++) {
        if (*slot != 0xFF) {
            Vhandler_UnmapResourcePage(&g_pagerPageMappings[*slot]);
            g_pagerPageMappings[*slot].id = 0xFFFF;
        }
        slot++;
    }
    osSendMesg(allocation->queue, node, 1);
}

void Virtual_AssignVirtualRegion(RegionDesc *desc)
{
    Region *p;
    Region *prev;
    Region *r;
    unsigned int start;
    s32 pages;
    s32 count;
    u8 *map;
    s32 i;
    s32 fill;

    start = 0;
    pages = (desc->size + 4095) / 0x1000;
    p = &g_pagerFirstRegion;
    prev = 0;
    r = desc->region;
    r->map = (u8 *)(r + 1);
    count = (pages + 1) & ~1;
    for (; p != 0; p = p->next) {
        prev = p;
        start = p->start + p->pages;
    }
    if (start & 1) {
        start++;
    }
    if (start < 0x800) {
        start = 0x800;
    }
    i = count;
    r->start = start;
    r->pages = pages;
    r->next = 0;
    prev->next = r;
    map = r->map;
    fill = 0xFF;
    while (i-- != 0) {
        *map++ = fill;
    }
    osSendMesg(desc->mapping, start << 12, 1);
}

extern char g_pagerPendingQueue[];

void Virtual_FinishPageJob(ResourcePageJob *req) {
    ResourcePageMapping *link;

    if (*req->slot == 0xFF) {
        link = req->mapping;
        writeLink(&link->next, 0);
        writeLink(&link->prev, g_resourcePager.tail);
        if (g_resourcePager.tail != 0) {
            g_resourcePager.tail->next = link;
        }
        g_pagerLruTail = link;
        if (g_pagerLruHead == 0) {
            g_pagerLruHead = link;
        }
        Vhandler_MapResourcePage(req->page, req->mapping, req->thread->slot, req->slot);
        osInvalDCache((void *)(req->page << 12), 0x1000);
        osInvalICache((void *)(req->page << 12), 0x1000);
    } else {
        link = req->mapping;
        writeLink(&link->prev, 0);
        writeLink(&link->next, g_resourcePager.head);
        if (g_resourcePager.head != 0) {
            g_resourcePager.head->prev = link;
        }
        g_pagerLruHead = link;
        if (g_pagerLruTail == 0) {
            g_pagerLruTail = link;
        }
    }
    req->thread->state = 2;
    osStartThread(req->thread);
    osSendMesg(g_pagerPendingQueue, req, 1);
}

/* VHANDLER_1.CPP */
#if !(defined(VERSION_US_REV1))
const char g_virtualRegionText[15] =
    "Virtual Region\000";
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/s_virtualRegionText_Vhandler.c */
const unsigned char s_virtualRegionText[15] =
    "Virtual Region";
#endif

/* VHANDLER_4.CPP */
const float k_vhandlerConstantWords[4] = {
    1.0e-06f, 2.0f, 1.0e-06f, 2.0f,
};

/* CCOLLISION_INTERSECTSEGMENTBOX_DATA.CPP */
#if defined(VERSION_DE)
#if defined(VERSION_DE)
struct {
    MemoryBoundary boundaries[10];
    s32 lastMappedSlot;
    u32 alignmentFill;
} g_CcollisionIntersectsegmentboxWords2 __attribute__((aligned(4))) = {
    { { 0x807fffff, 0x3 }, { 0x9fffffff, 0x0 }, { 0xa07fffff, 0x3 }, { 0xa3ffffff, 0x0 }, { 0xa4001fff, 0xb }, { 0xa5ffffff, 0x0 }, { 0xa63fffff, 0x7 }, { 0xafffffff, 0x0 }, { 0xb1fdffff, 0x7 }, { 0xffffffff, 0x0 } },
    -2054,
    0x92060009
};
#endif
#endif

/* GEOMETRY_DRAWRESOURCEMODEL_DATA.CPP */
#if defined(VERSION_EU_X)
RestGeometryDrawresourcemodelEncodedWordsLayout375 k_GeometryDrawresourcemodelEncodedWords = {
    0x807FFFFF,
    3,
    0x9FFFFFFF,
    0,
    0xA07FFFFF,
    3,
    0xA3FFFFFF,
    0,
    0xA4001FFF,
    11,
    0xA5FFFFFF,
    0,
    0xA63FFFFF,
    7,
    0xAFFFFFFF,
    0,
    0xB1FDFFFF,
    { 7, -1, 0, -2054 },
    0x3FC80F9A,
};
#endif

/* G_LINKTABLESENCODEDWORDS.CPP */
#if defined(VERSION_US)
#if defined(VERSION_US)
struct {
    MemoryBoundary boundaries[10];
    s32 lastMappedSlot;
    u32 alignmentFill;
} g_LinktablesEncodedWords __attribute__((aligned(4))) = {
    { { 0x807fffff, 0x3 }, { 0x9fffffff, 0x0 }, { 0xa07fffff, 0x3 }, { 0xa3ffffff, 0x0 }, { 0xa4001fff, 0xb }, { 0xa5ffffff, 0x0 }, { 0xa63fffff, 0x7 }, { 0xafffffff, 0x0 }, { 0xb1fdffff, 0x7 }, { 0xffffffff, 0x0 } },
    -2054,
    0x4e455f32
};
#endif
#endif

/* G_OVERLAYSSEVENCONSTANTSRETAINEDWORDS14.CPP */
#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
struct {
    MemoryBoundary boundaries[10];
    s32 lastMappedSlot;
    u32 alignmentFill;
} g_OverlaysSevenConstantsRetainedWords14 __attribute__((aligned(4))) = {
    { { 0x807fffff, 0x3 }, { 0x9fffffff, 0x0 }, { 0xa07fffff, 0x3 }, { 0xa3ffffff, 0x0 }, { 0xa4001fff, 0xb }, { 0xa5ffffff, 0x0 }, { 0xa63fffff, 0x7 }, { 0xafffffff, 0x0 }, { 0xb1fdffff, 0x7 }, { 0xffffffff, 0x0 } },
    -2054,
    0x3fc88fbb
};
#endif
#endif

/* K_RESOURCESENCODEDWORDSBLOCK6.CPP */
#if defined(VERSION_EU)
#if defined(VERSION_EU)
struct {
    MemoryBoundary boundaries[10];
    s32 lastMappedSlot;
    u32 alignmentFill;
} k_ResourcesEncodedWordsBlock6 __attribute__((aligned(4))) = {
    { { 0x807fffff, 0x3 }, { 0x9fffffff, 0x0 }, { 0xa07fffff, 0x3 }, { 0xa3ffffff, 0x0 }, { 0xa4001fff, 0xb }, { 0xa5ffffff, 0x0 }, { 0xa63fffff, 0x7 }, { 0xafffffff, 0x0 }, { 0xb1fdffff, 0x7 }, { 0xffffffff, 0x0 } },
    -2054,
    0x202d2043
};
#endif
#endif
