#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_US)
const char g_scene_collisionTextWords[10] =
    "collision\000";
#endif
#if defined(VERSION_EU_X)
const char g_scene_collisionTextWords[12] =
    "collision\000\000\000";
#endif
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/s_collisionText.c */
const char s_collisionText[10] = "collision";
#endif
