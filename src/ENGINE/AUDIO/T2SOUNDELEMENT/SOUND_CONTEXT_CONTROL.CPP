#include "COMMON/SOUNDINFO.H"
#include "COMMON/GAME_SESSION.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "SYSTEM/SOUND_CONTEXT_MUSIC_AND_VOICE_CONTROL.H"
#include "TEXTURE/SOUND_UPDATEAUDIOCONTEXT.H"
#include "COMMON/AUDIO_CONTEXT.H"
#include "include_asm.h"
#include "SYSTEM/SOUND_CONTEXT_LOCK_AND_ACTIVITY.H"

/* 8025E280.CPP */
extern void Audio_SetVoiceMixValue(GameAudioContext *context, int mixValue);
extern void Audio_SetListenerCamera(GameAudioContext *object, int value);
extern void Audio_SetMusicGainScalingEnabled(GameAudioContext *object, int value);
extern void Audio_FadeOutContextMusic(int contextAddress);
extern void Audio_SetPeriodicSoundEnabled(char *object, int value);
extern void Audio_StopContextMusic(int contextAddress);
extern void Audio_EnableContextMusicGainOverride(int contextAddress);
extern void Audio_DisableContextMusicGainOverride(int contextAddress);
extern void Audio_ClearContextVoiceFlags(int contextAddress);

/** Read the global word at VRAM 0x8010DE0C. */

s32 Audio_SetClampedAudioLevel(s32 *, f32);

void SoundElement_SetTrackAndPeriodicPlayback(int trackId)
{
  int hasTrack;
  hasTrack = trackId != 0;
  g_soundElementContext.track = (s32) trackId;
  if (hasTrack)
  {
    if (1)
    {
      SoundElement_EnablePeriodicSound();
    }
    return;
  }
  SoundElement_DisablePeriodicSound();
}

void SoundElement_SetVoiceMixValue(s32 mixValue) {
    Audio_SetVoiceMixValue(&g_soundElementContext, mixValue);
}

int SoundElement_GetMusicPlaybackEnabled(void) {
    return g_musicPlaybackEnabled;
}

void SoundElement_SetMusicPlaybackEnabled(s32 a) {
    if (g_gameSession.transitionBlocked == 0) {
        s32 *p = &g_musicPlaybackEnabled;
        if (*p != a) {
            *p = a;
            if (a == 0) {
                SoundElement_FadeOutMusic();
            }
        }
    }
}

void SoundElement_FadeOutMusic(void) {
    Audio_FadeOutContextMusic((s32) &g_soundElementContext);
}

void SoundElement_StopMusic(void) {
    Audio_StopContextMusic((s32) &g_soundElementContext);
}

void SoundElement_EnableMusicGainOverride(void) {
    Audio_EnableContextMusicGainOverride((s32) &g_soundElementContext);
}

void SoundElement_DisableMusicGainOverride(void) {
    Audio_DisableContextMusicGainOverride((s32) &g_soundElementContext);
}

void SoundElement_DisablePeriodicSound(void) {
    Audio_SetPeriodicSoundEnabled(&g_soundElementContext, 0);
}

void SoundElement_EnablePeriodicSound(void) {
    Audio_SetPeriodicSoundEnabled(&g_soundElementContext, 1);
}

void SoundElement_SetListenerCamera(s32 listenerCameraAddress) {
    Audio_SetListenerCamera(&g_soundElementContext, listenerCameraAddress);
}

void SoundElement_SetMusicGainScalingEnabled(s32 enabled) {
    Audio_SetMusicGainScalingEnabled(&g_soundElementContext, enabled);
}

void SoundElement_SetClampedAudioLevel(f32 level) {
    Audio_SetClampedAudioLevel(&g_soundElementContext, level);
}

void SoundElement_ClearVoiceFlags(void) {
    Audio_ClearContextVoiceFlags((s32) &g_soundElementContext);
}

void SoundElement_AcquireContextLock(void) {
    Sound_AcquireContextLock(&g_soundElementContext);
}

/* 8025E280_3.CPP */
s32 Sound_HasActiveOrPendingSound(struct GameAudioContext *, s32);

void SoundElement_ReleaseContextLock(void) {
    Sound_ReleaseContextLock(&g_soundElementContext);
}

struct GameAudioContext;

s32 SoundElement_HasActiveOrPendingSound(s32 wantedKey) {
    return Sound_HasActiveOrPendingSound(&g_soundElementContext, wantedKey);
}

