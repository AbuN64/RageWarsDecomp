#ifndef SYSTEM_SOUND_CONTEXT_LOCK_AND_ACTIVITY_H
#define SYSTEM_SOUND_CONTEXT_LOCK_AND_ACTIVITY_H
#include "COMMON/SOUNDINFO.H"
extern s32 SoundElement_HasActiveOrPendingSound(s32 wantedKey);
extern void SoundElement_ReleaseContextLock(void);
#endif
