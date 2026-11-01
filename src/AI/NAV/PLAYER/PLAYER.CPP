#include "COMMON/VECTOR4F.H"
#include "include_asm.h"
#include "COMMON/SHAREDCALLBACK5.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "WEAPONS/PLAYER_MOVEMENT_INTERFACES.H"
#include "COMMON/NAVIGATION_GRAPH.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/RENDERCOUNTERS.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"
#include "COMMON/NAVIGATION_NODE_AND_ROUTE_VIEWS.H"
#include "COMMON/REC.H"
#include "AI/NAV/NAV_UPDATECOMPUTERPLAYERSTATUS.H"
#include "COMMON/SHAREDPLAYER.H"

/* 80208000.CPP */
/* Resets a player controller: marks the active, requested and committed selections empty, sets the
   request kind to 0xB, clears the four link words at 0x14 to -1, resets the stage counters at 0x1BC
   and 0x1C8 and the target list, installs the default table g_playerDefaultBehaviorTable through Scaled_SetBehaviorTable and mode
   2 through Scaled_SetBehaviourState_Player, zeroes the tracking values from 0x23C to 0x260, runs the resets
   Nav_ResetWheelProbeState, Scaled_ResetBehaviorState and Scaled_ClearAuxiliaryBehaviorState, and clears the remaining state words. */

extern void Scaled_SetBehaviorTable(void *, char *, s32);
extern void Scaled_SetBehaviourState(void *, s32);
extern void Nav_ResetWheelProbeState(void *);

extern void Scaled_ClearAuxiliaryBehaviorState(void *);

void Nav_ResetPlayerState(s32 *state) {
    s32 i;
    s32 none;

    state[1] = -1;
    state[2] = -1;
    state[3] = 11;
    state[4] = -1;
    state[11] = 0;
    state[12] = 0;
    state[13] = 0;
    none = -1;
    for (i = 3; i >= 0; i--) {
        state[5 + i] = none;
    }
    state[10] = -1;
    ((Brain *)state)->stage = 0xFFFF;
    ((Brain *)state)->state = 0;
    ((Brain *)state)->matches = 0;
    state[14] = 1;
    state[15] = 0;
    state[25] = 0;
    ((Brain *)state)->preferred = 0;
    state[26] = 0;
    ((Brain *)state)->routeState = -1;
    ((Brain *)state)->patrolRoute = -1;
    ((Brain *)state)->patrolPosition = 0;
    for (i = 0; i < 10; i++) {
        state[15 + i] = 0;
        state[27 + i] = 0;
        state[37 + i] = 0;
    }
    ((Brain *)state)->arrived = 0;
    Scaled_SetBehaviorTable(state, &g_playerDefaultBehaviorTable, none);
    Scaled_SetBehaviourState(state, 2);
    ((Brain *)state)->tracking[0] = 0.0f;
    ((Brain *)state)->w23C = 0;
    ((Brain *)state)->w240 = 0;
    ((Brain *)state)->tracking[3] = ((Brain *)state)->tracking[4] = ((Brain *)state)->tracking[1] =
        ((Brain *)state)->tracking[2] = ((Brain *)state)->tracking[5] = ((Brain *)state)->tracking[6] =
        ((Brain *)state)->tracking[7] = ((Brain *)state)->tracking[0];
    Nav_ResetWheelProbeState(state);
    Scaled_ResetBehaviorState(state);
    Scaled_ClearAuxiliaryBehaviorState(state);
    ((Brain *)state)->frames = 0;
    ((Brain *)state)->visible = 0;
    ((Brain *)state)->fireTimer = -1;
    ((Brain *)state)->cooldown = 0;
    ((Brain *)state)->lastAttacker = 0;
    ((Brain *)state)->timer = 0;
    ((Brain *)state)->actionDelay = 0;
    ((Brain *)state)->alternateCountdown = 0;
    ((Brain *)state)->actionDuration = 0;
    ((Brain *)state)->pattern = 0;
    ((Brain *)state)->distance = 0;
    ((Brain *)state)->previousPortalLink = -1;
}

