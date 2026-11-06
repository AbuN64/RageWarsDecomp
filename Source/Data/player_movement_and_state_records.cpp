#include "Common/packed_callback.h"
#include "Data/rest_source_records.h"
#include "include_asm.h"
#include "Ai/player_symbols.h"
#include "Data/Ovl1_e/g_playerstatespecialcallbacks05pointerwords1_ovl1e.h"
#include "Data/Ovl1_e/g_playerstatespecialcallbacks06pointerwords1_ovl1e.h"
#include "Data/Ovl1_e/g_playerstatespecialcallbacks07pointerwords1_ovl1e.h"
#include "Data/Ovl1_e/g_playerstatespecialcallbacks08pointerwords1_ovl1e.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Ai/nav_symbols.h"
#include "Ai/ai_shared_symbols.h"
#include "Ai/player_g18_symbols.h"
#include "Ai/ai_address_labels.h"

#if defined(VERSION_US) || defined(VERSION_US_REV1)
float g_playerAlternateMovementTuningPrimary[8] = {
    7.68f, 23.039999f, 5.7599998f, 7.68f,
    26.880001f, 5.7599998f, 10.24f, 0.768f,
};
#endif

#if defined(VERSION_US)
extern PlayerPoolInitWords k_OvlgameInitializeplayerpoolData;
#endif

#if defined(VERSION_US_REV1)
s32 g_playerAlternateMovementTuningPrimaryFlag = 1; /* trailing word of the row above */
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
#if defined(VERSION_US)
extern float g_playerAlternateMovementTuningSecondary[8];
#else
float g_playerAlternateMovementTuningSecondary[8] = {
    2.048f, 15.36f, 1.024f, 20.48f,
    1.536f, 20.48f, 153.59999f, 102.399994f,
};
#endif
#endif

#if defined(VERSION_US_REV1)
s32 g_playerAlternateMovementTuningSecondaryFlag = 1; /* trailing word of the row above */
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
float g_playerAlternateViewTuningPrimary[6] = {
    0.4f, 0.5f, 1.0f, 0.25f,
    -1.5707965f, 1.5707965f,
};
#endif

#if defined(VERSION_US_REV1)
float g_playerAlternateViewTuningSecondary[6] = {
    0.2f, 0.25f, 0.5f, 0.125f,
    -1.5707965f, 1.5707965f,
};
#endif

#if defined(VERSION_US_REV1)
float g_playerAlternateMovementTuningSecondaryHalf[9] = {
    1.024f, 7.68f, 0.512f, 10.24f,
    0.768f, 10.24f, 76.799995f, 51.199997f,
    0.0f,
};
#endif

#if defined(VERSION_US_REV1)
PlayerActionStateRecord g_playerActionStatesUsRev1[17] = {
    { (void *)g_Player_ZeroBodyVelocityAddress_us_rev1, (void *)g_Player_UpdateFlyModeAddress_us_us_rev1, (void *)&g_secondaryCollisionContext[6].info, 0, 1, 131072 },
    { 0, (void *)g_Player_UpdateFlyModeAddress_us_us_rev1, (void *)&g_secondaryCollisionContext[6].info, 0, 1, 131072 },
    { (void *)g_Player_ZeroBodyVelocityCallbackAddressDe, (void *)g_Player_UpdateStandingStateAddress_us_us_rev1, (void *)&g_secondaryCollisionContext[1].info, 0, 1, 131072 },
    { (void *)PACKED_CALLBACK_LOW(PlayerSpecial_LeadingEmptyCallback), (void *)addrLow_Playerai_UpdateWalkingMovement_us, (void *)&g_secondaryCollisionContext[1].info, 0, 2010, 196608 },
    { (void *)PACKED_CALLBACK_LOW(PlayerSpecial_TrailingEmptyCallback), (void *)g_Player_UpdateGroundMoveStateAddress_de_us_rev1, (void *)&g_secondaryCollisionContext[1].info, 0, 2660, 196608 },
    { (void *)PACKED_CALLBACK_LOW(Player_BeginJump), (void *)PACKED_CALLBACK_LOW(Player_UpdateJumpAscent), (void *)&g_collisionSurfaceExcludedFromTraceJumpEntry, 2048, 2030, 131072 },
    { 0, (void *)PACKED_CALLBACK_LOW(Player_UpdateJumpAirMotion), (void *)&g_collisionSurfaceExcludedFromTraceJumpEntry, 2048, 2030, 131072 },
    { (void *)PACKED_CALLBACK_LOW(Player_BeginLateralLeap), (void *)PACKED_CALLBACK_LOW(Player_UpdateLateralLeap), (void *)&g_secondaryCollisionContext[1].info, 0, 2030, 131072 },
    { 0, (void *)PACKED_CALLBACK_LOW(Player_UpdateLeapMotion), (void *)&g_secondaryCollisionContext[1].info, 0, 2030, 131072 },
    { (void *)PACKED_CALLBACK_LOW(Player_ClearGlobalFlagBit), (void *)g_Player_UpdateWadingStateAddress_us_us_rev1, (void *)&g_globalGameplayFlags, 128, 2210, 131072 },
    { (void *)PACKED_CALLBACK_LOW(Player_ClearGlobalFlagBit), (void *)g_Player_UpdateWadingStateAddress_us_us_rev1, (void *)&g_globalGameplayFlags, 128, 2210, 196608 },
    { (void *)PACKED_CALLBACK_LOW(Player_AbsorbImpact), (void *)g_Player_UpdateFloatingStateAddress_us_us_rev1, (void *)&g_pagerPageCounters[8], 64, 2210, 131072 },
    { (void *)PACKED_CALLBACK_LOW(Player_AbsorbImpact), (void *)g_Player_UpdateFloatingStateAddress_us_us_rev1, (void *)&g_pagerPageCounters[8], 64, 2210, 196608 },
    { (void *)PACKED_CALLBACK_LOW(Player_DampMotion), (void *)Player_AbsorbImpact, (void *)&g_collisionSurfaceExcludedFromTraceTravelEntry, 0, 2010, 131072 },
    { (void *)PACKED_CALLBACK_LOW(Player_DampMotion), (void *)Player_AbsorbImpact, (void *)&g_collisionSurfaceExcludedFromTraceTravelEntry, 0, 2010, 131072 },
    { (void *)PACKED_CALLBACK_LOW(Player_ResetMovementInput), (void *)g_Player_UpdateSwimmingStateAddress_us_us_rev1, (void *)&g_supportingPlatformCollisionQuery[1].info, 256, 2620, 131072 },
    { (void *)PACKED_CALLBACK_LOW(Player_ResetObjectVelocity), (void *)g_Player_ResetObjectVelocityAddress_de_us_rev1, (void *)&g_secondaryCollisionContext[1].info, 524288, 1, 131072 },
};
#endif
