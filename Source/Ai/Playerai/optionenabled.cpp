#include "Data/Weapon_callbacks/addrlow_weaponai_initializeswitchforsingleround.h"
#include "Ai/ai_functions.h"
#include "Common/weapon_marker_and_profile_views.h"
#include "Weapons/charge_and_linked_actor_handles.h"
#include "Weapons/startup_cues_and_side_yaw.h"
#include "Data/Weapon_callbacks/g_weapon_resetcontrollerandspinencodedcallback.h"
#include "Data/Weapon_callbacks/addrlow_weapon_release_handles_and_exit_state_label.h"
#include "Data/Weapon_callbacks/player_health_callback_labels.h"
#include "Data/Ovl1_f/weapon_charge_callback_address.h"
#include "Data/Weapon_callbacks/addrlow_weaponai_updatealternatefire.h"
#include "Data/Weapon_callbacks/weapon_update_trigger_release_state_address.h"
#include "Data/Ovl1_d/weapon_charge_and_loop_sound_callback_address.h"
#include "Data/Ovl1_f/weapon_update_held_fire_callback_address.h"
#include "Data/Weapon_callbacks/weapon_state_callback_address.h"
#include "Data/Weapon_callbacks/weapon_startup_cue_address.h"
#include "Data/Weapon_callbacks/addrlow_weapon_advancespinandtriggermode.h"
#include "Data/Weapon_callbacks/weaponai_selectreleasedfirestate_address.h"
#include "Data/Weapon_callbacks/weapon_fire_state_table.h"
#include "Ai/player_reaction_rate_data.h"

#if defined(VERSION_US_REV1)

/* Rates read by Playerai_UpdateTargetFacing and Playerai_UpdateReactionReserve. */

/* Linker fill between the rate and the next constant: no instruction reads it and the other builds hold other words here. */


/* Mirror flags read by Player_BuildWeaponHandTransform, followed by two unread zero words. */


/* Base state table of the weapon fire state machine (Weapon_InitializeFireStateCallbacks installs it). */
WeaponFireStateCallbackTable g_weaponFireStateCallbackTable = {
    0,
    { 0 },
    {
        { 0, Weaponai_InitializeSwitchForSingleRound, g_Weapon_ResetControllerAndSpinEncodedCallback, 0, 20000, 1.0f, 0, 0 },
        { 1, Weapon_ReleaseHandlesAndExitState39, Weapon_UpdateIdleWeaponSelection, 0, 20010, 1.0f, 2, 0 },
        { 2, Weapon_ReleaseLinkedActorHandles, Weaponai_UpdateAlternateFire, 0, 20100, 1.0f, 0, 0 },
        { 3, 0, Weaponai_UpdateAlternateFire, 0, 20110, 1.0f, 0, 0 },
        { 4, Weapon_ReleaseLinkedActorHandles, Weapon_UpdateTriggerReleaseState, 0, (u32)g_weaponAnimationChoicesA, 1.0f, 3, 0 },
        { 8, Weapon_InitializeChargeAndLoopSound, Weaponai_UpdateHeldFire, 0, (u32)g_weaponAnimationChoicesB, 1.0f, 3, 0 },
        { 7, 0, Weapon_UpdateIdleWeaponSelection, 0, 20249, 1.0f, 3, 0 },
        { -1 },
    },
};

/* Spin weapon states searched before the base table. */
WEAPON_STATE_TABLE(4) g_weaponSpinFireStateTable = {
    (struct WeaponStateTable *)&g_weaponFireStateCallbackTable,
    { 0 },
    {
        { 2, 0, Weaponai_UpdateSpinAndAlternateFire, 0, 20100, 1.0f, 0, 0 },
        { 3, 0, Weaponai_UpdateSpinAndAlternateFire, 0, 20110, 1.0f, 0, 0 },
        { 5, Weapon_PlayStartupCue9E2, Weapon_AdvanceSpinAndTriggerMode, 0, 20200, 1.0f, 3, 0 },
        { -1 },
    },
};

/* Trigger release weapon states searched before the base table. */
WEAPON_STATE_TABLE(5) g_weaponTriggerReleaseFireStateTable = {
    (struct WeaponStateTable *)&g_weaponFireStateCallbackTable,
    { 0 },
    {
        { 4, 0, Weaponai_SelectReleasedFireState, 0, 20200, 1.0f, 3, 0 },
        { 8, 0, Weaponai_SelectReleasedFireState, 0, 20200, 1.0f, 3, 0x20 },
        { 5, 0, Weapon_UpdateTriggerReleaseState, 0, 20210, 1.0f, 3, 0x20 },
        { 9, 0, Weapon_UpdateTriggerReleaseState, 0, 20550, 1.0f, 3, 0x20 },
        { -1 },
    },
};
#endif
