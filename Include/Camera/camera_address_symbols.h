#include "Data/rest_source_records.h"
#ifndef CAMERA_ADDRESS_SYMBOLS_H
#define CAMERA_ADDRESS_SYMBOLS_H
#include "Ai/player_symbols.h"
#include "Common/globals.h"
#include "Common/Lone/g_defaultcamerasurfacetype.h"
#include "Common/ballisticparams.h"
#include "Ai/ai_shared_symbols.h"
#include "Common/menu_model_preview.h"
#include "Common/funcptr.h"
typedef struct Shared_CameraModeCallback CameraModeCallbackEntry;
/* Symbols that exist only at a fixed ROM address; each is referenced through its address. */
extern char g_tlbMissExceptionVector[];
#include "Data/Weapon_callbacks/weapon_fire_state_table.h"
extern u8 g_playerSequenceSavedViewBytes[4];
extern struct MenuModelScreen g_fallbackScreenMessageEmitter[];
extern CameraModeCallbackEntry g_cameraModeCallbacks[];
extern f32 Gu_Sqrtf(float value);
extern FuncPtr g_cameraGameplayModeCallbacks[][2];
extern s32 g_hudReferenceViewportWidth;
extern s32 g_skyLayerDescriptorCount;
extern char addrLow_Weaponai_DecaySpinAndActivateEffect_us[];
extern char addrLow_Weaponai_ToggleFiringModeWithAmmoCheck_us[];
extern char addrLow_Weaponai_UpdateSpinAndRepeatCue_us[];
extern char addrLow_Weaponai_SettleSpinToThirdTurn_us[];
extern char addrLow_Weaponai_UpdateAnimatedFiringMode_us[];
extern char addrLow_Weaponai_TryEnterAmmoCostState_us[];
extern char addrLow_Weaponai_TryEnterAlternateFireState_us[];
extern char addrLow_Weaponai_TryEnterAlternateAmmoMode_us[];
extern char addrLow_Weaponai_TryEnterChargedAlternateMode_us[];
extern char addrLow_Weaponai_UpdateForceMarkerTrigger_us[];
extern char addrLow_Weaponai_UpdateHeldFire_us[];
extern char addrLow_Weapon_InitializeFireStateCallbacks_eu_us[];
extern char addrLow_Weapon_ReleaseLinkedActorHandlesEntryVariant1[];
extern char addrLow_Weapon_ApplyScaledSideYaw_us[];
extern char addrLow_Weapon_ApplySideDependentYaw_us[];
extern char addrLow_Weapon_EnterChargeStateWithCues_us[];
extern char addrLow_Weapon_EmptyChargeStateHookEntryVariant1[];
extern char addrLow_Weapon_SetDelayAndRequestAlternateFireState_us[];
extern char addrLow_Weapon_StartStateB_us[];
extern char addrLow_Weapon_UpdateStateB_us[];
extern char addrLow_Weapon_UpdateSpecialFireAndAmmo_us[];
extern char addrLow_Weapon_RequestReleaseOnEnabledEvent_us[];
extern char addrLow_Weapon_PlayStartupCue80C_us[];
extern char addrLow_Weapon_UpdateAlternateTriggerCompletion_us[];
extern char addrLow_Weapon_EaseSpinAndUpdateFeedback_us[];
extern char addrLow_Weapon_ApproachSpinPhaseAndRelease_us[];
extern char addrLow_Weapon_TranslateEventSixByPitch_us[];
extern char addrLow_Gsky_FloorSurfaceNoOpEntryVariant1[];
extern f32 k_cameraFadeResetValue[];
extern f32 k_cameraInitialBobRateY[];
#endif
