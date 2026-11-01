#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
const char s_particleEffectsText[20] =
    "particle effects\000\000\000\000";
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
const char s_particleEffectsText[17] =
    "particle effects\000";
#endif
#endif

#if defined(VERSION_US_REV1)
const char g_particleEffects[17] =
    "particle effects";
#endif
