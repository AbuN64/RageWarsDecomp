#ifndef AI_NAV_ROAM_H
#define AI_NAV_ROAM_H
#include "AI/SOURCE.H"
extern void Nav_InitRoamingWithJumps(Shared_Actor *actor);
extern void Nav_ChooseNewRoamingGoal(void *actor);
extern void Nav_UpdateRoamingWithJumps(Shared_Actor *actor);
#endif
