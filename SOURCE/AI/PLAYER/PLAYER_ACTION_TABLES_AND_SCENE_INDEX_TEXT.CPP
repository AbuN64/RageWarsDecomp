#include "DATA/REST_SOURCE_RECORDS.H"
extern s32 PAKInterface_LoadGame(s32 anUser, s32 anNote);
extern char g_PlayerEnterRunEndWaitCallbackAddressUs[];
extern char g_PlayerInterpolateTravelTargetCallbackAddressUs[];
extern char g_PlayerRequestCinemaTrackCallbackAddressUs[];
extern char g_PlayerResetStunAndMotionCallbackAddressUs[];
extern char g_PlayerSequence10StartCallbackAddressUs[];
extern char g_PlayerSequence11StartCallbackAddressUs[];
extern char g_PlayerSequence12StartCallbackAddressUs[];
extern char g_PlayerSequence13StartCallbackAddressUs[];
extern char g_PlayerSequence14StartCallbackAddressUs[];
extern char g_PlayerSequence15StartCallbackAddressUs[];
extern char g_PlayerSequence20StartCallbackAddressUs[];
extern char g_PlayerSequence30StartCallbackAddressUs[];
extern char g_PlayerSequence40StartCallbackAddressUs[];
extern char g_PlayerSequence50StartCallbackAddressUs[];
extern char g_PlayerSequence70StartCallbackAddressUs[];
extern char g_PlayerSequenceRunEndUpdateCallbackAddressUs[];
extern char g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant10[];
extern char g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant11[];
extern char g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant2[];
extern char g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant3[];
extern char g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant4[];
extern char g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant5[];
extern char g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant6[];
extern char g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant7[];
extern char g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant8[];
extern char g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant9[];
extern char g_PlayerSetSequenceFlag20CallbackAddressUs[];
extern char g_PlayerStateNoOperationCallbackAddressUs[];
extern char g_PlayerStateNoOperationCallbackAddressUsVariant10[];
extern char g_PlayerStateNoOperationCallbackAddressUsVariant11[];
extern char g_PlayerStateNoOperationCallbackAddressUsVariant2[];
extern char g_PlayerStateNoOperationCallbackAddressUsVariant3[];
extern char g_PlayerStateNoOperationCallbackAddressUsVariant4[];
extern char g_PlayerStateNoOperationCallbackAddressUsVariant5[];
extern char g_PlayerStateNoOperationCallbackAddressUsVariant6[];
extern char g_PlayerStateNoOperationCallbackAddressUsVariant7[];
extern char g_PlayerStateNoOperationCallbackAddressUsVariant8[];
extern char g_PlayerStateNoOperationCallbackAddressUsVariant9[];
extern char g_PlayerTrackNearbyAimTargetCallbackAddressUs[];
extern char g_PlayerUpdateHeldActorReleaseCallbackAddressUs[];
extern char g_PlayerUpdateRunEndCameraCallbackAddressUs[];
extern char g_PlayerUpdateRunEndSequenceCallbackAddressUs[];
extern char g_PlayerUpdateViewAnglesCallbackAddressUs[];
extern char g_Player_AbsorbImpactAddress[];
extern char g_Player_AimPreviousPositionAtResetAddress[];
extern char g_Player_BeginJumpAddress[];
extern char g_Player_BeginLateralLeapAddress[];
extern char g_Player_ClearGlobalFlagBitAddress[];
extern char g_Player_DampMotionAddress[];
extern char g_Player_ResetMovementInputCallbackAddressUs[];
extern char g_Player_ResetObjectVelocityAddress[];
extern char g_Player_ResetStunAndReleaseHandlesAddress[];
extern char g_Player_ResetStunFlagsAddress[];
extern char g_Player_StartMovingOnStickInputAddress[];
extern char g_Player_UpdateFloatPoseAddress[];
extern char g_Player_UpdateFloatingStateAddress[];
extern char g_Player_UpdateFlyModeAddress[];
extern char g_Player_UpdateGroundMoveStateAddress[];
extern char g_Player_UpdateJumpAirMotionAddress[];
extern char g_Player_UpdateJumpAscentAddress[];
extern char g_Player_UpdateLateralLeapAddress[];
extern char g_Player_UpdateLeapMotionAddress[];
extern char g_Player_UpdateStandingStateAddress[];
extern char g_Player_UpdateSwimmingStateAddress[];
extern char g_Player_UpdateWadingStateAddress[];
extern char g_Player_ZeroBodyVelocityAddress[];
extern char g_Playerai_ClearPlayerWeaponLockAddress[];
extern char g_Playerai_EnterMovingSequenceStateCallbackAddressUs[];
extern char g_Playerai_EnterStoppedSequenceStateCallbackAddressUs[];
extern char g_Playerai_InitializeActorModelEffectCallbackAddressUs[];
extern char g_Playerai_OffsetActorForState15Address[];
extern char g_Playerai_ResetPlayerAfterDeathAddress[];
extern char g_Playerai_ResetPlayerWeaponLockAddress[];
extern char g_Playerai_StartPlayerSequence60Address[];
extern char g_Playerai_StartPlayerSequence71CallbackAddressUs[];
extern char g_Playerai_StartPlayerSequence72CallbackAddressUs[];
extern char g_Playerai_StartPlayerSequence73CallbackAddressUs[];
extern char g_Playerai_StartPlayerSequence74CallbackAddressUs[];
extern char g_Playerai_UpdateSequence60RunEndPoseCallbackAddressUs[];
extern char g_Playerai_UpdateSequence71RunEndPoseCallbackAddressUs[];
extern char g_Playerai_UpdateSequence72RunEndPoseCallbackAddressUs[];
extern char g_Playerai_UpdateSequence73RunEndPoseCallbackAddressUs[];
extern char g_Playerai_UpdateSequence74RunEndPoseCallbackAddressUs[];
extern char g_Playerai_UpdateWalkingMovementAddress[];
extern char g_collisionSurfaceExcludedFromTrace[];
extern char g_defaultActorCollisionInfo[];
extern char g_globalGameplayFlags[];
extern u16 g_pagerPageCounters[];
extern char g_particleOwnerEffectFlags[];
extern char g_portalDefaultCollisionQuery[];
extern char g_secondaryCollisionContext[];
#include "include_asm.h"
#include "TYPES.H"
#if defined(VERSION_US)
/* SceneEffectMaximumColorUsRev1.CPP */
/* PlayerActionStateTableUs.CPP */
extern char g_Player_UpdateFlyModeAddress[];
extern char g_Player_UpdateStandingStateAddress[];
extern char g_Playerai_UpdateWalkingMovementAddress[];
extern char g_Player_UpdateWadingStateAddress[];
extern char g_Player_UpdateFloatingStateAddress[];
extern char g_Player_UpdateSwimmingStateAddress[];
extern char g_Playerai_ResetPlayerAfterDeathAddress[];
extern char g_PlayerInterpolateTravelTargetCallbackAddressUs[];
extern char g_PlayerUpdateHeldActorReleaseCallbackAddressUs[];
extern char g_PlayerTrackNearbyAimTargetCallbackAddressUs[];
extern char g_Player_ZeroBodyVelocityAddress[];
extern char g_Player_StartMovingOnStickInputAddress[];
extern char g_PlayerStateNoOperationCallbackAddressUs[];
extern char g_PlayerStateNoOperationCallbackAddressUsVariant2[];
extern char g_Player_UpdateGroundMoveStateAddress[];
extern char g_Player_BeginJumpAddress[];
extern char g_Player_UpdateJumpAscentAddress[];
extern char g_Player_UpdateJumpAirMotionAddress[];
extern char g_Player_BeginLateralLeapAddress[];
extern char g_Player_UpdateLateralLeapAddress[];
extern char g_Player_UpdateLeapMotionAddress[];
extern char g_Player_ClearGlobalFlagBitAddress[];
extern char g_Player_AbsorbImpactAddress[];
extern char g_Player_DampMotionAddress[];
extern char g_Player_UpdateFloatPoseAddress[];
extern char g_Player_ResetMovementInputCallbackAddressUs[];
extern char g_Player_ResetObjectVelocityAddress[];
extern char g_PlayerStateNoOperationCallbackAddressUsVariant3[];
extern char g_PlayerStateNoOperationCallbackAddressUsVariant4[];
extern char g_Player_AimPreviousPositionAtResetAddress[];
extern char g_PlayerStateNoOperationCallbackAddressUsVariant5[];
extern char g_Player_ResetStunAndReleaseHandlesAddress[];
extern char g_Player_ResetStunFlagsAddress[];
extern char g_PlayerStateNoOperationCallbackAddressUsVariant6[];
extern char g_PlayerResetStunAndMotionCallbackAddressUs[];
extern char g_PlayerEnterRunEndWaitCallbackAddressUs[];
extern char g_PlayerStateNoOperationCallbackAddressUsVariant7[];
extern char g_PlayerStateNoOperationCallbackAddressUsVariant8[];
extern char g_PlayerUpdateViewAnglesCallbackAddressUs[];
extern char g_PlayerStateNoOperationCallbackAddressUsVariant9[];
extern char g_PlayerUpdateRunEndCameraCallbackAddressUs[];
extern char g_PlayerStateNoOperationCallbackAddressUsVariant10[];
extern char g_PlayerStateNoOperationCallbackAddressUsVariant11[];
extern char g_PlayerSetSequenceFlag20CallbackAddressUs[];
extern char g_PlayerUpdateRunEndSequenceCallbackAddressUs[];
extern char g_PlayerRequestCinemaTrackCallbackAddressUs[];
extern char g_PlayerSequence10StartCallbackAddressUs[];
extern char g_PlayerSequenceRunEndUpdateCallbackAddressUs[];
extern char g_PlayerSequence50StartCallbackAddressUs[];
extern char g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant2[];
extern char g_PlayerSequence30StartCallbackAddressUs[];
extern char g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant3[];
extern char g_PlayerSequence40StartCallbackAddressUs[];
extern char g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant4[];
extern char g_PlayerSequence11StartCallbackAddressUs[];
extern char g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant5[];
extern char g_PlayerSequence12StartCallbackAddressUs[];
extern char g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant6[];
extern char g_PlayerSequence13StartCallbackAddressUs[];
extern char g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant7[];
extern char g_PlayerSequence14StartCallbackAddressUs[];
extern char g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant8[];
extern char g_PlayerSequence15StartCallbackAddressUs[];
extern char g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant9[];
extern char g_PlayerSequence20StartCallbackAddressUs[];
extern char g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant10[];
extern char g_PlayerSequence70StartCallbackAddressUs[];
extern char g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant11[];
extern char g_Playerai_StartPlayerSequence60Address[];
extern char g_Playerai_UpdateSequence60RunEndPoseCallbackAddressUs[];
extern char g_Playerai_StartPlayerSequence71CallbackAddressUs[];
extern char g_Playerai_UpdateSequence71RunEndPoseCallbackAddressUs[];
extern char g_Playerai_StartPlayerSequence72CallbackAddressUs[];
extern char g_Playerai_UpdateSequence72RunEndPoseCallbackAddressUs[];
extern char g_Playerai_StartPlayerSequence73CallbackAddressUs[];
extern char g_Playerai_UpdateSequence73RunEndPoseCallbackAddressUs[];
extern char g_Playerai_StartPlayerSequence74CallbackAddressUs[];
extern char g_Playerai_UpdateSequence74RunEndPoseCallbackAddressUs[];
extern char g_Playerai_InitializeActorModelEffectCallbackAddressUs[];
extern char g_Playerai_ClearPlayerWeaponLockAddress[];
extern char g_Playerai_EnterMovingSequenceStateCallbackAddressUs[];
extern char g_Playerai_ResetPlayerWeaponLockAddress[];
extern char g_Playerai_EnterStoppedSequenceStateCallbackAddressUs[];
extern char g_Playerai_OffsetActorForState15Address[];
RestplayerActionStateTableWordsUsLayout362 g_playerActionStateTableWordsUs = {
    1,
    { 0.4f, 0.5f, 1.0f, 0.25f, -1.5707965f, 1.5707965f, 0.2f, 0.25f, 0.5f, 0.125f, -1.5707965f, 1.5707965f, 1.024f, 7.68f, 0.512f, 10.24f, 0.768f, 10.24f, 76.799995f, 51.199997f, 0.0f },
    { (void *)&g_Player_ZeroBodyVelocityAddress, (void *)&g_Player_UpdateFlyModeAddress, (void *)((char *)&g_secondaryCollisionContext + 192), 0 },
    { 1, 131072, 0 },
    { (void *)&g_Player_UpdateFlyModeAddress, (void *)((char *)&g_secondaryCollisionContext + 192), 0 },
    { 1, 131072 },
    { (void *)&g_Player_StartMovingOnStickInputAddress, (void *)&g_Player_UpdateStandingStateAddress, (void *)((char *)&g_secondaryCollisionContext + 32), 0 },
    { 1, 131072 },
    { (void *)&g_PlayerStateNoOperationCallbackAddressUs, (void *)&g_Playerai_UpdateWalkingMovementAddress, (void *)((char *)&g_secondaryCollisionContext + 32), 0 },
    { 2010, 196608 },
    { (void *)&g_PlayerStateNoOperationCallbackAddressUsVariant2, (void *)&g_Player_UpdateGroundMoveStateAddress, (void *)((char *)&g_secondaryCollisionContext + 32), 0 },
    { 2660, 196608 },
    { (void *)&g_Player_BeginJumpAddress, (void *)&g_Player_UpdateJumpAscentAddress, (void *)((char *)&g_collisionSurfaceExcludedFromTrace + 32) },
    { 2048, 2030, 131072, 0 },
    { (void *)&g_Player_UpdateJumpAirMotionAddress, (void *)((char *)&g_collisionSurfaceExcludedFromTrace + 32) },
    { 2048, 2030, 131072 },
    { (void *)&g_Player_BeginLateralLeapAddress, (void *)&g_Player_UpdateLateralLeapAddress, (void *)((char *)&g_secondaryCollisionContext + 32), 0 },
    { 2030, 131072, 0 },
    { (void *)&g_Player_UpdateLeapMotionAddress, (void *)((char *)&g_secondaryCollisionContext + 32), 0 },
    { 2030, 131072 },
    { (void *)&g_Player_ClearGlobalFlagBitAddress, (void *)&g_Player_UpdateWadingStateAddress, (void *)&g_globalGameplayFlags },
    { 128, 2210, 131072 },
    { (void *)&g_Player_ClearGlobalFlagBitAddress, (void *)&g_Player_UpdateWadingStateAddress, (void *)&g_globalGameplayFlags },
    { 128, 2210, 196608 },
    { (void *)&g_Player_AbsorbImpactAddress, (void *)&g_Player_UpdateFloatingStateAddress, (void *)((char *)&g_pagerPageCounters + 16) },
    { 64, 2210, 131072 },
    { (void *)&g_Player_AbsorbImpactAddress, (void *)&g_Player_UpdateFloatingStateAddress, (void *)((char *)&g_pagerPageCounters + 16) },
    { 64, 2210, 196608 },
    { (void *)&g_Player_DampMotionAddress, (void *)&g_Player_UpdateFloatPoseAddress, (void *)((char *)&g_collisionSurfaceExcludedFromTrace + 64), 0 },
    { 2010, 131072 },
    { (void *)&g_Player_DampMotionAddress, (void *)&g_Player_UpdateFloatPoseAddress, (void *)((char *)&g_collisionSurfaceExcludedFromTrace + 64), 0 },
    { 2010, 131072 },
    { (void *)&g_Player_ResetMovementInputCallbackAddressUs, (void *)&g_Player_UpdateSwimmingStateAddress, (void *)((char *)&PAKInterface_LoadGame + 28) },
    { 256, 2620, 131072 },
    { (void *)&g_Player_ResetObjectVelocityAddress, (void *)&g_PlayerStateNoOperationCallbackAddressUsVariant3, (void *)((char *)&g_secondaryCollisionContext + 32) },
    { 524288, 1, 131072 },
    { (void *)&g_PlayerStateNoOperationCallbackAddressUsVariant4, (void *)&g_Player_AimPreviousPositionAtResetAddress, (void *)((char *)&g_secondaryCollisionContext + 192) },
    { 1048576, 1, 131072 },
    { (void *)&g_Playerai_ResetPlayerAfterDeathAddress, (void *)&g_PlayerStateNoOperationCallbackAddressUsVariant5, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 0 },
    65536,
    { (void *)&g_Player_ResetStunAndReleaseHandlesAddress, 0, (void *)&g_defaultActorCollisionInfo, 0, 0 },
    65536,
    { (void *)&g_Player_ResetStunFlagsAddress, (void *)&g_PlayerStateNoOperationCallbackAddressUsVariant6, (void *)&g_defaultActorCollisionInfo, 0, 0 },
    65536,
    { (void *)&g_PlayerResetStunAndMotionCallbackAddressUs, (void *)&g_PlayerEnterRunEndWaitCallbackAddressUs, (void *)&g_defaultActorCollisionInfo, 0, 0 },
    65536,
    { (void *)&g_PlayerSequence10StartCallbackAddressUs, (void *)&g_PlayerSequenceRunEndUpdateCallbackAddressUs, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7000, 65536 },
    { (void *)&g_PlayerSequence30StartCallbackAddressUs, (void *)&g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant3, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7100, 65536 },
    { (void *)&g_PlayerSequence70StartCallbackAddressUs, (void *)&g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant11, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7101, 65536 },
    { (void *)&g_PlayerSequence11StartCallbackAddressUs, (void *)&g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant5, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7200, 65536 },
    { (void *)&g_Playerai_StartPlayerSequence60Address, (void *)&g_Playerai_UpdateSequence60RunEndPoseCallbackAddressUs, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7201, 65536 },
    { (void *)&g_PlayerSequence40StartCallbackAddressUs, (void *)&g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant4, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7400, 65536 },
    { (void *)&g_PlayerSequence12StartCallbackAddressUs, (void *)&g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant6, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7005, 65536 },
    { (void *)&g_PlayerSequence13StartCallbackAddressUs, (void *)&g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant7, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7500, 65536 },
    { (void *)&g_PlayerSequence14StartCallbackAddressUs, (void *)&g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant8, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7505, 65536 },
    { (void *)&g_PlayerSequence50StartCallbackAddressUs, (void *)&g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant2, (void *)((char *)&PAKInterface_LoadGame + 124), 0 },
    { 7020, 65536 },
    { (void *)&g_PlayerSequence20StartCallbackAddressUs, (void *)&g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant10, (void *)((char *)&PAKInterface_LoadGame + 124), 0 },
    { 7010, 65536 },
    { (void *)&g_PlayerSequence15StartCallbackAddressUs, (void *)&g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant9, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7004, 65536 },
    { (void *)&g_PlayerRequestCinemaTrackCallbackAddressUs, 0, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 0 },
    65536,
    { (void *)&g_Playerai_InitializeActorModelEffectCallbackAddressUs, (void *)&g_PlayerInterpolateTravelTargetCallbackAddressUs, (void *)((char *)&g_collisionSurfaceExcludedFromTrace + 64), 0 },
    { 2030, 65536 },
    { (void *)&g_Playerai_ClearPlayerWeaponLockAddress, (void *)&g_Playerai_EnterMovingSequenceStateCallbackAddressUs, (void *)((char *)&g_portalDefaultCollisionQuery + 32) },
    { 32768, 2010, 131072 },
    { (void *)&g_Playerai_ResetPlayerWeaponLockAddress, (void *)&g_Playerai_EnterStoppedSequenceStateCallbackAddressUs, (void *)((char *)&g_portalDefaultCollisionQuery + 32) },
    { 32768, 2010, 196608 },
    { (void *)&g_Playerai_OffsetActorForState15Address, (void *)&g_PlayerUpdateHeldActorReleaseCallbackAddressUs, (void *)((char *)&g_secondaryCollisionContext + 32), 0 },
    { 9200, 131072 },
    { (void *)&g_PlayerStateNoOperationCallbackAddressUsVariant7, (void *)&g_PlayerTrackNearbyAimTargetCallbackAddressUs, (void *)((char *)&g_secondaryCollisionContext + 32), 0 },
    { 1, 131072 },
    { (void *)&g_PlayerStateNoOperationCallbackAddressUsVariant8, (void *)&g_PlayerUpdateViewAnglesCallbackAddressUs, (void *)((char *)&g_secondaryCollisionContext + 32), 0 },
    { 1, 131072 },
    { (void *)&g_Playerai_StartPlayerSequence71CallbackAddressUs, (void *)&g_Playerai_UpdateSequence71RunEndPoseCallbackAddressUs, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7043, 65536 },
    { (void *)&g_Playerai_StartPlayerSequence72CallbackAddressUs, (void *)&g_Playerai_UpdateSequence72RunEndPoseCallbackAddressUs, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7044, 65536 },
    { (void *)&g_Playerai_StartPlayerSequence73CallbackAddressUs, (void *)&g_Playerai_UpdateSequence73RunEndPoseCallbackAddressUs, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7045, 65536 },
    { (void *)&g_Playerai_StartPlayerSequence74CallbackAddressUs, (void *)&g_Playerai_UpdateSequence74RunEndPoseCallbackAddressUs, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7046, 65536 },
    { (void *)&g_PlayerStateNoOperationCallbackAddressUsVariant10, (void *)&g_PlayerStateNoOperationCallbackAddressUsVariant11, (void *)((char *)&g_secondaryCollisionContext + 32), 0 },
    { 23300, 131072 },
    { (void *)&g_PlayerSetSequenceFlag20CallbackAddressUs, (void *)&g_PlayerUpdateRunEndSequenceCallbackAddressUs, (void *)((char *)&g_secondaryCollisionContext + 32), 0 },
    { 23301, 131072 },
    { (void *)&g_Player_ZeroBodyVelocityAddress, (void *)&g_Player_UpdateFlyModeAddress, (void *)((char *)&g_secondaryCollisionContext + 192), 0 },
    { 1, 131072, 0 },
    { (void *)&g_Player_UpdateFlyModeAddress, (void *)((char *)&g_secondaryCollisionContext + 192), 0 },
    { 1, 131072 },
    { (void *)&g_Player_StartMovingOnStickInputAddress, (void *)&g_Player_UpdateStandingStateAddress, (void *)((char *)&g_secondaryCollisionContext + 32), 0 },
    { 24100, 131072 },
    { (void *)&g_PlayerStateNoOperationCallbackAddressUs, (void *)&g_Playerai_UpdateWalkingMovementAddress, (void *)((char *)&g_secondaryCollisionContext + 32), 0 },
    { 24105, 196608 },
    { (void *)&g_PlayerStateNoOperationCallbackAddressUsVariant2, (void *)&g_Player_UpdateGroundMoveStateAddress, (void *)((char *)&g_secondaryCollisionContext + 32), 0 },
    { 2660, 196608 },
    { (void *)&g_Player_BeginJumpAddress, (void *)&g_Player_UpdateJumpAscentAddress, (void *)((char *)&g_collisionSurfaceExcludedFromTrace + 32) },
    { 2048, 24109, 131072, 0 },
    { (void *)&g_Player_UpdateJumpAirMotionAddress, (void *)((char *)&g_collisionSurfaceExcludedFromTrace + 32) },
    { 2048, 24109, 131072 },
    { (void *)&g_Player_BeginLateralLeapAddress, (void *)&g_Player_UpdateLateralLeapAddress, (void *)((char *)&g_secondaryCollisionContext + 32), 0 },
    { 24109, 131072, 0 },
    { (void *)&g_Player_UpdateLeapMotionAddress, (void *)((char *)&g_secondaryCollisionContext + 32), 0 },
    { 24109, 131072 },
    { (void *)&g_Player_ClearGlobalFlagBitAddress, (void *)&g_Player_UpdateWadingStateAddress, (void *)&g_globalGameplayFlags },
    { 128, 2210, 131072 },
    { (void *)&g_Player_ClearGlobalFlagBitAddress, (void *)&g_Player_UpdateWadingStateAddress, (void *)&g_globalGameplayFlags },
    { 128, 2210, 196608 },
    { (void *)&g_Player_AbsorbImpactAddress, (void *)&g_Player_UpdateFloatingStateAddress, (void *)((char *)&g_pagerPageCounters + 16) },
    { 64, 2210, 131072 },
    { (void *)&g_Player_AbsorbImpactAddress, (void *)&g_Player_UpdateFloatingStateAddress, (void *)((char *)&g_pagerPageCounters + 16) },
    { 64, 2210, 196608 },
    { (void *)&g_Player_DampMotionAddress, (void *)&g_Player_UpdateFloatPoseAddress, (void *)((char *)&g_collisionSurfaceExcludedFromTrace + 64), 0 },
    { 24105, 131072 },
    { (void *)&g_Player_DampMotionAddress, (void *)&g_Player_UpdateFloatPoseAddress, (void *)((char *)&g_collisionSurfaceExcludedFromTrace + 64), 0 },
    { 24105, 131072 },
    { (void *)&g_Player_ResetMovementInputCallbackAddressUs, (void *)&g_Player_UpdateSwimmingStateAddress, (void *)((char *)&PAKInterface_LoadGame + 28) },
    { 256, 24104, 131072 },
    { (void *)&g_Player_ResetObjectVelocityAddress, (void *)&g_PlayerStateNoOperationCallbackAddressUsVariant3, (void *)((char *)&g_secondaryCollisionContext + 32) },
    { 524288, 24100, 131072 },
    { (void *)&g_PlayerStateNoOperationCallbackAddressUsVariant4, (void *)&g_Player_AimPreviousPositionAtResetAddress, (void *)((char *)&g_secondaryCollisionContext + 192) },
    { 1048576, 24100, 131072 },
    { (void *)&g_Playerai_ResetPlayerAfterDeathAddress, (void *)&g_PlayerStateNoOperationCallbackAddressUsVariant5, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 0 },
    65536,
    { (void *)&g_Player_ResetStunAndReleaseHandlesAddress, 0, (void *)&g_defaultActorCollisionInfo, 0, 0 },
    65536,
    { (void *)&g_Player_ResetStunFlagsAddress, (void *)&g_PlayerStateNoOperationCallbackAddressUsVariant6, (void *)&g_defaultActorCollisionInfo, 0, 0 },
    65536,
    { (void *)&g_PlayerResetStunAndMotionCallbackAddressUs, (void *)&g_PlayerEnterRunEndWaitCallbackAddressUs, (void *)&g_defaultActorCollisionInfo, 0, 0 },
    65536,
    { (void *)&g_PlayerSequence10StartCallbackAddressUs, (void *)&g_PlayerSequenceRunEndUpdateCallbackAddressUs, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7000, 65536 },
    { (void *)&g_PlayerSequence30StartCallbackAddressUs, (void *)&g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant3, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7100, 65536 },
    { (void *)&g_PlayerSequence70StartCallbackAddressUs, (void *)&g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant11, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7101, 65536 },
    { (void *)&g_PlayerSequence11StartCallbackAddressUs, (void *)&g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant5, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7200, 65536 },
    { (void *)&g_Playerai_StartPlayerSequence60Address, (void *)&g_Playerai_UpdateSequence60RunEndPoseCallbackAddressUs, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7201, 65536 },
    { (void *)&g_PlayerSequence40StartCallbackAddressUs, (void *)&g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant4, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7400, 65536 },
    { (void *)&g_PlayerSequence12StartCallbackAddressUs, (void *)&g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant6, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7005, 65536 },
    { (void *)&g_PlayerSequence13StartCallbackAddressUs, (void *)&g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant7, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7500, 65536 },
    { (void *)&g_PlayerSequence14StartCallbackAddressUs, (void *)&g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant8, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7505, 65536 },
    { (void *)&g_PlayerSequence50StartCallbackAddressUs, (void *)&g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant2, (void *)((char *)&PAKInterface_LoadGame + 124), 0 },
    { 7020, 65536 },
    { (void *)&g_PlayerSequence20StartCallbackAddressUs, (void *)&g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant10, (void *)((char *)&PAKInterface_LoadGame + 124), 0 },
    { 7010, 65536 },
    { (void *)&g_PlayerSequence15StartCallbackAddressUs, (void *)&g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant9, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7011, 65536 },
    { (void *)&g_PlayerRequestCinemaTrackCallbackAddressUs, 0, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 0 },
    65536,
    { (void *)&g_Playerai_InitializeActorModelEffectCallbackAddressUs, (void *)&g_PlayerInterpolateTravelTargetCallbackAddressUs, (void *)((char *)&g_collisionSurfaceExcludedFromTrace + 64), 0 },
    { 24109, 65536 },
    { (void *)&g_Playerai_ClearPlayerWeaponLockAddress, (void *)&g_Playerai_EnterMovingSequenceStateCallbackAddressUs, (void *)((char *)&g_portalDefaultCollisionQuery + 32) },
    { 32768, 24105, 131072 },
    { (void *)&g_Playerai_ResetPlayerWeaponLockAddress, (void *)&g_Playerai_EnterStoppedSequenceStateCallbackAddressUs, (void *)((char *)&g_portalDefaultCollisionQuery + 32) },
    { 32768, 24105, 196608 },
    { (void *)&g_Playerai_OffsetActorForState15Address, (void *)&g_PlayerUpdateHeldActorReleaseCallbackAddressUs, (void *)((char *)&g_secondaryCollisionContext + 32), 0 },
    { 9200, 131072 },
    { (void *)&g_PlayerStateNoOperationCallbackAddressUsVariant7, (void *)&g_PlayerTrackNearbyAimTargetCallbackAddressUs, (void *)((char *)&g_secondaryCollisionContext + 32), 0 },
    { 24100, 131072 },
    { (void *)&g_PlayerStateNoOperationCallbackAddressUsVariant8, (void *)&g_PlayerUpdateViewAnglesCallbackAddressUs, (void *)((char *)&g_secondaryCollisionContext + 32), 0 },
    { 24100, 131072 },
    { (void *)&g_PlayerStateNoOperationCallbackAddressUsVariant9, (void *)&g_PlayerUpdateRunEndCameraCallbackAddressUs, (void *)((char *)&g_secondaryCollisionContext + 32), 0 },
    { 7043, 131072 },
    { (void *)&g_Playerai_StartPlayerSequence72CallbackAddressUs, (void *)&g_Playerai_UpdateSequence72RunEndPoseCallbackAddressUs, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7044, 65536 },
    { (void *)&g_Playerai_StartPlayerSequence73CallbackAddressUs, (void *)&g_Playerai_UpdateSequence73RunEndPoseCallbackAddressUs, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7045, 65536 },
    { (void *)&g_Playerai_StartPlayerSequence74CallbackAddressUs, (void *)&g_Playerai_UpdateSequence74RunEndPoseCallbackAddressUs, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0 },
    { 7046, 65536 },
    { (void *)&g_PlayerStateNoOperationCallbackAddressUsVariant10, (void *)&g_PlayerStateNoOperationCallbackAddressUsVariant11, (void *)((char *)&g_secondaryCollisionContext + 32), 0 },
    { 23300, 131072 },
    { (void *)&g_PlayerSetSequenceFlag20CallbackAddressUs, (void *)&g_PlayerUpdateRunEndSequenceCallbackAddressUs, (void *)((char *)&g_secondaryCollisionContext + 32), 0 },
    { 23301, 131072, 299 },
    0x012B012B,
    0x012B012B,
    0x012B012B,
    0x012B012B,
    0x012B0000,
    -0.25f,
};
#endif
