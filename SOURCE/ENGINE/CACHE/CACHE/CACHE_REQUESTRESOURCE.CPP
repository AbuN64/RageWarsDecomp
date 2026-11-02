#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "COMMON/LONE/RESOURCE_REQUEST_QUEUE.H"
#include "COMMON/MANAGER.H"
#include "SCENE/RESOURCE_BINDING_AND_FADE_VIEWS.H"
#include "COMMON/CARTRIDGEREADWORKER.H"
#include "COMMON/TRIGGER_AND_FLOAT_VALUE_OPERATIONS.H"
#include "COMMON/CONTROLLER_MOTOR_STATE.H"
#include "COMMON/OS_TIMER_INTERRUPT_INTERNALS.H"
#include "COMMON/S1.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "TEXTURE/CACHE_RECYCLELOADREQUEST.H"
#include "ENGINE/CACHE/LIST.H"

extern Manager g_resourceRequestManager;
extern s32 g_resourceRecencyList;
extern u32 g_resourceHashEvenIndexMask;
extern ResourceHashEntry *g_resourceHashBuckets;
extern struct CartridgeReadWorker g_cartridgeReadWorker;
extern s32 g_resourceCacheFrameStamp;
extern void List_MoveIntrusiveToHead(void *, s32);
extern void *Cache_AcquireLoadRequestWithEviction(s32, s32);
extern void *Cache_AcquireResourceNodeWithEviction(s32, s32);
extern void Cache_ReleasePendingResourceEntry(s32 unused0, s32 entryAddress);
extern void Cache_InsertResourceByAddress(s32 unused, void *object);
extern s32 Cache_SubmitResourceLoadAndWait(s32 *, ResourceLoadRequest *);
extern ResourceLoadRequest *Cache_FinalizeResourceLoad(s32 unused, ResourceLoadRequest *request, s32 dropReference);
extern void Cartridge_ReadChunksAndWait(struct CartridgeReadWorker *, u32, s32, void *);
extern void Cartridge_SubmitReadChunks(struct CartridgeReadWorker *, u32, s32, void *, struct Queue *, s32, s32);

static inline void acquire(void) {
    u32 token = __osDisableInt();
    s32 count = g_resourceHeapLockUsers + 1;
    g_resourceHeapLockUsers = count;
    if (count != 1) {
        __osRestoreInt(token);
        osRecvMesg(g_resourceRequestManager.lock, 0, 1);
    } else __osRestoreInt(token);
}
static inline void release(void) {
    u32 token = __osDisableInt();
    s32 count = g_resourceHeapLockUsers - 1;
    g_resourceHeapLockUsers = count;
    if (count != 0) {
        __osRestoreInt(token);
        osSendMesg(g_resourceRequestManager.lock, 0, 1);
    } else __osRestoreInt(token);
}
static inline void find(u32 key, ResourceLoadRequest **out) {
    ResourceHashEntry *node = g_resourceHashBuckets + (((key<<5)^(key>>1)^(key>>9)^(key>>17))&g_resourceHashEvenIndexMask);
    if (node->key != key) goto not_initial;
    *out=node->value;
    goto done;
loop_found:
    *out=node->value;
    goto done;
not_initial:
    *out=0;
    if (node==0) goto done;
loop:
    if (node->key==key) goto loop_found;
    node=node->next;
    if (node!=0) goto loop;
done:;
}
static inline void addref(CachedResource *node) {
    node->count++;
    node->flags |= 0x100;
}
static inline void stamp(CachedResource *node) {
    node->stamp=g_resourceCacheFrameStamp;
    List_MoveIntrusiveToHead(&g_resourceRecencyList,(s32)node);
}
static inline CachedResource *allocate(u32 size, u32 flags) {
    CachedResource *node=Cache_AcquireResourceNodeWithEviction(0,flags);
    if (node!=0) {
        addref(node);
        node->data=Cache_AllocateHeapWithEviction(0,size,(flags>>5)&1,flags);
        if (node->data!=0) {
            node->dataSize=size;
            node->flags |= flags;
            Cache_InsertResourceByAddress(0,node);
        } else {
            if (--node->count==0) node->flags &= ~0x100;
            Cache_ReleasePendingResourceEntry(0,(s32)node);
            node=0;
        }
    }
    return node;
}
void *Cache_RequestResource(s32 unused, u32 key, u32 source, u32 size,
                          u32 mode, s32 owner, void *tag, const char *spare, u32 direct) {
    ResourceLoadRequest *request;
    ResourceLoadRequest *scan;
    ResourceLoadRequest *resolved;
    CachedResource *node;
    u32 flags;
    u32 oldFlags;
    s32 busy;
    ResourceLoadRequest *allocated;

    acquire();
    find(key,&request);
    if (request!=0 && (u32)request->priority<=size) {
        addref(request->node);
        stamp(request->node);
        release();
        return request->node;
    }
    direct |= g_resourceRequestManager.mask;
    busy=0;
    if(direct!=0) allocated=Cache_AcquireLoadRequestWithEviction(0,mode);
    else {
        scan=g_resourceRequestManager.active.head;
        while(scan!=0) {
            if(scan->key==key && size<=(u32)scan->priority) {busy=1;break;}
            scan=scan->next;
        }

        if(direct==0 && busy) goto failed;
        allocated=Cache_AcquireLoadRequestWithEviction(0,mode);
    }
    request=allocated;
    if(request!=0) {
        if(tag!=0) flags=(mode&0x1C)|0x22;
        else flags=mode;
        request->extra=0;
        node=allocate(size,flags);
        request->node=node;
        if(request->node!=0) {
            if(size&1) size++;
            request->key=key;
            request->priority=size;
            request->owner=owner;
            request->tag=tag;
            request->mode=mode;
            List_RemoveIntrusive(&g_resourceRequestManager.pending,request);
            List_AppendIntrusive(&g_resourceRequestManager.active,request);
            if(direct!=0) {
                if(tag!=0) request->flags |= 4;
                release();
                Cartridge_ReadChunksAndWait(&g_cartridgeReadWorker,source,size,request->node->data);
                if(tag!=0) Cache_SubmitResourceLoadAndWait(&g_resourceCacheWorker,request);
                acquire();
                if(tag!=0) request->flags &= ~4;
                resolved=Cache_FinalizeResourceLoad(0,request,0);
                if(resolved!=0 && resolved!=request) addref(resolved->node);
                release();
                if(resolved!=0) return resolved->node;
                return 0;
            } else {
                oldFlags=request->flags;
                request->flags=oldFlags|2;
                if(tag!=0) request->flags=oldFlags|0xE;
                release();
                {
                    void *replyQueue = &g_resourceRequestManager;
                    Cartridge_SubmitReadChunks(&g_cartridgeReadWorker,source,size,request->node->data,replyQueue,(s32)request,0);
                }
                return 0;
            }
        }
        Cache_RecycleLoadRequest(0,request);
    }
failed:
    release();
    return 0;
}
