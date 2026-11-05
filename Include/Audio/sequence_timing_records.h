#ifndef AUDIO_SEQUENCE_TIMING_RECORDS_H
#define AUDIO_SEQUENCE_TIMING_RECORDS_H
#include "types.h"

struct SequenceTicksPerQuarterView {
    char pad18[0x18];
    s16 ticksPerQuarter;
};

#endif
