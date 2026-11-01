#include "include_asm.h"
#include "COMMON/SHAREDCALLBACK5.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/NAVIGATION_GRAPH.H"
#include "COMMON/NAVIGATION_NODE_AND_ROUTE_VIEWS.H"
#include <ultra64.h>
#include "TYPES.H"
#include "AI/NAV/NAV_SETPICKUPGOALWEIGHTS.H"
#include "AI/NAV/PORTAL.H"

f32 Graphu64_GetSquaredDistance(void *a, void *b);

extern void Route_ClearGoalList(void *);


extern void Nav_AddGoalNode(void *, s32);

extern void Portal_SearchPath(CNavData *, NavigationSearchNode *);

s32 Portal_CollectDirectedNeighbors(CNavData *graph, s32 nodeKey, s32 preferredNodeKey, s32 *neighborsOut, s32 reverseDirection) {
    NavigationPoint *point;
    NavigationBuffer *points;
    NavigationBuffer *m_pusNavLinksValue;
    s32 *neighborCursor;
    s32 i;
    s32 neighborCount;
    s32 j;
    s32 k;
    s32 reverseIsBidirectional;
    s32 forwardIsBidirectional;
    s32 kind;
    s32 reverseKind;
    NavigationPortal *portal;

    if (preferredNodeKey != -1) {
        points = graph->points;
        point = navigationRecord(points, preferredNodeKey);
    } else {
        point = NULL;
    }
    k = 0;
    neighborCount = 0;
    if (graph->m_nNavLinks > 0) {
        s32 reversibleKind4 = 4;
        s32 reversibleKind1 = 1;
        s32 reversibleKind7 = 7;
        s32 noRoom = -1;
        s32 forwardExcludedKind = 6;
        neighborCursor = neighborsOut;
        do {
            m_pusNavLinksValue = graph->m_pusNavLinks;
            portal = navigationRecord(m_pusNavLinksValue, k);
            if (reverseDirection != 0) {
                if (portal->second == nodeKey) {
                    neighborCount += 1;
                    *neighborCursor = (s32) portal->first;
                    neighborCursor += 1;
                }
                if (portal->first == nodeKey) {
                    kind = portal->kind;
                    if (kind != reversibleKind4) {
                        if ((s32) kind < 5) {
                            reverseIsBidirectional = 0;
                            if (kind != reversibleKind1) {

                            } else {
                                goto block_14;
                            }
                        } else {
                            reverseIsBidirectional = 0;
                            if (kind == reversibleKind7) {
                                goto block_14;
                            }
                        }
                    } else {
block_14:
                        reverseIsBidirectional = 1;
                    }
                    if (reverseIsBidirectional != 0) {
                        neighborCount += 1;
                        *neighborCursor = (s32) portal->second;
                        neighborCursor += 1;
                    }
                }
                if ((preferredNodeKey != noRoom) && (portal->first == nodeKey) && (portal->second == preferredNodeKey) && (point != NULL) && (navigation_point_flags(point) & 2)) {
                    *neighborCursor = preferredNodeKey;
                    neighborCursor += 1;
                    neighborCount += 1;
                }
            } else {
                if ((portal->first == nodeKey) && (portal->kind != forwardExcludedKind)) {
                    neighborCount += 1;
                    *neighborCursor = (s32) portal->second;
                    neighborCursor += 1;
                }
                if (portal->second == nodeKey) {
                    reverseKind = portal->kind;
                    if (reverseKind != reversibleKind4) {
                        if ((s32) reverseKind < 5) {
                            forwardIsBidirectional = 0;
                            if (reverseKind != reversibleKind1) {

                            } else {
                                goto block_32;
                            }
                        } else {
                            forwardIsBidirectional = 0;
                            if (reverseKind == reversibleKind7) {
                                goto block_32;
                            }
                        }
                    } else {
block_32:
                        forwardIsBidirectional = 1;
                    }
                    if (forwardIsBidirectional != 0) {
                        neighborCount += 1;
                        *neighborCursor = (s32) portal->first;
                        neighborCursor += 1;
                    }
                }
            }
            k += 1;
        } while (k < graph->m_nNavLinks);
    }
    if (preferredNodeKey == -1) return neighborCount;
    if (point != 0) {
            for (j = 0; j < neighborCount - 1; j++) {
                for (i = j + 1; i < neighborCount; i++) {
                    NavigationBuffer *table = graph->points;
                    s32 firstIndex = neighborsOut[j] * table->stride;
                    s32 secondIndex = neighborsOut[i] * table->stride;
                    void *first = table->data + firstIndex;
                    void *other = table->data + secondIndex;
                    f32 distance = Graphu64_GetSquaredDistance(&point->position.x, first);
                    if (Graphu64_GetSquaredDistance(&point->position.x, other) < distance) {
                        s32 saved = neighborsOut[j];
                        neighborsOut[j] = neighborsOut[i];
                        neighborsOut[i] = saved;
                    }
                }
            }
    }
    return neighborCount;
}

