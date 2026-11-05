#include "Common/output.h"
#include "frontend_symbols.h"
#include "Common/game_session.h"
#include "Common/vector4f.h"
#include "include_asm.h"
#include "Common/ai_behaviour_types.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Weapons/player_movement_interfaces.h"
#include "Common/navigation_graph.h"
#include "Common/shared_gameslot.h"
#include "Common/rendercounters.h"
#include "Fx/normalize_vector.h"
#include "Common/navigation_node_and_route_views.h"
#include "Common/rec.h"
#include "Ai/Nav/nav_updatecomputerplayerstatus.h"
#include "Common/sharedplayer.h"
#include "Ai/Player/scaled_updatetargetpitch.h"
#include "Behaviour/behaviour.h"
#include "Engine/contpad.h"
#include "Frontend/player.h"
#include "Gfx/Text/onscreen_drawscaledmaskedtilegrid.h"
#include "Insthdr/insthdr_getactorshadowradius.h"
#include "Ai/Cbarrel/barrel_getsignedangletopoint.h"
#include "Ai/Player/player_getammocapacity.h"
#include "Common/font_style_and_glyph_operations.h"
#include "Ai/shared_pickupgoalnode.h"
#include "Common/triple.h"
#include "Ai/nav_symbols.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Ai/ai_functions.h"
#include "Common/Lone/particle_collision_probe_result.h"
#include "Common/aiprofile.h"
#include "Common/weapon_screen_message_operations.h"
#include "Common/ballisticparams.h"
#include "Common/integerstate2c.h"
#include "Ai/Player/player_placeplayerforround.h"
#include "Render/playerai_toggleforcemarker.h"
#include "Libsn/nav_isballisticarcobstructed_data.h"
#include "Ai/portal_isnodemovementblocked.h"
#include "Engine/Unicol/unicol.h"
#include "Common/Lone/collision_current_actor.h"
#include "Ai/ai_shared_symbols.h"
#include "Data/rest_source_records.h"
#include "Ai/Nav/Scaled/g_actorradialdirections_wheel.h"
#include "Ai/Nav/carrier.h"
#include "Ai/Nav/combatinit.h"
#include "Ai/Nav/farthest.h"
#include "Ai/Nav/jumproute.h"
#include "Ai/Nav/nav_initpursuitstrafe.h"
#include "Ai/Nav/nav_resetobjectarrivalchase.h"
#include "Ai/Nav/nav_selectpickupgoal.h"
#include "Ai/Nav/nav_updateclosecombat.h"
#include "Ai/Nav/nav_updaterangedcombat.h"
#include "Ai/Nav/nav_updatevisiblepursuit.h"
#include "Ai/Nav/roam.h"
#include "Ai/Nav/targetfollow.h"
#include "Ai/Nav/wheel.h"
#include "Attack/attack.h"
#include "Fx/target.h"
#include "Game/weaponselect.h"
#include "pickup.h"
#include "Data/Ovl1_c/navigation_callback_address.h"
#include "Data/Ovl1_d/nav_initvisiblepursuit.h"
#include "Data/Ovl1_d/addrlow_nav_updatevisiblepursuit.h"
#include "Data/Actor_state_callbacks/actor_state_callback_labels.h"

/* Resets a player controller: marks the active, requested and committed selections empty, sets the
   request kind to 0xB, clears the four link words to -1, resets the stage counters
   and 0x1C8 and the target list, installs the default table g_playerDefaultBehaviorTable through Scaled_SetBehaviorTable and mode
   2 through Scaled_SetBehaviourState_Player, zeroes the tracking values, runs the resets
   Nav_ResetWheelProbeState, Scaled_ResetBehaviorState and Scaled_ClearAuxiliaryBehaviorState, and clears the remaining state words. */


