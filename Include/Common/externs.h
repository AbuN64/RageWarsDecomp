#ifndef COMMON_EXTERNS_H
#define COMMON_EXTERNS_H
#include "types.h"
#include "Common/runtime_declarations.h"



#include "Common/sharedplayer.h"
struct AudioInstanceLimitOwner;
extern void Audio_ResolveInstrumentSectionZero(void *instrument, s16 index);

#include "Common/listnode.h"
extern int Audio_IsSoundInstanceLimitReached(struct AudioInstanceLimitOwner *obj, int id);

#include "Common/resident_event_handler.h"




extern void AudioWorld_RecyclePendingSoundsByKey(void *channelOwner, s32 matchingKey);
extern void AudioWorld_RecyclePendingSoundsByTrack(struct AudioPendingSoundListOwner *, s32);


#include "Common/vector4f.h"

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
