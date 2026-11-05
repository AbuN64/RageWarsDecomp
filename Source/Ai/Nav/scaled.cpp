#include "Data/rest_source_records.h"
#include "Ai/ai_shared_symbols.h"
#include "Data/Ovl1_c/navigation_callback_address.h"
#include "Ai/ai_functions.h"
#include "Ai/Nav/carrier.h"
#include "Ai/Nav/combatinit.h"
#include "Ai/Nav/farthest.h"
#include "Ai/Nav/jumproute.h"
#include "Ai/Nav/nav_initpursuitstrafe.h"
#include "Ai/Nav/nav_resetobjectarrivalchase.h"
#include "Ai/Nav/nav_selectpickupgoal.h"
#include "Ai/Nav/nav_updateclosecombat.h"
#include "Ai/Nav/nav_updaterangedcombat.h"
#include "Ai/Nav/nav_updatevisiblepursuit.h"
#include "Ai/Nav/roam.h"
#include "Ai/Nav/targetfollow.h"
#include "Ai/Nav/wheel.h"
#include "Attack/attack.h"
#include "Fx/target.h"
#include "Game/weaponselect.h"
#include "pickup.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Data/Ovl1_d/nav_initvisiblepursuit.h"
#include "Data/Ovl1_d/addrlow_nav_updatevisiblepursuit.h"
#include "Data/Actor_state_callbacks/actor_state_callback_labels.h"
#include "Ai/nav_behavior_callback_rows.h"
#include "Ai/Nav/portal_dispatchactorbehavior_data.h"
#include "Common/vector.h"

