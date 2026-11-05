#ifndef AI_PORTAL_ISNODEMOVEMENTBLOCKED_H
#define AI_PORTAL_ISNODEMOVEMENTBLOCKED_H
#include "Ai/shared_pickupgoalnode.h"
#include "types.h"
#include "Common/navigation_node_and_route_views.h"
extern void *Portal_GetStridedTableEntry(struct CNavData_t *object, int index);

extern void * Portal_GetGraphPoint(void *table, int index);

extern void * Portal_FindSearchNode(char *object, s32 current);
struct CNavData_t;
extern int Portal_FindLinkIndex(struct CNavData_t *graph, int from, int to);

#endif
