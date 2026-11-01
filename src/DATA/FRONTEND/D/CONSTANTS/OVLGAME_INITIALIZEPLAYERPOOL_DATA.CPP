#include "DATA/REST_SOURCE_RECORDS.H"
#include "include_asm.h"

/* g_playerMovementTuningProfileThreeUsRev1_OvlgameInitializeplayerpoolData.CPP */
#if defined(VERSION_US) || defined(VERSION_US_REV1)
float g_playerMovementTuningProfileThreeUsRev1[8] = {
    7.68f, 23.039999f, 5.7599998f, 7.68f,
    26.880001f, 5.7599998f, 10.24f, 0.768f,
};
#endif

#if defined(VERSION_US)
RestOvlgameInitializeplayerpoolEncodedWordsRecord391 k_OvlgameInitializeplayerpoolEncodedWords = {
    1,
};
#endif

#if defined(VERSION_US_REV1)
RestOvlgameInitializeplayerpoolEncodedWordsBlock1Record392 k_OvlgameInitializeplayerpoolEncodedWordsBlock1 = {
    1,
};
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

/* g_playerMovementTuningProfileFourUsRev1_OvlgameInitializeplayerpoolData.CPP */
#if defined(VERSION_US) || defined(VERSION_US_REV1)
float g_playerMovementTuningProfileFourUsRev1[8] = {
    2.048f, 15.36f, 1.024f, 20.48f,
    1.536f, 20.48f, 153.59999f, 102.399994f,
};
#endif

#if defined(VERSION_US_REV1)
RestOvlgameInitializeplayerpoolEncodedWordsBlock2Record393 k_OvlgameInitializeplayerpoolEncodedWordsBlock2 = {
    1,
};
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

/* g_playerViewTuningProfileThreeUsRev1_OvlgameInitializeplayerpoolData.CPP */
#if defined(VERSION_US_REV1)
float g_playerViewTuningProfileThreeUsRev1[6] = {
    0.4f, 0.5f, 1.0f, 0.25f,
    -1.5707965f, 1.5707965f,
};
#endif

/* g_playerViewTuningProfileFourUsRev1_OvlgameInitializeplayerpoolData.CPP */
#if defined(VERSION_US_REV1)
float g_playerViewTuningProfileFourUsRev1[6] = {
    0.2f, 0.25f, 0.5f, 0.125f,
    -1.5707965f, 1.5707965f,
};
#endif

/* g_playerViewTuningProfileTailUsRev1_OvlgameInitializeplayerpoolData.CPP */
#if defined(VERSION_US_REV1)
float g_playerViewTuningProfileTailUsRev1[9] = {
    1.024f, 7.68f, 0.512f, 10.24f,
    0.768f, 10.24f, 76.799995f, 51.199997f,
    0.0f,
};
#endif

/* g_playerMovementProfileFiveStateFlagUsRev1_OvlgameInitializeplayerpoolData.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_callbacks_00_us_rev1.c */
extern char g_Player_UpdateFlyModeAddress[];
extern char g_Player_ZeroBodyVelocityAddressVariant2[];
unsigned int g_playerMovementProfileFiveStateFlagUsRev1[2] = {
    (unsigned int)g_Player_ZeroBodyVelocityAddressVariant2, (unsigned int)g_Player_UpdateFlyModeAddress,
};
#endif

/* g_playerMovementProfileThreeStateFlagUsRev1_OvlgameInitializeplayerpoolData.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF474_unclaimed_CF4A4_unclaimed_CF4D0 */
extern char g_secondaryCollisionContext[];
void *g_playerMovementProfileThreeStateFlagUsRev1[1] = {
    (void *)(g_secondaryCollisionContext + 192),
};
#endif

/* g_playerMovementProfileFourStateFlagUsRev1_OvlgameInitializeplayerpoolData.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/rw_player_state_normal_timing_00_us_rev1.c */
RestplayerMovementProfileFourStateFlagUsRev1Record394 g_playerMovementProfileFourStateFlagUsRev1 = {
    { 0, 1 },
};
#endif
