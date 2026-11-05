#include "Data/rom_callback_word.h"
#include "Common/output.h"
#include "frontend_symbols.h"
#include "include_asm.h"
#include "Common/sharedplayer.h"
#include "Common/self.h"
#include "Common/motion_step.h"
#include "Common/aiprofile.h"
#include "Common/ai_behaviour_types.h"
#include "types.h"
#include "Ai/Nav/wheel.h"
#include "Ai/Player/scaled_updatetargetpitch.h"
#include "Insthdr/insthdr_getactorshadowradius.h"
#include "Libsn/nav_isballisticarcobstructed_data.h"
#include "Engine/Unicol/unicol.h"
#include "Engine/Unicol/PLTFMCOL.h"
#include "Gobjinst/gameobject_getactorheight.h"
#include "Ai/Nav/Scaled/g_actorradialdirections_wheel.h"
#include "Common/Lone/collision_current_actor.h"
#include "Ai/nav_symbols.h"
#include "Ai/ai_functions.h"
#if defined(VERSION_US_REV1)
#include "Data/Ovl1_f/weapon_update_held_fire_callback_address.h"
#endif

/* Probes one of a vehicle's eight wheel rays: casts from the vehicle position to its scaled wheel offset
 * through Unicol_SweepActorMotion and stores the wheel's reach as the XZ distance to whatever was hit (diagonals
 * scaled by 1/sqrt 2, components tested against the zeroed y), or the full ray length on a miss. */


void Wheel_MeasureWheelReach(Player *player, s32 wheel) {
    CVector3 from;
    CVector3 to;
    CVector3 delta;
    f32 actorReach;
    f32 actorRadius;
    f32 actorHeight;
    from = player->pos;
    to = g_actorRadialDirections[wheel];
    to.x *= player->controller->length;
    to.y *= player->controller->length;
    to.z *= player->controller->length;
    to.x += from.x;
    to.y += from.y;
    to.z += from.z;
    from.y += 61.44f;
    actorReach = InstHdr_GetActorReach(player);
    actorRadius = Gobjinst_GetActorRadius(player);
    actorHeight = Gobjinst_GetActorHeight(player);
    if (Unicol_SweepActorMotion(player, from, to, &g_particleCollisionProbeResult, actorReach, actorRadius, actorHeight, InstHdr_GetActorBaseOffset(player))) {
        delta = (*(CVector3 *)&g_collisionCurrentActor->vecE4);
        delta.x -= from.x;
        delta.y = 0.0f;
        delta.z -= from.z;
        if (delta.x != delta.y) {
            if (delta.z == delta.y) {
                player->controller->reach[wheel] = ((delta.x) < (delta.y) ? -(delta.x) : (delta.x));
            } else {
                player->controller->reach[wheel] =
                    (((delta.x) < (delta.y) ? -(delta.x) : (delta.x)) + ((delta.z) < (delta.y) ? -(delta.z) : (delta.z))) * 0.70710677f;
            }
        } else if (delta.z != delta.y) {
            player->controller->reach[wheel] = ((delta.z) < (delta.y) ? -(delta.z) : (delta.z));
        }
    } else {
        player->controller->reach[wheel] = player->controller->length;
    }
}

/* Stores the clearance reached before the given step: (stepIndex - 1) x reach, never below 0. */
static inline void storeClearance(Player *player, s32 wheel, s32 stepIndex, f32 reach) {
    player->controller->clearance[wheel] = (stepIndex - 1 >= 0 ? stepIndex - 1 : 0) * reach;
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
        if (g_collisionCurrentActor->typeFC == 5 || g_collisionCurrentActor->typeFC == 6) {
            storeClearance(player, wheel, i, reach);
            return;
        }
        if ((*(CVector3 *)&g_collisionCurrentActor->vecE4).y <= below.y - 100.0f) {
            storeClearance(player, wheel, i, reach);
            return;
        }
    }
}


/* Builds the eight radial probe segments around the player at two heights (reach at 180, clearance at
 * 140) from its position through Scaled_GetControllerPosition, after turning its heading into a sector in [0, 8].
 * The segments stay on the stack: the debug draw that used them (and the sector) is compiled out. */
void Wheel_PrepareProbeSegments(AiController *controller) {
    CVector3 probeEnd, probeStart;
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
        probeEnd = *Scaled_GetControllerPosition(controller);
        probeStart = *Scaled_GetControllerPosition(controller);
        probeEnd.x += g_actorRadialDirections[i].x * controller->reach[i];
        probeEnd.z += g_actorRadialDirections[i].z * controller->reach[i];
        probeEnd.y += yA;
        probeStart.y += yA;
        probeEnd = *Scaled_GetControllerPosition(controller);
        probeStart = *Scaled_GetControllerPosition(controller);
        probeEnd.x += g_actorRadialDirections[i].x * controller->clearance[i];
        probeEnd.z += g_actorRadialDirections[i].z * controller->clearance[i];
        probeEnd.y += yB;
        probeStart.y += yB;
    }
}

/* Advances an animation player one frame: returns 1 when there is no player or clip, or after wrapping
   past frame 7 back to 0; otherwise prepares and shows the current frame through Wheel_MeasureWheelReach and
   Wheel_MeasureWheelClearance, advances the frame and returns 0. */


void Wheel_MeasureWheelReach(Player *player, s32 wheel);
void Wheel_MeasureWheelClearance(Player *player, s32 wheel);

int Wheel_AdvanceWheelProbe(WheelProbeClipState *probe) {
    if (probe == 0) {
        return 1;
    }
    if (probe->clip == 0) {
        return 1;
    }
    if (probe->frame < 8) {
        Wheel_MeasureWheelReach(probe->clip, probe->frame);
        Wheel_MeasureWheelClearance(probe->clip, probe->frame);
        probe->frame++;
        return 0;
    }
    probe->frame = 0;
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



#if defined(VERSION_US)
char s_WheelDirectionSectorConstantReSetRText[8] =
    "reSetR\000\000";
#endif

#if defined(VERSION_EU_X)
void *k_weaponaiUpdateHeldFireCaseAddresses[2] = {
    (void *)&Weaponai_UpdateHeldFire_label752, (void *)&Weaponai_UpdateHeldFire_label744,
};
#endif

#if defined(VERSION_DE)
unsigned int k_WheelDirectionSectorConstantData[2] = {
    0x0C0AC91C, 0x02402821,
};
#endif



#if defined(VERSION_EU_X)
const RomCallbackWord k_navResetwheelprobestateFragment[2] = {
    { 0x00232790 }, { 0x00232790 },
};
#endif

#if defined(VERSION_EU)
const unsigned int k_navResetwheelprobestateFragment[2] = {
    0x00641023, 0xAEA20010,
};
#endif

#if defined(VERSION_DE)

#endif

#if defined(VERSION_US_REV1)
void *g_NavData[2] = {
    (void *)&Weaponai_UpdateHeldFire_label1064, (void *)&Weaponai_UpdateHeldFire_label1064,
};
#endif

/* Retained data for this translation unit. */

const float g_Wheel_GetDirectionSectorConstantWords[8] = {
    0.3926991f, 6.2831855f, 6.2831855f, 6.1831856f,
    0.1f, 0.15915494f, 8.0f, 7.0f,
};

const float g_Nav_ResetWheelProbeStateConstantWords[2] = {
    100.0f, 307.2f,
};
#if defined(VERSION_DE)
const unsigned int k_NavResetwheelprobestateData[2] = {
    0x40490FDB, 0x3FC90FDB,
};
#endif
