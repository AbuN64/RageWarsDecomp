#ifndef COMMON_OBJRECAT18V1_H
#define COMMON_OBJRECAT18V1_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"


struct SequenceTicksPerQuarterView;
typedef struct SequenceTicksPerQuarterView SequenceTicksPerQuarterView;


extern double g_sequenceTicksToSecondsUnsignedBias;











extern float g_sequenceQuarterNoteUnit;











extern s16 read16(ALSeq *sequenceObject);
extern s32 read32(ALSeq *sequenceObject);

#endif
