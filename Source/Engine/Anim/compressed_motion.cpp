#include "Engine/Anim/BitArray.h"
#include "Common/localdecoderange.h"
#include "include_asm.h"
#include "Common/Lone/motion_track_decode_range_end.h"
#include "Common/stream.h"
#include "Game/soundinfo.h"
#include "Common/vector4f.h"
#include "Common/ppdecom_unpackresource.h"
#include "Common/triple.h"
#include "types.h"
#include "System/polytrak2_interpolatejointquaternion.h"
#include "System/bitarray_sample_evaluation.h"
#include "Render/setn64_getpacksection.h"
#include "Engine/graphics_math.h"
#include "Engine/Anim/compressed_motion.h"
#if defined(VERSION_US_REV1)
#include "types.h"
#endif
#if defined(VERSION_US_REV1)
#include "Common/stream.h"
#endif
#if defined(VERSION_US_REV1)
#include "System/bitarray_sample_evaluation.h"
#endif
#include "LIBC.H"
#include "Engine/Cache/cache.h"
#include "Engine/session.h"
#include "Engine/cache.h"
#include "Common/cache_releaseresource.h"
#include "Common/runtime_declarations.h"
#include "Common/resident_event_handler.h"
#include "Polytrak2/polytrak2_evaluateanimationcurve.h"
#include "Common/sharedplayer.h"
#include "Common/aiprofile.h"
#include "Common/localdecoderange.h"
#include "System/polytrak2_decodescalarsamples_data.h"
#include "Common/format.h"
#include "data_overlay_layouts.h"
#include "Engine/contpad.h"
#include "Data/rest_source_records.h"
#include "Common/actorresourceheader.h"

/* POLYTRAK2_SAMPLEROTATIONTRACK.CPP */

