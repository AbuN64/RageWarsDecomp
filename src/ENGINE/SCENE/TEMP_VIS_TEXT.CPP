#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const char s_tempVisText[9] =
    "temp vis\000";
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_temporaryVisibilityText_TempVisText.c */
const char g_temporaryVisibilityText[9] =
    "temp vis";
#endif
