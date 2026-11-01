#include "include_asm.h"
#include "COMMON/ROUTE_CHASE_RECORDS.H"
#include "COMMON/TRIPLE.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "AI/SOURCE.H"
#include "TYPES.H"
#include "AI/NAV/NAV_RESETOBJECTARRIVALCHASE.H"

#if defined(VERSION_EU)
#if defined(VERSION_EU)
struct {
    u8 alignmentFill[8];
} k_NavUpdateobjectarrivalchaseEncodedWordsBlock1 __attribute__((aligned(4))) = {
    { 0x00, 0x0B, 0x58, 0x42, 0x01, 0x64, 0x60, 0x24 }
};
#endif
#endif

/* NAV_UPDATEOBJECTARRIVALCHASE_DATA.CPP */
#if defined(VERSION_EU_X)
float k_NavUpdateobjectarrivalchaseEncodedWordsBlock2[2] = {
    48.0f, 255.0f,
};
#endif

/* 800C71D8.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800C71D8 */
#if defined(VERSION_US_REV1)
f32 g_navUpdateobjectarrivalchaseDataFloatConstantWords[2] = {
    30.0f, 0.0f
};
#endif
#endif

/* NAV_UPDATEOBJECTARRIVALCHASE.CPP */
#if defined(VERSION_DE)
unsigned int k_NavUpdateobjectarrivalchaseEncodedWords[2] = {
    0x24040001, 0xAFBF0028,
};
#endif

/* NAV_UPDATEOBJECTARRIVALCHASE_DATA.CPP */
/* 800C6E84_20.CPP */
#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
/* ROM-grounded data: src/k_navUpdateobjectarrivalchaseDataFloatConstantWords_NavUpdateobjectarrivalchaseData.c */
#if defined(VERSION_EU)
const f32 k_navUpdateobjectarrivalchaseDataFloatConstantWords[2] = {
    102.399994f, 51.1999969f
};
#endif
#if defined(VERSION_EU_X)
const f32 k_navUpdateobjectarrivalchaseDataFloatConstantWords[2] = {
    102.399994f, 51.1999969f
};
#endif
#if defined(VERSION_US_REV1)
const f32 k_navUpdateobjectarrivalchaseDataFloatConstantWords[2] = {
    102.399994f, 51.1999969f
};
#endif
#endif

/* NAV_UPDATEOBJECTARRIVALCHASE.CPP */
/* 800C6E84_2.CPP */
#if defined(VERSION_DE)
const float g_Nav_ResetPatrolRouteSelectionConstantWords[2] = {
    102.399994f, 51.199997f,
};
#endif

/* OBJECTCHASE.CPP */
#if defined(VERSION_DE)
/* Fuzzy draft: the other versions' body, not diffed against this version's asm. */
/* Runs a computer player's chase step toward the object at 0x68: without a target id at 0xBC it
   switches to mode 2 and without an object it only updates; farther than g_objectChaseRouteDistanceLimit from its goal
   node it heads there through Nav_SteerAlongRoute, otherwise it takes mode 8 once arrived or copies the
   object's position to 0x2C; then, within g_objectChaseArrivalDistance of the object and not yet arrived, it marks
   arrival at 0x238 and plans a new route through Portal_CollectDirectedNeighbors to pick the next goal node. */
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"

extern RouteChaseGraph g_navigationGraph;
extern const f32 g_Nav_ResetPatrolRouteSelectionConstantWords[2];

extern void Scaled_SetBehaviourState(RouteChaseBot *bot, s32 mode);
extern void Nav_RunBehaviorHandler(RouteChaseBot *bot);
extern f32 Scaled_DistanceToNode(RouteChaseBot *bot, s32 node);
extern void Nav_SteerAlongRoute(RouteChaseBot *bot);
extern void Nav_UpdateTargetSteering(RouteChaseBot *bot);
extern f32 Graphu64_GetPointDistance(CVector3 *a, CVector3 *b);
extern s32 Portal_CollectDirectedNeighbors(RouteChaseGraph *graph, s32 from, s32 to, s32 *path, s32 flags);
extern void Scaled_ClearNodeQueue(RouteChaseBot *bot);

