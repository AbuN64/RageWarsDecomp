#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const char g_flyModeOffText[13] =
    "Fly Mode Off\000";
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/s_flyModeOffText_TryJump.c */
const char s_flyModeOffText[13] = "Fly Mode Off";
#endif
