#ifndef ENGINE_AUDIO_VOICE_H
#define ENGINE_AUDIO_VOICE_H
#include "types.h"

struct SoundVoicePool;
extern s32 *SoundVoicePool_GetGlobalState(void);
extern void SoundVoicePool_Resume(struct SoundVoicePool *soundVoicePool);
#endif
