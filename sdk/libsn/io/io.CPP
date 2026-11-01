#include "TYPES.H"
#include "IO/libsn_readportbufferwithdma.H"
#include "IO/libsn_writememorybyte.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "IO/EXTERNS.H"
#include "IO/libsn_disableinterrupts.H"

/* 80200B14.CPP */
void Libsn_CopyPortToWordMemory(s32 source, s32 destination, u32 count) {
    while (count != 0 && (source & 3) != 0) {
        Libsn_WriteMemoryByte(destination++, (u8)Libsn_ReadPortByte(source++));
        count--;
    }
    while (count >= 4) {
        u32 word = Libsn_ReadPortWord(source);
        Libsn_WriteMemoryByte(destination++, word >> 24);
        Libsn_WriteMemoryByte(destination++, (word >> 16) & 0xFF);
        Libsn_WriteMemoryByte(destination++, (word >> 8) & 0xFF);
        Libsn_WriteMemoryByte(destination++, word & 0xFF);
        source += 4;
        count -= 4;
    }
    while (count != 0) {
        Libsn_WriteMemoryByte(destination++, (u8)Libsn_ReadPortByte(source++));
        count--;
    }
}

/* 80200800_3.CPP */
void Libsn_WritePortByte(s32 address, unsigned char byteValue)
{
  s32 unusedInteger1;
  s32 byteShift;
  byteShift = ((~address) & 3) * 8;
  address &= ~3;
  Libsn_WritePortWord(address, (Libsn_ReadPortWord(address) & (~(0xFF << byteShift))) | ((byteValue & 0xFF) << byteShift));
}
