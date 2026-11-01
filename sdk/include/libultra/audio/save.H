#ifndef LIBULTRA_AUDIO_SAVE_H
#define LIBULTRA_AUDIO_SAVE_H
#include "TYPES.H"
#include "COMMON/ALDELAY28.H"
typedef struct ALSave_u1 {
    ALFilter_u1 filter;
    s32 dramout;
    s32 first;
} ALSave_u1;
#endif
