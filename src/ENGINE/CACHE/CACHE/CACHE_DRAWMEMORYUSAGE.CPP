#include "ENGINE/CACHE/CACHE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/LONE/RUNTIME_HEAP.H"
#include "include_asm.h"
#include "COMMON/VECTOR4F.H"
#include "COMMON/MANAGER.H"
#include "COMMON/ENTRYRECAT18V3.H"
#include "TYPES.H"
#include "COMMON/EXTERNS.H"
#include "AUDIO/HASHTABLE.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "TEXTURE/CACHE_RECYCLELOADREQUEST.H"
#include "ENGINE/CACHE/LIST.H"
#include "ENGINE/CACHE/LIST.H"

/* Activates a load request: moves it from the pending to the active list and, when its node is set, looks its key up in the request hash table; an existing request with lower priority is removed from the table and finished, releasing its node's data and node when nothing else holds them, while an existing request with at least the same priority wins and this request's node is released and the request finished, returning the existing one; otherwise, or after replacing, the request is inserted, owns its node and optionally drops the node's pending reference. The hash lookup and node release are the inline forms of Cache_RetainResourceByKey's lookup and Cache_ReleasePendingResourceEntry. */







extern s32 g_resourceRecencyList;
extern struct { CachedResource **value; } g_resourceFreeNodeStack;
extern u32 g_resourceHashEvenIndexMask;


extern void Heap_FreeAllocation(void *, void *);
extern void HashTable_SetResourceByKey(s32, ResourceLoadRequest *);

static inline void find(s32 key, ResourceLoadRequest **out) {
    CacheHashEntry *node = g_resourceHashBuckets + (((key << 5) ^ ((u32)key >> 1) ^ ((u32)key >> 9) ^ ((u32)key >> 17)) & g_resourceHashEvenIndexMask);

    if (node->key == key) {
        *out = node->value;
        return;
    }
    *out = 0;
    while (node != 0) {
        if (node->key == key) {
            *out = node->value;
            return;
        }
        node = node->next;
    }
}




static inline void release(s32 node) {
    List_RemoveIntrusive(&g_resourceRecencyList, (void *)node);
    if (((CachedResource *)node)->flags & 0x1000) {
        List_RemoveIntrusive(&((IntrusiveList *)&g_resourceRecencyList)[1], (void *)node);
    }
    if (*(&g_resourceRecencyList - 2) == node) {
        *(&g_resourceRecencyList - 2) = 0;
    }
    ((CachedResource *)node)->flags = 0;
    g_resourceFreeNodeStack.value[((struct Pool *)&g_resourceFreeNodeCount)->count] = (CachedResource *)node;
    *(&g_resourceRecencyList + (((char *)&((struct ResMgr *)0)->count - (char *)0) - ((char *)&((struct ResMgr *)0)->entries - (char *)0)) / sizeof(s32)) += 1;
}

ResourceLoadRequest *Cache_FinalizeResourceLoad(s32 unused, ResourceLoadRequest *request, s32 dropReference) {
    ResourceLoadRequest *existing;
    CachedResource *node;

    List_RemoveIntrusive(&g_resourceCompletionRequests, request);
    List_PrependIntrusive((char *)&g_resourceCompletionRequests - (((char *)&((struct ResMgr *)0)->listBC0 - (char *)0) - ((char *)&((struct ResMgr *)0)->listBAC - (char *)0)), request);
    if (request->node != 0) {
        find(request->key, &existing);
        if (existing != 0) {
            if (existing->priority < request->priority) {
                HashTable_RemoveResourceByKey(existing->key);
                existing->node->owner = 0;
                if (!(existing->node->flags & 0x702)) {
                    Heap_FreeAllocation(&g_runtimeHeap, existing->node->data);
                    release((s32)existing->node);
                }
                Cache_RecycleLoadRequest(0, existing);
            } else {
                Heap_FreeAllocation(&g_runtimeHeap, request->node->data);
                release((s32)request->node);
                Cache_RecycleLoadRequest(0, request);
                return existing;
            }
        }
        HashTable_SetResourceByKey(request->key, request);
        request->node->owner = request;
        if (dropReference != 0) {
            node = request->node;
            if (--node->count == 0) {
                node->flags &= ~0x100;
            }
        }
        return request;
    }
    Cache_RecycleLoadRequest(0, request);
    return 0;
}

#include <PR/gbi.h>
#include "ENGINE/CACHE/HEAP.H"
#include "SCENE/RESOURCE_BINDING_AND_FADE_VIEWS.H"

extern Gfx *g_displayListCursor;
extern struct MemoryUsageStats g_resourceCacheFrameStamp;
extern Manager g_resourceRequestManager;
extern void Geometry_SetCombineMode(u32);
extern s32 Geometry_SetModePreset(s32);

/* The main heap (its other users declare g_runtimeHeap as a plain byte); its block list is read through this view. */
static inline struct Heap *mainHeap(void) {
    return (struct Heap *)&g_runtimeHeap;
}

