#include "include_asm.h"
#include "DATA/REST_SOURCE_RECORDS.H"

/* PLAYER_MOUNTED_MOVEMENT_SPEED_CONSTANT.CPP */
/* ROM-grounded data: src/g_playerMountedMovementSpeedConstantsUsRev1_PlayerMountedMovementSpeedConstant.c */
const float g_playerMountedMovementSpeedConstantsUsRev1[1] = {
    34.559998f,
};

/* PLAYER_TUNING_FLOAT_TRIPLES.CPP */
#if defined(VERSION_US_REV1)
float g_playerTuningFloatTriplesUsRev1[16] = {
    1.7280002f, 2.7648f, 20.736f, 1.0368001f, 0.0f, 0.0f,
    0.0f, 2.88f, 21.599998f, 1.08f, 1.7280002f, 12.960001f,
    0.64800006f, 0.0f, 0.0f, 0.0f,
};
#endif

/* PLAYER_MOVEMENT_TUNING_PROFILE_ONE.CPP */
#if defined(VERSION_US) || defined(VERSION_US_REV1)
float g_playerMovementTuningProfileOneUsRev1[8] = {
    10.24f, 30.72f, 13.44f, 10.24f,
    35.84f, 13.44f, 0.0f, 0.0f,
};
#endif

/* PLAYER_MOVEMENT_ZERO_HALFWORDS.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CE75C_unclaimed_CF3BC */
u16 g_playerMovementTuningZeroHalfwordsUsRev1[2] = {
    0, 0,
};
#endif

#if defined(VERSION_US_REV1)
/* bytes live in the preceding array */
#endif
