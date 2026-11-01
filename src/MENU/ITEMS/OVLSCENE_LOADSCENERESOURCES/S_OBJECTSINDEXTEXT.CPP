#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const char s_objectsIndexText[14] =
    "objects index\000";
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_objectsIndexSource.c */
const char g_objectsIndex[14] = "objects index";
#endif
