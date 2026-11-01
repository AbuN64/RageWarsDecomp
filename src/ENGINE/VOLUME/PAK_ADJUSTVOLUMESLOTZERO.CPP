#include "include_asm.h"

#include "MENU/OPTIONEDITSTATE.H"
#include "COMMON/SHARED_GAMESLOT.H"
#include "TYPES.H"
#include <ultra64.h>
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "SYSTEM/SOUND_CONTEXT_MUSIC_AND_VOICE_CONTROL.H"
extern s32 Menu_AdjustValue(struct MenuValueStepView *menu,s32 value,s32 step,s32 minimum,s32 maximum,s32 wrap);

/* Adjusts the volume in steps of eight and starts a sound preview when no preview is playing. */

s32 Pak_AdjustVolumeSlotZero(void *unused, void *menu) {
    s32 volume;
    volume = g_gameSettings.volume[0];
    volume = Menu_AdjustValue(menu, volume, 8, 0, 0xFF, 0);
    if(volume==247)volume=248;
    g_gameSettings.volume[0]=volume;
    if (SoundElement_GetMusicPlaybackEnabled() <= 0) {
        SoundElement_SetMusicPlaybackEnabled(1);
    }
    return 0;
}
