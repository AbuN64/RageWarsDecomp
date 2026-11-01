#ifndef ENGINE_VIRTUAL_VHANDLER_H
#define ENGINE_VIRTUAL_VHANDLER_H
#include "COMMON/OWNERRECAT8V2.H"
#include "COMMON/DESCRIPTORRECAT29.H"
#include "TYPES.H"

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
    ResourcePageMapping *mapping;
    ResourcePageThread *thread;
    u8 *slot;
} ResourcePageJob;

extern int Vhandler_RecycleTlbSlot(void);
extern void Vhandler_HandleResourcePageRequest(void);
extern void Vhandler_MapResourcePage(s16 flags, ResourcePageMapping *item, s32 unused, u8 *out);
extern void Vhandler_UnmapResourcePage(ResourcePageMapping *mapping);
extern void Virtual_AppendPageChainNode(Field_void_4*pageChain, void*pageNode);
extern void Virtual_PrependPageChainNode(Field_void_4 *, Field_void_4 *);
extern ResourcePageMapping *Virtual_AcquireRecycledPage(void);
extern void Virtual_ReleaseVirtualRegion(VirtualRegionOwnerState *);
extern void Virtual_AssignVirtualRegion(RegionDesc *desc);
#endif
