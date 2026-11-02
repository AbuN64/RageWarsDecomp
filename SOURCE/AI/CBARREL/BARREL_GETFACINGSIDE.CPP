#include "include_asm.h"
#include "COMMON/WORLD.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/FIELD_VEC_B0.H"
#include "TYPES.H"
#include <ultra64.h>
#include "COMMON/PROBE.H"
#include "COMMON/MATH_HELPERS.H"
#include "ENGINE/INSTANCE/GOBJINST_GETACTOROFFSETPOSITIONANDMODEL.H"

/* 800C6E84_25.CPP */
/* ROM-grounded data: src/k_BarrelGetfacingsideOneWords_BarrelGetfacingside.c */
const float k_BarrelGetfacingsideOneWords[1] = {
    1.0f,
};
/* ROM-grounded data: src/k_BarrelGetfacingsideEncodedWords_BarrelGetfacingside.c */
const float k_BarrelGetfacingsideEncodedWords[1] = {
    1.5f,
};
/* ROM-grounded data: src/k_BarrelGetfacingsideEncodedWordsBlock1_BarrelGetfacingside.c */
const float k_BarrelGetfacingsideEncodedWordsBlock1[1] = {
    0.8f,
};

/* 80213ED4_4.CPP */
/* Picks an actor's target (the tracked enemy when the aim point is chosen, else the nearest permitted target from Cbarrel_SelectCombatTarget), classifies it into one of eight kinds, and fills the target record with the kind, target, height difference, position, direction and distance, both in full and flattened to the horizontal plane. */
extern void *Cbarrel_SelectCombatTarget(void *,void *,s32,s32), *Playerai_GetRouteCursorPoint(void *);
extern f32 Barrel_GetSignedAngleToPoint(void *,f32,f32,f32),Gu_Sqrtf(f32);
extern void Graphu64_SubtractVectors(CVector3 *, CVector3 *, CVector3 *);
static inline s32 Barrel_ClassifyAnchorTarget(BarrelAnchorActorView *self, Tracker *ctx, BarrelAnchorActorView *target) {
    if (ctx->active == 0) {
        return 6;
    }
    if (target == NULL) {
        if (ctx->slot != 0) {
            return 4;
        }
        return 3;
    }
    if (target == ctx->self) {
        return 2;
    }
    if (*target->kind == 5) {
        return 5;
    }
    if (target->id == 1615) {
        return 7;
    }
    if (g_world.visibilityEnabled == 0) {
        if ((target->flags100 & 0x300000) && target->controller->owner == self
            && target->controller->state == 2) {
            return 1;
        }
        if ((self->flags2E0 & 2) && self->id != 202) {
            return 1;
        }
    }
    return 0;
}
void Barrel_FillAnchorTargetInfo(BarrelAnchorActorView *actor, Tracker *tracker, s32 unused, CTargetInfo *targetInfo) {
    CVector3 pos;
    CVector3 delta;
    f32 height;
    s32 kind;
    BarrelAnchorActorView *target;
    Location *point;
    if ((tracker->team == g_world.kind1Cursor) && !(actor->kind[1] & 0x400) && (!(tracker->flags & 0x80000) || (tracker->lockedTarget != 0))) {
        tracker->anchor = Cbarrel_SelectCombatTarget(actor, tracker, 1, 0);
    }
    if ((*actor->kind == 1) && (tracker->mode == 11)
        && Barrel_ClassifyAnchorTarget(actor, tracker, tracker->target) == 4) {
        target = tracker->target;
        kind = 4;
    } else {
        target = tracker->anchor;
        kind = Barrel_ClassifyAnchorTarget(actor, tracker, target);
    }
    if (target != NULL) {
        pos = target->pos;
        height = Barrel_GetSignedAngleToPoint(actor, pos.x, pos.y, pos.z);
    } else {
        switch (kind) {
            case 4:
                point = Playerai_GetRouteCursorPoint(&tracker->slot);
                pos = point->pos;
                if (point->flags & 1) {
                    height = point->heading * 0.0174532942f - actor->heading;
                } else {
                    height = Barrel_GetSignedAngleToPoint(actor, pos.x, pos.y, pos.z);
                }
                break;
            case 3:
                pos = tracker->homePos;
                height = tracker->homeYaw - actor->heading;
                break;
            case 6:
                pos = actor->pos;
                height = 0.0f;
                break;
        }
    }
    Graphu64_WrapPeriodicValue(&height);
    Graphu64_SubtractVectors(&delta, &pos, &actor->pos);
    targetInfo->m_DeltaAngle = height;
    targetInfo->kind = kind;
    targetInfo->target = target;
    targetInfo->m_vTargetPos = pos;
    targetInfo->m_vDeltaTargetPos = delta;
    targetInfo->m_DistFrom = Gu_Sqrtf((delta.x * delta.x) + (delta.y * delta.y) + (delta.z * delta.z));
    delta.y = 0.0f;
    pos.y = 0;
    targetInfo->m_vXZTargetPos = pos;
    targetInfo->m_vXZDeltaTargetPos = delta;
    targetInfo->m_XZDistFrom = Gu_Sqrtf((delta.x * delta.x) + (delta.y * delta.y) + (delta.z * delta.z));
}

