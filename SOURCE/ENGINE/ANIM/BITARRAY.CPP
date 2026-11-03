#include "include_asm.h"
#include "COMMON/LOCALDECODERANGE.H"
#include "COMMON/LONE/MOTION_TRACK_DECODE_RANGE_END.H"
#include "SYSTEM/POLYTRAK2_DECODESCALARSAMPLES_DATA.H"
#include "GAME/SOUNDINFO.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "TYPES.H"
#include "SYSTEM/BITARRAY_SAMPLE_EVALUATION.H"
#include "SYSTEM/POLYTRAK2_INTERPOLATEJOINTQUATERNION.H"
#include "RENDER/SETN64_GETPACKSECTION.H"
#include "ENGINE/ANIM/BITARRAY.H"
#include "POLYTRAK2/POLYTRAK2_EVALUATEANIMATIONCURVE.H"

/* BITARRAY.CPP */
/* ROM-grounded data: src/g_motionTranslationQuantizationScale_StorageWords.c */
const float g_motionTranslationQuantizationScale_StorageWords[1] = {
    -2e+03f,
};

/* Reads a sampled track from a stream: parses its header through Polytrak2_InitializePackedCurve, evaluates the track at each whole frame into the first float of consecutive 16-byte output records, and advances the stream cursor past the track's key data. */



extern f32 Polytrak2_SampleAnimationCurve(TrackBitarrayExpandCurveSamples *track, f32 time, s32 unusedFirst, s32 unusedSecond);

#if defined(VERSION_EU)
extern s32 Polytrak2_DecodeTrackSectionsEu(void *, void *, s32, s32, s32, s32);
#elif defined(VERSION_EU_X)
extern s32 Polytrak2_DecodeTrackSectionsEuX(void *, void *, s32, s32, s32, s32);
#elif defined(VERSION_US)
extern s32 Polytrak2_DecodeAndSmoothSampleTracks(void *, void *, s32, s32, s32, s32);
#elif defined(VERSION_US_REV1)
extern s32 Polytrak2_ExpandAnimationTracks(void *, void *, s32, s32, s32, s32);
#else
extern s32 Polytrak2_DecodeTrackSections(void *, void *, s32, s32, s32, s32);
#endif

extern s32 g_motionTrackDecodeTranslation;

extern s32 g_motionTrackDecodeRotation;

/* Seeks the containing frame in a variable-length stream and reloads it when the frame changes. */

extern void Polytrak2_DecodeCubicSegment(Curve *compressedCurve);

extern int Polytrak2_ReadBitsAtAddress(s32, unsigned int);

extern f32 g_motionQuantizationRangeAndUnit[2];

void Bitarray_ExpandCurveSamples(char **stream, f32 *out, s32 frames)
{
    TrackBitarrayExpandCurveSamples track;
    char *cursor;
    s32 i;

    cursor = *stream;
    Polytrak2_InitializePackedCurve(&track, &cursor);
    for (i = 0; i < frames; i++) {
        *out = Polytrak2_SampleAnimationCurve(&track, i, 0, 0);
        out += 4;
    }
    cursor += track.stride * (track.keys * 4 + 6);
    *stream = cursor;
}

void Bitarray_ReadStridedFloatSamples(s32 bitCursor, void *sampleRecords, s32 sampleCount)
{
  int firstSampleIndex;
  s32 rawSampleBits;
  s32 sampleIndex;
  u8 *sampleOutput;
  firstSampleIndex = 0;
  sampleIndex = firstSampleIndex;
  if (sampleCount > firstSampleIndex)
  {
    sampleOutput = (u8 *) sampleRecords;
    do
    {
      sampleIndex += 1;
      rawSampleBits = Polytrak2_ReadBitsAndAdvance(bitCursor, 32);
      *((f32 *) sampleOutput) = *((f32 *) (&rawSampleBits));
      sampleOutput += sizeof(CQuatern);
    }
    while (sampleIndex < sampleCount);
  }
}

