#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE) || defined(VERSION_US)
const char s_pakNoteLabelFormat[6] =
    "%d.%s";
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X)
const char s_pakNoteLabelFormat[3] =
    "%d";
#endif
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
const char s_pakNoteIndexAndNameFormatUsRev1[6] =
    "%d.%s";
#endif
