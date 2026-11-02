#include "include_asm.h"

#if defined(VERSION_DE) || defined(VERSION_US)
const char s_snapshotThreePartNumberFormatVariant[14] =
    "%3d.%02d.%02d";
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/pak_format_dotted_triple_us_rev1.c */
const char g_pakFormatDottedTriple[14] =
    "%3d.%02d.%02d";
#endif
