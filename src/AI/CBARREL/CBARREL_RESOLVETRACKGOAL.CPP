#include "RSP/RANDOM_DIRECTION_AND_AFFINE_MATH.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/WORLD.H"
#include "COMMON/FIELD_VEC_B0.H"
#include "TYPES.H"
#include "COMMON/MATH_HELPERS.H"
#include "AI/CBARREL.H"
#include "FX/GRAPHU64_NORMALIZEVEC3.H"

extern s32 Cbarrel_UpdateTrackerAim(BarrelAnchorActorView *actor, Tracker *tracker, BarrelAnchorActorView *target);
extern BarrelAnchorActorView *Cbarrel_SelectCombatTarget(BarrelAnchorActorView *actor, Tracker *tracker, s32 lineOfSight, s32 combat);
extern f32 Barrel_FindClearAimAngle(BarrelAnchorActorView *actor, CVector3 pos, BarrelAnchorActorView *target, f32 distance);
extern f32 Barrel_GetSignedAngleToPoint(void *actor, struct CVector3_t point);
struct Cursor;
extern Location *Playerai_GetRouteCursorPoint(struct Cursor *slot);
extern f32 Gobjinst_GetActorHeight(BarrelAnchorActorView *actor);
extern f32 Gobjinst_GetActorRadius(BarrelAnchorActorView *actor);
extern f32 InstHdr_GetActorReach(BarrelAnchorActorView *object);
extern void InstHdr_CopyActorPositionAndModel(BarrelAnchorActorView *levelActor, CVector3 pos, CVector3 *outPos, s32 *outRoom, s32 unused6, s32 unused7);
extern f32 InstHdr_GetModelRecordValue20(BarrelAnchorActorView *object);
extern f32 Graphu64_GetHorizontalAngle(CVector3 *direction);
extern void Graphu64_AddVec3(CVector3 *result, CVector3 *left, CVector3 *right);
extern void Graphu64_SubtractVectors(CVector3 *result, CVector3 *left, CVector3 *right);
extern void Graphu64_ScaleVector(CVector3 *result, CVector3 *vec, f32 scale);


/* Places the goal beside kind-7 targets: pushed away from the anchor by both extents. */
static inline void Weapons_PlaceGoalBeside(BarrelAnchorActorView *actor, BarrelAnchorActorView *target, BarrelAnchorActorView *anchor, CVector3 *outPos, s32 *outRoom) {
    CVector3 dir;
    CVector3 goal;
    if (anchor != 0) {
        Graphu64_SubtractVectors(&dir, &target->pos, &anchor->pos);
        dir.y = 0.0f;
        Graphu64_NormalizeVec3(&dir);
    } else {
        dir.x = 0.0f;
        dir.y = 0.0f;
        dir.z = 0.0f;
    }
    Graphu64_ScaleVector(&dir, &dir, Gobjinst_GetActorRadius(target) + Gobjinst_GetActorRadius(actor) + g_goalBesideActorClearance);
    Graphu64_AddVec3(&goal, &target->pos, &dir);
    InstHdr_CopyActorPositionAndModel(target, goal, outPos, outRoom, 0, 0);
}
/** Picks what the tracker aims at (its target, itself, a slot or home point, or the actor) and
    fills out with the kind, target, reach, goal position and its offset from the actor, both in 3D
    and flattened to the ground plane. The third parameter is overwritten: it serves as the boost flag. */