#if defined(VERSION_DE)
NavBehaviorCallbackRowsLayout k_navBehaviorCallbackRowsData = {
    /* routeModeIds */ {
        0x00000003, 0x00000000, 0x00000004, 0x00000000, 0x00000003, 0x00000001, 0x00000000, 0x00000005,
        0x00000005, 0x00000000, 0x00000003, 0x00000000, 0x00000002, 0x00000006, 0x00000006, 0x00000001,
        0x00000000, 0x00000001, 0x00000008, 0x00000000, 0x00000003, 0x00000000, 0x00000008, 0x00000000,
        0x00000008, 0x00000007, 0x00000007, 0x00000001, 0x00000004, 0x00000005, 0x00000005, 0x00000000,
        0x00000003, 0x00000000, 0x00000008, 0x00000000, 0x00000008, 0x00000000, 0x00000008, 0x00000000,
        0x00000008, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    },
    /* compassDirectionBits */ {
        0x3F800000, 0x3F3504F3, 0x00000000, 0x3F3504F3, 0x3F800000, 0x00000000, 0x00000000, 0x3F3504F3,
        0x00000000, 0xBF3504F3, 0x00000000, 0x00000000, 0xBF800000, 0xBF3504F3, 0x00000000, 0xBF3504F3,
        0xBF800000, 0x00000000, 0x00000000, 0xBF3504F3, 0x00000000, 0x3F3504F3,
    },
    /* behaviorCallbackSlots */ {
        (void *)Nav_CollectEnemyTargets, (void *)Target_UpdateTargetSelection, (void *)Wheel_AdvanceWheelProbe, (void *)Nav_RefineBallisticAim, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, (void *)Nav_RebuildRequestedGoalRoute, (void *)Nav_CollectEnemyTargets, (void *)Target_UpdateTargetSelection, (void *)Nav_SelectPlayerState,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, (void *)Nav_UpdateRouteIntermediateGoal, (void *)Nav_RebuildRequestedGoalRoute,
        (void *)Nav_CollectEnemyTargets, (void *)Target_UpdateTargetSelection, (void *)Nav_CheckCloseAttackRoute, (void *)Nav_RefineBallisticAim, (void *)Nav_SelectPlayerState, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        (void *)Nav_RebuildRequestedGoalRoute, (void *)Nav_CollectEnemyTargets, (void *)Target_UpdateTargetSelection, (void *)Nav_SelectPlayerState, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, (void *)Nav_RebuildRequestedGoalRoute, (void *)Nav_CollectEnemyTargets, (void *)Target_UpdateTargetSelection, (void *)UpdateCloseAttack,
        (void *)Nav_AdvancePickupRouteSelection, (void *)Nav_SelectWeaponFromThirdAmmoGroup, (void *)Nav_RefineBallisticAim, (void *)Nav_SelectPlayerState, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, (void *)Nav_RebuildRequestedGoalRoute, (void *)Nav_CollectEnemyTargets,
        (void *)Target_UpdateTargetSelection, (void *)UpdateCloseAttack, (void *)Nav_AdvancePickupRouteSelection, (void *)Nav_SelectWeaponFromSecondAmmoGroup, (void *)Nav_RefineBallisticAim, (void *)Nav_SelectPlayerState,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        (void *)Nav_RebuildRequestedGoalRoute, (void *)Nav_CollectEnemyTargets, (void *)Target_UpdateTargetSelection, (void *)UpdateCloseAttack, (void *)Nav_SelectWeaponFromFirstAmmoGroup, (void *)Nav_RefineBallisticAim,
        (void *)Nav_SelectPlayerState, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, (void *)Nav_RebuildRequestedGoalRoute, (void *)Nav_CollectEnemyTargets, (void *)Target_UpdateTargetSelection, (void *)Nav_SelectSecondAmmoGroupVariantOne,
        (void *)Nav_RefineBallisticAim, (void *)Nav_SelectPlayerState, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, (void *)Nav_RebuildRequestedGoalRoute, (void *)Nav_CollectEnemyTargets,
        (void *)Target_UpdateTargetSelection, (void *)Nav_SelectSecondAmmoGroupVariantTwo, (void *)Nav_RefineBallisticAim, (void *)Nav_SelectPlayerState, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        (void *)Nav_SelectPickupGoal, (void *)Nav_RebuildRequestedGoalRoute, (void *)Nav_CollectEnemyTargets, (void *)Target_UpdateTargetSelection, (void *)Nav_SelectSecondAmmoGroupVariantTwo, (void *)Nav_RefineBallisticAim,
        (void *)Nav_SelectPlayerState, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, (void *)Nav_SelectCloseAttackPickupGoal, (void *)Nav_RebuildRequestedGoalRoute, (void *)Nav_CollectEnemyTargets, (void *)Target_UpdateTargetSelection,
        (void *)Nav_SelectPlayerState, (void *)Nav_SelectWeaponFromSecondAmmoGroup, (void *)Nav_RefineBallisticAim, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, (void *)Nav_SelectChaseObjectGoal, (void *)Nav_RebuildRequestedGoalRoute,
        (void *)Nav_CollectEnemyTargets, (void *)Target_UpdateTargetSelection, (void *)Nav_SelectWeaponFromSecondAmmoGroup, (void *)Nav_RefineBallisticAim, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        (void *)Nav_SelectStationaryObjectGoal, (void *)Nav_RebuildRequestedGoalRoute, (void *)Nav_CollectEnemyTargets, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, (void *)Nav_RebuildRequestedGoalRoute, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, (void *)Nav_RebuildRequestedGoalRoute, (void *)Nav_CollectEnemyTargets,
        (void *)Target_UpdateTargetSelection, (void *)Nav_SelectWeaponFromThirdAmmoGroup, (void *)Nav_RefineBallisticAim, (void *)Nav_SelectPlayerState, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        (void *)g_navBehaviorCallbackRows[0], (void *)g_navBehaviorCallbackRows[1], (void *)g_navBehaviorCallbackRows[2], (void *)g_navBehaviorCallbackRows[3], (void *)g_navBehaviorCallbackRows[4], (void *)g_navBehaviorCallbackRows[5],
        (void *)g_navBehaviorCallbackRows[6], (void *)g_navBehaviorCallbackRows[7], (void *)g_navBehaviorCallbackRows[8], (void *)g_navBehaviorCallbackRows[9], (void *)g_navBehaviorCallbackRows[10], (void *)g_navBehaviorCallbackRows[11],
        (void *)g_navBehaviorCallbackRows[12], (void *)g_navBehaviorCallbackRows[13], 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0,
    },
    /* flankRowWords */ {
        (unsigned int)Nav_ResetPatrolRouteSelection, (unsigned int)Nav_UpdatePatrolRoute, 0x00000000, 0x00000000, 0x3F800000, 0x00000005, 0x00000000, 0x00000001,
        (unsigned int)Nav_ResetTargetFollowStateDe, (unsigned int)Nav_UpdateTargetRouteFollow, 0x00000000, 0x00000000, 0x3F800000, 0x00000005, 0x00000000, 0x00000002,
        (unsigned int)Nav_InitRoamingWithJumps, (unsigned int)Nav_UpdateRoamingWithJumps, 0x00000000, 0x00000000, 0x3F800000, 0x00000005, 0x00000000, 0x00000003,
        (unsigned int)Nav_InitPursuitStrafe, (unsigned int)Nav_UpdatePursuitStrafe, 0x00000000, 0x00000000, 0x3F800000, 0x00000005, 0x00000000, 0x00000004,
        (unsigned int)Nav_InitRangedCombat, (unsigned int)Nav_UpdateRangedCombat, 0x00000000, 0x00000000, 0x3F800000, 0x00000005, 0x00000000, 0x00000005,
        (unsigned int)Nav_InitCloseCombat, (unsigned int)Nav_UpdateCloseCombat, 0x00000000, 0x00000000, 0x3F800000, 0x00000005, 0x00000000, 0x00000006,
        (unsigned int)Nav_InitCombatTargetApproach, (unsigned int)Nav_ApproachCombatTargetAlongRoute, 0x00000000, 0x00000000, 0x3F800000, 0x00000005, 0x00000000, 0x00000007,
        (unsigned int)Nav_InitRetreatMovement, (unsigned int)Nav_UpdateRetreatMovement, 0x00000000, 0x00000000, 0x3F800000, 0x00000005, 0x00000000, 0x00000008,
        (unsigned int)Nav_ResetObjectArrivalChase, 0x00212FE0, 0x00000000, 0x00000000, 0x3F800000, 0x00000005, 0x00000000, 0x00000009,
        (unsigned int)Nav_InitUnclaimedMarkerSearch, (unsigned int)Nav_SeekUnclaimedMarker, 0x00000000, 0x00000000, 0x3F800000, 0x00000005, 0x00000000, 0x0000000A,
        (unsigned int)Nav_InitCarrierRoute, (unsigned int)Nav_FollowMarkerCarrierRoute, 0x00000000, 0x00000000, 0x3F800000, 0x00000005, 0x00000000, 0x0000000B,
        (unsigned int)Nav_InitTimedJumpRoute, (unsigned int)Nav_UpdateTransientJumpRoute, 0x00000000, 0x00000000, 0x3F800000, 0x00000005, 0x00000000, 0x0000000C,
        (unsigned int)Nav_InitNearbyUnrestrictedGoal, (unsigned int)Nav_SeekNearbyUnrestrictedGoal, 0x00000000, 0x00000000, 0x3F800000, 0x00000005, 0x00000000, 0x0000000D,
        (unsigned int)Nav_InitVisiblePursuit, (unsigned int)Nav_UpdateVisiblePursuit, 0x00000000, 0x00000000, 0x3F800000, 0x00000005, 0x00000000, 0xFFFFFFFF,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    },
    /* tailConstantWords */ {
        0x00000000, 0x00000001, 0x000006A5, 0x00000002, 0x000006A6, 0x00000004, 0x000006A7, 0x00000008,
        0x000006A8, 0x00000010, 0x000006A9, 0x00000020, 0x000006AA, 0x00000040, 0x00000898, 0x00000080,
        0x00000898, 0x00000100, 0x00000898, 0x00000200, 0x00000898, 0x00000400, 0x00000898, 0x00000800,
        0x00000898, 0x00001000, 0x00000898, 0x00002000, 0x00000898, 0x00004000, 0x00000898, 0x00008000,
        0x00000898, 0x00010000, 0x00000898, 0x00020000, 0x00000898, 0x00040000, 0x00000898, 0x00080000,
        0x00000898, 0x00100000, 0x00000898, 0x00200000, 0x00000898, 0x00400000, 0x00000898, 0x00800000,
        0x00000898, 0x01000000, 0x00000898, 0x02000000, 0x00000898, 0x04000000, 0x00000898, 0x08000000,
        0x00000898, 0x10000000, 0x00000898, 0x20000000, 0x00000898, 0x40000000, 0x00000898, 0x80000000,
        0x00000898, 0x00000000, 0x00000000, 0x00000001, 0x00000898, 0x00000000, 0x00000000, 0x00040000,
        0x000C0000, 0x00010000, 0x00050000, 0x00040000, 0x000C0000, 0x00080000, 0x000A0000, 0x00020000,
        0x00030000, 0x41F00000, 0x42400000, 0x43020000,
    },
};
#endif

