#include "include_asm.h"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/SELF.H"
#include "COMMON/MOTION_STEP.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/SHAREDCALLBACK5.H"
#include "TYPES.H"
#include "AI/NAV/WHEEL.H"

/* Probes one of a vehicle's eight wheel rays: casts from the vehicle position to its scaled wheel offset
 * through Unicol_SweepActorMotion and stores the wheel's reach as the XZ distance to whatever was hit (diagonals
 * scaled by 1/sqrt 2, components tested against the zeroed y), or the full ray length on a miss. */
extern CVector3 g_actorRadialDirections[8];
extern SweepHit *g_collisionCurrentActor;
extern CCollisionInfo2_t g_particleCollisionProbeResult;
extern f32 InstHdr_GetActorReach(Player *);
extern f32 Gobjinst_GetActorRadius(Player *);
extern f32 Gobjinst_GetActorHeight(Player *);
extern f32 InstHdr_GetActorBaseOffset(void *);
extern s32 Unicol_SweepActorMotion(Player *, CVector3, CVector3, CCollisionInfo2_t *, f32, f32, f32, f32);
void Wheel_MeasureWheelReach(Player *player, s32 wheel) {
    CVector3 from;
    CVector3 to;
    CVector3 delta;
    f32 a;
    f32 b;
    f32 c;
    from = player->pos;
    to = g_actorRadialDirections[wheel];
    to.x *= player->controller->length;
    to.y *= player->controller->length;
    to.z *= player->controller->length;
    to.x += from.x;
    to.y += from.y;
    to.z += from.z;
    from.y += 61.44f;
    a = InstHdr_GetActorReach(player);
    b = Gobjinst_GetActorRadius(player);
    c = Gobjinst_GetActorHeight(player);
    if (Unicol_SweepActorMotion(player, from, to, &g_particleCollisionProbeResult, a, b, c, InstHdr_GetActorBaseOffset(player))) {
        delta = g_collisionCurrentActor->pos;
        delta.x -= from.x;
        delta.y = 0.0f;
        delta.z -= from.z;
        if (delta.x != delta.y) {
            if (delta.z == delta.y) {
                player->controller->reach[wheel] = ((delta.x) < (delta.y) ? -(delta.x) : (delta.x));
            } else {
                player->controller->reach[wheel] = (((delta.x) < (delta.y) ? -(delta.x) : (delta.x)) + ((delta.z) < (delta.y) ? -(delta.z) : (delta.z))) * 0.70710677f;
            }
        } else if (delta.z != delta.y) {
            player->controller->reach[wheel] = ((delta.z) < (delta.y) ? -(delta.z) : (delta.z));
        }
    } else {
        player->controller->reach[wheel] = player->controller->length;
    }
}

/* Stores the clearance reached before step I: (I - 1) x REACH, never below 0. */
static inline void storeClearance(Player *player, s32 wheel, s32 i, f32 reach) {
    player->controller->clearance[wheel] = (i - 1 >= 0 ? i - 1 : 0) * reach;
}
/* Walks wheel ray WHEEL outward from the vehicle in steps of 2.25 x its reach, probing the ground under
 * each step (Unicol_SweepActorMotion), and stores in the clearance table the distance covered before a probe
 * misses, lands on a kind 5/6 surface or drops more than 100; it stays 100 when the ray is shorter
 * than the reach. */
void Wheel_MeasureWheelClearance(Player *player, s32 wheel) {
    CVector3 position;
    CVector3 below;
    CVector3 step;
    CCollisionInfo2_t surface;
    f32 reach;
    f32 length;
    f32 radius;
    f32 height;
    f32 base;
    s32 steps;
    s32 i;
    player->controller->clearance[wheel] = 100.0f;
    reach = InstHdr_GetActorReach(player);
    length = player->controller->clearance[wheel];
    if (length < reach) {
        return;
    }
    step = g_actorRadialDirections[wheel];
    steps = length / (reach * 2.25f) + 0.5f;
    step.x = step.x * 2.25f * reach;
    step.z = step.z * 2.25f * reach;
    i = 0;
    radius = Gobjinst_GetActorRadius(player);
    height = Gobjinst_GetActorHeight(player);
    base = InstHdr_GetActorBaseOffset(player);
    position = player->pos;
    surface.dwFlags = 0xC008;
    surface.InstanceBehavior = 1;
    surface.WallBehavior = 1;
    surface.GroundBehavior = 1;
    surface.GravityAcceleration = 0.0f;
    surface.BounceReturnEnergy = 0.0f;
    surface.GroundFriction = 0.0f;
    surface.AirFriction = 0.0f;
    surface.WaterFriction = 0.0f;
    position.y += 2.5f * 61.44f;
    for (; i < steps; i++) {
        position.x += step.x;
        position.z += step.z;
        below = position;
        below.y -= 5 * 61.44f;
        if (!Unicol_SweepActorMotion(player, position, below, &surface, reach, radius, height, base)) {
            storeClearance(player, wheel, i, reach);
            return;
        }
        if (g_collisionCurrentActor->kind == 5 || g_collisionCurrentActor->kind == 6) {
            storeClearance(player, wheel, i, reach);
            return;
        }
        if (g_collisionCurrentActor->pos.y <= below.y - 100.0f) {
            storeClearance(player, wheel, i, reach);
            return;
        }
    }
}

