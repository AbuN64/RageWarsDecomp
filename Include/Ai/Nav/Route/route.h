#ifndef AI_NAV_ROUTE_ROUTE_H
#define AI_NAV_ROUTE_ROUTE_H
#include "types.h"

extern s32 Route_GetRouteRelation(void *relationTable, s32 sourceNode, s32 destinationNode);
extern void Route_ClearGoalList(s32 cNavData);
extern void Route_ReconstructSearchPath(char *owner, s32 *output, s32 count);
extern void Route_SearchPathByKey(void *graph, s32 key);

#endif
