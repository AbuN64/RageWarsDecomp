#ifndef LIBULTRA_AUDIO_SAVE_H
#define LIBULTRA_AUDIO_SAVE_H
#include "types.h"
#include "Common/audio_effect_chain.h"
typedef struct ALSave_u1 {
    ALFilter_u1 filter;
    s32 dramout;
    s32 first;
} ALSave_u1;
#endif