/* Nav_UpdateComputerPlayerStatus_Player.CPP */
/* Updates a computer player's brain for the frame: fixes its route start, runs its planner through Scaled_UpdateTargetPitch and its state callback, counts down its cooldown at 0x324, and for a displayed player sets the health meter from its health over the character's maximum (400 for kinds 11 and 12, 300 for 13 and 14, otherwise Player_GetMaxHealth_Player), as a percentage, rescaled for kind 14 by the difficulty g_difficulty; in the tutorial (g_matchRoundCounters) kind 11 also shows the timer and refills its ammunition, then the meter is drawn through OnScreen_SetFirstBarTarget or OnScreen_SetSecondBarTarget; finally it restarts a stalled player (state 0x12) through Scaled_HandlePlayerTimeout. */

extern char g_tutorialStatusBars[];

extern void Scaled_UpdateTargetPitch(Brain *);
extern s32 Player_GetMaxHealth(SharedPlayer *);
extern void OnScreen_SetSecondBarTarget(char *, s32);
extern void ContPad_ClearControllerInput(char *);
extern void Scaled_HandlePlayerTimeout(Brain *, SharedPlayer *);

void Nav_UpdateComputerPlayerStatus(Brain *brain) {
    s32 health;
    s32 maximum;
    f32 meter;
    s32 kind;
    CGameStatus *tutorial;
    SharedPlayer *player;

    if (brain->player->views1450.view1450_1.computer == 0) {
        return;
    }
    if (brain->route == -1) {
        brain->route = brain->start;
    }
    Scaled_UpdateTargetPitch(brain);
    if (brain->behaviour->update != 0) {
        brain->behaviour->update(brain->player, 0);
    }
    if (brain->cooldown > 0) {
        brain->cooldown--;
    }
    if (brain->player->views5D8.view5D8_1.record->display != 0) {
        health = brain->player->views5E4.view5E4_2.health >> 8;
        kind = brain->player->views5D8.view5D8_1.record->characterId;
        if (kind == 11) {
            maximum = 400;
        } else if (kind == 12) {
            maximum = 400;
        } else if (kind == 14) {
            maximum = 300;
        } else if (kind == 13) {
            maximum = 300;
        } else {
            maximum = Player_GetMaxHealth(brain->player) >> 8;
        }
        meter = (f32)health / (f32)maximum * 100.0f;
        if (brain->player->views5D8.view5D8_1.record->characterId == 14) {
            if (meter == 0.0f) {
                meter = (3 - g_gameSettings.counters.m_nTalsetLives) * 33;
            } else {
                meter *= 0.33333334f;
                meter += (2 - g_gameSettings.counters.m_nTalsetLives) * 33;
            }
            if (meter < 0.0f) {
                meter = 0.0f;
            }
        }
        tutorial = &g_gameSettings.counters;
        if (tutorial->enabled != 0) {
            if (brain->player->views5D8.view5D8_1.record->characterId == 11) {
                OnScreen_SetFirstBarTarget(g_tutorialStatusBars, (f32)tutorial->m_nBastilleShield);
                if (tutorial->m_nBastilleTimer > 0) {
                    tutorial->m_nBastilleTimer--;
                    ContPad_ClearControllerInput((char *)&((SharedPlayer *)brain->player)->views5E8.view688_33.body);
                    brain->w23C = 0;
                    brain->w240 = 0;
                }
                if (tutorial->m_nBastilleTimer == 0 && brain->player->views5E4.view5E4_2.health > 0) {
                    tutorial->m_nBastilleShield = 100;
                    tutorial->m_nBastilleTimer = -1;
                    Player_SetPlayerState(brain->player, brain->player, 2);
                }
            }
            if (brain->player->views5D8.view5D8_1.record->display == 1) {
                OnScreen_SetFirstBarTarget(g_tutorialStatusBars, meter);
            } else {
                OnScreen_SetSecondBarTarget(g_tutorialStatusBars, meter);
            }
        }
    }
    player = brain->player;
    if (player->views5E8.view650_16.state == 18) {
        player->views1340.view1340_1.stalls++;
        Scaled_HandlePlayerTimeout(brain, player);
    }
}

