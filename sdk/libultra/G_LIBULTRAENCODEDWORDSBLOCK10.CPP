#include "../include/libgultra.h"
#include "DATA/OVL1_C/NAVIGATION_CALLBACK_ADDRESS.H"
#include "DATA/ACTOR_STATE_CALLBACKS/ACTOR_STATE_CALLBACK_LABELS.H"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: data/unresolved/800CCC44 */
unsigned int g_LibultraEncodedWordsBlock10[3] = {
    (unsigned int)addrLow_Nav_CollectEnemyTargets, (unsigned int)addrLow_Target_UpdateTargetSelection, (unsigned int)addrLow_Nav_SelectPlayerState,
};
#endif
