#include "../../../../sdk/include/LIBC.H"
#include "COMMON/LOCALDECODERANGE.H"
#include "SYSTEM/POLYTRAK2_DECODESCALARSAMPLES_DATA.H"
#include "COMMON/STREAM.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/AIPROFILE.H"
#include "TYPES.H"
#include "ENGINE/ANIM/POLYTRAK2.H"

/* Decodes the next packed bit-field float from a stream record into its range and advances the record's bit address by the field width. Adapted from Polytrak2_ReadQuantizedFloatAndAdvance, inlined as a helper called with the record and a copy of the record's own range. */









static inline f32 decode(u32 *stream, Polytrak2QuantizationRange range) {
    u32 bitAddress;
    u32 *streamPtr;
    s32 shift;
    u32 *word;
    u32 value;
    u32 next;
    u32 width;
    f64 converted;
    f32 result;
    LocalDecodeRange local;

    streamPtr = stream;
    bitAddress = *streamPtr;
    local.range = range;
    width = local.range.value;
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
        converted += g_packedStreamUnsignedBias;
    }
    result = (f32) converted;
    result /= (f32) ((1 << width) - 1);
    result *= local.range.delta;
    result += local.range.start;
    *streamPtr += range.value;
    return result;
}

extern f32 Polytrak2_EvaluateAnimationCurve(Stream *stream, f32 time);

/* Opens the next entry of a packed file: finds the last filled slot before the 0xDEADBEEF end marker in the offset table, records the following slot's offset as that slot's offset plus the given size, optionally copies the source bytes into the slot, and returns a pointer to it. */





f32 Polytrak2_ReadQuantizedStreamValue(LocalDecodeRange *valueStream) {
    return decode(&valueStream->unused, valueStream->range);
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

void Polytrak2_InitializeOutputPack(void *packBuffer, s32 sectionCount) {
    s32 count;
    s32 *ptr;
    Pack *pack = packBuffer;
    s32 magic;

    count = 1;
    pack->count = sectionCount;
    pack->offsets[0] = ((sectionCount * 4) + 15) & ~7;
    if (sectionCount > 0) {
        magic = 0xDEADBEEF;
        ptr = pack->offsets;
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
