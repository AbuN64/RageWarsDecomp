#include "COMMON/ROUTE_CHASE_RECORDS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/TRIPLE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"
#include "COMMON/SELF.H"
#include "include_asm.h"

/* Runs a computer player's patrol step: starts its route at 0x224 on the first route of g_world_AchieveUpdateresultsscreen,
   or random roaming (-2) when there are none; once within g_patrolGoalArrivalDistance of its goal node it advances the
   route position at 0x228 (wrapping at the route length) and drops the goal; a dropped goal is then
   taken from the route through Scene_GetPlatformRoutePoint and Portal_FindNearestPointIndex_Patrol, or a random node of g_navigationGraph when
   roaming; finally runs Nav_SteerAlongRoute, Nav_RunBehaviorHandler and Nav_UpdatePlayerSteering. */













extern RoutePatrolNodes g_navigationGraph;



extern Clip *Scene_GetPlatformRoute(PatrolRouteSet *set, s32 route);
extern s32 Scene_GetPlatformRoutePoint(PatrolRouteSet *set, s32 route, s32 pos);
extern s32 Portal_FindNearestPointIndex(RoutePatrolNodes *list, s32 id);
extern void *Portal_GetGraphPoint(RoutePatrolNodes *list, s32 index);
extern void *Scaled_GetControllerPosition(PatrolBot *bot);
extern f32 Graphu64_GetPointDistance(void *a, void *b);
extern void Nav_SteerAlongRoute(PatrolBot *bot);
extern void Nav_RunBehaviorHandler(PatrolBot *bot);
extern void Nav_UpdatePlayerSteering(PatrolBot *bot);

void Nav_UpdatePatrolRoute(PatrolActor *actor)
{
    PatrolBot *bot = actor->player->bot;
    RoutePatrolNodes *nodes = &g_navigationGraph;
    void *pos;
    Clip *route;

    if (bot->route == -1) {
        Shared_World *routes = &g_world;

        if (*routes->routeCount > 0) {
            bot->route = 0;
            bot->routePos = 0;
            Scene_GetPlatformRoute(routes, bot->route);
        } else {
            bot->route = -2;
            bot->routePos = -1;
        }
        bot->goal = -1;
    }
    if (bot->node == bot->goal) {
        pos = Scaled_GetControllerPosition(bot);
        if (Graphu64_GetPointDistance(pos, Portal_GetGraphPoint(nodes, bot->goal)) < g_patrolGoalArrivalDistance) {
            if (bot->route >= 0) {
                route = Scene_GetPlatformRoute(&g_world, bot->route);
                bot->routePos++;
                if (bot->routePos == route->frames) {
                    bot->routePos = 0;
                }
            }
            bot->goal = -1;
        }
    }
    if (bot->goal == -1) {
        if (bot->route == -2) {
            bot->goal = Graphu64_NextRandom() % nodes->count;
        } else {
            bot->goal = Portal_FindNearestPointIndex(nodes, Scene_GetPlatformRoutePoint(&g_world, bot->route, bot->routePos));
        }
    }
    Nav_SteerAlongRoute(bot);
    Nav_RunBehaviorHandler(bot);
    Nav_UpdatePlayerSteering(bot);
}


#if !(defined(VERSION_DE))
/* Reset the two bot state words reached through the actor and player records. */
void Nav_ResetPatrolRouteSelection(void *object) {
    RouteChaseActor *actor = object;
    RouteChaseBot *bot = actor->player->bot;
    bot->resetWord220 = 0;
    bot->resetWord224 = -1;
}
#endif

