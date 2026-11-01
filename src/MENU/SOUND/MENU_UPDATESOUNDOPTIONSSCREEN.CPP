#include "COMMON/MENUSELECTIONMESSAGE.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "COMMON/SCREEN.H"
#include "TYPES.H"
extern struct SoundOptionsScreen *g_soundOptionsScreen;
#include "COMMON/INTEGERSTATE530.H"
#include "SYSTEM/SOUND_CONTEXT_MUSIC_AND_VOICE_CONTROL.H"
#include "RENDER/SOUNDELEMENT_PLAYFLATSOUND.H"
#include "SCENE/CACHE_FREEMEMORY.H"

/* Releases the object g_soundOptionsScreen holds through Cache_FreeMemory, clears g_soundOptionsScreen and returns zero. */



/* Runs the sound options screen g_soundOptionsScreen each frame: when its menu reports 4 it calls
   MarkMenuEventHandled and leaves through SmXlate_SwitchScreen with the stored target or Menu_ReturnToPreviousScreen when
   that is -1; otherwise it copies the effects slider into option byte g_soundEffectsVolumeOption, playing sound
   0x460 when it changed, and the music slider into g_gameSettingsVolumeBytes, stopping the music through
   SoundElement_SetMusicPlaybackEnabled(0) below 5 or starting track 0x34 when SoundElement_GetMusicPlaybackEnabled reports none playing.
   Returns zero. */






extern s32 SmpSlider_GetTransitionMode(s32 *record);

extern s32 SmpSlider_GetSliderItem(s32 *record);


extern void SmXlate_SwitchScreen(s32);




/* Calls MarkMenuEventHandled; when Menu_GetFocusedElementId reports 0x73, sets the word at offset 0x14 of the object
   g_soundOptionsScreen points to to -1 and calls SmpSlider_SetTransitionMode on its first word with 2. Returns zero. */


s32 Menu_FreeSoundOptionsScreen(void) {
    Cache_FreeMemory(g_soundOptionsScreen);
    g_soundOptionsScreen = 0;
    return 0;
}

/* Returns zero. Nothing in the cartridge image calls it or stores its address as a word, so it is
   either reached through a pointer built at run time or never used. */
s32 Menu_SoundOptionsReturnZero(void) {
    return 0;
}

s32 Menu_UpdateSoundOptionsScreen(void) {
    u8 *options;
    s32 value;
    s32 track;

    switch (SmpSlider_GetTransitionMode(g_soundOptionsScreen->menu)) {
    case 3:
        break;
    case 4:
        MarkMenuEventHandled();
        if (g_soundOptionsScreen->target != -1) {
            SmXlate_SwitchScreen(g_soundOptionsScreen->target);
            return 0;
        }
        Menu_ReturnToPreviousScreen();
        return 0;
    }
    value = SmpSlider_GetSliderItem(g_soundOptionsScreen->effects);
    options = &g_gameSettings.volume[1];
    if (value != options[0]) {
        options[0] = value;
        SoundElement_PlayFlatSound(1120);
    }
    value = SmpSlider_GetSliderItem(g_soundOptionsScreen->music);
    if (value != options[-1]) {
        options[-1] = value;
        track = 0;
        if ((u8)value >= 5) {
            if (SoundElement_GetMusicPlaybackEnabled() != 0) {
                return 0;
            }
            track = 52;
        }
        SoundElement_SetMusicPlaybackEnabled(track);
    }
    return 0;
}

s32 Menu_ConfirmSoundOptionsScreen(void) {
    struct SoundOptionsScreen *state;
    MarkMenuEventHandled();
#if defined(VERSION_DE)
    if (Menu_GetFocusedElementId() == 113) {
#elif defined(VERSION_EU) || defined(VERSION_US) || defined(VERSION_US_REV1)
    if (Menu_GetFocusedElementId() == 115) {
#elif defined(VERSION_EU_X)
    if (Menu_GetFocusedElementId() == 119) {
#endif
        state = g_soundOptionsScreen;
        state->target = -1;
        SmpSlider_SetTransitionMode((s32)state->menu, 2);
    }
    return 0;
}
