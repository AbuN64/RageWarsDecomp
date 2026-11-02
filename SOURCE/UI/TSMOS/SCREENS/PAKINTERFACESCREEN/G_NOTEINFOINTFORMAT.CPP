#include "include_asm.h"

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
/* ROM-grounded data: src/noteInfoIntFormatUsRev1.c */
const unsigned char g_noteInfoIntFormat[3] = {
    0x25, 0x64, 0x00,
};
#endif