extern CNavData g_navigationGraph;
float Graphu64_GetPointDistance(void *, void *);
void Graphu64_SubtractVectors(CVector3 *, CVector3 *, CVector3 *);
f32 Nav_SteerTowardPoint(PlayerAimBrainView *, CVector3 *, f32, f32);
void Scaled_SetPitchFromAngle(PlayerAimBrainView *, f32, s32);
void Portal_DispatchActorBehavior(AiController *);
float Gu_Sqrtf(float);
NavigationPoint *Portal_GetGraphPoint(CNavData *,s32);
NavigationPortal *Portal_GetStridedTableEntry(CNavData *,s32);
NavigationSearchNode *Portal_FindSearchNode(CNavData *,s32);
s32 Portal_FindLinkIndex(CNavData *,s32,s32);
s32 Scaled_AdvanceNodeQueue(AiController *);
typedef struct GroundObject { char pad[0x18]; ActorMotionResource *resource; } GroundObject;
GroundObject *InstHdr_GetEnabledItemValue(Player *);
extern f32 g_jumpLinkStartDistance;
extern f32 g_jumpLinkNegativeAimTolerance;
extern f32 g_jumpLinkPositiveAimTolerance;
extern f32 g_platformLinkStartDistance;
extern f32 g_platformBoardingDistance;
extern f32 g_platformRiderHorizontalTolerance;
extern f32 g_platformExitEndpointDistance;
extern f32 g_routeIntermediateNodeReach;
extern f32 g_routeFinalNodeReach;
void Nav_SteerAlongRoute(AiController *controller) {
    CNavData *graph = &g_navigationGraph;
    CVector3 delta;
    Player *player;
    NavigationPoint *point;
    NavigationPoint *goal;
    NavigationPoint *start;
    NavigationPoint *entry;
    NavigationPortal *portal;
    NavigationSearchNode *node;
    GroundObject *ground;
    CVector3 *pos;
    f32 distance;
    f32 offset;
    f32 reach;
    f32 gap;
    s32 from;
    s32 link;
    s32 riding;
    s32 moving;

    player = controller->player;
    if (controller->mode != -1) {
        controller->routeComplete = 0;
        controller->holdMovement = 0;
        controller->airPitchNode = 0;
        controller->jumpLinkActive = 0;
        controller->kindFourLinkActive = 0;
        if (controller->queue[0] != -1) {
                point = Portal_GetGraphPoint(graph, controller->queue[0]);
                pos = &controller->player->pos;
                distance = Graphu64_GetPointDistance(pos, point);
                controller->airPitchNode = (navigation_attributes(point) & 0x300000) != 0;
                if (controller->queue[0] == controller->current) {
                    link = Portal_FindLinkIndex(graph, controller->previous, controller->queue[0]);
                } else {
                    link = Portal_FindLinkIndex(graph, controller->current, controller->queue[0]);
                }
                if (link > 0) {
                    portal = Portal_GetStridedTableEntry(graph, link);
                    if (portal->kind == 4) {
                        controller->kindFourLinkActive = 1;
                    }
                    if (portal->kind == 8) {
                        Graphu64_GetPointDistance(pos, Portal_GetGraphPoint(graph, controller->current));
                        goal = Portal_GetGraphPoint(graph, controller->queue[0]);
                        controller->jumpLinkActive = 1;
                        if (link != controller->previousPortalLink) {
                            controller->linkTraversalPhase = 0;
                            controller->previousPortalLink = link;
                        }
                        if (controller->linkTraversalPhase == 0) {
                            start = Portal_GetGraphPoint(graph, controller->current);
                            Graphu64_SubtractVectors(&delta, pos, &start->position);
                            if (!(Gu_Sqrtf(delta.x * delta.x + delta.z * delta.z) < g_jumpLinkStartDistance)) {
                                controller->destination = start->position;
                                return;
                            }
                            controller->linkTraversalPhase = 1;
                        }
                        if (controller->linkTraversalPhase == 1) {
                            controller->destination = goal->position;
                            offset = Nav_SteerTowardPoint(controller, &controller->destination, 2.0f, 0.0f);
                            if (offset < 0.0f ? g_jumpLinkNegativeAimTolerance < -offset : g_jumpLinkPositiveAimTolerance < offset) {
                                controller->holdMovement = 1;
                                return;
                            }
                            controller->linkTraversalPhase = 2;
                        }
                        if (controller->linkTraversalPhase == 2) {
                            controller->destination = goal->position;
                            controller->linkTraversalPhase = 3;
                            return;
                        }
                        if (controller->linkTraversalPhase == 3) {
                            controller->destination = goal->position;
                            controller->linkTraversalPhase = 4;
                            return;
                        }
                        if (controller->linkTraversalPhase == 4) {
                            controller->destination = goal->position;
                            controller->linkTraversalPhase = 5;
                            return;
                        }
                        if (controller->linkTraversalPhase == 5) {
                            controller->destination = goal->position;
                            player->actionFlags |= 0x10;
                            controller->linkTraversalPhase = 6;
                            return;
                        }
                        if (controller->linkTraversalPhase == 6) {
                            {
                            s32 jumping, falling;
                            moving = controller->player->movementFlags;
                            jumping = moving & 0x2000;
                            falling = moving & 0x1000;
                            if (jumping || falling) {
                                controller->linkTraversalPhase = 2;
                            }
                            }
                            controller->destination = goal->position;
                        }
                    } else if (portal->kind == 5) {
                        if (controller->linkTraversalPhase == 0) {
                            entry = Portal_GetGraphPoint(graph, controller->current);
                            if (!(Graphu64_GetPointDistance(pos, entry) < g_platformLinkStartDistance)) {
                                controller->destination = entry->position;
                                return;
                            }
                            controller->linkTraversalPhase = 1;
                        }
                        if (controller->linkTraversalPhase == 1) {
                            node = Portal_FindSearchNode(graph, controller->current);
                            if (Graphu64_GetPointDistance(&node->platform->pos, &node->endpoint) < g_platformBoardingDistance) {
                                controller->destination = node->platform->pos;
                                player->actionFlags |= 0x10;
                                controller->linkTraversalPhase = 2;
                                return;
                            }
                            controller->destination = node->endpoint;
                            controller->holdMovement = 1;
                        }
                        if (controller->linkTraversalPhase == 2) {
                            riding = 0;
                            ground = InstHdr_GetEnabledItemValue(controller->player);
                            if (ground != 0) {
                                riding = ground->resource->kind == 2;
                            }
                            Graphu64_SubtractVectors(&delta, pos, &Portal_FindSearchNode(graph, controller->current)->platform->pos);
                            gap = Gu_Sqrtf(delta.x * delta.x + delta.z * delta.z);
                            if (riding != 0 && gap < g_platformRiderHorizontalTolerance) {
                                controller->linkTraversalPhase = 3;
                            } else {
                                controller->destination = Portal_FindSearchNode(graph, controller->current)->platform->pos;
                                return;
                            }
                        }
                        if (controller->linkTraversalPhase == 3) {
                            riding = 0;
                            ground = InstHdr_GetEnabledItemValue(controller->player);
                            if (ground != 0) {
                                riding = ground->resource->kind == 2;
                            }
                            if (riding == 0) {
                                controller->linkTraversalPhase = 0;
                            }
                            point = Portal_GetGraphPoint(graph, controller->queue[0]);
                            node = Portal_FindSearchNode(graph, controller->queue[0]);
                            if (Graphu64_GetPointDistance(&node->platform->pos, &node->endpoint) < g_platformExitEndpointDistance) {
                                controller->destination = point->position;
                                player->actionFlags |= 0x10;
                            } else {
                                controller->destination = point->position;
                                controller->holdMovement = 1;
                                return;
                            }
                        }
                    } else {
                        controller->linkTraversalPhase = 0;
                    }
                } else {
                    controller->linkTraversalPhase = 0;
                }
                if (controller->queue[1] == -1) {
                    reach = g_routeFinalNodeReach;
                } else {
                    reach = g_routeIntermediateNodeReach;
                    if (navigation_point_flags(point) & 0x100) {
                        reach = g_routeFinalNodeReach;
                    }
                }
                if (distance < reach && controller->current == controller->queue[0]) {
                    if (Scaled_AdvanceNodeQueue(controller) == 0) {
                        return;
                    }
                }
        } else {
            controller->routeComplete = 1;
            return;
        }
    } else {
        controller->routeComplete = 1;
        return;
    }
    if (controller->queue[0] != -1) {
        point = Portal_GetGraphPoint(graph, controller->queue[0]);
        if (navigation_point_flags(point) & 2) {
            controller->destination = controller->home;
            return;
        }
        controller->destination = point->position;
    }
}

