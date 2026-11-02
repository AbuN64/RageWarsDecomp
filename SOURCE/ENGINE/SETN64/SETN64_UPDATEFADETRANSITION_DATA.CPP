#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
const char g_buildDateTimeText[21] =
    "Oct 19 1999\00010:19:36\000";
#endif
#if defined(VERSION_EU)
const char g_buildDateTimeText[21] =
    "Oct 13 1999\00015:24:28\000";
#endif
#if defined(VERSION_EU_X)
const char g_buildDateTimeText[21] =
    "Oct 15 1999\00010:56:04\000";
#endif
#if defined(VERSION_US)
const char g_buildDateTimeText[21] =
    "Oct  8 1999\00015:39:01\000";
#endif
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
const char g_buildDateTimeTextRev1[21] = "Oct 13 1999\0" "14:57:39";
#endif
