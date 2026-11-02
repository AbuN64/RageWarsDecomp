#include "../../../../sdk/include/LIBC.H"
#include "COMMON/STREAM.H"
#include "COMMON/LONE/MOTION_TRACK_DECODE_RANGE_END.H"
#include "GAME/SOUNDINFO.H"
#include "TYPES.H"
#include "SYSTEM/POLYTRAK2_INTERPOLATEJOINTQUATERNION.H"
#include "RENDER/SETN64_GETPACKSECTION.H"

/* Resource blocks store a count and relative offsets; unused entries carry
 * the resource builder's DEADBEEF sentinel. */
typedef struct ResourceBlock { s32 count; s32 offset[1]; } ResourceBlock;

typedef struct ResourceHandle { ResourceBlock *block; s32 bytes; } ResourceHandle;

typedef struct CAnimCompInfo {
    s32 channels;
    s32 frames;
    s32 flags;
    f32 duration;
    s32 rotations;
    s32 translations;
    f32 frameCount;
    f32 frameStep;
} CAnimCompInfo;

extern s32 Ppdecom_UnpackResource(void **, s32);

extern s32 SetN64_GetSizedPackSection(s32, s32, s32 *);


extern void *Cache_AllocResourceBlock(s32, void *, s32);




extern void Cache_ReplaceResourceBlock(s32, void **, void *);

extern s32 Polytrak2_ExpandAnimationTracks(void *, void *, s32, s32, s32, s32);

extern const f32 g_expandedAnimationInitialFrameStep, g_expandedTranslationRangeStart, g_expandedTranslationRangeEnd;

extern const f32 g_expandedRotationRangeStart, g_expandedRotationRangeEnd;

extern f32 g_motionTrackFrameScale;

#include "COMMON/STREAM.H"
extern void Cache_ReleaseResource(void *cacheContext, void *resource);
extern s32 g_motionTrackDecodeRotation, g_motionTrackDecodeTranslation;

static inline void resource_begin(ResourceBlock *block, s32 count, s32 bytes) {
    s32 i = 1;
    s32 *entry = &block->offset[0];
    block->count = count;
    block->offset[0] = bytes;
    do {
        entry[1] = 0xDEADBEEF;
        i++;
        entry++;
    } while (i <= count);
}

static inline char *resource_reserve(ResourceBlock *block, s32 bytes) {
    s32 count = block->count;
    s32 i = 0;
    s32 *entry;
    s32 sentinel;
    if (count >= 0) {
        sentinel = 0xDEADBEEF;
        entry = &block->count;
loop:
        if (entry[1] != sentinel) {
            i++;
            entry++;
            if (count >= i) goto loop;
        }
    }
    i--;
    block->offset[i+1] = block->offset[i] + bytes;
    return (char *)block + block->offset[i];
}

static inline void resource_copy(ResourceBlock *block, void *from, s32 bytes) {
    char *destination = resource_reserve(block, bytes);
    if (from != 0) Libc_CopyBytes(destination, from, bytes);
}

static inline s32 motion_storage(s32 channels, s32 frames) {
    s32 data = channels * 16;
    s32 offsets = (channels * 4 + 15) & ~7;
    return data * frames + offsets;
}

/* Reads a packed cubic segment and computes its scaled polynomial coefficients. */



