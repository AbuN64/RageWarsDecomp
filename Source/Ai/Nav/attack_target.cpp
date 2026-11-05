#include "include_asm.h"

#if defined(VERSION_DE)
float g_navAttackTargetDiagonalRangeFloats[3] = {
    0.70710677f, 100.0f, 2.25f,
};
#endif

#if defined(VERSION_US)
char s_NavLifeTimeRText[12] =
    "LifeTimeR\000\000(";
#endif

#if defined(VERSION_EU_X)
unsigned int k_navFragment[3] = {
    0x40490FDB, 0x40A78D36, 0x3FE52EDF,
};
#endif

#if defined(VERSION_US_REV1)
unsigned int g_navAttackTargetScaleFloats[3] = {
    0x3FE52EDF, 0x3F800000, 0x3FE52EDF,
};
#endif
