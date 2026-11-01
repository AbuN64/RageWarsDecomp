#ifndef RESMGR_STREAM_H
#define RESMGR_STREAM_H
#include "COMMON/CALLBACK.H"

extern void Stream_SetFloatPairToNegativeOne(float *firstValue, float *secondValue);

extern void StreamBufferFree(struct StreamBuffer *streamBuffer);
#endif
