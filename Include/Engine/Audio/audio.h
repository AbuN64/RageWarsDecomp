#ifndef ENGINE_AUDIO_AUDIO_H
#define ENGINE_AUDIO_AUDIO_H
#include "types.h"

struct FftTables {
    f32 *sines;
    f32 *cosines;
    s32 *order;
    s32 size;
};
typedef struct FftTables FftTables;

struct ResourceKeyView;
/* The dialog players' default sample: the ALSound alSndpAllocate takes (envelope, key map, wave table, pan, volume,
   flags), whose envelope word Audio_UpdateDialogPlayer reads as the resource key it rewrites, then the 8 bytes each
   version holds after it up to the next object. */
typedef struct DialogDefaultSample {
    struct ResourceKeyView *key;
    void *keyMap;
    void *wavetable;
    u8 samplePan;
    u8 sampleVolume;
    u8 flags;
    u8 pad;
    u8 next[8];
} DialogDefaultSample;
extern DialogDefaultSample g_dialogDefaultSample;
#endif
