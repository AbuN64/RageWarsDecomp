#include "Common/output.h"
#include "frontend_symbols.h"
#include "Ai/ai_functions.h"
#include "Common/libsn_and_resident_callbacks.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "Common/ballisticparams.h"
#include "Common/obj.h"
#include "Common/triple.h"
#include "types.h"
#include "Fx/normalize_vector.h"
#include "Ai/Enemies/turretai.h"
#include "include_asm.h"
#include "Game/builddirectionmatrix.h"
#include "Graphu64/graphu64_getangledistance.h"
#include "Graphu64/graphu64_packfixedmatrix.h"
#include "Particle/graphu64_matrixfromeulerxyz.h"
#include "Common/shared_gameslot.h"
#include "Libsn/nav_isballisticarcobstructed_data.h"
#include "Graphu64/graphu64_buildlookatmatrix.h"
#include "Engine/Unicol/unicol.h"
#include "Gobjinst/gameobject_getactorheight.h"
#include "Common/Lone/collision_current_actor.h"
#include "Common/runtime_declarations.h"
#include "Common/resident_event_handler.h"
#include "Common/approachlocation.h"
#include "Common/weapon_screen_message_operations.h"
#include "Common/level_actor.h"
#include "Common/world.h"
#include "Common/rec.h"
#include "Common/graphics_matrix_and_vector_math.h"
#include <platform_sdk.h>
#include "Weapons/actor_requestactorstate.h"
#include "Cbarrel/barrel_spawnflaggedeffects.h"
#include "Turretai/turret_tracktarget.h"
#include "Engine/rumble_setactorstatebit.h"
#include "Animpool/animpool_spawndescribedsceneeffect.h"
#include "Link/link_dispatchmatchingtriggers.h"
#include "Common/aiprofile.h"
#include "Common/gameplay_reactions.h"
#include "Common/breakable_hits.h"
#include "Ai/turret_setup_death.h"
#include "Common/vector.h"
#include "Ai/cbarrel.h"

/* Debug function records left in the retail image. */


static inline void alignment_from_rider(f32 *matrix, TurretRiderTargetView *rider) {
    CQuatern q;
    CVector3 aim;
    aim.x = rider->aim.x;
    aim.y = rider->aim.y;
    aim.z = rider->aim.z;
    q = CVector3_GetDirectionRotation2(&aim);
    MatrixFromQuaternion(&q.x, matrix);
}

CQuatern CVector3_GetDirectionRotation2(CVector3 *dir) {
    CQuatern q;
    CVector3 up;
    CVector3 axis;
    f32 angle;
    f32 turn;

    up = k_turretUpDirection;
    Graphu64_NormalizeVec3(dir);
    if (dir->y > k_turretVerticalAimUpperLimit) {
        q.x = q.y = q.z = 0.0f;
        q.w = k_turretIdentityQuaternionW;
    } else if (dir->y < k_turretVerticalAimLowerLimit) {
        angle = k_turretInvertedAimAngle;
        q.x = g_turretAimSine = Gu_Sinf(angle);
        q.y = 0.0f;
        q.z = 0.0f;
        q.w = Math_Cosf(angle);
    } else {
        turn = Graphu64_ArcCos(dir->x * up.x + dir->y * up.y + dir->z * up.z);
        Graphu64_CrossVectors(&axis, &up, dir);
        Graphu64_NormalizeVec3(&axis);
        angle = turn * k_turretTurnAngleScale;
        g_turretAimSine = Gu_Sinf(angle);
        q.x = axis.x * g_turretAimSine;
        q.y = axis.y * g_turretAimSine;
        q.z = axis.z * g_turretAimSine;
        q.w = Math_Cosf(angle);
    }
    return q;
}

