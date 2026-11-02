#include "include_asm.h"
#include "COMMON/LONE/MOTION_TRACK_DECODE_RANGE_END.H"
#include "COMMON/STREAM.H"
#include "GAME/SOUNDINFO.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/PPDECOM_UNPACKRESOURCE.H"
#include "COMMON/TRIPLE.H"
#include "TYPES.H"
#include "SYSTEM/POLYTRAK2_INTERPOLATEJOINTQUATERNION.H"

static __inline__ f32 unsignedFloat(u32 value,const f64 *bias) {
    f64 result=(f64)(s32)value;
    if((s32)value<0) result+=*bias;
    return (f32)result;
}

#include "TYPES.H"
#include "SYSTEM/BITARRAY_SAMPLE_EVALUATION.H"
#include "RENDER/SETN64_GETPACKSECTION.H"


/* Fills a three-float sample for an animation track: either the stored constant vector or a linear blend
 * of the two keys around the time. */


void Polytrak2_SampleVectorTrack(AnimRef *anim, s32 index, f32 time, CVector3 *out) {
    void *root;
    void *tracks;
    AnimTrack *track;
    f32 length;
    f32 rate;
    f32 position;
    f32 frac;
    f32 *frames;
    f32 *dest;
    s32 key;
    s32 first;
    s32 second;
    u32 span;
    s32 i;

    root = *anim->data;
    tracks = SetN64_GetPackSection(root, 5);
    track = SetN64_GetPackSection(tracks, 0);
    { AnimKeyTable *keys=SetN64_GetPackSection(root,1); key=keys->entries[index].position; }
    rate = track->rate;
    length = track->length;
    position = time * rate;
    if (key == -1) {
        u8 *table = SetN64_GetPackSection(root, 2);

        s32 offset = index * *(s32 *)table + 8;
        void *sample=table+offset;
        CVector3 *vec=sample;

        *out=*vec;
    } else {
        frames = SetN64_GetPackSection(SetN64_GetPackSection(tracks, 1), key);
        frac = (position >= 0.0f) ? position-(s32)position : (f32)(s32)position==position ? position-(s32)position : position-((s32)position-1);
        dest=&out->x;
        span = anim->span;
        if (span == 0xFFFF) {
            span = 0;
        }
        first = position >= 0.0f ? (s32)position : (s32)position - ((f32)(s32)position != position);
        if (length <= (f32)first) {
            if (unsignedFloat(span,&g_rotationTrackFirstSpanTestBias)*rate <= 0.0f) {
            first = (s32)(unsignedFloat(span,&g_rotationTrackFirstSpanIndexBias)*rate);
        } else {
            f32 integer = (f32)(s32)(unsignedFloat(span,&g_rotationTrackFirstWrappedIntegerSpanBias)*rate);
            f32 value = unsignedFloat(span,&g_rotationTrackFirstWrappedValueSpanBias)*rate;
            first = (integer != value);
            first += (s32)(unsignedFloat(span,&g_rotationTrackFirstWrappedSpanBias)*rate);
        }
            }
        second=first+1;
        if (length <= (f32)second) {
            if (unsignedFloat(span,&g_rotationTrackSecondSpanTestBias)*rate <= 0.0f) {
            second = (s32)(unsignedFloat(span,&g_rotationTrackSecondSpanIndexBias)*rate);
        } else {
            f32 integer = (f32)(s32)(unsignedFloat(span,&g_rotationTrackSecondWrappedIntegerSpanBias)*rate);
            f32 value = unsignedFloat(span,&g_rotationTrackSecondWrappedValueSpanBias)*rate;
            second = (integer != value);
            second += (s32)(unsignedFloat(span,&g_rotationTrackSecondWrappedSpanBias)*rate);
        }
        }
        for (i = 0; i < 3; i++) {
            dest[i] = (g_rotationTrackInterpolationUnit - frac) * frames[first * 4 + i] + frac * frames[second * 4 + i];
        }
    }
}

extern void Graphu64_InterpolateQuaternionArc(CQuatern *out, f32 t, CQuatern *from, CQuatern *to);






extern f32 Polytrak2_ReadQuantizedFloatAndAdvance(u32 *stream, s32 bits, f32 base, f32 range);

/* Fills a four-float keyframe sample for an animation track: either the stored constant pose or an
 * interpolation between the two keys around the time. */
