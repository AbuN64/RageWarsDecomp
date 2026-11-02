#include "COMMON/ROUTE_CHASE_RECORDS.H"
#include "COMMON/WORLD.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/FIELD_VEC_B0.H"
#include "TYPES.H"
#include "COMMON/APPROACHLOCATION.H"
#include "AI/CBARREL.H"

s32 Cbarrel_ClassifyTrackTarget(LevelActor *actor, RouteChaseBot *routeChaseBot, LevelActor *target) {
    void *controller;

    if (routeChaseBot->node == 0) {
        return 6;
    }
    if (target == 0) {
        if (routeChaseBot->routeReady != 0) {
            return 4;
        }
        return 3;
    }
    if (target == routeChaseBot->target) {
        return 2;
    }
    if (target->definition->kind == 5) {
        return 5;
    }
    if (target->type == 1615) {
        return 7;
    }
    if (g_world.visibilityEnabled == 0) {
        if (target->flags & 0x300000) {
            controller = target->controller;
            if ((((Shared_ActorView *)controller)->controllerOwner == actor) &&
                (((Shared_ActorView *)controller)->controllerMode == 2)) {
                return 1;
            }
        }
        if (actor->renderFlags & 2) {
            if (actor->type != 202) {
                return 1;
            }
        }
    }
    return 0;
}
