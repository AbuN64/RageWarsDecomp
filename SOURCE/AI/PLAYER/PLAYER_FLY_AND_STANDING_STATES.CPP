#include "WEAPONS/PLAYER_MOVEMENT_INTERFACES.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/MENU_MATCH_GLOBALS.H"
#include "COMMON/WORLD.H"
#include "TYPES.H"
#include "ENGINE/AUDIO/CHANNEL.H"

extern f32 g_frameElapsedTime;


extern void Graphu64_EaseValueToward(f32 *value, f32 target, f32 rate);

extern void Graphu64_ScaleVector(CVector3 *, CVector3 *, f32);

extern void Graphu64_AddVec3(CVector3 *, CVector3 *, CVector3 *);

/* Runs a player's standing and walking state for its body: settles the weapon sway through
   Player_UpdateWeaponSwayAndBob, turns the view through Player_UpdateViewAngles with the crouching tuning g_playerGroundViewAngleParameters while the
   crouch at 0x718 is past 5.12 or the standing tuning g_playerAirViewAngleParameters otherwise, and unless a jump releases
   the player into mode 5 it hands strafing at 0x6A4 or lifting at 0x6A8 (outside zoom mode 2) to mode
   3; then, unless an unfinished pickup, reload or wave animation is playing, it picks the animation at
   0x86C: for the idle character g_fragTagModelId the fidget animations 1 and 2 alternate after 12 and 21 time
   units at 0x104, and otherwise the turning animations follow the heading change this frame (0xA28
   while the body is falling, with a separate set for the character g_playerSpecialAnimationTable). */












extern char g_playerSpecialAnimationTable;

extern void Player_UpdateWeaponSwayAndBob(SharedPlayer *, BodyPlayerUpdateStandingState *);

extern void Player_UpdateViewAngles(SharedPlayer *, BodyPlayerUpdateStandingState *, char *);

static inline s32 try_jump(SharedPlayer *player, BodyPlayerUpdateStandingState *body) {
    if (player->views5E8.view7E8_106.zoomed == 0 && !(11.25f < player->views5E8.view6E4_62.depth) && !(body->flags & 0xC0000)
        && (body->surface->flags & 2) && (player->views5E8.view6B0_47.input & 0x10) && player->views5E8.view11D8_149.stun <= 0.0f) {
        Player_SetPlayerState(player, body, 5);
        return 1;
    }
    return 0;
}

void Player_UpdateFlyMode(void *player, void *bodyActor) {
    CVector3 direction;
    f32 held;
    f32 value;
    s32 flags;
    s32 result;
    void *data;

    if (((PlayerFlyModeView *)player)->action == 0 &&
        !(((PlayerFlyModeView *)player)->motionFlags & 0xE000)) {
        ((PlayerFlyModeView *)player)->action = 1;
    }
    ((PlayerFlyModeView *)player)->lean = 0;

    held = (&g_playerFlyYawInputScale)[1];
    Graphu64_EaseValueToward(&((PlayerFlyBodyView *)(bodyActor))->yaw,
                  ((PlayerFlyBodyView *)bodyActor)->yaw +
                      (f32)((ControllerAxesView *)((PlayerFlyModeView *)player)->controller)->x * g_playerFlyYawInputScale,
                  held);
    Graphu64_EaseValueToward(&((PlayerFlyModeView *)(player))->pitch,
                  ((PlayerFlyModeView *)player)->pitch +
                      (f32)-((ControllerAxesView *)((PlayerFlyModeView *)player)->controller)->y * g_playerFlyPitchInputScale,
                  held);

    value = ((PlayerFlyModeView *)player)->lateralInput;
    if (value != 0.0f) {
        f32 step;
        f32 limit;
        step = value * (&g_playerFlyPitchInputScale)[1];
        if (value < 0.0f) {
            limit = -value * g_playerFlyReverseSpeedScale;
        } else {
            limit = value * g_playerFlyForwardSpeedScale;
        }
        ((PlayerFlyModeView *)player)->forwardSpeed =
            Graphu64_IntegrateBoundedValue(((PlayerFlyModeView *)player)->forwardSpeed, step, limit);
    } else {
        ((PlayerFlyModeView *)player)->forwardSpeed =
            Graphu64_DecayToZero(((PlayerFlyModeView *)player)->forwardSpeed, g_playerFlyForwardSpeedDecay);
    }

    value = ((PlayerFlyModeView *)player)->forwardInput;
    if (value != 0.0f) {
        f32 step;
        f32 limit;
        step = value * g_playerFlyStrafeAcceleration;
        if (value < 0.0f) {
            limit = -value * g_playerFlyLeftSpeedScale;
        } else {
            limit = value * g_playerFlyRightSpeedScale;
        }
        ((PlayerFlyModeView *)player)->lateralSpeed =
            Graphu64_IntegrateBoundedValue(((PlayerFlyModeView *)player)->lateralSpeed, step, limit);
    } else {
        ((PlayerFlyModeView *)player)->lateralSpeed =
            Graphu64_DecayToZero(((PlayerFlyModeView *)player)->lateralSpeed, g_playerFlyStrafeSpeedDecay);
    }

    flags = ((PlayerFlyModeView *)player)->motionFlags;
    if (flags & 0x10) {
        ((PlayerFlyBodyView *)bodyActor)->verticalSpeed =
            Graphu64_IntegrateBoundedValue(((PlayerFlyBodyView *)bodyActor)->verticalSpeed, g_playerFlyRiseAcceleration, 71.68f);
    } else if (flags & 0x2020) {
        ((PlayerFlyBodyView *)bodyActor)->verticalSpeed =
            Graphu64_IntegrateBoundedValue(((PlayerFlyBodyView *)bodyActor)->verticalSpeed, g_playerFlyFallAcceleration, 71.68f);
    } else {
        ((PlayerFlyBodyView *)bodyActor)->verticalSpeed =
            Graphu64_DecayToZero(((PlayerFlyBodyView *)bodyActor)->verticalSpeed, g_playerFlyVerticalSpeedDecay);
    }

    {
        f32 angle;
        angle = ((PlayerFlyBodyView *)bodyActor)->yaw;
        angle += (held = g_playerFlyPositiveYawPeriod);
        direction.x = ((PlayerFlyModeView *)player)->forwardSpeed * Gu_Sinf(angle);
    }
    direction.y = ((PlayerFlyBodyView *)bodyActor)->verticalSpeed;
    direction.z = ((PlayerFlyModeView *)player)->forwardSpeed *
                  Math_Cosf(((PlayerFlyBodyView *)bodyActor)->yaw + held);
    held = g_playerFlyNegativeYawPeriod;
    direction.x += ((PlayerFlyModeView *)player)->lateralSpeed *
                   Gu_Sinf(((PlayerFlyBodyView *)bodyActor)->yaw - held);
    direction.z += ((PlayerFlyModeView *)player)->lateralSpeed *
                   Math_Cosf(((PlayerFlyBodyView *)bodyActor)->yaw - held);

    Graphu64_ScaleVector(&direction, &direction, g_frameElapsedTime);
    Graphu64_AddVec3(&((PlayerFlyModeView *)(player))->previousPosition,
                  &((PlayerFlyModeView *)(player))->previousPosition, &direction);
    result = Scene_FindFloorPolygon(&g_world, &((PlayerFlyBodyView *)bodyActor)->position);
    if (result != 0) {
        ((PlayerFlyBodyView *)bodyActor)->model = result;
    }

    if (((PlayerFlyModeView *)player)->action == 1 &&
        (((PlayerFlyModeView *)player)->motionFlags & 0xE000) == 0xE000 &&
        (((PlayerFlyModeView *)player)->inputFlags & 0xE000)) {
        Player_SetPlayerState(player, bodyActor, 2);
        data = ((PlayerFlyModeView *)player)->view;
        if (data != 0) {
            Camera_PostScreenMessage(&g_frontendScreenStatus, data, &s_flyModeOffText);
        }
    }
}

