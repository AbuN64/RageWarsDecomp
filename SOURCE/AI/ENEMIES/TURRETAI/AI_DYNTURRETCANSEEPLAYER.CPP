#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/GAMEPLAY_REACTIONS.H"
#include "COMMON/WORLD.H"
#include "COMMON/LIBSN_AND_RESIDENT_CALLBACKS.H"
#include "COMMON/OBJ.H"
#include "COMMON/OBJRECAT30.H"
#include "AI/ENEMIES/TURRETAI.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"

extern s32 Rumble_TestActorStateBit(void *worldState, void *actorPointer);

extern void Turret_LinkEffect_MakeVisible(void *turretActor, void *effectActor, s32 unusedEvent);

extern void MatrixFromQuaternion(f32 *, f32 *);

extern void Graphu64_SubtractVectors(CVector3 *, CVector3 *, CVector3 *);

extern void Graphu64_TransformDirectionTranspose(f32 *, CVector3 *, CVector3 *);

extern void Graphu64_AddVec3(CVector3 *, CVector3 *, CVector3 *);

static inline void build_rotation(struct RotationObject *object, f32 *matrix) {
    CQuatern rotation;
    f32 angles[3];

    angles[0] = object->angleX;
    angles[1] = object->angleY;
    angles[2] = object->angleZ;
    rotation = CVector3_GetDirectionRotation2(angles);
    MatrixFromQuaternion(&rotation.x, matrix);
}

extern void RollMatrix(void *matrixStorage, f32 rollAngle);

/* Returns whether a player may act on a target: never on its own linked object or an inactive
   target, always when the team rule g_teamScoringEnabled is off, otherwise only across different teams. */





/* Tests whether a viewer can see a target: raises both positions by their heights scaled by one half and casts
   a ray between them through CCollision_SweepPoint into g_particleCollisionProbeResult, returning 1 when nothing or the target itself
   blocks it. */







extern Player **g_collisionCurrentActor;

extern char g_particleCollisionProbeResult[];

extern f32 Gobjinst_GetActorHeight(Player *);

extern s32 CCollision_SweepPoint(Player *, CVector3, CVector3, char *);

void Turret_LinkEffect_Activate(void *actor, WeaponFireState *state, s32 unusedArg) {
    if ((Rumble_TestActorStateBit(&g_world, actor) == 0) &&
        (state->variant == 0)) {
        Turret_LinkEffect_MakeVisible(actor, state, unusedArg);
        Actor_RequestActorState(actor, state, 1);
    }
}

void Turret_BuildPlaneOrient(void *unused0, struct RotationObject *object, f32 *out) {
    CQuatern orientation;
    f32 angles[3];

    angles[0] = object->angleX;
    angles[1] = object->angleY;
    angles[2] = object->angleZ;
    orientation = CVector3_GetDirectionRotation2(angles);
    MatrixFromQuaternion(&orientation.x, out);
}

void Turret_MoveTargetIntoTurretSpace(void *unused, struct RotationObject *object, CVector3 *pivot, CVector3 *point) {
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

int AI_DynTurretOpposingPlayer(TurretPlayerRelation *self, int unused, TurretPlayerRelation *target) {
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
    if (blocked != 0 && *g_collisionCurrentActor != other) {
        return 0;
    }
    return 1;
}
