#ifndef ENGINE_AUDIO_SEQUENCER_H
#define ENGINE_AUDIO_SEQUENCER_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/ENTRYRECAT18V3.H"
#include "COMMON/S1.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/STATERECAT34.H"

struct MusicFadeState {
    char pad[0x18];
    s32 playbackState;
    s32 fadeMode;
    s32 currentMidiVolume;
    s32 baseVolume;
    s32 requestedSequence;
    f32 volume;
    f32 fadeDuration;
    f32 fadeStep;
};

struct MusicStopState {
    unsigned char padding_0[20];
    s32 sequencePlayer;
    unsigned char padding_18[16];
    s32 stopSentinel;
};

struct AudioParamsD844 {
    s32 count38, count1C;
    u8 kind;
    u8 pad9[3];
    struct AudioHeapD844 *context;
    s32 value10, value14, value18;
};

struct AudioStateD844 {
    struct AudioRootD844 *root;
    char pad4[0xC];
    void *allocation;
    void *player;
    s32 mode, flags, unused20, timer, index, unused2C;
    f32 first, second;
    s32 counter;
    f32 third, fourth;
};

extern void Sequencer_SetTrackVolume(void *track, f32 volume);

extern void Sequencer_UpdateTrackVolume(void *trackState);

extern void Sequencer_AttachTrackSequence(struct Track *track);
#endif
