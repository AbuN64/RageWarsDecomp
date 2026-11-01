#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/NAVIGATION_GRAPH.H"
#include "include_asm.h"
#include "COMMON/NAVIGATION_ACTOR_SEARCH_VIEWS.H"
#include "TYPES.H"
#include "COMMON/SHAREDCALLBACK5.H"
#include "AI/NAV/NAV_SETPICKUPGOALWEIGHTS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "AI/NAV/PICKUPTARGET.H"

/* PICKUPGOAL.CPP */
/* 8020EAE0.CPP */
/* Commits a pending selection to the controller g_navigationGraph: returns at once when nothing is
   requested at 0xC, the request is already active at 0x4, or it continues the committed request at
   0x28 through valid links at 0x14 and 0x18 that are already current or that Portal_FindLinkIndex joins;
   otherwise it resets the controller, runs the pending release passes flagged at 0x2F4, 0x2F8 and
   0x2FC, rebuilds through Nav_SetPickupGoalWeights, loads the request, clears the controller's link word,
   reselects the active entry, copies the four link words from 0x14 and records the request as
   committed. Always returns 1. Written from its own assembly with early returns. */

extern CNavData g_navigationGraph;
extern s32 Portal_FindLinkIndex(s32 *, s32, s32);
extern void Portal_ResetSearchState(struct NavigationSearchGraphView *graph);
extern void Route_ClearGoalList(s32 cNavData);
extern void Nav_AddGoalNode(s32 *, s32);
extern void Route_SearchPathByKey(void *graph, s32 key);
extern void Route_ReconstructSearchPath(char *owner, s32 *output, s32 count);

s32 Nav_RebuildRequestedGoalRoute(void *controller) {
    s32 *base;
    s32 requested;
    s32 current;
    s32 link;

    base = &g_navigationGraph;
    if (base == 0) {
        return 1;
    }
    requested = ((NavigationRouteControllerView *)controller)->requestedGoalNode;
    if (requested == -1) {
        return 1;
    }
    current = ((NavigationRouteControllerView *)controller)->currentNode;
    if (current == requested) {
        return 1;
    }
    if (((NavigationRouteControllerView *)controller)->committed == requested) {
        link = ((NavigationRouteControllerView *)controller)->links[0];
        if (link != -1 && ((NavigationRouteControllerView *)controller)->links[1] != -1) {
            if (current == link) {
                return 1;
            }
            if (Portal_FindLinkIndex(base, current, link) != -1) {
                return 1;
            }
        }
    }
    Portal_ResetSearchState(base);
    if (((NavigationRouteControllerView *)controller)->releaseFlags[0] != 0) {
        Nav_SetLinkedActorNodeCosts(controller);
    }
    if (((NavigationRouteControllerView *)controller)->releaseFlags[1] != 0) {
        Nav_AccumulateNodeTickCosts(controller);
    }
    if (((NavigationRouteControllerView *)controller)->releaseFlags[2] != 0) {
        Nav_AddPickupCategoryCosts(controller);
    }
    Nav_SetPickupGoalWeights(controller);
    Route_ClearGoalList(base);
    Nav_AddGoalNode(base, ((NavigationRouteControllerView *)controller)->requestedGoalNode);
    base[6] = -1;
    Route_SearchPathByKey(base, ((NavigationRouteControllerView *)controller)->currentNode);
    Route_ReconstructSearchPath(base, &((NavigationRouteControllerView *)controller)->links[0], 4);
    ((NavigationRouteControllerView *)controller)->linkState = 0;
    ((NavigationRouteControllerView *)controller)->selection = -1;
    ((NavigationRouteControllerView *)controller)->committed = ((NavigationRouteControllerView *)controller)->requestedGoalNode;
    return 1;
}

