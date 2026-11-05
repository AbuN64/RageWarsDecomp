#ifndef SYSTEM_BITARRAY_SAMPLE_EVALUATION_H
#define SYSTEM_BITARRAY_SAMPLE_EVALUATION_H
#include "Common/localdecoderange.h"
extern f32 Bitarray_EvaluateCubicPolynomial(s32 constantBits, s32 linearBits, s32 quadraticBits, s32 cubicBits, s32 polynomialDegree, f32 sampleTime);
extern int Bitarray_GetCurveBitAddress(char *object);
extern void Bitarray_ReadStridedFloatSamples(s32 bitCursor, CQuatern *sampleRecords, s32 sampleCount);
#endif
