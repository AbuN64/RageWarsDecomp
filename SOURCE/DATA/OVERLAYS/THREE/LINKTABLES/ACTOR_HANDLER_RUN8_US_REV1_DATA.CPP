#include "DATA/OVL1_C/NAVIGATION_CALLBACK_ADDRESS.H"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/ragewars_actor_handler_run_CE890_us_rev1.c */
unsigned int g_actorHandlerRun8_us_rev1[2] = {
    (unsigned int)addrLow_Nav_RebuildRequestedGoalRoute, (unsigned int)addrLow_Nav_CollectEnemyTargets,
};
#endif
