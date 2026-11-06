#include "Menu/menu_event_handlers.h"
#include "Menu/Level/Level_getselectedresourceid/level_getselectedresourceid_symbols.h"

#if defined(VERSION_US_REV1)
unsigned int g_levelSelectedResourceFrameAnimPointers[3] = {
    (unsigned int)SmpFrameAnim_UpdateFrameSequence - 0x80000000U, 0x00000000, 0x00000000,
};
#endif
