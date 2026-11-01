#ifndef AUDIO_LIST_AND_CHANNEL_VIEWS_H
#define AUDIO_LIST_AND_CHANNEL_VIEWS_H
#include "TYPES.H"
#include "COMMON/LISTNODE.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
struct Lists {
    char pad0[4];
    AudioPendingFlagsNode first;
    char padB4[0x24];
    AudioPendingFlagsNode second;
};
struct AudioSpatialVoiceManagerView {
    struct AudioScene *scene;
    AudioPendingSoundLinks active;
    char padC[0xCC];
    AudioPendingSoundLinks free;
};
struct AudioVoiceListLinks {
    void *prev;
    void *next;
};
struct AudioSoundCell {
    s32 index;
    s32 pad4;
    s32 texture;
    s32 sequence;
    s32 frame;
    char pad14[0x44 - 0x14];
    char data[0xCC - 0x44];
};
struct AudioPriorityQueueManagerView {
    s32 *scene;
    LinkAudioWorldQueuePrioritizedSound active;
    char padC[0xCC];
    LinkAudioWorldQueuePrioritizedSound free;
};
struct LinkPair {
    void **first;
    void **second;
};
struct Bytes12 {
    char bytes[12];
};
struct ChannelPitchMotionView {
    char pad0[0x10];
    Motion motion;
    Angles angles;
    char pad68[4];
    f32 pitch;
    f32 pitchStep;
    char pad74[0xB0 - 0x74];
    s32 presets;
};
#endif