const float k_NavQuarterWords[1] = {
    0.25f,
};

#if defined(VERSION_DE)
/* DE-only constant block after k_NavQuarterWords; nothing reads these words, so their types follow the values. */
const float g_teamWheelTuningFloats[3] = {
    0.09f, 0.05f, 0.5f,
};

/* stale word completing the 16-byte literal group (0x000C0000 here, 0x2E656F73 in the US image); read by nothing */
const u32 g_teamWheelTuningStaleWord = 0x000C0000;

/* eight (id, 0) halfword pairs */
const u16 g_teamWheelSlotOrder[8][2] = {
    { 1, 0 }, { 5, 0 }, { 4, 0 }, { 12, 0 }, { 8, 0 }, { 10, 0 }, { 2, 0 }, { 3, 0 },
};

/* the last word is g_teamWheelScalePoolPrefix; g_teamWheelInitialSlotScale (0.25f) follows */
const float g_teamWheelScaleLiterals[3] = {
    30.0f, 48.0f, 130.0f,
};
#endif

#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* behavior kind (0-8) per actor type, two weapon gears each: indexed [selectedAction * 2 + gear - 1] and switched on by Portal_DispatchActorBehavior */
s32 g_actorBehaviorDispatchModes[40] = {
    0, 4,
    0, 3,
    1, 0,
    5, 5,
    0, 3,
    0, 2,
    6, 6,
    1, 0,
    1, 8,
    0, 3,
    0, 8,
    0, 8,
    7, 7,
    1, 4,
    5, 5,
    0, 3,
    0, 8,
    0, 8,
    0, 8,
    0, 8,
};
#endif