static __inline__ f32 unsignedFloat(u32 value,const f64 *bias) {
    f64 result=(f64)(s32)value;
    if((s32)value<0) result+=*bias;
    return (f32)result;
}


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
            if (unsignedFloat(span,g_rotationTrackLowerKeySpanTestBias)*rate <= 0.0f) {
            first = (s32)(unsignedFloat(span,&g_rotationTrackLowerKeySpanIndexBias)*rate);
        } else {
            f32 integer = (f32)(s32)(unsignedFloat(span,&g_rotationTrackLowerKeyWrappedIntegerSpanBias)*rate);
            f32 value = unsignedFloat(span,&g_rotationTrackLowerKeyWrappedValueSpanBias)*rate;
            first = (integer != value);
            first += (s32)(unsignedFloat(span,&g_rotationTrackLowerKeyWrappedSpanBias)*rate);
        }
            }
        second=first+1;
        if (length <= (f32)second) {
            if (unsignedFloat(span,&g_rotationTrackUpperKeySpanTestBias)*rate <= 0.0f) {
            second = (s32)(unsignedFloat(span,&g_rotationTrackUpperKeySpanIndexBias)*rate);
        } else {
            f32 integer = (f32)(s32)(unsignedFloat(span,&g_rotationTrackUpperKeyWrappedIntegerSpanBias)*rate);
            f32 value = unsignedFloat(span,&g_rotationTrackUpperKeyWrappedValueSpanBias)*rate;
            second = (integer != value);
            second += (s32)(unsignedFloat(span,&g_rotationTrackUpperKeyWrappedSpanBias)*rate);
        }
        }
        for (i = 0; i < 3; i++) {
            dest[i] = (g_rotationTrackInterpolationUnit - frac) * frames[first * 4 + i] + frac * frames[second * 4 + i];
        }
    }
}

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
    {
        u8 *keys = (u8 *)SetN64_GetPackSection((s32 *)root, 1);
        base = index * 4;
        keys += base;
        key = ((KeyIndex *)keys)->rotation;
    }
    rate = track->rate;
    length = track->length;
    time *= rate;
    if (key == -1) {
        u8 *table = SetN64_GetPackSection((s32 *)root, 2);
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
            if (length - g_rotationTrackLowerKeyFrameEndBias[0] <= (f32)first) {
                if ((unsignedFloat(anim->span,&g_rotationTrackLowerKeyEndSpanTestBias)*rate) <= 0.0f) first = (s32)(unsignedFloat(anim->span,&g_rotationTrackLowerKeyEndSpanIndexBias)*rate);
                else {
                    f32 integer = (f32)(s32)(unsignedFloat(anim->span,&g_rotationTrackLowerKeyEndWrappedIntegerSpanBias)*rate);
                    f32 value = unsignedFloat(anim->span,&g_rotationTrackLowerKeyEndWrappedValueSpanBias)*rate;
                    first = (integer != value);
                    first += (s32)(unsignedFloat(anim->span,&g_rotationTrackLowerKeyEndWrappedSpanBias)*rate);
                }
            }
            second = first + 1;
            if (length - g_rotationTrackUpperKeyFrameEndBias <= (f32)second) {
                if ((unsignedFloat(anim->span,&g_rotationTrackUpperKeyEndSpanTestBias)*rate) <= 0.0f) second = (s32)(unsignedFloat(anim->span,&g_rotationTrackUpperKeyEndSpanIndexBias)*rate);
                else {
                    f32 integer = (f32)(s32)(unsignedFloat(anim->span,&g_rotationTrackUpperKeyEndWrappedIntegerSpanBias)*rate);
                    f32 value = unsignedFloat(anim->span,&g_rotationTrackUpperKeyEndWrappedValueSpanBias)*rate;
                    second = (integer != value);
                    second += (s32)(unsignedFloat(anim->span,&g_rotationTrackUpperKeyEndWrappedSpanBias)*rate);
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
            converted += g_sampleTrackUnsignedConversionBias[0];
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
    decode.quantization.start = first;
    decode.quantization.delta = second - first;
    decode.quantization.value = Polytrak2_ReadBitsAndAdvance(&decode.stream, 6);
    i = 0;
    if (count > 0) {
        do {
            out->value = Polytrak2_ReadQuantizedFloatAndAdvance(&decode.stream, decode.quantization);
            i++;
            out++;
        } while (i < count);
    }
    *stream = decode.stream;
}

#if defined(VERSION_US)


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


/* Expand each encoded track, optionally smooth its four channels in place,
 * then normalize quaternion samples. */


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

/* POLYTRAK2_CHOOSEQUANTIZEDTRACKRATE.CPP */

/* Converts an amount over a period into a whole rate: returns g_motionQuantizedRateZero[0] for an amount
 * equal to it or a period not above g_motionQuantizedRatePeriodThreshold; otherwise the ratio scaled by g_motionQuantizedRatePeriodThreshold + 4 and rounded up
 * when that stays below the limit g_motionMinimumQuantizedRate, else the ratio scaled by g_motionQuantizedRateFallbackScale rounded up when that
 * stays below the limit, else the amount itself. Rounding up is a static helper. */
static inline f32 round_up(f32 x, f32 floor) {
    s32 i;

    if (x <= floor) {
        return (f32)(s32)x;
    }
    i = (s32)x;
    if ((f32)i == x) {
        return (f32)i;
    }
    return (f32)(i + 1);
}






f32 Polytrak2_ChooseQuantizedTrackRate(f32 amount, f32 period) {
    f32 rate;

    rate = 0.0f;
    if (amount == g_motionQuantizedRateZero[0]) {
        return g_motionQuantizedRateZero[0];
    }
    if (period <= g_motionQuantizedRatePeriodThreshold) {
        return g_motionQuantizedRateZero[0];
    }
    rate = round_up(amount / period * g_motionQuantizedRateScale, rate);
    if (rate < g_motionMinimumQuantizedRate) {
        return rate;
    }
    rate = round_up(amount / period * g_motionQuantizedRateFallbackScale, 0.0f);
    if (rate < g_motionMinimumQuantizedRate) {
        return rate;
    }
    return amount;
}

/* POLYTRAK2_REBUILDEXPANDEDANIMATIONRESOURCE.CPP */

/* Resource blocks store a count and relative offsets; empty entries carry
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
void Polytrak2_RebuildExpandedAnimationResource(s32 cacheContext, ResourceHandle **handle) {
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
        header->frameStep = g_expandedAnimationInitialFrameStep[0];
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

/* POLYTRAK2_EVALUATEANIMATIONCURVE.CPP */

/* Reads one envelope segment from a bitstream, either as raw floats or as scaled table values. */

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
        lo = Polytrak2_ScaleToRange(lo, g_motionTrackDecodeRangeStart, g_motionTrackDecodeRangeEnd);
        hi = Polytrak2_ScaleToRange(hi, g_motionTrackDecodeRangeStart, g_motionTrackDecodeRangeEnd);
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
  PackedBitPair *words;
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
  words = (PackedBitPair *) address;
  words->low = (words->low & (~lowMask)) | low;
  words->high = (words->high & (~highMask)) | high;
}
static inline void writeQuantized(u32 bitAddress, Polytrak2QuantizationRange range, f32 value) {
    f32 scaled;
    s32 integral;
    s32 quantized;

    scaled = (((value - range.start) / range.delta) * (f32) ((1 << range.value) - 1)) + g_packedFloatQuantizationRoundBias[0];
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

/* POLYTRAK2_INTERPOLATEJOINTQUATERNION.CPP */

/** Return the first word of the object referenced. */
void *Polytrak2_GetResidentResource(AnimRef *object) {
    return *object->data;
}

void Polytrak2_InterpolateJointTranslation(BoneRotationTrackView *animationLinks, s32 jointIndex, Triple *translationOut) {
    BoneRotationIndexPair *indices = (void *)animationLinks->boneIndexPairs;
    s16 idx;
    CROMInitialOrientation_t *recs;
    void *base;

    idx = indices[jointIndex].translation;
    if (idx == -1) {
        recs = (void *)animationLinks->initialOrientations;
        __builtin_memcpy(translationOut, &recs[jointIndex].position, sizeof(*translationOut));
        return;
    }
    base = SetN64_GetPackSection(animationLinks->translationFrames, (s32) idx);
    Graphu64_InterpolateVector(translationOut, animationLinks->frameBlend,
                  (s32 *)base + animationLinks->translationFirst,
                  (s32 *)base + animationLinks->translationNext);
}

void Polytrak2_InterpolateJointQuaternion(BoneRotationTrackView *animationLinks, s32 jointIndex, CQuatern *cQuatern) {
    BoneRotationIndexPair *indices = (void *)animationLinks->boneIndexPairs;
    s16 idx;
    CROMInitialOrientation_t *rec;
    void *base;
    f32 scale;

    idx = indices[jointIndex].rotationIndex;
    if (idx == -1) {
        rec = (void *)(animationLinks->initialOrientations + jointIndex * sizeof(CROMInitialOrientation_t));
        scale = g_jointInterpolationAngleScale[0];
        cQuatern->x = (f32)(rec->m_RotX) * scale;
        cQuatern->y = (f32)(rec->m_RotY) * scale;
        cQuatern->z = (f32)(rec->m_RotZ) * scale;
        cQuatern->w = (f32)(rec->m_RotW) * scale;
        return;
    }
    base = SetN64_GetPackSection(animationLinks->rotationFrames, (s32) idx);
    Graphu64_InterpolateQuaternionArc(cQuatern, animationLinks->frameBlend,
                  (s32 *)base + animationLinks->rotationFirst,
                  (s32 *)base + animationLinks->rotationNext);
}

/** Scale a value by the maximum integer represented by a bit count. */
float Polytrak2_UnpackUnitValue(float value, int bits) {
    return value / (float)((1 << bits) - 1);
}

f32 Polytrak2_ScaleToRange(f32 value, f32 lower, f32 upper) {
    return value * (upper - lower) + lower;
}

s32 Polytrak2_ByteAddressToBitAddress(s32 byteAddress) {
    return (byteAddress & 0xF0000000) | ((byteAddress & 0x0FFFFFFF) * 8);
}

/** Preserve the top nibble and shift the lower 28 bits right by three. */
unsigned int Polytrak2_BitAddressToByteAddress(unsigned int value) {
    return (value & 0xF0000000) | ((value & 0x0FFFFFFF) >> 3);
}

/** Repack the low address bits while retaining the high nibble. */
unsigned int Polytrak2_BitAddressToWordAddress(unsigned int bitAddress) {
    return (bitAddress & 0xF0000000) | ((bitAddress & 0x0FFFFFE0) >> 3);
}

/* Reads a width-bit field starting at a packed bit address, returning it right-aligned. */

int Polytrak2_ReadBitsAtAddress(int bitAddress, unsigned int width) {
    int shift;
    int *word;
    unsigned int value;
    unsigned int next;

    word = (int *) ((bitAddress & 0xF0000000) |
                    ((unsigned int) (bitAddress & 0x0FFFFFE0) >> 3));
    shift = bitAddress & 0x1F;
    value = word[0];
    next = word[1];
    if (shift != 0) {
        value >>= shift;
        next <<= 32 - shift;
        value |= next;
    }
    if (width < 32U) {
        value &= (1 << width) - 1;
    }
    return value;
}

void Polytrak2_WriteBitsAtAddress(u32 bitAddress, u32 bitCount, u32 fieldValue) {
    u32 wordAddress;
    s32 bitOffset;
    s32 remainingWordBits;
    u32 overflowMask;
    u32 maskedValue;
    u32 writeShift;
    u32 overflowValue;
    u32 firstWordValue;
    u32 firstWordMask;

    overflowMask = (1 << bitCount) - 1;
    firstWordMask = overflowMask;
    bitOffset = bitAddress & 0x1F;
    writeShift = bitOffset;
    maskedValue = fieldValue & overflowMask;
    if (bitOffset == 0) {
        firstWordValue = maskedValue;
        overflowMask = 0;
        overflowValue = 0;
    } else {
        firstWordMask = overflowMask << writeShift;
        remainingWordBits = 32 - writeShift;
        overflowMask >>= remainingWordBits;
        firstWordValue = maskedValue << writeShift;
        overflowValue = maskedValue >> remainingWordBits;
    }
    wordAddress = (bitAddress & 0xF0000000) | ((u32)(bitAddress & 0x0FFFFFE0) >> 3);
    *(s32 *)wordAddress = (*(s32 *)wordAddress & ~firstWordMask) | firstWordValue;
    ((s32 *)wordAddress)[1] = (((s32 *)wordAddress)[1] & ~overflowMask) | overflowValue;
}

u32 Polytrak2_ReadBitsAndAdvance(u32 *stream, u32 width) {
    u32 bitAddress;
    u32 shift;
    u32 *word;
    u32 value;
    u32 next;

    bitAddress = *stream;
    word = (u32 *) ((bitAddress & 0xF0000000) |
                    ((bitAddress & 0x0FFFFFE0) >> 3));
    shift = bitAddress & 0x1F;
    value = word[0];
    next = word[1];
    if (shift != 0) {
        value >>= shift;
        next <<= 32 - shift;
        value |= next;
    }
    if (width < 32U) {
        value &= (1 << width) - 1;
    }
    *stream = bitAddress + width;
    return value;
}

void Polytrak2_WriteBitsAndAdvance(u32 *bitCursor, u32 bitCount, u32 fieldValue) {
    u32 wordAddress;
    s32 bitOffset;
    s32 remainingWordBits;
    u32 overflowMask;
    u32 maskedValue;
    u32 writeShift;
    u32 overflowValue;
    u32 firstWordValue;
    u32 firstWordMask;
    u32 value;

    value = *bitCursor;
    overflowMask = (1 << bitCount) - 1;
    firstWordMask = overflowMask;
    bitOffset = value & 0x1F;
    writeShift = bitOffset;
    maskedValue = fieldValue & overflowMask;
    if (bitOffset == 0) {
        firstWordValue = maskedValue;
        overflowMask = 0;
        overflowValue = 0;
    } else {
        firstWordMask = overflowMask << writeShift;
        remainingWordBits = 32 - writeShift;
        overflowMask >>= remainingWordBits;
        firstWordValue = maskedValue << writeShift;
        overflowValue = maskedValue >> remainingWordBits;
    }
    wordAddress = (value & 0xF0000000) | ((u32)(value & 0x0FFFFFE0) >> 3);
    *(s32 *)wordAddress = (*(s32 *)wordAddress & ~firstWordMask) | firstWordValue;
    ((s32 *)wordAddress)[1] = (((s32 *)wordAddress)[1] & ~overflowMask) | overflowValue;
    *bitCursor += bitCount;
}

Polytrak2QuantizationRange Polytrak2_ComputeQuantizationRange(f32 minimumValue, f32 maximumValue, f32 maximumError) {
    Polytrak2QuantizationRange result;
    f32 ratio;
    s32 truncated;
    s32 bits;
    u32 count;
    u32 highest;
    u32 bit;
    u32 value;

    result.start = minimumValue;
    result.delta = maximumValue - minimumValue;
    ratio = result.delta / (maximumError + maximumError);
    if (ratio <= 0.0f) {
        bits = (s32)ratio + 1;
    } else {
        truncated = (s32)ratio;
        bits = truncated + 1;
        if ((f32)truncated != ratio) {
            bits = truncated + 2;
        }
    }
    count = 0;
    highest = 0;
    bit = 0;
    do {
        if (bits & (u32)(1 << bit)) {
            count += 1;
            highest = bit;
        }
        bit += 1;
    } while (bit < 32U);
    value = highest;
    if (count >= 2U) {
        value += 1;
    }
    result.value = value;
    return result;
}

/* POLYTRAK2_DECODESCALARSAMPLES_DATA.CPP */

/* Quantizes a float into a range's bit width and writes the value into the packed bit words at an address. */

inline static void write_bits_polytrak2_decodescalarsamples_data(u32 value, u32 bitAddress, u32 bitWidth)
{
  u32 wordAddress;
  s32 bitOffset;
  s32 highWordShift;
  u32 fieldMask;
  u32 maskedValue;
  u32 bitShift;
  u32 highWordValue;
  u32 lowWordValue;
  u32 lowWordMask;
  PackedBitPair *words;
  fieldMask = (1 << bitWidth) - 1;
  lowWordMask = fieldMask;
  bitOffset = bitAddress & 0x1F;
  bitShift = bitOffset;
  maskedValue = value & fieldMask;
  if (bitOffset == 0)
  {
    lowWordValue = maskedValue;
    fieldMask = 0;
    highWordValue = 0;
  }
  else
  {
    lowWordMask = fieldMask << bitShift;
    highWordShift = 32 - bitShift;
    fieldMask >>= highWordShift;
    lowWordValue = maskedValue << bitShift;
    highWordValue = maskedValue >> highWordShift;
  }
  wordAddress = (bitAddress & 0xF0000000) | (((u32) (bitAddress & 0x0FFFFFE0)) >> 3);
  words = (PackedBitPair *) wordAddress;
  words->low = (words->low & (~lowWordMask)) | lowWordValue;
  words->high = (words->high & (~fieldMask)) | highWordValue;
}

/* Decodes element elementIndex of a packed bit-field float array into a float scaled into its range. */

static inline f32 decode(s32 bitAddress, Polytrak2QuantizationRange range) {
    s32 shift;
    u32 *word;
    u32 value;
    u32 next;
    f64 converted;
    f32 result;
    u32 width;

    width = range.value;
    word = (u32 *) ((bitAddress & 0xF0000000) |
                    ((u32) (bitAddress & 0x0FFFFFE0) >> 3));
    shift = bitAddress & 0x1F;
    value = word[0];
    next = word[1];
    if (shift != 0) {
        value >>= shift;
        next <<= 32 - shift;
        value |= next;
    }
    if (width < 32U) {
        value &= (1 << width) - 1;
    }
    converted = (s32) value;
    if ((s32) value < 0) {
        converted += g_packedRangeUnsignedBias[0];
    }
    result = (f32) converted;
    result /= (f32) ((1 << width) - 1);
    result *= range.delta;
    result += range.start;
    return result;
}

f32 Polytrak2_ReadQuantizedFloatAtAddress(s32 bitAddress, Polytrak2QuantizationRange range) {
    s32 shift;
    u32 *word;
    u32 value;
    u32 next;
    f64 converted;
    f32 result;

    word = (u32 *) ((bitAddress & 0xF0000000) |
                    ((u32) (bitAddress & 0x0FFFFFE0) >> 3));
    shift = bitAddress & 0x1F;
    value = word[0];
    next = word[1];
    if (shift != 0) {
        value >>= shift;
        next <<= 32 - shift;
        value |= next;
    }
    if (range.value < 32U) {
        value &= (1 << range.value) - 1;
    }
    converted = (s32) value;
    if ((s32) value < 0) {
        converted += g_packedScalarUnsignedBias[0];
    }
    result = (f32) converted;
    result /= (f32) ((1 << range.value) - 1);
    result *= range.delta;
    result += range.start;
    return result;
}

void Polytrak2_WriteQuantizedFloatAtAddress(s32 bitAddress, Polytrak2QuantizationRange range, f32 sourceValue)
{
  f32 unscaledValue;
  f32 roundedScaledValue;
  s32 truncatedScaledValue;
  s32 quantizedValue;
  unscaledValue = sourceValue;
  roundedScaledValue = (unscaledValue - range.start) / range.delta * (f32) ((1 << range.value) - 1) + 0.5f;
  if (roundedScaledValue >= 0.0f)
  {
    quantizedValue = (s32) roundedScaledValue;
  }
  else
  {
    truncatedScaledValue = (s32) roundedScaledValue;
    quantizedValue = 1;
    if ((f32) truncatedScaledValue == roundedScaledValue)
    {
      quantizedValue = 0;
    }
    if (range.value)
    {
      quantizedValue = truncatedScaledValue - quantizedValue;
    }
    else
    {
      quantizedValue = truncatedScaledValue - quantizedValue;
    }
  }
  write_bits_polytrak2_decodescalarsamples_data(quantizedValue, bitAddress, range.value);
}

f32 Polytrak2_ReadQuantizedFloatAndAdvance(u32 *stream, Polytrak2QuantizationRange range) {
    u32 bitAddress;
    u32 *streamPtr;
    s32 shift;
    u32 *word;
    u32 value;
    u32 next;
    u32 width;
    f64 converted;
    f32 result;
    LocalDecodeRange decodeRange;

    streamPtr = stream;
    bitAddress = *streamPtr;
    decodeRange.range = range;
    width = decodeRange.range.value;
    word = (u32 *) ((bitAddress & 0xF0000000) |
                    ((bitAddress & 0x0FFFFFE0) >> 3));
    shift = bitAddress & 0x1F;
    value = word[0];
    next = word[1];
    if (shift != 0) {
        value >>= shift;
        next <<= 32 - shift;
        value |= next;
    }
    if (width < 32U) {
        value &= (1 << width) - 1;
    }
    converted = (s32) value;
    if ((s32) value < 0) {
        converted += g_packedArrayUnsignedBias[0];
    }
    result = (f32) converted;
    result /= (f32) ((1 << width) - 1);
    result *= decodeRange.range.delta;
    result += decodeRange.range.start;
    *streamPtr += range.value;
    return result;
}

/** Initialize a packed array and its decoding range. */
void Polytrak2_InitializeQuantizedArray(DecodeArray *decodeArray, int baseBitAddress, Polytrak2QuantizationRange valueRange, int elementCount) {
    decodeArray->base = baseBitAddress;
    decodeArray->range = valueRange;
    decodeArray->count = elementCount;
}

f32 Polytrak2_GetQuantizedArrayElement(DecodeArray *packedArray, s32 elementIndex) {
    return decode(packedArray->base + (packedArray->range.value * elementIndex), packedArray->range);
}

/** Initialize a packed array and its decoding range. */
void Polytrak2_InitializeUnsignedArray(DecodeArray *decodeArray, int baseBitAddress, Polytrak2QuantizationRange valueRange, int elementCount) {
    decodeArray->base = baseBitAddress;
    decodeArray->range = valueRange;
    decodeArray->count = elementCount;
}

int Polytrak2_GetUnsignedArrayElement(BitFieldSource *packedArray, int elementIndex) {
    int bitAddress;
    int shift;
    int *word;
    unsigned int value;
    unsigned int next;
    unsigned int width;

    width = packedArray->width;
    bitAddress = packedArray->base + (width * elementIndex);
    word = (int *) ((bitAddress & 0xF0000000) |
                    ((unsigned int) (bitAddress & 0x0FFFFFE0) >> 3));
    shift = bitAddress & 0x1F;
    value = word[0];
    next = word[1];
    if (shift != 0) {
        value >>= shift;
        next <<= 32 - shift;
        value |= next;
    }
    if (width < 32U) {
        value &= (1 << width) - 1;
    }
    return value;
}

/** Initialize a packed array and its decoding range. */
void Polytrak2_InitializeHighBitsSetArray(DecodeArray *decodeArray, int baseBitAddress, Polytrak2QuantizationRange valueRange, int elementCount) {
    decodeArray->base = baseBitAddress;
    decodeArray->range = valueRange;
    decodeArray->count = elementCount;
}

int Polytrak2_GetPackedHighBitsSetElement(BitFieldSource *packedArray, int elementIndex) {
    int bitAddress;
    int shift;
    int *word;
    unsigned int value;
    unsigned int next;
    unsigned int width;

    width = packedArray->width;
    bitAddress = packedArray->base + (width * elementIndex);
    word = (int *) ((bitAddress & 0xF0000000) |
                    ((unsigned int) (bitAddress & 0x0FFFFFE0) >> 3));
    shift = bitAddress & 0x1F;
    value = word[0];
    next = word[1];
    if (shift != 0) {
        value >>= shift;
        next <<= 32 - shift;
        value |= next;
    }
    if (width < 32U) {
        value &= (1 << width) - 1;
    }
    return value | (-1 << width);
}

/** Store a scalar word plus a three-word record by value. */
void Polytrak2_StoreWordAndTriple(PolytrakWordAndTripleRecord *destination, int wordValue, Triple tripleValue) {
    destination->wordValue = wordValue;
    destination->tripleValue = tripleValue;
}

/* POLYTRAK2_READQUANTIZEDSTREAMVALUE.CPP */

/* Decodes the next packed bit-field float from a stream record into its range and advances the record's bit address by the field width. */

static inline f32 decode_polytrak2_readquantizedstreamvalue(u32 *stream, Polytrak2QuantizationRange range) {
    u32 bitAddress;
    u32 *streamPtr;
    s32 shift;
    u32 *word;
    u32 value;
    u32 next;
    u32 width;
    f64 converted;
    f32 result;
    LocalDecodeRange decodeRange;

    streamPtr = stream;
    bitAddress = *streamPtr;
    decodeRange.range = range;
    width = decodeRange.range.value;
    word = (u32 *) ((bitAddress & 0xF0000000) |
                    ((bitAddress & 0x0FFFFFE0) >> 3));
    shift = bitAddress & 0x1F;
    value = word[0];
    next = word[1];
    if (shift != 0) {
        value >>= shift;
        next <<= 32 - shift;
        value |= next;
    }
    if (width < 32U) {
        value &= (1 << width) - 1;
    }
    converted = (s32) value;
    if ((s32) value < 0) {
        converted += g_packedStreamUnsignedBias[0];
    }
    result = (f32) converted;
    result /= (f32) ((1 << width) - 1);
    result *= decodeRange.range.delta;
    result += decodeRange.range.start;
    *streamPtr += range.value;
    return result;
}

/* Opens the next entry of a packed file: finds the last filled slot before the 0xDEADBEEF end marker in the offset table, records the following slot's offset as that slot's offset plus the given size, optionally copies the source bytes into the slot, and returns a pointer to it. */

f32 Polytrak2_ReadQuantizedStreamValue(LocalDecodeRange *valueStream) {
    return decode_polytrak2_readquantizedstreamvalue(&valueStream->bitAddress, valueStream->range);
}

/** Advance a record pointer by an indexed number of strides. */
void Polytrak2_SeekArrayElement(unsigned int *record, int index) {
    record[0] += index * record[1];
}

unsigned int Polytrak2_ReadCursorBits(unsigned int *bitCursor, unsigned int bitCount) {
    unsigned int bitAddress;
    unsigned int shift;
    unsigned int *word;
    unsigned int value;
    unsigned int next;

    bitAddress = *bitCursor;
    word = (unsigned int *) ((bitAddress & 0xF0000000) |
                             ((bitAddress & 0x0FFFFFE0) >> 3));
    shift = bitAddress & 0x1F;
    value = word[0];
    next = word[1];
    if (shift != 0) {
        value >>= shift;
        next <<= 32 - shift;
        value |= next;
    }
    if (bitCount < 32U) {
        value &= (1 << bitCount) - 1;
    }
    *bitCursor = bitAddress + bitCount;
    return value;
}

void Polytrak2_SkipCursorBits(int *bitCursor, int bitCount) {
    *bitCursor = *bitCursor + bitCount;
}

/** Samples the parsed animation track at the supplied frame time. */
f32 Polytrak2_SampleAnimationCurve(TrackBitarrayExpandCurveSamples *track, f32 time, s32 unusedFirst, s32 unusedSecond) {
    return Polytrak2_EvaluateAnimationCurve((Stream *)track, time);
}

void Polytrak2_InitializeOutputPack(Pack *packBuffer, s32 sectionCount) {
    s32 count;
    s32 *ptr;
    s32 magic;

    count = 1;
    packBuffer->count = sectionCount;
    packBuffer->offsets[0] = ((sectionCount * 4) + 15) & ~7;
    if (sectionCount > 0) {
        magic = 0xDEADBEEF;
        ptr = packBuffer->offsets;
        do {
            ptr[1] = magic;
            count += 1;
            ptr += 1;
        } while (sectionCount >= count);
    }
}

char *Polytrak2_AppendOutputPackSection(Pack *pack, const void *source, s32 size)
{
    s32 i;
    char *data;

    for (i = 0; i <= pack->count; i++) {
        if (pack->offsets[i] == 0xDEADBEEF) {
            break;
        }
    }
    i--;
    pack->offsets[i + 1] = pack->offsets[i] + size;
    data = (char *)pack + pack->offsets[i];
    if (source) {
        Libc_CopyBytes(data, source, size);
    }
    return data;
}

/* ROTATION_TRACK_START_SPAN_TEST_BIAS_DATA.CPP */

#if defined(VERSION_DE)
extern const double g_rotationTrackLowerKeySpanTestBias[10];
#endif

/* K_POLYTRAK2ENCODEDWORDS.CPP */



/* POLYTRAK2_SAMPLEROTATIONTRACK_DATA.CPP */

extern const f32 g_rotationTrackLowerKeyFrameEndBias[24];

/* SAMPLE_TRACK_UNSIGNED_CONVERSION_BIAS_DATA.CPP */

extern const double g_sampleTrackUnsignedConversionBias[2];

/* POLYTRAK2_REBUILDEXPANDEDANIMATIONRESOURCE_DATA.CPP */

extern const float g_motionQuantizedRateZero[4];

extern const float g_expandedAnimationInitialFrameStep[5];

/* POLYTRAK2.CPP */

extern const float g_packedFloatQuantizationRoundBias[1];

extern const float g_jointInterpolationAngleScale[1];

/* POLYTRAK2_DECODESCALARSAMPLES_DATA_DATA.CPP */

extern const double g_packedScalarUnsignedBias[1];

/* POLYTRAK2_READQUANTIZEDSTREAMVALUE_DATA.CPP */

#if !(defined(VERSION_US_REV1))
extern const double g_packedArrayUnsignedBias[1];
#endif

#if defined(VERSION_US_REV1)
extern const double g_packedArrayUnsignedBias[1];
#endif

#if !(defined(VERSION_US_REV1))
extern const double g_packedRangeUnsignedBias[1];
#endif

#if defined(VERSION_US_REV1)
extern const double g_packedRangeUnsignedBias[1];
#endif

#if !(defined(VERSION_US_REV1))
extern const double g_packedStreamUnsignedBias[1];
#endif

#if defined(VERSION_US_REV1)
extern const double g_packedStreamUnsignedBias[1];
#endif

/* G_AUDIOPITCHRATIOCURVE.CPP */
#if defined(VERSION_DE)

const f32 g_GAudiopitchratiocurveWords = 90.0f;
#endif
#if defined(VERSION_EU)
const f32 g_GAudiopitchratiocurveWords = 90.0f;
#endif
#if defined(VERSION_EU_X)
const f32 g_GAudiopitchratiocurveWords = 90.0f;
#endif
#if defined(VERSION_US)
const f32 g_GAudiopitchratiocurveWords = 90.0f;
#endif
#if defined(VERSION_US_REV1)
const f32 g_GAudiopitchratiocurveWords = 90.0f;
#endif

/* G_CONTROLLERBUTTONREMAP_DE.CPP */
#if defined(VERSION_DE)

/* Bytes the original holds up to the next 16-byte object boundary; no instruction reads them. */
unsigned int g_buttonRemapMasks[3] = {
    0x00008000, 0x00004000, 0x00004000,
};
#endif

/* POLYTRAK2_SAMPLEVECTORTRACK_DATA.CPP */

#if defined(VERSION_US_REV1)

#endif

#if defined(VERSION_EU) || defined(VERSION_EU_X) || defined(VERSION_US)

#endif

/* G_CONTROLLERBUTTONREMAP_RESOURCES.CPP */
#if defined(VERSION_EU)



char g_staleTextUeyJrD[12] __attribute__((aligned(4))) = "UEY, JR., D.";
#endif

/* G_CONTROLLERBUTTONREMAP.CPP */
#if defined(VERSION_EU_X)


ByteBlock12 g_buttonRemapScaleBytes = {
    { 63, 138, 67, 147, 63, 138, 31, 64, 63, 137, 250, 231 },
};
#endif

/* G_CONTROLLERBUTTONREMAP_US.CPP */
#if defined(VERSION_US)

/* Bytes the original holds up to the next 16-byte object boundary; no instruction reads them. */
unsigned int g_buttonRemapUsMaskWords[3] = {
    0x0000000F, 0x000A0004, 0x0000001A,
};
#endif

/* G_CONTROLLERBUTTONREMAP_CONTPAD.CPP */
#if defined(VERSION_US_REV1)

/* Bytes the original holds up to the next 16-byte object boundary; no instruction reads them. */
unsigned int g_buttonRemapScaleTriple[3] = {
    0x3F8AD4AA, 0x3F8AB06C, 0x3F8A8C29,
};
#endif

/* Retained data for this translation unit. */

const float g_packedHalfwordToUnitScale[1] = {
    3.051851e-05f,
};
/* 2^32 per unsigned span conversion of the rotation track keys, then the interpolation unit. */
const double g_rotationTrackLowerKeySpanTestBias[10] = {
    4294967296.0, 4294967296.0, 4294967296.0, 4294967296.0, 4294967296.0,
    4294967296.0, 4294967296.0, 4294967296.0, 4294967296.0, 4294967296.0,
};

const float g_rotationTrackInterpolationUnit = 1.0f;

const f32 g_rotationTrackLowerKeyFrameEndBias[24] = {
    1.0f, 0.0f, 30.0f, 0.0f, 30.0f, 0.0f,
    30.0f, 0.0f, 30.0f, 0.0f, 30.0f, 0.0f,
    1.0f, 0.0f, 30.0f, 0.0f, 30.0f, 0.0f,
    30.0f, 0.0f, 30.0f, 0.0f, 30.0f, 0.0f,
};

const double g_sampleTrackUnsignedConversionBias[2] = {
    4294967296.0, 4294967296.0,
};

const float g_motionQuantizedRateZero[4] = {
    1.0f, 0.01f, 3.0e+01f, 15.0f,
};

const float g_expandedAnimationInitialFrameStep[5] = {
    1.0f, -2.0e+03f, 2.0e+03f, -1.0f, 1.0f,
};

const float g_packedFloatQuantizationRoundBias[1] = {
    0.5f,
};

const float g_jointInterpolationAngleScale[1] = {
    3.051851e-05f,
};

const double g_packedScalarUnsignedBias[1] = {
    4294967296.0,
};
#if !(defined(VERSION_US_REV1))
const double g_packedArrayUnsignedBias[1] = {
    4294967296.0,
};
#endif
#if defined(VERSION_US_REV1)
const double g_packedArrayUnsignedBias[1] = {
    4294967296.0,
};
#endif
#if !(defined(VERSION_US_REV1))
const double g_packedRangeUnsignedBias[1] = {
    4294967296.0,
};
#endif
#if defined(VERSION_US_REV1)
const double g_packedRangeUnsignedBias[1] = {
    4294967296.0,
};
#endif
#if !(defined(VERSION_US_REV1))
const double g_packedStreamUnsignedBias[1] = {
    4294967296.0,
};
#endif
#if defined(VERSION_US_REV1)
const double g_packedStreamUnsignedBias[1] = {
    4294967296.0,
};
#endif
