#ifndef VOICE_VOICE_H
#define VOICE_VOICE_H
#include "COMMON/OBJRECAT4V6.H"
#include "AUDIO/VOICE_AND_SPATIAL_SOURCE_VIEWS.H"
extern void Audio_InitializeVoiceRecord(void *, int owner, int);
extern s32 Audio_GetVoiceSoundState(AudioVoiceSoundSlotView *voicePool, s16 slotIndex);
extern void Audio_PlayVoiceSound(AudioVoiceSoundSlotView *base, s16 index);
extern s32 Audio_ReleaseMatchingExclusiveVoice(RecordD90 *record, s16 value, s16 id);
extern void Audio_ClearVoiceFlags(s32 a);
extern void Audio_SetVoiceTrackId(void *, int newTrackId);
extern void Audio_UpdateVoicePool(void * *);
extern f32 Audio_InterpolatePitchTable(f32);
extern s16 Audio_RandomizeSignedRange(s16, s16);
extern f32 Audio_RandomizeScaledByteRange(u8, u8);
extern f32 Audio_ComputeSpatialAttenuationCurve(char *source, char *listener);
extern void Audio_SetScaledVoiceVolume(void *, s32);
extern void Audio_SetScaledVoicePitch(void *, f32);
extern void Audio_SetVoicePan(AudioVoiceControlSlotView *voiceRecord, s32 panValue);
extern void Audio_QueryVoicePlaybackState(AudioVoiceControlSlotView *voiceRecord);
extern void Audio_StartSelectedVoice(AudioVoiceControlSlotView *voiceRecord);
extern void Audio_StopVoiceForDifferentKey(AudioVoiceControlSlotView *voiceRecord);
extern void Audio_DeallocateVoiceSlot(AudioVoiceControlSlotView *voiceRecord);
extern void SoundVoicePool_ResetNode(void *cLoopingSoundData);
extern void SoundVoicePool_ResetNodeNoOp(void);
extern void *SoundVoicePool_PlaySpatialSound(void *voicePool, s32 soundId, CVector3 *soundPosition, void *position, s32 fallback);
extern void SoundVoicePool_Pause(void *voicePool);
extern void SoundVoicePool_RetireFinishedSounds(void *soundVoicePool);
extern void SoundVoicePool_StopAll(void *soundVoicePool);
extern void SoundVoicePool_GetGlobalStateNoOp(void);
#endif
