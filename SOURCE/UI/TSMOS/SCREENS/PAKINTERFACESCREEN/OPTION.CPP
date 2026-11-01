#include "include_asm.h"
#include "COMMON/MENURECAT20V1.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "../../../../../sdk/include/AUDIO/sprintf.H"
#if !(defined(VERSION_US_REV1))
extern s32 g_gameSettings;
/* Toggles bit 0 of the settings flag word g_gameSettings and returns 0. */
s32 Pak_ToggleTextChoice(void) {
    g_gameSettings ^= 1;
    return 0;
}
#endif
