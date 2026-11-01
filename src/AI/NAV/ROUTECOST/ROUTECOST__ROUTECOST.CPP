#include "include_asm.h"
#include "COMMON/NAVIGATION_ACTOR_SEARCH_VIEWS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/NAVIGATION_GRAPH.H"
#include "TYPES.H"
#include "AI/NAV/PICKUPTARGET.H"

extern s32 Route_GetRouteRelation(void *relationTable, s32 sourceNode, s32 destinationNode);

struct NavigationSearchGraphView; extern s32 Portal_SearchRelatedGoalPath(struct NavigationSearchGraphView *obj, s32 key, s32 requested, void *owner);

/** Reset the float field of each occupied player slot's table entry to the default value. */


extern char *Portal_FindSearchNode(CNavData *, int);
extern CNavData g_navigationGraph;

extern void *Portal_GetGraphPoint(void *, s32);

s32 Nav_UpdateRouteIntermediateGoal(NavigationRouteControllerView *owner) {
    s32 *base;

    base = &g_navigationGraph;
    if (base != 0) {
        if (owner->destinationNode == -1) {
            return 1;
        }
        if (owner->currentNode == owner->destinationNode) {
            return 1;
        }
        if (Route_GetRouteRelation(base, owner->currentNode, owner->destinationNode) == 0) {
            owner->requestedGoalNode = Portal_SearchRelatedGoalPath(base, owner->currentNode, owner->destinationNode, owner);
        }
    }
    return 1;
}

void Nav_SetLinkedActorNodeCosts(char *actor) {
    CNavData *table = &g_navigationGraph;
    int i;
    float value;

    if (table != 0) {
        value = g_linkedActorNodeDefaultCost;
        for (i = 0; i < 10; i++) {
            Actor1DC *a = ((struct NavigationActorListEntryView *) (actor + (i * 4)))->actor;
            if (a != 0) {
                ((struct NavigationNodeCostView *) Portal_FindSearchNode(table, ((struct ResourceKeyView *) ((NavigationActorSearchStateView *) a->info)->resourceKeyRecord)->key))->cost = value;
            }
        }
    }
}

void Nav_AccumulateNodeTickCosts(void) {
    NavigationSearchNode *node;
    f32 k;

    node = g_pickupNavigationGoalList;
    if (node != 0) {
        k = g_navigationNodeTickCostScale;
        do {
            node->extra =
                node->extra +
                (f32) (node->ticks * 30) * k;
            node = node->next;
        } while (node != 0);
    }
}

void Nav_AddPickupCategoryCosts(void) {
    CNavData *base;
    NavigationSearchNode *node;
    NavigationPoint *result;
    f32 addVal;
    u16 objectId;

    base = &g_navigationGraph;
    node = base->nodes;
    if (node != 0) {
        addVal = g_pickupCategoryNodeCost;
        do {
            result = Portal_GetGraphPoint(base, node->key);
            if (navigation_point_flags(result) & 1) {
                objectId = navigation_point_object_id(result);
                if (Nav_IsPickupObjectInPairCategory(objectId) != 0 || Nav_IsPickupObjectInSixEntryCategory(navigation_point_object_id(result)) != 0) {
                    node->extra = node->extra + addVal;
                }
            }
            node = node->next;
        } while (node != 0);
    }
}




#if defined(VERSION_US)
const unsigned int k_RoutecostEncodedWords[2] = {
    0x14000000, 0x00000E43,
};
#endif
