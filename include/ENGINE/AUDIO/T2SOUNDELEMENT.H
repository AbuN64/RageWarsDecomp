#ifndef ENGINE_AUDIO_T2SOUNDELEMENT_H
#define ENGINE_AUDIO_T2SOUNDELEMENT_H
#include "COMMON/STATERECAT34.H"
#include "TYPES.H"

extern void SoundElement_InitializeContext(void);

extern s32 SoundElement_PlayPositionedSoundWithScale(s32 trackId, CVector3 soundPosition, s32 spatialMode, s32 ownerId, f32 playbackScale);

extern s32 SoundElement_PlayFlatSound(s32 track);

extern s32 SoundElement_PlayInstrumentAtPosition(s32 index, CVector3 position, s32 voiceParameter);

extern int SoundElement_PlayFlatInstrument(int index);

extern void SoundElement_PlayDialogGroup(s32 callback);

extern void SoundElement_StopDialog(void);

extern void SoundElement_StopSoundsByIdentifier(s32 soundId);

extern void SoundElement_StopAudioByKey(s32 matchingKey);

extern void SoundElement_StopAudioBySecondaryValue(s32 matchingValue);

extern void SoundElement_StopAudioByMask(s32 matchingFlags);

extern void SoundElement_StopAudioExceptKey(s32 retainedKey);

extern void SoundElement_UpdateContext(void);

extern int Sound_PlayInstrumentAtPosition(void *self, int index, CVector3 position, int voiceParameter);

extern s32 Sound_StopSoundsByIdentifier(void *context, s32 id);

struct GameAudioContext;

extern void Sound_InitializeContext(struct GameAudioContext *context);

extern int SoundElement_CountOwnerVoices(int owner);
#endif
