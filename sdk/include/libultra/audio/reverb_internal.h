#ifndef LIBULTRA_AUDIO_REVERB_INTERNAL_H
#define LIBULTRA_AUDIO_REVERB_INTERNAL_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/ALDELAY28.H"
#include <PR/abi.h>
extern void *_filterBuffer(void *audioLowPassFilter, s32 dmemBuffer, s32 sampleCount, void *awords);
extern f32 _getDelta(ALDelay28 *d, s32 count);
extern Acmd *_loadBuffer(ALFx *, s16 *, s32, s32, Acmd *);
#endif
