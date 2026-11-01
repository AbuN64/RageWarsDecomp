#ifndef AUDIO_AUDIO_INITBITREVERSEORDER_H
#define AUDIO_AUDIO_INITBITREVERSEORDER_H
#include "COMMON/LLDIVRESULT.H"
#include "COMMON/AUDIO_LOADDECODEDSAMPLES.H"
extern u32 Audio_DecodeFrameOk(void);
extern void Audio_RotateComplexSamples(float *samples, float *rotationReal, float *rotationImaginary);
extern void Audio_ReorderTransformSamples(float *output, float *input);
extern s16 Audio_QuantizeSampleS16(f32 sample);
extern void Audio_TransformFft(f32 *data, FftTables *tables, s32 sign);
extern void Audio_InitBitReverseOrder(s32 *permutation, s32 elementCount);
#endif
