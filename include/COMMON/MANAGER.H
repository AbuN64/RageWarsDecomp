#ifndef COMMON_MANAGER_H
#define COMMON_MANAGER_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"

struct Manager;

extern int g_resourceSlotOwners[];

struct CachedResource;
typedef struct CachedResource CachedResource;

struct Manager;

struct NodeCacheRunResourceCompletionWorker;
typedef struct NodeCacheRunResourceCompletionWorker NodeCacheRunResourceCompletionWorker;


struct GeometryVariantByteView;
typedef struct GeometryVariantByteView GeometryVariantByteView;



struct CMemEntry;
struct CMemEntry {
    s32 resource;
    s32 size;
    s32 references;
    s32 flags;
    s32 lastUsed;
    s32 owner;
    struct CMemEntry *next;
    s32 key;
    s32 pending;
    s32 callback;
};

struct CachedResource;
struct ResourceLoadRequest;
struct CachedResource {
    void *data;
    s32 dataSize;
    s32 count;
    s32 flags;
    s32 stamp;
    struct ResourceLoadRequest *owner;
};

struct ResourceLoadRequest {
    struct CachedResource *node;
    struct CachedResource *extra; /* 0x04: optional companion resource */
    s32 key;
    s32 priority;
    s32 flags;                         /* 0x10 */
    void *tag;                         /* 0x14 */
    s32 owner;                         /* 0x18: bank/variation id */
    s32 mode;                          /* 0x1C */
    void *replyQueue;                  /* 0x20 */
    struct ResourceLoadRequest *next; /* 0x24 */
};

struct ResourceHashEntry;
struct ResourceLoadRequest;
struct ResourceHashEntry {
    s32 key;
    struct ResourceLoadRequest *value;
    s32 reservedWord;
    struct ResourceHashEntry *next;
};

struct Manager;
typedef struct Manager Manager;






struct RequestCacheRunResourceCompletionWorker;
typedef struct RequestCacheRunResourceCompletionWorker RequestCacheRunResourceCompletionWorker;

struct GeometryVariantByteView;

struct Manager;

struct NodeCacheRunResourceCompletionWorker;
struct NodeCacheRunResourceCompletionWorker {
    void *data;
    s32 pad4;
    s32 count;
    s32 flags;
};

struct NodeCacheRunResourceCompletionWorker;
struct RequestCacheRunResourceCompletionWorker;
struct RequestCacheRunResourceCompletionWorker {
    struct NodeCacheRunResourceCompletionWorker *node;
    s32 pad4[3];
    s32 flags;
};

struct OwnerStaticInstanceDrawGeometryVariant;

struct CMemEntry;
typedef struct CMemEntry CMemEntry;


struct CachedResource;






extern int Statinst_AdvanceResourceKey(void);





struct LevelActor;




struct ActorResourceStatusView;
typedef struct ActorResourceStatusView ActorResourceStatusView;

struct ActorResourceStatusView;

struct ResourceHashEntry;
typedef struct ResourceHashEntry ResourceHashEntry;



struct OwnerStaticInstanceDrawGeometryVariant;
typedef struct OwnerStaticInstanceDrawGeometryVariant OwnerStaticInstanceDrawGeometryVariant;

struct ResourceHashEntry;

struct ResourceLoadRequest;
typedef struct ResourceLoadRequest ResourceLoadRequest;

struct CacheAllocationNodeView;

struct ResourceLoadRequest;








#endif
