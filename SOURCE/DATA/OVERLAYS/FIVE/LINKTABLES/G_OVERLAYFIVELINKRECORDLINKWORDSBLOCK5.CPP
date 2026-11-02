#include "TYPES.H"


#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_special_callbacks_39_us_rev1.c */
extern char g_PlayerTrackNearbyAimTargetCallbackAddressUs[];
extern char g_PlayerState39EmptyHookAddress[];
#if defined(VERSION_US_REV1)
void * g_overlayFiveLinkRecordLinkWordsBlock5[2] = {
    (void *)&g_PlayerState39EmptyHookAddress, (void *)&g_PlayerTrackNearbyAimTargetCallbackAddressUs
};
#endif
#endif