void Turret_CalcOrientMtx(struct Owner *owner, TurretRiderTargetView *rider) {
    CQuatern rotation;
    CQuatern combined;
    f32 model[16];
    f32 alignment[16];
    CTurretIntelligence *segment;
    f32 angleScale;
    f32 angle;
    f32 sine;

    segment = &owner->navigationTrack->segment;
    alignment_from_rider(alignment, rider);
    if (segment->m_RotNode == -1) {
        angle = owner->heading;
        angleScale = k_turretQuaternionAngleScale;
        sine = Gu_Sinf(angle * angleScale);
        rotation.x = 0.0f;
        rotation.y = sine;
        g_turretAimSine = sine;
        rotation.z = 0.0f;
        rotation.w = Math_Cosf(owner->heading * angleScale);
    } else {
        g_turretAimSine = Gu_Sinf(rider->heading * k_turretHeadingSineScale);
    }
    rotation.x = 0.0f;
    rotation.z = 0.0f;
    rotation.y = g_turretAimSine;
    rotation.w = Math_Cosf(rider->heading * k_turretHeadingCosineScale);
    MultiplyQuaternions(&combined, &rotation, &owner->orientation);
    MatrixFromQuaternion(&combined, model);
    ScaleMatrixLocal(model, owner->scale.x, owner->scale.y, owner->scale.z);
    Graphu64_LimitVectorLength(&owner->position.x, 20000.0f);
    TranslateMatrix((char *)model, owner->position.x, owner->position.y, owner->position.z);
    Graphu64_MultiplyAffineMatrices(&owner->transform.right.x, alignment, model);
    SwapMatrixUpForward(&owner->transform);
}

const float k_turretaiFloatConstants[5] = {
    0.5f, 6.283186f, 0.5f, 0.01f,
    0.01f,
};

const float k_turretaiUnitAndNegativeQuarterTurn[2] = {
    1.0f, -1.5707965f,
};

struct Owner;

/* Moves a rider along its path segment: limits the throttle change by the segment's length over its radius, then
 * either rocks the throttle back and forth between 0 and 1 (mode 1, flipping direction at the ends) or steers it
 * toward a target's projected distance along the segment (mode 2), eases the change through
 * Graphu64_ApproachValue_TurretMove, clamps the throttle to 0..1 and places the rider at the segment's circle
 * point for that throttle through Graphu64_InterpolateVector. */




/* Picks a rider's nearest target: walks the player list g_transientPlayerList for players within the segment's
 * range (squared distance through Graphu64_GetSquaredDistance) that are not the rider's own player, are active
 * and, in team play (g_teamScoringEnabled), are on the other team, keeps those with a clear line of sight
 * between their raised centres through CCollision_SweepPoint (or whose blocker is the player itself), and
 * records the nearest in the rider and in the result with its distance through Gu_Sqrtf_TurretMove, clearing
 * both when none qualifies. */




void Turret_Move(struct Owner *owner, Rider *rider, s32 mode, SharedPlayer *target) {
    Segment *segment;
    f32 throttle;
    f32 limit;
    f32 step;
    f32 goal;
    CVector3 position;
    CVector3 offset;
    CVector3 local;
    f32 matrix[16];

    segment = (Segment *)(&((struct NavigationTrack *)owner->track)->segment);
    throttle = rider->throttle;
    if (segment->radius != 0.0f || segment->rise != 0.0f) {
        limit = segment->length / Gu_Sqrtf(segment->radius * segment->radius + segment->rise * segment->rise);
    } else {
        limit = 0.0f;
    }
    switch (mode) {
    case 0:
        break;
    case 1:
        step = limit;
        if (rider->direction == mode) {
            step = -step;
        }
        rider->change = Graphu64_ApproachValue(rider->change, step, 0.25f);
        throttle += rider->change;
        if (rider->direction == 0) {
            if (throttle > 1.0f) {
                rider->change = 0.0f;
                rider->direction = mode;
            }
        } else if (throttle < 0.0f) {
            rider->change = 0.0f;
            rider->direction = 0;
        }
        break;
    case 2:
        if (target != 0) {
            if (segment->angle != 0.0f) {
                Graphu64_SubtractVectors(&offset, &target->views0.view8_3.pos, &rider->base);
                BuildYawMatrix(matrix, -segment->angle);
                Graphu64_TransformPoint(matrix, &offset, &local);
                goal = local.z / segment->radius;
            } else {
                goal = 0.0f;
            }
            step = goal - throttle;
            if (step > limit) {
                step = limit;
            } else if (step < -limit) {
                step = -limit;
            }
            rider->change = Graphu64_ApproachValue(rider->change, step, 0.25f);
            throttle += rider->change;
        }
        break;
    }
    if (throttle > 1.0f) {
        throttle = 1.0f;
    } else if (throttle < 0.0f) {
        throttle = 0.0f;
    }
    rider->throttle = throttle;
    position = rider->base;
    position.x += segment->radius * Gu_Sinf(segment->angle);
    position.y += segment->rise;
    position.z += segment->radius * Math_Cosf(segment->angle);
    Graphu64_InterpolateVector(rider->frame, throttle, &rider->base, &position);
}

