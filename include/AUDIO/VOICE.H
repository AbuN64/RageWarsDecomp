#ifndef AUDIO_VOICE_H
#define AUDIO_VOICE_H
#include "COMMON/OBJRECAT4V6.H"
extern f32 Audio_InterpolatePitchTable(f32 pitch);
extern f32 Audio_RandomizeScaledByteRange(u8 center, u8 spread);
extern void Audio_SetScaledVoiceVolume(void *voice, s32 volume);
extern void Audio_SetScaledVoicePitch(void *voice, f32 pitch);
extern s16 Audio_RandomizeSignedRange(s16 center, s16 spread);
extern void Audio_UpdateVoicePool(void **pool);
extern void Audio_ClearVoiceFlags(s32 a);
#endif
