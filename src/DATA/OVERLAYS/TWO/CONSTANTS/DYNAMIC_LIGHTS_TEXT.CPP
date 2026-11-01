#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const char s_dynamicLightsText[15] =
    "dynamic lights\000";
#endif

#if defined(VERSION_US_REV1)
const char g_dynamicLightsText[15] =
    "dynamic lights";
#endif
