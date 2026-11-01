
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_callbacks_18_us_rev1.c */
extern char g_Playerai_ResetPlayerAfterDeathAddress[];
extern char g_PlayerState18EmptyHookAddress[];
unsigned int g_PlayerStateNormalCallbacks18UsRev1[2] = {
    (unsigned int)g_Playerai_ResetPlayerAfterDeathAddress, (unsigned int)g_PlayerState18EmptyHookAddress,
};
#endif