/* Rebuild the resource motion blocks, then replace the original handle. */
void Polytrak2_RebuildExpandedAnimationResource(s32 unused, ResourceHandle **handle) {
    s32 bytes0, bytes1, bytes2, bytes3, bytes4, bytes5, bytes6;
    s32 fetchedRotationBytes, fetchedTranslationBytes;
    ResourceBlock *source;
    void *section0, *section1, *section2, *section3, *section4;
    s32 rotationBytes, translationBytes;
    void *section6;
    ResourceBlock *motion;
    CAnimCompInfo *header;
    ResourceHandle *output;
    ResourceBlock *result;
    ResourceBlock *newMotion;
    CAnimCompInfo *newHeader;
    void *rotations, *translations, *newRotations, *newTranslations;
    s32 sourceBytes;
    s32 sourceFrames;
    s32 motionBytes;
    s32 success;
    f32 count;

    if (Ppdecom_UnpackResource((void **)handle, 1)) {
        source = (*handle)->block;
        sourceBytes = (*handle)->bytes;
        section0 = (void *)SetN64_GetSizedPackSection((s32)source, 0, &bytes0);
        section1 = (void *)SetN64_GetSizedPackSection((s32)source, 1, &bytes1);
        section2 = (void *)SetN64_GetSizedPackSection((s32)source, 2, &bytes2);
        section3 = (void *)SetN64_GetSizedPackSection((s32)source, 3, &bytes3);
        section4 = (void *)SetN64_GetSizedPackSection((s32)source, 4, &bytes4);
        motion = (ResourceBlock *)SetN64_GetSizedPackSection((s32)source, 5, &bytes5);
        header = (CAnimCompInfo *)SetN64_GetPackSection((s32 *)motion, 0);
        SetN64_GetSizedPackSection((s32)motion, 1, &fetchedRotationBytes);
        SetN64_GetSizedPackSection((s32)motion, 2, &fetchedTranslationBytes);
        section6 = (void *)SetN64_GetSizedPackSection((s32)source, 6, &bytes6);
        SetN64_GetPackSection(section3, 0);
        sourceFrames = header->frames;
        g_motionTrackSourceFrameCount = sourceFrames;
        g_motionTrackRotationFrameCount = sourceFrames;
        header->frameCount = (f32)sourceFrames;
        header->frameStep = g_expandedAnimationInitialFrameStep;
        if (sourceFrames >= 2) {
            count = (f32)(sourceFrames - 1);
            header->frameStep = count / count;
        }
        rotationBytes = motion_storage(header->translations, g_motionTrackRotationFrameCount);
        translationBytes = motion_storage(header->rotations, g_motionTrackRotationFrameCount);
        motionBytes = translationBytes + rotationBytes + 56;
        output = Cache_AllocResourceBlock(0, handle, sourceBytes - bytes5 + motionBytes + bytes6);
        if (output != 0) {
            result = output->block;
            resource_begin(result, 7, 40);
            resource_copy(result, section0, bytes0);
            resource_copy(result, section1, bytes1);
            resource_copy(result, section2, bytes2);
            resource_copy(result, section3, bytes3);
            resource_copy(result, section4, bytes4);
            newMotion = (ResourceBlock *)resource_reserve(result, motionBytes);
            resource_begin(newMotion, 3, 24);
            resource_copy(newMotion, header, 32);
            resource_reserve(newMotion, rotationBytes);
            resource_reserve(newMotion, translationBytes);
            resource_copy(result, section6, bytes6);
            newHeader = (CAnimCompInfo *)SetN64_GetPackSection((s32 *)motion, 0);
            rotations = SetN64_GetPackSection((s32 *)motion, 1);
            translations = SetN64_GetPackSection((s32 *)motion, 2);
            newRotations = SetN64_GetPackSection((s32 *)newMotion, 1);
            newTranslations = SetN64_GetPackSection((s32 *)newMotion, 2);
            g_motionTrackDecodeTranslation = 1;
            g_motionTrackDecodeRotation = 0;
            g_motionTrackDecodeRangeStart = g_expandedTranslationRangeStart;
            g_motionTrackDecodeRangeEnd = g_expandedTranslationRangeEnd;
            g_motionTrackFrameScale = newHeader->duration;
            if (Polytrak2_ExpandAnimationTracks(rotations, newRotations, newHeader->translations, 3, newHeader->channels, newHeader->flags) == 0) {
                success = 0;
            } else {
                g_motionTrackDecodeTranslation = 0;
                g_motionTrackDecodeRotation = 1;
                g_motionTrackDecodeRangeStart = g_expandedRotationRangeStart;
                g_motionTrackDecodeRangeEnd = g_expandedRotationRangeEnd;
                g_motionTrackFrameScale = newHeader->duration;
                success = Polytrak2_ExpandAnimationTracks(translations, newTranslations, newHeader->rotations, 4, newHeader->channels, newHeader->flags) != 0;
            }
            if (success == 0) {
                Cache_ReleaseResource(0, output);
                Cache_ReplaceResourceBlock(0, (void **)handle, 0);
            } else {
                goto replace_output;
            }
        } else {
replace_output:
            Cache_ReplaceResourceBlock(0, (void **)handle, output);
        }
    }
}

