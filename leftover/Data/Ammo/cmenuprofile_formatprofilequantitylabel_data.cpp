#include "Data/rest_source_records.h"
#include "include_asm.h"

#if defined(VERSION_US)
const char s_CmenuprofileFormatprofilequantitylabelEquEosRText[12] =
    "equ\004.eosR\000\000\000";
#endif
#if defined(VERSION_DE)
/* Stale "%3d" format text bytes; no instruction reads it. */
const ByteBlock12 g_profileQuantityStaleFormatText = {
    { 0, 0, 0, 0, 37, 51, 100, 0, 0, 0, 0, 0 },
};
#endif

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
const char g_profileQuantityTwoDigitFormat[5] = "%02d";
#endif
