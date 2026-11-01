#include "DATA/OVL1_C/NAVIGATION_CALLBACK_ADDRESS.H"
#include "DATA/ACTOR_STATE_CALLBACKS/ACTOR_STATE_CALLBACK_LABELS.H"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/ragewars_actor_handler_run_CE7F0_us_rev1.c */
unsigned int g_actorHandlerRun3_us_rev1[3] = {
    (unsigned int)addrLow_Nav_UpdateRouteIntermediateGoal, (unsigned int)addrLow_Nav_RebuildRequestedGoalRoute, (unsigned int)addrLow_Nav_CollectEnemyTargets,
};
#endif
