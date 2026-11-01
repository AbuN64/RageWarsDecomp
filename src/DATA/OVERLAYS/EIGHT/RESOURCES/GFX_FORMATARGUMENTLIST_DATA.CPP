#include "TYPES.H"

#include "include_asm.h"

#if defined(VERSION_DE)
char g_GfxFormatargumentlistBytes1[36] __attribute__((aligned(1))) = "                0000000000000000\000\000\000\000";
#endif
#if defined(VERSION_EU)
char g_GfxFormatargumentlistBytes1[36] __attribute__((aligned(1))) = "                0000000000000000\000\000\000\000";
#endif
#if defined(VERSION_EU_X)
char g_GfxFormatargumentlistBytes1[36] __attribute__((aligned(1))) = "                0000000000000000\000\000\000\000";
#endif
#if defined(VERSION_US)
char g_GfxFormatargumentlistBytes1[36] __attribute__((aligned(1))) = "                0000000000000000\000\000\000\000";
#endif
#if defined(VERSION_US_REV1)
char g_GfxFormatargumentlistBytes1[36] __attribute__((aligned(1))) = "                0000000000000000\000";
#endif

#if defined(VERSION_US)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_EU_X)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_EU)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_DE)
/* bytes live in the preceding array */
#endif