void Cbarrel_ResolveTrackGoal(BarrelAnchorActorView *actor, Tracker *tracker, s32 boost, CTargetInfo *out) {
    CVector3 pos;
    CVector3 probe;
    CVector3 away;
    CVector3 delta;
    s32 room;
    BarrelAnchorActorView *target;
    s32 kind;
    s32 mode;
    f32 range;
    f32 gap;
    f32 angle;
    f32 reach;
    Location *loc;
    boost = 0; /* the shared tracker-callback slot (unused, as in Barrel_FillAnchorTargetInfo) holds the boost flag */
    if (*actor->kind != 1) {
        mode = -1;
    }
    if (tracker->team == g_world.kind1Cursor) {
        if ((tracker->flags & 0x40000) && tracker->lockedTarget == 0) {
            if (Cbarrel_UpdateTrackerAim(actor, tracker, tracker->target) == 0) {
                tracker->flags &= ~0x40000;
            }
        } else {
            tracker->target = Cbarrel_SelectCombatTarget(actor, tracker, 0, 1);
        }
    }
    target = tracker->target;
    kind = 6;
    if (tracker->active != 0) {
        if (target == 0) {
            kind = 3;
            if (tracker->slot != 0) {
                kind = 4;
            }
        } else if (target == tracker->self) {
            kind = 2;
        } else if (*target->kind == 5) {
            kind = 5;
        } else if (target->id == 1615) {
            kind = 7;
        } else if (g_world.visibilityEnabled != 0) {
            kind = 0;
        } else if (((target->flags100 & 0x300000) && target->controller->owner == actor &&
                    target->controller->state == 2) ||
                   ((actor->flags2E0 & 2) && actor->id != 202)) {
            kind = 1;
        } else {
            kind = 0;
        }
    }
    if (target != 0) {
        if (kind == 7) {
            Weapons_PlaceGoalBeside(actor, target, tracker->anchor, &pos, &room);
        } else {
            pos = target->pos;
            room = target->room;
            if (mode == 1) {
                pos.y += target->height + Gobjinst_GetActorHeight(target) * g_trackGoalTargetHeightFactor;
            }
        }
        gap = Gobjinst_GetActorRadius(target) + Gobjinst_GetActorRadius(actor);
        switch (kind) {
            case 2:
                gap += k_barrelKindTwoApproachPadding;
            default:
                boost = 1;
                break;
            case 5:
            case 7:
                boost = 1;
                gap = 0.0f;
                break;
        }
    } else {
        gap = Gobjinst_GetActorRadius(actor);
        switch (kind) {
            case 4:
                loc = Playerai_GetRouteCursorPoint(&tracker->slot);
                pos = loc->pos;
                gap = 0.0f;
                room = loc->room;
                if (tracker->slot == 2 || tracker->slot == kind) {
                    boost = 1;
                }
                break;
            case 3:
                pos = tracker->homePos;
                room = tracker->homeRoom;
                boost = 1;
                break;
            case 6:
                pos = actor->pos;
                room = actor->room;
                if (mode == 2) {
                    pos.y = InstHdr_GetModelRecordValue20(actor);
                }
                break;
        }
    }
    Graphu64_AddVec3(&pos, &pos, &tracker->offset);
    if (gap > 0.0f) {
        Graphu64_SubtractVectors(&away, &actor->pos, &pos);
        angle = Graphu64_GetHorizontalAngle(&away);
        pos.x -= gap * Gu_Sinf(angle);
        pos.z -= gap * Math_Cosf(angle);
    }
    if (mode == 2) {
        pos.y = RW_MIN_LT(pos.y, InstHdr_GetModelRecordValue20(actor));
    }
    if (boost) {
        reach = InstHdr_GetActorReach(actor);
        probe.x = actor->pos.x + reach * Gu_Sinf(tracker->angle);
        probe.y = tracker->height;
        probe.z = actor->pos.z + reach * Math_Cosf(tracker->angle);
        range = Barrel_FindClearAimAngle(actor, probe, target, k_barrelClearAimSearchRange);
        pos.y = tracker->height;
    } else {
        range = Barrel_GetSignedAngleToPoint(actor, pos);
    }
    Graphu64_SubtractVectors(&delta, &pos, &actor->pos);
    out->kind = kind;
    out->target = target;
    out->m_DeltaAngle = range;
    out->m_vTargetPos = pos;
    out->m_vDeltaTargetPos = delta;
    out->m_DistFrom = Gu_Sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
    delta.y = 0.0f;
    pos.y = 0.0f;
    out->m_vXZTargetPos = pos;
    out->m_vXZDeltaTargetPos = delta;
    out->m_XZDistFrom = Gu_Sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
}
