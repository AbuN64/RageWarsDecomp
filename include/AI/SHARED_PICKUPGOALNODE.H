#ifndef AI_SHARED_PICKUPGOALNODE_H
#define AI_SHARED_PICKUPGOALNODE_H
struct NavigationSearchGraphView;
#ifndef AI_PICKUP_GOAL_SEARCH_DECLARATIONS_H
#define AI_PICKUP_GOAL_SEARCH_DECLARATIONS_H
#include "TYPES.H"
typedef struct Shared_PickupGoalNode Shared_PickupGoalNode;
struct Shared_PickupGoalNode {
    s32 id;
    u32 reservedElements[3];
    Shared_PickupGoalNode *next;
    f32 radius;
    u32 reservedElements1[7];
    s32 goal;
};

#include "COMMON/RUNTIME_DECLARATIONS.H"

extern PickupGoalNodeList g_navigationGraph;

extern void Portal_ResetSearchState(struct NavigationSearchGraphView *graph);
extern void Route_ClearGoalList(PickupGoalNodeList *list);
extern s32 Nav_AddPickupGoalsByObjectIds(s32 *ids);
extern void Route_SearchPathByKey(PickupGoalNodeList *list, s32 key);
extern Shared_PickupGoalNode *Portal_FindSearchNode(PickupGoalNodeList *list, u32 key);
extern void Route_ReconstructSearchPath(PickupGoalNodeList *list, s32 *output, s32 count);


#endif
#endif
