#ifndef AUDIO_AUDIO_CHOOSEWEIGHTEDSOUNDVARIANT_H
#define AUDIO_AUDIO_CHOOSEWEIGHTEDSOUNDVARIANT_H
#include "Common/music_track_volume.h"
struct Track;
struct AudioInstrumentPackView {
    unsigned char padding_0[11084];
    void *instrumentPack;
};
s32 Audio_PlayPositionedSoundWithScale(struct GameAudioContext *context, s32 track, CVector3 position, s32 spatialMode, s32 owner, f32 volumeScale);
extern s32 Audio_GetVoiceMixValue(struct GameAudioContext *context);
extern void Audio_SetVoiceMixValue(struct GameAudioContext *context, s32 mixValue);
extern s32 Audio_CountSoundVoices(char *obj, s32 owner);
extern void * Audio_GetSoundPlayer(void *audioContext);
extern s32 Audio_PlayDialogGroup(struct GameAudioContext *audioContext, s32 group);
extern void Audio_StopContextDialog(s32 contextAddress);
extern void Audio_StopAudioByKey(struct GameAudioContext *context, s32 matchValue);
extern void Audio_StopAudioBySecondaryValue(struct GameAudioContext *context, s32 matchValue);
extern void Audio_StopAudioByMask(struct GameAudioContext *context, s32 matchMask);
extern void Audio_StopAudioExceptKey(void *context, s32 matchValue);
int Audio_GetSpatialPanMode(struct GameAudioContext *audioContext);
extern void Audio_SetPeriodicSoundEnabled(struct GameAudioContext *audioContext, int value);
extern f32 g_audioContextGainScaleConstants[];
extern void Audio_EnableMusicGainOverride(struct Track *a);
extern void Audio_DisableMusicGainOverride(struct Track *a);
#endif
