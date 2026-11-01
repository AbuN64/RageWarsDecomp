#include "include_asm.h"
#include "COMMON/GAMEPLAY_TRANSITION.H"

/* PLAYER_DEATH_CONSTANTS__PLAYER.CPP */
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X)
const float k_playerApplyPlayerDamageConstants[3] = {
    0.06666667f, 1.0f, 51.199997f,
};
#endif

/* PLAYERAI_COMPUTEAIMROTATION_DATA__PLAYERAI.CPP */
/* 800C7474.CPP */
/* ROM-grounded data: src/k_aimRotationPoolHalf_us_rev1.c */
const float k_PlayeraiComputeaimrotationHalfWords[1] = {
    0.5f,
};

/* 800C7478.CPP */

/* PLAYERAI_COMPUTEAIMROTATION_DATA__PLAYER.CPP */
/* 800C7474.CPP */
/* ROM-grounded data: src/k_aimRotationPoolHalf_us_rev1.c */

/* 800C7478.CPP */
const float k_PlayeraiComputeaimrotationEncodedWords[7] = {
    1.0f, 0.5f, 1.0f, 0.75f,
    0.75f, 0.5f, 1.0f,
};
