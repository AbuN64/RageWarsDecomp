#include "TYPES.H"


#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_callbacks_35_us_rev1.c */
extern char g_PlayerInterpolateTravelTargetCallbackAddressUs[];
extern char addrLow_Playerai_InitializeActorModelEffect[];
#if defined(VERSION_US_REV1)
void * g_playerStateNormalCallbacks35Words[2] = {
    (void *)&addrLow_Playerai_InitializeActorModelEffect, (void *)&g_PlayerInterpolateTravelTargetCallbackAddressUs
};
#endif
#endif
