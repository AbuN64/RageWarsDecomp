#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const char g_staticEventsText[14] =
    "static events\000";
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/staticEventsTagUsRev1.c */
const char s_staticEventsTagUsRev1[14] = "static events";
#endif
