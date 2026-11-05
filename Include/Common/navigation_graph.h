#ifndef COMMON_NAVIGATION_GRAPH_H
#define COMMON_NAVIGATION_GRAPH_H
#include "types.h"
#include "Common/sharedplayer.h"

struct NavigationBuffer;
struct NavigationPoint;
struct Player;
struct NavigationPlatform;

typedef struct NavigationBuffer { s32 stride; s32 count; u8 data[1]; } NavigationBuffer;

/* The ROM attribute word holds flags in its high half and the object id in its low half. Guest memory keeps the word
   numeric, so a little-endian host finds the low half (object id) at the first halfword address. */
typedef struct NavigationPoint {
    CVector3 position;
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    u16 objectId;
    u16 flags;
#else
    u16 flags;
    u16 objectId;
#endif
} NavigationPoint;

typedef struct NavigationPortal { u16 first, second; u8 kind; } NavigationPortal;

typedef struct NavigationSearchNode {
    s32 key; /* 0x0 */
    f32 value; /* 0x4 */
    s32 state; /* 0x8 */
    struct NavigationSearchNode *previous; /* 0xC: List_InitializeIntrusive prevOffset */
    struct NavigationSearchNode * next; /* 0x10 */
    f32 wait; /* 0x14 */
    f32 extra; /* 0x18 */
    f32 cost; /* 0x1C */
    f32 estimate; /* 0x20 */
    f32 total; /* 0x24 */
    s32 open; /* 0x28 */
    s32 goal; /* 0x2C */
    struct NavigationSearchNode * parent; /* 0x30 */
    struct Player * object; /* 0x34 */
    s32 ticks; /* 0x38 */
    s32 delay; /* 0x3C */
    struct NavigationPlatform * platform; /* 0x40 */
    CVector3 endpoint; /* 0x44 */
} NavigationSearchNode;

typedef struct CNavData_t {
    struct NavigationBuffer * points; /* 0x0 */
    s32 m_nNavNodes; /* 0x4 */
    struct NavigationBuffer * m_pusNavLinks; /* 0x8 */
    s32 m_nNavLinks; /* 0xC */
    struct NavigationBuffer * links; /* 0x10 */
    s32 visionCount; /* 0x14: resource header copied by Scene_LoadLevelResources */
    s32 result; /* 0x18 */
    f32 value; /* 0x1C */
    s32 selected; /* 0x20 */
    IntrusiveList searchNodes; /* 0x24: links at node +0xC/+0x10 */
    s32 m_nGoalList[64]; /* 0x38 */
} CNavData;

/* Resource tables store records with a runtime stride. */
static __inline__ void *navigationRecord(struct NavigationBuffer *table, s32 index) { return table->data + index * table->stride; }
/* The point's flags and object id read as the one ROM attribute word (tests that span both halves). */
static __inline__ u32 navigation_attributes(const struct NavigationPoint *point) {
    u32 value;
    __builtin_memcpy(&value, &point->position + 1, sizeof(value));
    return value;
}
static __inline__ u16 navigation_point_flags(const struct NavigationPoint *point) {
    return point->flags;
}
static __inline__ u16 navigation_point_object_id(const struct NavigationPoint *point) {
    return point->objectId;
}
static __inline__ void navigation_point_clear_flags(struct NavigationPoint *point, u16 flags) {
    point->flags = (u16)(point->flags & ~flags);
}
#endif