#if defined(VERSION_US_REV1)
unsigned int g_navScaledRouteFlagWord[1] = {
    0x00000100,
};
#endif

#if defined(VERSION_US_REV1)
/* 16 zero bytes ahead of the direction table, read by no instruction */
unsigned int g_actorRadialDirectionsZeroLead[4] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

/* eight unit directions in the xz plane, 45 degrees apart starting at +z; read by Wheel_MeasureWheelReach / Wheel_MeasureWheelClearance */
#endif

#if defined(VERSION_US_REV1)
/* 16 zero bytes ahead of the direction table, read by no instruction */

/* eight unit directions in the xz plane, 45 degrees apart starting at +z; read by Wheel_MeasureWheelReach / Wheel_MeasureWheelClearance */
CVector3 g_actorRadialDirections[8] = {
    { 0.0f, 0.0f, 1.0f },
    { 0.70710677f, 0.0f, 0.70710677f },
    { 1.0f, 0.0f, 0.0f },
    { 0.70710677f, 0.0f, -0.70710677f },
    { 0.0f, 0.0f, -1.0f },
    { -0.70710677f, 0.0f, -0.70710677f },
    { -1.0f, 0.0f, 0.0f },
    { -0.70710677f, 0.0f, 0.70710677f },
};
#endif

