#ifndef COMMON_STREAM_H
#define COMMON_STREAM_H
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"

struct ScalarSampleOutput;
typedef struct ScalarSampleOutput ScalarSampleOutput;

struct ScalarSampleOutput;

extern void Polytrak2_DecodeScalarSamples(u32 *stream, ScalarSampleOutput *out, s32 count);



struct Stream;
typedef struct Stream Stream;

struct PackedCurveSegment;
typedef struct PackedCurveSegment PackedCurveSegment;



extern float g_motionQuantizedRateFallbackScale;

extern float g_packedFloatQuantizationRoundBias;




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


extern double g_sampleTrackUnsignedConversionBias;

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
