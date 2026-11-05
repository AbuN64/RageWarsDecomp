#ifndef CHANNEL_CHANNEL_UPDATEVOICEVOLUME_H
#define CHANNEL_CHANNEL_UPDATEVOICEVOLUME_H
#include "types.h"
struct AudioVolumeVoice;
void Channel_UpdateVoiceVolume(struct AudioVolumeVoice *voice);
struct VoiceChannelUpdateVoicePan;
void Channel_UpdateVoicePan(struct VoiceChannelUpdateVoicePan *voice);
struct Emitter;
void Channel_UpdateDistancePitchFactor(struct Emitter *emitter);
#endif
