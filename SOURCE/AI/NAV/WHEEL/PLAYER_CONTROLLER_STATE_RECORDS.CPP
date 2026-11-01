#include "DATA/REST_SOURCE_RECORDS.H"
#include "DATA/OVL1_D/NAV_INITVISIBLEPURSUIT.H"
#include "DATA/OVL1_D/NAV_UPDATEVISIBLEPURSUIT_Nav4.H"
#if defined(VERSION_US_REV1)
/* PLAYER_CONTROLLER_STATE_HEADER_US_REV1.CPP */
/* ROM-grounded data: rodata/unresolved/800CDA3C_unclaimed_CE6E0_unclaimed_CE750_unclaimed_CEBCC_unclaimed_CEC6C_unclaimed_CEC8C_unclaimed_CECAC_unclaimed_CECCC_unclaimed_CECEC_unclaimed_CED0C_unclaimed_CED2C_unclaimed_CED4C_unclaimed_CED6C_unclaimed_CED8C_unclaimed_CEDAC_unclaimed_CEDCC_unclaimed_CEDEC */
RestplayerControllerStateHeaderUsRev1Layout396 g_playerControllerStateHeaderUsRev1 = {
    { 0, 0 },
    1.0f,
    { 5, 0 },
};
/* ROM-grounded data: src/rw_controller_state_id_CEE00_us_rev1.c */
RestplayerControllerStateIdThirteenUsRev1Record397 g_playerControllerStateIdThirteenUsRev1 = {
    13,
};
/* NAV_INITVISIBLEPURSUIT.CPP */
/* ROM-grounded data: rodata/unresolved/800CDA3C_unclaimed_CE6E0_unclaimed_CE750_unclaimed_CEBCC_unclaimed_CEC6C_unclaimed_CEC8C_unclaimed_CECAC_unclaimed_CECCC_unclaimed_CECEC_unclaimed_CED0C_unclaimed_CED2C_unclaimed_CED4C_unclaimed_CED6C_unclaimed_CED8C_unclaimed_CEDAC_unclaimed_CEDCC_unclaimed_CEDEC_unclaimed_CEE04 */
unsigned int g_playerControllerStartCallbackUsRev1[1] = {
    (unsigned int)addrLow_Nav_InitVisiblePursuit,
};
/* NAV_UPDATEVISIBLEPURSUIT_Nav4.CPP */
/* ROM-grounded data: src/rw_controller_state_update_CEE08_us_rev1.c */
unsigned int g_playerControllerUpdateCallbackUsRev1[1] = {
    (unsigned int)addrLow_Nav_UpdateVisiblePursuit,
};
/* PLAYER_CONTROLLER_STATE_HEADER_ALTERNATE_US_REV1.CPP */
/* ROM-grounded data: rodata/unresolved/800CDA3C_unclaimed_CE6E0_unclaimed_CE750_unclaimed_CEBCC_unclaimed_CEC6C_unclaimed_CEC8C_unclaimed_CECAC_unclaimed_CECCC_unclaimed_CECEC_unclaimed_CED0C_unclaimed_CED2C_unclaimed_CED4C_unclaimed_CED6C_unclaimed_CED8C_unclaimed_CEDAC_unclaimed_CEDCC_unclaimed_CEDEC_unclaimed_CEE04_unclaimed_CEE0C */
RestplayerControllerStateHeaderAlternateUsRev1Layout398 g_playerControllerStateHeaderAlternateUsRev1 = {
    { 0, 0 },
    1.0f,
    { 5, 0 },
};
/* ROM-grounded data: src/rw_controller_state_end_CEE20_us_rev1.c */
RestplayerControllerStateEndUsRev1Record399 g_playerControllerStateEndUsRev1 = {
    -1,
};
#endif
