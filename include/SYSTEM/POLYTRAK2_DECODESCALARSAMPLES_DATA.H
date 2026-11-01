#ifndef SYSTEM_POLYTRAK2_DECODESCALARSAMPLES_DATA_H
#define SYSTEM_POLYTRAK2_DECODESCALARSAMPLES_DATA_H
#include "COMMON/LOCALDECODERANGE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/SHAREDPLAYER.H"
struct LocalDecodeRange {
    u32 unused;
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
extern void Polytrak2_InitializeQuantizedArray(void *decodeArray, int baseBitAddress, Polytrak2QuantizationRange t, int elementCount);
extern int Polytrak2_GetPackedHighBitsSetElement(BitFieldSource *packedArray, int elementIndex);
extern f32 Polytrak2_GetQuantizedArrayElement(DecodeArray *packedArray, s32 elementIndex);
extern int Polytrak2_GetUnsignedArrayElement(BitFieldSource *packedArray, int elementIndex);
extern void Polytrak2_WriteQuantizedFloatAtAddress(s32 bitAddress, Polytrak2QuantizationRange range, f32 sourceValue);
extern void Polytrak2_InitializeHighBitsSetArray(void *decodeArray, int baseBitAddress, Polytrak2QuantizationRange t, int elementCount);
extern void Polytrak2_StoreWordAndTriple(void *destination, int wordValue, Triple t);
extern f32 Polytrak2_ReadQuantizedFloatAtAddress(s32 bitAddress, Polytrak2QuantizationRange range);
extern void Polytrak2_InitializeUnsignedArray(void *decodeArray, int baseBitAddress, Polytrak2QuantizationRange t, int elementCount);
#endif