extern f32 g_playerSteeringFallDistance;
extern f32 g_playerSteeringNegativeFallAngle;
extern f32 g_playerSteeringPositiveFallAngle;
extern f32 g_playerSteeringFallForward;
extern f32 g_playerSteeringFirstAirForward;
extern f32 g_playerSteeringHeadingOffset;
extern f32 g_playerSteeringAirForward;
extern f32 g_playerSteeringDescendingPoseForward;
extern f32 g_playerSteeringAscendingPoseForward;

static __inline__ void navigationTurnLeft(CVector3 *v) {
    v->y = v->x;
    v->x = -v->z;
    v->z = v->y;
    v->y = 0.0f;
}
static __inline__ void navigationTurnRight(CVector3 *v) {
    v->y = v->x;
    v->x = v->z;
    v->z = -v->y;
    v->y = 0.0f;
}
void Nav_UpdatePlayerSteering(AiController *controller) {
    CNavData *graph;
    CVector3 delta;
    CVector3 desired;
    CVector3 facing;
    CVector3 tangent;
    CVector3 *destination;
    CVector3 *position;
    Player *player;
    f32 value;
    f32 angle;
    f32 distance;
    f32 projection;
    s32 jumping;
    s32 falling;

    if (controller->routeComplete == 0) {
        destination = &controller->destination;
        jumping = controller->player->movementFlags & 0x2000;
        player = controller->player;
        position = &player->pos;
        falling = player->movementFlags & 0x1000;
        Graphu64_SubtractVectors(&delta, destination, position);
        distance = Gu_Sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
        graph = &g_navigationGraph;
        if (falling) {
            if (g_playerSteeringFallDistance < distance) {
                angle = Nav_SteerTowardPoint(controller, destination, 2.0f, 0.0f);
                if (angle < 0.0f ? -angle < g_playerSteeringNegativeFallAngle : angle < g_playerSteeringPositiveFallAngle) {
                    player->forward = g_playerSteeringFallForward;
                }
                if ((jumping || falling) && controller->airPitchNode) {
                    value = delta.y;
                    Scaled_SetPitchFromAngle(controller, XMath_EvaluateArcTangentTwo(value, Gu_Sqrtf(delta.x * delta.x + delta.z * delta.z)), 1);
                    player->forward = g_playerSteeringFirstAirForward;
                }
            }
        } else {
            Nav_SteerTowardPoint(controller, destination, 2.0f, 0.0f);
            angle = controller->player->heading + g_playerSteeringHeadingOffset;
            facing.x = Gu_Sinf(angle);
            facing.y = 0.0f;
            facing.z = Math_Cosf(angle);
            angle = XMath_EvaluateArcTangentTwo(controller->destination.z - position->z, controller->destination.x - position->x);
            desired.x = Math_Cosf(angle);
            desired.y = 0.0f;
            desired.z = Gu_Sinf(angle);
            player->forward = desired.x * facing.x + desired.y * facing.y + desired.z * facing.z;
            if (graph != 0 && controller->current != -1) {
                angle = 0.0f;
            }
            tangent = Portal_GetGraphPoint(graph, controller->current)->position;
            tangent.x -= controller->destination.x;
            tangent.z -= controller->destination.z;
            navigationTurnLeft(&tangent);
            value = XMath_EvaluateArcTangentTwo(tangent.z, tangent.x);
            tangent.x = Math_Cosf(value);
            tangent.z = Gu_Sinf(value);
            projection = desired.x * tangent.x + desired.y * tangent.y + desired.z * tangent.z;
            tangent.x *= projection;
            tangent.z *= projection;
            navigationTurnRight(&facing);
            tangent.z = tangent.x * facing.x + tangent.z * facing.z;
            player->strafe = tangent.z;
        }
        if ((jumping || falling) && controller->airPitchNode) {
            value = delta.y;
            Scaled_SetPitchFromAngle(controller, XMath_EvaluateArcTangentTwo(value, Gu_Sqrtf(delta.x * delta.x + delta.z * delta.z)), 1);
            player->forward = g_playerSteeringAirForward;
        }
        if (controller->player->pose == 15) {
            if (position->y > controller->destination.y) {
                player->forward = g_playerSteeringDescendingPoseForward;
            } else {
                player->forward = g_playerSteeringAscendingPoseForward;
            }
        }
        if (controller->holdMovement) {
            player->strafe = 0.0f;
            player->forward = 0.0f;
        }
    }
}

