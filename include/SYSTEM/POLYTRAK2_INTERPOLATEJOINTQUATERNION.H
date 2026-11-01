#ifndef SYSTEM_POLYTRAK2_INTERPOLATEJOINTQUATERNION_H
#define SYSTEM_POLYTRAK2_INTERPOLATEJOINTQUATERNION_H
#include "COMMON/STREAM.H"
extern unsigned int Polytrak2_BitAddressToByteAddress(unsigned int value);
extern float Polytrak2_UnpackUnitValue(float value, int bits);
extern f32 Polytrak2_ScaleToRange(f32 value, f32 lower, f32 upper);
extern void Polytrak2_WriteBitsAtAddress(u32 bitAddress, u32 bitCount, u32 fieldValue);
extern unsigned int Polytrak2_BitAddressToWordAddress(unsigned int bitAddress);
extern Polytrak2QuantizationRange Polytrak2_ComputeQuantizationRange(f32 minimumValue, f32 maximumValue, f32 maximumError);
extern void Polytrak2_WriteBitsAndAdvance(u32 *bitCursor, u32 bitCount, u32 fieldValue);
extern void * Polytrak2_GetResidentResource(void *object);
extern s32 Polytrak2_ByteAddressToBitAddress(s32 byteAddress);
extern u32 Polytrak2_ReadBitsAndAdvance(u32 *stream, u32 width);
#endif