s32 Portal_SearchRelatedGoalPath(NavigationSearchGraphView *obj, s32 key, s32 requested, void *owner) {
    NavigationSearchNodeView *node;
    s32 found;

    {
        NavigationSearchNodeView *reset;

        reset = obj->nodes;
        while (reset != 0) {
            reset->value = g_portalResetSearchValue;
            reset->state = -1;
            reset->extra = 0;
            reset->cost = 0;
            reset->estimate = 0;
            reset->total = 0;
            reset->open = 0;
            reset->goal = 0;
            reset->parent = 0;
            reset = reset->next;
        }
    }

    obj->selected = -1;
    obj->value = g_portalRelatedGoalDefaultValue;
    Route_ClearGoalList(obj);
    found = 0;
    Nav_SetPickupGoalWeights(owner);
    Nav_AddGoalNode(obj, requested);

    {
        s32 i;
        s32 count;
        u32 mask;

        i = found;
        count = obj->count;
        if (count > 0) {
            mask = 0x04300000;
            do {
            char *record;
            s32 product;

            product = i * count;
            if (i != requested) {
                if (((struct PortalLinkAvailabilityView *) (obj->links->data + ((product + requested) * obj->links->stride)))->available != 0) {
                    record = (char *)obj->records +
                             (i * obj->records->stride + 8);
                    if (record != 0 && (((NavigationNodeFlagsView *)(record))->flags.v0 & mask) == 0) {
                        Nav_AddGoalNode(obj, i);
                        found++;
                    }
                }
            }
                i++;
                count = obj->count;
            } while (i < count);
        }

        if (found == 0) {
            for (i = 0; i < obj->count; i++) {
                char *record;
                s32 product;

                product = i * obj->count;
                if (i != requested) {
                    if (((struct PortalLinkAvailabilityView *) (obj->links->data + ((product + requested) * obj->links->stride)))->available != 0) {
                        record = (char *)obj->records +
                                 (i * obj->records->stride + 8);
                        if (record != 0 && (((NavigationNodeFlagsView *)(record))->flags.v1 & 0x400) == 0) {
                            Nav_AddGoalNode(obj, i);
                        }
                    }
                }
            }
        }
    }

    node = obj->nodes;
    if (node == 0) {
        goto not_found;
    }
    do {
        if (node->key == key) {
            goto search_done;
        }
        node = node->next;
    } while (node != 0);
not_found:
    node = 0;
search_done:
    Portal_SearchPath(obj, node);
    return obj->selected = obj->result;
}

