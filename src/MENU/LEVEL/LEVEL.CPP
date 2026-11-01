#include "TYPES.H"

#if defined(VERSION_US_REV1)
extern s32 g_gameSettings;

/* Toggles bit 0 of the settings flag word g_gameSettings and returns 0. */
s32 Level_ToggleGameFlagOne(void) {
    g_gameSettings ^= 1;
    return 0;
}
#endif
