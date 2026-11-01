#include "COMMON/SHAREDCALLBACK5.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/NAVIGATION_NODE_AND_ROUTE_VIEWS.H"
#include "COMMON/SELF.H"
#include "TYPES.H"
#include "AI/SHARED_PICKUPGOALNODE.H"
#include "AI/ROUTE_RELATION_GRID.H"
#include "COMMON/SHARED_WORLDFUNC.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/NAVIGATION_GRAPH.H"
#include "AI/NAV/FARTHEST.H"
#include "include_asm.h"
#include "AI/SOURCE.H"
#include "AI/NAV/CARRIER.H"
#include "COMMON/FORMAT.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "DATA_OVERLAY_LAYOUTS.H"

/* FARTHEST.CPP */
/* 802106E0_17.CPP */
void *Portal_GetStridedTableEntry(struct NavigationLinkListView *object, int index);
extern void *Portal_GetGraphPoint(void *, s32);
extern f32 Graphu64_GetSquaredDistance(f32 *, f32 *);

/* Choose the farthest reachable neighbor linked by kinds 1, 2 or 7
 * from the actor that this state is following. */
void Nav_SelectFarthestReachableNeighbor(AiController *object)
{
    s32 neighbors[64];
    s32 links[64];
    s32 *linkCursor;
    CVector3 position;
    Player *actor;
    f32 *point;
    f32 distance;
    f32 farthest;
    s32 actor_node;
    register s32 best;
    s32 count;
    s32 i;
    Link *link;
    void *graph = &g_navigationGraph;

    actor = object->target->player;
    actor_node = actor->controller->current;
    position = actor->pos;
    for (i = 0; i < 64; i++) {
        neighbors[i] = -1;
        links[i] = -1;
    }
    linkCursor = links;
    farthest = g_navigationFarthestDistanceAndArrivalLimits[0];
    count = Portal_CollectIncidentLinks(graph, object->current, neighbors, linkCursor);
    best = -1;
    for (i = 0; i < count; i++) {
        link = Portal_GetStridedTableEntry(graph, links[i]);
        if ((link->type >= 1 && link->type <= 2) || link->type == 7) {
            point = Portal_GetGraphPoint(graph, neighbors[i]);
            if (Route_GetRouteRelation(graph, actor_node, neighbors[i])) {
                distance = Graphu64_GetSquaredDistance(&position.x, point);
                if (farthest < distance) {
                    farthest = distance;
                    best = i;
                }
            }
        }
    }
    object->mode = best;
}

/* 802106E0_20.CPP */
extern s32 Scaled_SetBehaviourState(void *, s32);
extern void Nav_UpdateTargetSteering(void *);

extern void Nav_RunBehaviorHandler(void *);

extern void Nav_SteerAlongRoute(void *);

extern f32 g_navigationRetreatDistanceLimit;

extern f32 g_navigationNearbyGoalDistanceLimit;

extern void Nav_AddGoalNode(void *, s32);

extern void Nav_UpdatePlayerSteering(void *controller);

extern void Nav_SelectPlayerState(void *controller);

extern f32 Scaled_DistanceToNode(s32 *, s32);

void Nav_InitCombatTargetApproach(void *actor) {
    void *brain;
    brain = (((struct NavigationActorBrainView *) ((s8 *) ((struct ActorPlayerControllerView *) ((s8 *) actor))->player))->brain);
    (((struct NavigationBrainView *) ((s8 *) brain))->state) = 0;
    Scaled_ResetBehaviorState(brain);
    (((struct NavigationBrainView *) ((s8 *) brain))->postRouteInitReset) = 0;
}

void Nav_ApproachCombatTargetAlongRoute(CloseAttackActor *actor)
{
    CloseAttackBrain *state;
    CloseAttackActor *peer;
    CloseAttackActor *peer_actor;
    CloseAttackBrain *peer_state;
    s32 value;

    state = actor->self->brain;
    peer = state->target;
    if (peer == 0) {
        Nav_RunBehaviorHandler(state);
        return;
    }

    peer_actor = peer->self;
    peer_state = peer_actor->brain;
    value = peer_state->route;
    state->destination = value;
    if (value != state->node) {
        state->node = value;
        if (!Route_GetRouteRelation(&g_navigationGraph, state->route, value)) {
            Scaled_SetBehaviourState(state, 1);
            return;
        }
    }

    Nav_RunBehaviorHandler(state);
    Nav_SteerAlongRoute(state);
    Nav_UpdateTargetSteering(state);
    if (Graphu64_GetSquaredDistance(&peer_actor->pos.x,
                       &state->player->pos.x) < g_navigationFarthestDistanceAndArrivalLimits[1] ||
        state->route == state->destination) {
        Scaled_SetBehaviourState(state, state->combat);
    }
}

