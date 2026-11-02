#include "TYPES.H"


#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_callbacks_42_us_rev1.c */
extern char g_Playerai_UpdateSequence72RunEndPoseCallbackAddressUs[];
extern char g_Playerai_StartPlayerSequence73CallbackAddressUs[];
#if defined(VERSION_US_REV1)
void * g_playerStateNormalCallbacks42Words[2] = {
    (void *)&g_Playerai_UpdateSequence72RunEndPoseCallbackAddressUs, (void *)&g_Playerai_StartPlayerSequence73CallbackAddressUs
};
#endif
#endif