s32 Bitarray_ExpandMotionPack(void *sourceMotionPack, void *destinationMotionPack) {
    MotionPackHeader *first;
    void *a;
    void *b;
    void *c;
    void *d;
    s32 one;

    first = SetN64_GetPackSection(sourceMotionPack, 0);
    a = SetN64_GetPackSection(sourceMotionPack, 1);
    b = SetN64_GetPackSection(sourceMotionPack, 2);
    c = SetN64_GetPackSection(destinationMotionPack, 1);
    d = SetN64_GetPackSection(destinationMotionPack, 2);

    one = 1;
    g_motionTrackDecodeTranslation = one;
    g_motionTrackDecodeRotation = 0;
    g_motionTrackDecodeRangeStart = g_motionTranslationQuantizationScale;
    g_motionTrackDecodeRangeEnd = (2000.0f);
    g_motionTrackFrameScale = first->f0C;
    if (
#if defined(VERSION_EU)
Polytrak2_DecodeTrackSectionsEu
#elif defined(VERSION_EU_X)
Polytrak2_DecodeTrackSectionsEuX
#elif defined(VERSION_US)
Polytrak2_DecodeAndSmoothSampleTracks
#elif defined(VERSION_US_REV1)
Polytrak2_ExpandAnimationTracks
#else
Polytrak2_DecodeTrackSections
#endif
(a, c, first->n14, 3, first->x, first->z) == 0) {
        return 0;
    }
    g_motionTrackDecodeTranslation = 0;
    g_motionTrackDecodeRotation = one;
    g_motionTrackDecodeRangeStart = g_motionRotationQuantizationScale;
    g_motionTrackDecodeRangeEnd = g_motionRotationDecodeLimit;
    g_motionTrackFrameScale = first->f0C;
    return
#if defined(VERSION_EU)
Polytrak2_DecodeTrackSectionsEu
#elif defined(VERSION_EU_X)
Polytrak2_DecodeTrackSectionsEuX
#elif defined(VERSION_US)
Polytrak2_DecodeAndSmoothSampleTracks
#elif defined(VERSION_US_REV1)
Polytrak2_ExpandAnimationTracks
#else
Polytrak2_DecodeTrackSections
#endif
(b, d, first->n10, 4, first->x, first->z) != 0;
}

/** Return the word at offset twelve. */
int Bitarray_GetCurveBitAddress(char *object) {
    Stream *stream = (void *)object;
    return stream->segmentBitAddress;
}

void Bitarray_SeekCurveSegment(Stream *compressedCurve, u32 sampleIndex) {
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
            segmentBitCursor += segmentBitStride;
            if(sampleIndex>=segmentStartSample && sampleIndex<segmentEndSample) {
                if(segmentIndex!=compressedCurve->segmentIndex) {
                    compressedCurve->segmentStartSample=segmentStartSample;compressedCurve->segmentIndex=segmentIndex;Polytrak2_DecodeCubicSegment(compressedCurve);
                }
                break;
            }
            segmentIndex++;
            segmentStartSample=segmentEndSample;
            segmentSampleCounts[segmentIndex]=Polytrak2_ReadBitsAtAddress(segmentBitCursor,6);
            segmentEndSample+=segmentSampleCounts[segmentIndex];
        }
    }
}

s32 Bitarray_GetQuantizationBitCount(f32 quantizationError)
{
  unsigned long long unitConstantIndex;
  f32 requiredLevels;
  s32 bitCount;
  bitCount = 0;
  unitConstantIndex = 1;
  requiredLevels = quantizationError;
  requiredLevels = (g_motionQuantizationRangeAndUnit[unitConstantIndex] / (2.0f * requiredLevels)) + g_motionQuantizationRangeAndUnit[unitConstantIndex];
  if (g_motionQuantizationRangeAndUnit[0] <= quantizationError)
  {
    return 0;
  }
  if (g_motionQuantizationRangeAndUnit[unitConstantIndex] < requiredLevels)
  {
    do
    {
      bitCount += 1;
    }
    while (((f32) (1 << bitCount)) < requiredLevels);
  }
  return bitCount;
}

f32 Bitarray_EvaluateCubicPolynomial(s32 constantBits, s32 linearBits, s32 quadraticBits, s32 cubicBits, s32 unused4, f32 sampleTime) {
    f32 bits = *(f32 *)&constantBits;
    f32 v1 = *(f32 *)&linearBits;
    f32 v2 = *(f32 *)&quadraticBits;
    f32 v3 = *(f32 *)&cubicBits;
    return bits + (v1 * sampleTime) + (v2 * sampleTime * sampleTime) + (v3 * sampleTime * sampleTime * sampleTime);
}

/** Return the low five bits of the supplied value. */
unsigned int Bitarray_GetWordBitOffset(unsigned int value) {
    return value & 0x1F;
}

u32 Bitarray_GetRequiredBitCount(s32 value) {
    u32 setBitCount;
    u32 highestSetBit;
    u32 bitIndex;

    setBitCount = 0;
    highestSetBit = 0;
    bitIndex = 0;
    do {
        if (value & (u32)(1 << bitIndex)) {
            setBitCount += 1;
            highestSetBit = bitIndex;
        }
        bitIndex += 1;
    } while (bitIndex < 32U);
    if (setBitCount >= 2U) {
        return highestSetBit + 1;
    }
    return highestSetBit;
}

/* ROM-grounded data: rodata/unresolved/800C9290 */
const float g_motionRotationQuantizationScale_StorageWords[2] = {
    -1.0f, 1.0f,
};

/* ROM-grounded data: src/g_motionQuantizationRangeAndUnit_StorageWords.c */
const float g_motionQuantizationRangeAndUnit_StorageWords[2] = {
    0.5f, 1.0f,
};
