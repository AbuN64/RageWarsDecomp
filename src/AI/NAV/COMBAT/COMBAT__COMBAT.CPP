#include "include_asm.h"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/SELF.H"
#include "TYPES.H"
#include "AI/NAV/NAV_UPDATERANGEDCOMBAT.H"
#include "AI/NAV/NAV_UPDATECLOSECOMBAT.H"
#include "COMMON/WEAPON_MARKER_AND_PROFILE_VIEWS.H"
#include "AI/NAV/NAV_UPDATEVISIBLEPURSUIT.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "AI/NAV/NAV_INITPURSUITSTRAFE.H"

extern void Nav_RunBehaviorHandler(void *);
extern s32 Scaled_HasLineOfSight(void *, void *);
extern void Scaled_SetBehaviourState(void *, s32);
extern f32 Scaled_ScaleCharacterSettingByDifficulty(void *);
extern f32 Scaled_UpdateDifficultyAimJitter(void *);
extern f32 Nav_SteerTowardPoint(void *, CVector3 *, f32, f32);
extern void Wheel_MeasureWheelClearance(void *, s32);
extern void Portal_DispatchActorBehavior(void *);

/* 802106E0_11.CPP */
/* Drives combat pursuit, retreat and strafing while refreshing target visibility, routes and fire timing. */

extern char g_navigationGraph[];

extern f32 Graphu64_GetSquaredDistance(CVector3 *, CVector3 *);
extern s32 Wheel_GetDirectionSector(f32);
extern s32 Route_GetRouteRelation(char *, s32, s32);

extern void Nav_SteerAlongRoute(CloseAttackBrain *),Nav_UpdatePlayerSteering(CloseAttackBrain *),Nav_SelectPlayerState(CloseAttackBrain *);
extern struct {char pad[0xC];unsigned short flags;} *Portal_GetGraphPoint(char *,int);

