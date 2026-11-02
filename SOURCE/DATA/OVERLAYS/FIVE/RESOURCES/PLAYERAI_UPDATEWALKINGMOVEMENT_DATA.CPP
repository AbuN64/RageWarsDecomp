#include "TYPES.H"


#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_special_callbacks_00_us_rev1.c */
extern char g_Player_UpdateFlyModeAddress[];
extern char g_Player_ZeroBodyVelocityAddressVariant2[];
#if defined(VERSION_US_REV1)
void * g_playerStateSpecialCallbacks00Words[2] = {
    (void *)&g_Player_ZeroBodyVelocityAddressVariant2, (void *)&g_Player_UpdateFlyModeAddress
};
#endif
#endif
