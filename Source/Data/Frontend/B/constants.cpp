#include "include_asm.h"
#include "Data/rest_source_records.h"
#include "Common/runtime_declarations.h"
#include "Common/effectrender.h"
#include "Frontend/frontend_data_address_symbols.h"

/* OVLSCENE_LOADSCENERESOURCES_DATA.CPP */
#if defined(VERSION_DE)
const unsigned char s_sceneResourceIndexTagsDe[29] = {
    0x63, 0x61, 0x72, 0x74, 0x72, 0x69, 0x64, 0x67, 0x65, 0x20, 0x69, 0x6E, 0x64, 0x65, 0x78, 0x00,
    0x6C, 0x65, 0x76, 0x65, 0x6C, 0x73, 0x20, 0x69, 0x6E, 0x64, 0x65, 0x78, 0x00,
};
#endif

/* SCENE_EFFECT_TUNING_DE.CPP */
#if defined(VERSION_DE)
extern SceneEffectTuningDeLayout g_sceneEffectTuningDe;
#endif

/* PLAYER_ACTION_TABLE_DE.CPP */
#if defined(VERSION_DE)
SceneEffectTuningUsRev1Layout g_sceneEffectTuningUsRevision = {
    { 1.7280002f, 2.7648f, 20.736f, 1.0368001f, 0.0f, 0.0f, 0.0f, 2.88f, 21.599998f, 1.08f, 1.7280002f, 12.960001f, 0.64800006f, 0.0f, 0.0f, 0.0f, 10.24f, 30.72f, 13.44f, 10.24f, 35.84f, 13.44f, 0.0f, 0.0f, 0.0f, 5.12f, 15.36f, 3.84f, 5.12f, 17.92f, 3.84f, 0.0f, 0.0f, 0.0f, 0.25f, 0.9f, 0.6f, 0.3f, -1.5707965f, 1.5707965f, 0.25f, 0.9f, 0.6f, 0.3f, -0.78539824f, 1.5707965f, 0.0f, 0.0f, 0.5f, 0.25f, -0.06981318f, 1.5707965f, 7.68f, 23.039999f, 5.7599998f, 7.68f, 26.880001f, 5.7599998f, 10.24f, 0.768f },
    1,
    { 2.048f, 15.36f, 1.024f, 20.48f, 1.536f, 20.48f, 153.59999f, 102.399994f },
    {
    1,
    { 0.4f, 0.5f, 1.0f, 0.25f, -1.5707965f, 1.5707965f, 0.2f, 0.25f, 0.5f, 0.125f, -1.5707965f, 1.5707965f, 1.024f, 7.68f, 0.512f, 10.24f, 0.768f, 10.24f, 76.799995f, 51.199997f, 0.0f },
    {
        { (void *)&g_Player_ZeroBodyVelocityCallbackAddressDe, (void *)&g_Player_UpdateFlyModeAddress_de, (void *)&g_secondaryCollisionContext[6], 0, 1, 131072 },
        { 0, (void *)&g_Player_UpdateFlyModeAddress_de, (void *)&g_secondaryCollisionContext[6], 0, 1, 131072 },
        { (void *)&g_Player_StartMovingOnStickInputAddress_de, (void *)&g_Player_UpdateStandingStateAddress_de, (void *)&g_secondaryCollisionContext[1], 0, 1, 131072 },
        { (void *)&g_Player_UpdateGroundMoveStateAddress_de_us_rev1, (void *)&g_Playerai_UpdateWalkingMovementAddress_de, (void *)&g_secondaryCollisionContext[32], 0, 2010, 196608 },
        { (void *)&g_PlayerStateNoOperationCallbackAddressDe, (void *)&addrLow_Player_UpdateGroundMoveState_de, (void *)&g_secondaryCollisionContext[1], 0, 2660, 196608 },
        { (void *)&g_Player_BeginJumpAddress_de, (void *)&g_Player_UpdateJumpAscentAddress_de, (void *)&g_collisionSurfaceExcludedFromTrace[32], 2048, 2030, 131072 },
        { 0, (void *)&g_Player_UpdateJumpAirMotionAddress_de, (void *)&g_collisionSurfaceExcludedFromTrace[32], 2048, 2030, 131072 },
        { (void *)&g_Player_BeginLateralLeapAddress_de, (void *)&g_Player_UpdateLateralLeapAddress_de, (void *)&g_secondaryCollisionContext[1], 0, 2030, 131072 },
        { 0, (void *)&g_Player_UpdateLeapMotionAddress_de, (void *)&g_secondaryCollisionContext[1], 0, 2030, 131072 },
        { (void *)&g_Player_ClearGlobalFlagBitAddress_de, (void *)&g_Player_UpdateWadingStateAddress_de, (void *)&g_globalGameplayFlags, 128, 2210, 131072 },
        { (void *)&g_Player_ClearGlobalFlagBitAddress_de, (void *)&g_Player_UpdateWadingStateAddress_de, (void *)&g_globalGameplayFlags, 128, 2210, 196608 },
        { (void *)&g_Player_AbsorbImpactAddress_de, (void *)&g_Player_UpdateFloatingStateAddress_de, (void *)&g_pagerPageCounters[8], 64, 2210, 131072 },
        { (void *)&g_Player_AbsorbImpactAddress_de, (void *)&g_Player_UpdateFloatingStateAddress_de, (void *)&g_pagerPageCounters[8], 64, 2210, 196608 },
        { (void *)&g_Player_DampMotionCallbackAddressDe, (void *)&g_Player_UpdateFloatPoseAddress_de, (void *)&g_collisionSurfaceExcludedFromTrace[64], 0, 2010, 131072 },
        { (void *)&g_Player_DampMotionCallbackAddressDe, (void *)&g_Player_UpdateFloatPoseAddress_de, (void *)&g_collisionSurfaceExcludedFromTrace[64], 0, 2010, 131072 },
        { (void *)&g_Player_ResetMovementInputCallbackAddressDe, (void *)&g_Player_UpdateSwimmingStateAddress_de, (void *)&g_supportingPlatformCollisionQuery[1].info, 256, 2620, 131072 },
        { (void *)&g_Player_ResetObjectVelocityAddress_de_us_rev1, (void *)&g_Player_AimPreviousPositionAtResetAddress_de_us_rev1, (void *)&g_secondaryCollisionContext[32], 524288, 1, 131072 },
        { (void *)&g_playerStateNoOperationCallbackWords[0x236], (void *)&addrLow_Player_AimPreviousPositionAtReset_de, (void *)&g_secondaryCollisionContext[6], 1048576, 1, 131072 },
        { (void *)&g_Playerai_ResetPlayerAfterDeathAddress_de, (void *)&g_playerStateNoOperationCallbackWords[0x251], (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 0, 65536 },
        { (void *)&g_Player_ResetStunAndReleaseHandlesAddress_de, 0, (void *)&g_defaultActorCollisionInfo, 0, 0, 65536 },
        { (void *)&g_playerStateNoOperationCallbackWords[0x265], (void *)&g_Player_ResetMovementInputAddress, (void *)&g_defaultActorCollisionInfo, 0, 0, 65536 },
        { (void *)&g_PlayerResetStunAndMotionCallbackAddressDe, (void *)&g_PlayerEnterRunEndWaitCallbackAddressDe, (void *)&g_defaultActorCollisionInfo, 0, 0, 65536 },
        { (void *)&addrLow_Playerai_StartGroundDeathSequence_de, (void *)&addrLow_Playerai_UpdateGroundDeathSequenceWait_de, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7000, 65536 },
        { (void *)&addrLow_Playerai_StartQuicksandDeathSequence_de, (void *)g_playerSequenceRunEndUpdateCallbackRecords[1], (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7100, 65536 },
        { (void *)&addrLow_Playerai_StartPrimagenDeathSequence_de, (void *)g_playerSequenceRunEndUpdateCallbackRecords[9], (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7101, 65536 },
        { (void *)&addrLow_Playerai_StartExplosiveDeathSequence_de, (void *)g_playerSequenceRunEndUpdateCallbackRecords[3], (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7200, 65536 },
        { (void *)&addrLow_Playerai_StartImpalementDeathSequence_de, (void *)&addrLow_Playerai_UpdateImpalementDeathSequenceWait_de, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7201, 65536 },
        { (void *)&addrLow_Playerai_StartLavaDeathSequence_de, (void *)g_playerSequenceRunEndUpdateCallbackRecords[2], (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7400, 65536 },
        { (void *)&addrLow_Playerai_StartDisabledCrawlDeathSequence_de, (void *)g_playerSequenceRunEndUpdateCallbackRecords[4], (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7005, 65536 },
        { (void *)&addrLow_Playerai_StartRunningDeathSequence_de, (void *)g_playerSequenceRunEndUpdateCallbackRecords[5], (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7500, 65536 },
        { (void *)&addrLow_Playerai_StartBackwardMovingDeathSequence_de, (void *)g_playerSequenceRunEndUpdateCallbackRecords[6], (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7505, 65536 },
        { (void *)&addrLow_Playerai_StartViewSavingDrowningDeathSequence_de, (void *)g_playerSequenceRunEndUpdateCallbackRecords[0], (void *)((char *)&g_supportingPlatformCollisionQuery + 128), 0, 7020, 65536 },
        { (void *)&addrLow_Playerai_StartFallingDeathSequence_de, (void *)g_playerSequenceRunEndUpdateCallbackRecords[8], (void *)((char *)&g_supportingPlatformCollisionQuery + 128), 0, 7010, 65536 },
        { (void *)&addrLow_Playerai_StartClimbingDeathSequence_de, (void *)g_playerSequenceRunEndUpdateCallbackRecords[7], (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7004, 65536 },
        { (void *)&g_PlayerRequestCinemaTrackCallbackAddressDe, 0, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 0, 65536 },
        { (void *)&g_Playerai_InitializeActorModelEffectAddress, (void *)&g_PlayerInterpolateTravelTargetCallbackAddressDe, (void *)&g_collisionSurfaceExcludedFromTrace[64], 0, 2030, 65536 },
        { (void *)&g_Playerai_EnterMovingSequenceStateCallbackAddressUs, (void *)&g_Playerai_EnterMovingSequenceStateCallbackAddressDe, (void *)((char *)&g_portalDefaultCollisionQuery + 32), 32768, 2010, 131072 },
        { (void *)&g_Playerai_EnterStoppedSequenceStateCallbackAddressUs, (void *)&g_Playerai_EnterStoppedSequenceStateAddress, (void *)((char *)&g_portalDefaultCollisionQuery + 32), 32768, 2010, 196608 },
        { (void *)&addrLow_Playerai_OffsetActorForForceMarker_de, (void *)&g_PlayerUpdateHeldActorReleaseCallbackAddressDe, (void *)&g_secondaryCollisionContext[1], 0, 9200, 131072 },
        { (void *)&g_playerStateNoOperationCallbackWords[0x2C9], (void *)&g_PlayerTrackNearbyAimTargetCallbackAddressDe, (void *)&g_secondaryCollisionContext[1], 0, 1, 131072 },
        { (void *)&g_playerStateNoOperationCallbackWords[0x2CB], (void *)&g_PlayerUpdateRunEndCameraCallbackAddressUs, (void *)&g_secondaryCollisionContext[1], 0, 1, 131072 },
        { (void *)&addrLow_Playerai_StartChestbursterDeathSequence_de, (void *)&addrLow_Playerai_UpdateChestbursterDeathSequenceWait_de, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7043, 65536 },
        { (void *)&addrLow_Playerai_StartSwimmingChestbursterDeathSequence_de, (void *)&addrLow_Playerai_UpdateSwimmingChestbursterDeathSequenceWait_de, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7044, 65536 },
        { (void *)&addrLow_Playerai_StartRaptorChestbursterDeathSequence_de, (void *)&addrLow_Playerai_UpdateRaptorChestbursterDeathSequenceWait_de, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7045, 65536 },
        { (void *)&addrLow_Playerai_StartSwimmingRaptorChestbursterDeathSequence_de, (void *)&addrLow_Playerai_UpdateSwimmingRaptorChestbursterDeathSequenceWait_de, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7046, 65536 },
        { (void *)&g_playerStateNoOperationCallbackWords[0x2F5], (void *)&g_playerStateNoOperationCallbackWords[0x2F7], (void *)&g_secondaryCollisionContext[1], 0, 23300, 131072 },
        { (void *)&g_PlayerSetRunEndFlagCallbackAddressDe, (void *)&g_PlayerUpdateRunEndSequenceCallbackAddressDe, (void *)&g_secondaryCollisionContext[32], 0, 23301, 131072 },
        { (void *)&g_Player_ZeroBodyVelocityCallbackAddressDe, (void *)&g_Player_UpdateFlyModeAddress_de, (void *)&g_secondaryCollisionContext[6], 0, 1, 131072 },
        { 0, (void *)&g_Player_UpdateFlyModeAddress_de, (void *)&g_secondaryCollisionContext[6], 0, 1, 131072 },
        { (void *)&g_Player_StartMovingOnStickInputAddress_de, (void *)&g_Player_UpdateStandingStateAddress_de, (void *)&g_secondaryCollisionContext[1], 0, 24100, 131072 },
        { (void *)&g_Player_UpdateGroundMoveStateAddress_de_us_rev1, (void *)&g_Playerai_UpdateWalkingMovementAddress_de, (void *)&g_secondaryCollisionContext[32], 0, 24105, 196608 },
        { (void *)&g_PlayerStateNoOperationCallbackAddressDe, (void *)&addrLow_Player_UpdateGroundMoveState_de, (void *)&g_secondaryCollisionContext[1], 0, 2660, 196608 },
        { (void *)&g_Player_BeginJumpAddress_de, (void *)&g_Player_UpdateJumpAscentAddress_de, (void *)&g_collisionSurfaceExcludedFromTrace[32], 2048, 24109, 131072 },
        { 0, (void *)&g_Player_UpdateJumpAirMotionAddress_de, (void *)&g_collisionSurfaceExcludedFromTrace[32], 2048, 24109, 131072 },
        { (void *)&g_Player_BeginLateralLeapAddress_de, (void *)&g_Player_UpdateLateralLeapAddress_de, (void *)&g_secondaryCollisionContext[1], 0, 24109, 131072 },
        { 0, (void *)&g_Player_UpdateLeapMotionAddress_de, (void *)&g_secondaryCollisionContext[1], 0, 24109, 131072 },
        { (void *)&g_Player_ClearGlobalFlagBitAddress_de, (void *)&g_Player_UpdateWadingStateAddress_de, (void *)&g_globalGameplayFlags, 128, 2210, 131072 },
        { (void *)&g_Player_ClearGlobalFlagBitAddress_de, (void *)&g_Player_UpdateWadingStateAddress_de, (void *)&g_globalGameplayFlags, 128, 2210, 196608 },
        { (void *)&g_Player_AbsorbImpactAddress_de, (void *)&g_Player_UpdateFloatingStateAddress_de, (void *)&g_pagerPageCounters[8], 64, 2210, 131072 },
        { (void *)&g_Player_AbsorbImpactAddress_de, (void *)&g_Player_UpdateFloatingStateAddress_de, (void *)&g_pagerPageCounters[8], 64, 2210, 196608 },
        { (void *)&g_Player_DampMotionCallbackAddressDe, (void *)&g_Player_UpdateFloatPoseAddress_de, (void *)&g_collisionSurfaceExcludedFromTrace[64], 0, 24105, 131072 },
        { (void *)&g_Player_DampMotionCallbackAddressDe, (void *)&g_Player_UpdateFloatPoseAddress_de, (void *)&g_collisionSurfaceExcludedFromTrace[64], 0, 24105, 131072 },
        { (void *)&g_Player_ResetMovementInputCallbackAddressDe, (void *)&g_Player_UpdateSwimmingStateAddress_de, (void *)&g_supportingPlatformCollisionQuery[1].info, 256, 24104, 131072 },
        { (void *)&g_Player_ResetObjectVelocityAddress_de_us_rev1, (void *)&g_Player_AimPreviousPositionAtResetAddress_de_us_rev1, (void *)&g_secondaryCollisionContext[32], 524288, 24100, 131072 },
        { (void *)&g_playerStateNoOperationCallbackWords[0x236], (void *)&addrLow_Player_AimPreviousPositionAtReset_de, (void *)&g_secondaryCollisionContext[6], 1048576, 24100, 131072 },
        { (void *)&g_Playerai_ResetPlayerAfterDeathAddress_de, (void *)&g_playerStateNoOperationCallbackWords[0x251], (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 0, 65536 },
        { (void *)&g_Player_ResetStunAndReleaseHandlesAddress_de, 0, (void *)&g_defaultActorCollisionInfo, 0, 0, 65536 },
        { (void *)&g_playerStateNoOperationCallbackWords[0x265], (void *)&g_Player_ResetMovementInputAddress, (void *)&g_defaultActorCollisionInfo, 0, 0, 65536 },
        { (void *)&g_PlayerResetStunAndMotionCallbackAddressDe, (void *)&g_PlayerEnterRunEndWaitCallbackAddressDe, (void *)&g_defaultActorCollisionInfo, 0, 0, 65536 },
        { (void *)&addrLow_Playerai_StartGroundDeathSequence_de, (void *)&addrLow_Playerai_UpdateGroundDeathSequenceWait_de, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7000, 65536 },
        { (void *)&addrLow_Playerai_StartQuicksandDeathSequence_de, (void *)g_playerSequenceRunEndUpdateCallbackRecords[1], (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7100, 65536 },
        { (void *)&addrLow_Playerai_StartPrimagenDeathSequence_de, (void *)g_playerSequenceRunEndUpdateCallbackRecords[9], (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7101, 65536 },
        { (void *)&addrLow_Playerai_StartExplosiveDeathSequence_de, (void *)g_playerSequenceRunEndUpdateCallbackRecords[3], (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7200, 65536 },
        { (void *)&addrLow_Playerai_StartImpalementDeathSequence_de, (void *)&addrLow_Playerai_UpdateImpalementDeathSequenceWait_de, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7201, 65536 },
        { (void *)&addrLow_Playerai_StartLavaDeathSequence_de, (void *)g_playerSequenceRunEndUpdateCallbackRecords[2], (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7400, 65536 },
        { (void *)&addrLow_Playerai_StartDisabledCrawlDeathSequence_de, (void *)g_playerSequenceRunEndUpdateCallbackRecords[4], (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7005, 65536 },
        { (void *)&addrLow_Playerai_StartRunningDeathSequence_de, (void *)g_playerSequenceRunEndUpdateCallbackRecords[5], (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7500, 65536 },
        { (void *)&addrLow_Playerai_StartBackwardMovingDeathSequence_de, (void *)g_playerSequenceRunEndUpdateCallbackRecords[6], (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7505, 65536 },
        { (void *)&addrLow_Playerai_StartViewSavingDrowningDeathSequence_de, (void *)g_playerSequenceRunEndUpdateCallbackRecords[0], (void *)((char *)&g_supportingPlatformCollisionQuery + 128), 0, 7020, 65536 },
        { (void *)&addrLow_Playerai_StartFallingDeathSequence_de, (void *)g_playerSequenceRunEndUpdateCallbackRecords[8], (void *)((char *)&g_supportingPlatformCollisionQuery + 128), 0, 7010, 65536 },
        { (void *)&addrLow_Playerai_StartClimbingDeathSequence_de, (void *)g_playerSequenceRunEndUpdateCallbackRecords[7], (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7011, 65536 },
        { (void *)&g_PlayerRequestCinemaTrackCallbackAddressDe, 0, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 0, 65536 },
        { (void *)&g_Playerai_InitializeActorModelEffectAddress, (void *)&g_PlayerInterpolateTravelTargetCallbackAddressDe, (void *)&g_collisionSurfaceExcludedFromTrace[64], 0, 24109, 65536 },
        { (void *)&g_Playerai_EnterMovingSequenceStateCallbackAddressUs, (void *)&g_Playerai_EnterMovingSequenceStateCallbackAddressDe, (void *)((char *)&g_portalDefaultCollisionQuery + 32), 32768, 24105, 131072 },
        { (void *)&g_Playerai_EnterStoppedSequenceStateCallbackAddressUs, (void *)&g_Playerai_EnterStoppedSequenceStateAddress, (void *)((char *)&g_portalDefaultCollisionQuery + 32), 32768, 24105, 196608 },
        { (void *)&addrLow_Playerai_OffsetActorForForceMarker_de, (void *)&g_PlayerUpdateHeldActorReleaseCallbackAddressDe, (void *)&g_secondaryCollisionContext[1], 0, 9200, 131072 },
        { (void *)&g_playerStateNoOperationCallbackWords[0x2C9], (void *)&g_PlayerTrackNearbyAimTargetCallbackAddressDe, (void *)&g_secondaryCollisionContext[1], 0, 24100, 131072 },
        { (void *)&g_playerStateNoOperationCallbackWords[0x2CB], (void *)&g_PlayerUpdateRunEndCameraCallbackAddressUs, (void *)&g_secondaryCollisionContext[1], 0, 24100, 131072 },
        { (void *)&g_playerStateNoOperationCallbackWords[0x2D6], (void *)&g_PlayerUpdateRunEndCameraCallbackAddressDe, (void *)&g_secondaryCollisionContext[1], 0, 7043, 131072 },
        { (void *)&addrLow_Playerai_StartSwimmingChestbursterDeathSequence_de, (void *)&addrLow_Playerai_UpdateSwimmingChestbursterDeathSequenceWait_de, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7044, 65536 },
        { (void *)&addrLow_Playerai_StartRaptorChestbursterDeathSequence_de, (void *)&addrLow_Playerai_UpdateRaptorChestbursterDeathSequenceWait_de, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7045, 65536 },
        { (void *)&addrLow_Playerai_StartSwimmingRaptorChestbursterDeathSequence_de, (void *)&addrLow_Playerai_UpdateSwimmingRaptorChestbursterDeathSequenceWait_de, (void *)((char *)&g_particleOwnerEffectFlags + 8), 0, 7046, 65536 },
        { (void *)&g_playerStateNoOperationCallbackWords[0x2F5], (void *)&g_playerStateNoOperationCallbackWords[0x2F7], (void *)&g_secondaryCollisionContext[1], 0, 23300, 131072 },
        { (void *)&g_PlayerSetRunEndFlagCallbackAddressDe, (void *)&g_PlayerUpdateRunEndSequenceCallbackAddressDe, (void *)&g_secondaryCollisionContext[32], 0, 23301, 131072 }
    },
    299,
    { 0x012B012B, 0x012B012B, 0x012B012B, 0x012B012B, 0x012B0000 },
    -0.25f
}
};
#endif
