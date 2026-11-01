#include "DATA/PLAYER_STUN/PLAYER_RESETSTUNFLAGS.H"

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_callbacks_20_us_rev1.c */
unsigned int g_PlayerStateNormalCallbacks20UsRev1[2] = {
    (unsigned int)addrLow_Player_ResetStunFlags, (unsigned int)g_playerStateCallbacks20SecondTargetUsRev1,
};
#endif
