#include "DATA/REST_SOURCE_RECORDS.H"


/* 800C7B88.CPP */
#if defined(VERSION_US)
RestDecimalPowersPool793 g_xprintfConstantWords = { { 0x00007000, 0x00000800 },
    { 10.0, 100.0, 10000.0, 100000000.0, 1e+16, 1e+32, 1e+64, 1e+128, 1e+256 },
    "ctDirect"
};
#endif

/* 800C8554.CPP */
#if defined(VERSION_EU)
/* ROM-grounded data for eu; supplied-list member has no us-rev1 placement. */
float g_xprintfFloatConstantWords[3] = {
    127.0f, 7168.0f, 0.09765625f,
};
#endif
