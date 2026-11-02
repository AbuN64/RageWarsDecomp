#include "TYPES.H"

#include "include_asm.h"

/* ROM-grounded us-rev1 data; explicit withholding in other holders. */
#if defined(VERSION_DE)
int g_FrontendUpdatescreenmodeWords1 = -1;
#endif
#if defined(VERSION_EU)
int g_FrontendUpdatescreenmodeWords1 = -1;
#endif
#if defined(VERSION_EU_X)
int g_FrontendUpdatescreenmodeWords1 = -1;
#endif
#if defined(VERSION_US)
int g_FrontendUpdatescreenmodeWords1 = -1;
#endif
#if defined(VERSION_US_REV1)
int g_FrontendUpdatescreenmodeWords1 = -1;
#endif