void AI_DynTurretGetTargetInfo(SharedPlayer *player, TurretRiderTargetView *rider, Result *result) {
    f32 nearest;
    SharedPlayer *best;
    CTurretIntelligence *segment;
    SharedPlayer *other;
    f32 distance;
    f32 lift;
    s32 enemy;
    s32 valid;
    s32 blocked;
    CVector3 from;
    CVector3 to;

    nearest = 0.0f;
    best = 0;
    segment = (CTurretIntelligence *)(&((struct NavigationTrack *)player->views18.view18_1.track)->segment);
    other = g_transientPlayerList.actorList;
    if (other != 0) {
        lift = (0.5f);
        do {
            distance = Graphu64_GetSquaredDistance(&player->views0.view8_3.pos, &other->views0.view8_3.pos);
            if (distance < segment->range * segment->range) {
                enemy = 0;
                if (player->views1C.view1D8_23.self != other && other->views5E4.view5E4_1.active != 0) {
                    enemy = 1;
                    if (g_gameSettings.counters.teams != 0) {
                        enemy = player->views1C.view1D8_23.self->views5D8.view5D8_1.record->team != other->views5D8.view5D8_1.record->team;
                    }
                }
                if (enemy) {
                    Graphu64_SubtractVectors(&to, &other->views0.view8_3.pos, &player->views0.view8_3.pos);
                    from.x = rider->aim.x;
                    from.y = rider->aim.y;
                    from.z = rider->aim.z;
                    from = player->views0.view8_3.pos;
                    from.y += Gobjinst_GetActorHeight(player) * lift;
                    to = other->views0.view8_3.pos;
                    to.y += Gobjinst_GetActorHeight(other) * lift;
                    blocked = CCollision_SweepPoint(player, from, to, g_particleCollisionProbeResult);
                    valid = 1;
                    if (blocked != 0) {
                        valid = g_collisionCurrentActor->instance0 == other;
                    }
                    if (valid && (best == 0 || distance < nearest)) {
                        best = other;
                        nearest = distance;
                    }
                }
            }
            other = other->views16E0.view16E0_1.next;
        } while (other != 0);
    }
    if (best != 0) {
        rider->target = best;
        result->distance = Gu_Sqrtf(nearest);
        result->target = best;
    } else {
        result->target = 0;
        rider->target = 0;
    }
}

typedef union NavRider { TurretRiderTargetView target; Rider rider; struct { char pad0[0x9C]; f32 heading; char padA0[0x124-0xA0]; f32 speed; char pad128[8];
    CVector3 aim; } nav; } NavRider;

/* Callers reserve a 136-byte result workspace shared by both target searches. */
static inline void navRotation(CQuatern *rotation, CVector3 *aim) {
    ((void (*)(CQuatern *, CVector3 *))CVector3_GetDirectionRotation2)(rotation, aim);
}
typedef union NavResult { Result result; struct { s32 kind; void *target; f32 projection; char padC[0x88-0xC]; } workspace;
    } NavResult;

static inline void navProject(f32 *matrix, CVector3 *local, CVector3 *out, CVector3 *to, CVector3 *from) {
    Graphu64_SubtractVectors(local, to, from);
    Graphu64_TransformDirectionTranspose(matrix, local, out);
}


typedef struct NavWork {
    NavResult result;
    NavVec origin, destination, relative;
    f32 matrix[16];
    NavVec local;
    CQuatern rotation;
    NavVec aim;
    f32 heading;
} NavWork;

/* Installs a weapon record's handler table and routine pointers and, when its owner's id is 0x40C,
   clears its counters and sets its rate to 200 and its range and speed from k_turretInitialRange and k_turretInitialSpeeds. */


