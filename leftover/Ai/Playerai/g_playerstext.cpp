#include "include_asm.h"
#include "Playerai/g_playerstext.h"

const float g_playerTargetFacingConstantWords_us_C367C[7] = {
    1024.0f, 1.5707964f, -1.5707964f, 6.2831855f,
    1.5707964f, -1.5707964f, 6.2831855f,
};

#if !(defined(VERSION_US_REV1))
const char g_playersText_us_C3698[8] =
    "Players\000";
#endif

#if defined(VERSION_US_REV1)
const char s_playersText[8] = "Players";
#endif
