#include "COMMON/PLAYER_RECORD_AND_FRAGTAG_VIEWS.H"
#include "COMMON/WORLD.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "COMMON/GAMEPLAY_TRANSITION.H"
#include "TYPES.H"
#include "COMMON/RESOURCELOADSTATE.H"
#include "COMMON/VIEWFLAGS.H"
#include "GFX/TEXT/PLAYERAI_APPLYDAMAGEOVERTIME_DATA.H"

/* Drains a player's ammunition over time: unless Cinema_IsSequenceActive reports a pause, Playerai_IsRoundEndState blocks
   the player, g_worldFrozenFlag is set, bit 1 of g_gameSettings is set or the player's state is below 2, it
   advances the tick counter at 0x84C modulo the period (a fifth of it while 0x80C is set), counting
   only kind 0x20 while the value at 0x670 is positive, and on each wrap takes one from each of the
   three slot counts at 0x5F4 without going below zero. Written from its own assembly with early
   returns and a clamp-at-zero decrement. */
extern s32 g_gameSettings;



int Playerai_SelectedWeaponUsesAmmo(Shared_ActorView *actor) {
    short index = actor->selectedAction;
    return ((WeaponInfo *)g_weaponInfoByType[index])->capacity > 0;
}

/** Perform the no-op callback at VRAM 0x8022BEEC. */
void Playerai_NoopDamageSourceCallback_de(void *unused0, void *unused1) {
}

void Playerai_ApplyPeriodicDamage(void *player, s32 unused, s32 period, s32 kind) {
    s32 tick;
    if (Cinema_IsSequenceActive() != 0) {
        return;
    }
    if (Playerai_IsRoundEndState(player) != 0) {
        return;
    }
    if (g_world.frozen != 0) {
        return;
    }
    if (g_gameSettings & 1) {
        return;
    }
    if ((u16)(((SharedPlayer *)(player))->views5E8.view650_15.actionState) < 2) {
        return;
    }
    if (((SharedPlayer *)(player))->views5E8.view80C_107.mount != 0) {
        period /= 5;
    }
    if (((SharedPlayer *)(player))->views5E8.view670_30.shield > 0.0f && kind != 32) {
        return;
    }
    tick = (((SharedPlayer *)(player))->views5E8.view84C_149.periodicTick + 1) % period;
    ((SharedPlayer *)(player))->views5E8.view84C_149.periodicTick = tick;
    if (tick != 0) {
        return;
    }
    ((((SharedPlayer *)(player))->views5E8.view5F4_11.ammo[0]) = ((((SharedPlayer *)(player))->views5E8.view5F4_11.ammo[0]) - 1 < 0) ? 0 : (((SharedPlayer *)(player))->views5E8.view5F4_11.ammo[0]) - 1);
    ((((SharedPlayer *)(player))->views5E8.view5F4_11.ammo[1]) = ((((SharedPlayer *)(player))->views5E8.view5F4_11.ammo[1]) - 1 < 0) ? 0 : (((SharedPlayer *)(player))->views5E8.view5F4_11.ammo[1]) - 1);
    ((((SharedPlayer *)(player))->views5E8.view5F4_11.ammo[2]) = ((((SharedPlayer *)(player))->views5E8.view5F4_11.ammo[2]) - 1 < 0) ? 0 : (((SharedPlayer *)(player))->views5E8.view5F4_11.ammo[2]) - 1);
}
