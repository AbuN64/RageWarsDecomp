#include "include_asm.h"
#include "Common/localdecoderange.h"
#include "Common/Lone/motion_track_decode_range_end.h"
#include "System/polytrak2_decodescalarsamples_data.h"
#include "Game/soundinfo.h"
#include "Common/vector4f.h"
#include "types.h"
#include "System/bitarray_sample_evaluation.h"
#include "System/polytrak2_interpolatejointquaternion.h"
#include "Render/setn64_getpacksection.h"
#include "Engine/Anim/BitArray.h"
#include "Polytrak2/polytrak2_evaluateanimationcurve.h"
#include "Engine/Anim/compressed_motion.h"
#include "Common/runtime_declarations.h"

/* BITARRAY.CPP */

const float g_motionTranslationQuantizationScale[1] = {
    -2e+03f,
};

/* Reads a sampled track from a stream: parses its header through Polytrak2_InitializePackedCurve, evaluates the track at each whole frame into the first float of consecutive 16-byte output records, and advances the stream cursor past the track's key data. */



/* Seeks the containing frame in a variable-length stream and reloads it when the frame changes. */

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

/* Reads sampleCount 32-bit floats from the bit stream into the first float of each CQuatern-sized record. */
void Bitarray_ReadStridedFloatSamples(s32 bitCursor, CQuatern *sampleRecords, s32 sampleCount) {
    s32 rawSampleBits;
    s32 sampleIndex;

    for (sampleIndex = 0; sampleIndex < sampleCount; sampleIndex++) {
        rawSampleBits = Polytrak2_ReadBitsAndAdvance(bitCursor, 32);
        *(f32 *)&sampleRecords[sampleIndex] = *(f32 *)&rawSampleBits;
    }
}

s32 Bitarray_ExpandMotionPack(void *sourceMotionPack, void *destinationMotionPack) {
    MotionPackHeader *sourceHeader;
    void *sourceTranslationSection;
    void *sourceRotationSection;
    void *destinationTranslationSection;
    void *destinationRotationSection;
    s32 decodeEnabled;

    sourceHeader = SetN64_GetPackSection(sourceMotionPack, 0);
    sourceTranslationSection = SetN64_GetPackSection(sourceMotionPack, 1);
    sourceRotationSection = SetN64_GetPackSection(sourceMotionPack, 2);
    destinationTranslationSection = SetN64_GetPackSection(destinationMotionPack, 1);
    destinationRotationSection = SetN64_GetPackSection(destinationMotionPack, 2);

    decodeEnabled = 1;
    g_motionTrackDecodeTranslation = decodeEnabled;
    g_motionTrackDecodeRotation = 0;
    g_motionTrackDecodeRangeStart = g_motionTranslationQuantizationScale[0];
    g_motionTrackDecodeRangeEnd = (2000.0f);
    g_motionTrackFrameScale = sourceHeader->f0C;
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
(sourceTranslationSection, destinationTranslationSection, sourceHeader->n14, 3, sourceHeader->x, sourceHeader->z) == 0) {
        return 0;
    }
    g_motionTrackDecodeTranslation = 0;
    g_motionTrackDecodeRotation = decodeEnabled;
    g_motionTrackDecodeRangeStart = g_motionRotationQuantizationScale[0];
    g_motionTrackDecodeRangeEnd = g_motionRotationDecodeLimit;
    g_motionTrackFrameScale = sourceHeader->f0C;
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
(sourceRotationSection, destinationRotationSection, sourceHeader->n10, 4, sourceHeader->x, sourceHeader->z) != 0;
}

/** Returns the bit address of the stream segment. */
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

f32 Bitarray_EvaluateCubicPolynomial(s32 constantBits, s32 linearBits, s32 quadraticBits, s32 cubicBits, s32 polynomialDegree, f32 sampleTime) {
    f32 bits = *(f32 *)&constantBits;
    f32 linearCoefficient = *(f32 *)&linearBits;
    f32 quadraticCoefficient = *(f32 *)&quadraticBits;
    f32 cubicCoefficient = *(f32 *)&cubicBits;
    return bits + (linearCoefficient * sampleTime) + (quadraticCoefficient * sampleTime * sampleTime) + (cubicCoefficient * sampleTime * sampleTime * sampleTime);
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

const float g_motionRotationQuantizationScale[2] = {
    -1.0f, 1.0f,
};

const float g_motionQuantizationRangeAndUnit[2] = {
    0.5f, 1.0f,
};
