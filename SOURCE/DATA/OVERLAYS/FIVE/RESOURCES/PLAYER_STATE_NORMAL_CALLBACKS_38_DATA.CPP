#include "TYPES.H"


#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_callbacks_38_us_rev1.c */
extern char g_PlayerUpdateHeldActorReleaseCallbackAddressUs[];
extern char addrLow_Playerai_OffsetActorForState15[];
#if defined(VERSION_US_REV1)
void * g_playerStateNormalCallbacks38Words[2] = {
    (void *)&addrLow_Playerai_OffsetActorForState15, (void *)&g_PlayerUpdateHeldActorReleaseCallbackAddressUs
};
#endif
#endif