void Nav_UpdateRangedCombat(CloseAttackActor *actor) {
 char *routes;int mine,theirs,dir; CloseAttackActor *player;
    CloseAttackActor *target;
    CloseAttackActor *targetActor;
    CloseAttackActor *playerValue;
    CloseAttackBrain *brain;
    CVector3 *targetPosition;
    f32 squaredDistance;
    f32 approachThreshold;
    f32 retreatThreshold;
    f32 strafeSpeed;
    f32 difficultySetting;
    f32 distance;
    f32 desiredSquaredDistance;
    s32 route;
    s32 movementTimer;
    s32 fireTimer;
    s32 unusedValue;
    s32 pattern;
    s32 unusedValue1;
    s32 unusedValue2;
    s32 unusedValue3;
    s32 unusedValue4;
    s32 unusedValue5;
    s32 unusedValue6;

    brain = actor->self->brain;
    Nav_RunBehaviorHandler(brain);
    target = brain->target;routes=g_navigationGraph;
    if (target != 0) {
        if (!(brain->frames & 3)) {
            brain->visible = Scaled_HasLineOfSight(brain, target);
        }
        brain->frames += 1;
        targetActor = brain->target->self;
        mine=brain->player->flags&0x3000;theirs=(targetActor->flags&0x3000)!=0;
        if (mine && !theirs) {
            Scaled_SetBehaviourState(brain,12);return;
        }
        route = targetActor->brain->route;
        if (Portal_GetGraphPoint(routes, route)->flags & 0x400) {
            brain->target = 0;
            Nav_SelectPlayerState(brain);
            return;
        }
        if (brain->visible != 0) {
            difficultySetting = Scaled_ScaleCharacterSettingByDifficulty(brain);
            movementTimer = brain->timer - 1;
            strafeSpeed = difficultySetting * 0.6f;
            brain->timer = movementTimer;
            if (movementTimer <= 0) {
                brain->timer=Graphu64_NextRandom()%4+12;
                brain->pattern = Graphu64_NextRandom() % 2;
                brain->distance = (Graphu64_NextRandom() % 250000) + 360000;
            }
            targetPosition = &targetActor->pos;
            Nav_SteerTowardPoint(brain, targetPosition, 2.0f, Scaled_UpdateDifficultyAimJitter(brain));
            squaredDistance = Graphu64_GetSquaredDistance(targetPosition, &brain->player->pos);
            approachThreshold = squaredDistance + 10000.0f;
            distance = (f32) brain->distance;
            if (approachThreshold < 0.0f) {
                if (distance < -approachThreshold) {
                    goto block_19;
                }
                goto block_23;
            }
            if (distance < approachThreshold) {
block_19:
                dir = Wheel_GetDirectionSector(brain->player->yaw - 3.1415927f);
                player = brain->player;
                if ((player->slot % 2) == g_lightingBufferIndex) {
                    Wheel_MeasureWheelClearance(player, dir);
                }
                if (!(brain->clearance[dir] < 100.0f)) {
                    brain->player->forward = 1.0f;
                } else {
                    goto block_31;
                }
            } else {
block_23:
                retreatThreshold = squaredDistance - 10000.0f;
                desiredSquaredDistance = (f32) brain->distance;
                if (retreatThreshold < 0.0f) {
                    if (-retreatThreshold < desiredSquaredDistance) {
                        goto block_27;
                    }
                    goto block_31;
                }
                if (retreatThreshold < desiredSquaredDistance) {
block_27:
                    dir = Wheel_GetDirectionSector(brain->player->yaw);
                    player = brain->player;
                    if ((player->slot % 2) == g_lightingBufferIndex) {
                        Wheel_MeasureWheelClearance(player, dir);
                    }
                    if (!(brain->clearance[dir] < 100.0f)) {
                        brain->player->forward = -1.0f;
                    } else {
                        goto block_31;
                    }
                } else {
block_31:
                    brain->player->forward = 0.0f;
                }
            }
            pattern = brain->pattern;
            if (pattern == 0) {
                dir = Wheel_GetDirectionSector((brain->player->yaw - 3.1415927f) - 1.5707964f);
                player = brain->player;
                if ((player->slot % 2) == g_lightingBufferIndex) {
                    Wheel_MeasureWheelClearance(player, dir);
                }
                if (!(brain->clearance[dir] < 100.0f)) {
                    brain->player->strafe = -strafeSpeed;
                } else {
                    goto block_41;
                }
            } else if (pattern == 1) {
                dir = Wheel_GetDirectionSector((brain->player->yaw - 3.1415927f) + 1.5707964f);
                player = brain->player;
                if ((player->slot % 2) == g_lightingBufferIndex) {
                    Wheel_MeasureWheelClearance(player, dir);
                }
                if (brain->clearance[dir] < 100.0f) {
block_41:
                    brain->player->strafe = 0.0f;
                    brain->pattern = 2;
                } else {
                    brain->player->strafe = strafeSpeed;
                }
            } else {
                brain->player->strafe = 0.0f;
            }
            brain->routeNodes[0] = -1;
            fireTimer = brain->fireTimer - 1;
            brain->fireTimer = fireTimer;
            if ((fireTimer == 0) && ((Graphu64_NextRandom() % 100) < (s32) difficultySetting)) {
                playerValue = brain->player;
                playerValue->buttons |= 0x10;
            }
            if (brain->fireTimer < 0) {
                brain->fireTimer = ((Graphu64_NextRandom() % 2) + 2) * 15;
            }
            Portal_DispatchActorBehavior(brain);
        } else {
            brain->destination = route;
            Nav_SteerAlongRoute(brain);
            Nav_UpdatePlayerSteering(brain);
        }
        if (route != brain->node) {
            brain->node = route;
            if (Route_GetRouteRelation(routes, brain->route, route) == 0) {
                Scaled_SetBehaviourState(brain,1);
            }
        }
    }
}

/* 802106E0_12.CPP */
/* Drives close-range combat: pursuit, retreat and strafing around a target, bailing out when it gets too far away. */