f32 Nav_SteerTowardPoint(PlayerAimBrainView *, CVector3 *, f32, f32);

extern f32 g_targetSteeringFallDistance;
extern f32 g_targetSteeringNegativeFallAngle;
extern f32 g_targetSteeringPositiveFallAngle;
extern f32 g_targetSteeringFallForward;
extern f32 g_targetSteeringFirstAirForward;
extern f32 g_targetSteeringHeadingOffset;
extern f32 g_targetSteeringAirForward;
extern f32 g_targetSteeringDescendingPoseForward;
extern f32 g_targetSteeringAscendingPoseForward;

void Nav_UpdateTargetSteering(AiController *controller) {
    CNavData *graph;
    AiTarget *target;
    CVector3 delta;
    CVector3 desired;
    CVector3 facing;
    CVector3 tangent;
    CVector3 steer;
    CVector3 *destination;
    CVector3 *position;
    Player *player;
    f32 value;
    f32 angle;
    f32 distance;
    f32 projection;
    s32 jumping;
    s32 falling;

    target = controller->target;
    if (target == 0 || controller->jumpLinkActive != 0 || controller->kindFourLinkActive != 0 || controller->linkTraversalPhase != 0) {
        Nav_SteerTowardPoint(controller, &controller->destination, 2.0f, 0.0f);
    } else {
        Nav_SteerTowardPoint(controller, &target->player->pos, 2.0f, 0.0f);
        Portal_DispatchActorBehavior(controller);
    }
    if (controller->routeComplete == 0) {
        destination = &controller->destination;
        jumping = controller->player->movementFlags & 0x2000;
        player = controller->player;
        position = &player->pos;
        falling = player->movementFlags & 0x1000;
        Graphu64_SubtractVectors(&delta, destination, position);
        distance = Gu_Sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
        graph = &g_navigationGraph;
        if (falling) {
            if (g_targetSteeringFallDistance < distance) {
                angle = Nav_SteerTowardPoint(controller, destination, 2.0f, 0.0f);
                if (angle < 0.0f ? -angle < g_targetSteeringNegativeFallAngle : angle < g_targetSteeringPositiveFallAngle) {
                    player->forward = g_targetSteeringFallForward;
                }
                if ((jumping || falling) && controller->airPitchNode) {
                    value = delta.y;
                    Scaled_SetPitchFromAngle(controller, XMath_EvaluateArcTangentTwo(value, Gu_Sqrtf(delta.x * delta.x + delta.z * delta.z)), 1);
                    player->forward = g_targetSteeringFirstAirForward;
                }
            }
        } else {
            angle = controller->player->heading + g_targetSteeringHeadingOffset;
            facing.x = Gu_Sinf(angle);
            facing.y = 0.0f;
            facing.z = Math_Cosf(angle);
            desired.x = controller->destination.x - position->x;
            desired.z = controller->destination.z - position->z;
            desired.y = 0.0f;
            if (graph != 0 && controller->current != -1) {
                angle = 0.0f;
            }
            tangent = Portal_GetGraphPoint(graph, controller->current)->position;
            tangent.x -= controller->destination.x;
            tangent.z -= controller->destination.z;
            navigationTurnLeft(&tangent);
            value = XMath_EvaluateArcTangentTwo(tangent.z, tangent.x);
            tangent.x = Math_Cosf(value);
            tangent.z = Gu_Sinf(value);
            projection = desired.x * tangent.x + desired.y * tangent.y + desired.z * tangent.z;
            tangent.x *= projection;
            tangent.z *= projection;
            steer.x = desired.x + tangent.x;
            steer.y = 0.0f;
            steer.z = desired.z + tangent.z;
            Graphu64_NormalizeVec3(&steer);
            player->forward = steer.x * facing.x + steer.y * facing.y + steer.z * facing.z;
            navigationTurnRight(&facing);
            player->strafe = steer.x * facing.x + steer.z * facing.z;
        }
        if ((jumping || falling) && controller->airPitchNode) {
            value = delta.y;
            Scaled_SetPitchFromAngle(controller, XMath_EvaluateArcTangentTwo(value, Gu_Sqrtf(delta.x * delta.x + delta.z * delta.z)), 1);
            player->forward = g_targetSteeringAirForward;
        }
        if (controller->player->pose == 15) {
            if (position->y > controller->destination.y) {
                player->forward = g_targetSteeringDescendingPoseForward;
            } else {
                player->forward = g_targetSteeringAscendingPoseForward;
            }
        }
        if (controller->holdMovement) {
            player->strafe = 0.0f;
            player->forward = 0.0f;
        }
    }
}

