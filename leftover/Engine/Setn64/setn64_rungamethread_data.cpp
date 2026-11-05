#include "types.h"

#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE)
const char g_runGameThreadConstants[6] __attribute__((aligned(2))) = "%s %s\000";
#endif
#if defined(VERSION_EU)
const char g_runGameThreadConstants[6] __attribute__((aligned(2))) = "%s %s\000";
#endif
#if defined(VERSION_EU_X)
const char g_runGameThreadConstants[6] __attribute__((aligned(2))) = "%s %s\000";
#endif
#if defined(VERSION_US)
const char g_runGameThreadConstants[6] __attribute__((aligned(2))) = "%s %s\000";
#endif
#endif

#if defined(VERSION_US_REV1)
const char g_gameThreadTwoStringFormat_usrev1_CB0F0[6] = "%s %s";
#endif
