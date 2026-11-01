#include "TYPES.H"

#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
const char g_SetN64_RunGameThreadConstantWords[6] __attribute__((aligned(2))) = "%s %s\000";
#endif
#if defined(VERSION_EU)
const char g_SetN64_RunGameThreadConstantWords[6] __attribute__((aligned(2))) = "%s %s\000";
#endif
#if defined(VERSION_EU_X)
const char g_SetN64_RunGameThreadConstantWords[6] __attribute__((aligned(2))) = "%s %s\000";
#endif
#if defined(VERSION_US)
const char g_SetN64_RunGameThreadConstantWords[6] __attribute__((aligned(2))) = "%s %s\000";
#endif
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/g_gameThreadTwoStringFormat_Setn64RungamethreadData.c */
const char g_gameThreadTwoStringFormat[6] = "%s %s";
#endif
