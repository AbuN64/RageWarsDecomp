#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE) || defined(VERSION_EU)
const char g_skyLayersText[12] =
    "sky layers\000\000";
#endif
#if defined(VERSION_EU_X) || defined(VERSION_US)
const char g_skyLayersText[11] =
    "sky layers\000";
#endif
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/s_skyLayersText.c */
const unsigned char s_skyLayersText[11] =
    "sky layers";
#endif
