#include "Ai/ai_functions.h"
#include "Ai/nav_symbols.h"
#include "Common/ai_behaviour_types.h"
#include "Common/navigation_graph.h"
#include "Ai/route_relation_grid.h"
#include "Common/navigation_node_and_route_views.h"
#include "types.h"
#include "Ai/portal_isnodemovementblocked.h"
#include "Ai/Nav/Route/route.h"

extern void Portal_ResetSearchState(struct CNavData_t *graph);


struct CNavData_t;

extern void Route_SearchPathByKey(void *graph, s32 startKey);

struct CNavData_t; struct NavigationSearchNode; extern void Portal_SearchPath(struct CNavData_t *graph, struct NavigationSearchNode *start);

void Route_SearchSingleGoalPath(void *graph, s32 startKey, s32 goalKey) {
    Portal_ResetSearchState(graph);
    Route_ClearGoalList((s32) graph);
    Nav_AddGoalNode(graph, goalKey);
    Route_SearchPathByKey(graph, startKey);
}

/** Find a keyed node in the object's list and pass it to Portal_SearchPath. */
void Route_SearchPathByKey(void *graph, s32 key) {
    NavigationSearchNode *node = ((CNavData *)graph)->searchNodes.head;

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

    node = ((CNavData *)owner)->searchNodes.head;
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
    CNavData *table = relationTable;
    NavigationBuffer *bytes = table->links;
    s32 index = (sourceNode * table->m_nNavNodes + destinationNode) * bytes->stride;
    return *(index + bytes->data);
}

void Route_ClearGoalList(s32 cNavData) {
    CNavData *graph = (CNavData *)cNavData;
    s32 i;
    s32 value = -1;
    for (i = 63; i >= 0; i--) {
        graph->m_nGoalList[i] = value;
    }
}
