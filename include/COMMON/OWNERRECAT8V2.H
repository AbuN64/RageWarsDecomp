#ifndef COMMON_OWNERRECAT8V2_H
#define COMMON_OWNERRECAT8V2_H
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"

struct BlockVirtualFreeVirtualRegion;
typedef struct BlockVirtualFreeVirtualRegion BlockVirtualFreeVirtualRegion;

struct VirtualRegionOwnerState;

struct VirtualRegionOwnerState;
typedef struct VirtualRegionOwnerState VirtualRegionOwnerState;

extern void Virtual_ReleaseVirtualRegion(VirtualRegionOwnerState *allocation);

struct Channels;
typedef struct Channels Channels;



struct DialogPlayerState;




struct NodeVirtualAcquireRecycledPage;
typedef struct NodeVirtualAcquireRecycledPage NodeVirtualAcquireRecycledPage;


struct Block10;
typedef struct Block10 Block10;

union PagerSlotLookupStorage;
union PagerSlotLookupStorage {
    u8 marks[4096];
    struct { u8 padding[0x3CF]; u8 indices[96]; } first;
    struct { u8 padding[0x3D0]; u8 indices[96]; } second;
};

struct ResourcePageMapping;
struct ResourcePageMapping {
    struct ResourcePageMapping *next;
    struct ResourcePageMapping *prev;
    u16 id;
    union { u16 padA; struct { u8 index; u8 slot; }; };
    s32 age;
};

extern float g_collisionMotionRetreatDistance;

struct Region;
struct Region {
    struct Region *next;
    u16 start;
    u16 pages;
    u8 (*source)[4096];
    s32 padC;
    u8 *map;
    s32 pad14;
};

struct Region;
struct RegionDesc;

struct RegionDesc;
typedef struct RegionDesc RegionDesc;

extern void Virtual_AssignVirtualRegion(RegionDesc *desc);


struct SlotVirtualInitializePagerEuroExtended;
typedef struct SlotVirtualInitializePagerEuroExtended SlotVirtualInitializePagerEuroExtended;

struct ResourcePageMapping;
typedef struct ResourcePageMapping ResourcePageMapping;

struct BlockVirtualFreeVirtualRegion;

struct Channels;
struct Channels {
    char pad0[0x1C];
};

struct SlotVirtualInitializePagerEuroExtended;
struct SlotVirtualInitializePagerEuroExtended {
    union {
        struct { s32 a; s32 b; char pad8[2]; u8 index; char padB[5]; };
        ResourcePageMapping chain;
    };
};

/* The first 0x20 bytes of the resource pager state: request statistics, copied out whole by Vhandler_GetPagerCounters. */
struct PagerCounters {
    s32 requests;
    s32 misses;
    u32 lastAddress;
    char padC[0x20 - 0xC];
};
struct PagerState;


union PagerSlotLookupStorage;
typedef union PagerSlotLookupStorage PagerSlotLookupStorage;

/* g_pagerPageMappings: the page mappings of the resource pager */
typedef struct ResourcePageMapping SlotVirtualReleaseVirtualRegion;

struct NodeVirtualFindRegionForPage;
typedef struct NodeVirtualFindRegionForPage NodeVirtualFindRegionForPage;

struct NodeVirtualFindRegionForPage;
struct NodeVirtualFindRegionForPage {
    struct NodeVirtualFindRegionForPage *next;
    u16 f4;
    u16 f6;
};

struct Region;
typedef struct Region Region;

struct PagerState;
typedef struct PagerState PagerState;


struct Block10;


struct NodeVirtualAcquireRecycledPage;
struct NodeVirtualAcquireRecycledPage {
    struct NodeVirtualAcquireRecycledPage *next;
    u16 start;
    u16 size;
    char pad8[8];
    u8 *data;
};



#endif
