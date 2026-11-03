#include "include_asm.h"
#include "OVLSCENE/OVLSCENE.H"

#if !(defined(VERSION_US_REV1))
const char k_ovlsceneTextBytes[26] =
    "load save persistent data\000";
#endif

#if defined(VERSION_US_REV1)
const char g_loadSavePersistentData[26] = "load save persistent data";
#endif
