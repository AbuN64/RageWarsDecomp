#ifndef TEXTURE_SOUND_UPDATEAUDIOCONTEXT_H
#define TEXTURE_SOUND_UPDATEAUDIOCONTEXT_H
#include "TYPES.H"
extern void Sound_AcquireContextLock(s32 *engine);
extern void Sound_ReleaseContextLock(s32 *engine);
extern s32 Sound_UpdateAudioContext(void *context);
#endif
