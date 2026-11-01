#include "include_asm.h"
#include "COMMON/LOCALDECODERANGE.H"
#include "ENGINE/ANIM/POLYTRAK2.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
#include "TYPES.H"
#include "SYSTEM/POLYTRAK2_DECODESCALARSAMPLES_DATA.H"

/* 802609CC.CPP */
/* Quantizes a float into a range's bit width and writes the value into the packed bit words at an address. */

inline static void write_bits(u32 value, u32 bitAddress, u32 bitWidth)
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
  PackedBitWords *words;
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
  words = (PackedBitWords *) wordAddress;
  words->low = (words->low & (~lowWordMask)) | lowWordValue;
  words->high = (words->high & (~fieldMask)) | highWordValue;
}

/* Decodes element elementIndex of a packed bit-field float array into a float scaled into its range. Adapted from Polytrak2_ReadQuantizedFloatAtAddress, inlined as a helper (with the width held in a local) called with a base plus width-times-index bit address and the record's range. */

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
        converted += g_packedRangeUnsignedBias;
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
        converted += g_packedScalarUnsignedBias;
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
  write_bits(quantizedValue, bitAddress, range.value);
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
        converted += g_packedArrayUnsignedBias;
    }
    result = (f32) converted;
    result /= (f32) ((1 << width) - 1);
    result *= local.range.delta;
    result += local.range.start;
    *streamPtr += range.value;
    return result;
}

/** Initialize a packed array and its decoding range. */
void Polytrak2_InitializeQuantizedArray(void *decodeArray, int baseBitAddress, Polytrak2QuantizationRange valueRange, int elementCount) {
    DecodeArray *array = decodeArray;
    array->base = baseBitAddress;
    array->range = valueRange;
    array->count = elementCount;
}

f32 Polytrak2_GetQuantizedArrayElement(DecodeArray *packedArray, s32 elementIndex) {
    return decode(packedArray->base + (packedArray->range.value * elementIndex), packedArray->range);
}

/** Initialize a packed array and its decoding range. */
void Polytrak2_InitializeUnsignedArray(void *decodeArray, int baseBitAddress, Polytrak2QuantizationRange valueRange, int elementCount) {
    DecodeArray *array = decodeArray;
    array->base = baseBitAddress;
    array->range = valueRange;
    array->count = elementCount;
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
void Polytrak2_InitializeHighBitsSetArray(void *decodeArray, int baseBitAddress, Polytrak2QuantizationRange valueRange, int elementCount) {
    DecodeArray *array = decodeArray;
    array->base = baseBitAddress;
    array->range = valueRange;
    array->count = elementCount;
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
void Polytrak2_StoreWordAndTriple(void *destination, int wordValue, Triple tripleValue) {
    PolytrakWordAndTripleRecord *record = destination;
    record->wordValue = wordValue;
    record->tripleValue = tripleValue;
}