/** Run the object's update hook, then advance its timer and fire the expiry action when due. */


struct Owner;

s32 Turret_TrackTarget(NavActor *actor, NavRider *riderState) {
    NavWork work;
    SharedPlayer *target;
    f32 heightScale;
    f32 maxTurn;
    f32 minTurn;
    f32 fireCone;
    f32 turnLimit;
    f32 turnedAimError;
    f32 aimError;
    f32 desiredSpeed;
    s32 inFireCone;
    u16 actorKind;
    CTurretIntelligence *turret;

    inFireCone = 0;
    turret = &actor->player.views18.navigationTrack->segment;
    work.heading = actor->player.views1C.view6C_4.heading - riderState->nav.heading;
    Graphu64_WrapPeriodicValue(&work.heading);
    actorKind = actor->player.views1C.viewE4_6.kind;
    switch (actorKind) {                              /* irregular */
    case 1035:
        Barrel_UpdateTrackGoals(&actor->actor, riderState, (struct BarrelTargetInfo *)&work.result.workspace, 0, 1);
        break;
    case 1036:
        AI_DynTurretGetTargetInfo(&actor->player, &riderState->target, &work.result.result);
        break;
    }
    target = riderState->target.target;
    if ((target != NULL) && (work.result.result.distance <= turret->m_SightRadius)) {
        heightScale = k_turretAimHeightScale;
        work.origin.v = actor->player.views0.view8_2.position;
        desiredSpeed = Gobjinst_GetActorHeight(&actor->player);
        work.origin.v.y += desiredSpeed*heightScale;
        work.destination.v = target->views0.view8_2.position;
        desiredSpeed = Gobjinst_GetActorHeight(target);
        work.destination.v.y += desiredSpeed*heightScale;
        work.aim.v.x = riderState->nav.aim.x;
        work.aim.v.y = riderState->nav.aim.y;
        work.aim.v.z = riderState->nav.aim.z;
        /* SN64 struct-return ABI writes directly to the caller-supplied CQuatern. */
        navRotation(&work.rotation, &work.aim.v);
        MatrixFromQuaternion(&work.rotation.x, work.matrix);
        navProject(work.matrix, &work.local.v, &work.destination.v, &work.destination.v, &work.origin.v);
        Graphu64_AddVec3(&work.destination.v, &work.destination.v, &work.origin.v);
        Graphu64_SubtractVectors(&work.relative.v, &work.destination.v, &work.origin.v);
        desiredSpeed = Graphu64_GetVerticalAngle(&work.relative.v.x);
        aimError = Barrel_GetSignedAngleToPoint(&actor->actor, work.destination.v);
        work.result.workspace.projection = aimError;
        if (work.result.result.distance <= turret->range) {
            fireCone = turret->m_FireAngle * heightScale;
            if (aimError < 0.0f) {
                if (!(-aimError < fireCone)) {

                } else {
                    goto block_12;
                }
            } else if (aimError < fireCone) {
block_12:
                inFireCone = 1;
            }
        }
        turnLimit = turret->limit;
        if (turnLimit < k_turretTurnLimitThreshold) {
            maxTurn = turnLimit * k_turretMaximumTurnScale;
            turnedAimError = work.heading + aimError;
            if (maxTurn < turnedAimError) {
                aimError = maxTurn - work.heading;
            } else {
                minTurn = -maxTurn;
                if (turnedAimError < minTurn) {
                    aimError = minTurn - work.heading;
                }
            }
        }
        Turret_Move(&actor->owner, &riderState->rider, turret->m_TargetVisibleMotionType, target);
    } else {
        desiredSpeed = 0.0f;

        aimError = -work.heading;
        Turret_Move(&actor->owner, &riderState->rider, turret->m_TargetNotVisibleMotionType, target);
    }

    if (aimError<0.0f) {
        if (k_turretNegativeAimTolerance < -aimError) goto changed;
    } else if (k_turretPositiveAimTolerance < aimError) goto changed;
    if (riderState->nav.speed != desiredSpeed) {
changed:
        Barrel_SetLoopingSound(actor, riderState, 3135);
    } else Barrel_StopActorLoopingSound(actor, riderState);
    /* The second ABI word is the actual rider pointer, used as such by this callee. */
    ((void (*)(void *, void *, f32, f32))Barrel_ApplyClampedTurn)(actor, riderState, turret->rate, aimError);
    riderState->nav.speed = Graphu64_ApproachValue(riderState->nav.speed, desiredSpeed, turret->rate);
    return inFireCone;
}

