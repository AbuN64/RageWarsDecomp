#ifndef AI_NAV_ROUTECOST_H
#define AI_NAV_ROUTECOST_H
struct NavigationRouteControllerView;
extern s32 Nav_RebuildRequestedGoalRoute(void *controller);
extern s32 Nav_UpdateRouteIntermediateGoal(struct NavigationRouteControllerView *owner);
#endif
