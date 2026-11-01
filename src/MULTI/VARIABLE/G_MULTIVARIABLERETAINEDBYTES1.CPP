#include "include_asm.h"

/* "%s" format for an unnamed typed menu variable, formatted in MULTI_ADJUSTTYPEDMENUVARIABLE.CPP. */
#if defined(VERSION_DE) || defined(VERSION_EU_X)
const char g_debugVariableUnnamedFormat[] = "%s";
#endif
#if defined(VERSION_EU) || defined(VERSION_US)
const char g_debugVariableUnnamedFormat[4] = "%s";
#endif

#if defined(VERSION_US_REV1)
const char g_debugVariableUnnamedFormat[] = "%s";
#endif
