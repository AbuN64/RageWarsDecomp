#ifndef LIBULTRA_AUDIO_ENV_H
#define LIBULTRA_AUDIO_ENV_H
#include "TYPES.H"
extern s16 _getRate(f64 vol, f64 tgt, s32 count, u16 *ratel);
extern f64 _ldexpf(f64 value, s32 shift);
extern f32 _getVol(f32 initialVolume, s32 sampleCount, s32 rateInteger, s32 rateFraction);
#endif
