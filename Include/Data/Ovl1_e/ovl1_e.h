#ifndef DATA_OVL1_E_OVL1_E_H
#define DATA_OVL1_E_OVL1_E_H
#include "Ai/nav_symbols.h"
#include "Ai/ai_shared_symbols.h"
#include "Data/rest_source_records.h"
extern char g_globalGameplayFlags[];
#if defined(VERSION_US_REV1)
extern char g_Player_UpdateStandingStateAddress_us_us_rev1[];
extern char g_Player_ZeroBodyVelocityCallbackAddressDe[];
extern char addrLow_Playerai_UpdateWalkingMovement_us[];
extern char g_PlayerSpecial_LeadingEmptyCallbackPackedAddress[];
extern char g_PlayerSpecial_TrailingEmptyCallbackPackedAddress[];
extern char g_Player_UpdateGroundMoveStateAddress_de_us_rev1[];
extern char g_Player_UpdateWadingStateAddress_us_us_rev1[];
extern char g_Player_ClearGlobalFlagBitPackedAddress[];
extern char g_Player_UpdateWadingStateAddress_us_us_rev1[];
extern char g_Player_ClearGlobalFlagBitPackedAddress[];
extern char g_Player_UpdateFloatingStateAddress_us_us_rev1[];
extern char g_Player_AbsorbImpactPackedAddress[];
extern char g_Player_UpdateFloatingStateAddress_us_us_rev1[];
extern char g_Player_AbsorbImpactPackedAddress[];
extern char g_Player_DampMotionPackedAddress[];
extern char addrLow_Player_AbsorbImpact_eu[];
extern char g_Player_DampMotionPackedAddress[];
extern char addrLow_Player_AbsorbImpact_eu[];
extern char g_Player_UpdateSwimmingStateAddress_us_us_rev1[];
extern char g_Player_ResetMovementInputPackedAddress[];
extern char g_Player_ResetObjectVelocityPackedAddress[];
extern char addrLow_PlayerSpecial_LeadingEmptyCallback[];
extern char addrLow_PlayerSpecial_TrailingEmptyCallback[];
extern char addrLow_Player_ClearGlobalFlagBit[];
extern char addrLow_Player_AbsorbImpact[];
extern char addrLow_Player_DampMotion[];
extern char addrLow_Player_ResetMovementInput[];
extern char addrLow_Player_ResetObjectVelocity[];
extern char g_Player_ResetObjectVelocityAddress_de_us_rev1[];
extern char g_playerNormalAuxiliaryStateLeadingTarget[];
extern char g_Player_AimPreviousPositionAtResetAddress_de_us_rev1[];
#endif
#endif
