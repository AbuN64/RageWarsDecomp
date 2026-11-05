#include "include_asm.h"
#include "Libc/libc_formatinteger_data.h"

#if !(defined(VERSION_US_REV1))
const char g_lowercaseHexDigitsText[17] =
    "0123456789abcdef\000";
#endif

#if defined(VERSION_US_REV1)
const char g_lowercaseHexDigitsText_StorageWords[17] = "0123456789abcdef";
#endif
