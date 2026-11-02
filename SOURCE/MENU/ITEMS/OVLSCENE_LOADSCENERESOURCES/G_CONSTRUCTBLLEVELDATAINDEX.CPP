#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X)
const char s_sceneConstructLevelDataIndexText[37] =
    "CScene__Construct: BLLevelData Index\000";
#endif
#if defined(VERSION_US)
const char s_sceneConstructLevelDataIndexText[40] =
    "CScene__Construct: BLLevelData Index\000\000\000\000";
#endif
#endif

#if defined(VERSION_US_REV1)
const char g_constructBlLevelDataIndex[37] =
    "CScene__Construct: BLLevelData Index";
#endif
