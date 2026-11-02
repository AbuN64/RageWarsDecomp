#include "include_asm.h"

/* The string occupies 23 bytes. Keep its following retained byte in the
 * same object's storage: us 800DB9AF=53, eu-x 800E853F=7c,
 * de 800DCCFF=70, us-rev1 800E0D2F=6c. These are not string characters. */
#if defined(VERSION_EU)
const char s_mempakWriteTempDataText[23] = "Mempak write temp data\000";
#endif
#if defined(VERSION_US)
const char s_mempakWriteTempDataText[24] = "Mempak write temp data\000\000S";
#endif
#if defined(VERSION_EU_X)
const char s_mempakWriteTempDataText[24] = "Mempak write temp data\000\000|";
#endif
#if defined(VERSION_DE)
const char s_mempakWriteTempDataText[24] = "Mempak write temp data\000\000p";
#endif
#if defined(VERSION_US_REV1)
const char g_pakWriteScratchNoteName[24] = "Mempak write temp data\000\000l";
#endif
