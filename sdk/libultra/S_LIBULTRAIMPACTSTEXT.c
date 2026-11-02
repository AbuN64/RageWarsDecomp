#include "include_asm.h"


#if defined(VERSION_EU) || defined(VERSION_EU_X)
/* Zero word ending the object; no instruction reads it. */
unsigned int g_libgultraSetWatchpointZeroTail[1] = {
    0x00000000,
};
#endif