s32 Turret_BuildPlaneRot(s32 out, s32 actor, struct RotationObject *rotation) {
    f32 angles[3];
    angles[0] = rotation->angleX;
    angles[1] = rotation->angleY;
    angles[2] = rotation->angleZ;
    ((void (*)(s32, f32 *))CVector3_GetDirectionRotation2)(out, angles);
    return out;
}
void Turret_Construct(struct LevelActor *owner, struct TurretSetupState *record)
{
    record->table = g_turretDispatchTable;
    record->first = Turret_AdvanceRomEntry;
    record->second = Turret_DecreaseHealthRomEntry;
    record->third = Turret_CalcOrientMtxRomEntry;
    record->fourth = Turret_SpecialEffectsRomEntry;
    if (owner->type == 1036) {
        record->a = 0;
        record->b = 0;
        record->fourth = Turret_SpecialEffectsRomEntry;
        record->rate = 200;
        record->c = 0;
        record->range = k_turretInitialRange;
        record->speed = k_turretInitialSpeeds;
    }
}

void Turret_Setup(LevelActor *actor, struct TurretSetupState *turret) {
    s32 flags;
    ActorMotionDefinition *record;

    record = &((ActorMotionResource *)actor->definition)->motion;
    if (actor->type == 1036) {
        turret->speed = (&k_turretInitialSpeeds)[1];
    } else {
        turret->speed = 0.0f;
    }
    turret->setupResetWord = 0;
    turret->threshold = record->eventThreshold;

    if (Rumble_TestActorStateBit(&g_world, actor) == 0) {
        if (record->flags & 0x1000) {
            flags = actor->flags & ~0x2000;
            flags = flags & ~0x100;
            actor->flags = flags;
        }
        if (record->flags & 0x800) {
            actor->flags =
                actor->flags & ~0x100;
            Actor_RequestActorState(actor, turret, 0);
        } else {
            Actor_RequestActorState(actor, turret, 1);
        }
    } else {
        Actor_RequestActorState(actor, turret, 64);
    }
    turret->state = 0;
}

void Turret_Advance(char *actor, Obj *state) {
    if (state->hook != 0 && state->hook->fn != 0) {
        state->hook->fn(actor, state);
    }
    if (((struct LevelActor *)(actor))->type == 1036) {
        state->timer += g_frameElapsedTime;
        if (k_turretStateTimeout < state->timer || state->count <= 0) {
            Actor_RequestActorState(actor, state, 64);
        }
    }
}

/** Return the nested record's field, or a fallback constant when zero. */
int Turret_Anim_ACTIVATE(struct Owner *owner) {
    int activationAnimation = ((struct MenuRules *) owner->track)->locked;
    if (activationAnimation != 0) {
        return activationAnimation;
    }
    return 12100;
}

void Turret_Code_ACTIVATE(void *actor, struct WeaponEventSource *eventSource) {
    if (eventSource->eventEnabled != 0) {
        Actor_RequestActorState(actor, eventSource, 62);
    }
}

void Turret_Code_IDLE(void *actor, void *state) {
    if (Turret_TrackTarget(actor, state) != 0) {
        Actor_RequestActorState(actor, state, 63);
    }
}

void Turret_Code_FIRE(void *actor, void *state) {
    if (Turret_TrackTarget(actor, state) == 0) {
        Actor_RequestActorState(actor, state, 62);
    }
}

void Turret_Setup_DEATH(void *actor, void *state) {
    LevelActor *actorView = actor;
    ActorMotionState *stateView = state;
    ActorMotionDefinition *motion;
    s32 clearedFlags;
    Shared_World *world;

    motion = &((ActorMotionResource *)actorView->definition)->motion;
    Barrel_SpawnFlaggedEffects(actor, state, 4, motion->eventMask, motion->secondaryEventMask);
    world = &g_world;
    stateView->event = 0;
    Rumble_SetActorStateBit(world, actor, 1);
    Link_DispatchActorLinks(actor, 1, actor);
    clearedFlags = actorView->flags & 0xFFFEFFFF;
    actorView->flags = clearedFlags;
    if (world->mode != 4) {
        actorView->flags = clearedFlags | 0x08000000;
    }
}

