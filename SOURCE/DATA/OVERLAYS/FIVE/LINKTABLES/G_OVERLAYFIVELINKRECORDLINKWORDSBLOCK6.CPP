#include "TYPES.H"


#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_special_callbacks_40_us_rev1.c */
extern char g_playerStateCallbacks40FirstTargetUsRev1[];
extern char g_PlayerStateNoOperationCallbackAddressDeVariant4[];
#if defined(VERSION_US_REV1)
void * g_overlayFiveLinkRecordLinkWordsBlock6[2] = {
    (void *)&g_playerStateCallbacks40FirstTargetUsRev1, (void *)&g_PlayerStateNoOperationCallbackAddressDeVariant4
};
#endif
#endif
