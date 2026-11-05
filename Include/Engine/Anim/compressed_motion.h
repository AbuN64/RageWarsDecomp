#ifndef ENGINE_ANIM_COMPRESSED_MOTION_H
#define ENGINE_ANIM_COMPRESSED_MOTION_H
#include "Engine/folded_constants.h"











#include "types.h"
typedef struct AnimationSampleTable {
    s32 count;
    s32 offsets[1];
} AnimationSampleTable;
#include "Common/small_records.h"
#include "Common/Lone/motion_track_decode_range_end.h"
#include "types.h"
#include "Common/stream.h"
#include "Common/localdecoderange.h"
#include "System/polytrak2_decodescalarsamples_data.h"



struct BoneRotationIndexPair {
    s16 translation;
    short rotationIndex;
};
typedef struct BoneRotationIndexPair BoneRotationIndexPair;

struct BoneRotationTrackView {
    char * boneIndexPairs;
    char pad0[0x4 - 0x0 - sizeof(char*)];
    char * initialOrientations;
    void * translationFrames;
    void * rotationFrames;
    char padC[0x10 - 0xC - sizeof(void*)];
    s32 rotationFirst;
    char pad10[0x14 - 0x10 - sizeof(s32)];
    s32 rotationNext;
    s32 translationFirst;
    s32 translationNext;
    f32 frameBlend;
};
typedef struct BoneRotationTrackView BoneRotationTrackView;


struct Curve;
struct LocalDecodeRange;
struct Stream;
struct TrackBitarrayExpandCurveSamples;
/* Consecutive 32-bit storage words used by the scalar bit packer. */
typedef struct { u32 low; u32 high; } PackedBitPair;

extern f32 Polytrak2_ChooseQuantizedTrackRate(f32 amount, f32 period);

extern f32 Polytrak2_ReadQuantizedStreamValue(struct LocalDecodeRange *valueStream);

extern unsigned int Polytrak2_ReadCursorBits(unsigned int *bitCursor, unsigned int bitCount);

extern void Polytrak2_SeekArrayElement(unsigned int *record, int index);

extern void Polytrak2_SkipCursorBits(int *bitCursor, int bitCount);
extern f32 Polytrak2_SampleAnimationCurve(struct TrackBitarrayExpandCurveSamples *track, f32 time, s32 unusedFirst, s32 unusedSecond);
#if defined(VERSION_EU)
extern s32 Polytrak2_DecodeTrackSectionsEu(s32 source, AnimationSampleTable *buffer, s32 tracks, s32 channels, s32 radius, s32 encoding);
#endif
#if defined(VERSION_EU_X)
extern s32 Polytrak2_DecodeTrackSectionsEuX(s32 source, AnimationSampleTable *buffer, s32 tracks, s32 channels, s32 radius, s32 encoding);
#endif
#if defined(VERSION_US)
extern s32 Polytrak2_DecodeAndSmoothSampleTracks(s32 source, AnimationSampleTable *buffer, s32 tracks, s32 channels, s32 radius, s32 encoding);
#endif
#if defined(VERSION_US_REV1)
extern s32 Polytrak2_ExpandAnimationTracks(s32 source, AnimationSampleTable *buffer, s32 tracks, s32 channels, s32 radius, s32 encoding);
#endif
#if defined(VERSION_DE)
extern s32 Polytrak2_DecodeTrackSections(s32 source, AnimationSampleTable *buffer, s32 tracks, s32 channels, s32 radius, s32 encoding);
#endif
extern void Polytrak2_DecodeCubicSegment(struct Curve *compressedCurve);
extern int Polytrak2_ReadBitsAtAddress(int bitAddress, unsigned int width);
extern float Polytrak2_EvaluateAnimationCurve(struct Stream *stream, float time);
extern f32 Polytrak2_ReadQuantizedFloatAndAdvance(u32 *stream, Polytrak2QuantizationRange range);
extern f32 g_motionTrackFrameScale;
extern char Bitarray_ExpandCurveSamples_AddressEuX[];
extern char Bitarray_ExpandCurveSamples_AddressEu[];
extern char Bitarray_ExpandCurveSamples_AddressUsRev1[];
extern char Bitarray_ExpandCurveSamples_AddressUs[];
extern char Bitarray_ExpandCurveSamples_Address[];
extern char Bitarray_ReadStridedFloatSamples_AddressEuX[];
extern char Bitarray_ReadStridedFloatSamples_AddressEu[];
extern char Bitarray_ReadStridedFloatSamples_AddressUsRev1[];
extern char Bitarray_ReadStridedFloatSamples_AddressUs[];
extern char Bitarray_ReadStridedFloatSamples_Address[];
extern char Polytrak2_DecodeScalarSamples_AddressEuX[];
extern char Polytrak2_DecodeScalarSamples_AddressEu[];
extern char Polytrak2_DecodeScalarSamples_AddressUsRev1[];
extern char Polytrak2_DecodeScalarSamples_AddressUs[];
extern char Polytrak2_DecodeScalarSamples_Address[];

extern const f32 g_expandedRotationRangeEnd;
extern const f32 g_expandedRotationRangeStart;
extern const f32 g_expandedTranslationRangeEnd;
extern const f32 g_expandedTranslationRangeStart;
extern s32 g_motionTrackDecodeRotation;
extern s32 g_motionTrackDecodeTranslation;
struct AnimRef; struct CVector3_t; extern void Polytrak2_SampleVectorTrack(struct AnimRef *anim, s32 index, f32 time, struct CVector3_t *out);
#endif
