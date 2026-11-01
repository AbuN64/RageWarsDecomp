#include "include_asm.h"
#include "COMMON/GAMEPLAY_TRANSITION.H"

/* PLAYER_DEATH_CONSTANTS__PLAYERAI.CPP */
const Shared_HeightBonuses g_playerDeathHeightOffsets = {
    10.23999977f,
    81.91999817f,
};
const float g_playerDeathMotionCenter = 512.0f;
const float g_playerDeathMovingSpeed = 5.119999886f;

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X)
#endif

/* PLAYER_APPLYPLAYERDAMAGE_DATA.CPP */
#if defined(VERSION_US) || defined(VERSION_US_REV1)
/* ROM-grounded data: src/k_PlayerApplyplayerdamageEncodedWords_PlayerApplyplayerdamageData.c */
const float k_PlayerApplyplayerdamageEncodedWords[3] = {
    0.06666667f, 1.0f, 51.199997f,
};
#endif
