#ifndef TEXTURE_SOUND_UPDATEAUDIOCONTEXT_H
#define TEXTURE_SOUND_UPDATEAUDIOCONTEXT_H
#include "Audio/audio_chooseweightedsoundvariant.h"
#include "types.h"
extern void Sound_AcquireContextLock(s32 *engine);
extern void Sound_ReleaseContextLock(s32 *engine);
extern s32 Sound_UpdateAudioContext(void *context);
extern s32 AudioWorld_HasPendingSoundWithKey(void *channelOwner, s32 wantedKey);
#endif
