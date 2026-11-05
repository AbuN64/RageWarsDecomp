#ifndef AUDIO_VOICE_H
#define AUDIO_VOICE_H
#include "Common/audio_voice_slots.h"
extern f32 Audio_InterpolatePitchTable(f32 pitch);
extern f32 Audio_RandomizeScaledByteRange(u8 center, u8 spread);
extern void Audio_SetScaledVoiceVolume(void *voice, s32 volume);
extern void Audio_SetScaledVoicePitch(void *voice, f32 pitch);
extern s16 Audio_RandomizeSignedRange(s16 center, s16 spread);
extern void Audio_UpdateVoicePool(void **pool);
extern void Audio_ClearVoiceFlags(s32 a);
f32 Audio_ComputeDistanceAttenuation(f32 *a, f32 *b);
struct VoiceKeyPairTable;
int Audio_FindVoiceByKeyPair(struct VoiceKeyPairTable *obj, int keyA, int keyB);
struct VoiceKeyTable;
s32 Audio_HasVoiceOrReservedSlotWithKey(struct VoiceKeyTable *record, s32 value);
s32 Audio_HasVoiceWithKey(struct VoiceKeyTable *record, s32 value);
void Audio_InitializeVoiceParameters(void *voiceRecord, void *desc, s32 extra);
void Audio_InitializeVoicePool(s32 *voicePool, s32 ownerAddress);
void Audio_SetVoicePositionTracking(void *voiceRecord, void *initialPosition, int trackedPositionAddress);
void Audio_StopVoiceSlot(s32 voicePoolAddress, s16 slotIndex);
struct AudioVoiceFlagsPoolView;
void Audio_StopVoicesByFlags(struct AudioVoiceFlagsPoolView *record, s32 value);
struct VoiceStopKeyTable;
void Audio_StopVoicesByKey(struct VoiceStopKeyTable *record, s32 value);
struct VoiceSecondaryKeyTable;
void Audio_StopVoicesBySecondaryValue(struct VoiceSecondaryKeyTable *record, s32 value);
void Audio_StopVoicesExceptKey(struct VoiceStopKeyTable *record, s32 value);
struct CLoopingSoundData_t;
void SoundVoicePool_Initialize(void *soundVoicePool, struct CLoopingSoundData_t *availableNodes, s32 nodeCount);
void SoundVoicePool_Pause(void *voicePool);
s32 SoundVoicePool_StopNode(void *work, void *wantedNode);
#endif
