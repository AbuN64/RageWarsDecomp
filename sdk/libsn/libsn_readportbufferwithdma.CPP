#include "TYPES.H"
#include "COMMON/LIBSN_AND_RESIDENT_CALLBACKS.H"
#include "IO/libsn_readportbufferwithdma.H"
#include "include_asm.h"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

int Libsn_ReadPortByte(int address) {
    u32 shift = (~address & 3) << 3;
    u32 word = Libsn_ReadPortWord(address & ~3);

    return (word >> shift) & 0xFF;
}

/* Signature follows the published cartridge word reader implementation. */


int Libsn_ReadTransferPortByte(int address) {
    int shift = (~address & 3) << 3;
    return ((u32)Libsn_ReadPortWord(address & -4) >> shift) & 0xFF;
}



void Libsn_ReadPortBuffer(s32 source, u8 *destination, u32 count) {
    while (count != 0 && (source & 3) != 0) {
        *destination++ = Libsn_ReadPortByte(source++);
        count--;
    }
    while (count >= 4) {
        u32 word = Libsn_ReadPortWord(source);
        *destination++ = word >> 24;
        *destination++ = word >> 16;
        *destination++ = word >> 8;
        *destination++ = word;
        source += 4;
        count -= 4;
    }
    while (count != 0) {
        *destination++ = Libsn_ReadPortByte(source++);
        count--;
    }
}

extern s32 g_staticDataRegionStart;
extern u8 g_libsnDmaRequest[],g_libsnDmaCompletionQueue[];

OSIoMesg;
struct OSMesgQueue;

void Libsn_ReadPortBufferWithDma(u32 address,u8 *out,u32 count) {
 s32 status = -(g_staticDataRegionStart == 0); u32 word;
 while(count!=0 && (address&3)!=0) { *out++=Libsn_ReadTransferPortByte(address++); count--; }
 while(count>3) {
  if(count>=16 && ((((u32)out&15)==0) & (status!=-1))) {
   status=osPiStartDma(g_libsnDmaRequest,1,0,address,out,count,g_libsnDmaCompletionQueue);
   if(status!=-1) { osRecvMesg(g_libsnDmaCompletionQueue,0,1); count=0; }
  } else {
   word=Libsn_ReadPortWord(address);
   *out++=word>>24; *out++=word>>16; *out++=word>>8; *out++=word;
   address+=4; count-=4;
  }
 }
 while(count!=0) { *out++=Libsn_ReadTransferPortByte(address++); count--; }
}
