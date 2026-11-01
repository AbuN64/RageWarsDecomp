#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const char s_warpDestsText[11] =
    "warp dests\000";
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_warpDests.c */
const char g_warpDests[11] =
    "warp dests";
#endif
