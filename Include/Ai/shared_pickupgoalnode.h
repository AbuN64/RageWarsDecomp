#ifndef AI_SHARED_PICKUPGOALNODE_H
#define AI_SHARED_PICKUPGOALNODE_H
#include "Ai/portal_isnodemovementblocked.h"
struct Shared_PickupGoalNode;
struct CNavData_t;
#ifndef AI_PICKUP_GOAL_SEARCH_DECLARATIONS_H
#define AI_PICKUP_GOAL_SEARCH_DECLARATIONS_H
#include "types.h"
#include "Common/navigation_graph.h"
typedef struct Shared_PickupGoalNode Shared_PickupGoalNode;
struct Shared_PickupGoalNode {
    s32 id;
    u32 reservedElements[3];
    struct Shared_PickupGoalNode *next;
    f32 radius;
    u32 reservedElements1[7];
    s32 goal;
};

#include "Common/runtime_declarations.h"

extern CNavData g_navigationGraph;

extern void Portal_ResetSearchState(struct CNavData_t *graph);
extern void Route_ClearGoalList(s32 cNavData);
extern s32 Nav_AddPickupGoalsByObjectIds(s32 *ids);
extern void Route_SearchPathByKey(void *graph, s32 key);
extern void Route_ReconstructSearchPath(char *owner, s32 *output, s32 count);


#endif
#endif
