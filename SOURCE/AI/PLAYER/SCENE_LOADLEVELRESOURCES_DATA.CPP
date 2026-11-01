#include "include_asm.h"
#if defined(VERSION_US)
/* 800C9E9C.CPP */
float k_SceneLoadlevelresourcesEncodedWords[6] = {
    -132.0f, 64.0f, 64.0f, 24.0f, -12.0f, -48.0f,
};
#endif
#if defined(VERSION_EU)
/* 800CA0FC.CPP */
extern char addrLow_Player_UpdateFlyMode_eu[];
extern char addrLow_Player_UpdateStandingState_eu[];
extern char addrLow_Playerai_UpdateWalkingMovement_eu[];
extern char addrLow_Player_UpdateWadingState_eu[];
extern char addrLow_Player_UpdateFloatingState_eu[];
extern char addrLow_Player_UpdateSwimmingState_eu[];
extern char addrLow_Playerai_ResetPlayerAfterDeath_eu[];
extern char addrLow_Playerai_UpdateTravelSequenceEntryVariant1[];
extern char addrLow_Playerai_UpdateHazardDamageEntryVariant1[];
extern char addrLow_Playerai_UpdateTargetFacingEntryVariant1[];
extern char addrLow_Player_ZeroBodyVelocity_eu[];
extern char addrLow_Player_StartMovingOnStickInput_eu[];
extern char addrLow_Playerai_StartWalkingMovement_eu[];
extern char addrLow_Player_StartGroundMoveState_eu[];
extern char addrLow_Player_UpdateGroundMoveState_eu[];
extern char addrLow_Player_BeginJump_eu[];
extern char addrLow_Player_UpdateJumpAscent_eu[];
extern char addrLow_Player_UpdateJumpAirMotion_eu[];
extern char addrLow_Player_BeginLateralLeap_eu[];
extern char addrLow_Player_UpdateLateralLeap_eu[];
extern char addrLow_Player_UpdateLeapMotion_eu[];
extern char g_Player_DampMotionCallbackAddressDe[];
extern char addrLow_Player_AbsorbImpact_eu[];
extern char addrLow_Player_DampMotion_eu[];
extern char g_Player_ResetMovementInputCallbackAddressUs[];
extern char g_PlayerStateNoOperationCallbackAddressUsVariant6[];
extern char addrLow_Playerai_BeginRoundEndWait[];
extern char g_PlayerResetStunAndMotionCallbackAddressDe[];
extern char addrLow_Player_StartAimPreviousPositionAtReset_eu[];
extern char addrLow_Player_AimPreviousPositionAtReset_eu[];
extern char addrLow_Playerai_UpdateAfterResetPlayerAfterDeath_eu[];
extern char addrLow_Player_ResetStunAndReleaseHandles_eu[];
extern char addrLow_Player_ResetStunFlags_eu[];
extern char addrLow_Player_ResetStunFlags_eu_eu_x[];
extern char addrLow_Playerai_BeginRoundEndWaitEntryVariant1[];
extern char addrLow_Playerai_UpdateRoundEndWaitEntryVariant2[];
extern char addrLow_Playerai_StartTargetFacingEntryVariant1_eu[];
extern char addrLow_Playerai_StartRoundEndViewAngles_eu[];
extern char addrLow_Playerai_UpdateRoundEndViewAngles[];
extern char addrLow_Playerai_StartRequestCinemaTrack_eu_x[];
extern char g_PlayerRequestCinemaTrackCallbackAddressUs[];
extern char addrLow_Playerai_StartEntry5B04_eu[];
extern char addrLow_Playerai_UpdateEntry5B04_eu[];
extern char addrLow_Playerai_SetRunEndFlagEntryVariant1[];
extern char addrLow_Playerai_UpdateRunEndTransition[];
extern char g_PlayerSequenceRunEndUpdateCallbackAddressDeVariant2[];
extern char addrLow_Playerai_StartSequenceTen[];
extern char addrLow_Playerai_UpdateSequence50Wait[];
extern char addrLow_Playerai_StartSequence50[];
extern char addrLow_Playerai_UpdateSequence30Wait[];
extern char addrLow_Playerai_StartSequence30[];
extern char addrLow_Playerai_UpdateSequence40Wait[];
extern char addrLow_Playerai_StartSequence40[];
extern char addrLow_Playerai_UpdateSequence11Wait[];
extern char addrLow_Playerai_StartSequence11[];
extern char addrLow_Playerai_UpdateSequence12Wait[];
extern char addrLow_Playerai_StartSequence12[];
extern char addrLow_Playerai_UpdateSequence13Wait[];
extern char addrLow_Playerai_StartSequence13[];
extern char addrLow_Playerai_UpdateSequence14Wait[];
extern char addrLow_Playerai_StartSequence14[];
extern char addrLow_Playerai_UpdateSequence15Wait[];
extern char addrLow_Playerai_StartSequence15[];
extern char addrLow_Playerai_UpdateSequence20Wait[];
extern char addrLow_Playerai_StartSequence20[];
extern char addrLow_Playerai_UpdateSequence70Wait[];
extern char addrLow_Playerai_StartSequence70[];
extern char addrLow_Playerai_UpdateSequence60Wait[];
extern char addrLow_Playerai_StartPlayerSequence60_eu[];
extern char addrLow_Playerai_UpdateSequence60RunEndPose_eu[];
extern char addrLow_Playerai_StartPlayerSequence71_eu[];
extern char addrLow_Playerai_UpdateSequence71RunEndPose_eu[];
extern char addrLow_Playerai_StartPlayerSequence72_eu[];
extern char addrLow_Playerai_UpdateSequence72RunEndPose_eu[];
extern char addrLow_Playerai_StartPlayerSequence73_eu[];
extern char addrLow_Playerai_UpdateSequence73RunEndPose_eu[];
extern char g_Playerai_EnterMovingSequenceStateCallbackAddressDe[];
extern char addrLow_Playerai_UpdateSequence74RunEndPose_eu[];
extern char addrLow_Playerai_InitializeActorModelEffect_eu[];
extern char addrLow_Playerai_ClearPlayerWeaponLock[];
extern char addrLow_Playerai_StartMovingSequenceState_eu_x[];
extern char addrLow_Playerai_ResetPlayerWeaponLock[];
extern char addrLow_Playerai_StartStoppedSequenceState_eu_x[];
extern char addrLow_Playerai_OffsetActorForState15_eu[];
unsigned int g_playerMovementStateWordsDe[662] = {
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
    0x42999999, 0x424CCCCC, 0x00000000, (unsigned int)addrLow_Player_ZeroBodyVelocity_eu, (unsigned int)addrLow_Player_UpdateFlyMode_eu, 0x801104F8, 0x00000000, 0x00000001,
    0x00020000, 0x00000000, (unsigned int)addrLow_Player_UpdateFlyMode_eu, 0x801104F8, 0x00000000, 0x00000001, 0x00020000, (unsigned int)addrLow_Player_StartMovingOnStickInput_eu,
    (unsigned int)addrLow_Player_UpdateStandingState_eu, 0x80110458, 0x00000000, 0x00000001, 0x00020000, (unsigned int)addrLow_Playerai_StartWalkingMovement_eu, (unsigned int)addrLow_Playerai_UpdateWalkingMovement_eu, 0x80110458,
    0x00000000, 0x000007DA, 0x00030000, (unsigned int)addrLow_Player_StartGroundMoveState_eu, (unsigned int)addrLow_Player_UpdateGroundMoveState_eu, 0x80110458, 0x00000000, 0x00000A64,
    0x00030000, (unsigned int)addrLow_Player_BeginJump_eu, (unsigned int)addrLow_Player_UpdateJumpAscent_eu, 0x80110190, 0x00000800, 0x000007EE, 0x00020000, 0x00000000,
    (unsigned int)addrLow_Player_UpdateJumpAirMotion_eu, 0x80110190, 0x00000800, 0x000007EE, 0x00020000, (unsigned int)addrLow_Player_BeginLateralLeap_eu, (unsigned int)addrLow_Player_UpdateLateralLeap_eu, 0x80110458,
    0x00000000, 0x000007EE, 0x00020000, 0x00000000, (unsigned int)addrLow_Player_UpdateLeapMotion_eu, 0x80110458, 0x00000000, 0x000007EE,
    0x00020000, (unsigned int)g_Player_DampMotionCallbackAddressDe, (unsigned int)addrLow_Player_UpdateWadingState_eu, 0x80110418, 0x00000080, 0x000008A2, 0x00020000, (unsigned int)g_Player_DampMotionCallbackAddressDe,
    (unsigned int)addrLow_Player_UpdateWadingState_eu, 0x80110418, 0x00000080, 0x000008A2, 0x00030000, (unsigned int)addrLow_Player_AbsorbImpact_eu, (unsigned int)addrLow_Player_UpdateFloatingState_eu, 0x8010FFB0,
    0x00000040, 0x000008A2, 0x00020000, (unsigned int)addrLow_Player_AbsorbImpact_eu, (unsigned int)addrLow_Player_UpdateFloatingState_eu, 0x8010FFB0, 0x00000040, 0x000008A2,
    0x00030000, (unsigned int)addrLow_Player_DampMotion_eu, (unsigned int)g_Player_ResetMovementInputCallbackAddressUs, 0x801101B0, 0x00000000, 0x000007DA, 0x00020000, (unsigned int)addrLow_Player_DampMotion_eu,
    (unsigned int)g_Player_ResetMovementInputCallbackAddressUs, 0x801101B0, 0x00000000, 0x000007DA, 0x00020000, (unsigned int)g_PlayerStateNoOperationCallbackAddressUsVariant6, (unsigned int)addrLow_Player_UpdateSwimmingState_eu, 0x80110358,
    0x00000100, 0x00000A3C, 0x00020000, (unsigned int)addrLow_Playerai_BeginRoundEndWait, (unsigned int)g_PlayerResetStunAndMotionCallbackAddressDe, 0x80110458, 0x00080000, 0x00000001,
    0x00020000, (unsigned int)addrLow_Player_StartAimPreviousPositionAtReset_eu, (unsigned int)addrLow_Player_AimPreviousPositionAtReset_eu, 0x801104F8, 0x00100000, 0x00000001, 0x00020000, (unsigned int)addrLow_Playerai_ResetPlayerAfterDeath_eu,
    (unsigned int)addrLow_Playerai_UpdateAfterResetPlayerAfterDeath_eu, 0x801102F8, 0x00000000, 0x00000000, 0x00010000, (unsigned int)addrLow_Player_ResetStunAndReleaseHandles_eu, 0x00000000, 0x801103D8,
    0x00000000, 0x00000000, 0x00010000, (unsigned int)addrLow_Player_ResetStunFlags_eu, (unsigned int)addrLow_Player_ResetStunFlags_eu_eu_x, 0x801103D8, 0x00000000, 0x00000000,
    0x00010000, (unsigned int)addrLow_Playerai_BeginRoundEndWaitEntryVariant1, (unsigned int)addrLow_Playerai_UpdateRoundEndWaitEntryVariant2, 0x801103D8, 0x00000000, 0x00000000, 0x00010000, (unsigned int)addrLow_Playerai_StartSequenceTen,
    (unsigned int)addrLow_Playerai_UpdateSequence50Wait, 0x801102F8, 0x00000000, 0x00001B58, 0x00010000, (unsigned int)addrLow_Playerai_StartSequence30, (unsigned int)addrLow_Playerai_UpdateSequence40Wait, 0x801102F8,
    0x00000000, 0x00001BBC, 0x00010000, (unsigned int)addrLow_Playerai_StartSequence70, (unsigned int)addrLow_Playerai_UpdateSequence60Wait, 0x801102F8, 0x00000000, 0x00001BBD,
    0x00010000, (unsigned int)addrLow_Playerai_StartSequence11, (unsigned int)addrLow_Playerai_UpdateSequence12Wait, 0x801102F8, 0x00000000, 0x00001C20, 0x00010000, (unsigned int)addrLow_Playerai_StartPlayerSequence60_eu,
    (unsigned int)addrLow_Playerai_UpdateSequence60RunEndPose_eu, 0x801102F8, 0x00000000, 0x00001C21, 0x00010000, (unsigned int)addrLow_Playerai_StartSequence40, (unsigned int)addrLow_Playerai_UpdateSequence11Wait, 0x801102F8,
    0x00000000, 0x00001CE8, 0x00010000, (unsigned int)addrLow_Playerai_StartSequence12, (unsigned int)addrLow_Playerai_UpdateSequence13Wait, 0x801102F8, 0x00000000, 0x00001B5D,
    0x00010000, (unsigned int)addrLow_Playerai_StartSequence13, (unsigned int)addrLow_Playerai_UpdateSequence14Wait, 0x801102F8, 0x00000000, 0x00001D4C, 0x00010000, (unsigned int)addrLow_Playerai_StartSequence14,
    (unsigned int)addrLow_Playerai_UpdateSequence15Wait, 0x801102F8, 0x00000000, 0x00001D51, 0x00010000, (unsigned int)addrLow_Playerai_StartSequence50, (unsigned int)addrLow_Playerai_UpdateSequence30Wait, 0x801103B8,
    0x00000000, 0x00001B6C, 0x00010000, (unsigned int)addrLow_Playerai_StartSequence20, (unsigned int)addrLow_Playerai_UpdateSequence70Wait, 0x801103B8, 0x00000000, 0x00001B62,
    0x00010000, (unsigned int)addrLow_Playerai_StartSequence15, (unsigned int)addrLow_Playerai_UpdateSequence20Wait, 0x801102F8, 0x00000000, 0x00001B5C, 0x00010000, (unsigned int)g_PlayerSequenceRunEndUpdateCallbackAddressDeVariant2,
    0x00000000, 0x801102F8, 0x00000000, 0x00000000, 0x00010000, (unsigned int)addrLow_Playerai_InitializeActorModelEffect_eu, (unsigned int)addrLow_Playerai_UpdateTravelSequenceEntryVariant1, 0x801101B0,
    0x00000000, 0x000007EE, 0x00010000, (unsigned int)addrLow_Playerai_ClearPlayerWeaponLock, (unsigned int)addrLow_Playerai_StartMovingSequenceState_eu_x, 0x80110010, 0x00008000, 0x000007DA,
    0x00020000, (unsigned int)addrLow_Playerai_ResetPlayerWeaponLock, (unsigned int)addrLow_Playerai_StartStoppedSequenceState_eu_x, 0x80110010, 0x00008000, 0x000007DA, 0x00030000, (unsigned int)addrLow_Playerai_OffsetActorForState15_eu,
    (unsigned int)addrLow_Playerai_UpdateHazardDamageEntryVariant1, 0x80110458, 0x00000000, 0x000023F0, 0x00020000, (unsigned int)addrLow_Playerai_StartTargetFacingEntryVariant1_eu, (unsigned int)addrLow_Playerai_UpdateTargetFacingEntryVariant1, 0x80110458,
    0x00000000, 0x00000001, 0x00020000, (unsigned int)addrLow_Playerai_StartRoundEndViewAngles_eu, (unsigned int)addrLow_Playerai_UpdateRoundEndViewAngles, 0x80110458, 0x00000000, 0x00000001,
    0x00020000, (unsigned int)addrLow_Playerai_StartPlayerSequence71_eu, (unsigned int)addrLow_Playerai_UpdateSequence71RunEndPose_eu, 0x801102F8, 0x00000000, 0x00001B83, 0x00010000, (unsigned int)addrLow_Playerai_StartPlayerSequence72_eu,
    (unsigned int)addrLow_Playerai_UpdateSequence72RunEndPose_eu, 0x801102F8, 0x00000000, 0x00001B84, 0x00010000, (unsigned int)addrLow_Playerai_StartPlayerSequence73_eu, (unsigned int)addrLow_Playerai_UpdateSequence73RunEndPose_eu, 0x801102F8,
    0x00000000, 0x00001B85, 0x00010000, (unsigned int)g_Playerai_EnterMovingSequenceStateCallbackAddressDe, (unsigned int)addrLow_Playerai_UpdateSequence74RunEndPose_eu, 0x801102F8, 0x00000000, 0x00001B86,
    0x00010000, (unsigned int)addrLow_Playerai_StartEntry5B04_eu, (unsigned int)addrLow_Playerai_UpdateEntry5B04_eu, 0x80110458, 0x00000000, 0x00005B04, 0x00020000, (unsigned int)addrLow_Playerai_SetRunEndFlagEntryVariant1,
    (unsigned int)addrLow_Playerai_UpdateRunEndTransition, 0x80110458, 0x00000000, 0x00005B05, 0x00020000, (unsigned int)addrLow_Player_ZeroBodyVelocity_eu, (unsigned int)addrLow_Player_UpdateFlyMode_eu, 0x801104F8,
    0x00000000, 0x00000001, 0x00020000, 0x00000000, (unsigned int)addrLow_Player_UpdateFlyMode_eu, 0x801104F8, 0x00000000, 0x00000001,
    0x00020000, (unsigned int)addrLow_Player_StartMovingOnStickInput_eu, (unsigned int)addrLow_Player_UpdateStandingState_eu, 0x80110458, 0x00000000, 0x00005E24, 0x00020000, (unsigned int)addrLow_Playerai_StartWalkingMovement_eu,
    (unsigned int)addrLow_Playerai_UpdateWalkingMovement_eu, 0x80110458, 0x00000000, 0x00005E29, 0x00030000, (unsigned int)addrLow_Player_StartGroundMoveState_eu, (unsigned int)addrLow_Player_UpdateGroundMoveState_eu, 0x80110458,
    0x00000000, 0x00000A64, 0x00030000, (unsigned int)addrLow_Player_BeginJump_eu, (unsigned int)addrLow_Player_UpdateJumpAscent_eu, 0x80110190, 0x00000800, 0x00005E2D,
    0x00020000, 0x00000000, (unsigned int)addrLow_Player_UpdateJumpAirMotion_eu, 0x80110190, 0x00000800, 0x00005E2D, 0x00020000, (unsigned int)addrLow_Player_BeginLateralLeap_eu,
    (unsigned int)addrLow_Player_UpdateLateralLeap_eu, 0x80110458, 0x00000000, 0x00005E2D, 0x00020000, 0x00000000, (unsigned int)addrLow_Player_UpdateLeapMotion_eu, 0x80110458,
    0x00000000, 0x00005E2D, 0x00020000, (unsigned int)g_Player_DampMotionCallbackAddressDe, (unsigned int)addrLow_Player_UpdateWadingState_eu, 0x80110418, 0x00000080, 0x000008A2,
    0x00020000, (unsigned int)g_Player_DampMotionCallbackAddressDe, (unsigned int)addrLow_Player_UpdateWadingState_eu, 0x80110418, 0x00000080, 0x000008A2, 0x00030000, (unsigned int)addrLow_Player_AbsorbImpact_eu,
    (unsigned int)addrLow_Player_UpdateFloatingState_eu, 0x8010FFB0, 0x00000040, 0x000008A2, 0x00020000, (unsigned int)addrLow_Player_AbsorbImpact_eu, (unsigned int)addrLow_Player_UpdateFloatingState_eu, 0x8010FFB0,
    0x00000040, 0x000008A2, 0x00030000, (unsigned int)addrLow_Player_DampMotion_eu, (unsigned int)g_Player_ResetMovementInputCallbackAddressUs, 0x801101B0, 0x00000000, 0x00005E29,
    0x00020000, (unsigned int)addrLow_Player_DampMotion_eu, (unsigned int)g_Player_ResetMovementInputCallbackAddressUs, 0x801101B0, 0x00000000, 0x00005E29, 0x00020000, (unsigned int)g_PlayerStateNoOperationCallbackAddressUsVariant6,
    (unsigned int)addrLow_Player_UpdateSwimmingState_eu, 0x80110358, 0x00000100, 0x00005E28, 0x00020000, (unsigned int)addrLow_Playerai_BeginRoundEndWait, (unsigned int)g_PlayerResetStunAndMotionCallbackAddressDe, 0x80110458,
    0x00080000, 0x00005E24, 0x00020000, (unsigned int)addrLow_Player_StartAimPreviousPositionAtReset_eu, (unsigned int)addrLow_Player_AimPreviousPositionAtReset_eu, 0x801104F8, 0x00100000, 0x00005E24,
    0x00020000, (unsigned int)addrLow_Playerai_ResetPlayerAfterDeath_eu, (unsigned int)addrLow_Playerai_UpdateAfterResetPlayerAfterDeath_eu, 0x801102F8, 0x00000000, 0x00000000, 0x00010000, (unsigned int)addrLow_Player_ResetStunAndReleaseHandles_eu,
    0x00000000, 0x801103D8, 0x00000000, 0x00000000, 0x00010000, (unsigned int)addrLow_Player_ResetStunFlags_eu, (unsigned int)addrLow_Player_ResetStunFlags_eu_eu_x, 0x801103D8,
    0x00000000, 0x00000000, 0x00010000, (unsigned int)addrLow_Playerai_BeginRoundEndWaitEntryVariant1, (unsigned int)addrLow_Playerai_UpdateRoundEndWaitEntryVariant2, 0x801103D8, 0x00000000, 0x00000000,
    0x00010000, (unsigned int)addrLow_Playerai_StartSequenceTen, (unsigned int)addrLow_Playerai_UpdateSequence50Wait, 0x801102F8, 0x00000000, 0x00001B58, 0x00010000, (unsigned int)addrLow_Playerai_StartSequence30,
    (unsigned int)addrLow_Playerai_UpdateSequence40Wait, 0x801102F8, 0x00000000, 0x00001BBC, 0x00010000, (unsigned int)addrLow_Playerai_StartSequence70, (unsigned int)addrLow_Playerai_UpdateSequence60Wait, 0x801102F8,
    0x00000000, 0x00001BBD, 0x00010000, (unsigned int)addrLow_Playerai_StartSequence11, (unsigned int)addrLow_Playerai_UpdateSequence12Wait, 0x801102F8, 0x00000000, 0x00001C20,
    0x00010000, (unsigned int)addrLow_Playerai_StartPlayerSequence60_eu, (unsigned int)addrLow_Playerai_UpdateSequence60RunEndPose_eu, 0x801102F8, 0x00000000, 0x00001C21, 0x00010000, (unsigned int)addrLow_Playerai_StartSequence40,
    (unsigned int)addrLow_Playerai_UpdateSequence11Wait, 0x801102F8, 0x00000000, 0x00001CE8, 0x00010000, (unsigned int)addrLow_Playerai_StartSequence12, (unsigned int)addrLow_Playerai_UpdateSequence13Wait, 0x801102F8,
    0x00000000, 0x00001B5D, 0x00010000, (unsigned int)addrLow_Playerai_StartSequence13, (unsigned int)addrLow_Playerai_UpdateSequence14Wait, 0x801102F8, 0x00000000, 0x00001D4C,
    0x00010000, (unsigned int)addrLow_Playerai_StartSequence14, (unsigned int)addrLow_Playerai_UpdateSequence15Wait, 0x801102F8, 0x00000000, 0x00001D51, 0x00010000, (unsigned int)addrLow_Playerai_StartSequence50,
    (unsigned int)addrLow_Playerai_UpdateSequence30Wait, 0x801103B8, 0x00000000, 0x00001B6C, 0x00010000, (unsigned int)addrLow_Playerai_StartSequence20, (unsigned int)addrLow_Playerai_UpdateSequence70Wait, 0x801103B8,
    0x00000000, 0x00001B62, 0x00010000, (unsigned int)addrLow_Playerai_StartSequence15, (unsigned int)addrLow_Playerai_UpdateSequence20Wait, 0x801102F8, 0x00000000, 0x00001B63,
    0x00010000, (unsigned int)g_PlayerSequenceRunEndUpdateCallbackAddressDeVariant2, 0x00000000, 0x801102F8, 0x00000000, 0x00000000, 0x00010000, (unsigned int)addrLow_Playerai_InitializeActorModelEffect_eu,
    (unsigned int)addrLow_Playerai_UpdateTravelSequenceEntryVariant1, 0x801101B0, 0x00000000, 0x00005E2D, 0x00010000, (unsigned int)addrLow_Playerai_ClearPlayerWeaponLock, (unsigned int)addrLow_Playerai_StartMovingSequenceState_eu_x, 0x80110010,
    0x00008000, 0x00005E29, 0x00020000, (unsigned int)addrLow_Playerai_ResetPlayerWeaponLock, (unsigned int)addrLow_Playerai_StartStoppedSequenceState_eu_x, 0x80110010, 0x00008000, 0x00005E29,
    0x00030000, (unsigned int)addrLow_Playerai_OffsetActorForState15_eu, (unsigned int)addrLow_Playerai_UpdateHazardDamageEntryVariant1, 0x80110458, 0x00000000, 0x000023F0, 0x00020000, (unsigned int)addrLow_Playerai_StartTargetFacingEntryVariant1_eu,
    (unsigned int)addrLow_Playerai_UpdateTargetFacingEntryVariant1, 0x80110458, 0x00000000, 0x00005E24, 0x00020000, (unsigned int)addrLow_Playerai_StartRoundEndViewAngles_eu, (unsigned int)addrLow_Playerai_UpdateRoundEndViewAngles, 0x80110458,
    0x00000000, 0x00005E24, 0x00020000, (unsigned int)addrLow_Playerai_StartRequestCinemaTrack_eu_x, (unsigned int)g_PlayerRequestCinemaTrackCallbackAddressUs, 0x80110458, 0x00000000, 0x00001B83,
    0x00020000, (unsigned int)addrLow_Playerai_StartPlayerSequence72_eu, (unsigned int)addrLow_Playerai_UpdateSequence72RunEndPose_eu, 0x801102F8, 0x00000000, 0x00001B84, 0x00010000, (unsigned int)addrLow_Playerai_StartPlayerSequence73_eu,
    (unsigned int)addrLow_Playerai_UpdateSequence73RunEndPose_eu, 0x801102F8, 0x00000000, 0x00001B85, 0x00010000, (unsigned int)g_Playerai_EnterMovingSequenceStateCallbackAddressDe, (unsigned int)addrLow_Playerai_UpdateSequence74RunEndPose_eu, 0x801102F8,
    0x00000000, 0x00001B86, 0x00010000, (unsigned int)addrLow_Playerai_StartEntry5B04_eu, (unsigned int)addrLow_Playerai_UpdateEntry5B04_eu, 0x80110458, 0x00000000, 0x00005B04,
    0x00020000, (unsigned int)addrLow_Playerai_SetRunEndFlagEntryVariant1, (unsigned int)addrLow_Playerai_UpdateRunEndTransition, 0x80110458, 0x00000000, 0x00005B05, 0x00020000, 0x0000012B,
    0x012B012B, 0x012B012B, 0x012B012B, 0x012B012B, 0x012B0000, 0xBE800000,
};
#endif
