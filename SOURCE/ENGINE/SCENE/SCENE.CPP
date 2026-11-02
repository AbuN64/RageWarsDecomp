#include "include_asm.h"

/* ROM-grounded data: rodata/shared/800CA374 */
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US_REV1)
const char g_levelNameText[11] = "level name\000";
#endif
#if defined(VERSION_US)
const char g_levelNameText[12] = "level name\000\000";
#endif
