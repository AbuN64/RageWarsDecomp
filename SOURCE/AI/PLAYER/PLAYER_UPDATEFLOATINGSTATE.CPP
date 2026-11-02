#include "WEAPONS/PLAYER_MOVEMENT_INTERFACES.H"
#include "COMMON/WEAPON_SCREEN_MESSAGE_OPERATIONS.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/MULTIPLAYEROPTIONS.H"
#include "TYPES.H"

/* Runs a player's floating movement state for its body: sets the movement mode at 0x650 to 11 when
   still and 12 when moving (speed at 0x6C8), turns the view through Player_UpdateViewAngles with tuning
   g_playerSwimViewAngleParameters, sways the weapon on three sine waves of the state time at 0x658, moves the body through
   Player_UpdateFlyingThrustAndBoost with tuning g_playerSwimMovementParameters, and once the state time passes 2 without the body's flag
   0x1000 it ends the state: clears the strokes at 0x938 and the body's 0x20, plays sound 0x2DE, clears
   0x840 and hands the player to Player_SetPlayerState (mode 2 when body flags 3 are set, else 10); it then
   picks the animation at 0x86C from the vertical speed at 0x6C0 (kept while idle animation 0x1144
   plays) and, while moving faster than 5.12, plays the tuning's stroke sound and sound 0x2E0 whenever
   the sound timer at 0x11C4 passes 45, restarting it at a random value below 15. */








extern void Player_UpdateViewAngles(SharedPlayer *, BodyPlayerUpdateFloatingState *, char *);

extern void Player_UpdateFlyingThrustAndBoost(SharedPlayer *, BodyPlayerUpdateFloatingState *, Tuning *);
extern void TeamSelect_EmptyWeaponWheelHook(char *);
extern s32 SoundElement_PlaySoundAtPosition(s16, s32, s32, s32, s32, s32);


void Player_UpdateFloatingState(SharedPlayer *player, BodyPlayerUpdateFloatingState *body) {
    s32 idle;

    if (player->views5E8.view6C8_57.speed == 0.0f) {
        player->views5E8.view650_18.mode = 11;
    } else {
        player->views5E8.view650_18.mode = 12;
    }
    Player_UpdateViewAngles(player, body, &g_playerSwimViewAngleParameters);
    player->views5E8.view730_79.sway[0] = 2.0f * Gu_Sinf(player->views5E8.view658_24.swimTime * 0.06981318f) * 0.017453294f;
    player->views5E8.view730_79.sway[1] = 2.0f * Gu_Sinf(player->views5E8.view658_24.swimTime * 0.08726647496f) * 0.017453294f;
    player->views5E8.view730_79.sway[2] = 2.0f * Gu_Sinf(player->views5E8.view658_24.swimTime * 0.10471976548f) * 0.017453294f;
    Player_UpdateFlyingThrustAndBoost(player, body, &g_playerSwimMovementParameters);
    if (!(body->flags & 0x1000) && 2.0f < player->views5E8.view658_24.swimTime) {
        TeamSelect_EmptyWeaponWheelHook(player->views5E8.view938_129.strokes);
        body->stroke = 0;
        SoundElement_PlaySoundAtPosition(734, body->x, body->y, body->z, 0, -1);
        player->views5E8.view840_118.surfaced = 0;
        if (body->flags & 3) {
            Player_SetPlayerState(player, body, 2);
        } else {
            Player_SetPlayerState(player, body, 10);
        }
    }
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
    if (5.12f < player->views5E8.view6C8_57.speed && 45.0f < player->views5E8.view11C4_144.soundTime) {
        player->views5E8.view11C4_144.soundTime = Graphu64_RandomFloat(15.0f);
        SoundElement_PlaySoundAtPosition(g_playerSwimMovementParameters.strokeSound, body->x, body->y, body->z, 0, -1);
        SoundElement_PlaySoundAtPosition(736, body->x, body->y, body->z, 0, -1);
    }
}
