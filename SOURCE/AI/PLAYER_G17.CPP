#include "DATA/REST_SOURCE_RECORDS.H"
#include "include_asm.h"

/* PLAYERAI_UPDATEWALKINGMOVEMENT_DATA.CPP */
#if defined(VERSION_US) || defined(VERSION_US_REV1)
float g_playerMovementTuningProfileTwoUsRev1[8] = {
    5.12f, 15.36f, 3.84f, 5.12f,
    17.92f, 3.84f, 0.0f, 0.0f,
};
#endif

/* PLAYER_MOVEMENT_ZERO_HALFWORDS_ALTERNATE.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF3E0 */
u16 g_playerMovementTuningZeroHalfwordsAlternateUsRev1[2] = {
    0, 0,
};
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif

/* PLAYERAI_ENTERMOVINGSEQUENCESTATE_DATA_DATA.CPP */
#if defined(VERSION_US_REV1)
float g_playerViewTuningProfileOneUsRev1[6] = {
    0.25f, 0.9f, 0.6f, 0.3f,
    -1.5707965f, 1.5707965f,
};
#endif

/* PLAYER_VIEW_TUNING_PROFILE_TWO.CPP */
#if defined(VERSION_US_REV1)
float g_playerViewTuningProfileTwoUsRev1[6] = {
    0.25f, 0.9f, 0.6f, 0.3f,
    -0.78539824f, 1.5707965f,
};
#endif

/* PLAYER_VIEW_TUNING_TAIL.CPP */
#if defined(VERSION_US_REV1)
float g_playerViewTuningTailUsRev1[6] = {
    0.0f, 0.0f, 0.5f, 0.25f,
    -0.06981318f, 1.5707965f,
};
#endif
