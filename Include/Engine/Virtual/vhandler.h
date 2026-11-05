#ifndef ENGINE_VIRTUAL_VHANDLER_H
#define ENGINE_VIRTUAL_VHANDLER_H
#include "Common/virtual_pager.h"
#include "Common/sky_layers.h"
#include "types.h"

struct ResourcePageThread;
struct ListNodeNextView;
struct RegionDesc;
struct ResourcePageMapping;
struct VirtualRegionOwnerState;
struct VirtualRegionOwnerState {
    s32 reservedWord;
    u32 handle;
    s32 queue;
};

struct RegionDesc {
    s32 pad0;
    s32 size;
    struct Region *region;
    void *mapping;
};

typedef struct ResourcePageThread {
    u8 reserved0[0x12]; s16 state;
    u8 reserved14[3]; u8 slot;
    u8 reserved18[0x108]; u32 message, address;
} ResourcePageThread;

typedef struct ResourcePageJob {
    u32 reserved0; u8 *source; u32 size;
    u16 page; u8 reservedE[2];
    struct ResourcePageMapping *mapping;
    struct ResourcePageThread *thread;
    u8 *slot;
} ResourcePageJob;

extern int Vhandler_RecycleTlbSlot(void);
extern void Vhandler_HandleResourcePageRequest(void);
extern void Vhandler_MapResourcePage(s16 flags, struct ResourcePageMapping *item, s32 pageVirtualAddress, u8 *out);
extern void Vhandler_UnmapResourcePage(struct ResourcePageMapping *mapping);
extern void Virtual_AppendPageChainNode(struct ListNodeNextView*pageChain, void*pageNode);
extern void Virtual_PrependPageChainNode(struct ListNodeNextView *pageChain, struct ListNodeNextView *pageNode);
extern struct ResourcePageMapping *Virtual_AcquireRecycledPage(void);
extern void Virtual_ReleaseVirtualRegion(struct VirtualRegionOwnerState *);
extern void Virtual_AssignVirtualRegion(struct RegionDesc *desc);
/* Pager state and entry points that exist only at their map addresses (no C definition). */
extern char g_cartridgeReadWorker[];
extern struct ResourcePageMapping *g_pagerLruHead;
extern struct Region g_pagerRegionHead;
extern char g_pagerDispatcherRomEntry[];
extern char g_pagerPendingQueue[];

#endif
