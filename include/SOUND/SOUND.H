#ifndef SOUND_SOUND_H
#define SOUND_SOUND_H
struct GameAudioContext;
struct CVector3_t;
s32 Sound_PlayInstrumentAtPosition(struct GameAudioContext *self, s32 index, struct CVector3_t position, s32 voiceParameter);
s32 Sound_UpdateSoundSlot(struct GameAudioContext *context, s32 id, s32 unused, struct CVector3_t *position);
#endif
