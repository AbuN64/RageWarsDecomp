#ifndef COMMON_SEQUENCE_TIMING_H
#define COMMON_SEQUENCE_TIMING_H
#include "types.h"


struct SequenceTicksPerQuarterView;
typedef struct SequenceTicksPerQuarterView SequenceTicksPerQuarterView;


extern double g_sequenceTicksToSecondsUnsignedBias;











extern float g_sequenceQuarterNoteUnit;











extern s16 read16(ALSeq *sequenceObject);
extern s32 read32(ALSeq *sequenceObject);

#endif