void Nav_UpdateCloseCombat(CloseAttackActor *actor) {
    char *routes;
    s32 mine, theirs, dir, route;
    CloseAttackActor *player;
    CloseAttackActor *target;
    CloseAttackBrain *brain;
    CVector3 *pos;
    f32 dist, near, far, range, speed, strafe;
    s32 pattern;

    brain = actor->self->brain;
    Nav_RunBehaviorHandler(brain);
    player = brain->target;
    routes = g_navigationGraph;
    if (player != 0) {
        if (!(brain->frames & 3)) {
            brain->visible = Scaled_HasLineOfSight(brain, player);
        }
        brain->frames += 1;
        target = brain->target->self;
        mine = brain->player->flags & 0x3000;
        theirs = (target->flags & 0x3000) != 0;
        if (mine && !theirs) {
            Scaled_SetBehaviourState(brain, 12);
            return;
        }
        route = target->brain->route;
        if (Portal_GetGraphPoint(routes, route)->flags & 0x400) {
            brain->target = 0;
            Nav_SelectPlayerState(brain);
            return;
        }
        if (brain->visible != 0) {
            speed = Scaled_ScaleCharacterSettingByDifficulty(brain);
            strafe = speed;
            if (--brain->timer <= 0) {
                brain->timer = Graphu64_NextRandom() % 4 + 2;
                brain->pattern = Graphu64_NextRandom() % 2;
                brain->distance = Graphu64_NextRandom() % 32400 + 10000;
            }
            pos = &target->pos;
            Nav_SteerTowardPoint(brain, pos, 2.0f, Scaled_UpdateDifficultyAimJitter(brain));
            dist = Graphu64_GetSquaredDistance(pos, &brain->player->pos);
            if (dist > 377487.3f) {
                brain->combat = 5;
                Scaled_SetBehaviourState(brain, 6);
                return;
            }
            near = dist + 10000.0f;
            range = (f32)brain->distance;
            if (near < 0.0f) {
                if (range < -near) {
                    goto fwd;
                }
                goto back_test;
            }
            if (range < near) {
fwd:
                dir = Wheel_GetDirectionSector(brain->player->yaw - 3.1415927f);
                player = brain->player;
                if ((player->slot % 2) == g_lightingBufferIndex) {
                    Wheel_MeasureWheelClearance(player, dir);
                }
                if (!(brain->clearance[dir] < 100.0f)) {
                    brain->player->forward = 1.0f;
                } else {
                    goto stop;
                }
            } else {
back_test:
                far = dist - 10000.0f;
                range = (f32)brain->distance;
                if (far < 0.0f) {
                    if (-far < range) {
                        goto back;
                    }
                    goto stop;
                }
                if (far < range) {
back:
                    dir = Wheel_GetDirectionSector(brain->player->yaw);
                    player = brain->player;
                    if ((player->slot % 2) == g_lightingBufferIndex) {
                        Wheel_MeasureWheelClearance(player, dir);
                    }
                    if (!(brain->clearance[dir] < 100.0f)) {
                        brain->player->forward = -1.0f;
                    } else {
                        goto stop;
                    }
                } else {
stop:
                    brain->player->forward = 0.0f;
                }
            }
            pattern = brain->pattern;
            if (pattern == 0) {
                dir = Wheel_GetDirectionSector((brain->player->yaw - 3.1415927f) - 1.5707964f);
                player = brain->player;
                if ((player->slot % 2) == g_lightingBufferIndex) {
                    Wheel_MeasureWheelClearance(player, dir);
                }
                if (!(brain->clearance[dir] < 100.0f)) {
                    brain->player->strafe = -strafe;
                } else {
                    goto halt;
                }
            } else if (pattern == 1) {
                dir = Wheel_GetDirectionSector((brain->player->yaw - 3.1415927f) + 1.5707964f);
                player = brain->player;
                if ((player->slot % 2) == g_lightingBufferIndex) {
                    Wheel_MeasureWheelClearance(player, dir);
                }
                if (brain->clearance[dir] < 100.0f) {
halt:
                    brain->player->strafe = 0.0f;
                    brain->pattern = 2;
                } else {
                    brain->player->strafe = strafe;
                }
            } else {
                brain->player->strafe = 0.0f;
            }
            brain->routeNodes[0] = -1;
            if (--brain->fireTimer == 0 && (Graphu64_NextRandom() % 100) < (s32)speed) {
                brain->player->buttons |= 0x10;
            }
            if (brain->fireTimer < 0) {
                brain->fireTimer = ((Graphu64_NextRandom() % 1) + 2) * 15;
            }
            Portal_DispatchActorBehavior(brain);
        } else {
            brain->destination = route;
            Nav_SteerAlongRoute(brain);
            Nav_UpdatePlayerSteering(brain);
        }
        if (route != brain->node) {
            brain->node = route;
            if (Route_GetRouteRelation(routes, brain->route, route) == 0) {
                Scaled_SetBehaviourState(brain, 1);
            }
        }
    }
}

