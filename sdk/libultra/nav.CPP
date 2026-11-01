#include "../include/libgultra.h"

#if defined(VERSION_EU_X)
extern char Nav_AdvancePickupRouteSelection_Address[];
extern char UpdateCloseAttack_Address[];
extern char Nav_RefineBallisticAim_Address[];
extern char Nav_RebuildRequestedGoalRoute_Address[];
extern char Nav_UpdateRouteIntermediateGoal_Address[];
extern char Nav_SelectPickupGoal_Address[];
extern char Nav_SelectCloseAttackPickupGoal_Address[];
extern char Nav_SelectChaseObjectGoal_Address[];
extern char Nav_SelectStationaryObjectGoal_Address[];
extern char Target_UpdateTargetSelection_Address[];
extern char Nav_SelectPlayerState_Address[];
extern char g_Nav_SelectWeaponFromFirstAmmoGroupEncodedCallback[];
extern char g_Nav_SelectWeaponFromSecondAmmoGroupEncodedCallback[];
extern char g_Nav_SelectWeaponFromThirdAmmoGroupEncodedCallback[];
extern char g_Nav_SelectSecondAmmoGroupVariantOneEncodedCallback[];
extern char g_Nav_SelectSecondAmmoGroupVariantTwoEncodedCallback[];
extern char Nav_CheckCloseAttackRoute_Address[];
extern char Nav_CollectEnemyTargets_Address[];
extern char Wheel_AdvanceWheelProbe_Address[];
extern char Nav_UpdatePursuitStrafe_Address[];
extern char Nav_UpdateRangedCombat_Address[];
extern char Nav_UpdateCloseCombat_Address[];
extern char Nav_UpdateVisiblePursuit_Address[];
extern char Nav_InitPursuitStrafe_Address[];
extern char Nav_InitRangedCombat_Address[];
extern char Nav_InitCloseCombat_Address[];
extern char Nav_InitVisiblePursuit_Address[];
extern char g_Nav_InitCombatTargetApproachEncodedCallback[];
extern char Nav_ApproachCombatTargetAlongRoute_Address[];
extern char g_Nav_InitRetreatMovementEncodedCallback[];
extern char Nav_UpdateRetreatMovement_Address[];
extern char g_Nav_InitNearbyUnrestrictedGoalEncodedCallback[];
extern char Nav_SeekNearbyUnrestrictedGoal_Address[];
extern char g_Nav_InitUnclaimedMarkerSearchEncodedCallback[];
extern char Nav_SeekUnclaimedMarker_Address[];
extern char g_Nav_InitCarrierRouteEncodedCallback[];
extern char Nav_FollowMarkerCarrierRoute_Address[];
extern char Nav_InitTargetRouteFollow_Address[];
extern char Nav_UpdateTargetRouteFollow_Address[];
extern char Nav_UpdatePatrolRoute_Address[];
extern char Nav_ResetPatrolRouteSelection_Address[];
extern char Nav_UpdateObjectArrivalChase_Address[];
extern char Nav_ResetObjectArrivalChase_Address[];
extern char Nav_InitTimedJumpRoute_Address[];
extern char Nav_UpdateTransientJumpRoute_Address[];
extern char Nav_UpdateRoamingWithJumps_Address[];
extern char Nav_InitRoamingWithJumps_Address[];
extern char g_weapon_InitializeChargeForWeaponFiveEntry[];
unsigned int k_NavEncodedWordsBlock3[596] = {
    0x00000100, 0x00000000, 0x00000004, 0x00000000, 0x00000003, 0x00000001, 0x00000000, 0x00000005,
    0x00000005, 0x00000000, 0x00000003, 0x00000000, 0x00000002, 0x00000006, 0x00000006, 0x00000001,
    0x00000000, 0x00000001, 0x00000008, 0x00000000, 0x00000003, 0x00000000, 0x00000008, 0x00000000,
    0x00000008, 0x00000007, 0x00000007, 0x00000001, 0x00000004, 0x00000005, 0x00000005, 0x00000000,
    0x00000003, 0x00000000, 0x00000008, 0x00000000, 0x00000008, 0x00000000, 0x00000008, 0x00000000,
    0x00000008, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000,
    0x3F3504F3, 0x00000000, 0x3F3504F3, 0x3F800000, 0x00000000, 0x00000000, 0x3F3504F3, 0x00000000,
    0xBF3504F3, 0x00000000, 0x00000000, 0xBF800000, 0xBF3504F3, 0x00000000, 0xBF3504F3, 0xBF800000,
    0x00000000, 0x00000000, 0xBF3504F3, 0x00000000, 0x3F3504F3, (unsigned int)Nav_CollectEnemyTargets_Address, (unsigned int)Target_UpdateTargetSelection_Address, (unsigned int)Wheel_AdvanceWheelProbe_Address,
    (unsigned int)Nav_RefineBallisticAim_Address, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, (unsigned int)Nav_RebuildRequestedGoalRoute_Address, (unsigned int)Nav_CollectEnemyTargets_Address, (unsigned int)Target_UpdateTargetSelection_Address, (unsigned int)Nav_SelectPlayerState_Address, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, (unsigned int)Nav_UpdateRouteIntermediateGoal_Address, (unsigned int)Nav_RebuildRequestedGoalRoute_Address, (unsigned int)Nav_CollectEnemyTargets_Address,
    (unsigned int)Target_UpdateTargetSelection_Address, (unsigned int)Nav_CheckCloseAttackRoute_Address, (unsigned int)Nav_RefineBallisticAim_Address, (unsigned int)Nav_SelectPlayerState_Address, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, (unsigned int)Nav_RebuildRequestedGoalRoute_Address, (unsigned int)Nav_CollectEnemyTargets_Address, (unsigned int)Target_UpdateTargetSelection_Address, (unsigned int)Nav_SelectPlayerState_Address, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, (unsigned int)Nav_RebuildRequestedGoalRoute_Address, (unsigned int)Nav_CollectEnemyTargets_Address, (unsigned int)Target_UpdateTargetSelection_Address,
    (unsigned int)UpdateCloseAttack_Address, (unsigned int)Nav_AdvancePickupRouteSelection_Address, (unsigned int)g_Nav_SelectWeaponFromThirdAmmoGroupEncodedCallback, (unsigned int)Nav_RefineBallisticAim_Address, (unsigned int)Nav_SelectPlayerState_Address, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, (unsigned int)Nav_RebuildRequestedGoalRoute_Address, (unsigned int)Nav_CollectEnemyTargets_Address, (unsigned int)Target_UpdateTargetSelection_Address, (unsigned int)UpdateCloseAttack_Address, (unsigned int)Nav_AdvancePickupRouteSelection_Address, (unsigned int)g_Nav_SelectWeaponFromSecondAmmoGroupEncodedCallback, (unsigned int)Nav_RefineBallisticAim_Address,
    (unsigned int)Nav_SelectPlayerState_Address, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, (unsigned int)Nav_RebuildRequestedGoalRoute_Address, (unsigned int)Nav_CollectEnemyTargets_Address, (unsigned int)Target_UpdateTargetSelection_Address,
    (unsigned int)UpdateCloseAttack_Address, (unsigned int)g_Nav_SelectWeaponFromFirstAmmoGroupEncodedCallback, (unsigned int)Nav_RefineBallisticAim_Address, (unsigned int)Nav_SelectPlayerState_Address, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, (unsigned int)Nav_RebuildRequestedGoalRoute_Address, (unsigned int)Nav_CollectEnemyTargets_Address, (unsigned int)Target_UpdateTargetSelection_Address, (unsigned int)g_Nav_SelectSecondAmmoGroupVariantOneEncodedCallback, (unsigned int)Nav_RefineBallisticAim_Address, (unsigned int)Nav_SelectPlayerState_Address, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, (unsigned int)Nav_RebuildRequestedGoalRoute_Address, (unsigned int)Nav_CollectEnemyTargets_Address, (unsigned int)Target_UpdateTargetSelection_Address,
    (unsigned int)g_Nav_SelectSecondAmmoGroupVariantTwoEncodedCallback, (unsigned int)Nav_RefineBallisticAim_Address, (unsigned int)Nav_SelectPlayerState_Address, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, (unsigned int)Nav_SelectPickupGoal_Address, (unsigned int)Nav_RebuildRequestedGoalRoute_Address, (unsigned int)Nav_CollectEnemyTargets_Address, (unsigned int)Target_UpdateTargetSelection_Address, (unsigned int)g_Nav_SelectSecondAmmoGroupVariantTwoEncodedCallback, (unsigned int)Nav_RefineBallisticAim_Address, (unsigned int)Nav_SelectPlayerState_Address,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, (unsigned int)Nav_SelectCloseAttackPickupGoal_Address, (unsigned int)Nav_RebuildRequestedGoalRoute_Address, (unsigned int)Nav_CollectEnemyTargets_Address,
    (unsigned int)Target_UpdateTargetSelection_Address, (unsigned int)Nav_SelectPlayerState_Address, (unsigned int)g_Nav_SelectWeaponFromSecondAmmoGroupEncodedCallback, (unsigned int)Nav_RefineBallisticAim_Address, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, (unsigned int)Nav_SelectChaseObjectGoal_Address, (unsigned int)Nav_RebuildRequestedGoalRoute_Address, (unsigned int)Nav_CollectEnemyTargets_Address, (unsigned int)Target_UpdateTargetSelection_Address, (unsigned int)g_Nav_SelectWeaponFromSecondAmmoGroupEncodedCallback, (unsigned int)Nav_RefineBallisticAim_Address, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, (unsigned int)Nav_SelectStationaryObjectGoal_Address, (unsigned int)Nav_RebuildRequestedGoalRoute_Address, (unsigned int)Nav_CollectEnemyTargets_Address,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, (unsigned int)Nav_RebuildRequestedGoalRoute_Address, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, (unsigned int)Nav_RebuildRequestedGoalRoute_Address, (unsigned int)Nav_CollectEnemyTargets_Address, (unsigned int)Target_UpdateTargetSelection_Address,
    (unsigned int)g_Nav_SelectWeaponFromThirdAmmoGroupEncodedCallback, (unsigned int)Nav_RefineBallisticAim_Address, (unsigned int)Nav_SelectPlayerState_Address, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x800C9F10, 0x800C9F60, 0x800C9FB0, 0x800CA000, 0x800CA050, 0x800CA0A0, 0x800CA0F0,
    0x800CA140, 0x800CA190, 0x800CA1E0, 0x800CA230, 0x800CA280, 0x800CA2D0, 0x800CA320, 0x8010A3B8,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, (unsigned int)Nav_ResetPatrolRouteSelection_Address, (unsigned int)Nav_UpdatePatrolRoute_Address, 0x00000000, 0x00000000, 0x3F800000, 0x00000005,
    0x00000000, 0x00000001, (unsigned int)Nav_InitTargetRouteFollow_Address, (unsigned int)Nav_UpdateTargetRouteFollow_Address, 0x00000000, 0x00000000, 0x3F800000, 0x00000005,
    0x00000000, 0x00000002, (unsigned int)Nav_InitRoamingWithJumps_Address, (unsigned int)Nav_UpdateRoamingWithJumps_Address, 0x00000000, 0x00000000, 0x3F800000, 0x00000005,
    0x00000000, 0x00000003, (unsigned int)Nav_InitPursuitStrafe_Address, (unsigned int)Nav_UpdatePursuitStrafe_Address, 0x00000000, 0x00000000, 0x3F800000, 0x00000005,
    0x00000000, 0x00000004, (unsigned int)Nav_InitRangedCombat_Address, (unsigned int)Nav_UpdateRangedCombat_Address, 0x00000000, 0x00000000, 0x3F800000, 0x00000005,
    0x00000000, 0x00000005, (unsigned int)Nav_InitCloseCombat_Address, (unsigned int)Nav_UpdateCloseCombat_Address, 0x00000000, 0x00000000, 0x3F800000, 0x00000005,
    0x00000000, 0x00000006, (unsigned int)g_Nav_InitCombatTargetApproachEncodedCallback, (unsigned int)Nav_ApproachCombatTargetAlongRoute_Address, 0x00000000, 0x00000000, 0x3F800000, 0x00000005,
    0x00000000, 0x00000007, (unsigned int)g_Nav_InitRetreatMovementEncodedCallback, (unsigned int)Nav_UpdateRetreatMovement_Address, 0x00000000, 0x00000000, 0x3F800000, 0x00000005,
    0x00000000, 0x00000008, (unsigned int)Nav_ResetObjectArrivalChase_Address, (unsigned int)Nav_UpdateObjectArrivalChase_Address, 0x00000000, 0x00000000, 0x3F800000, 0x00000005,
    0x00000000, 0x00000009, (unsigned int)g_Nav_InitUnclaimedMarkerSearchEncodedCallback, (unsigned int)Nav_SeekUnclaimedMarker_Address, 0x00000000, 0x00000000, 0x3F800000, 0x00000005,
    0x00000000, 0x0000000A, (unsigned int)g_Nav_InitCarrierRouteEncodedCallback, (unsigned int)Nav_FollowMarkerCarrierRoute_Address, 0x00000000, 0x00000000, 0x3F800000, 0x00000005,
    0x00000000, 0x0000000B, (unsigned int)Nav_InitTimedJumpRoute_Address, (unsigned int)Nav_UpdateTransientJumpRoute_Address, 0x00000000, 0x00000000, 0x3F800000, 0x00000005,
    0x00000000, 0x0000000C, (unsigned int)g_Nav_InitNearbyUnrestrictedGoalEncodedCallback, (unsigned int)Nav_SeekNearbyUnrestrictedGoal_Address, 0x00000000, 0x00000000, 0x3F800000, 0x00000005,
    0x00000000, 0x0000000D, (unsigned int)Nav_InitVisiblePursuit_Address, (unsigned int)Nav_UpdateVisiblePursuit_Address, 0x00000000, 0x00000000, 0x3F800000, 0x00000005,
    0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000001, 0x000006A5, 0x00000002, 0x000006A6, 0x00000004, 0x000006A7, 0x00000008,
    0x000006A8, 0x00000010, 0x000006A9, 0x00000020, 0x000006AA, 0x00000040, 0x00000898, 0x00000080,
    0x00000898, 0x00000100, 0x00000898, 0x00000200, 0x00000898, 0x00000400, 0x00000898, 0x00000800,
    0x00000898, 0x00001000, 0x00000898, 0x00002000, 0x00000898, 0x00004000, 0x00000898, 0x00008000,
    0x00000898, 0x00010000, 0x00000898, 0x00020000, 0x00000898, 0x00040000, 0x00000898, 0x00080000,
    0x00000898, 0x00100000, 0x00000898, 0x00200000, 0x00000898, 0x00400000, 0x00000898, 0x00800000,
    0x00000898, 0x01000000, 0x00000898, 0x02000000, 0x00000898, 0x04000000, 0x00000898, 0x08000000,
    0x00000898, 0x10000000, 0x00000898, 0x20000000, 0x00000898, 0x40000000, 0x00000898, 0x80000000,
    0x00000898, 0x00000000, 0x00000000, 0x00000001, 0x00000898, 0x00000000, 0x00000000, 0x00000008,
    (unsigned int)g_weapon_InitializeChargeForWeaponFiveEntry, 0x00010000, 0x00050000, 0x00040000, 0x000C0000, 0x00080000, 0x000A0000, 0x00020000,
    0x00030000, 0x41F00000, 0x42400000, 0x43020000,
};
#endif
