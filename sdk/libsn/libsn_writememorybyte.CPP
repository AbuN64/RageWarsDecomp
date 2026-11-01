#include "COMMON/SHAREDPLAYER.H"
#include "COMMON/LIBSN_AND_RESIDENT_CALLBACKS.H"
#include "IO/libsn_writememorybyte.H"

/* Updates the selected byte in the aligned word addressed by address. */

void Libsn_WriteMemoryByte(s32 address, s32 byteValue) {
    int shiftedByte;
    s32 word_2;
    struct MemoryUsageStats *word_3;
    int new_var3_2;
    s32 shift = (~address & 3) * 8;
    int shift_ff;
    int unusedValue;
    struct MemoryUsageStats *word = (struct MemoryUsageStats *) (address & ~3);
    int new_var5_2;
    word_2 = (*word).value;
    shift_ff = 0xFF << shift;
    word_3 = word;
    new_var5_2 = shift_ff;
    do {
        ;
    } while (0);
    new_var3_2 = ~new_var5_2;
    shiftedByte = (byteValue & 0xFF) << shift;
    word_3->value = (word_2 & new_var3_2) | shiftedByte;
}
