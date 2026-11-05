#include "Data/rest_source_records.h"

/* XPRINTF.CPP */
#if defined(VERSION_US)
RestDecimalPowersPool793 g_xprintfConstant = { { 0x00007000, 0x00000800 },
    { 10.0, 100.0, 10000.0, 100000000.0, 1e+16, 1e+32, 1e+64, 1e+128, 1e+256 },
    "ctDirect"
};
#endif

#if defined(VERSION_EU)
float g_xprintfFloatConstant[3] = {
    127.0f, 7168.0f, 0.09765625f,
};
#endif