/* Band edge shades: half (darker) and one and a half (brighter) of a colour channel, clamped to 255. */
#define DARKEN(c) ((s32)((u32)(c) >> 1) < 0x100 ? (s32)((u32)(c) >> 1) : 0xFF)
#define BRIGHTEN(c) ((((c) * 3) >> 1) > 0xFF ? 0xFF : (((c) * 3) >> 1))

static inline void lock(void) {
    u32 token = __osDisableInt();
    s32 counter = g_resourceHeapLockUsers + 1;

    g_resourceHeapLockUsers = counter;
    if (counter != 1) {
        __osRestoreInt(token);
        osRecvMesg(g_resourceRequestManager.lock, 0, 1);
    } else {
        __osRestoreInt(token);
    }
}

static inline void unlock(void) {
    u32 token = __osDisableInt();
    s32 counter = g_resourceHeapLockUsers - 1;

    g_resourceHeapLockUsers = counter;
    if (counter != 0) {
        __osRestoreInt(token);
        osSendMesg(g_resourceRequestManager.lock, 0, 1);
    } else {
        __osRestoreInt(token);
    }
}

/* Debug heap map inside a grey frame: the bar is scaled to the heap's extent (bytes from 0x80000000 to its first
 * block plus every block's used and free size); the part below the first block is olive, then each cache entry is a
 * band (yellow, red, blue or green by its flags) with a darker bottom edge, entries outside the locked set in the
 * first pass and locked ones in the second; an entry that is not locked or loading and was unused for 5+ frames
 * also gets a white inset band. Runs under the resource lock. */
void Cache_DrawMemoryUsage(s32 unused, s32 left, s32 top, s32 right, s32 bottom) {
    struct HeapAllocationBlock *span;
    CacheEvictionNode *node;
    u32 total;
    s32 pass;
    s32 select;
    s32 lo;
    s32 hi;
    s32 r;
    s32 g;
    s32 b;
    u32 base;

    gDPPipeSync(g_displayListCursor++);
    gDPSetCycleType(g_displayListCursor++, G_CYC_1CYCLE);
    Geometry_SetCombineMode(25);
    Geometry_SetModePreset(21);
    gDPSetPrimColor(g_displayListCursor++, 0, 0, 0xA0, 0xA0, 0xA0, 0x00);
    gDPFillRectangle(g_displayListCursor++, left - 1, top - 1, right + 1, bottom + 1);
    Geometry_SetModePreset(27);
    gDPSetPrimColor(g_displayListCursor++, 0, 0, 0xA0, 0xA0, 0xA0, 0xFF);
    gDPFillRectangle(g_displayListCursor++, left, top, right, bottom);

    lock();

    base = 0x80000000;
    span = mainHeap()->first;
    total = (u32)span - base;
    for (; span != 0; span = span->next) {
        total += span->size + span->free;
    }

    gDPSetPrimColor(g_displayListCursor++, 0, 0, 0x64, 0x64, 0x00, 0xFF);
    hi = bottom - ((u32)(((u32)mainHeap()->first - base) * (bottom - top)) / total) - 1;
    gDPFillRectangle(g_displayListCursor++, left, hi, right, bottom + 1);

    for (pass = 0; pass < 2; pass++) {
        for (node = g_resourcesByAddress.head; node != 0; node = node->next) {
            if (pass != 0) {
                select = (node->flags & 0x101) == 0x100;
            } else {
                select = (node->flags & 0x101) != 0x100;
            }
            if (select == 0) {
                continue;
            }

            if (node->flags & 1) { r = 255; g = 255; b = 0; }
            else if (node->flags & 0x100) { r = 255; g = 0; b = 0; }
            else if (node->flags & 0x600) { r = 0; g = 0; b = 255; }
            else { r = 0; g = 255; b = 0; }

            gDPSetPrimColor(g_displayListCursor++, 0, 0, r, g, b, 0xFF);
            hi = bottom - ((u32)(((node->start + node->end) - base) * (bottom - top)) / total) - 1;
            lo = bottom - ((u32)(((node->start - base) - 32) * (bottom - top)) / total) - 1;
            if (hi < lo) {
                gDPFillRectangle(g_displayListCursor++, left, hi, right, lo);
            }
            gDPSetPrimColor(g_displayListCursor++, 0, 0, DARKEN(r), DARKEN(g), DARKEN(b), 0xFF);
            gDPFillRectangle(g_displayListCursor++, left, lo - 1, right, lo);

            if (!(node->flags & 0x702)) {
                r = g = b = 0xFF;
                if ((u32)(g_resourceCacheFrameStamp.value - node->stamp) >= 5U) {
                gDPSetPrimColor(g_displayListCursor++, 0, 0, r, g, b, 255);
                if (hi < lo) {
                    gDPFillRectangle(g_displayListCursor++, left + 8, hi, right, lo);
                }
                gDPSetPrimColor(g_displayListCursor++, 0, 0, BRIGHTEN(r), BRIGHTEN(g), BRIGHTEN(b), 255);
                gDPFillRectangle(g_displayListCursor++, left + 8, lo - 1, right, lo);
                }
            }
        }
    }

    unlock();
}