extern s32 g_currentActorInstance;
extern s32 Gobjinst_ProbeActorMovement(Actor_u1 *, CVector3, char **);

/* Aim toward a point; when obstructed, try progressively wider left/right
 * directions and choose the first clear probe. */
extern f32 Gobjinst_GetActorRadius(Actor_u1 *);
static inline f32 Weapons_ProbeHeading(Actor_u1 *actor, CVector3 point) {
    f32 dx;
    f32 dz;
    f32 dist;
    f32 s;
    f32 c;
    f32 dot;
    f32 angle;

    dx = point.x - actor->position.x;
    dz = point.z - actor->position.z;
    dist = Gu_Sqrtf(dx * dx + dz * dz);
    if (dist == 0.0f) {
        return 0.0f;
    }
    do {
        s = Gu_Sinf(actor->yaw);
    } while (0);
    c = -Math_Cosf(actor->yaw);
    dot = (dx * -s + dz * c) / dist;
    dot = ((RW_MIN(dot, 1.0f)) < (-1.0f) ? (-1.0f) : (RW_MIN(dot, 1.0f)));
    angle = Graphu64_ArcCos(dot);
    if (!(dx * c + dz * s > 0.0f)) {
        angle = -angle;
    }
    return angle;
}
f32 Barrel_FindClearAimAngle(Actor_u1 *actor, CVector3 point, s32 target, f32 distance) {
    CVector3 probe;
    char *hit;
    f32 heading = Weapons_ProbeHeading(actor, point);
    f32 cosine, sine, offset, angle, bias;
    s32 step, side, parity;
    if ((actor->flags & 0x200) && Gobjinst_ProbeActorMovement(actor, point, &hit)) {
        if (target != 0 && g_currentActorInstance == target) return heading;
        parity = ((u32)actor % 744U) & 1;
        probe.y = actor->position.y;
        for (step = 1; step < 6; step++) {
            offset = (f32)step * (RW_PI_F6 / 6.0f);
            for (side = 0; side < 2; side++) {
                angle = heading;
                if (side != parity) {
                    angle += offset;
                    bias = (RW_PI_F6 / 12.0f);
                } else {
                    angle -= offset;
                    bias = (-RW_PI_F6 / 12.0f);
                }
                cosine = Gu_Sinf(actor->yaw + 3.1415927f + angle);
                probe.x = actor->position.x + cosine * (distance * Gobjinst_GetActorRadius(actor));
                sine = Math_Cosf(actor->yaw + 3.1415927f + angle);
                probe.z = actor->position.z + sine * (distance * Gobjinst_GetActorRadius(actor));
                if (!Gobjinst_ProbeActorMovement(actor, probe, 0)) {
                    angle += bias;
                    Graphu64_WrapPeriodicValue(&angle);
                    return angle;
                }
            }
        }
    }
    return heading;
}