void Turret_Code_DEATH(LevelActor *actor, ActorMotionState *state) {
    if ((state->actionPending != 0) && (actor->flags & 0x80000)) {
        Animpool_ReleaseSceneEffect(actor);
    }
}

void Turret_LinkEffect_MakeVisible(Shared_Actor *actor, void *effectActor, s32 unusedEvent) {
    if (Rumble_TestActorStateBit(&g_world, actor) == 0) {
        actor->weaponFlags |= 0x2100;
    }
}

static inline void build_rotation(struct RotationObject *object, f32 *matrix) {
    CQuatern rotation;
    CVector3 angles;

    angles.x = object->angleX;
    angles.y = object->angleY;
    angles.z = object->angleZ;
    rotation = CVector3_GetDirectionRotation2(&angles);
    MatrixFromQuaternion(&rotation.x, matrix);
}


/* Returns whether a player may act on a target: never on its own linked object or an inactive
   target, always when the team rule g_teamScoringEnabled is off, otherwise only across different teams. */


/* Tests whether a viewer can see a target: raises both positions by their heights scaled by one half and casts
   a ray between them through CCollision_SweepPoint into g_particleCollisionProbeResult, returning 1 when nothing or the target itself
   blocks it. */




void Turret_LinkEffect_Activate(void *actor, WeaponFireState *state, s32 unusedArg) {
    if ((Rumble_TestActorStateBit(&g_world, actor) == 0) &&
        (state->variant == 0)) {
        Turret_LinkEffect_MakeVisible(actor, state, unusedArg);
        Actor_RequestActorState(actor, state, 1);
    }
}

void Turret_BuildPlaneOrient(void *ownerActor, struct RotationObject *object, f32 *out) {
    CQuatern orientation;
    CVector3 angles;

    angles.x = object->angleX;
    angles.y = object->angleY;
    angles.z = object->angleZ;
    orientation = CVector3_GetDirectionRotation2(&angles);
    MatrixFromQuaternion(&orientation.x, out);
}

void Turret_MoveTargetIntoTurretSpace(void *ownerActor, struct RotationObject *object, CVector3 *pivot, CVector3 *point) {
    f32 matrix[16];
    CVector3 offset;

    build_rotation(object, matrix);
    Graphu64_SubtractVectors(&offset, point, pivot);
    Graphu64_TransformDirectionTranspose(matrix, &offset, point);
    Graphu64_AddVec3(point, point, pivot);
}

void Turret_SpecialEffects(void *actor, ActorEffectEventView *event) {
    TurretAimOwnerView *eventOwner;
    CTurretIntelligence *turretInfo;
    TurretAimOwnerView *headingOwner;

    struct NavigationTrack *track;

    eventOwner = event->actor;
    track = (void *)eventOwner->definition;
    turretInfo = &track->segment;
    if (event->eventIndex == turretInfo->m_GunNode) {
        PitchMatrix(actor, eventOwner->pitch);
    }
    if (event->eventIndex == turretInfo->m_RotNode) {
        headingOwner = event->actor;
        RollMatrix(actor,
                      headingOwner->targetHeading -
                          headingOwner->heading);
    }
}

void Turret_DecreaseHealth(void *actor, Dest *state, CDamageInfo *damage) {
    s32 health;

    health = state->health - damage->m_Hits;
    if (health < 0) {
        health = 0;
    }
    state->health = health;
    if (health == 0) {
        Actor_RequestActorState(actor, state, 64);
    }
}

int AI_DynTurretOpposingPlayer(TurretPlayerRelation *self, int trackerState, TurretPlayerRelation *target) {
    TurretPlayerRelation *linked = self->linked;
    if (linked == target || target->active == 0) {
        return 0;
    }
    if (g_gameSettings.counters.teams != 0) { if (linked->info->team == target->info->team) { return 0; } } return 1;
}

