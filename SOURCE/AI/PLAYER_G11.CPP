#include "include_asm.h"
#include "TYPES.H"

/* G_PLAYERSWIMCONSTANTS.CPP */
#if defined(VERSION_US_REV1)
const float g_playerSwimConstants[34] = {
    2.048f, 0.1f, 0.0625f, 1.0f,
    -1.0f, 0.78539824f, 1e+02f, -9e+01f,
    9e+01f, 0.017453294f, 11.25f, 1.5707965f,
    3.141593f, -1.5707965f, 3.141593f, 6.2831855f,
    384.0f, 1.5707965f, 3.141593f, -1.5707965f,
    3.141593f, 0.06981318f, 6.144f, 20.48f,
    20.48f, 4.096f, 6.144f, 20.48f,
    20.48f, 4.096f, 8.4375f, 0.1f,
    1.5707964f, 1.5f,
};
#endif

/* PLAYER_CLIMB_MOVEMENT_CONSTANTS.CPP */
/* 8021CD70_21.CPP */
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
const f32 g_playerClimbMovementConstantsGerman[34] = {
    2.0480001f, 0.100000001f, 0.0625f, 1.0f, -1.0f, 0.785398245f,
    100.0f, -90.0f, 90.0f, 0.0174532942f, 11.25f, 1.57079649f,
    3.14159298f, -1.57079649f, 3.14159298f, 6.28318548f, 384.0f, 1.57079649f,
    3.14159298f, -1.57079649f, 3.14159298f, 0.069813177f, 6.14400005f, 20.4799995f,
    20.4799995f, 4.09600019f, 6.14400005f, 20.4799995f, 20.4799995f, 4.09600019f,
    8.4375f, 0.100000001f, 1.57079637f, 1.5f,
};
#endif

/* 8021CD70_22.CPP */

/* 8021CD70_23.CPP */

/* 8021CD70_24.CPP */

/* PLAYER_TRAVEL_AND_RIDE_CONSTANT_WORDS.CPP */
/* 800C7BD0.CPP */
const float g_playerTravelSequenceConstantWordsUsRev1[5] = {
    6.2831855f, 6.2831855f, 0.2f, 0.2f,
    4.0f,
};

/* 800C7BE4.CPP */
const float g_playerRideMovementConstantWordsUsRev1[16] = {
    0.2792527f, 1.0f, 0.01f, 0.06f,
    8e+01f, 0.017453294f, 8.0f, 9e+01f,
    0.5f, 2.5f, 2.5f, 5e+01f,
    1.0f, 10.24f, 10.24f, 15.0f,
};
