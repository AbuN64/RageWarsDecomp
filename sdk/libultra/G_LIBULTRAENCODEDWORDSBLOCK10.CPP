#include "../include/libgultra.h"
#include "Data/Ovl1_c/navigation_callback_address.h"
#include "Data/Actor_state_callbacks/actor_state_callback_labels.h"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: data/unresolved/800CCC44 */
unsigned int g_navTargetingCallbackAddresses[3] = {
    (unsigned int)addrLow_Nav_CollectEnemyTargets, (unsigned int)addrLow_Target_UpdateTargetSelection, (unsigned int)addrLow_Nav_SelectPlayerState,
};
#endif
