#include "Common/packed_callback.h"
#include "Ai/player_g18_symbols.h"
#include "Data/rest_source_records.h"
#include "Data/Ovl1_e/g_playerstatespecialcallbacks05pointerwords1_ovl1e.h"
#include "Data/Ovl1_e/g_playerstatespecialcallbacks06pointerwords1_ovl1e.h"
#include "Data/Ovl1_e/g_playerstatespecialcallbacks07pointerwords1_ovl1e.h"
#include "Data/Ovl1_e/g_playerstatespecialcallbacks08pointerwords1_ovl1e.h"
#include "Common/runtime_declarations.h"
#include "Data/Ovl1_e/ovl1_e.h"

#if defined(VERSION_US_REV1)
void * g_Ovl1ERetained21[1] = {
    &g_secondaryCollisionContext[6],
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialTiming01Record g_PlayerStateSpecialTiming_usrev1_CF954 = {
    0,
    1,
};
#endif

#if defined(VERSION_US_REV1)
RestBytes4 g_ovl1ERetained5Halfword_usrev1_CF95C = {
    { 0, 2, 0, 0 },
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialCallbacks02PointerRecord g_PlayerStateSpecialCallbacks02Pointer_usrev1_CF960 = {
    (unsigned int)g_Player_ZeroBodyVelocityCallbackAddressDe,
    (unsigned int)g_Player_UpdateStandingStateAddress_us_us_rev1,
};
#endif

#if defined(VERSION_US_REV1)
void * g_Ovl1ERetained19[1] = {
    &g_secondaryCollisionContext[1],
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialTiming02Record g_PlayerStateSpecialTiming_usrev1_CF96C = {
    0,
    24100,
};
#endif

#if defined(VERSION_US_REV1)
Ovl1EOvl1ECppRetainedWords24Layout g_Ovl1ERetained_usrev1_CF974 = {
    131072,
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialCallbacks03PointerRecord g_PlayerStateSpecialCallbacks03Pointer_usrev1_CF978 = {
    PACKED_CALLBACK_LOW(PlayerSpecial_LeadingEmptyCallback),
    (unsigned int)addrLow_Playerai_UpdateWalkingMovement_us,
};
#endif

#if defined(VERSION_US_REV1)
void * g_Ovl1ERetained28[1] = {
    &g_secondaryCollisionContext[1],
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialTiming03Record g_PlayerStateSpecialTiming_usrev1_CF984 = {
    0,
    24105,
};
#endif

#if defined(VERSION_US_REV1)
RestBytes4 g_ovl1ERetained23Halfword_usrev1_CF98C = {
    { 0, 3, 0, 0 },
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialCallbacks04PointerRecord g_PlayerStateSpecialCallbacks04Pointer_usrev1_CF990 = {
    PACKED_CALLBACK_LOW(PlayerSpecial_TrailingEmptyCallback),
    (unsigned int)g_Player_UpdateGroundMoveStateAddress_de_us_rev1,
};
#endif

#if defined(VERSION_US_REV1)
void * g_Ovl1ERetained14[1] = {
    &g_secondaryCollisionContext[1],
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialTiming04Record g_PlayerStateSpecialTiming_usrev1_CF99C = {
    0,
    2660,
};
#endif

#if defined(VERSION_US_REV1)
Ovl1EOvl1ECppRetainedWords17Layout g_Ovl1ERetained_usrev1_CF9A4 = {
    196608,
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialCallbacks05PointerRecord g_PlayerStateSpecialCallbacks05Pointer_usrev1_CF9A8 = {
    PACKED_CALLBACK_LOW(Player_BeginJump),
    PACKED_CALLBACK_LOW(Player_UpdateJumpAscent),
};
#endif

#if defined(VERSION_US_REV1)
void * g_Ovl1ERetained26[1] = {
    &g_collisionSurfaceExcludedFromTrace[32],
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialTiming05Record g_PlayerStateSpecialTiming_usrev1_CF9B4 = {
    2048,
    24109,
};
#endif

#if defined(VERSION_US_REV1)
RestBytes4 g_ovl1ERetained12Halfword_usrev1_CF9BC = {
    { 0, 2, 0, 0 },
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialCallbacks06PointerRecord g_PlayerStateSpecialCallbacks06Pointer_usrev1_CF9C0 = {
    0x00000000,
    PACKED_CALLBACK_LOW(Player_UpdateJumpAirMotion),
};
#endif

#if defined(VERSION_US_REV1)
void * g_Ovl1ERetained11[1] = {
    &g_collisionSurfaceExcludedFromTrace[32],
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialTiming06Record g_PlayerStateSpecialTiming_usrev1_CF9CC = {
    2048,
    24109,
};
#endif

#if defined(VERSION_US_REV1)
Ovl1EOvl1ECppRetainedWords15Layout g_Ovl1ERetained_usrev1_CF9D4 = {
    131072,
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialCallbacks07PointerRecord g_PlayerStateSpecialCallbacks07Pointer_usrev1_CF9D8 = {
    PACKED_CALLBACK_LOW(Player_BeginLateralLeap),
    PACKED_CALLBACK_LOW(Player_UpdateLateralLeap),
};
#endif

#if defined(VERSION_US_REV1)
void * g_Ovl1ERetained7[1] = {
    &g_secondaryCollisionContext[1],
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialTiming07Record g_PlayerStateSpecialTiming_usrev1_CF9E4 = {
    0,
    24109,
};
#endif

#if defined(VERSION_US_REV1)
RestBytes4 g_ovl1ERetained10Halfword_usrev1_CF9EC = {
    { 0, 2, 0, 0 },
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialCallbacks08PointerRecord g_PlayerStateSpecialCallbacks08Pointer_usrev1_CF9F0 = {
    0x00000000,
    PACKED_CALLBACK_LOW(Player_UpdateLeapMotion),
};
#endif

#if defined(VERSION_US_REV1)
void * g_Ovl1ERetained32[1] = {
    &g_secondaryCollisionContext[1],
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialTiming08Record g_PlayerStateSpecialTiming_usrev1_CF9FC = {
    0,
    24109,
};
#endif

#if defined(VERSION_US_REV1)
Ovl1EOvl1ECppRetainedWords25Layout g_Ovl1ERetained_usrev1_CFA04 = {
    131072,
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialCallbacks09PointerRecord g_PlayerStateSpecialCallbacks09Pointer_usrev1_CFA08 = {
    PACKED_CALLBACK_LOW(Player_ClearGlobalFlagBit),
    (unsigned int)g_Player_UpdateWadingStateAddress_us_us_rev1,
};
#endif

#if defined(VERSION_US_REV1)
void * g_Ovl1ERetained29[1] = {
    (void *)&g_globalGameplayFlags,
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialTiming09Record g_PlayerStateSpecialTiming_usrev1_CFA14 = {
    128,
    2210,
};
#endif

#if defined(VERSION_US_REV1)
RestBytes4 g_ovl1ERetained31Halfword_usrev1_CFA1C = {
    { 0, 2, 0, 0 },
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialCallbacks10PointerRecord g_PlayerStateSpecialCallbacks10Pointer_usrev1_CFA20 = {
    PACKED_CALLBACK_LOW(Player_ClearGlobalFlagBit),
    (unsigned int)g_Player_UpdateWadingStateAddress_us_us_rev1,
};
#endif

#if defined(VERSION_US_REV1)
void * g_Ovl1ERetained20[1] = {
    (void *)&g_globalGameplayFlags,
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialTiming10Record g_PlayerStateSpecialTiming_usrev1_CFA2C = {
    128,
    2210,
};
#endif

#if defined(VERSION_US_REV1)
Ovl1EOvl1ECppRetainedWords30Layout g_Ovl1ERetained_usrev1_CFA34 = {
    196608,
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialCallbacks11PointerRecord g_PlayerStateSpecialCallbacks11Pointer_usrev1_CFA38 = {
    PACKED_CALLBACK_LOW(Player_AbsorbImpact),
    (unsigned int)g_Player_UpdateFloatingStateAddress_us_us_rev1,
};
#endif

#if defined(VERSION_US_REV1)
void * g_Ovl1ERetained2[1] = {
    (void *)&g_pagerPageCounters[8],
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialTiming11Record g_PlayerStateSpecialTiming_usrev1_CFA44 = {
    64,
    2210,
};
#endif

#if defined(VERSION_US_REV1)
RestBytes4 g_ovl1ERetained8Halfword_usrev1_CFA4C = {
    { 0, 2, 0, 0 },
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialCallbacks12PointerRecord g_PlayerStateSpecialCallbacks12Pointer_usrev1_CFA50 = {
    PACKED_CALLBACK_LOW(Player_AbsorbImpact),
    (unsigned int)g_Player_UpdateFloatingStateAddress_us_us_rev1,
};
#endif

#if defined(VERSION_US_REV1)
void * g_Ovl1ERetained3[1] = {
    (void *)&g_pagerPageCounters[8],
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialTiming12Record g_PlayerStateSpecialTiming_usrev1_CFA5C = {
    64,
    2210,
};
#endif

#if defined(VERSION_US_REV1)
Ovl1EOvl1ECppRetainedWords18Layout g_Ovl1ERetained_usrev1_CFA64 = {
    196608,
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialCallbacks13PointerRecord g_PlayerStateSpecialCallbacks13Pointer_usrev1_CFA68 = {
    PACKED_CALLBACK_LOW(Player_DampMotion),
    PACKED_CALLBACK_LOW(Player_AbsorbImpact),
};
#endif

#if defined(VERSION_US_REV1)
void * g_Ovl1ERetained16[1] = {
    &g_collisionSurfaceExcludedFromTrace[64],
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialTiming13Record g_PlayerStateSpecialTiming_usrev1_CFA74 = {
    0,
    24105,
};
#endif

#if defined(VERSION_US_REV1)
RestBytes4 g_ovl1ERetained4Halfword_usrev1_CFA7C = {
    { 0, 2, 0, 0 },
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialCallbacks14PointerRecord g_PlayerStateSpecialCallbacks14Pointer_usrev1_CFA80 = {
    PACKED_CALLBACK_LOW(Player_DampMotion),
    PACKED_CALLBACK_LOW(Player_AbsorbImpact),
};
#endif

#if defined(VERSION_US_REV1)
void * g_Ovl1ERetained13[1] = {
    &g_collisionSurfaceExcludedFromTrace[64],
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialTiming14Record g_PlayerStateSpecialTiming_usrev1_CFA8C = {
    0,
    24105,
};
#endif

#if defined(VERSION_US_REV1)
Ovl1EOvl1ECppRetainedWords22Layout g_Ovl1ERetained_usrev1_CFA94 = {
    131072,
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialCallbacks15PointerRecord g_PlayerStateSpecialCallbacks15Pointer_usrev1_CFA98 = {
    PACKED_CALLBACK_LOW(Player_ResetMovementInput),
    (unsigned int)g_Player_UpdateSwimmingStateAddress_us_us_rev1,
};
#endif

#if defined(VERSION_US_REV1)
void * g_Ovl1ERetained1[1] = {
    &g_supportingPlatformCollisionQuery[1].info,
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialTiming15Record g_PlayerStateSpecialTiming_usrev1_CFAA4 = {
    256,
    24104,
};
#endif

#if defined(VERSION_US_REV1)
RestBytes4 g_ovl1ERetained9Halfword_usrev1_CFAAC = {
    { 0, 2, 0, 0 },
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialCallbacks16PointerRecord g_PlayerStateSpecialCallbacks16Pointer_usrev1_CFAB0 = {
    PACKED_CALLBACK_LOW(Player_ResetObjectVelocity),
    (unsigned int)g_Player_ResetObjectVelocityAddress_de_us_rev1,
};
#endif

#if defined(VERSION_US_REV1)
void * g_Ovl1ERetained6[1] = {
    &g_secondaryCollisionContext[1],
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialTiming16Record g_PlayerStateSpecialTiming_usrev1_CFABC = {
    524288,
    24100,
};
#endif

#if defined(VERSION_US_REV1)
Ovl1EOvl1ECppRetainedWords27Layout g_Ovl1ERetained_usrev1_CFAC4 = {
    131072,
};
#endif

#if defined(VERSION_US_REV1)
PlayerStateSpecialCallbacks17PointerRecord g_PlayerStateSpecialCallbacks17Pointer_usrev1_CFAC8 = {
    (unsigned int)g_playerNormalAuxiliaryStateLeadingTarget,
    (unsigned int)g_Player_AimPreviousPositionAtResetAddress_de_us_rev1,
};
#endif
