#include "DATA/REST_SOURCE_RECORDS.H"
#if defined(VERSION_DE)
#elif defined(VERSION_EU)
#elif defined(VERSION_EU_X)
#elif defined(VERSION_US)
RestsmpControllerStateAndEventWordsLayout875 g_smpControllerStateAndEventWords = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    "uR\000\000",
    0x98000000,
    { 1, 0 },
    0x1E475241,
    "PHIC",
};
#elif defined(VERSION_US_REV1)
RestsmpControllerStateAndEventWordsLayout876 g_smpControllerStateAndEventWords = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 177, 196, 1, 194, 134, 126 },
};
#endif
