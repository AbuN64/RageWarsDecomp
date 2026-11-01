#ifndef AUDIO_AUDIO_CHOOSEWEIGHTEDSOUNDVARIANT_H
#define AUDIO_AUDIO_CHOOSEWEIGHTEDSOUNDVARIANT_H
#include "COMMON/STATERECAT34.H"
struct AudioInstrumentPackView {
    unsigned char padding_0[11084];
    void *instrumentPack;
};
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
#endif
