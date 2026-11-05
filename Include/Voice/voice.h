#ifndef VOICE_VOICE_H
#define VOICE_VOICE_H
#include "Engine/Audio/voice.h"
#include "Common/audio_voice_slots.h"
#include "Audio/voice_and_spatial_source_views.h"
#include "Audio/voice.h"
struct AudioVoiceControlSlotView;
struct AudioVoiceSoundSlotView;
struct RecordD90;
extern void Audio_InitializeVoiceRecord(void *, int owner, int);
extern s32 Audio_GetVoiceSoundState(struct AudioVoiceSoundSlotView *voicePool, s16 slotIndex);
extern void Audio_PlayVoiceSound(struct AudioVoiceSoundSlotView *base, s16 index);
extern s32 Audio_ReleaseMatchingExclusiveVoice(struct RecordD90 *record, s16 value, s16 id);
extern void Audio_ClearVoiceFlags(s32 a);
extern void Audio_SetVoiceTrackId(void *, int newTrackId);
extern void Audio_UpdateVoicePool(void * *);
extern f32 Audio_InterpolatePitchTable(f32);
extern s16 Audio_RandomizeSignedRange(s16, s16);
extern f32 Audio_RandomizeScaledByteRange(u8, u8);
extern f32 Audio_ComputeSpatialAttenuationCurve(char *source, char *listener);
extern void Audio_SetScaledVoiceVolume(void *, s32);
extern void Audio_SetScaledVoicePitch(void *, f32);
extern void Audio_SetVoicePan(struct AudioVoiceControlSlotView *voiceRecord, s32 panValue);
extern void Audio_QueryVoicePlaybackState(struct AudioVoiceControlSlotView *voiceRecord);
extern void Audio_StartSelectedVoice(struct AudioVoiceControlSlotView *voiceRecord);
extern void Audio_StopVoiceForDifferentKey(struct AudioVoiceControlSlotView *voiceRecord);
extern void Audio_DeallocateVoiceSlot(struct AudioVoiceControlSlotView *voiceRecord);
extern void SoundVoicePool_ResetNode(void *cLoopingSoundData);
extern void SoundVoicePool_ResetNodeNoOp(void);
extern void *SoundVoicePool_PlaySpatialSound(void *voicePool, s32 soundId, CVector3 *soundPosition, void *position, s32 fallback);

extern void SoundVoicePool_RetireFinishedSounds(void *soundVoicePool);
extern void SoundVoicePool_StopAll(void *soundVoicePool);
extern void SoundVoicePool_GetGlobalStateNoOp(void);
#endif
