#ifndef AI_ROUTE_RELATION_GRID_H
#define AI_ROUTE_RELATION_GRID_H
#include "TYPES.H"
/* The relation lookup multiplies row*columns+column by the stored byte stride.
 * The ROM lookup reads that byte after this eight-byte buffer header. */
typedef struct RouteRelationBytes {
    s32 stride;
    s32 reserved;
    u8 entries[0];
} RouteRelationBytes;
/* The result is transported as a complete integer register; entries are bytes. */
s32 Route_GetRouteRelation(void *table, s32 row, s32 column);
#endif