void Nav_ResetPlayerState(s32 *state) {
    s32 i;
    s32 none;

    ((Brain *)state)->start = -1;
    ((Brain *)state)->route = -1;
    ((Brain *)state)->destination = 11;
    ((Brain *)state)->node = -1;
    ((Brain *)state)->goalCounters[0] = 0;
    ((Brain *)state)->goalCounters[1] = 0;
    ((Brain *)state)->goalCounters[2] = 0;
    none = -1;
    for (i = 3; i >= 0; i--) {
        ((Brain *)state)->recentNodes[i] = none;
    }
    ((Brain *)state)->pickupGoal = -1;
    ((Brain *)state)->stage = 0xFFFF;
    ((Brain *)state)->state = 0;
    ((Brain *)state)->matches = 0;
    ((Brain *)state)->searchEnabled = 1;
    ((Brain *)state)->goalHistory[0] = 0;
    ((Brain *)state)->target = 0;
    ((Brain *)state)->preferred = 0;
    ((Brain *)state)->targetAux = 0;
    ((Brain *)state)->routeState = -1;
    ((Brain *)state)->patrolRoute = -1;
    ((Brain *)state)->patrolPosition = 0;
    for (i = 0; i < 10; i++) {
        ((Brain *)state)->goalHistory[i] = 0;
        ((Brain *)state)->goalSlotsA[i] = 0;
        ((Brain *)state)->goalSlotsB[i] = 0;
    }
    ((Brain *)state)->arrived = 0;
    Scaled_SetBehaviorTable(state, &g_playerDefaultBehaviorTable);
    Scaled_SetBehaviourState(state, 2);
    ((Brain *)state)->tracking[0] = 0.0f;
    ((Brain *)state)->waitingFlag = 0;
    ((Brain *)state)->pursuitEndedFlag = 0;
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


extern void Scaled_UpdateTargetPitch(Brain *);



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
    if (brain->behaviour->update.address != 0) {
        ((void (*)(Player *, s32))brain->behaviour->update.address)(brain->player, 0);
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
                OnScreen_SetFirstBarTarget((char *)&g_gameSession.hud, (f32)tutorial->m_nBastilleShield);
                if (tutorial->m_nBastilleTimer > 0) {
                    tutorial->m_nBastilleTimer--;
                    ContPad_ClearControllerInput((char *)&((SharedPlayer *)brain->player)->views5E8.view688_33.body);
                    brain->waitingFlag = 0;
                    brain->pursuitEndedFlag = 0;
                }
                if (tutorial->m_nBastilleTimer == 0 && brain->player->views5E4.view5E4_2.health > 0) {
                    tutorial->m_nBastilleShield = 100;
                    tutorial->m_nBastilleTimer = -1;
                    Player_SetPlayerState(brain->player, brain->player, 2);
                }
            }
            if (brain->player->views5D8.view5D8_1.record->display == 1) {
                OnScreen_SetFirstBarTarget((char *)&g_gameSession.hud, meter);
            } else {
                OnScreen_SetSecondBarTarget((char *)&g_gameSession.hud, meter);
            }
        }
    }
    player = brain->player;
    if (player->views5E8.view650_16.state == 18) {
        player->views1340.view1340_1.stalls++;
        Scaled_HandlePlayerTimeout(brain);
    }
}

