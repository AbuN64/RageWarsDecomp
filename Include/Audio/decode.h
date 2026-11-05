#ifndef AUDIO_DECODE_H
#define AUDIO_DECODE_H
#include "Common/lldivresult.h"
struct DecodeState;
extern u16 Audio_ReadPackedSamples(u16 *, u16, u16, s16, struct DecodeState *);
#endif
