#include "TYPES.H"
#include "COMMON/SHARED_GAMESLOT.H"
extern s32 g_gameSettingsView __asm__("g_gameSettings");

#if defined(VERSION_US_REV1)

/* Toggles bit 0 of the settings flag word g_gameSettings and returns 0. */
s32 Level_ToggleGameFlagOne(void) {
    g_gameSettingsView ^= 1;
    return 0;
}
#endif
