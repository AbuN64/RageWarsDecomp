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
extern struct ResourceKeyView *g_dialogDefaultSample;
#endif