extern f32 g_portalFirstGoalEmptyDistance;
s32 Portal_SearchPortalRoute(CNavData *, s32, s32, u8, s32, f32 *, f32);
/* Collects the nodes linked to key, with the link index of each, into out/edges; returns how many. */
static __inline__ s32 navigationNeighbors(CNavData *graph, s32 key, s32 *out, s32 *edges) {
    s32 i;
    s32 count = 0;
    for (i = 0; i < graph->m_nNavLinks; i++) {
        NavigationPortal *portal = navigationRecord(graph->m_pusNavLinks, i);
        if (portal->first == key) {
            out[count] = portal->second;
            edges[count] = i;
            count++;
        }
        if (portal->second == key) {
            out[count] = portal->first;
            edges[count] = i;
            count++;
        }
    }
    return count;
}
/* Returns startNode when one of its own links has portalKind, else the portal node the nearest
 * neighbor route reaches within maxDepth links (-1 when none). */
s32 Portal_FindPortalRoute(CNavData *graph, s32 startNode, u8 portalKind, s32 maxDepth) {
    s32 neighborNodes[64];
    s32 neighborLinks[64];
    f32 distance;
    f32 *origin;
    f32 bestDistance;
    s32 foundNode;
    s32 result;
    s32 index;
    s32 neighborCount;
    NavigationPortal *portal;

    result = -1;
    bestDistance = g_portalFirstGoalEmptyDistance;
    for (index = 0; index < graph->m_nNavLinks; index++) {
        portal = navigationRecord(graph->m_pusNavLinks, index);
        if (portal->first == startNode && portal->kind == portalKind) return startNode;
    }
    origin = navigationRecord(graph->points, startNode);
    neighborCount = navigationNeighbors(graph, startNode, neighborNodes, neighborLinks);
    for (index = 0; index < neighborCount; index++) {
        distance = Graphu64_GetSquaredDistance(origin, navigationRecord(graph->points, neighborNodes[index]));
        foundNode = Portal_SearchPortalRoute(graph, startNode, neighborNodes[index], portalKind, maxDepth - 1, &distance, bestDistance);
        if (foundNode != -1) {
            bestDistance = distance;
            result = foundNode;
        }
    }
    return result;
}

extern f32 g_portalRelatedGoalEmptyDistance;
/* Depth-limited search from currentNode (entered from previousNode): returns currentNode when one of its links
 * has portalKind, else the portal node of the shortest route under distanceLimit (-1 when none); stores that
 * route's length in *routeDistance. */
s32 Portal_SearchPortalRoute(CNavData *graph, s32 previousNode, s32 currentNode, u8 portalKind, s32 remainingDepth, f32 *routeDistance, f32 distanceLimit) {
    s32 neighborNodes[64];
    s32 neighborLinks[64];
    f32 candidateDistance;
    f32 *previousPosition;
    f32 bestDistance;
    s32 result;
    s32 index;
    s32 neighborCount;
    s32 portalNode;
    NavigationPortal *portal;

    bestDistance = g_portalRelatedGoalEmptyDistance;
    result = -1;
    for (index = 0; index < graph->m_nNavLinks; index++) {
        portal = navigationRecord(graph->m_pusNavLinks, index);
        if (portal->first == currentNode && portal->kind == portalKind) return currentNode;
    }
    if (remainingDepth == 0) return -1;
    previousPosition = navigationRecord(graph->points, previousNode);
    neighborCount = navigationNeighbors(graph, previousNode, neighborNodes, neighborLinks);
    for (index = 0; index < neighborCount; index++) {
        f32 *point = navigationRecord(graph->points, neighborNodes[index]);
        if (point != previousPosition) {
            candidateDistance = *routeDistance + Graphu64_GetSquaredDistance(previousPosition, point);
            if (candidateDistance < distanceLimit) {
                portalNode = Portal_SearchPortalRoute(graph, currentNode, neighborNodes[index], portalKind, remainingDepth - 1, &candidateDistance, distanceLimit);
            } else {
                portalNode = -1;
            }
            if (portalNode != -1 && candidateDistance < bestDistance) {
                bestDistance = candidateDistance;
                result = portalNode;
            }
        }
    }
    if (bestDistance < distanceLimit) {
        *routeDistance = bestDistance;
    }
    return result;
}