/* 80208000_3.CPP */
/* Steers a computer player toward a point: measures the heading error to the point through Barrel_GetSignedAngleToPoint plus an offset, wrapped to -pi..pi, and when it exceeds the turn rate in degrees sets the player's steering at 0x69C to full lock beyond 60 degrees or to a half, quarter, eighth or tenth of lock beyond 30, 10 and 4 degrees, in the error's direction; then passes the brain's speed sum (by the player's gear at 0x594) in radians and the turn rate to Scaled_SetPitchFromAngle_Player and returns the heading error. */

extern f32 Barrel_GetSignedAngleToPoint(void *actor, struct CVector3_t point);
extern void Scaled_SetPitchFromAngle(PlayerAimBrainView *, f32, s32);

const float g_Nav_SteerAlongRouteConstantWords[9] = {
    5e+01f, 0.26179942f, 0.26179942f, 5e+01f,
    5e+01f, 5e+01f, 5e+01f, 1e+02f,
    3e+01f,
};
#if !(defined(VERSION_US_REV1))
const float g_Nav_UpdatePlayerSteeringConstantWords_de_eu_eu_x_us[9] = {
    1e+01f, 0.26179942f, 0.26179942f, 0.5f,
    1.0f, 3.1415927f, 1.0f, -1.0f,
    1.0f,
};
#endif
#if !(defined(VERSION_US_REV1))
const float g_Nav_UpdateTargetSteeringConstantWords_de_eu_eu_x_us[9] = {
    1e+01f, 0.26179942f, 0.26179942f, 0.5f,
    1.0f, 3.1415927f, 1.0f, -1.0f,
    1.0f,
};
#endif
#if defined(VERSION_US_REV1)
const float g_Nav_UpdatePlayerSteeringConstantWords_us_rev1[9] = {
    1e+01f, 0.26179942f, 0.26179942f, 0.5f,
    1.0f, 3.1415927f, 1.0f, -1.0f,
    1.0f,
};
#endif
#if defined(VERSION_US_REV1)
const float g_Nav_UpdateTargetSteeringConstantWords_us_rev1[9] = {
    1e+01f, 0.26179942f, 0.26179942f, 0.5f,
    1.0f, 3.1415927f, 1.0f, -1.0f,
    1.0f,
};
#endif
f32 Nav_SteerTowardPoint(PlayerAimBrainView *brain, CVector3 *target, f32 rate, f32 offset) {
    f32 angle;
    f32 direction;
    f32 limit;
    f32 scale;

    angle = Barrel_GetSignedAngleToPoint(brain->player, *target) + offset;
    if (angle > 3.141593f) {
        angle -= 6.283186f;
    } else if (angle < -3.141593f) {
        angle += 6.283186f;
    }
    direction = -1.0f;
    if (angle > 0.0f) {
        direction = 1.0f;
    }
    limit = rate * 0.017453294f;
    if (angle < 0.0f ? limit < -angle : limit < angle) {
        if (angle < 0.0f ? 1.0471977f < -angle : 1.0471977f < angle) {
            brain->player->steer = direction;
        } else {
            if (angle < 0.0f ? 0.52359885f < -angle : 0.52359885f < angle) {
                scale = 0.5f;
            } else if (angle < 0.0f ? 0.17453295f < -angle : 0.17453295f < angle) {
                scale = 0.25f;
            } else if (angle < 0.0f ? 0.06981318f < -angle : 0.06981318f < angle) {
                scale = 0.125f;
            } else {
                scale = 0.1f;
            }
            brain->player->steer = direction * scale;
        }
    }
    Scaled_SetPitchFromAngle(brain, (brain->player->gear == 2 ? brain->speed[1] + brain->speed[3] : brain->speed[0] + brain->speed[2]) * 0.017453294f, rate);
    return angle;
}

