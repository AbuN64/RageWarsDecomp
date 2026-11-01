#ifndef ENGINE_AUDIO_T2SOUNDELEMENT_SOUND_CONTEXT_CONTROL_H
#define ENGINE_AUDIO_T2SOUNDELEMENT_SOUND_CONTEXT_CONTROL_H
#include "COMMON/SOUNDINFO.H"
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
#endif