extern f32 g_portalEstimateEmptyDistance;
extern const f32 g_portalExitEstimateEmptyDistance;
extern f32 Graphu64_GetPointDistance(f32 *, f32 *);

f32 Portal_EstimateGoalDistance(CNavData *graph, NavigationSearchNode *node)
{
    s32 neighbors[64];
    s32 portalIds[64];
    NavigationBuffer *portalTable;
    NavigationBuffer *exitPoints;
    NavigationBuffer *goalPoints;
    NavigationBuffer *exitGoalPoints;
    f32 empty;
    f32 distance;
    f32 exitDistance;
    f32 best;
    s32 goal;
    s32 exitGoal;
    s32 goalIndex;
    s32 neighborIndex;
    s32 neighborCount;
    NavigationPortal *portal;
    NavigationPoint *origin;
    NavigationPoint *exitPoint;
    best = g_portalEstimateEmptyDistance;
    empty = best;
    origin = navigationRecord(graph->points, node->key);
    for (goalIndex = 0; goalIndex < 64; goalIndex++)
    {
        goal = graph->m_nGoalList[goalIndex];
        if (goal == -1)
        {
            continue;
        }
        goalPoints = graph->points;
        distance = Graphu64_GetPointDistance(&origin->position.x, navigationRecord(goalPoints, goal));
        if ((distance < best) || (best == empty))
        {
            best = distance;
        }
    }

    for (goalIndex = 0; goalIndex < 64; goalIndex++)
    {
        neighbors[goalIndex] = -1;
        portalIds[goalIndex] = -1;
    }

    {
        s32 key = node->key;
        s32 *neighborBase = neighbors;
        s32 *portalBase = portalIds;
        s32 portalIndex = 0;
        s32 count = 0;
        s32 *neighborOut;
        s32 *portalOut;
        NavigationBuffer *links;
        NavigationPortal *link;
        if (graph->m_nNavLinks > portalIndex)
        {
            portalOut = portalBase;
            neighborOut = neighborBase;
            do
            {
                links = graph->m_pusNavLinks;
                link = navigationRecord(links, portalIndex);
                if (link->first == key)
                {
                    count += 1;
                    *neighborOut = link->second;
                    *portalOut = portalIndex;
                    portalOut++;
                    neighborOut++;
                }
                if (link->second == key)
                {
                    count += 1;
                    *neighborOut = link->first;
                    *portalOut = portalIndex;
                    portalOut++;
                    neighborOut++;
                }
                portalIndex += 1;
            }
            while (portalIndex < graph->m_nNavLinks);
        }
        neighborCount = count;
    }
    {
        for (neighborIndex = 0; neighborIndex < neighborCount; neighborIndex++)
        {
            portalTable = graph->m_pusNavLinks;
            portal = navigationRecord(portalTable, portalIds[neighborIndex]);
            if ((portal->kind == 9) && (portal->first == node->key))
            {
                exitPoints = graph->points;
                exitPoint = navigationRecord(exitPoints, portal->second);
                for (goalIndex = 0; goalIndex < 64; goalIndex++)
                {
                    exitGoal = graph->m_nGoalList[goalIndex];
                    if (exitGoal == -1)
                    {
                        continue;
                    }
                    exitGoalPoints = graph->points;
                    exitDistance = Graphu64_GetPointDistance(&exitPoint->position.x, navigationRecord(exitGoalPoints, exitGoal));
                    if ((exitDistance < best) || (best == g_portalExitEstimateEmptyDistance))
                    {
                        best = exitDistance;
                    }
                }

            }
        }

    }
    return best;
}

extern const f32 g_portalSearchEmptyTotal;
extern f32 g_portalSearchInitialMinimum;
extern f32 g_portalFlaggedNodeCost;

