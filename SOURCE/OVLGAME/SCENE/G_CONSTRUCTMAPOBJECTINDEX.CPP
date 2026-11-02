#include "include_asm.h"

#if !(defined(VERSION_US_REV1))
#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_US)
const char g_sceneConstructMapObjectIndexText[35] =
    "CScene__ConstructMap: object index\000";
#endif
#if defined(VERSION_EU_X)
const char g_sceneConstructMapObjectIndexText[36] =
    "CScene__ConstructMap: object index\000\000";
#endif
#endif

#if defined(VERSION_US_REV1)
const u8 g_constructMapObjectIndex[35] =
    "CScene__ConstructMap: object index";
#endif