void Polytrak2_DecodeCubicSegment(Curve *compressedCurve)
{
  s32 bitCursor;
  int weightedFirstSample;
  f32 halfRange;
  f32 coefficientScale;
  f32 unusedCoefficientScratch;
  f32 cubicCoefficient;
  f32 linearCoefficient;
  f32 constantCoefficient;
  f32 quadraticCoefficient;
  f32 inverseSampleSpan;
  f32 quantizedValueScale;
  f64 sampleCountDouble;
  s32 secondSampleTimes32;
  s32 segmentBitOffset;
  s32 valueBitWidth;
  s32 secondSample;
  s32 firstSample;
  s32 thirdSample;
  u32 segmentSampleCount;
  s32 fourthSample;
  valueBitWidth = compressedCurve->valueBitWidth;
  segmentBitOffset = compressedCurve->segmentIndex * ((valueBitWidth * 4) + 6);
  bitCursor = compressedCurve->bitStreamAddress + segmentBitOffset;
  segmentSampleCount = Polytrak2_ReadBitsAndAdvance(&bitCursor, 6);
  firstSample = Polytrak2_ReadBitsAndAdvance(&bitCursor, valueBitWidth);
  secondSample = Polytrak2_ReadBitsAndAdvance(&bitCursor, valueBitWidth);
  thirdSample = Polytrak2_ReadBitsAndAdvance(&bitCursor, valueBitWidth);
  fourthSample = Polytrak2_ReadBitsAndAdvance(&bitCursor, valueBitWidth);
  constantCoefficient = (f32) firstSample;
  weightedFirstSample=firstSample*21;
  secondSampleTimes32 = secondSample << 5;
  linearCoefficient = (f32) (((secondSampleTimes32 - weightedFirstSample) - (thirdSample * 12)) + fourthSample);
  linearCoefficient *= 0.33333334f;
  quadraticCoefficient = (f32) ((((firstSample * 14) - secondSampleTimes32) + (thirdSample * 20)) - (fourthSample * 2));
  weightedFirstSample = firstSample * 24;
  cubicCoefficient = (f32) ((((secondSample << 6) - weightedFirstSample) - (thirdSample * 48)) + (fourthSample * 8));
  cubicCoefficient *= 0.33333334f;
  if (valueBitWidth != 0)
  {
    quantizedValueScale = compressedCurve->valueRange / ((f32) ((1 << valueBitWidth) - 1));
  }
  else
  {
    halfRange = compressedCurve->valueRange * 0.5f;
    compressedCurve->valueRange = 0.0f;
    quantizedValueScale = compressedCurve->valueRange;
    compressedCurve->baseValue = (f32) (compressedCurve->baseValue + halfRange);
  }
  constantCoefficient *= quantizedValueScale;
  if (segmentSampleCount >= 2U)
  {
    sampleCountDouble = (f64) segmentSampleCount;
    inverseSampleSpan = 1.0f / (((f32) sampleCountDouble) - 1.0f);
  }
  else
  {
    inverseSampleSpan = 1.0f;
  }
  coefficientScale = inverseSampleSpan * quantizedValueScale;
  linearCoefficient *= coefficientScale;
  coefficientScale *= inverseSampleSpan;
  quadraticCoefficient *= coefficientScale;
  coefficientScale *= inverseSampleSpan;
  constantCoefficient += compressedCurve->baseValue;
  cubicCoefficient *= coefficientScale;
  compressedCurve->segmentSampleCount = segmentSampleCount;
  compressedCurve->linearCoefficient = linearCoefficient;
  compressedCurve->constantCoefficient = constantCoefficient;
  compressedCurve->quadraticCoefficient = quadraticCoefficient;
  compressedCurve->cubicCoefficient = cubicCoefficient;
}
