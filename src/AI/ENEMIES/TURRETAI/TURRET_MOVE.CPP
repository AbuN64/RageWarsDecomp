#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/OBJ.H"
#include "GAME/BUILDDIRECTIONMATRIX.H"
#include "particle/GRAPHU64_MATRIXFROMEULERXYZ.H"

typedef struct Owner Owner;

/* Moves a rider along its path segment: limits the throttle change by the segment's length over its radius, then either rocks the throttle back and forth between 0 and 1 (mode 1, flipping direction at the ends) or steers it toward a target's projected distance along the segment (mode 2), eases the change through Graphu64_ApproachValue_TurretMove, clamps the throttle to 0..1 and places the rider at the segment's circle point for that throttle through Graphu64_InterpolateVector. */








extern f32 Gu_Sqrtf(f32);

extern f32 Graphu64_ApproachValue(f32, f32, f32);


extern void Graphu64_InterpolateVector(CVector3 *, f32, CVector3 *, CVector3 *);

/* Picks a rider's nearest target: walks the player list g_transientPlayerList for players within the segment's range at 0x54 (squared distance through Graphu64_GetSquaredDistance) that are not the rider's own player, are active and, in team play (g_teamScoringEnabled), are on the other team, keeps those with a clear line of sight between their raised centres through CCollision_SweepPoint (or whose blocker is the player itself), and records the nearest in the rider at 0x80 and in the result with its distance through Gu_Sqrtf_TurretMove, clearing both when none qualifies. */









extern SharedPlayer *g_transientPlayerList;

extern SharedPlayer **g_collisionCurrentActor;

extern char g_particleCollisionProbeResult[];

extern f32 Graphu64_GetSquaredDistance(CVector3 *, CVector3 *);

extern f32 Gobjinst_GetActorHeight(SharedPlayer *);

extern s32 CCollision_SweepPoint(SharedPlayer *, CVector3, CVector3, char *);

extern void Graphu64_SubtractVectors(CVector3 *, CVector3 *, CVector3 *);
void Turret_Move(Owner *owner, Rider *rider, s32 mode, SharedPlayer *target) {
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
    other = g_transientPlayerList;
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
                        valid = *g_collisionCurrentActor == other;
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
