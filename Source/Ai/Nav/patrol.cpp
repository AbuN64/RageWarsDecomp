#include "Common/navigation_graph.h"
#include "Common/route_chase_records.h"
#include "Common/triple.h"
#include "Common/runtime_declarations.h"
#include "types.h"
#include "Common/self.h"
#include "include_asm.h"
#include "Ai/Player/scaled_updatetargetpitch.h"
#include "Engine/scene_drawtransitioncoloroverlay.h"
#include "Engine/scene_findtrackedactors.h"
#include "Behaviour/behaviour.h"
#include "Frontend/player.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Ai/portal_isnodemovementblocked.h"
#include "Ai/shared_pickupgoalnode.h"
#include "Ai/Nav/Patrol/patrol.h"

/* Runs a computer player's patrol step: starts its route on the first route of g_world_AchieveUpdateresultsscreen,
   or random roaming (-2) when there are none; once within g_patrolGoalArrivalDistance of its goal node it advances the
   route position (wrapping at the route length) and drops the goal; a dropped goal is then
   taken from the route through Scene_GetPlatformRoutePoint and Portal_FindNearestPointIndex_Patrol, or a random node of g_navigationGraph when
   roaming; finally runs Nav_SteerAlongRoute, Nav_RunBehaviorHandler and Nav_UpdatePlayerSteering. */













extern CNavData g_navigationGraph;



extern char *Scene_GetPlatformRoute(void *world, s32 index);
extern void *Scene_GetPlatformRoutePoint(void *a, s32 b, s32 c);
struct CNavData_t; extern s32 Portal_FindNearestPointIndex(struct CNavData_t *pointSet, void *point);

extern f32 Graphu64_GetPointDistance(f32 *a, f32 *b);
struct AiController; extern void Nav_SteerAlongRoute(struct AiController *controller);
extern void Nav_RunBehaviorHandler(void *aiController);
struct AiController; extern void Nav_UpdatePlayerSteering(struct AiController *controller);

void Nav_UpdatePatrolRoute(PatrolActor *actor)
{
    PatrolBot *bot = actor->player->bot;
    CNavData *nodes = &g_navigationGraph;
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
            bot->goal = Graphu64_NextRandom() % nodes->m_nNavNodes;
        } else {
            bot->goal = Portal_FindNearestPointIndex(nodes, Scene_GetPlatformRoutePoint(&g_world, bot->route, bot->routePos));
        }
    }
    Nav_SteerAlongRoute(bot);
    Nav_RunBehaviorHandler(bot);
    Nav_UpdatePlayerSteering(bot);
}


/* Reset the two bot state words reached through the actor and player records. */
void Nav_ResetPatrolRouteSelection(void *object) {
    RouteChaseActor *actor = object;
    RouteChaseBot *bot = actor->player->bot;
    bot->closeAttackState = 0;
    bot->resetWord224 = -1;
}
