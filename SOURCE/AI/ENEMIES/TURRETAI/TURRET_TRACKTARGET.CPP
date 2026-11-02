#include "COMMON/LIBSN_AND_RESIDENT_CALLBACKS.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "COMMON/APPROACHLOCATION.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/BALLISTICPARAMS.H"
#include "COMMON/LEVEL_ACTOR.H"
#include "COMMON/WORLD.H"
#include "COMMON/OBJ.H"
#include "COMMON/REC.H"
#include "COMMON/GRAPHICS_MATRIX_AND_VECTOR_MATH.H"
#include "COMMON/TRIPLE.H"
#include <ultra64.h>
#include "TYPES.H"
#include "AI/ENEMIES/TURRETAI.H"
#include "WEAPONS/ACTOR_REQUESTACTORSTATE.H"

void AI_DynTurretGetTargetInfo(SharedPlayer *player, TurretRiderTargetView *rider, Result *result);

void Graphu64_TransformDirectionTranspose(void *matrix, void *inputVector, void *outputVector);

void Turret_Move(struct Owner *owner, Rider *rider, s32 mode, SharedPlayer *target);

void Barrel_SetLoopingSound(void *actor, void *stateController, s32 sixth);

void Barrel_StopActorLoopingSound(void *actor, void *soundState);

f32 Graphu64_ApproachValue(f32 current, f32 target, f32 rate);

typedef union NavRider { TurretRiderTargetView target; Rider rider; struct { char pad0[0x9C]; f32 heading; char padA0[0x124-0xA0]; f32 speed; char pad128[8]; CVector3 aim; } nav; } NavRider;

/* Callers reserve a 136-byte result workspace shared by both target searches. */
static inline void navRotation(CQuatern *q,CVector3 *aim) {
    ((void (*)(CQuatern *,CVector3 *))CVector3_GetDirectionRotation2)(q,aim); }
typedef union NavResult { Result result; BarrelTargetInfo output; struct { s32 kind; void *target; f32 projection; char padC[0x88-0xC]; } workspace; } NavResult;

static inline void navProject(f32 *matrix,CVector3 *local,CVector3 *out,CVector3 *to,CVector3 *from) { Graphu64_SubtractVectors(local,to,from); Graphu64_TransformDirectionTranspose(matrix,local,out); }


typedef struct NavWork {
    NavResult result;
    NavVec origin,destination,relative;
    f32 matrix[16];
    NavVec local;
    CQuatern rotation;
    NavVec aim;
    f32 heading;
} NavWork;

/* Installs a weapon record's handler table and routine pointers and, when its owner's id is 0x40C,
   clears its counters and sets its rate to 200 and its range and speed from k_turretInitialRange and k_turretInitialSpeeds. */










extern s32 Rumble_TestActorStateBit(void *, void *);

/** Run the object's update hook, then advance its timer and fire the expiry action when due. */



typedef struct Owner Owner;

s32 Turret_TrackTarget(NavActor *actor,NavRider *riderState) {
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
        Barrel_UpdateTrackGoals(&actor->input, riderState, &work.result.output, 0, 1);
        break;
    case 1036:
        AI_DynTurretGetTargetInfo(&actor->player,&riderState->target,&work.result.result);
        break;
    }
    target = riderState->target.target;
    if ((target != NULL) && (work.result.result.distance <= turret->m_SightRadius)) {
        heightScale = k_turretAimHeightScale;
        work.origin.v=actor->player.views0.view8_2.position;
        desiredSpeed=Gobjinst_GetActorHeight(&actor->player);
        work.origin.v.y+=desiredSpeed*heightScale;
        work.destination.v=target->views0.view8_2.position;
        desiredSpeed=Gobjinst_GetActorHeight(target);
        work.destination.v.y+=desiredSpeed*heightScale;
        work.aim.v.x = riderState->nav.aim.x;
        work.aim.v.y = riderState->nav.aim.y;
        work.aim.v.z = riderState->nav.aim.z;
        /* SN64 struct-return ABI writes directly to the caller-supplied CQuatern. */
        navRotation(&work.rotation,&work.aim.v);
        MatrixFromQuaternion(&work.rotation.x,work.matrix);
        navProject(work.matrix,&work.local.v,&work.destination.v,&work.destination.v,&work.origin.v);
        Graphu64_AddVec3(&work.destination.v, &work.destination.v, &work.origin.v);
        Graphu64_SubtractVectors(&work.relative.v, &work.destination.v, &work.origin.v);
        desiredSpeed = Graphu64_GetVerticalAngle(&work.relative.v.x);
        aimError = Barrel_GetSignedAngleToPoint(&actor->actor,work.destination.v);
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
        Turret_Move(&actor->owner,&riderState->rider,turret->m_TargetVisibleMotionType,target);
    } else {
        desiredSpeed = 0.0f;

        aimError = -work.heading;
        Turret_Move(&actor->owner,&riderState->rider,turret->m_TargetNotVisibleMotionType,target);
    }

    if(aimError<0.0f) {
        if(k_turretNegativeAimTolerance < -aimError) goto changed;
    } else if(k_turretPositiveAimTolerance < aimError) goto changed;
    if(riderState->nav.speed != desiredSpeed) {
changed:
        Barrel_SetLoopingSound(actor,riderState,3135);
    } else Barrel_StopActorLoopingSound(actor,riderState);
    /* The second ABI word is the actual rider pointer, used as such by this callee. */
    ((void (*)(void *,void *,f32,f32))Barrel_ApplyClampedTurn)(actor,riderState, turret->rate, aimError);
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
void Turret_Construct(struct ItemMenuSelectionView *owner, struct TurretSetupState *record)
{
    record->table = g_turretDispatchTable;
    record->first = Turret_AdvanceRomEntry;
    record->second = Turret_DecreaseHealthRomEntry;
    record->third = Turret_CalcOrientMtxRomEntry;
    record->fourth = Turret_SpecialEffectsRomEntry;
    if (owner->id == 1036) {
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
    turret->pad128 = 0;
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
    if (((struct ItemMenuSelectionView *)(actor))->id == 1036) {
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

void Turret_Code_ACTIVATE(void *a, struct WeaponEventSource *b) {
    if (b->eventEnabled != 0) {
        Actor_RequestActorState(a, b, 62);
    }
}
