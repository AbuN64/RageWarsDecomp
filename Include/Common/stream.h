#ifndef COMMON_STREAM_H
#define COMMON_STREAM_H
#include "Engine/folded_constants.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/resident_event_handler.h"

struct ScalarSampleOutput;
struct ScalarSampleOutput;
typedef struct ScalarSampleOutput ScalarSampleOutput;

struct ScalarSampleOutput;

extern void Polytrak2_DecodeScalarSamples(u32 *stream, struct ScalarSampleOutput *out, s32 count);



struct Stream;
typedef struct Stream Stream;

struct PackedCurveSegment;
typedef struct PackedCurveSegment PackedCurveSegment;



extern float g_motionQuantizedRateFallbackScale;






struct PackedCurveSegment;

struct Stream;
struct Stream {
    s32 coefficientBitWidth;
    char pad4[8];
    s32 segmentBitAddress;
    float coeff[4];
    u32 segmentSampleCount;
    u32 segmentStartSample;
    s32 segmentIndex;
};

struct ScalarSampleDecodeState;

struct Curve;
typedef struct Curve Curve;




extern float g_motionQuantizedRatePeriodThreshold;

extern double g_trackSectionUnsignedConversionBias;



struct ScalarSampleDecodeState;
typedef struct ScalarSampleDecodeState ScalarSampleDecodeState;

struct Poly;

struct Poly;
typedef struct Poly Poly;

struct Curve;



/* Frame counts of the loaded motion, read by the stream decoder. */
extern s32 g_motionTrackSourceFrameCount;
extern s32 g_motionTrackRotationFrameCount;
#endif
