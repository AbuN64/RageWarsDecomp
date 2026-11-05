#ifndef AUDIO_SYNTH_PLAYER_AND_VOICE_RECORDS_H
#define AUDIO_SYNTH_PLAYER_AND_VOICE_RECORDS_H
#include "Common/small_records.h"
#include "types.h"
#include <PR/libaudio.h>
#include "Common/audio_callbacks.h"

struct ALPlayer_s14 {
    struct ALPlayer_s14 *next;
    void *clientData;
    ALVoiceHandler handler;
    s32 callTime;
    s32 samplesLeft;
};

typedef struct ALPlayer_s14 ALPlayer_s14;

struct AudioVoiceChannelFilterView {
    struct AudioVoiceChannelFilterView *source;
    void *handler;
    ALSetParam setParam;
};

typedef struct AudioVoiceChannelFilterView AudioVoiceChannelFilterView;

struct AudioAllocatedPhysicalVoiceView {
    ListLink node;
    struct ALVoice_s *vvoice;
    struct AudioVoiceChannelFilterView *channelKnob;
    char pad10[0xD8 - 0x10];
    s32 offset;
};

#endif
