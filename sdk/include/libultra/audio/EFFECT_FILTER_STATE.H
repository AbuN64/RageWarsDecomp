#ifndef LIBULTRA_AUDIO_EFFECT_FILTER_STATE_H
#define LIBULTRA_AUDIO_EFFECT_FILTER_STATE_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
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
