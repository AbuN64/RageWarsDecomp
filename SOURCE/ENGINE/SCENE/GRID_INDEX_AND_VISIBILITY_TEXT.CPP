#include "include_asm.h"
#include "MENU/ITEMS/SCENE/GRID_INDEX_AND_VISIBILITY_TEXT.H"

const char g_gridBoundsAndSectionsIndexText[32] = "grid bounds\000grid sections index";

#if defined(VERSION_DE) || defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)
const char g_visibilityText[11] =
    "Visibility\000";
#endif