#if defined(VERSION_US)
Ovldat2ConstantWordsLayout k_playerNavDirectionAndHandlerTable = {
    { 0, 0, 0, 0, 0, 0 },
    { 1.0f, 0.70710677f, 0.0f, 0.70710677f, 1.0f, 0.0f, 0.0f, 0.70710677f, 0.0f, -0.70710677f, 0.0f, 0.0f, -1.0f, -0.70710677f, 0.0f, -0.70710677f, -1.0f, 0.0f, 0.0f, -0.70710677f, 0.0f, 0.70710677f },
    { { 0x00210230 }, { 0x0020F6C0 }, { 0x00210E88 }, { 0x0020DDE0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0x0020EAE0 }, { 0x00210230 }, { 0x0020F6C0 }, { 0x0020FA10 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0x0020ED50 }, { 0x0020EAE0 }, { 0x00210230 }, { 0x0020F6C0 }, { 0x00210180 }, { 0x0020DDE0 }, { 0x0020FA10 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0x0020EAE0 }, { 0x00210230 }, { 0x0020F6C0 }, { 0x0020FA10 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0x0020EAE0 }, { 0x00210230 }, { 0x0020F6C0 }, { 0x0020DC10 }, { 0x0020D370 }, { 0x00210068 }, { 0x0020DDE0 }, { 0x0020FA10 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0x0020EAE0 }, { 0x00210230 }, { 0x0020F6C0 }, { 0x0020DC10 }, { 0x0020D370 }, { 0x00210040 }, { 0x0020DDE0 }, { 0x0020FA10 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0x0020EAE0 }, { 0x00210230 }, { 0x0020F6C0 }, { 0x0020DC10 }, { 0x00210018 }, { 0x0020DDE0 }, { 0x0020FA10 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0x0020EAE0 }, { 0x00210230 }, { 0x0020F6C0 }, { 0x00210090 }, { 0x0020DDE0 }, { 0x0020FA10 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0x0020EAE0 }, { 0x00210230 }, { 0x0020F6C0 }, { 0x002100B8 }, { 0x0020DDE0 }, { 0x0020FA10 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0x0020EF60 }, { 0x0020EAE0 }, { 0x00210230 }, { 0x0020F6C0 }, { 0x002100B8 }, { 0x0020DDE0 }, { 0x0020FA10 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0x0020F2A8 }, { 0x0020EAE0 }, { 0x00210230 }, { 0x0020F6C0 }, { 0x0020FA10 }, { 0x00210040 }, { 0x0020DDE0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0x0020F388 }, { 0x0020EAE0 }, { 0x00210230 }, { 0x0020F6C0 }, { 0x00210040 }, { 0x0020DDE0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0x0020F444 }, { 0x0020EAE0 }, { 0x00210230 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0x0020EAE0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0x0020EAE0 }, { 0x00210230 }, { 0x0020F6C0 }, { 0x00210068 }, { 0x0020DDE0 }, { 0x0020FA10 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 } },
    { &k_playerNavDirectionAndHandlerTable.references2[20], &k_playerNavDirectionAndHandlerTable.references2[40], &k_playerNavDirectionAndHandlerTable.references2[60], &k_playerNavDirectionAndHandlerTable.references2[80], &k_playerNavDirectionAndHandlerTable.references2[100], &k_playerNavDirectionAndHandlerTable.references2[120], &k_playerNavDirectionAndHandlerTable.references2[140], &k_playerNavDirectionAndHandlerTable.references2[160], &k_playerNavDirectionAndHandlerTable.references2[180], &k_playerNavDirectionAndHandlerTable.references2[200], &k_playerNavDirectionAndHandlerTable.references2[220], &k_playerNavDirectionAndHandlerTable.references2[240], &k_playerNavDirectionAndHandlerTable.references2[260], &k_playerNavDirectionAndHandlerTable.references2[280] },
    "OT_FLAGe\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    {
        { { { 0x00212FBC }, { 0x00212E10 }, { 0 }, { 0 } }, 1.0f, { 5, 0, 1 } },
        { { { 0x00212D60 }, { 0x00212D94 }, { 0 }, { 0 } }, 1.0f, { 5, 0, 2 } },
        { { { 0x002136EC }, { 0x00213500 }, { 0 }, { 0 } }, 1.0f, { 5, 0, 3 } },
        { { { 0x002123DC }, { 0x00211120 }, { 0 }, { 0 } }, 1.0f, { 5, 0, 4 } },
        { { { 0x00212450 }, { 0x00211470 }, { 0 }, { 0 } }, 1.0f, { 5, 0, 5 } },
        { { { 0x00212524 }, { 0x00211A7C }, { 0 }, { 0 } }, 1.0f, { 5, 0, 6 } },
        { { { 0x002127F4 }, { 0x00212828 }, { 0 }, { 0 } }, 1.0f, { 5, 0, 7 } },
        { { { 0x0021290C }, { 0x00212948 }, { 0 }, { 0 } }, 1.0f, { 5, 0, 8 } },
        { { { 0x002131AC }, { 0x00212FE0 }, { 0 }, { 0 } }, 1.0f, { 5, 0, 9 } },
        { { { 0x00212BD0 }, { 0x00212C04 }, { 0 }, { 0 } }, 1.0f, { 5, 0, 10 } },
        { { { 0x00212C90 }, { 0x00212CC4 }, { 0 }, { 0 } }, 1.0f, { 5, 0, 11 } },
        { { { 0x002131E0 }, { 0x0021321C }, { 0 }, { 0 } }, 1.0f, { 5, 0, 12 } },
        { { { 0x00212A40 }, { 0x00212A7C }, { 0 }, { 0 } }, 1.0f, { 5, 0, 13 } }
    },
    { { 0x002125F0 }, { 0x00212088 }, { 0 }, { 0 } },
    1.0f,
    { 5, 0, -1, 0, 0, 0, 0, 0, 0, 0 }
};
#endif

#if defined(VERSION_US)
/* Movement tuning shared with the decode block: scales, nine state masks, then limits. */
const DecodeEncodedWordsBlock1Layout k_ResourcesData = {
    { 0.09f, 0.05f, 0.5f },
    { 0x2E656F73, 0x00010000, 0x00050000, 0x00040000, 0x000C0000, 0x00080000, 0x000A0000, 0x00020000, 0x00030000 },
    { 30.0f, 48.0f, 130.0f },
};
#endif
