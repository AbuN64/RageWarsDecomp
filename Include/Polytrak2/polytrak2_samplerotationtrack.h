#ifndef POLYTRAK2_POLYTRAK2_SAMPLEROTATIONTRACK_H
#define POLYTRAK2_POLYTRAK2_SAMPLEROTATIONTRACK_H
#include "types.h"
struct AnimRef; struct CVector3_t;
void Polytrak2_SampleVectorTrack(struct AnimRef *anim, s32 index, f32 time, struct CVector3_t *out);
#endif
