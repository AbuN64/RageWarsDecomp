#ifndef AI_NAV_PICKUPTARGET_H
#define AI_NAV_PICKUPTARGET_H
#include "Common/navigation_actor_search_views.h"
extern s32 Nav_IsPickupObjectInPairCategory(s32 objectId);
extern s32 Nav_AddInactiveObjectGoals(void);
extern s32 Nav_IsPickupObjectInSixEntryCategory(s32 objectId);
s32 Nav_GetWeaponPickupGoalClass(void **pickupHandle);
#endif