void Polytrak2_SampleRotationTrack(AnimRef *anim, s32 index, f32 time, CQuatern *out) {
    void *root;
    void *tracks;
    AnimTrack *track;
    f32 length;
    f32 rate;
    s32 key;
    s32 first;
    s32 second;
    CQuatern *frames;
    s32 base;
    PoseTable *pose;

    root = *anim->data;
    tracks = SetN64_GetPackSection((s32 *)root, 5);
    track = (AnimTrack *)SetN64_GetPackSection((s32 *)tracks, 0);
     { u8 *keys = (u8 *)SetN64_GetPackSection((s32 *)root, 1); base = index * 4; keys += base; key = ((KeyIndex *)keys)->rotation; }
    rate = track->rate;
    length = track->length;
    time *= rate;
    if (key == -1) {
        u8 *table = (u8 *)SetN64_GetPackSection((s32 *)root, 2);
        s32 offset = index * *(s32 *)table + 8;
        s16 *entry = (s16 *)(table + offset);
        f32 scale = g_rotationTrackQuantizedComponentScale;

        out->x = entry[6] * scale;
        out->y = entry[7] * scale;
        out->z = entry[8] * scale;
        out->w = entry[9] * scale;
    } else {
        frames = (CQuatern *)SetN64_GetPackSection((s32 *)SetN64_GetPackSection((s32 *)tracks, 2), key);
        if (anim->span == 0xFFFF) {
            first = (time >= 0.0f ? (s32)time : (s32)time - ((f32)(s32)time != time));
            if (length <= (f32)first) {
                first = 0;
            }
            second = first + 1;
            if (length <= (f32)second) {
                second = 0;
            }
        } else {
            first = (time >= 0.0f ? (s32)time : (s32)time - ((f32)(s32)time != time));
            if (length - g_rotationTrackFirstFrameEndBias <= (f32)first) {
                if ((unsignedFloat(anim->span,&g_rotationTrackFirstEndSpanTestBias)*rate) <= 0.0f) first = (s32)(unsignedFloat(anim->span,&g_rotationTrackFirstEndSpanIndexBias)*rate);
                else {
                    f32 integer = (f32)(s32)(unsignedFloat(anim->span,&g_rotationTrackFirstEndWrappedIntegerSpanBias)*rate);
                    f32 value = unsignedFloat(anim->span,&g_rotationTrackFirstEndWrappedValueSpanBias)*rate;
                    first = (integer != value);
                    first += (s32)(unsignedFloat(anim->span,&g_rotationTrackFirstEndWrappedSpanBias)*rate);
                }
            }
            second = first + 1;
            if (length - g_rotationTrackSecondFrameEndBias <= (f32)second) {
                if ((unsignedFloat(anim->span,&g_rotationTrackSecondEndSpanTestBias)*rate) <= 0.0f) second = (s32)(unsignedFloat(anim->span,&g_rotationTrackSecondEndSpanIndexBias)*rate);
                else {
                    f32 integer = (f32)(s32)(unsignedFloat(anim->span,&g_rotationTrackSecondEndWrappedIntegerSpanBias)*rate);
                    f32 value = unsignedFloat(anim->span,&g_rotationTrackSecondEndWrappedValueSpanBias)*rate;
                    second = (integer != value);
                    second += (s32)(unsignedFloat(anim->span,&g_rotationTrackSecondEndWrappedSpanBias)*rate);
                }
            }
        }
        Graphu64_InterpolateQuaternionArc(out, time - (f32)(time >= 0.0f ? (s32)time : (s32)time - ((f32)(s32)time != time)), frames + first, frames + second);
    }
}

void Polytrak2_DecodeScalarSamples(u32 *stream, ScalarSampleOutput *out, s32 count) {
    ScalarSampleDecodeState decode;
    f32 first;
    f32 second;
    s32 i;
    f64 converted;

    decode.stream = *stream;
    if (g_motionTrackDecodeTranslation != 0) {
        decode.first_bits = Polytrak2_ReadBitsAndAdvance(&decode.stream, 32);
        decode.second_bits = Polytrak2_ReadBitsAndAdvance(&decode.stream, 32);
        first = *(f32 *)&decode.first_bits;
        second = *(f32 *)&decode.second_bits;
    } else {
        decode.first_bits = Polytrak2_ReadBitsAndAdvance(&decode.stream, 6);
        decode.second_bits = Polytrak2_ReadBitsAndAdvance(&decode.stream, 6);
        converted = (f64)decode.first_bits;
        if (decode.first_bits < 0) {
            converted += g_sampleTrackUnsignedConversionBias;
        }
        first = Polytrak2_UnpackUnitValue((f32)converted, 6);
        converted = (f64)decode.second_bits;
        if (decode.second_bits < 0) {
            converted += g_trackSectionUnsignedConversionBias;
        }
        second = Polytrak2_UnpackUnitValue((f32)converted, 6);
        first = Polytrak2_ScaleToRange(first, g_motionTrackDecodeRangeStart, g_motionTrackDecodeRangeEnd);
        second = Polytrak2_ScaleToRange(second, g_motionTrackDecodeRangeStart, g_motionTrackDecodeRangeEnd);
    }
    decode.base = first;
    decode.range = second - first;
    decode.bits = Polytrak2_ReadBitsAndAdvance(&decode.stream, 6);
    i = 0;
    if (count > 0) {
        do {
            out->value = Polytrak2_ReadQuantizedFloatAndAdvance(&decode.stream, decode.bits,
                                       decode.base, decode.range);
            i++;
            out++;
        } while (i < count);
    }
    *stream = decode.stream;
}

