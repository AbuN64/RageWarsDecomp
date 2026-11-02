#include "include_asm.h"
#include "COMMON/SHARED_GAMESLOT.H"
#include "MENU/OPTIONEDITSTATE.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/SOUNDINFO.H"
#include "COMMON/ACTORRECAT5E0.H"
#include "SYSTEM/SOUND_CONTEXT_MUSIC_AND_VOICE_CONTROL.H"

#if defined(VERSION_EU) || defined(VERSION_EU_X)

s32 Pak_RestoreAudioAndCloseMenu(void *first, void *second, void *third) { SoundElement_StopAudioExceptKey(-1); SoundElement_SetVoiceMixValue(0); if (g_musicPreviewMenuActive != 0) { SoundElement_EnableMusicGainOverride(); } SoundElement_SetMusicPlaybackEnabled(g_menuSavedAudioSelection); Control_SetMenuControlFlag(); return Menu_TryCreateMenu(first, second, third); }

s32 Pak_AdjustVolumeSlotTwo(void *first, void *second) { u8 *option = &g_gameSettings.volume[2]; s32 value = *option; value = Menu_AdjustValue(second, value, 8, 0, 0xFF, 0); if (value == 247) { value = 248; } *option = value; return 0; }
#endif

#if defined(VERSION_DE) || defined(VERSION_US) || defined(VERSION_US_REV1)
/* Stops sound for a menu: calls SoundElement_StopAudioExceptKey with -1 and SoundElement_SetVoiceMixValue with zero, calls
   SoundElement_EnableMusicGainOverride when g_musicPreviewMenuActive is set, passes g_menuSavedAudioSelection to SoundElement_SetMusicPlaybackEnabled, calls Control_SetMenuControlFlag and
   returns what Menu_TryCreateMenu gives for the three arguments. */


extern s32 Menu_TryCreateMenu(void *, void *, void *);

s32 Pak_RestoreAudioAndCloseMenu(void *first, void *second, void *third) {
    SoundElement_StopAudioExceptKey(-1);
    SoundElement_SetVoiceMixValue(0);
    if (g_musicPreviewMenuActive != 0) {
        SoundElement_EnableMusicGainOverride();
    }
    SoundElement_SetMusicPlaybackEnabled(g_menuSavedAudioSelection);
    Control_SetMenuControlFlag();
    return Menu_TryCreateMenu(first, second, third);
}

/* Replaces the option byte g_soundEffectsVolumeOption_PakFormatvolumeslotone with what Menu_AdjustValue returns for the second argument, that byte, 8, 0, 0xFF and 0, turning 0xF7 into 0xF8, and returns zero. */

extern s32 Menu_AdjustValue(struct MenuValueStepView *menu,s32 value,s32 step,s32 minimum,s32 maximum,s32 wrap);

s32 Pak_AdjustVolumeSlotTwo(void *first, void *second) {
    u8 *option = &g_gameSettings.volume[2];
    s32 value = *option;

    value = Menu_AdjustValue(second, value, 8, 0, 0xFF, 0);
    if (value == 247) {
        value = 248;
    }
    *option = value;
    return 0;
}
#endif
