#ifndef LIBULTRA_AUDIO_REVERB_INTERNAL_H
#define LIBULTRA_AUDIO_REVERB_INTERNAL_H
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/audio_effect_chain.h"
#include <PR/abi.h>
extern void *_filterBuffer(void *audioLowPassFilter, s32 dmemBuffer, s32 sampleCount, void *awords);
extern f32 _getDelta(ALDelay28 *d, s32 count);
extern Acmd *_loadBuffer(ALFx *, s16 *, s32, s32, Acmd *);
#endif
