#ifndef TEXTURE_CACHE_RECYCLELOADREQUEST_H
#define TEXTURE_CACHE_RECYCLELOADREQUEST_H
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
struct EntryList {
    s32 pad0;
    struct CacheEvictionEntry *first;
};
/* Resource-loader thread, its request queue, message slots and stack. */
typedef struct ResourceLoadWorker {
    u8 thread[560];
    OSMesgQueue requests;
    s32 messages[128];
    u8 stack[4096];
    s32 timestamp; /* 0x1448: frame of last dispatched request */
} ResourceLoadWorker;
struct ResourceRequest {
    u8 reserved[0x14];
    void (*dispatch)(s32 argument, ResourceRequest *request);
    s32 argument;
    u8 reserved1C[4];
    void *replyQueue;
};
extern void Cache_RecycleLoadRequest(s32 unused0, void *request);
#endif
