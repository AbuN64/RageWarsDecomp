#include "include_asm.h"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/STREAM.H"
#include "GAME/SOUNDINFO.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "SYSTEM/POLYTRAK2_INTERPOLATEJOINTQUATERNION.H"

/* Reads one envelope segment from a bitstream, either as raw floats or as scaled table values. */





extern s32 g_motionTrackDecodeRangeEnd;


extern void Polytrak2_DecodeCubicSegment(Curve *compressedCurve);

extern int Polytrak2_ReadBitsAtAddress(s32, unsigned int);

static inline void seek(Stream *compressedCurve, u32 sampleIndex) {
    u32 segmentSampleCounts[64];
    s32 segmentSampleCount;
    s32 segmentBitOffset;
    s32 firstSegmentBitAddress;
    s32 segmentBitStride;
    s32 segmentBitCursor;
    s32 segmentIndex;
    u32 *sampleCountCursor;
    u32 sampleCount;
    u32 activeSegmentStart;
    u32 segmentEndSample;
    u32 segmentStartSample;

    segmentBitStride = (compressedCurve->coefficientBitWidth * 4) + 6;
    activeSegmentStart = compressedCurve->segmentStartSample;
    if (sampleIndex < activeSegmentStart || sampleIndex >= activeSegmentStart + compressedCurve->segmentSampleCount) {
        segmentIndex = compressedCurve->segmentIndex;
        segmentStartSample = activeSegmentStart;
        segmentEndSample = segmentStartSample + compressedCurve->segmentSampleCount;
        segmentBitCursor = compressedCurve->segmentBitAddress;
        firstSegmentBitAddress=segmentBitCursor;
        segmentBitCursor += segmentIndex * segmentBitStride;
        if(sampleIndex < activeSegmentStart) {
            segmentBitCursor=firstSegmentBitAddress;segmentIndex=0;segmentStartSample=0;
            segmentEndSample=Polytrak2_ReadBitsAtAddress(segmentBitCursor,6);
        }
        for (;;) {
            if(sampleIndex>=segmentStartSample && sampleIndex<segmentEndSample) {
                if(segmentIndex!=compressedCurve->segmentIndex) {
                    compressedCurve->segmentStartSample=segmentStartSample;compressedCurve->segmentIndex=segmentIndex;Polytrak2_DecodeCubicSegment(compressedCurve);
                }
                break;
            }
            segmentBitCursor += segmentBitStride;
            segmentIndex++;
            segmentStartSample=segmentEndSample;
            segmentSampleCounts[segmentIndex]=Polytrak2_ReadBitsAtAddress(segmentBitCursor,6);
            segmentEndSample+=segmentSampleCounts[segmentIndex];
        }
    }
}

static inline float evaluate(Poly p,float t) { return p.a + p.b*t + p.c*t*t + p.d*t*t*t; }

void Polytrak2_InitializePackedCurve(PackedCurveSegment *curve, u32 *stream) {
    u32 bits;
    u32 first;
    u32 second;
    f32 lo;
    f32 hi;

    bits = *stream;
    curve->segmentCount = Polytrak2_ReadBitsAndAdvance(&bits, 6);
    if (g_motionTrackDecodeTranslation != 0) {
        first = Polytrak2_ReadBitsAndAdvance(&bits, 32);
        second = Polytrak2_ReadBitsAndAdvance(&bits, 32);
        lo = *(f32 *)&first;
        hi = *(f32 *)&second;
    } else {
        first = Polytrak2_ReadBitsAndAdvance(&bits, 6);
        second = Polytrak2_ReadBitsAndAdvance(&bits, 6);
        lo = Polytrak2_UnpackUnitValue((f32)first, 6);
        hi = Polytrak2_UnpackUnitValue((f32)second, 6);
        lo = ((f32 (*)(f32, f32, s32))Polytrak2_ScaleToRange)(lo, g_motionTrackDecodeRangeStart, g_motionTrackDecodeRangeEnd);
        hi = ((f32 (*)(f32, f32, s32))Polytrak2_ScaleToRange)(hi, g_motionTrackDecodeRangeStart, g_motionTrackDecodeRangeEnd);
    }
    curve->baseValue = lo;
    curve->valueRange = hi - lo;
    do {
        curve->valueBitWidth = Polytrak2_ReadBitsAndAdvance(&bits, 6);
        curve->segmentIndex = 0;
        curve->segmentStartSample = 0;
        curve->bitStreamAddress = bits;
        Polytrak2_DecodeCubicSegment(curve);
    } while (0);
    *stream = bits;
}

float Polytrak2_EvaluateAnimationCurve(Stream *stream, float time) {
    seek(stream, (u32)time);
    return evaluate(*(Poly *)&stream->coeff[0], time - stream->segmentStartSample);
}

#include "ENGINE/ANIM/POLYTRAK2.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
inline static void write_bits(u32 value, u32 bitAddress, u32 width)
{
  u32 address;
  s32 shift;
  s32 remaining;
  u32 highMask;
  u32 offset;
  u32 high;
  u32 low;
  u32 lowMask;
  PackedBitWords *words;
  highMask = (1 << width) - 1;
  lowMask = highMask;
  shift = bitAddress & 0x1F;
  offset = shift;
  value &= highMask;
  if (shift == 0)
  {
    low = value;
    highMask = 0;
    high = 0;
  }
  else
  {
    lowMask = highMask << offset;
    remaining = 32 - offset;
    highMask >>= remaining;
    low = value << offset;
    high = value >> remaining;
  }
  address = (bitAddress & 0xF0000000) | (((u32) (bitAddress & 0x0FFFFFE0)) >> 3);
  words = (PackedBitWords *) address;
  words->low = (words->low & (~lowMask)) | low;
  words->high = (words->high & (~highMask)) | high;
}
static inline void writeQuantized(u32 bitAddress, Polytrak2QuantizationRange range, f32 value) {
    f32 scaled;
    s32 integral;
    s32 quantized;

    scaled = (((value - range.start) / range.delta) * (f32) ((1 << range.value) - 1)) + g_packedFloatQuantizationRoundBias;
    if (scaled >= 0.0f) {
        quantized = (s32) scaled;
    } else {
        integral = (s32) scaled;
        quantized = 1;
        if ((f32) integral == scaled) {
            quantized = 0;
        }
        quantized = integral - quantized;
    }
    write_bits(quantized, bitAddress, range.value);
}

void Polytrak2_WriteQuantizedFloatAndAdvance(u32 *stream, Polytrak2QuantizationRange range, f32 value) {
    writeQuantized(*stream, range, value);
    *stream += range.value;
}
