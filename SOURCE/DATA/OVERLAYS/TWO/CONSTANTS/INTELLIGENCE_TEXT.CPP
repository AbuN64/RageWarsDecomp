#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const char s_intelligenceText[13] =
    "intelligence\000";
#endif

#if defined(VERSION_US_REV1)
const char g_intelligenceText[13] =
    "intelligence";
#endif