/* 800C6CA8.CPP */

/* 800C6CCC.CPP */

/* 800C6CF0.CPP */

/* 800C6D64.CPP */
const float g_Scaled_UpdateTargetPitchConstantWords[5] = {
    0.9f, 0.7f, -9e+01f, 9e+01f,
    57.295776f,
};

/* 800C6D78.CPP */
/* ROM-grounded data: src/g_Scaled_SetPitchFromAngleConstantWords_Player.c */
const float g_Scaled_SetPitchFromAngleConstantWords[1] = {
    0.6366197f,
};

/* 800C6D7C.CPP */
/* ROM-grounded data: src/g_Scaled_HasLineOfSightConstantWords_Player.c */
const float g_Scaled_HasLineOfSightConstantWords[1] = {
    102.399994f,
};

/* 800C6D80.CPP */
#if !(defined(VERSION_US_REV1))
const float g_Scaled_GetDifficultyEngagementAdjustmentConstantWords_de_eu_eu_x_us[3] = {
    0.01f, 0.9f, 1.1f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_Scaled_GetDifficultyEngagementAdjustmentConstantWords_us_rev1_Player.c */
const float g_Scaled_GetDifficultyEngagementAdjustmentConstantWords_us_rev1[3] = {
    0.01f, 0.9f, 1.1f,
};
#endif

/* 800C6D8C.CPP */
#if !(defined(VERSION_US_REV1))
const float g_Scaled_GetScaledAggressionConstantWords_de_eu_eu_x_us[3] = {
    0.01f, 0.9f, 1.1f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_Scaled_GetScaledAggressionConstantWords_us_rev1_Player.c */
const float g_Scaled_GetScaledAggressionConstantWords_us_rev1[3] = {
    0.01f, 0.9f, 1.1f,
};
#endif

/* 800C6D98.CPP */
#if !(defined(VERSION_US_REV1))
const float g_Scaled_ScaleCharacterSettingByDifficultyConstantWords[3] = {
    0.01f, 0.9f, 1.1f,
};
#endif

#if defined(VERSION_US_REV1)
const float k_PlayerEncodedWordsBlock13[3] = {
    0.01f, 0.9f, 1.1f,
};
#endif

/* 800C6DA4.CPP */
#if !(defined(VERSION_US_REV1))
const float g_Scaled_GetScaledAttackRangeConstantWords_de_eu_eu_x_us[3] = {
    0.01f, 0.9f, 1.1f,
};
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_Scaled_GetScaledAttackRangeConstantWords_us_rev1_Player.c */
const float g_Scaled_GetScaledAttackRangeConstantWords_us_rev1[3] = {
    0.01f, 0.9f, 1.1f,
};
#endif

/* 800C6DB0_2.CPP */
/* ROM-grounded data: src/g_Scaled_UpdateDifficultyAimJitterConstantWords_Player.c */
const float g_Scaled_UpdateDifficultyAimJitterConstantWords[2] = {
    0.26179942f, 0.26179942f,
};

#if defined(VERSION_US)
unsigned int k_PlayerEncodedWordsBlock15[2] = {
    0x001C0000, 0x00080008,
};
#endif

#if defined(VERSION_EU_X)
unsigned int k_PlayerEncodedWordsBlock17[2] = {
    0x00229F54, 0x3B800000,
};
#endif

#if defined(VERSION_EU)
unsigned int k_PlayerEncodedWordsBlock16[2] = {
    0x1440FFFD, 0x00000000,
};
#endif