#if defined(VERSION_US)
extern char Bitarray_ExpandCurveSamples_AddressUs[], Polytrak2_DecodeScalarSamples_AddressUs[], Bitarray_ReadStridedFloatSamples_AddressUs[];
typedef struct {
    s32 count;
    s32 offsets[1];
} AnimationSampleTable;

s32 Polytrak2_DecodeAndSmoothSampleTracks(s32 source, AnimationSampleTable *buffer, s32 tracks, s32 channels, s32 radius, s32 encoding) {
    void (*decode)(void *, void *, s32) = 0;
    s32 stream[2];
    s32 *cursor;
    s32 i, index, j, offset, frames;
    f32 *out;
    f32 total, weight;
    switch (encoding) {
    case 0:
        decode = (void (*)(void *, void *, s32))Bitarray_ExpandCurveSamples_AddressUs;
        break;
    case 1:
        decode = (void (*)(void *, void *, s32))Polytrak2_DecodeScalarSamples_AddressUs;
        break;
    case 2:
        decode = (void (*)(void *, void *, s32))Bitarray_ReadStridedFloatSamples_AddressUs;
        break;
    }
    buffer->count = tracks;
    buffer->offsets[0] = (tracks * 4 + 15) & ~7;
    for (index = 1; index <= tracks; index++) {
        buffer->offsets[index] = 0xDEADBEEF;
    }
    for (i = 0; i < tracks; i++) {
        for (index = 0; index <= buffer->count && (u32)buffer->offsets[index] != 0xDEADBEEF; index++) {
        }
        index--;
        buffer->offsets[index + 1] = buffer->offsets[index] + g_motionTrackRotationFrameCount * 16;
    }
    stream[0] = Polytrak2_ByteAddressToBitAddress(source);
    i = 0;
    if (tracks > 0) {
        cursor = stream;
        do {
            f32 *values = (f32 *)SetN64_GetPackSection(buffer, i);
            j = 0;
            if (channels > 0) {
                out = values;
                do {
                    Polytrak2_ReadBitsAndAdvance((u32 *)cursor, 31);
                    decode(cursor, out, g_motionTrackSourceFrameCount);
                    out += 1;
                    j++;
                } while (j < channels);
            }
            i++;
        } while (i < tracks);
    }
    for (i = 0; i < tracks; i++) {
        s32 component;
        f32 *values;
        values = (f32 *)SetN64_GetPackSection(buffer, i);
        if (channels == 4 && radius != 0) {
            for (component = 0; component < channels; component++) {
                frames = g_motionTrackRotationFrameCount;
                for (j = 0; j < frames; j++) {
                    total = 0;
                    weight = 0;
                    for (offset = -radius; offset <= radius; offset++) {
                        total += values[((j + offset + frames) % frames) * 4 + component];
                        weight += 1.0f;
                    }
                    values[j * 4 + component] = total / weight;
                }
            }
        }
    }
    if (channels == 4) {
        for (j = 0; j < tracks; j++) {
            f32 *values = (f32 *)SetN64_GetPackSection(buffer, j);
            i = 0;
            if (g_motionTrackRotationFrameCount > 0) {
                out = values;
                do {
                    Graphu64_NormalizeQuaternion(out);
                    out += 4;
                } while (++i < g_motionTrackRotationFrameCount);
            }
        }
    }
    return 1;
}
#endif

