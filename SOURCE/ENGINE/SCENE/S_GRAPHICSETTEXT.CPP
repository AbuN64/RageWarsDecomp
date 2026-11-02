#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
const char s_graphicsetText[12] =
    "graphicset\000\000";
#endif
#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
const char s_graphicsetText[11] =
    "graphicset\000";
#endif
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/s_graphicsetText_SGraphicsettext.c */
const char k_SGraphicsettextEncodedBytes[11] =
    "graphicset";
#endif
