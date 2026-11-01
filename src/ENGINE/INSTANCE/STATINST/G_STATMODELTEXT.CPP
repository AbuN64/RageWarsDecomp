#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const char g_statModelText[11] =
    "stat model\000";
#endif



#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/s_statModelText_GStatmodeltext.c */
const char s_statModelText[11] =
    "stat model";
#endif
