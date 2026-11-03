#include "DATA/OVL1_C/NAVIGATION_CALLBACK_ADDRESS.H"
#include "LINKTABLES/ACTOR_HANDLER_RUN14_US_REV1_DATA.H"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/ragewars_actor_handler_run_CE930_us_rev1.c */
unsigned int g_actorHandlerRun14_us_rev1[2] = {
    (unsigned int)addrLow_Nav_RebuildRequestedGoalRoute, (unsigned int)addrLow_Nav_CollectEnemyTargets,
};
#endif
