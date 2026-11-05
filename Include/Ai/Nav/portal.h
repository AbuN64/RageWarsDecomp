#ifndef AI_NAV_PORTAL_H
#define AI_NAV_PORTAL_H
#include "Ai/nav_symbols.h"
#include "Common/navigation_graph.h"
#include "types.h"
struct NavigationSearchNode;
extern f32 Portal_EstimateGoalDistance(CNavData*graph, struct NavigationSearchNode*node);
struct CNavData_t; extern void Portal_AssignPlatformEndpoints(struct CNavData_t *graph);
#endif