/* 802106E0_13.CPP */
/* Runs a computer player's chase state: refreshes its view through Nav_RunBehaviorHandler and, without a target, returns to roaming (state 2); otherwise re-checks the target's visibility every fourth frame through Nav_CheckTarget_de, backs off (state 12) when only it is on the upper layer, switches to close combat (state 7, sub-state 13) within 600 units, re-rolls its strafe pattern through Nav_RollRandom_de when its timer runs out, steers at the target through Nav_SteerAtTarget_de and strafes left or right at 0.4 of its speed while Wheel_MeasureWheelClearance reports room to walk, stopping otherwise, then drives through Portal_DispatchActorBehavior; losing sight of the target or failing to re-route to the target's new node through Route_GetRouteRelation also returns it to roaming. */


void Nav_UpdateVisiblePursuit(Self *actor) {
    BrainNavUpdateVisiblePursuit *brain;
    s32 mine;
    Self *target;
    s32 node;
    f32 speed;
    s32 dir;
    s32 roll;
    s32 theirs;

    brain = actor->self->brain;
    Nav_RunBehaviorHandler(brain);
    if (brain->target == 0) {
        brain->target = 0;
        Scaled_SetBehaviourState(brain, 2);
        return;
    }
    if (!(brain->frames & 3)) {
        brain->visible = Scaled_HasLineOfSight(brain, brain->target);
    }
    brain->frames++;
    target = brain->target->self;
    mine = brain->player->flags & 0x3000;
    theirs = (target->flags & 0x3000) != 0;
    if (mine && !theirs) {
        Scaled_SetBehaviourState(brain, 12);
        return;
    }
    node = target->brain->route;
    if (brain->visible != 0) {
        if (Graphu64_GetSquaredDistance(&target->pos, &brain->player->pos) < 360000.0f) {
            brain->combat = 13;
            Scaled_SetBehaviourState(brain, 7);
            return;
        }
        speed = Scaled_ScaleCharacterSettingByDifficulty(brain) * 0.4f;
        if (--brain->timer <= 0) {
            brain->timer = Graphu64_NextRandom() % 4 + 12;
            brain->pattern = Graphu64_NextRandom() % 2;
            roll = Graphu64_NextRandom();
            if (roll / 2 * 2 == roll - 1) {
                brain->pattern = 2;
            }
        }
        Nav_SteerTowardPoint(brain, &target->pos, 2.0f, Scaled_UpdateDifficultyAimJitter(brain));
        if (brain->pattern == 0) {
            dir = Wheel_GetDirectionSector(brain->player->yaw - 3.1415927f - 1.5707964f);
            if (brain->player->slot % 2 == g_lightingBufferIndex) {
                Wheel_MeasureWheelClearance(brain->player, dir);
            }
            if (brain->clearance[dir] < 100.0f) {
                goto stop;
            }
            brain->player->strafe = -speed;
        } else if (brain->pattern == 1) {
            dir = Wheel_GetDirectionSector(brain->player->yaw - 3.1415927f + 1.5707964f);
            if (brain->player->slot % 2 == g_lightingBufferIndex) {
                Wheel_MeasureWheelClearance(brain->player, dir);
            }
            if (brain->clearance[dir] < 100.0f) {
            stop:
                brain->player->strafe = 0.0f;
                brain->pattern = 2;
            } else {
                brain->player->strafe = speed;
            }
        } else {
            brain->player->strafe = 0.0f;
        }
        brain->routeNodes[0] = -1;
        Portal_DispatchActorBehavior(brain);
    } else {
        brain->target = 0;
        Scaled_SetBehaviourState(brain, 2);
    }
    if (node != brain->node) {
        brain->node = node;
        if (Route_GetRouteRelation(g_navigationGraph, brain->route, node) == 0) {
            brain->target = 0;
            Scaled_SetBehaviourState(brain, 2);
        }
    }
}

/* 802106E0_14.CPP */
#if !(defined(VERSION_DE))
void Nav_InitPursuitStrafe(void *closeAttackActor) {
    CloseAttackActor *actor = closeAttackActor;
    CloseAttackActor *level1 = actor->self;
    CloseAttackBrain *inner = level1->brain;
    s32 r1, r2;

    inner->state = 0;
    Scaled_ResetBehaviorState(inner);

    r1 = Graphu64_NextRandom();
    inner->timer = r1 % 4 + 12;

    r2 = Graphu64_NextRandom();
    inner->pattern = r2 % 2;
}
#endif