extern char g_actorParticleEffectSystem[];
struct NavigationSearchGraphView; extern s32 Portal_FindNearestPointIndex(struct NavigationSearchGraphView *pointSet, void *point);
extern char *Portal_FindSearchNode(CNavData *, int);
/* Finds the nav node of obj and stores weight as its goal weight (+0x18). */
#define navigationNodeOf(graph, obj, out) do { (out) = Portal_FindSearchNode((graph), Portal_FindNearestPointIndex((graph), (obj))); } while (0)
#define navigationSetGoalWeight(graph, obj, weight) do { u8 *node_; navigationNodeOf(graph, obj, node_); ((NavigationSearchNode *)node_)->extra = (weight); } while (0)
void Nav_SetPickupGoalWeights(void *arg) {
    s32 *ctrl = &g_navigationGraph;
    u8 *node;
    u8 *link;
    s32 i;
    u8 *tbl = g_actorParticleEffectSystem;
    if (ctrl == 0) {
        return;
    }
    for (i = 0; i < 3; i++) {
        for (node = (u8 *)((IntrusiveList *)(tbl + ((char *)&((struct EffectSystem *)0)->lists - (char *)0) + i * sizeof(IntrusiveList)))->head; node != 0; node = (u8 *)((struct ParticleEffect *)node)->next) {
            switch (*(u16 *)(node + 4)) {
            case 1054:
                link = (u8 *)((struct ParticleEffect *)node)->owner;
                if (link == 0 || *link != 1 || !(((LevelActor *)link)->flags & 0x300000) || link == (u8 *)*(s32 **)arg) {
                    break;
                }
            case 1026:
            case 1028:
            case 1035:
            case 1039:
                navigationSetGoalWeight(ctrl, node + 8, 51200.0f);
                break;
            default:
                break;
            }
        }
    }
}

/* 800C6E84_11.CPP */
#if !(defined(VERSION_US_REV1))
const float g_Nav_SetLinkedActorNodeCostsConstantWords_de_eu_eu_x_us[3] = {
    51200.0f, 10.24f, -614.39996f,
};
#endif

#if defined(VERSION_EU_X)
void *k_PickupgoalEncodedWords[2] = {
    (void *)((char *)&Weapon_FireStateEnterCallbackEntry + 1120), (void *)((char *)&Weapon_FireStateEnterCallbackEntry + 948),
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/Nav_SetLinkedActorNodeCostsConstantWords_us_rev1.c */
const float g_Nav_SetLinkedActorNodeCostsConstantWords_us_rev1[1] = {
    51200.0f,
};

/* ROM-grounded data: src/Nav_AccumulateNodeTickCostsConstantWords.c */
const float g_Nav_AccumulateNodeTickCostsConstantWords[1] = {
    10.24f,
};

/* ROM-grounded data: src/Nav_AddPickupCategoryCostsConstantWords.c */
const float g_Nav_AddPickupCategoryCostsConstantWords[1] = {
    -614.39996f,
};
#endif

/* ROUTECOST__ROUTECOST.CPP */
extern s32 Route_GetRouteRelation(void *relationTable, s32 sourceNode, s32 destinationNode);

struct NavigationSearchGraphView; extern s32 Portal_SearchRelatedGoalPath(struct NavigationSearchGraphView *obj, s32 key, s32 requested, void *owner);

/** Reset the float field of each occupied player slot's table entry to the default value. */

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

/* NAV__ROUTECOST.CPP */
/* 800C1EE8.CPP */
#if defined(VERSION_DE)
extern char addrLow_Nav_SelectPickupGoal[];
void *k_NavEncodedWordsBlock4[2] = {
    (void *)(addrLow_Nav_SelectPickupGoal + 188), (void *)(addrLow_Nav_SelectPickupGoal + 200),
};
#endif
/* 800C6E84_4.CPP */
#if defined(VERSION_EU) || defined(VERSION_US)
#if defined(VERSION_EU)
#endif
#if defined(VERSION_US)
#endif
#endif

/* 800C6FD8.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800C6FD8 */
unsigned int g_NavEncodedWordsBlock4[2] = {
    0x3F800000, 0x3F800000,
};
#endif
