#ifndef AI_NAV_SEARCH_NODE_STATE_H
#define AI_NAV_SEARCH_NODE_STATE_H
#include "COMMON/NAVIGATION_NODE_AND_ROUTE_VIEWS.H"
extern int Nav_OpenSearchNode(void *navigationSearchNode);
extern void Nav_CloseSearchNode(void *object);
extern void Nav_ClearSearchNodeStatus(void *controller);
extern int Nav_IsSearchNodeClosed(void *navigationSearchNode);
extern int Nav_IsSearchNodeOpen(void *navigationSearchNode);
extern void *Nav_TakeLowestCostOpenNode(void *cNavData);
#endif
