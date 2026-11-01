#include "COMMON/OBJRECAT5F14.H"
#include "TYPES.H"

/* Two-word value setter; live Barrel_FillWordPair uses the same word-array representation. */
void AnimPool_InitializeBitReader(s32 *value, s32 word) {
    value[0] = word;
    value[1] = 0;
}

s32 CBitReader_ReadBits(BitReader *reader, s32 bitCount);

s32 AnimPool_ReadSignedBits(BitReader *reader, s32 bitCount) {
    s32 val;
    s32 i;
    s32 mask;

    val = CBitReader_ReadBits(reader, bitCount);
    mask = 1 << (bitCount - 1);
    if (val & mask) {
        i = bitCount;
        if (bitCount < 32) {
            do {
                val |= 1 << i;
                i += 1;
            } while (i < 32);
        }
    }
    return val;
}

/** Reads bitCount bits (LSB first) from the bitstream at reader, advancing its bit position. */
s32 CBitReader_ReadBits(BitReader *reader, s32 bitCount) {
    s32 bitPos;
    s32 i;
    s32 result;

    i = 0;
    result = 0;
    if (bitCount > 0) {
        do {
            bitPos = reader->bitPos;
            result |= (((s32) *(reader->data + (bitPos >> 3)) >> (bitPos & 7)) & 1) << i;
            i += 1;
            reader->bitPos = (s32) (bitPos + 1);
        } while (i < bitCount);
    }
    return result;
}