/** Reset the inner record via Scaled_ResetBehaviorState, then override two of its fields. */
void Nav_InitRetreatMovement(LevelActor *actor) {
    Shared_ActorView *level1 = actor->controller;
    CloseAttackBrain *inner = level1->owner;
    inner->state = 0;
    Scaled_ResetBehaviorState(inner);
    inner->reset2FC = 0;
    inner->destination = -1;
}

void Nav_UpdateRetreatMovement(void *actorObject)
{
    CloseAttackBrain *brain;
    CloseAttackActor *actor = actorObject;
    s32 previousDestination;

    brain = actor->self->brain;
    if (brain->target == 0) {
        Nav_RunBehaviorHandler(brain);
        return;
    }

    previousDestination = brain->destination;
    if (previousDestination == -1) {
        Nav_SelectFarthestReachableNeighbor((AiController *)brain);
        if (brain->destination == previousDestination ||
            brain->destination == brain->route) {
            Scaled_SetBehaviourState(brain, 4);
            return;
        }
    }

    if (g_navigationRetreatDistanceLimit < Graphu64_GetSquaredDistance(
            &brain->target->self->pos.x,
            &brain->player->pos.x)) {
        Scaled_SetBehaviourState(brain, brain->combat);
        return;
    }

    Nav_RunBehaviorHandler(brain);
    Nav_SteerAlongRoute(brain);
    Nav_UpdateTargetSteering(brain);
    if (brain->route == brain->destination) {
        brain->destination = -1;
    }
}

/** Reset the inner record's flag fields, then clear its state via Scaled_ResetBehaviorState. */
void Nav_InitNearbyUnrestrictedGoal(LevelActor *actor) {
    Shared_ActorView *level1 = actor->controller;
    CloseAttackBrain *inner = level1->owner;
    inner->state = 0;
    inner->destination = -1;
    Scaled_ResetBehaviorState(inner);
    inner->reset2FC = 0;
}

void Nav_SeekNearbyUnrestrictedGoal(Shared_Actor *actor)
{
    AiController *state;
    CNavData *table;
    NavigationPoint *entry;
    f32 threshold;
    s32 index;
    s32 value;
    u32 flags;

    state = ((Player *)actor->entity)->controller;
    table = &g_navigationGraph;
    if (state->mode == -1) {
        Portal_ResetSearchState(table);
        Route_ClearGoalList(table);
        threshold = g_navigationNearbyGoalDistanceLimit;
        index = 0;
        if (table->m_nNavNodes > 0) {
            do {
                entry = Portal_GetGraphPoint(table, index);
                if (Graphu64_GetSquaredDistance(&state->player->pos.x, entry) < threshold &&
                    !(navigation_attributes(entry) & 0x04300000)) {
                    Nav_AddGoalNode(table, index);
                }
                index++;
            } while (index < table->m_nNavNodes);
        }
        Route_SearchPathByKey(table, state->current);
        Route_ReconstructSearchPath(table, &state->queue, 4);
        value = table->result;
        state->mode = value;
        state->routeGoal = value;
    }
    Nav_RunBehaviorHandler(state);
    Nav_SteerAlongRoute(state);
    Nav_UpdatePlayerSteering(state);
    flags = (state->player->movementFlags & 0x3000) != 0;
    if (state->current == state->mode &&
        !flags) {
        Nav_SelectPlayerState(state);
    }
}

void Nav_InitUnclaimedMarkerSearch(void *actor) {
    void *brain;
    brain = (((struct NavigationActorBrainView *) ((s8 *) ((struct ActorPlayerControllerView *) ((s8 *) actor))->player))->brain);
    (((struct NavigationBrainView *) ((s8 *) brain))->state) = 0;
    Scaled_ResetBehaviorState(brain);
    (((struct NavigationBrainView *) ((s8 *) brain))->postRouteInitReset) = 0;
}