void Nav_UpdateObjectArrivalChase(RouteChaseActor *actor)
{
    s32 path[64];
    RouteChaseBot *bot = actor->player->bot;
    RouteChaseGraph *graph = &g_navigationGraph;
    f32 dist;
    s32 i;
    s32 len;
    s32 start;
    s32 none;

    if (bot->targetId == -1) {
        Scaled_SetBehaviourState(bot, 2);
        return;
    }
    if (bot->target == 0) {
        Nav_RunBehaviorHandler(bot);
        return;
    }
    dist = Scaled_DistanceToNode(bot, bot->goal);
    if (bot->node != bot->goal && g_Nav_ResetPatrolRouteSelectionConstantWords[0] < dist) {
        Nav_SteerAlongRoute(bot);
    } else if (bot->arrived != 0) {
        Scaled_SetBehaviourState(bot, 8);
    } else {
        bot->dest = bot->target->pos;
    }
    Nav_RunBehaviorHandler(bot);
    if (bot->target != 0) {
        Nav_UpdateTargetSteering(bot);
        if (Graphu64_GetPointDistance(&bot->self->pos, &bot->target->pos) < g_Nav_ResetPatrolRouteSelectionConstantWords[1] && bot->arrived == 0) {
            bot->arrived = 1;
            none = -1;
            for (i = 63; i >= 0; i--) {
                path[i] = none;
            }
            Portal_CollectDirectedNeighbors(graph, bot->goal, bot->goal, path, 0);
            start = path[0];
            none = -1;
            for (i = 63; i >= 0; i--) {
                path[i] = none;
            }
            len = Portal_CollectDirectedNeighbors(graph, start, bot->goal, path, 0);
            Scaled_ClearNodeQueue(bot);
            bot->goal = path[len - 1];
        }
    }
}
#endif

/* NAV_UPDATEOBJECTARRIVALCHASE.CPP */
/* 80212C90_8.CPP */
#if !defined(VERSION_DE)
/* Fuzzy draft: the other versions' body, not diffed against this version's asm. */
/* Runs a computer player's chase step toward the object at 0x68: without a target id at 0xBC it
   switches to mode 2 and without an object it only updates; farther than g_objectChaseRouteDistanceLimit from its goal
   node it heads there through Nav_SteerAlongRoute, otherwise it takes mode 8 once arrived or copies the
   object's position to 0x2C; then, within g_objectChaseArrivalDistance of the object and not yet arrived, it marks
   arrival at 0x238 and plans a new route through Portal_CollectDirectedNeighbors to pick the next goal node. */
#include "TYPES.H"
#include "COMMON/SHAREDPLAYER.H"

extern RouteChaseGraph g_navigationGraph;

extern void Scaled_SetBehaviourState(RouteChaseBot *bot, s32 mode);
extern void Nav_RunBehaviorHandler(RouteChaseBot *bot);
extern f32 Scaled_DistanceToNode(RouteChaseBot *bot, s32 node);
extern void Nav_SteerAlongRoute(RouteChaseBot *bot);
extern void Nav_UpdateTargetSteering(RouteChaseBot *bot);
extern f32 Graphu64_GetPointDistance(CVector3 *a, CVector3 *b);
extern s32 Portal_CollectDirectedNeighbors(RouteChaseGraph *graph, s32 from, s32 to, s32 *path, s32 flags);
extern void Scaled_ClearNodeQueue(RouteChaseBot *bot);

void Nav_UpdateObjectArrivalChase(RouteChaseActor *actor)
{
    s32 path[64];
    RouteChaseBot *bot = actor->player->bot;
    RouteChaseGraph *graph = &g_navigationGraph;
    f32 dist;
    s32 i;
    s32 len;
    s32 start;
    s32 none;

    if (bot->targetId == -1) {
        Scaled_SetBehaviourState(bot, 2);
        return;
    }
    if (bot->target == 0) {
        Nav_RunBehaviorHandler(bot);
        return;
    }
    dist = Scaled_DistanceToNode(bot, bot->goal);
    if (bot->node != bot->goal && g_objectChaseRouteDistanceLimit < dist) {
        Nav_SteerAlongRoute(bot);
    } else if (bot->arrived != 0) {
        Scaled_SetBehaviourState(bot, 8);
    } else {
        bot->dest = bot->target->pos;
    }
    Nav_RunBehaviorHandler(bot);
    if (bot->target != 0) {
        Nav_UpdateTargetSteering(bot);
        if (Graphu64_GetPointDistance(&bot->self->pos, &bot->target->pos) < g_objectChaseArrivalDistance && bot->arrived == 0) {
            bot->arrived = 1;
            none = -1;
            for (i = 63; i >= 0; i--) {
                path[i] = none;
            }
            Portal_CollectDirectedNeighbors(graph, bot->goal, bot->goal, path, 0);
            start = path[0];
            none = -1;
            for (i = 63; i >= 0; i--) {
                path[i] = none;
            }
            len = Portal_CollectDirectedNeighbors(graph, start, bot->goal, path, 0);
            Scaled_ClearNodeQueue(bot);
            bot->goal = path[len - 1];
        }
    }
}
#endif

/* 80212C90_9.CPP */
void Nav_ResetObjectArrivalChase(void *actor) {
    void *brain;
    brain = (((struct NavigationActorBrainView *) ((s8 *) ((struct ActorPlayerControllerView *) ((s8 *) actor))->player))->brain);
    (((struct NavigationChaseResetView *) ((s8 *) brain))->target) = 0;
    (((struct NavigationChaseResetView *) ((s8 *) brain))->arrived) = 0;
    (((struct NavigationChaseResetView *) ((s8 *) brain))->resetWord220) = 0;
    Scaled_ResetBehaviorState(brain);
}