static inline s32 navHasOpenNode(CNavData *graph, s32 status) {
    NavigationSearchNode *node = graph->nodes;
    while (node) {
        if (node->open == status) return 1;
        node = node->next;
    }
    return 0;
}
static inline NavigationSearchNode *navFindNode(CNavData *graph, s32 key) {
    NavigationSearchNode *node = graph->nodes;
    while (node) {
        if (node->key == key) return node;
        node = node->next;
    }
    return 0;
}
/* A* search from start over the link graph: repeatedly closes the open node with the lowest total, stores its
 * key in graph->result once it is a goal, otherwise relaxes the cost of every node it links to. */
void Portal_SearchPath(CNavData *graph, NavigationSearchNode *start) {
    s32 neighbors[64];
    s32 portals[64];
    NavigationPoint *origin;
    NavigationPoint *destination;
    f32 initialEstimate;
    f32 estimate;
    f32 cost;
    f32 distance;
    f32 edgeCost;
    s32 neighborKey;
    s32 state;
    s32 index;
    s32 count;
    const s32 open = 1;
    s32 reversible;
    u8 edgeKind;
    NavigationPortal *portal;
    NavigationSearchNode *current;
    NavigationSearchNode *node;
    NavigationSearchNode *best;
    f32 minimum;
    NavigationSearchNode *next;

    start->cost = 0.0f;
    initialEstimate = Portal_EstimateGoalDistance(graph, start);
    start->estimate = initialEstimate;
    start->parent = 0;
    start->open = open;
    start->total = start->cost + initialEstimate;
    while (navHasOpenNode(graph, open)) {
        node = graph->nodes;
        best = 0;
        minimum = g_portalSearchInitialMinimum;
        while (node) {
            if (node->open == open) {
                if (node->total < minimum) {
                    best = node;
                    minimum = node->total;
                } else if (minimum == g_portalSearchEmptyTotal) {
                    best = node;
                    minimum = node->total;
                }
            }
            node = node->next;
        }
        if (best) best->open = 0;
        current = best;
        origin = navigationRecord(graph->points, current->key);
        if (current->goal != 0) {
            graph->result = current->key;
            return;
        }
        for (index = 0; index < 64; index++) {
            neighbors[index] = -1;
            portals[index] = -1;
        }
        count = navigationNeighbors(graph, current->key, neighbors, portals);
        for (index = 0; index < count; index++) {
            f32 minimumCost = 0.0f;
            neighborKey = neighbors[index];
            destination = navigationRecord(graph->points, neighborKey);
            next = navFindNode(graph, neighborKey);
            portal = navigationRecord(graph->m_pusNavLinks, portals[index]);
            switch (portal->kind) {
                case 1:
                case 4:
                case 7:
                    reversible = 1;
                    break;
                default:
                    reversible = 0;
                    break;
            }
            if (reversible == 0 && portal->first != current->key) continue;
            edgeKind = portal->kind;
            if (edgeKind == 10) continue;
            if (edgeKind == 11) continue;
            if (edgeKind == 9) {
                distance = 0.0f;
            } else {
                distance = Graphu64_GetPointDistance(&destination->position.x, &origin->position.x);
            }
            edgeCost = distance + next->extra;
            if (navigation_point_flags(destination) & 0x400) {
                edgeCost += g_portalFlaggedNodeCost;
            }
            if (edgeCost < minimumCost) {
                edgeCost = minimumCost;
            }
            state = next->open;
            cost = current->cost + edgeCost;
            if (((state ^ 2) == 0) || ((state ^ 1) == 0)) {
                if (!(next->cost <= cost)) {
                    goto update_neighbor;
                }
            } else {
update_neighbor:
                next->parent = current;
                next->cost = cost;
                estimate = Portal_EstimateGoalDistance(graph, next);
                next->estimate = estimate;
                next->total = next->cost + estimate;
                if ((next->open ^ 2) == 0) {
                    next->open = 0;
                }
                if ((next->open ^ open) != 0) {
                    next->open = open;
                }
            }
        }
        current->open = 2;
    }
}
