#include "DATA/REST_SOURCE_RECORDS.H"
extern struct CVector3_t g_actorRadialDirections[];
#include "include_asm.h"
#include "TYPES.H"
#include "DATA/OVL1_C/NAVIGATION_CALLBACK_ADDRESS.H"
#include "DATA/OVL1_D/NAV_INITVISIBLEPURSUIT.H"
#include "DATA/OVL1_D/NAV_UPDATEVISIBLEPURSUIT_Nav4.H"
#include "DATA/ACTOR_STATE_CALLBACKS/ACTOR_STATE_CALLBACK_LABELS.H"
#if defined(VERSION_US)
/* 800C873C.CPP */
/* 800C87B0.CPP */
RestOvldat2ConstantWordsLayout4 k_Ovldat2ConstantWords = {
    { 0, 0, 0, 0, 0, 0 },
    { 1.0f, 0.70710677f, 0.0f, 0.70710677f, 1.0f, 0.0f, 0.0f, 0.70710677f, 0.0f, -0.70710677f, 0.0f, 0.0f, -1.0f, -0.70710677f, 0.0f, -0.70710677f, -1.0f, 0.0f, 0.0f, -0.70710677f, 0.0f, 0.70710677f },
    { (void *)&addrLow_Nav_CollectEnemyTargets, (void *)&addrLow_Target_UpdateTargetSelection, (void *)&addrLow_Wheel_AdvanceWheelProbe, (void *)&addrLow_Nav_RefineBallisticAim, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (void *)&addrLow_Nav_RebuildRequestedGoalRoute, (void *)&addrLow_Nav_CollectEnemyTargets, (void *)&addrLow_Target_UpdateTargetSelection, (void *)&addrLow_Nav_SelectPlayerState, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (void *)&addrLow_Nav_UpdateRouteIntermediateGoal, (void *)&addrLow_Nav_RebuildRequestedGoalRoute, (void *)&addrLow_Nav_CollectEnemyTargets, (void *)&addrLow_Target_UpdateTargetSelection, (void *)&addrLow_Nav_CheckCloseAttackRoute, (void *)&addrLow_Nav_RefineBallisticAim, (void *)&addrLow_Nav_SelectPlayerState, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (void *)&addrLow_Nav_RebuildRequestedGoalRoute, (void *)&addrLow_Nav_CollectEnemyTargets, (void *)&addrLow_Target_UpdateTargetSelection, (void *)&addrLow_Nav_SelectPlayerState, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (void *)&addrLow_Nav_RebuildRequestedGoalRoute, (void *)&addrLow_Nav_CollectEnemyTargets, (void *)&addrLow_Target_UpdateTargetSelection, (void *)&addrLow_UpdateCloseAttack, (void *)&addrLow_Nav_AdvancePickupRouteSelection, (void *)&addrLow_Nav_SelectWeaponFromThirdAmmoGroup, (void *)&addrLow_Nav_RefineBallisticAim, (void *)&addrLow_Nav_SelectPlayerState, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (void *)&addrLow_Nav_RebuildRequestedGoalRoute, (void *)&addrLow_Nav_CollectEnemyTargets, (void *)&addrLow_Target_UpdateTargetSelection, (void *)&addrLow_UpdateCloseAttack, (void *)&addrLow_Nav_AdvancePickupRouteSelection, (void *)&addrLow_Nav_SelectWeaponFromSecondAmmoGroup, (void *)&addrLow_Nav_RefineBallisticAim, (void *)&addrLow_Nav_SelectPlayerState, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (void *)&addrLow_Nav_RebuildRequestedGoalRoute, (void *)&addrLow_Nav_CollectEnemyTargets, (void *)&addrLow_Target_UpdateTargetSelection, (void *)&addrLow_UpdateCloseAttack, (void *)&addrLow_Nav_SelectWeaponFromFirstAmmoGroup, (void *)&addrLow_Nav_RefineBallisticAim, (void *)&addrLow_Nav_SelectPlayerState, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (void *)&addrLow_Nav_RebuildRequestedGoalRoute, (void *)&addrLow_Nav_CollectEnemyTargets, (void *)&addrLow_Target_UpdateTargetSelection, (void *)&addrLow_Nav_SelectSecondAmmoGroupVariantOne, (void *)&addrLow_Nav_RefineBallisticAim, (void *)&addrLow_Nav_SelectPlayerState, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (void *)&addrLow_Nav_RebuildRequestedGoalRoute, (void *)&addrLow_Nav_CollectEnemyTargets, (void *)&addrLow_Target_UpdateTargetSelection, (void *)&addrLow_Nav_SelectSecondAmmoGroupVariantTwo, (void *)&addrLow_Nav_RefineBallisticAim, (void *)&addrLow_Nav_SelectPlayerState, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (void *)&addrLow_Nav_SelectPickupGoal, (void *)&addrLow_Nav_RebuildRequestedGoalRoute, (void *)&addrLow_Nav_CollectEnemyTargets, (void *)&addrLow_Target_UpdateTargetSelection, (void *)&addrLow_Nav_SelectSecondAmmoGroupVariantTwo, (void *)&addrLow_Nav_RefineBallisticAim, (void *)&addrLow_Nav_SelectPlayerState, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (void *)&addrLow_Nav_SelectCloseAttackPickupGoal, (void *)&addrLow_Nav_RebuildRequestedGoalRoute, (void *)&addrLow_Nav_CollectEnemyTargets, (void *)&addrLow_Target_UpdateTargetSelection, (void *)&addrLow_Nav_SelectPlayerState, (void *)&addrLow_Nav_SelectWeaponFromSecondAmmoGroup, (void *)&addrLow_Nav_RefineBallisticAim, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (void *)&addrLow_Nav_SelectChaseObjectGoal, (void *)&addrLow_Nav_RebuildRequestedGoalRoute, (void *)&addrLow_Nav_CollectEnemyTargets, (void *)&addrLow_Target_UpdateTargetSelection, (void *)&addrLow_Nav_SelectWeaponFromSecondAmmoGroup, (void *)&addrLow_Nav_RefineBallisticAim, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (void *)&addrLow_Nav_SelectStationaryObjectGoal, (void *)&addrLow_Nav_RebuildRequestedGoalRoute, (void *)&addrLow_Nav_CollectEnemyTargets, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (void *)&addrLow_Nav_RebuildRequestedGoalRoute, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (void *)&addrLow_Nav_RebuildRequestedGoalRoute, (void *)&addrLow_Nav_CollectEnemyTargets, (void *)&addrLow_Target_UpdateTargetSelection, (void *)&addrLow_Nav_SelectWeaponFromThirdAmmoGroup, (void *)&addrLow_Nav_RefineBallisticAim, (void *)&addrLow_Nav_SelectPlayerState, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (void *)((char *)&g_actorRadialDirections + 176), (void *)((char *)&g_actorRadialDirections + 256), (void *)((char *)&g_actorRadialDirections + 336), (void *)((char *)&g_actorRadialDirections + 416), (void *)((char *)&g_actorRadialDirections + 496), (void *)((char *)&g_actorRadialDirections + 576), (void *)((char *)&g_actorRadialDirections + 656), (void *)((char *)&g_actorRadialDirections + 736), (void *)((char *)&g_actorRadialDirections + 816), (void *)((char *)&g_actorRadialDirections + 896), (void *)((char *)&g_actorRadialDirections + 976), (void *)((char *)&g_actorRadialDirections + 1056), (void *)((char *)&g_actorRadialDirections + 1136), (void *)((char *)&g_actorRadialDirections + 1216) },
    "OT_FLAGe\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
    { (void *)&addrLow_Nav_ResetPatrolRouteSelection, (void *)&addrLow_Nav_UpdatePatrolRoute, 0, 0 },
    1.0f,
    { 5, 0, 1 },
    { (void *)&addrLow_Nav_ResetTargetFollowStateDe, (void *)&addrLow_Nav_UpdateTargetRouteFollow, 0, 0 },
    1.0f,
    { 5, 0, 2 },
    { (void *)&addrLow_Nav_InitRoamingWithJumps, (void *)&addrLow_Nav_UpdateRoamingWithJumps, 0, 0 },
    1.0f,
    { 5, 0, 3 },
    { (void *)&addrLow_Nav_InitPursuitStrafe, (void *)&addrLow_Nav_UpdatePursuitStrafe, 0, 0 },
    1.0f,
    { 5, 0, 4 },
    { (void *)&addrLow_Nav_InitRangedCombat, (void *)&addrLow_Nav_UpdateRangedCombat, 0, 0 },
    1.0f,
    { 5, 0, 5 },
    { (void *)&addrLow_Nav_InitCloseCombat, (void *)&addrLow_Nav_UpdateCloseCombat, 0, 0 },
    1.0f,
    { 5, 0, 6 },
    { (void *)&addrLow_Nav_InitCombatTargetApproach, (void *)&addrLow_Nav_ApproachCombatTargetAlongRoute, 0, 0 },
    1.0f,
    { 5, 0, 7 },
    { (void *)&addrLow_Nav_InitRetreatMovement, (void *)&addrLow_Nav_UpdateRetreatMovement, 0, 0 },
    1.0f,
    { 5, 0, 8 },
    { (void *)&addrLow_Nav_ResetObjectArrivalChase, (void *)&addrLow_Nav_UpdateObjectArrivalChase, 0, 0 },
    1.0f,
    { 5, 0, 9 },
    { (void *)&addrLow_Nav_InitUnclaimedMarkerSearch, (void *)&addrLow_Nav_SeekUnclaimedMarker, 0, 0 },
    1.0f,
    { 5, 0, 10 },
    { (void *)&addrLow_Nav_InitCarrierRoute, (void *)&addrLow_Nav_FollowMarkerCarrierRoute, 0, 0 },
    1.0f,
    { 5, 0, 11 },
    { (void *)&addrLow_Nav_InitTimedJumpRoute, (void *)&addrLow_Nav_UpdateTransientJumpRoute, 0, 0 },
    1.0f,
    { 5, 0, 12 },
    { (void *)&addrLow_Nav_InitNearbyUnrestrictedGoal, (void *)&addrLow_Nav_SeekNearbyUnrestrictedGoal, 0, 0 },
    1.0f,
    { 5, 0, 13 },
    { (void *)&addrLow_Nav_InitVisiblePursuit, (void *)&addrLow_Nav_UpdateVisiblePursuit, 0, 0 },
    1.0f,
    { 5, 0, -1, 0, 0, 0, 0, 0, 0, 0 },
};
#endif
