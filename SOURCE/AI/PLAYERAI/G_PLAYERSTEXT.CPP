#include "include_asm.h"

/* 800C7C3C.CPP */
const float g_playerTargetFacingConstantWordsUsRev1[7] = {
    1024.0f, 1.5707964f, -1.5707964f, 6.2831855f,
    1.5707964f, -1.5707964f, 6.2831855f,
};

/* 800C7C58.CPP */
#if !(defined(VERSION_US_REV1))
const char g_playersText[8] =
    "Players\000";
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/s_playersText_us_rev1.c */
const char s_playersText[8] = "Players";
#endif
