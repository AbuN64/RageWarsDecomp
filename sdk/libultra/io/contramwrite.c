#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/CONTREADFORMAT.H"
#include "COMMON/CONTROLLER_MOTOR_STATE.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "../../include/OS/__OSPACKRAMWRITEDATA.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "../../include/os_pif.h"
#include "include_asm.h"

/* 802BD950.CPP */
/* Writes a 32-byte block to a controller pak address through the PIF RAM, re-reading the reply up to three times until the data CRC matches, and returns 0, 1 for no pak, 4 for a CRC failure or the pak status error (libultra __osContRamWrite). Adapted from __osContRamRead with the read command 2 changed to the write command 3 packed by __osPackRamWriteData, a guard returning 0 for label-area addresses below 7 unless forced, the CRC taken over the caller's buffer with no copy back, and the DMA results assigned to the result as libultra does. */

extern u32 __osPfsGetStatus(s32 queue, s32 channel);

u32 __osContRamWrite(s32 completionQueue, s32 channel, u16 blockAddress, u8 *inputData, s32 forceWrite) {
    Block40 saved;
    u8 *source;
    s32 i;
    s32 retries;
    u32 result;

    retries = 2;
    if (forceWrite != 1 && blockAddress < 7 && blockAddress != 0) {
        return 0;
    }
    __osSiGetAccess();
    g_controllerLastCommand = 3;
    __osPackRamWriteData(channel, blockAddress & 0xFFFF, inputData);
    result = __osSiRawStartDma(1, (u8 *)&g_controllerStatusPifBuffer);
    osRecvMesg(completionQueue, 0, 1);
    do {
        result = __osSiRawStartDma(0, (u8 *)&g_controllerStatusPifBuffer);
        osRecvMesg(completionQueue, 0, 1);
        source = (u8 *)&g_controllerStatusPifBuffer;
        if (channel != 0) {
            i = 0;
            if (channel > 0) {
                do {
                    i++;
                    source++;
                } while (i < channel);
            }
        }
        saved = *(Block40 *)source;
        result = (saved.bytes[2] & 0xC0) >> 4;
        if (result == 0) {
            if ((__osContDataCrc(inputData) & 0xFF) != saved.bytes[0x26]) {
                result = __osPfsGetStatus(completionQueue, channel);
                if (result != 0) {
                    break;
                }
                result = 4;
            }
        } else {
            result = 1;
        }
        if (result != 4) {
            break;
        }
    } while (retries-- >= 0);
    __osSiRelAccess();
    return result;
}

/* 802BD950_2.CPP */
extern u32 __osContAddressCrc(u32 blockAddress);

void __osPackRamWriteData(s32 channel, s32 blockAddress, u8 *inputData) {
    Block40 packet;
    u8 *dst;
    s32 i;
    u8 tail;
    u32 checksum;
    s32 shifted;

    dst = (u8 *)&g_controllerStatusPifBuffer;
    tail = 0xFF;
    g_controllerStatusPifBuffer.pifstatus = 1;
    packet.bytes[0] = tail;
    packet.bytes[1] = 0x23;
    packet.bytes[2] = 1;
    packet.bytes[3] = 3;
    checksum = __osContAddressCrc(blockAddress & 0xFFFF);
    shifted = blockAddress << 5;
    *(u16 *)&packet.bytes[4] = (checksum & 0xFF) | shifted;
    packet.bytes[0x26] = tail;
    i = 0;
    do {
        ((Block40 *)((u8 *)&packet + i))->bytes[6] = *inputData++;
        i++;
    } while (i < 0x20);
    if (channel != 0) {
        i = 0;
        if (channel > 0) {
            do {
                *dst++ = 0;
                i++;
            } while (i < channel);
        }
    }
    *(Block40 *)dst = packet;
    dst[0x28] = 0xFE;
}

#if defined(VERSION_US)
/* Zero word ending contramwrite's object; no instruction reads it. */
unsigned int g_osPackRamWriteDataZeroTail[1] = {
    0x00000000,
};
#endif

