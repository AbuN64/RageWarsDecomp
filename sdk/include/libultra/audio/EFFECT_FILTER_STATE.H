#ifndef LIBULTRA_AUDIO_EFFECT_FILTER_STATE_H
#define LIBULTRA_AUDIO_EFFECT_FILTER_STATE_H
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/small_records.h"
struct EffectFilterState {
    ALFilter_s14 filter;
    s16 *base;
    s16 *input;
    u32 length;
    struct ALDelayAudioSetEffectParameter *delay;
    u8 section_count;
    void *paramHdl;
};
#endif
