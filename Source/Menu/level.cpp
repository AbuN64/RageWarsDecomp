#include "types.h"
#include "Common/shared_gameslot.h"
#include "Menu/Level/level_symbols.h"

#if defined(VERSION_US_REV1)

/* Toggles bit 0 of the settings flag word g_gameSettings and returns 0. */
s32 Level_ToggleGameFlagOne(void) {
    g_gameSettings.flags ^= 1;
    return 0;
}
#endif
