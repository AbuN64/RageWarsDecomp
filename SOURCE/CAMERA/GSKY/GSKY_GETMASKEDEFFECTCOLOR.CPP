#include "COMMON/VIEWFLAGS.H"
#include "CAMERA/FADE_AND_COLOR_BLEND_VIEWS.H"
#include "TYPES.H"
#include "CAMERA/GSKY.H"
#include "COMMON/SHARED_GAMESLOT.H"
#define g_gameSettingsView (*(s32 *)&g_gameSettings)



void Gsky_GetMaskedEffectColor(ThreeChannels *threeChannels, s8 *red, s8 *green, s8 *blue) {
    if (g_gameSettingsView & 0x4000) {
        *red = 0;
        *green = 0;
        *blue = 0;
        return;
    }
    *red = threeChannels->first & 0xF8;
    *green = threeChannels->second & 0xF8;
    *blue = threeChannels->third & 0xF8;
}
