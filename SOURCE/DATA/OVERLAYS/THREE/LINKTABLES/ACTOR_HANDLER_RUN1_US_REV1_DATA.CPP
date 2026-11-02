#include "TYPES.H"

#include "DATA/OVL1_C/NAVIGATION_CALLBACK_ADDRESS.H"
#include "DATA/ACTOR_STATE_CALLBACKS/ACTOR_STATE_CALLBACK_LABELS.H"

#if defined(VERSION_US_REV1)
#if defined(VERSION_US_REV1)
void * k_ActorHandlerRun1UsRev1EncodedWords[20] = {
    (void *)&addrLow_Nav_CollectEnemyTargets, (void *)&addrLow_Target_UpdateTargetSelection, (void *)&addrLow_Wheel_AdvanceWheelProbe, (void *)&addrLow_Nav_RefineBallisticAim, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0
};
#endif

/* ROM-grounded data: src/ragewars_actor_handler_run_CE7A0_us_rev1.c */
unsigned int g_actorHandlerRun1_us_rev1[2] = {
    (unsigned int)addrLow_Nav_RebuildRequestedGoalRoute, (unsigned int)addrLow_Nav_CollectEnemyTargets,
};
#endif
