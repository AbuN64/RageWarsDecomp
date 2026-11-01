#include "TYPES.H"
#if defined(VERSION_EU_X)
/* 800CAACC.CPP */
extern char addrLow_Player_UpdateFlyMode_eu_x[];
extern char addrLow_Player_UpdateStandingState_eu_x[];
extern char addrLow_Playerai_UpdateWalkingMovement_eu_x[];
extern char addrLow_Player_UpdateWadingState_eu_x[];
extern char addrLow_Player_UpdateFloatingState_eu_x[];
extern char addrLow_Player_UpdateSwimmingState_eu_x[];
extern char addrLow_Playerai_ResetPlayerAfterDeath_eu_x[];
extern char addrLow_Playerai_UpdateTravelSequenceEntryVariant2[];
extern char addrLow_Playerai_UpdateHazardDamageEntryVariant2[];
extern char addrLow_Playerai_UpdateTargetFacingEntryVariant2[];
extern char addrLow_Player_ZeroBodyVelocity_eu_x[];
extern char addrLow_Player_StartMovingOnStickInput_eu_x[];
extern char addrLow_Playerai_StartWalkingMovement_eu_x[];
extern char addrLow_Player_StartGroundMoveState_eu_x[];
extern char addrLow_Player_UpdateGroundMoveState_eu_x[];
extern char addrLow_Player_BeginJump_eu_x[];
extern char addrLow_Player_UpdateJumpAscent_eu_x[];
extern char addrLow_Player_UpdateJumpAirMotion_eu_x[];
extern char addrLow_Player_BeginLateralLeap_eu_x[];
extern char addrLow_Player_UpdateLateralLeap_eu_x[];
extern char addrLow_Player_UpdateLeapMotion_eu_x[];
extern char addrLow_Player_ClearGlobalFlagBit[];
extern char addrLow_Player_AbsorbImpact[];
extern char addrLow_Player_DampMotion_eu_x[];
extern char g_Player_ResetMovementInputCallbackAddressDe[];
extern char g_Player_ResetMovementInputAddress[];
extern char addrLow_Player_ResetObjectVelocity[];
extern char addrLow_Player_UpdateAfterResetObjectVelocity_eu_x[];
extern char addrLow_Player_StartAimPreviousPositionAtReset_eu_x[];
extern char addrLow_Player_AimPreviousPositionAtReset_eu_x[];
extern char addrLow_Playerai_UpdateAfterResetPlayerAfterDeath_eu_x[];
extern char addrLow_Player_ResetStunAndReleaseHandles_eu_x[];
extern char addrLow_Player_ResetStunFlags_eu_eu_x[];
extern char addrLow_Player_UpdateAfterResetStunFlags_eu_x[];
extern char addrLow_Playerai_BeginRoundEndWaitEntryVariant2[];
extern char addrLow_Playerai_UpdateRoundEndWaitEntryVariant3[];
extern char addrLow_Playerai_StartTargetFacing_eu_x[];
extern char addrLow_Playerai_StartRequestCinemaTrack_eu_x[];
extern char g_PlayerRequestCinemaTrackCallbackAddressUs[];
extern char addrLow_Playerai_StartRequestCinemaTrackDe_eu_x[];
extern char g_PlayerRequestCinemaTrackCallbackAddressDe[];
extern char addrLow_Playerai_StartEntry5B04_eu_x[];
extern char addrLow_Playerai_UpdateEntry5B04_eu_x[];
extern char addrLow_Playerai_SetRunEndFlagEntryVariant2[];
extern char g_PlayerSequenceRunEndUpdateCallbackAddressUs[];
extern char addrLow_Playerai_RequestTrackFifty[];
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
extern char addrLow_Playerai_InitializeActorModelEffect[];
extern char addrLow_Playerai_StartPlayerSequence60_eu_x[];
extern char addrLow_Playerai_UpdateSequence60RunEndPose_eu_x[];
extern char addrLow_Playerai_StartPlayerSequence71_eu_x[];
extern char addrLow_Playerai_UpdateSequence71RunEndPose_eu_x[];
extern char addrLow_Playerai_StartPlayerSequence72_eu_x[];
extern char addrLow_Playerai_UpdateSequence72RunEndPose_eu_x[];
extern char addrLow_Playerai_StartPlayerSequence73_eu_x[];
extern char addrLow_Playerai_UpdateSequence73RunEndPose_eu_x[];
extern char addrLow_Playerai_StartPlayerSequence74[];
extern char addrLow_Playerai_UpdateSequence74RunEndPose_eu_x[];
extern char addrLow_Playerai_InitializeActorModelEffect_eu_x[];
extern char addrLow_Playerai_StartMovingSequenceState_eu_x[];
extern char addrLow_Playerai_EnterMovingSequenceState[];
extern char addrLow_Playerai_StartStoppedSequenceState_eu_x[];
extern char addrLow_Playerai_EnterStoppedSequenceState[];
extern char addrLow_Playerai_OffsetActorForState15_eu_x[];
unsigned int g_playerMovementStateWordsUs[662] = {
    0x3FDD2F1C, 0x4030F27C, 0x41A5E354, 0x3F84B5DE, 0x00000000, 0x00000000, 0x00000000, 0x403851EC,
    0x41ACCCCC, 0x3F8A3D71, 0x3FDD2F1C, 0x414F5C2A, 0x3F25E355, 0x00000000, 0x00000000, 0x00000000,
    0x4123D70A, 0x41F5C28F, 0x41570A3D, 0x4123D70A, 0x420F5C29, 0x41570A3D, 0x00000000, 0x00000000,
    0x00000000, 0x40A3D70A, 0x4175C28F, 0x4075C28F, 0x40A3D70A, 0x418F5C29, 0x4075C28F, 0x00000000,
    0x00000000, 0x00000000, 0x3E800000, 0x3F666666, 0x3F19999A, 0x3E99999A, 0xBFC90FDC, 0x3FC90FDC,
    0x3E800000, 0x3F666666, 0x3F19999A, 0x3E99999A, 0xBF490FDC, 0x3FC90FDC, 0x00000000, 0x00000000,
    0x3F000000, 0x3E800000, 0xBD8EFA36, 0x3FC90FDC, 0x40F5C28F, 0x41B851EB, 0x40B851EB, 0x40F5C28F,
    0x41D70A3E, 0x40B851EB, 0x4123D70A, 0x3F449BA6, 0x00000001, 0x4003126F, 0x4175C28F, 0x3F83126F,
    0x41A3D70A, 0x3FC49BA6, 0x41A3D70A, 0x43199999, 0x42CCCCCC, 0x00000001, 0x3ECCCCCD, 0x3F000000,
    0x3F800000, 0x3E800000, 0xBFC90FDC, 0x3FC90FDC, 0x3E4CCCCD, 0x3E800000, 0x3F000000, 0x3E000000,
    0xBFC90FDC, 0x3FC90FDC, 0x3F83126F, 0x40F5C28F, 0x3F03126F, 0x4123D70A, 0x3F449BA6, 0x4123D70A,
    0x42999999, 0x424CCCCC, 0x00000000, (unsigned int)addrLow_Player_ZeroBodyVelocity_eu_x, (unsigned int)addrLow_Player_UpdateFlyMode_eu_x, 0x8010A4F8, 0x00000000, 0x00000001,
    0x00020000, 0x00000000, (unsigned int)addrLow_Player_UpdateFlyMode_eu_x, 0x8010A4F8, 0x00000000, 0x00000001, 0x00020000, (unsigned int)addrLow_Player_StartMovingOnStickInput_eu_x,
    (unsigned int)addrLow_Player_UpdateStandingState_eu_x, 0x8010A458, 0x00000000, 0x00000001, 0x00020000, (unsigned int)addrLow_Playerai_StartWalkingMovement_eu_x, (unsigned int)addrLow_Playerai_UpdateWalkingMovement_eu_x, 0x8010A458,
    0x00000000, 0x000007DA, 0x00030000, (unsigned int)addrLow_Player_StartGroundMoveState_eu_x, (unsigned int)addrLow_Player_UpdateGroundMoveState_eu_x, 0x8010A458, 0x00000000, 0x00000A64,
    0x00030000, (unsigned int)addrLow_Player_BeginJump_eu_x, (unsigned int)addrLow_Player_UpdateJumpAscent_eu_x, 0x8010A190, 0x00000800, 0x000007EE, 0x00020000, 0x00000000,
    (unsigned int)addrLow_Player_UpdateJumpAirMotion_eu_x, 0x8010A190, 0x00000800, 0x000007EE, 0x00020000, (unsigned int)addrLow_Player_BeginLateralLeap_eu_x, (unsigned int)addrLow_Player_UpdateLateralLeap_eu_x, 0x8010A458,
    0x00000000, 0x000007EE, 0x00020000, 0x00000000, (unsigned int)addrLow_Player_UpdateLeapMotion_eu_x, 0x8010A458, 0x00000000, 0x000007EE,
    0x00020000, (unsigned int)addrLow_Player_ClearGlobalFlagBit, (unsigned int)addrLow_Player_UpdateWadingState_eu_x, 0x8010A418, 0x00000080, 0x000008A2, 0x00020000, (unsigned int)addrLow_Player_ClearGlobalFlagBit,
    (unsigned int)addrLow_Player_UpdateWadingState_eu_x, 0x8010A418, 0x00000080, 0x000008A2, 0x00030000, (unsigned int)addrLow_Player_AbsorbImpact, (unsigned int)addrLow_Player_UpdateFloatingState_eu_x, 0x80109FB0,
    0x00000040, 0x000008A2, 0x00020000, (unsigned int)addrLow_Player_AbsorbImpact, (unsigned int)addrLow_Player_UpdateFloatingState_eu_x, 0x80109FB0, 0x00000040, 0x000008A2,
    0x00030000, (unsigned int)addrLow_Player_DampMotion_eu_x, (unsigned int)g_Player_ResetMovementInputCallbackAddressDe, 0x8010A1B0, 0x00000000, 0x000007DA, 0x00020000, (unsigned int)addrLow_Player_DampMotion_eu_x,
    (unsigned int)g_Player_ResetMovementInputCallbackAddressDe, 0x8010A1B0, 0x00000000, 0x000007DA, 0x00020000, (unsigned int)g_Player_ResetMovementInputAddress, (unsigned int)addrLow_Player_UpdateSwimmingState_eu_x, 0x8010A358,
    0x00000100, 0x00000A3C, 0x00020000, (unsigned int)addrLow_Player_ResetObjectVelocity, (unsigned int)addrLow_Player_UpdateAfterResetObjectVelocity_eu_x, 0x8010A458, 0x00080000, 0x00000001,
    0x00020000, (unsigned int)addrLow_Player_StartAimPreviousPositionAtReset_eu_x, (unsigned int)addrLow_Player_AimPreviousPositionAtReset_eu_x, 0x8010A4F8, 0x00100000, 0x00000001, 0x00020000, (unsigned int)addrLow_Playerai_ResetPlayerAfterDeath_eu_x,
    (unsigned int)addrLow_Playerai_UpdateAfterResetPlayerAfterDeath_eu_x, 0x8010A2F8, 0x00000000, 0x00000000, 0x00010000, (unsigned int)addrLow_Player_ResetStunAndReleaseHandles_eu_x, 0x00000000, 0x8010A3D8,
    0x00000000, 0x00000000, 0x00010000, (unsigned int)addrLow_Player_ResetStunFlags_eu_eu_x, (unsigned int)addrLow_Player_UpdateAfterResetStunFlags_eu_x, 0x8010A3D8, 0x00000000, 0x00000000,
    0x00010000, (unsigned int)addrLow_Playerai_BeginRoundEndWaitEntryVariant2, (unsigned int)addrLow_Playerai_UpdateRoundEndWaitEntryVariant3, 0x8010A3D8, 0x00000000, 0x00000000, 0x00010000, (unsigned int)g_PlayerSequence13StartCallbackAddressUs,
    (unsigned int)g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant7, 0x8010A2F8, 0x00000000, 0x00001B58, 0x00010000, (unsigned int)g_PlayerSequence15StartCallbackAddressUs, (unsigned int)g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant9, 0x8010A2F8,
    0x00000000, 0x00001BBC, 0x00010000, (unsigned int)g_Playerai_InitializeActorModelEffectCallbackAddressUs, (unsigned int)addrLow_Playerai_InitializeActorModelEffect, 0x8010A2F8, 0x00000000, 0x00001BBD,
    0x00010000, (unsigned int)g_PlayerSequence70StartCallbackAddressUs, (unsigned int)g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant11, 0x8010A2F8, 0x00000000, 0x00001C20, 0x00010000, (unsigned int)addrLow_Playerai_StartPlayerSequence60_eu_x,
    (unsigned int)addrLow_Playerai_UpdateSequence60RunEndPose_eu_x, 0x8010A2F8, 0x00000000, 0x00001C21, 0x00010000, (unsigned int)g_PlayerSequence20StartCallbackAddressUs, (unsigned int)g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant10, 0x8010A2F8,
    0x00000000, 0x00001CE8, 0x00010000, (unsigned int)g_Playerai_StartPlayerSequence60Address, (unsigned int)g_Playerai_UpdateSequence60RunEndPoseCallbackAddressUs, 0x8010A2F8, 0x00000000, 0x00001B5D,
    0x00010000, (unsigned int)g_Playerai_StartPlayerSequence71CallbackAddressUs, (unsigned int)g_Playerai_UpdateSequence71RunEndPoseCallbackAddressUs, 0x8010A2F8, 0x00000000, 0x00001D4C, 0x00010000, (unsigned int)g_Playerai_StartPlayerSequence72CallbackAddressUs,
    (unsigned int)g_Playerai_UpdateSequence72RunEndPoseCallbackAddressUs, 0x8010A2F8, 0x00000000, 0x00001D51, 0x00010000, (unsigned int)g_PlayerSequence14StartCallbackAddressUs, (unsigned int)g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant8, 0x8010A3B8,
    0x00000000, 0x00001B6C, 0x00010000, (unsigned int)g_Playerai_StartPlayerSequence74CallbackAddressUs, (unsigned int)g_Playerai_UpdateSequence74RunEndPoseCallbackAddressUs, 0x8010A3B8, 0x00000000, 0x00001B62,
    0x00010000, (unsigned int)g_Playerai_StartPlayerSequence73CallbackAddressUs, (unsigned int)g_Playerai_UpdateSequence73RunEndPoseCallbackAddressUs, 0x8010A2F8, 0x00000000, 0x00001B5C, 0x00010000, (unsigned int)addrLow_Playerai_RequestTrackFifty,
    0x00000000, 0x8010A2F8, 0x00000000, 0x00000000, 0x00010000, (unsigned int)addrLow_Playerai_InitializeActorModelEffect_eu_x, (unsigned int)addrLow_Playerai_UpdateTravelSequenceEntryVariant2, 0x8010A1B0,
    0x00000000, 0x000007EE, 0x00010000, (unsigned int)addrLow_Playerai_StartMovingSequenceState_eu_x, (unsigned int)addrLow_Playerai_EnterMovingSequenceState, 0x8010A010, 0x00008000, 0x000007DA,
    0x00020000, (unsigned int)addrLow_Playerai_StartStoppedSequenceState_eu_x, (unsigned int)addrLow_Playerai_EnterStoppedSequenceState, 0x8010A010, 0x00008000, 0x000007DA, 0x00030000, (unsigned int)addrLow_Playerai_OffsetActorForState15_eu_x,
    (unsigned int)addrLow_Playerai_UpdateHazardDamageEntryVariant2, 0x8010A458, 0x00000000, 0x000023F0, 0x00020000, (unsigned int)addrLow_Playerai_StartTargetFacing_eu_x, (unsigned int)addrLow_Playerai_UpdateTargetFacingEntryVariant2, 0x8010A458,
    0x00000000, 0x00000001, 0x00020000, (unsigned int)addrLow_Playerai_StartRequestCinemaTrack_eu_x, (unsigned int)g_PlayerRequestCinemaTrackCallbackAddressUs, 0x8010A458, 0x00000000, 0x00000001,
    0x00020000, (unsigned int)addrLow_Playerai_StartPlayerSequence71_eu_x, (unsigned int)addrLow_Playerai_UpdateSequence71RunEndPose_eu_x, 0x8010A2F8, 0x00000000, 0x00001B83, 0x00010000, (unsigned int)addrLow_Playerai_StartPlayerSequence72_eu_x,
    (unsigned int)addrLow_Playerai_UpdateSequence72RunEndPose_eu_x, 0x8010A2F8, 0x00000000, 0x00001B84, 0x00010000, (unsigned int)addrLow_Playerai_StartPlayerSequence73_eu_x, (unsigned int)addrLow_Playerai_UpdateSequence73RunEndPose_eu_x, 0x8010A2F8,
    0x00000000, 0x00001B85, 0x00010000, (unsigned int)addrLow_Playerai_StartPlayerSequence74, (unsigned int)addrLow_Playerai_UpdateSequence74RunEndPose_eu_x, 0x8010A2F8, 0x00000000, 0x00001B86,
    0x00010000, (unsigned int)addrLow_Playerai_StartEntry5B04_eu_x, (unsigned int)addrLow_Playerai_UpdateEntry5B04_eu_x, 0x8010A458, 0x00000000, 0x00005B04, 0x00020000, (unsigned int)addrLow_Playerai_SetRunEndFlagEntryVariant2,
    (unsigned int)g_PlayerSequenceRunEndUpdateCallbackAddressUs, 0x8010A458, 0x00000000, 0x00005B05, 0x00020000, (unsigned int)addrLow_Player_ZeroBodyVelocity_eu_x, (unsigned int)addrLow_Player_UpdateFlyMode_eu_x, 0x8010A4F8,
    0x00000000, 0x00000001, 0x00020000, 0x00000000, (unsigned int)addrLow_Player_UpdateFlyMode_eu_x, 0x8010A4F8, 0x00000000, 0x00000001,
    0x00020000, (unsigned int)addrLow_Player_StartMovingOnStickInput_eu_x, (unsigned int)addrLow_Player_UpdateStandingState_eu_x, 0x8010A458, 0x00000000, 0x00005E24, 0x00020000, (unsigned int)addrLow_Playerai_StartWalkingMovement_eu_x,
    (unsigned int)addrLow_Playerai_UpdateWalkingMovement_eu_x, 0x8010A458, 0x00000000, 0x00005E29, 0x00030000, (unsigned int)addrLow_Player_StartGroundMoveState_eu_x, (unsigned int)addrLow_Player_UpdateGroundMoveState_eu_x, 0x8010A458,
    0x00000000, 0x00000A64, 0x00030000, (unsigned int)addrLow_Player_BeginJump_eu_x, (unsigned int)addrLow_Player_UpdateJumpAscent_eu_x, 0x8010A190, 0x00000800, 0x00005E2D,
    0x00020000, 0x00000000, (unsigned int)addrLow_Player_UpdateJumpAirMotion_eu_x, 0x8010A190, 0x00000800, 0x00005E2D, 0x00020000, (unsigned int)addrLow_Player_BeginLateralLeap_eu_x,
    (unsigned int)addrLow_Player_UpdateLateralLeap_eu_x, 0x8010A458, 0x00000000, 0x00005E2D, 0x00020000, 0x00000000, (unsigned int)addrLow_Player_UpdateLeapMotion_eu_x, 0x8010A458,
    0x00000000, 0x00005E2D, 0x00020000, (unsigned int)addrLow_Player_ClearGlobalFlagBit, (unsigned int)addrLow_Player_UpdateWadingState_eu_x, 0x8010A418, 0x00000080, 0x000008A2,
    0x00020000, (unsigned int)addrLow_Player_ClearGlobalFlagBit, (unsigned int)addrLow_Player_UpdateWadingState_eu_x, 0x8010A418, 0x00000080, 0x000008A2, 0x00030000, (unsigned int)addrLow_Player_AbsorbImpact,
    (unsigned int)addrLow_Player_UpdateFloatingState_eu_x, 0x80109FB0, 0x00000040, 0x000008A2, 0x00020000, (unsigned int)addrLow_Player_AbsorbImpact, (unsigned int)addrLow_Player_UpdateFloatingState_eu_x, 0x80109FB0,
    0x00000040, 0x000008A2, 0x00030000, (unsigned int)addrLow_Player_DampMotion_eu_x, (unsigned int)g_Player_ResetMovementInputCallbackAddressDe, 0x8010A1B0, 0x00000000, 0x00005E29,
    0x00020000, (unsigned int)addrLow_Player_DampMotion_eu_x, (unsigned int)g_Player_ResetMovementInputCallbackAddressDe, 0x8010A1B0, 0x00000000, 0x00005E29, 0x00020000, (unsigned int)g_Player_ResetMovementInputAddress,
    (unsigned int)addrLow_Player_UpdateSwimmingState_eu_x, 0x8010A358, 0x00000100, 0x00005E28, 0x00020000, (unsigned int)addrLow_Player_ResetObjectVelocity, (unsigned int)addrLow_Player_UpdateAfterResetObjectVelocity_eu_x, 0x8010A458,
    0x00080000, 0x00005E24, 0x00020000, (unsigned int)addrLow_Player_StartAimPreviousPositionAtReset_eu_x, (unsigned int)addrLow_Player_AimPreviousPositionAtReset_eu_x, 0x8010A4F8, 0x00100000, 0x00005E24,
    0x00020000, (unsigned int)addrLow_Playerai_ResetPlayerAfterDeath_eu_x, (unsigned int)addrLow_Playerai_UpdateAfterResetPlayerAfterDeath_eu_x, 0x8010A2F8, 0x00000000, 0x00000000, 0x00010000, (unsigned int)addrLow_Player_ResetStunAndReleaseHandles_eu_x,
    0x00000000, 0x8010A3D8, 0x00000000, 0x00000000, 0x00010000, (unsigned int)addrLow_Player_ResetStunFlags_eu_eu_x, (unsigned int)addrLow_Player_UpdateAfterResetStunFlags_eu_x, 0x8010A3D8,
    0x00000000, 0x00000000, 0x00010000, (unsigned int)addrLow_Playerai_BeginRoundEndWaitEntryVariant2, (unsigned int)addrLow_Playerai_UpdateRoundEndWaitEntryVariant3, 0x8010A3D8, 0x00000000, 0x00000000,
    0x00010000, (unsigned int)g_PlayerSequence13StartCallbackAddressUs, (unsigned int)g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant7, 0x8010A2F8, 0x00000000, 0x00001B58, 0x00010000, (unsigned int)g_PlayerSequence15StartCallbackAddressUs,
    (unsigned int)g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant9, 0x8010A2F8, 0x00000000, 0x00001BBC, 0x00010000, (unsigned int)g_Playerai_InitializeActorModelEffectCallbackAddressUs, (unsigned int)addrLow_Playerai_InitializeActorModelEffect, 0x8010A2F8,
    0x00000000, 0x00001BBD, 0x00010000, (unsigned int)g_PlayerSequence70StartCallbackAddressUs, (unsigned int)g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant11, 0x8010A2F8, 0x00000000, 0x00001C20,
    0x00010000, (unsigned int)addrLow_Playerai_StartPlayerSequence60_eu_x, (unsigned int)addrLow_Playerai_UpdateSequence60RunEndPose_eu_x, 0x8010A2F8, 0x00000000, 0x00001C21, 0x00010000, (unsigned int)g_PlayerSequence20StartCallbackAddressUs,
    (unsigned int)g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant10, 0x8010A2F8, 0x00000000, 0x00001CE8, 0x00010000, (unsigned int)g_Playerai_StartPlayerSequence60Address, (unsigned int)g_Playerai_UpdateSequence60RunEndPoseCallbackAddressUs, 0x8010A2F8,
    0x00000000, 0x00001B5D, 0x00010000, (unsigned int)g_Playerai_StartPlayerSequence71CallbackAddressUs, (unsigned int)g_Playerai_UpdateSequence71RunEndPoseCallbackAddressUs, 0x8010A2F8, 0x00000000, 0x00001D4C,
    0x00010000, (unsigned int)g_Playerai_StartPlayerSequence72CallbackAddressUs, (unsigned int)g_Playerai_UpdateSequence72RunEndPoseCallbackAddressUs, 0x8010A2F8, 0x00000000, 0x00001D51, 0x00010000, (unsigned int)g_PlayerSequence14StartCallbackAddressUs,
    (unsigned int)g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant8, 0x8010A3B8, 0x00000000, 0x00001B6C, 0x00010000, (unsigned int)g_Playerai_StartPlayerSequence74CallbackAddressUs, (unsigned int)g_Playerai_UpdateSequence74RunEndPoseCallbackAddressUs, 0x8010A3B8,
    0x00000000, 0x00001B62, 0x00010000, (unsigned int)g_Playerai_StartPlayerSequence73CallbackAddressUs, (unsigned int)g_Playerai_UpdateSequence73RunEndPoseCallbackAddressUs, 0x8010A2F8, 0x00000000, 0x00001B63,
    0x00010000, (unsigned int)addrLow_Playerai_RequestTrackFifty, 0x00000000, 0x8010A2F8, 0x00000000, 0x00000000, 0x00010000, (unsigned int)addrLow_Playerai_InitializeActorModelEffect_eu_x,
    (unsigned int)addrLow_Playerai_UpdateTravelSequenceEntryVariant2, 0x8010A1B0, 0x00000000, 0x00005E2D, 0x00010000, (unsigned int)addrLow_Playerai_StartMovingSequenceState_eu_x, (unsigned int)addrLow_Playerai_EnterMovingSequenceState, 0x8010A010,
    0x00008000, 0x00005E29, 0x00020000, (unsigned int)addrLow_Playerai_StartStoppedSequenceState_eu_x, (unsigned int)addrLow_Playerai_EnterStoppedSequenceState, 0x8010A010, 0x00008000, 0x00005E29,
    0x00030000, (unsigned int)addrLow_Playerai_OffsetActorForState15_eu_x, (unsigned int)addrLow_Playerai_UpdateHazardDamageEntryVariant2, 0x8010A458, 0x00000000, 0x000023F0, 0x00020000, (unsigned int)addrLow_Playerai_StartTargetFacing_eu_x,
    (unsigned int)addrLow_Playerai_UpdateTargetFacingEntryVariant2, 0x8010A458, 0x00000000, 0x00005E24, 0x00020000, (unsigned int)addrLow_Playerai_StartRequestCinemaTrack_eu_x, (unsigned int)g_PlayerRequestCinemaTrackCallbackAddressUs, 0x8010A458,
    0x00000000, 0x00005E24, 0x00020000, (unsigned int)addrLow_Playerai_StartRequestCinemaTrackDe_eu_x, (unsigned int)g_PlayerRequestCinemaTrackCallbackAddressDe, 0x8010A458, 0x00000000, 0x00001B83,
    0x00020000, (unsigned int)addrLow_Playerai_StartPlayerSequence72_eu_x, (unsigned int)addrLow_Playerai_UpdateSequence72RunEndPose_eu_x, 0x8010A2F8, 0x00000000, 0x00001B84, 0x00010000, (unsigned int)addrLow_Playerai_StartPlayerSequence73_eu_x,
    (unsigned int)addrLow_Playerai_UpdateSequence73RunEndPose_eu_x, 0x8010A2F8, 0x00000000, 0x00001B85, 0x00010000, (unsigned int)addrLow_Playerai_StartPlayerSequence74, (unsigned int)addrLow_Playerai_UpdateSequence74RunEndPose_eu_x, 0x8010A2F8,
    0x00000000, 0x00001B86, 0x00010000, (unsigned int)addrLow_Playerai_StartEntry5B04_eu_x, (unsigned int)addrLow_Playerai_UpdateEntry5B04_eu_x, 0x8010A458, 0x00000000, 0x00005B04,
    0x00020000, (unsigned int)addrLow_Playerai_SetRunEndFlagEntryVariant2, (unsigned int)g_PlayerSequenceRunEndUpdateCallbackAddressUs, 0x8010A458, 0x00000000, 0x00005B05, 0x00020000, 0x0000012B,
    0x012B012B, 0x012B012B, 0x012B012B, 0x012B012B, 0x012B0000, 0xBE800000,
};
#endif