void Nav_SeekUnclaimedMarker(void *actorStorage) {
    s32 *rec;
    void *v0;

    ActorPlayerControllerView *object = actorStorage;
    NavigationActorWordBrainView *actor = object->player;

    rec = actor->brainWords;
    v0 = Playerai_FindPlayerWithMarker((char *)&g_playerViewRenderContext);
    if (v0 == (void *) *rec) {
        Scaled_SetBehaviourState(rec, 10);
        return;
    }
    if (v0 != 0) {
        Scaled_SetBehaviourState(rec, 2);
        return;
    }
    Nav_RunBehaviorHandler(rec);
    Scaled_DistanceToNode(rec, rec[3]);
    Nav_SteerAlongRoute(rec);
    Nav_UpdateTargetSteering(rec);
}

/* 800C6E84_18.CPP */
#if !(defined(VERSION_US_REV1))
const float g_Nav_SelectFarthestReachableNeighborConstantWords_de_eu_eu_x_us[4] = {
    -1.0f, 212336.62f, 849346.5f, 1048576.0f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/Nav_SelectFarthestReachableNeighborConstantWords_us_rev1.c */
const float g_Nav_SelectFarthestReachableNeighborConstantWords_us_rev1[1] = {
    -1.0f,
};

/* ROM-grounded data: src/Nav_ApproachCombatTargetAlongRouteConstantWords.c */
const float g_Nav_ApproachCombatTargetAlongRouteConstantWords[1] = {
    212336.62f,
};

/* ROM-grounded data: src/Nav_UpdateRetreatMovementConstantWords.c */
const float g_Nav_UpdateRetreatMovementConstantWords[1] = {
    849346.5f,
};

/* ROM-grounded data: src/Nav_SeekNearbyUnrestrictedGoalConstantWords.c */
const float g_Nav_SeekNearbyUnrestrictedGoalConstantWords[1] = {
    1048576.0f,
};
#endif

/* CARRIER.CPP */
void Nav_InitCarrierRoute(AiTarget *aiTarget) {
    AiController *controller;
    controller = aiTarget->player->controller;
    ((CloseAttackBrain *)controller)->state = 0;
    Scaled_ResetBehaviorState(controller);
    controller->behaviorResetFlag = 0;
}

void Nav_FollowMarkerCarrierRoute(AiTarget *aiTarget) {
    AiController *controller;
    void *v0;

    controller = aiTarget->player->controller;
    v0 = Playerai_FindPlayerWithMarker((char *)&g_playerViewRenderContext);
    if (v0 == 0 || v0 != (void *)controller->player) {
        Scaled_SetBehaviourState(controller, 2);
        return;
    }
    controller = aiTarget->player->controller;
    Nav_RunBehaviorHandler(controller);
    Scaled_DistanceToNode(controller, controller->mode);
    Nav_SteerAlongRoute(controller);
    Nav_UpdateTargetSteering(controller);
}

/* NAV_UPDATEPATROLROUTE_DATA__FARTHEST.CPP */
/* 800C2000.CPP */
#if defined(VERSION_US)
#if defined(VERSION_US)
struct {
    f32 g_patrolGoalArrivalDistance;
    u8 alignmentFill4[12];
    f32 g_objectChaseRouteDistanceLimit;
    f32 g_objectChaseArrivalDistance;
    u8 alignmentFill24[8];
    f32 g_timedJumpRouteArrivalDistance;
    u8 alignmentFill36[12];
} g_NavUpdatepatrolrouteWords2 __attribute__((aligned(4))) = {
    102.399994f,
    { 0x52, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa, 0x0, 0x8, 0x0, 0x1c },
    102.399994f,
    51.1999969f,
    { 0x65, 0x72, 0x46, 0x78, 0x5f, 0x74, 0x54, 0x0 },
    102.399994f,
    { 0x0, 0x8, 0x0, 0x8, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7 }
};
typedef char g_NavUpdatepatrolrouteWords2SizeCheck[(sizeof(g_NavUpdatepatrolrouteWords2) == 48) ? 1 : -1];
#endif
#endif

/* 800C2374.CPP */
#if defined(VERSION_EU)
#if defined(VERSION_EU)
#endif
#endif

/* 802192C0_10.CPP */
#if defined(VERSION_EU_X)
#endif