#if defined(VERSION_EU_X)
extern char Bitarray_ExpandCurveSamples_AddressEuX[], Polytrak2_DecodeScalarSamples_AddressEuX[], Bitarray_ReadStridedFloatSamples_AddressEuX[];
typedef struct {
    s32 count;
    s32 offsets[1];
} AnimationSampleTable;

s32 Polytrak2_DecodeTrackSectionsEuX(s32 source, AnimationSampleTable *buffer, s32 tracks, s32 channels, s32 radius, s32 encoding) {
    void (*decode)(void *, void *, s32) = 0;
    s32 stream[2];
    s32 *cursor;
    s32 i, index, j, offset, frames;
    f32 *out;
    f32 total, weight;
    switch (encoding) {
    case 0:
        decode = (void (*)(void *, void *, s32))Bitarray_ExpandCurveSamples_AddressEuX;
        break;
    case 1:
        decode = (void (*)(void *, void *, s32))Polytrak2_DecodeScalarSamples_AddressEuX;
        break;
    case 2:
        decode = (void (*)(void *, void *, s32))Bitarray_ReadStridedFloatSamples_AddressEuX;
        break;
    }
    buffer->count = tracks;
    buffer->offsets[0] = (tracks * 4 + 15) & ~7;
    for (index = 1; index <= tracks; index++) {
        buffer->offsets[index] = 0xDEADBEEF;
    }
    for (i = 0; i < tracks; i++) {
        for (index = 0; index <= buffer->count && (u32)buffer->offsets[index] != 0xDEADBEEF; index++) {
        }
        index--;
        buffer->offsets[index + 1] = buffer->offsets[index] + g_motionTrackRotationFrameCount * 16;
    }
    stream[0] = Polytrak2_ByteAddressToBitAddress(source);
    i = 0;
    if (tracks > 0) {
        cursor = stream;
        do {
            f32 *values = (f32 *)SetN64_GetPackSection(buffer, i);
            j = 0;
            if (channels > 0) {
                out = values;
                do {
                    Polytrak2_ReadBitsAndAdvance((u32 *)cursor, 31);
                    decode(cursor, out, g_motionTrackSourceFrameCount);
                    out += 1;
                    j++;
                } while (j < channels);
            }
            i++;
        } while (i < tracks);
    }
    for (i = 0; i < tracks; i++) {
        s32 component;
        f32 *values;
        values = (f32 *)SetN64_GetPackSection(buffer, i);
        if (channels == 4 && radius != 0) {
            for (component = 0; component < channels; component++) {
                frames = g_motionTrackRotationFrameCount;
                for (j = 0; j < frames; j++) {
                    total = 0;
                    weight = 0;
                    for (offset = -radius; offset <= radius; offset++) {
                        total += values[((j + offset + frames) % frames) * 4 + component];
                        weight += 1.0f;
                    }
                    values[j * 4 + component] = total / weight;
                }
            }
        }
    }
    if (channels == 4) {
        for (j = 0; j < tracks; j++) {
            f32 *values = (f32 *)SetN64_GetPackSection(buffer, j);
            i = 0;
            if (g_motionTrackRotationFrameCount > 0) {
                out = values;
                do {
                    Graphu64_NormalizeQuaternion(out);
                    out += 4;
                } while (++i < g_motionTrackRotationFrameCount);
            }
        }
    }
    return 1;
}
#endif

#if defined(VERSION_EU)
extern char Bitarray_ExpandCurveSamples_AddressEu[], Polytrak2_DecodeScalarSamples_AddressEu[], Bitarray_ReadStridedFloatSamples_AddressEu[];
typedef struct {
    s32 count;
    s32 offsets[1];
} AnimationSampleTable;