void Player_UpdateStandingState(SharedPlayer *player, BodyPlayerUpdateStandingState *body) {
    f32 heading;
    s32 crouching;
    s32 animate;

    Player_UpdateWeaponSwayAndBob(player, body);
    heading = body->heading;
    crouching = 5.12f < player->views5E8.view718_70.crouch;
    if (crouching) {
        Player_UpdateViewAngles(player, body, &g_playerGroundViewAngleParameters);
    } else {
        Player_UpdateViewAngles(player, body, &g_playerAirViewAngleParameters);
    }
    heading = body->heading - heading;
    if (try_jump(player, body)) {
        return;
    }
    if (player->views5E8.view6A4_42.strafe != 0.0f || (player->views5E8.view7E8_106.zoomed != 2 && player->views5E8.view6A8_44.lift != 0.0f)) {
        Player_SetPlayerState(player, body, 3);
    }
    animate = 1;
    if ((player->views5E8.view86C_127.animation == 4400 || player->views5E8.view86C_127.animation == 4405) && player->views1C.view10E_13.idle == 0) {
        animate = 0;
    }
    if ((player->views5E8.view86C_127.animation == 24150 || player->views5E8.view86C_127.animation == 24158) && player->views1C.view10E_13.idle == 0) {
        animate = 0;
    }
    if ((player->views5E8.view86C_127.animation == 4000 || player->views5E8.view86C_127.animation == 4100) && player->views1C.view10E_13.idle == 0) {
        animate = 0;
    }
    if (animate) {
        if (player->views1C.viewE4_7.kind == g_fragTagModelId) {
            if (player->views5E8.view86C_127.animation == 1 && 12.0f <= player->views1C.view104_11.idleTime) {
                player->views5E8.view86C_127.animation = 2;
            } else if (player->views5E8.view86C_127.animation == 2 && 21.0f <= player->views1C.view104_11.idleTime) {
                player->views5E8.view86C_127.animation = 1;
            } else if ((u32) (player->views5E8.view86C_127.animation - 1) >= 2) {
                player->views5E8.view86C_127.animation = 1;
            }
        } else if (player->views13B4.view13B4_3.character == &g_playerSpecialAnimationTable) {
            if (body->flags & 0xC0000) {
                player->views5E8.view86C_127.animation = 2600;
            } else if (0.017453294f < heading) {
                player->views5E8.view86C_127.animation = 24102;
            } else if (heading < -0.017453294f) {
                player->views5E8.view86C_127.animation = 24101;
            } else {
                player->views5E8.view86C_127.animation = 24100;
            }
        } else {
            if (body->flags & 0xC0000) {
                player->views5E8.view86C_127.animation = 2600;
            } else if (0.017453294f < heading) {
                player->views5E8.view86C_127.animation = 2910;
            } else if (heading < -0.017453294f) {
                player->views5E8.view86C_127.animation = 2900;
            } else {
                player->views5E8.view86C_127.animation = 1;
            }
        }
    }
}
