#ifndef ENGINE_AUDIO_T2SOUNDELEMENT_SOUND_CONTEXT_CONTROL_H
#define ENGINE_AUDIO_T2SOUNDELEMENT_SOUND_CONTEXT_CONTROL_H
#include "Common/soundinfo.h"
struct GameAudioContext;
extern void SoundElement_SetTrackAndPeriodicPlayback(int trackId);
extern void SoundElement_SetVoiceMixValue(s32 mixValue);
extern int SoundElement_GetMusicPlaybackEnabled(void);
extern void SoundElement_SetMusicPlaybackEnabled(s32 a);
extern void SoundElement_FadeOutMusic(void);
extern void SoundElement_StopMusic(void);
extern void SoundElement_EnableMusicGainOverride(void);
extern void SoundElement_DisablePeriodicSound(void);
extern void SoundElement_EnablePeriodicSound(void);
extern void SoundElement_SetMusicGainScalingEnabled(s32 enabled);
extern void SoundElement_SetClampedAudioLevel(f32);
extern void SoundElement_ClearVoiceFlags(void);
extern void SoundElement_AcquireContextLock(void);
extern void SoundElement_ReleaseContextLock(void);
extern s32 SoundElement_HasActiveOrPendingSound(s32 wantedKey);
void SoundElement_SetListenerCamera(s32 listenerCameraAddress);
extern void Audio_SetListenerCamera(struct GameAudioContext *object, int value);
extern void Audio_SetMusicGainScalingEnabled(struct GameAudioContext *object, int value);
extern void Audio_FadeOutContextMusic(int contextAddress);
extern void Audio_StopContextMusic(int contextAddress);
extern void Audio_EnableContextMusicGainOverride(int contextAddress);
extern void Audio_DisableContextMusicGainOverride(int contextAddress);
extern void Audio_ClearContextVoiceFlags(int contextAddress);
#endif
