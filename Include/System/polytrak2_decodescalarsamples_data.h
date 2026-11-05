#ifndef SYSTEM_POLYTRAK2_DECODESCALARSAMPLES_DATA_H
#define SYSTEM_POLYTRAK2_DECODESCALARSAMPLES_DATA_H
#include "Common/small_records.h"
#include "Common/localdecoderange.h"
#include "Common/runtime_declarations.h"
#include "Common/sharedplayer.h"
struct BitFieldSource;
struct DecodeArray;
struct PolytrakWordAndTripleRecord;
struct LocalDecodeRange {
    u32 bitAddress;
    Polytrak2QuantizationRange range;
};
struct TrackBitarrayExpandCurveSamples {
    s32 keys;
    char pad4[0x2C - 4];
    s32 stride;
};
struct DecodeArray {
    s32 base;
    Polytrak2QuantizationRange range;
    s32 count; /* 0x10 */
};
struct BitFieldSource {
    int base;
    unsigned int width;
};
struct MotionPackHeader {
    s32 x;
    s32 pad4;
    s32 z;
    f32 f0C;
    s32 n10;
    s32 n14;
};
struct PolytrakWordAndTripleRecord {
    int wordValue;
    char pad0[0x4 - 0x0 - sizeof(int)];
    Triple tripleValue;
};
typedef struct RootActor { char pad0[0x100]; u32 flags; } RootActor;
typedef struct RootClip { u16 count,loopStart; char pad4[4]; f32 rate; } RootClip;
typedef struct AngleKeys { char header[8]; s16 keys[1]; } AngleKeys;
struct PolytrakScalarSampleMetadata {
    f32 framePosition;
    char pad4[0x4];
    s16 frameCount;
    char padA[0x2];
    s32 loopStart;
    s32 ** animationHandle;
};
extern void Polytrak2_InitializeQuantizedArray(struct DecodeArray *decodeArray, int baseBitAddress, Polytrak2QuantizationRange valueRange, int elementCount);
extern int Polytrak2_GetPackedHighBitsSetElement(struct BitFieldSource *packedArray, int elementIndex);
extern f32 Polytrak2_GetQuantizedArrayElement(struct DecodeArray *packedArray, s32 elementIndex);
extern int Polytrak2_GetUnsignedArrayElement(struct BitFieldSource *packedArray, int elementIndex);
extern void Polytrak2_WriteQuantizedFloatAtAddress(s32 bitAddress, Polytrak2QuantizationRange range, f32 sourceValue);
extern void Polytrak2_InitializeHighBitsSetArray(struct DecodeArray *decodeArray, int baseBitAddress, Polytrak2QuantizationRange valueRange, int elementCount);
extern void Polytrak2_StoreWordAndTriple(struct PolytrakWordAndTripleRecord *destination, int wordValue, Triple tripleValue);
extern f32 Polytrak2_ReadQuantizedFloatAtAddress(s32 bitAddress, Polytrak2QuantizationRange range);
extern void Polytrak2_InitializeUnsignedArray(struct DecodeArray *decodeArray, int baseBitAddress, Polytrak2QuantizationRange valueRange, int elementCount);
#endif