extern void Graphu64_NormalizeVec3(f32 *vectorComponents);
extern f32 Gobjinst_GetActorHeight(void *);

/* Barrel_GetSignedAngleToPoint's body: the signed angle between the actor's facing and the direction to the point. */
static inline f32 angleTo(BarrelAnchorActorView *actor, CVector3 point) {
    f32 dx;
    f32 dz;
    f32 dist;
    f32 s;
    f32 c;
    f32 dot;
    f32 angle;

    dx = point.x - actor->pos.x;
    dz = point.z - actor->pos.z;
    dist = Gu_Sqrtf(dx * dx + dz * dz);
    if (dist == 0.0f) {
        return 0.0f;
    }
    do {
        s = Gu_Sinf(actor->heading);
    } while (0);
    c = -Math_Cosf(actor->heading);
    dot = (dx * -s + dz * c) / dist;
    dot = ((RW_MIN(dot, 1.0f)) < ((-1.0f)) ? ((-1.0f)) : (RW_MIN(dot, 1.0f)));
    angle = Graphu64_ArcCos(dot);
    if (!(dx * c + dz * s > 0.0f)) {
        angle = -angle;
    }
    return angle;
}

#define ABS(x) ((x) < 0.0f ? -(x) : (x))

/* Whether the target faces the actor within a cone, and from which side. The target must be armed: a player with ammo
 * for its current weapon and the fire button held, an AI in anim type 0x10CC or later (kind 1) or in mode 0x3F
 * (kind 4). Targets 70 to 110 degrees off the actor's heading are skipped. The line from the actor (its height
 * clamped to the target's aim point) to the target is compared with the target's forward vector: 0 when the angle
 * between them is not under half the cone, else -1 or 1 for the side. */
s32 Barrel_GetFacingSide(BarrelAnchorActorView *self, void *unused, BarrelAnchorActorView *target, f32 cone) {
    CVector3 dir;
    CVector3 facing;
    CVector3 forward;
    CVector3 from;
    CVector3 to;
    struct Controller *controller;
    f32 low;
    f32 high;
    f32 angle;

    if (target == NULL) {
        return 0;
    }
    if (target->flags100 & 0x300000) {
        controller = target->controller;
        if (Player_HasAmmoForMode(controller, controller->currentWeapon) <= 0) {
            return 0;
        }
        if (!(controller->buttons & 0x2000)) {
            return 0;
        }
    } else {
        switch (*target->kind) {
        case 1:
            if (target->animType < 4300) {
                return 0;
            }
            break;
        case 4:
            if (target->aiMode != 63) {
                return 0;
            }
            break;
        default:
            return 0;
        }
    }
    low = self->pos.y + self->height;
    high = low + Gobjinst_GetActorHeight(self);
    to.x = target->pos.x;
    to.y = target->pos.y + target->height + Gobjinst_GetActorHeight(target) * 0.9f;
    to.z = target->pos.z;
    from.x = self->pos.x;
    from.z = self->pos.z;
    if (high < to.y) {
        from.y = high;
    } else if (to.y < low) {
        from.y = low;
    } else {
        from.y = to.y;
    }
    angle = ABS(angleTo(self, to));
    if (angle > 70.0f * RW_PI_F6 / 180.0f && angle < 110.0f * RW_PI_F6 / 180.0f) {
        return 0;
    }
    Graphu64_SubtractVectors(&dir, &from, &to);
    Graphu64_NormalizeVec3(&dir);
    forward.x = 0.0f;
    forward.y = 0.0f;
    forward.z = 1.0f;
    Gobjinst_TransformVectorByActorAim(&facing, target, forward);
    if (Graphu64_ArcCos(dir.x * facing.x + dir.y * facing.y + dir.z * facing.z) < cone * 0.5f) {
        if (dir.x * -facing.z + dir.z * facing.x < 0.0f) {
            return -1;
        }
        return 1;
    }
    return 0;
}
