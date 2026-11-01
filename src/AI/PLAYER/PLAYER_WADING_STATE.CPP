#include "WEAPONS/PLAYER_MOVEMENT_INTERFACES.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "TYPES.H"

/* Runs a player's wading state for its body: sets the movement mode at 0x650 to 9 when still and 10
   when moving, settles the roll kick at 0x72C, turns the view and moves the body through Player_UpdateViewAngles
   and Player_UpdateGroundThrustAndBoost with tunings g_playerAirViewAngleParameters and g_playerClimbMovementParameters, and leaves the state (clearing the strokes
   at 0x938, release mode 3) once the body loses surface flag 0x2000; otherwise looking down past 40
   degrees while lifting at 0x6A8 lowers the eye height at 0x6EC and sets flag 0x100000 of g_globalGameplayFlags
   (cleared otherwise), the weapon sways on three sine waves of the state time at 0x658, a jump input
   0x10 in shallow enough ground that allows it releases the player into mode 5, and otherwise the
   animation at 0x86C follows the vertical speed and a moving player plays the tuning's step sound
   whenever the step timer at 0x11C4 passes 11.25. Adapted from Player_UpdateFloatingState with the jump check as
   an inline function and the g_globalGameplayFlags flags read as an array. */










extern s32 g_globalGameplayFlags[];
extern void Graphu64_EaseValueToward(f32 *value, f32 target, f32 rate);
extern void Player_UpdateViewAngles(SharedPlayer *, BodyPlayerUpdateWadingState *, char *);

extern void TeamSelect_EmptyWeaponWheelHook(char *);
extern s32 SoundElement_PlaySoundAtPosition(s16, s32, s32, s32, s32, s32);

static inline s32 try_jump(SharedPlayer *player, BodyPlayerUpdateWadingState *body) {
    if (player->views5E8.view7E8_106.zoomed == 0 && !(11.25f < player->views5E8.view6E4_62.depth) && !(body->flags & 0xC0000)
        && (body->surface->flags & 2) && (player->views5E8.view6B0_47.input & 0x10) && player->views5E8.view11D8_149.stun <= 0.0f) {
        Player_SetPlayerState(player, body, 5);
        return 1;
    }
    return 0;
}

void Player_UpdateWadingState(SharedPlayer *player, BodyPlayerUpdateWadingState *body) {
    s32 idle;

    if (player->views5E8.view6C8_57.speed == 0.0f) {
        player->views5E8.view650_18.mode = 9;
    } else {
        player->views5E8.view650_18.mode = 10;
    }
    Graphu64_EaseValueToward(&player->views5E8.view72C_76.kickRoll, 0.0f, 0.25f);
    Player_UpdateViewAngles(player, body, &g_playerAirViewAngleParameters);
    Player_UpdateGroundThrustAndBoost(player, body, &g_playerClimbMovementParameters);
    if (!(body->flags & 0x2000)) {
        TeamSelect_EmptyWeaponWheelHook(player->views5E8.view938_129.strokes);
        Player_SetPlayerState(player, body, 3);
        return;
    }
    if (player->views5E8.view724_72.pitch * 57.295776f < -40.0f && player->views5E8.view6A8_44.lift > 0.0f) {
        player->views5E8.view6EC_65.height -= 10.24f;
        g_globalGameplayFlags[0] |= 0x100000;
    } else {
        g_globalGameplayFlags[0] &= ~0x100000;
    }
    player->views5E8.view730_79.sway[0] = Gu_Sinf(player->views5E8.view658_24.swimTime * 0.06981318f) * 0.043633237f;
    player->views5E8.view730_79.sway[1] = Gu_Sinf(player->views5E8.view658_24.swimTime * 0.08726647496f) * 0.043633237f;
    player->views5E8.view730_79.sway[2] = Gu_Sinf(player->views5E8.view658_24.swimTime * 0.10471976548f) * 0.043633237f;
    if (!try_jump(player, body)) {
        idle = 0;
        if (player->views5E8.view86C_127.animation == 4420) {
            idle = player->views1C.view10E_13.idle == 0;
        }
        if (player->views1C.viewE4_7.kind == g_fragTagModelId) {
            player->views5E8.view86C_127.animation = 2210;
        } else if (!idle) {
            if (1.024f <= player->views5E8.view6C0_52.climb) {
                player->views5E8.view86C_127.animation = 2210;
            } else if (player->views5E8.view6C0_52.climb <= -1.024f) {
                player->views5E8.view86C_127.animation = 2215;
            } else {
                player->views5E8.view86C_127.animation = 20;
            }
        }
        player->views5E8.view11C4_144.soundTime += g_frameElapsedTime;
        if (5.12f < player->views5E8.view6C8_57.speed && 11.25f < player->views5E8.view11C4_144.soundTime) {
            player->views5E8.view11C4_144.soundTime = 0.0f;
            SoundElement_PlaySoundAtPosition(g_playerClimbMovementParameters.strokeSound, body->x, body->y, body->z, 0, -1);
        }
    }
}
