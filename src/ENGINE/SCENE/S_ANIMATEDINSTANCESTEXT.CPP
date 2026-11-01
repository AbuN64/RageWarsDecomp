#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const char s_animatedInstancesText[19] =
    "animated instances\000";
#endif

#if defined(VERSION_US_REV1)
const unsigned char s_animatedInstancesText[19] =
    "animated instances";
#endif
