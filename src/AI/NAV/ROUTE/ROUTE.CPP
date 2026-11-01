#include "COMMON/SHAREDCALLBACK5.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/NAVIGATION_GRAPH.H"
#include "AI/ROUTE_RELATION_GRID.H"
#include "COMMON/NAVIGATION_NODE_AND_ROUTE_VIEWS.H"
#include "TYPES.H"

extern void Portal_ResetSearchState(void *graph);

extern void Route_ClearGoalList(s32);

extern void Nav_AddGoalNode(void *, s32);

extern void Route_SearchPathByKey(void *graph, s32 startKey);

extern void Portal_SearchPath(void *graph, void *node);

void Route_SearchSingleGoalPath(void *graph, s32 startKey, s32 goalKey) {
    Portal_ResetSearchState(graph);
    Route_ClearGoalList((s32) graph);
    Nav_AddGoalNode(graph, goalKey);
    Route_SearchPathByKey(graph, startKey);
}

/** Find a keyed node in the object's list and pass it to Portal_SearchPath. */
void Route_SearchPathByKey(void *graph, s32 key) {
    NavigationSearchNode *node = ((CNavData *)graph)->nodes;

    if (node == 0) {
        goto not_found;
    }
loop:
    if (node->key == key) {
        goto found;
    }
    node = node->next;
    if (node != 0) {
        goto loop;
    }
not_found:
    node = 0;
found:
    Portal_SearchPath(graph, node);
}

void Route_ReconstructSearchPath(char *owner, s32 *output, s32 count) {
    s32 i;
    s32 done;
    s32 value;
    NavigationSearchNode *node;

    for (i = 0; i < count; i++) {
        output[i] = -1;
    }

    node = ((CNavData *)owner)->nodes;
    value = ((CNavData *)owner)->result;
    done = 0;
    if (node == 0) {
        goto not_found;
    }
    do {
        if (node->key == value) {
            owner = (char *)node;
            goto found;
        }
        node = node->next;
    } while (node != 0);
not_found:
    owner = 0;
found:
    if (((NavigationSearchNode *)owner)->parent == 0) {
        output[0] = ((NavigationSearchNode *)owner)->key;
        return;
    }

    while (done == 0) {
        for (i = count - 1; i > 0; i--) {
            output[i] = output[i - 1];
        }
        output[0] = ((NavigationSearchNode *)owner)->key;
        owner = (char *)((NavigationSearchNode *)owner)->parent;
        if (((NavigationSearchNode *)owner)->parent == 0) {
            done = 1;
        }
    }
}

s32 Route_GetRouteRelation(void *relationTable, s32 sourceNode, s32 destinationNode) {
    RouteRelationTableView *table = relationTable;
    RouteRelationBytes *bytes = (RouteRelationBytes *)table->relationBytes;
    s32 index = (sourceNode * table->nodeCount + destinationNode) * bytes->stride;
    return *(index + bytes->entries);
}

void Route_ClearGoalList(s32 cNavData) {
    CNavData *graph = (CNavData *)cNavData;
    s32 i;
    s32 value = -1;
    for (i = 63; i >= 0; i--) {
        graph->m_nGoalList[i] = value;
    }
}
