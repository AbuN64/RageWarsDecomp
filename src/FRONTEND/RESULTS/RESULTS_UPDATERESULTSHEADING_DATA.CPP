#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
const char g_characterAndTimeFormatText[27] =
    "[CHARACTER]\000%d:%02d\000[TIME]\000";
#endif

#if defined(VERSION_US_REV1)
const char k_ResultsUpdateresultsheadingEncodedBytes[27] =
    "[CHARACTER]\000%d:%02d\000[TIME]";
#endif
