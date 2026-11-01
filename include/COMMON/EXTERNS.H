#ifndef COMMON_EXTERNS_H
#define COMMON_EXTERNS_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"



#include "COMMON/SHAREDPLAYER.H"
extern void Audio_ResolveInstrumentSectionZero(void *instrument, s16 index);

#include "COMMON/LISTNODE.H"
extern int Audio_IsSoundInstanceLimitReached(AudioInstanceLimitOwner *obj, int id);

#include "COMMON/RESIDENT_EVENT_HANDLER.H"




extern void AudioWorld_RecyclePendingSoundsByKey(void *channelOwner, s32 matchingKey);
extern void AudioWorld_RecyclePendingSoundsByTrack(struct AudioPendingSoundListOwner *, s32);


#include "COMMON/VECTOR4F.H"

extern s32 g_musicRequestedTrack;
extern s32 g_musicStartupFrameCount;
extern f32 g_musicDefaultFadeAndVolumeScale;
extern f32 g_musicVolumeAndFadeScale;
extern f32 g_musicPlaybackVolumeScale;
extern f32 g_musicDuckedVolumeScale;
extern f32 g_musicTargetVolumeToMidiScale;
extern f32 g_musicCurrentVolumeToMidiScale;
extern f32 g_musicFadeDurationLimits;
#endif
