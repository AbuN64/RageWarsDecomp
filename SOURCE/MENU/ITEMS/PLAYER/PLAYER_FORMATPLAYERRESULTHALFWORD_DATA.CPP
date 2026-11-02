#include "include_asm.h"

#if defined(VERSION_EU) || defined(VERSION_EU_X)
#if defined(VERSION_EU)
const char g_playerMenuValueFormat[8] =
    "%04d\000\000\000\000";
#endif
#if defined(VERSION_EU_X)
const char g_playerMenuValueFormat[5] =
    "%04d";
#endif
#endif
