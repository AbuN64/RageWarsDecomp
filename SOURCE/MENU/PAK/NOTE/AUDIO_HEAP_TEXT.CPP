#include "include_asm.h"

/* Eleven-byte text and the same object's retained final byte, when present:
 * eu-x 800E859F=38, de 800DCD5F=63, us-rev1 800E0D8F=40. */
#if defined(VERSION_EU_X)
const char g_audioHeapText[12] = "audio heap\0008";
#elif defined(VERSION_DE)
const char g_audioHeapText[12] = "audio heap\000c";
#elif defined(VERSION_US_REV1)
const char g_audioHeapText[12] = "audio heap\000@";
#else
const char g_audioHeapText[11] = "audio heap";
#endif
