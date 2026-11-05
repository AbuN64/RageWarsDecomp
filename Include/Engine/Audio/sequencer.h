#ifndef ENGINE_AUDIO_SEQUENCER_H
#define ENGINE_AUDIO_SEQUENCER_H
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/soundvoicepool.h"
#include "Common/heap_arena.h"
#include "Common/heap_arena_entry.h"
#include "Common/vector4f.h"
#include "Common/sharedplayer.h"
#include "Common/music_track_volume.h"

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
    s32 mode, flags, unusedBeforeTimer, timer, index, unusedAfterIndex;
    f32 first, second;
    s32 counter;
    f32 third, fourth;
};

extern void Sequencer_SetTrackVolume(void *track, f32 volume);

extern void Sequencer_UpdateTrackVolume(void *trackState);

extern void Sequencer_AttachTrackSequence(struct Track *track);
#endif
