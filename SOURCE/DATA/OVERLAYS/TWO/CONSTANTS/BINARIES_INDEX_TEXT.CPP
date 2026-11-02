#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const char g_binariesIndexText[15] =
    "binaries index\000";
#endif

#if defined(VERSION_US_REV1)
const char g_binariesIndexText[15] =
    "binaries index";
#endif
