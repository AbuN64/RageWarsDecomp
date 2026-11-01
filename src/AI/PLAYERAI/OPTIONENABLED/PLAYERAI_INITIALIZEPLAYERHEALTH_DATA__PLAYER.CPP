#include "DATA/WEAPON_CALLBACKS/ADDRLOW_WEAPONAI_INITIALIZESWITCHFORSINGLEROUND.H"
#include "DATA/WEAPON_CALLBACKS/G_WEAPON_RESETCONTROLLERANDSPINENCODEDCALLBACK.H"
#include "DATA/WEAPON_CALLBACKS/ADDRLOW_WEAPON_RELEASEHANDLESANDEXITSTATE39.H"
#include "DATA/WEAPON_CALLBACKS/PLAYER_HEALTH_CALLBACK_LABELS.H"
#include "DATA/OVL1_F/WEAPON_CHARGE_CALLBACK_ADDRESS.H"
#include "DATA/WEAPON_CALLBACKS/OVERLAY_SIX_FIRST_CALLBACK_ROM_ENTRY.H"
#include "DATA/WEAPON_CALLBACKS/WEAPON_UPDATE_TRIGGER_RELEASE_STATE_ADDRESS.H"
#include "DATA/OVL1_D/WEAPON_CHARGE_FIVE_CALLBACK_ADDRESS.H"
#include "DATA/OVL1_F/WEAPON_UPDATE_HELD_FIRE_CALLBACK_ADDRESS.H"
#include "DATA/WEAPON_CALLBACKS/WEAPON_STATE_CALLBACK_ADDRESS.H"
#include "DATA/WEAPON_CALLBACKS/WEAPON_STARTUP_CUE_ADDRESS.H"
#include "DATA/WEAPON_CALLBACKS/ADDRLOW_WEAPON_ADVANCESPINANDTRIGGERMODE.H"
#include "DATA/WEAPON_CALLBACKS/WEAPONAI_SELECTRELEASEDFIRESTATE_ADDRESS.H"
#include "DATA/WEAPON_CALLBACKS/WEAPON_FIRE_STATE_TABLE.H"

#if defined(VERSION_US_REV1)
extern char addrLow_Weapon_ReleaseLinkedActorHandles[];

/* Rates read by Playerai_UpdateTargetFacing and Playerai_UpdateReactionReserve. */
f32 g_playerTargetFacingEaseRate = 0.35f;
f32 g_playerReactionReserveApproachRate = 0.00625f;

/* Linker fill between the rate and the next constant: no instruction reads it and the other builds hold other words here. */
u32 g_playerReactionReserveApproachRatePad[2] = {
    0xFFFFFFFF, 0xFFFF0000,
};

f32 k_PlayeraiInitializeplayerhealthOneWords = 1.0f;

struct WeaponAnimationChoice g_weaponAnimationChoicesA[5] = {
    { 20210, 10 }, { 20220, 10 }, { 20230, 10 }, { 20240, 10 }, { -1, 0 },
};

struct WeaponAnimationChoice g_weaponAnimationChoicesB[5] = {
    { 20550, 10 }, { 20551, 10 }, { 20552, 10 }, { 20553, 10 }, { -1, 0 },
};

struct WeaponAnimationChoice g_weaponAnimationChoicesC[5] = {
    { 20510, 10 }, { 20520, 10 }, { 20530, 10 }, { 20540, 10 }, { -1, 0 },
};

/* Mirror flags read by Player_BuildWeaponHandTransform, followed by two unused zero words. */


/* Base state table of the weapon fire state machine (Weapon_InitializeFireStateCallbacks installs it). */

/* Spin weapon states searched before the base table. */

/* Trigger release weapon states searched before the base table. */
#endif
