#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const char s_statModelsIndexText[18] =
    "stat models index\000";
#endif

#if defined(VERSION_US_REV1)
const char g_statModelsIndexText[] = "stat models index"
#if defined(VERSION_US_REV1)
    "\000\000"
#endif
;
#endif
