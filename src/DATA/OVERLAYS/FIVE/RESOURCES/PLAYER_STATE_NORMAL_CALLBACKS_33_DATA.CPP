#include "TYPES.H"


#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_callbacks_33_us_rev1.c */
extern char g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant9[];
extern char g_PlayerSequence20StartCallbackAddressUs[];
#if defined(VERSION_US_REV1)
void * g_playerStateNormalCallbacks33Words[2] = {
    (void *)&g_PlayerSequenceRunEndUpdateCallbackAddressUsVariant9, (void *)&g_PlayerSequence20StartCallbackAddressUs
};
#endif
#endif
