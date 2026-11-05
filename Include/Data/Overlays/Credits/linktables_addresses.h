#ifndef DATA_OVERLAYS_CREDITS_LINKTABLES_ADDRESSES_H
#define DATA_OVERLAYS_CREDITS_LINKTABLES_ADDRESSES_H
#include "Ai/player_symbols.h"
#include "Ai/weapon_fire_state_table_row.h"
/* Overlay symbols known only by address in the version symbol maps. */
extern char addrLow_Weapon_InitializeFireStateCallbacks_eu_us[];
extern char addrLow_Weapon_ReleaseLinkedActorHandlesEntryVariant3[];
extern char addrLow_Weapon_StartStateB_us[];
extern char addrLow_Weapon_UpdateState0_eu[];
extern char addrLow_Weapon_UpdateStateB_us[];
extern char addrLow_Weaponai_UpdateHeldFire_eu[];
extern char g_Weaponai_UpdateAfterAmmoModeChangeEncodedCallback[];
extern char g_linktablesTrailingTargetAddress[];
extern char g_weapon_AdvanceSpinAndTriggerModeEntry[];
extern char g_weapon_ApplyScaledSideYawEntry[];
extern char g_weapon_ApproachSpinPhaseAndReleaseEntry[];
extern char g_weapon_EnterChargeStateWithCuesEntry[];
extern char g_weaponInitializeChargeAndLoopSoundEntry[];
extern char g_weapon_InitializeChargeAndLoopSoundEntry[];
extern char g_weapon_InitializeFireStateCallbacksEntry[];
extern char g_weapon_PlayAlternateTriggerStartupCueEntry[];
extern char g_weapon_PlaySpinStartupCueEntry[];
extern char g_weapon_ReleaseHandlesAndExitStateEntry[];
extern char g_weapon_RequestReleaseOnEnabledEventEntry[];
extern char g_weapon_ResetControllerAndSpinEntry[];
extern char g_weaponTranslatePitchEffectEventEntry[];
extern char g_weapon_UpdateAlternateTriggerCompletionEntry[];
extern char g_weapon_UpdateHeldAlternateFireEntry[];
extern char g_weapon_UpdateSpecialFireAndAmmoEntry[];
extern char g_weapon_UpdateTriggerReleaseStateEntry[];
extern char g_weaponai_DecaySpinAndActivateEffectEntry[];
extern char g_weaponai_SelectReleasedFireStateEntry[];
extern char g_weaponai_ToggleFiringModeWithAmmoCheckEntry[];
extern char g_weaponai_TryEnterAlternateAmmoModeEntry[];
extern char g_weaponTryRequestAlternateFireEntry[];
extern char g_weaponai_TryEnterAmmoCostStateEntry[];
extern char g_weaponai_TryEnterChargedAlternateModeEntry[];
extern char g_weaponai_UpdateAlternateFireEntry[];
extern char g_weaponai_UpdateAnimatedFiringModeEntry[];
extern char g_weaponai_UpdateForceMarkerTriggerEntry[];
extern char g_weaponai_UpdateHeldFireEntry[];
extern char g_weaponai_UpdateSpinAndAlternateFireEntry[];
extern char g_weaponai_UpdateSpinAndRepeatCueEntry[];
extern unsigned int g_actionInitBreakableMotionRecordTable_de[];
extern char g_turretDispatchTriggerPairs_de[];
#include "Data/Weapon_callbacks/weapon_fire_state_table.h"
#endif