s32 Polytrak2_DecodeTrackSectionsEu(s32 source, AnimationSampleTable *buffer, s32 tracks, s32 channels, s32 radius, s32 encoding) {
    void (*decode)(void *, void *, s32) = 0;
    s32 stream[2];
    s32 *cursor;
    s32 i, index, j, offset, frames;
    f32 *out;
    f32 total, weight;
    switch (encoding) {
    case 0:
        decode = (void (*)(void *, void *, s32))Bitarray_ExpandCurveSamples_AddressEu;
        break;
    case 1:
        decode = (void (*)(void *, void *, s32))Polytrak2_DecodeScalarSamples_AddressEu;
        break;
    case 2:
        decode = (void (*)(void *, void *, s32))Bitarray_ReadStridedFloatSamples_AddressEu;
        break;
    }
    buffer->count = tracks;
    buffer->offsets[0] = (tracks * 4 + 15) & ~7;
    for (index = 1; index <= tracks; index++) {
        buffer->offsets[index] = 0xDEADBEEF;
    }
    for (i = 0; i < tracks; i++) {
        for (index = 0; index <= buffer->count && (u32)buffer->offsets[index] != 0xDEADBEEF; index++) {
        }
        index--;
        buffer->offsets[index + 1] = buffer->offsets[index] + g_motionTrackRotationFrameCount * 16;
    }
    stream[0] = Polytrak2_ByteAddressToBitAddress(source);
    i = 0;
    if (tracks > 0) {
        cursor = stream;
        do {
            f32 *values = (f32 *)SetN64_GetPackSection(buffer, i);
            j = 0;
            if (channels > 0) {
                out = values;
                do {
                    Polytrak2_ReadBitsAndAdvance((u32 *)cursor, 31);
                    decode(cursor, out, g_motionTrackSourceFrameCount);
                    out += 1;
                    j++;
                } while (j < channels);
            }
            i++;
        } while (i < tracks);
    }
    for (i = 0; i < tracks; i++) {
        s32 component;
        f32 *values;
        values = (f32 *)SetN64_GetPackSection(buffer, i);
        if (channels == 4 && radius != 0) {
            for (component = 0; component < channels; component++) {
                frames = g_motionTrackRotationFrameCount;
                for (j = 0; j < frames; j++) {
                    total = 0;
                    weight = 0;
                    for (offset = -radius; offset <= radius; offset++) {
                        total += values[((j + offset + frames) % frames) * 4 + component];
                        weight += 1.0f;
                    }
                    values[j * 4 + component] = total / weight;
                }
            }
        }
    }
    if (channels == 4) {
        for (j = 0; j < tracks; j++) {
            f32 *values = (f32 *)SetN64_GetPackSection(buffer, j);
            i = 0;
            if (g_motionTrackRotationFrameCount > 0) {
                out = values;
                do {
                    Graphu64_NormalizeQuaternion(out);
                    out += 4;
                } while (++i < g_motionTrackRotationFrameCount);
            }
        }
    }
    return 1;
}
#endif

#if defined(VERSION_DE)
extern char Bitarray_ExpandCurveSamples_Address[], Polytrak2_DecodeScalarSamples_Address[], Bitarray_ReadStridedFloatSamples_Address[];
typedef struct {
    s32 count;
    s32 offsets[1];
} AnimationSampleTable;

s32 Polytrak2_DecodeTrackSections(s32 source, AnimationSampleTable *buffer, s32 tracks, s32 channels, s32 radius, s32 encoding) {
    void (*decode)(void *, void *, s32) = 0;
    s32 stream[2];
    s32 *cursor;
    s32 i, index, j, offset, frames;
    f32 *out;
    f32 total, weight;
    switch (encoding) {
    case 0:
        decode = (void (*)(void *, void *, s32))Bitarray_ExpandCurveSamples_Address;
        break;
    case 1:
        decode = (void (*)(void *, void *, s32))Polytrak2_DecodeScalarSamples_Address;
        break;
    case 2:
        decode = (void (*)(void *, void *, s32))Bitarray_ReadStridedFloatSamples_Address;
        break;
    }
    buffer->count = tracks;
    buffer->offsets[0] = (tracks * 4 + 15) & ~7;
    for (index = 1; index <= tracks; index++) {
        buffer->offsets[index] = 0xDEADBEEF;
    }
    for (i = 0; i < tracks; i++) {
        for (index = 0; index <= buffer->count && (u32)buffer->offsets[index] != 0xDEADBEEF; index++) {
        }
        index--;
        buffer->offsets[index + 1] = buffer->offsets[index] + g_motionTrackRotationFrameCount * 16;
    }
    stream[0] = Polytrak2_ByteAddressToBitAddress(source);
    i = 0;
    if (tracks > 0) {
        cursor = stream;
        do {
            f32 *values = (f32 *)SetN64_GetPackSection(buffer, i);
            j = 0;
            if (channels > 0) {
                out = values;
                do {
                    Polytrak2_ReadBitsAndAdvance((u32 *)cursor, 31);
                    decode(cursor, out, g_motionTrackSourceFrameCount);
                    out += 1;
                    j++;
                } while (j < channels);
            }
            i++;
        } while (i < tracks);
    }
    for (i = 0; i < tracks; i++) {
        s32 component;
        f32 *values;
        values = (f32 *)SetN64_GetPackSection(buffer, i);
        if (channels == 4 && radius != 0) {
            for (component = 0; component < channels; component++) {
                frames = g_motionTrackRotationFrameCount;
                for (j = 0; j < frames; j++) {
                    total = 0;
                    weight = 0;
                    for (offset = -radius; offset <= radius; offset++) {
                        total += values[((j + offset + frames) % frames) * 4 + component];
                        weight += 1.0f;
                    }
                    values[j * 4 + component] = total / weight;
                }
            }
        }
    }
    if (channels == 4) {
        for (j = 0; j < tracks; j++) {
            f32 *values = (f32 *)SetN64_GetPackSection(buffer, j);
            i = 0;
            if (g_motionTrackRotationFrameCount > 0) {
                out = values;
                do {
                    Graphu64_NormalizeQuaternion(out);
                    out += 4;
                } while (++i < g_motionTrackRotationFrameCount);
            }
        }
    }
    return 1;
}
#endif

