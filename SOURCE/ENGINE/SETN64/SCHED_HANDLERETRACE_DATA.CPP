#include "DATA/REST_SOURCE_RECORDS.H"
#include "include_asm.h"
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)

s32 g_SchedHandleretraceWords1[6] = {
    0, 0, 0, 20, 0, 0,
};
#endif
#if defined(VERSION_EU_X)

char g_schedHandleretraceTailBytesEuX[19] =
    "E\000\000\000SENT\000\000\000\000\000\000\000\001\000\000\000";
#endif
#if defined(VERSION_EU)

unsigned char g_schedHandleretraceTailBytesEu[19] = {
    0x00, 0x20, 0x7C, 0xB4, 0x80, 0x11, 0x00, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00,
};
#endif
#if defined(VERSION_DE)

unsigned char g_schedHandleretraceTailBytesDe[19] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00,
};
#endif
