#include "include_asm.h"

#if defined(VERSION_DE) || defined(VERSION_US)
#if defined(VERSION_DE)
unsigned int s_EDataSwooshVertexText[1] = {
    0x00000000,
};
#endif
#if defined(VERSION_US)
char s_EDataSwooshVertexText[12] =
    "SwooshVertex";
#endif
#endif

#if defined(VERSION_US_REV1)
float g_aiDevicesFloatConstants[3] = {
    6.2831855f, 0.2f, 0.2f,
};
#endif