#if defined(VERSION_US_REV1)
#include "TYPES.H"

#include "COMMON/STREAM.H"
#include "SYSTEM/BITARRAY_SAMPLE_EVALUATION.H"

/* Expand each encoded track, optionally smooth its four channels in place,
 * then normalize quaternion samples. */
extern char Bitarray_ExpandCurveSamples_AddressUsRev1[], Polytrak2_DecodeScalarSamples_AddressUsRev1[], Bitarray_ReadStridedFloatSamples_AddressUsRev1[];
typedef struct {
    s32 count;
    s32 offsets[1];
} AnimationSampleTable;

s32 Polytrak2_ExpandAnimationTracks(s32 source, AnimationSampleTable *buffer, s32 tracks, s32 channels, s32 radius, s32 encoding) {
    void (*decode)(void *, void *, s32) = 0;
    s32 stream[2];
    s32 *cursor;
    s32 i, index, j, offset, frames;
    f32 *out;
    f32 total, weight;
    switch (encoding) {
    case 0:
        decode = (void (*)(void *, void *, s32))Bitarray_ExpandCurveSamples_AddressUsRev1;
        break;
    case 1:
        decode = (void (*)(void *, void *, s32))Polytrak2_DecodeScalarSamples_AddressUsRev1;
        break;
    case 2:
        decode = (void (*)(void *, void *, s32))Bitarray_ReadStridedFloatSamples_AddressUsRev1;
        break;
    }
    buffer->count = tracks;
    buffer->offsets[0] = (tracks * 4 + 15) & ~7;
    for (index = 1; index <= tracks; index++) {
        buffer->offsets[index] = 0xDEADBEEF;
    }
    for (i = 0; i < tracks; i++) {
        for (index = 0; index <= buffer->count && (u32)buffer->offsets[index] != 0xDEADBEEF; index++) {
        }
        index--;
        buffer->offsets[index + 1] = buffer->offsets[index] + g_motionTrackRotationFrameCount * 16;
    }
    stream[0] = Polytrak2_ByteAddressToBitAddress(source);
    i = 0;
    if (tracks > 0) {
        cursor = stream;
        do {
            f32 *values = (f32 *)SetN64_GetPackSection(buffer, i);
            j = 0;
            if (channels > 0) {
                out = values;
                do {
                    Polytrak2_ReadBitsAndAdvance((u32 *)cursor, 31);
                    decode(cursor, out, g_motionTrackSourceFrameCount);
                    out += 1;
                    j++;
                } while (j < channels);
            }
            i++;
        } while (i < tracks);
    }
    for (i = 0; i < tracks; i++) {
        s32 component;
        f32 *values;
        values = (f32 *)SetN64_GetPackSection(buffer, i);
        if (channels == 4 && radius != 0) {
            for (component = 0; component < channels; component++) {
                frames = g_motionTrackRotationFrameCount;
                for (j = 0; j < frames; j++) {
                    total = 0;
                    weight = 0;
                    for (offset = -radius; offset <= radius; offset++) {
                        total += values[((j + offset + frames) % frames) * 4 + component];
                        weight += 1.0f;
                    }
                    values[j * 4 + component] = total / weight;
                }
            }
        }
    }
    if (channels == 4) {
        for (j = 0; j < tracks; j++) {
            f32 *values = (f32 *)SetN64_GetPackSection(buffer, j);
            i = 0;
            if (g_motionTrackRotationFrameCount > 0) {
                out = values;
                do {
                    Graphu64_NormalizeQuaternion(out);
                    out += 4;
                } while (++i < g_motionTrackRotationFrameCount);
            }
        }
    }
    return 1;
}
#endif
