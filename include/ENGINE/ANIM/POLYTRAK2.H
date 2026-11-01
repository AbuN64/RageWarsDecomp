#ifndef ENGINE_ANIM_POLYTRAK2_H
#define ENGINE_ANIM_POLYTRAK2_H
#include "TYPES.H"
#include "COMMON/STREAM.H"
#include "COMMON/LOCALDECODERANGE.H"
#include "SYSTEM/POLYTRAK2_DECODESCALARSAMPLES_DATA.H"

/* Consecutive 32-bit storage words used by the scalar bit packer. */
typedef struct { u32 low; u32 high; } PackedBitWords;

extern f32 Polytrak2_ChooseQuantizedTrackRate(f32 amount, f32 period);

extern f32 Polytrak2_ReadQuantizedStreamValue(LocalDecodeRange *valueStream);

extern unsigned int Polytrak2_ReadCursorBits(unsigned int *bitCursor, unsigned int bitCount);

extern void Polytrak2_SeekArrayElement(unsigned int *record, int index);

extern void Polytrak2_SkipCursorBits(int *bitCursor, int bitCount);
#endif