f32 Graphu64_GetPointDistance(f32 *a, f32 *b);
f32 Nav_SteerTowardPoint(PlayerAimBrainView *, CVector3 *, f32, f32);
float Gu_Sqrtf(float);
void *Portal_GetStridedTableEntry(struct CNavData_t *object, int index);
struct CNavData_t; int Portal_FindLinkIndex(struct CNavData_t *graph, int from, int to);
s32 Scaled_AdvanceNodeQueue(AiController *);

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
    LevelActor *ground;
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
                            ground = (LevelActor *)InstHdr_GetEnabledItemValue(controller->player);
                            if (ground != 0) {
                                riding = ((ActorMotionResource *)ground->definition)->kind == 2;
                            }
                            Graphu64_SubtractVectors(&delta, pos, &((NavigationSearchNode *)Portal_FindSearchNode(graph, controller->current))->platform->pos);
                            gap = Gu_Sqrtf(delta.x * delta.x + delta.z * delta.z);
                            if (riding != 0 && gap < g_platformRiderHorizontalTolerance) {
                                controller->linkTraversalPhase = 3;
                            } else {
                                controller->destination = ((NavigationSearchNode *)Portal_FindSearchNode(graph, controller->current))->platform->pos;
                                return;
                            }
                        }
                        if (controller->linkTraversalPhase == 3) {
                            riding = 0;
                            ground = (LevelActor *)InstHdr_GetEnabledItemValue(controller->player);
                            if (ground != 0) {
                                riding = ((ActorMotionResource *)ground->definition)->kind == 2;
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


static __inline__ void navigationTurnLeft(CVector3 *direction) {
    direction->y = direction->x;
    direction->x = -direction->z;
    direction->z = direction->y;
    direction->y = 0.0f;
}
static __inline__ void navigationTurnRight(CVector3 *direction) {
    direction->y = direction->x;
    direction->x = direction->z;
    direction->z = -direction->y;
    direction->y = 0.0f;
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
                    Scaled_SetPitchFromAngle(controller, XMath_EvaluateArcTangentTwo(value, Gu_Sqrtf(delta.x * delta.x + delta.z * delta.z)));
                    player->forward = g_playerSteeringAirPitchForward;
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
            tangent = ((NavigationPoint *)Portal_GetGraphPoint(graph, controller->current))->position;
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
            Scaled_SetPitchFromAngle(controller, XMath_EvaluateArcTangentTwo(value, Gu_Sqrtf(delta.x * delta.x + delta.z * delta.z)));
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
                    Scaled_SetPitchFromAngle(controller, XMath_EvaluateArcTangentTwo(value, Gu_Sqrtf(delta.x * delta.x + delta.z * delta.z)));
                    player->forward = g_targetSteeringAirPitchForward;
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
            tangent = ((NavigationPoint *)Portal_GetGraphPoint(graph, controller->current))->position;
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
            Scaled_SetPitchFromAngle(controller, XMath_EvaluateArcTangentTwo(value, Gu_Sqrtf(delta.x * delta.x + delta.z * delta.z)));
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

/* Steers a computer player toward a point: measures the heading error to the point through
 * Barrel_GetSignedAngleToPoint plus an offset, wrapped to -pi..pi, and when it exceeds the turn rate in degrees
 * sets the player's steering to full lock beyond 60 degrees or to a half, quarter, eighth or tenth of lock
 * beyond 30, 10 and 4 degrees, in the error's direction; then passes the brain's speed sum (by the player's
 * gear) in radians and the turn rate to Scaled_SetPitchFromAngle_Player and returns the heading error. */



#if !(defined(VERSION_US_REV1))

#endif
#if !(defined(VERSION_US_REV1))

#endif
#if defined(VERSION_US_REV1)

#endif
#if defined(VERSION_US_REV1)

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
    Scaled_SetPitchFromAngle(brain, (brain->player->gear == 2 ? brain->speed[1] + brain->speed[3] : brain->speed[0] + brain->speed[2]) * 0.017453294f);
    return angle;
}








#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_US_REV1)

#endif

#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_US_REV1)

#endif

#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_US_REV1)

#endif

#if !(defined(VERSION_US_REV1))

#endif

#if defined(VERSION_US_REV1)

#endif



#if defined(VERSION_US)
extern unsigned int k_playerPackedHalfwordPairs[2];
#endif

#if defined(VERSION_EU_X)
unsigned int k_playerPointerAndByteScale[2] = {
    0x00229F54, 0x3B800000,
};
#endif

#if defined(VERSION_EU)
extern unsigned int k_playerBranchInstructionWords[2];
#endif

/* Revives a player whose down timer has run past its limit (30 ticks, or 900 in
   control modes 12 and 15 while g_selectedProfileHealthOptionEnabled asks): clears the timer and calls Player_PlacePlayerForRound
   unless the session is running and the player's team membership and control
   mode disagree, or it is teamless and active outside session mode 3. */


void Scaled_UpdateTargetPitch(Brain *object) {
    void *memory = object;
    PitchBrain *brain = memory;
    CVector3 origin, delta;
    f32 ownHeight, targetHeight, correction, vertical, horizontal, zero;
    PitchPlayer *target;
    if (brain->target) {
        origin = brain->player->position;
        Player_GetPlayerViewTranslation(brain->player, &delta.x);
        ownHeight = delta.y - brain->player->position.y;
        target = brain->target->player;
        if (target->transformed) {
            Player_GetPlayerViewTranslation(target, &delta.x);
            targetHeight = delta.y - target->position.y;
        } else targetHeight = target->model->height - target->position.y;
        targetHeight *= g_targetPitchHeightScale;
        if (g_gameSettings.counters.m_bFragTagOn && target->profile->scaled) targetHeight *= g_fragTagTargetHeightScale;
        delta = brain->targetPosition;
        delta.x -= origin.x;
        delta.y -= origin.y;
        delta.z -= origin.z;
        correction = targetHeight - ownHeight;
        brain->distance = Gu_Sqrtf(delta.x*delta.x + delta.y*delta.y + delta.z*delta.z);
        vertical = delta.y;
        delta.y = 0.0f;
        vertical += correction;
        zero = delta.y;
        horizontal = Gu_Sqrtf(delta.x*delta.x + delta.z*delta.z);
        if (horizontal == zero) {
            if (vertical < zero) brain->angle = g_targetPitchDownAngle;
            else brain->angle = g_targetPitchUpAngle;
        } else brain->angle = XMath_EvaluateArcTangentTwo(vertical, horizontal) * g_targetPitchRadiansToDegrees;
    } else brain->angle = 0.0f;
    brain->previousAngle = brain->angle;
}

/* Stores the player, then resets its AI state using the same pointer. */
void Scaled_InitPlayerState(int *state, int player) {
    *state = player;
    Nav_ResetPlayerState(state);
}

void Scaled_ClearNodeQueue(AiController *controller)
{
    s32 i;
    s32 empty;
    empty = -1;
    i = 3;
    do {
        controller->queue[i] = empty;
        i -= 1;
    } while (i >= 0);
}

/* Pops the front of a four-entry queue of a record: shifts the entries down one,
   marks the last empty with -1 and returns whether an entry remains at the front. */

s32 Scaled_AdvanceNodeQueue(AiController *queue) {
    s32 i;

    for (i = 1; i < 4; i++) {
        queue->queue[i - 1] = queue->queue[i];
    }
    queue->queue[3] = -1;
    return queue->queue[0] != -1;
}

/** Store the second argument in the first argument. */
void Scaled_SetBehaviorTable(AiController *object, AiBehaviourTable *value) {
    object->table = value;
}

s32 Scaled_SetBehaviourState(AiController *controller, s32 behaviourId) {
    AiBehaviourTable *node;
    AiBehaviourEntry *entry;
    AiBehaviourEntry *found;
    void (*callback)(Player *, s32);

    node = controller->table;
    found = 0;
    controller->state = behaviourId;
    while (node != 0) {
        entry = node->entries;
        if (entry->id != -1) {
            while (entry->id != -1) {
                if (entry->id == behaviourId) {
                    found = entry;
                    node = 0;
                    break;
                }
                entry++;
            }
        }
        if (node != 0) node = node->next;
    }
    if (found == 0) return 0;
    controller->behaviour = found;
    callback = (void (*)(Player *, s32))found->enter.address;
    if (callback != 0) callback(controller->player, 0);
    return 1;
}

void Scaled_SetPitchFromAngle(AiController *controller, float amount) {
    float result = amount * g_difficultyAimAmountScale;
    if (controller != 0) {
        controller->player->pitch = -result;
    }
}

CVector3 *Scaled_GetControllerPosition(AiController *controller) {
    return &controller->player->pos;
}

f32 Scaled_DistanceToNode(AiController *controller, s32 nodeId) {
    return Graphu64_GetPointDistance(&controller->player->pos.x, Portal_GetGraphPoint(&g_navigationGraph, nodeId));
}

/** Reset three state words and set the final state to one. */
void Scaled_ResetBehaviorState(void *object) {
    AiController *controller = object;
    controller->behaviorStateWordA = 0;
    controller->behaviorStateWordB = 0;
    controller->behaviorResetFlag = 1;
}

/** Clear five consecutive object words beginning. */
void Scaled_ClearAuxiliaryBehaviorState(AiController *controller) {
    controller->routeComplete = 0;
    controller->airPitchNode = 0;
    controller->jumpLinkActive = 0;
    controller->kindFourLinkActive = 0;
    controller->holdMovement = 0;
}

s32 Scaled_HasLineOfSight(Player **fromRef, Player *target) {
    CVector3 first;
    CVector3 second;

    if (fromRef == 0 || target == 0) {
        return 0;
    }

    first = (*fromRef)->pos;
    second = target->pos;
    first.y += g_difficultyAimHeightOffset;
    second.y += g_difficultyAimHeightOffset;
    if (CCollision_SweepPoint(*fromRef, first, second, &g_particleCollisionProbeResult) != 0) {
        return g_collisionCurrentActor->instance0 == target;
    }
    return 1;
}

s32 Scaled_MatchesBehaviorStateFilter(AiController *controller) {
    s32 state;

    state = controller->state;
    if (state >= 8) {
        goto ge_8;
    }
    if (state >= 3) {
        goto ret1;
    }
    if (state == 1) {
        goto ret1;
    }
    goto ret0;
ge_8:
    if (state != 13) {
        goto ret0;
    }
ret1:
    return 1;
ret0:
    return 0;
}

/** Report whether the controller is in the seek-pickup state (8), which nav enters for health or ammo pickups. */
int Scaled_IsSeekingPickup(AiController *object) {
    return object->state == 8;
}

f32 Scaled_GetDifficultyEngagementAdjustment(AiController *controller)
{
  Player *object;
    AiCharacterDefinition *definition;
  u8 state;
  f32 difficultyMultiplier;
  f32 engagementAdjustment;
  object = controller->player;
    definition = object->definition;
  state = object->profile->difficulty;
  engagementAdjustment = definition->engagement;
  engagementAdjustment = engagementAdjustment * g_difficultyEngagementScale;
  switch (state)
  {
    case 1:
      goto done;

    default:
      controller->player->profile->difficulty = 0;

    case 0:
      difficultyMultiplier = g_difficultyEngagementDefaultMultiplier;
      break;

    case 2:
      difficultyMultiplier = g_difficultyEngagementOtherMultiplier;
      break;

  }

  engagementAdjustment *= difficultyMultiplier;
  done:
  return engagementAdjustment;

}

f32 Scaled_GetScaledAggression(AiController *controller) {
    f32 value;
    u8 difficulty;
    Player *player;
    AiCharacterDefinition *definition;

    player = controller->player;
    definition = player->definition;
    difficulty = player->profile->difficulty;
    value = definition->aggression;
    value *= g_aiAggressionBaseScale;
    switch (difficulty) {
    case 1:
        break;
    default:
        controller->player->profile->difficulty = 0;
    case 0:
        value *= g_aiAggressionEasyScale;
        break;
    case 2:
        value *= g_aiAggressionHardScale;
        break;
    }
    return value;
}

f32 Scaled_ScaleCharacterSettingByDifficulty(AiController *controller) {
    f32 difficultyScale;
    f32 value;
    u8 difficulty;
    Player *player;
    AiCharacterDefinition *definition;

    player = controller->player;
    definition = player->definition;
    difficulty = player->profile->difficulty;
    value = definition->characterSetting;
    value *= g_aiCharacterSettingBaseScale;
    switch (difficulty) {
    case 1:
        goto done;
    default:
        controller->player->profile->difficulty = 0;
    case 0:
        difficultyScale = g_aiCharacterSettingEasyScale;
        goto multiply;
    case 2:
        difficultyScale = g_aiCharacterSettingHardScale;
    }
multiply:
    value *= difficultyScale;
done:
    return value;
}

f32 Scaled_GetScaledAttackRange(AiController *controller) {
    f32 difficultyScale;
    f32 value;
    u8 difficulty;
    Player *player;
    AiCharacterDefinition *definition;

    player = controller->player;
    definition = player->definition;
    difficulty = player->profile->difficulty;
    value = definition->attackRange;
    value *= g_aiAttackRangeBaseScale;
    switch (difficulty) {
    case 1:
        break;
    default:
        controller->player->profile->difficulty = 0;
    case 0:
        difficultyScale = g_aiAttackRangeEasyScale;
        goto multiply;
    case 2:
        difficultyScale = g_aiAttackRangeHardScale;
multiply:
        value *= difficultyScale;
        break;
    }
    return value;
}

void Scaled_HandlePlayerTimeout(SharedPlayer **brain) {
    s32 limit;
    Controls *controls;
    CGameStatus *session;
    s8 mode;

    if (g_gameSettings.counters.enabled != 0) {
        mode = (*brain)->views5D8.view5D8_2.controls->mode;
        if (mode == 12 || mode == 15) {
            limit = 900;
        } else {
            limit = 30;
        }
    } else {
        limit = 30;
    }
    if (limit < (*brain)->views1340.view1340_2.timer) {
        session = &g_gameSettings.counters;
        do {
            (*brain)->views1340.view1340_2.timer = 0;
        } while (0);
        if (session->enabled != 0) {
            controls = (*brain)->views5D8.view5D8_2.controls;
            if (controls->team == 0) {
                if (controls->active == 0 || session->m_nTalsetLives == 3) {
                    Player_PlacePlayerForRound(*brain);
                }
            } else {
                mode = controls->mode;
                if (mode == 12 || mode == 15) {
                    Player_PlacePlayerForRound(*brain);
                }
            }
        } else {
            Player_PlacePlayerForRound(*brain);
        }
    }
}

f32 Scaled_UpdateDifficultyAimJitter(void *aiController) {
    AiController *brain = aiController;
    f32 aim;
    f32 aimLimit;
    u8 difficulty;

    difficulty = brain->player->profile->difficulty;
    switch (difficulty) {
    default:
        brain->player->profile->difficulty = 0;
    case 0:
        aimLimit = (1.2217305898666382f);
        break;
    case 1:
        aimLimit = (0.8726646900177002f);
        break;
    case 2:
        aimLimit = (0.523598849773407f);
        break;
    }
    aim = brain->aim;
    if (aim < Graphu64_RandomBetween(-aimLimit, aimLimit)) {
        aim += g_difficultyAimPositiveJitter;
    } else {
        aim -= g_difficultyAimNegativeJitter;
    }
    brain->aim = aim;
    return aim;
}

#if defined(VERSION_US)
extern unsigned int k_ScaledUpdatetargetpitchData[1];
#endif

#if defined(VERSION_EU)
#if defined(VERSION_EU)
extern SceneEffectLookupWordsEuEncodedHalfwordsLayout k_SceneEffectLookupWordsEuEncodedHalfwords;
#endif
#endif

/* Retained data for this translation unit. */

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

const float g_Scaled_UpdateTargetPitchConstantWords[5] = {
    0.9f, 0.7f, -9e+01f, 9e+01f,
    57.295776f,
};

const float g_Scaled_SetPitchFromAngleConstantWords[1] = {
    0.6366197f,
};

const float g_Scaled_HasLineOfSightConstantWords[1] = {
    102.399994f,
};
#if !(defined(VERSION_US_REV1))
const float g_Scaled_GetDifficultyEngagementAdjustmentConstantWords_de_eu_eu_x_us[3] = {
    0.01f, 0.9f, 1.1f,
};
#endif
#if defined(VERSION_US_REV1)
const float g_Scaled_GetDifficultyEngagementAdjustmentConstantWords_us_rev1[3] = {
    0.01f, 0.9f, 1.1f,
};
#endif
#if !(defined(VERSION_US_REV1))
const float g_Scaled_GetScaledAggressionConstantWords_de_eu_eu_x_us[3] = {
    0.01f, 0.9f, 1.1f,
};
#endif
#if defined(VERSION_US_REV1)
const float g_Scaled_GetScaledAggressionConstantWords_us_rev1[3] = {
    0.01f, 0.9f, 1.1f,
};
#endif
#if !(defined(VERSION_US_REV1))
const float g_Scaled_ScaleCharacterSettingByDifficultyConstantWords[3] = {
    0.01f, 0.9f, 1.1f,
};
#endif
#if defined(VERSION_US_REV1)
const float k_PlayerEpsilonAndScaleBand[3] = {
    0.01f, 0.9f, 1.1f,
};
#endif
#if !(defined(VERSION_US_REV1))
const float g_Scaled_GetScaledAttackRangeConstantWords_de_eu_eu_x_us[3] = {
    0.01f, 0.9f, 1.1f,
};
#endif
#if defined(VERSION_US_REV1)
const float g_Scaled_GetScaledAttackRangeConstantWords_us_rev1[3] = {
    0.01f, 0.9f, 1.1f,
};
#endif

const float g_Scaled_UpdateDifficultyAimJitterConstantWords[2] = {
    0.26179942f, 0.26179942f,
};