extern CVector3 *Scaled_GetControllerPosition(AiController *controller);
/* Builds the eight radial probe segments around the player at two heights (reach at 180, clearance at
 * 140) from its position through Scaled_GetControllerPosition, after turning its heading into a sector in [0, 8].
 * The segments stay on the stack: the debug draw that used them (and the sector) is compiled out. */
void Wheel_PrepareProbeSegments(AiController *controller) {
    CVector3 a, b;
    f32 angle, zero, yA, yB;
    s32 i;
    angle = controller->player->heading;
    angle -= 3.1415927f;
    angle += 0.3926991f;
    while (6.2831855f <= angle) angle -= 6.2831855f;
    zero = 0.0f;
    while (angle < zero) angle += 6.2831855f;
    if (6.1831856f < angle) angle = 6.1831856f;
    if (angle < 0.1f) angle = 0.1f;
    angle *= 0.15915494f;
    angle *= 8.0f;
    zero = 0.0f;
    if (angle < zero) angle = zero;
    if (8.0f < angle) angle = 8.0f;
    yA = 180.0f;
    yB = 140.0f;
    for (i = 0; i < 8; i++) {
        a = *Scaled_GetControllerPosition(controller);
        b = *Scaled_GetControllerPosition(controller);
        a.x += g_actorRadialDirections[i].x * controller->reach[i];
        a.z += g_actorRadialDirections[i].z * controller->reach[i];
        a.y += yA;
        b.y += yA;
        a = *Scaled_GetControllerPosition(controller);
        b = *Scaled_GetControllerPosition(controller);
        a.x += g_actorRadialDirections[i].x * controller->clearance[i];
        a.z += g_actorRadialDirections[i].z * controller->clearance[i];
        a.y += yB;
        b.y += yB;
    }
}

/* Advances an animation player one frame: returns 1 when there is no player or clip, or after wrapping
   past frame 7 back to 0; otherwise prepares and shows the current frame through Wheel_MeasureWheelReach and
   Wheel_MeasureWheelClearance, advances the frame at 0x1CC and returns 0. */


void Wheel_MeasureWheelReach(Player *player, s32 wheel);
void Wheel_MeasureWheelClearance(Player *player, s32 wheel);

int Wheel_AdvanceWheelProbe(WheelProbeClipState *p) {
    if (p == 0) {
        return 1;
    }
    if (p->clip == 0) {
        return 1;
    }
    if (p->frame < 8) {
        Wheel_MeasureWheelReach(p->clip, p->frame);
        Wheel_MeasureWheelClearance(p->clip, p->frame);
        p->frame++;
        return 0;
    }
    p->frame = 0;
    return 1;
}

s32 Wheel_GetDirectionSector(f32 angle) {
    f32 zeroBound;

    angle += g_wheelNegativeAngleWrap;
    if (g_wheelPositiveAngleWrap <= angle) {
        do {
            angle -= g_wheelPositiveAngleWrap;
        } while (g_wheelPositiveAngleWrap <= angle);
    }
    zeroBound = 0.0f;
    if (angle < zeroBound) {
        do {
            angle += g_wheelSectorAngleOffset;
        } while (angle < zeroBound);
    }
    if (g_wheelMaximumSectorAngle < angle) {
        angle = g_wheelMaximumSectorAngle;
    }
    if (angle < g_wheelMinimumSectorAngle) {
        angle = g_wheelMinimumSectorAngle;
    }
    angle *= g_wheelAngleToSectorScale;
    angle *= g_wheelSectorConversionLimits;
    zeroBound = 0.0f;
    if (angle < zeroBound) {
        angle = zeroBound;
    }
    if (g_wheelSectorConversionLimits <= angle) {
        angle = *(&g_wheelSectorConversionLimits + 1);
    }
    return (s32)angle;
}

int Wheel_NextDirectionSector(int sector) {
    int result = sector + 1;
    if (result == 8) {
        result = 0;
    }
    return result;
}

int Wheel_PreviousDirectionSector(int sector) {
    int result = sector - 1;
    if (sector == 0) {
        result = 7;
    }
    return result;
}