s32 AI_DynTurretCanSeePlayer(Player *player, TurretTargetVisibilityView *rider, Player *other) {
    CVector3 from;
    CVector3 to;
    f32 lift;
    s32 blocked;

    Graphu64_SubtractVectors(&to, &other->pos, &player->pos);
    lift = 0.5f;
    from.x = rider->aim.x;
    from.y = rider->aim.y;
    from.z = rider->aim.z;
    from = player->pos;
    from.y += Gobjinst_GetActorHeight(player) * lift;
    to = other->pos;
    to.y += Gobjinst_GetActorHeight(other) * lift;
    blocked = CCollision_SweepPoint(player, from, to, g_particleCollisionProbeResult);
    if (blocked != 0 && g_collisionCurrentActor->instance0 != other) {
        return 0;
    }
    return 1;
}

#if defined(VERSION_DE)
/* two stale words ahead of the up vector (0, 0.99999f): linker fill, read by nothing */
unsigned int g_turretUpDirectionLinkerFill[2] = {
    0x00000000, 0x3F7FFF58,
};
/* 800C19F0: world up, copied to the stack by CVector3_GetDirectionRotation2 (lw x3) */
CVector3 k_turretUpDirection = { 0.0f, 1.0f, 0.0f };
#endif

const float k_directionRotationFloats[8] = {
    0.99999f, 1.0f, -0.99999f, 1.5707965f,
    0.5f, 0.5f, 0.5f, 0.5f,
};

const float k_turretaiNegativeQuarterTurn[1] = {
    -1.5707965f,
};

const float k_turretAdvanceDataFloatConstants[1] = {
    675.0f,
};

#if defined(VERSION_US)
/* two stale words ahead of the up vector ('RGBR', 0): linker fill, read by nothing */
/* world up, copied to the stack by CVector3_GetDirectionRotation2 */
#endif

#if defined(VERSION_EU)
/* two stale opcode words (lw v0,12(s0); lui a2,0x500) ahead of the up vector: linker fill, read by nothing */
/* world up, copied to the stack by CVector3_GetDirectionRotation2 */
#endif

#if defined(VERSION_DE) || defined(VERSION_EU_X)
#if defined(VERSION_DE)
/* Two unread padding words between the aim jitter table and the behaviour literals; nothing reads them. */
unsigned int g_difficultyAimJitterLinkerFill[2] = {
    0x00209EF4, 0x00209EF4,
};
#endif
#if defined(VERSION_EU_X)
/* two stale words (8.0f, 23.0f as bit patterns) ahead of the up vector: linker fill, read by nothing */
/* world up, copied to the stack by CVector3_GetDirectionRotation2 */
#endif
#endif

#if defined(VERSION_US)
/* two stale words ahead of the up vector ('RGBR', 0): linker fill, read by nothing */
const unsigned int g_turretUpDirectionLinkerFill[2] = {
    0x52474252, 0x00000000,
};
/* world up, copied to the stack by CVector3_GetDirectionRotation2 */
const CVector3 k_turretUpDirection = { 0.0f, 1.0f, 0.0f };
#endif

#if defined(VERSION_EU)
/* two stale opcode words (lw v0,12(s0); lui a2,0x500) ahead of the up vector: linker fill, read by nothing */
const unsigned int g_turretUpDirectionLinkerFill[2] = {
    0x8E02000C, 0x3C060500,
};
/* world up, copied to the stack by CVector3_GetDirectionRotation2 */
const CVector3 k_turretUpDirection = { 0.0f, 1.0f, 0.0f };
#endif

#if defined(VERSION_DE) || defined(VERSION_EU_X)
#if defined(VERSION_DE)
/* Two unread padding words between the aim jitter table and the behaviour literals; nothing reads them. */
#endif
#if defined(VERSION_EU_X)
/* two stale words (8.0f, 23.0f as bit patterns) ahead of the up vector: linker fill, read by nothing */
unsigned int g_turretUpDirectionLinkerFill[2] = {
    0x41000000, 0x41B80000,
};
/* world up, copied to the stack by CVector3_GetDirectionRotation2 */
CVector3 k_turretUpDirection = { 0.0f, 1.0f, 0.0f };
#endif
#endif
