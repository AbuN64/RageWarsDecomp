#include "../../include/thread_queue.h"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RESIDENT_EVENT_HANDLER.H"
#include "IO/EXTERNS.H"
#include "TYPES.H"
#include "IO/libsn_disableinterrupts.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "COMMON/LIBSN_AND_RESIDENT_CALLBACKS.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "IO/libsn_readportbufferwithdma.H"
#include "IO/io_hostmemory.H"
#include "IO/DEBUG_MEMORY.H"
#include "IO/CONTROLLER_REQUEST.H"
#include "COMMON/OSTHREAD_S.H"
/* 80200B14_2.CPP */
void Libsn_WriteTransferPortByte(s32 address, unsigned char byteValue)
{
  int shiftedByte;
  s32 byteShift;
  shiftedByte = ((~address) & 3) * 8;
  address = address & (~3);
  byteShift = shiftedByte;
  Libsn_WritePortWord(address, (Libsn_ReadPortWord(address) & (~(0xFF << byteShift))) | (shiftedByte = (byteValue & 0xFF) << byteShift));
}
/* Copy an arbitrary byte buffer to a PI range, packing big-endian words. */
void Libsn_WritePortBuffer(s32 address, const u8 *source, u32 length)
{
  u32 word;
  while ((length != 0) && ((address & 3) != 0))
  {
    Libsn_WritePortByte(address++, *(source++));
 do { } while (0);
    length--;
  }

  if (length >= 4)
  {
    do
    {
      word = (((((u32) source[0]) << 24) | (((u32) source[1]) << 16)) | (((u32) source[2]) << 8)) | source[3];
      Libsn_WritePortWord(address, word);
      address += 4;
      source += 4;
      length -= 4;
    }
    while (length >= 4);
  }
  while (length != 0)
  {
    Libsn_WritePortByte(address++, *(source++));
    length--;
  }

}
extern volatile s32 g_staticDataRegionStart;
extern OSIoMesg g_libsnDmaRequest;
extern OSMesgQueue g_libsnDmaCompletionQueue;
extern s32 osPiStartDma(OSIoMesg *, s32, s32, u32, void *, u32, OSMesgQueue *);
/* Write an arbitrary byte stream to the device, using DMA when aligned
 * and falling back to byte/word writes if the DMA request is unavailable. */
void Libsn_WritePortBufferWithDma(u32 address, u8 *source, u32 remaining) {
    s32 dmaResult = -(g_staticDataRegionStart == 0);
    while (remaining != 0 && (address & 3) != 0) {
        Libsn_WriteTransferPortByte(address++, *source++);
        remaining--;
    }
    while (remaining >= 4) {
        if (remaining >= 16 && ((((u32)source & 15) == 0) & (dmaResult != -1))) {
            dmaResult = osPiStartDma(&g_libsnDmaRequest, 1, 1, address,
                source, remaining, &g_libsnDmaCompletionQueue);
            if (dmaResult != -1) {
                osRecvMesg(&g_libsnDmaCompletionQueue, 0, 1);
                remaining = 0;
            }
        } else {
            Libsn_WritePortWord(address, ((u32)source[0] << 24) |
                ((u32)source[1] << 16) | ((u32)source[2] << 8) | source[3]);
            address += 4;
            source += 4;
            remaining -= 4;
        }
    }
    while (remaining != 0) {
        Libsn_WriteTransferPortByte(address++, *source++);
        remaining--;
    }
}
/* io_hostmemory.CPP */
void Libsn_FillPortBytes(s32 address, s32 value, u32 count)
{
  u32 fillByte;
  u32 byte;
  unsigned char byteValue;
  u32 word;
  byteValue = value & 0xFF;
  while ((count != 0) && ((address & 3) != 0))
  {
    Libsn_WritePortByte(address++, byteValue);
    count--;
  }

  if (count >= 4)
  {
    byte = byteValue;
    fillByte = byte;
    word = (((byte << 24) | (byte << 16)) | (fillByte << 8)) | fillByte;
    do
    {
      Libsn_WritePortWord(address, word);
      count -= 4;
      address += 4;
    }
    while (count >= 4);
  }
  while (count)
  {
    Libsn_WritePortByte(address++, byteValue);
    count--;
  }

}
void Libsn_CopyPortBytes(s32 address, s32 port, s32 count) {
    s32 remaining, source, value;
    source = port;
    remaining = count - 1;
    if (count != 0) {
        do {
            value = Libsn_ReadPortByte(source++);
            Libsn_WritePortByte(address++, value & 0xFF);
            remaining--;
        } while (remaining != -1);
    }
}
extern void Libsn_EnumerateMemoryRanges(void);
extern u8 g_libsnHostAddressAdjustment[];
extern void Libsn_ReadPortBuffer(s32, u8 *, u32);
extern void Libsn_CopyPortToWordMemory(s32, s32, u32);
/* Split the debugger's memory transfer at permission boundaries. */
void Libsn_TransferHostMemoryRanges(u32 mode) {
    u32 address, remaining, chunk, flags, port;
    u32 i;
    Libsn_EnumerateMemoryRanges();
    port = 0xB1FE0000;
    address = Libsn_ReadPortWord(0xB1FFFFF4);
    remaining = Libsn_ReadPortWord(0xB1FFFFF8);
    if (address > 0xEFFFFFFF) address += (u32)g_libsnHostAddressAdjustment;
    while (remaining != 0) {
        i = 0;
        while (address < g_libsnHostMemoryRanges[i].first || address > g_libsnHostMemoryRanges[i].last) i++;
        if (i >= 48) {
            flags = 0;
            chunk = 0x1000 - (address & 0xFFF);
        } else {
            flags = g_libsnHostMemoryRanges[i].flags;
            chunk = (g_libsnHostMemoryRanges[i].last + 1) - address;
        }
        if (remaining < chunk) chunk = remaining;
        if ((flags & mode) == 0) {
            if (mode == 1) Libsn_FillPortBytes(port, 0, chunk);
        } else if (flags & 4) {
            if (mode == 1) Libsn_CopyPortBytes(port, address, chunk);
            else Libsn_CopyPortBytes(address, port, chunk);
        } else if (mode == 1) {
            Libsn_WritePortBuffer(port, address, chunk);
        } else if (flags & 8) {
            Libsn_CopyPortToWordMemory(port, address, chunk);
        } else {
            Libsn_ReadPortBuffer(port, (u8 *)address, chunk);
        }
        port += chunk;
        address += chunk;
        remaining -= chunk;
    }
}
/* Copy the block the debugger host announced (address at 0xB1FFFFF4, byte size at 0xB1FFFFF8) from its
 * 0xB1xxxxxx window onto the matching 0xB0xxxxxx address one word at a time, once the host signals ready at
 * 0xB0000010; the word index doubles as the ready poll result. */
void Libsn_CopyHostBlockToCart(void) {
    u32 address;
    u32 size;
    u32 index;

    address = Libsn_ReadPortWord(0xB1FFFFF4) & 0xB1FFFFFC;
    size = Libsn_ReadPortWord(0xB1FFFFF8) & 0x01FFFFFC;
    Libsn_WritePortWord(0xB1FFFFFC, 0);
    while ((index = Libsn_ReadPortWord(0xB0000010)) == 0) {
        Libsn_SpinDelay(500);
    }
    index = 0;
    if (size >> 2 != 0) {
        do {
            Libsn_WritePortWord((address & 0xB07FFFFF) + index * 4, Libsn_ReadPortWord(address + index * 4));
        } while (++index < size >> 2);
    }
    Libsn_SpinDelay(2000);
    Libsn_WritePortWord(0xB1FFFFF4, 0);
}
/* 802013D8.CPP */
extern u8 g_libsnMonitorResumeMask;
extern void Libsn_InstallDebuggerExceptionHooks(void);
void Libsn_InitializeHostMemoryAccess(void) {
    s32 saved;
    u32 size;
    saved = Libsn_DisableInterrupts();
    Libsn_InstallDebuggerExceptionHooks();
    Libsn_WritePortWord(0xB1FFFFF0, 0);
    Libsn_WritePortWord(0xB1FFFFFC, 0);
    size = *(u32 *)0x80000318;
    g_libsnMonitorEnabled = 1;
    g_libsnMonitorResumeMask = 0xFF;
    if (size > 0x3FFFFFU) {
        if (((size & 0x1FFFF) == 0) & (size <= 0x02000000U)) {
            size--;
            g_libsnDefaultMemoryRanges[1].last = size - 0x80000000;
            g_libsnDefaultMemoryRanges[3].last = size + 0xA0000000;
        }
    }
    Libsn_RestoreInterruptEnable(saved);
}
extern int Libgultra_TrwGetSr(void);
extern void Libgultra_TrwSetSr(int);
extern u32 g_libsnMonitorStatusFlags;
/* Host-command service loop: poll the command word at 0xB1FFFFF0, acknowledge it and run it. */
void Libsn_ServiceHostCommands(void) {
    s32 keepRunning;
    s32 command;
    do {
        keepRunning = 1;
        while ((command = Libsn_ReadPortWord(0xB1FFFFF0)) == 0) {
            Libsn_SpinDelay(1000);
        }
        if (command == 2) {
            Libsn_WritePortWord(0xB1FFFFFC, 0);
            Libsn_SpinDelay(1000);
            continue;
        }
        Libsn_WritePortWord(0xB1FFFFFC, 0x101);
        while (Libsn_ReadPortWord(0xB1FFFFF0) == command) {
            Libsn_SpinDelay(500);
        }
        if (Libsn_ReadPortWord(0xB1FFFFF0) == 2) {
            Libsn_WritePortWord(0xB1FFFFFC, 0);
            continue;
        }
        switch (command) {
        case 0x10:
            break;
        case 0x11:
            keepRunning = 0;
            break;
        case 0x12:
            g_libsnMonitorStatusFlags &= ~1U;
            g_libsnMonitorEnabled = 0;
            g_libsnMonitorResumeMask = 0;
            Libgultra_TrwSetSr(Libgultra_TrwGetSr() & ~1);
            break;
        case 0x13:
            g_libsnMonitorResumeMask = 0;
            g_libsnMonitorEnabled = 0;
            break;
        case 0x14:
            g_libsnMonitorResumeMask = 0xFF;
            break;
        case 0x15:
            g_libsnMonitorResumeMask = 0;
            break;
        case 0x16:
            Libsn_WritePortWord(0xB1FE0000, (g_libsnMonitorResumeMask << 24) | ((u8)g_libsnMonitorEnabled << 16));
            break;
        case 0x17:
            Libsn_TransferHostMemoryRanges(2);
            break;
        case 0x18:
            Libsn_TransferHostMemoryRanges(1);
            break;
        case 0x19:
            Libsn_CopyHostBlockToCart();
            break;
        }
        Libsn_WritePortWord(0xB1FFFFFC, 0);
        while (Libsn_ReadPortWord(0xB1FFFFF0) == 1) {
            Libsn_SpinDelay(500);
        }
    } while (keepRunning != 0 || g_libsnMonitorResumeMask == 0);
    Libsn_WritePortWord(0xB1FFFFF0, 0);
}
/* 802013D8_2.CPP */
/** Return strlen(string) + 1 (byte count including the terminating NUL). */
s32 Libsn_MeasureTerminatedString(u8 *string) {
    u8 *cursor;
    u8 temp;

    cursor = string + 1;
    if (*string != 0) {
        do {
            temp = *cursor;
            cursor += 1;
        } while (temp != 0);
    }
    return cursor - string;
}
/* Shared declarations of the host request code below. */
extern void g_libsnRunHostRequestThreadEntry(void *); /* host request thread entry, as the ROM stores its address */
extern s32 g_libsnHostTransportMode;
extern void *g_libsnHostEventMessage;
extern OSMesgQueue g_libsnHostEventQueue;
extern void *g_libsnHostRequestMessage;
extern void *g_libsnDmaCompletionMessage;
extern OSMesgQueue g_libsnHostRequestQueue;
extern void *g_libsnHostReplyMessage;
extern OSThread g_libsnHostRequestThread; /* host request thread */
extern OSMesgQueue g_libsnHostReplyQueue;
 /* osSetEventMesg */
extern void Libsn_ReadPortBufferWithDma(u32, u8 *, u32);
/* Create the host request queues and start the request thread once (thread id FS). */
void Libsn_InitializeHostRequestThread(s32 threadPriority) {
    if (g_staticDataRegionStart == 0) {
        g_staticDataRegionStart = 1;
        osCreateMesgQueue(&g_libsnDmaCompletionQueue, &g_libsnDmaCompletionMessage, 1);
        osCreateMesgQueue(&g_libsnHostRequestQueue, &g_libsnHostRequestMessage, 1);
        osCreateMesgQueue(&g_libsnHostReplyQueue, &g_libsnHostReplyMessage, 1);
        osCreateMesgQueue(&g_libsnHostEventQueue, &g_libsnHostEventMessage, 1);
        osSetEventMesg(0, &g_libsnHostEventQueue, (void *)1);
        osCreateThread(&g_libsnHostRequestThread, 0x4653, g_libsnRunHostRequestThreadEntry, 0, (u8 *)&g_libsnDmaRequest - 0x30, threadPriority);
        osStartThread(&g_libsnHostRequestThread);
    }
}
/* Host monitor call: writes the three arguments and then the command word to the SN cart port, polls until
   the host clears the command (a set error word raises SN's debugger trap `break 1`; cc1 has no construct
   for it, SN wrote it inline in their runtime: the only `break 1` in the ROM) and returns the host's reply. */
s32 Libsn_SendHostCommand(s32 command, s32 firstArgument, s32 secondArgument, s32 thirdArgument) {
    Libsn_WritePortWord(0xB1FFFFE4, firstArgument);
    Libsn_WritePortWord(0xB1FFFFE8, secondArgument);
    Libsn_WritePortWord(0xB1FFFFEC, thirdArgument);
    Libsn_WritePortWord(0xB1FFFFE0, command);
    do {
        Libsn_SpinDelay(0x3E8);
        if (Libsn_ReadPortWord(0xB1FFFFF0) != 0) {
#if defined(__i386__) || defined(__x86_64__)
            __builtin_trap();
#else
            __asm__ volatile ("break 1");
#endif
        }
    } while (Libsn_ReadPortWord(0xB1FFFFE0) != 0);
    return Libsn_ReadPortWord(0xB1FFFFDC);
}
void Libsn_RunHostRequestThread(void) {
    ControllerRequest *request;
    for (;;) {
        osRecvMesg(&g_libsnHostRequestQueue, (OSMesg *)&request, 1);
        if (request->status != 0 && request->reserved == 1) {
            if (request->command & 0x80000000) {
                g_staticDataRegionStart = 0;
            }
            Libsn_WritePortBufferWithDma(0xB1FF0000, (u8 *)request->header, request->status);
            if (request->command & 0x80000000) {
                g_staticDataRegionStart = 1;
            }
        }
        osRecvMesg(&g_libsnHostEventQueue, 0, 0);
        Libsn_WritePortWord(0xB1FFFFE4, request->argument0);
        Libsn_WritePortWord(0xB1FFFFE8, request->argument1);
        Libsn_WritePortWord(0xB1FFFFEC, request->argument2);
        Libsn_WritePortWord(0xB1FFFFD8, 0x01010101);
        Libsn_WritePortWord(0xB1FFFFE0, (u16)request->command);
        osRecvMesg(&g_libsnHostEventQueue, 0, 1);
        if (request->status != 0 && request->reserved == 0) {
            s32 length = Libsn_ReadPortWord(0xB1FFFFDC);
            if (length != 0) {
                if (request->command & 0x80000000) {
                    g_staticDataRegionStart = 0;
                }
                Libsn_ReadPortBufferWithDma(0xB1FF0000, (u8 *)request->header, length);
                if (request->command & 0x80000000) {
                    g_staticDataRegionStart = 1;
                }
            }
        }
        if (request->reply != 0) {
            osSendMesg(request->reply, (OSMesg)Libsn_ReadPortWord(0xB1FFFFDC), 1);
        }
    }
}
/* Issue the monitor command with interrupts disabled, then restore them. */
s32 Libsn_InitializePollingHost(void)
{
    s32 previous;
    s32 result;
    previous = Libsn_DisableInterrupts();
    g_libsnHostTransportMode = 1;
    result = Libsn_SendHostCommand(0x101, 0, 0, 0);
    Libsn_RestoreInterruptEnable(previous);
    return result;
}
void *Libsn_InitializeQueuedHost(void) {
    ControllerRequest request;
    ControllerResponse response;
    g_libsnHostTransportMode = 2;
    Libsn_InitializeHostRequestThread(0xFF);
    request.status = 0;
    request.command = 0x80000101;
    request.argument0 = 0;
    request.argument1 = 0;
    request.argument2 = 0;
    request.reply = &g_libsnHostReplyQueue;
    osSendMesg(&g_libsnHostRequestQueue, &request, 1);
    osRecvMesg(&g_libsnHostReplyQueue, &response.message, 1);
    return response.message;
}
u32 Libsn_SendHostStringRequest(u8 *buffer, s32 argument) {
    ControllerRequest request;
    ControllerResponse response;
    s32 length;
    s32 saved;
    length = Libsn_MeasureTerminatedString(buffer);
    if (g_libsnHostTransportMode == 2) {
        request.status = length;
        request.argument0 = length;
        request.header = (u32)buffer;
        request.reserved = 1;
        request.command = 0x80000202;
        request.argument1 = argument;
        request.argument2 = 0;
        request.reply = &g_libsnHostReplyQueue;
        osSendMesg(&g_libsnHostRequestQueue, &request, 1);
        osRecvMesg(&g_libsnHostReplyQueue, &response.message, 1);
        if (response.status & 0x8000) {
            response.status |= 0xFFFF0000;
        }
    } else {
        saved = Libsn_DisableInterrupts();
        length = Libsn_MeasureTerminatedString(buffer);
        Libsn_WritePortBuffer(0xB1FF0000, buffer, length);
        response.status = Libsn_SendHostCommand(0x202, length, argument, 0);
        if (response.status & 0x8000) {
            response.status |= 0xFFFF0000;
        }
        Libsn_RestoreInterruptEnable(saved);
    }
    return response.status;
}
s32 Libsn_SendHostNameFlags(u8 *name, u32 flags) {
    ControllerRequest request;
    ControllerResponse response;
    s32 length;
    s32 saved;
    length = Libsn_MeasureTerminatedString(name);
    if (g_libsnHostTransportMode == 2) {
        request.status = length;
        request.argument0 = length;
        request.header = (u32)name;
        request.reserved = 1;
        request.command = 0x80000303;
        request.argument1 = flags;
        request.argument2 = 0;
        request.reply = &g_libsnHostReplyQueue;
        osSendMesg(&g_libsnHostRequestQueue, &request, 1);
        osRecvMesg(&g_libsnHostReplyQueue, &response.message, 1);
        if (response.status & 0x8000) {
            response.status |= 0xFFFF0000;
        }
    } else {
        saved = Libsn_DisableInterrupts();
        length = Libsn_MeasureTerminatedString(name);
        Libsn_WritePortBuffer(0xB1FF0000, name, length);
        response.status = Libsn_SendHostCommand(0x303, length, flags, 0);
        if (response.status & 0x8000) {
            response.status |= 0xFFFF0000;
        }
        Libsn_RestoreInterruptEnable(saved);
    }
    return response.status;
}
s32 Libsn_SendHostScalarRequest(s32 argument) {
    ControllerRequest request;
    ControllerResponse response;
    s32 saved;
    if (g_libsnHostTransportMode == 2) {
        request.argument0 = argument;
        request.status = 0;
        request.command = 0x80000404;
        request.argument1 = 0;
        request.argument2 = 0;
        request.reply = &g_libsnHostReplyQueue;
        osSendMesg(&g_libsnHostRequestQueue, &request, 1);
        osRecvMesg(&g_libsnHostReplyQueue, &response.message, 1);
        if (response.status & 0x8000) {
            response.status |= 0xFFFF0000;
        }
    } else {
        saved = Libsn_DisableInterrupts();
        response.status = Libsn_SendHostCommand(0x404, argument, 0, 0);
        if (response.status & 0x8000) {
            response.status |= 0xFFFF0000;
        }
        Libsn_RestoreInterruptEnable(saved);
    }
    return response.status;
}
s32 Libsn_ReadHostChannel(s32 channel, u8 *destination, u32 remaining) {
    ControllerRequest request;
    ControllerResponse response;
    s32 total = 0;
    s32 saved;
    u32 chunk;
    if (g_libsnHostTransportMode == 2) {
        while (remaining != 0) {
            chunk = remaining;
            if (chunk > 0x8000) {
                chunk = 0x8000;
            }
            request.header = (u32)destination;
            request.status = 1;
            request.reserved = 0;
            request.command = 0x80000505;
            request.argument0 = channel;
            request.argument1 = chunk;
            request.argument2 = 0;
            request.reply = &g_libsnHostReplyQueue;
            osSendMesg(&g_libsnHostRequestQueue, &request, 1);
            osRecvMesg(&g_libsnHostReplyQueue, &response.message, 1);
            if (response.status == 0) {
                return total;
            }
            destination += response.status;
            total += response.status;
            remaining -= response.status;
        }
    } else {
        saved = Libsn_DisableInterrupts();
        while (remaining != 0) {
            chunk = remaining;
            if (chunk > 0x8000) {
                chunk = 0x8000;
            }
            response.status = Libsn_SendHostCommand(0x505, channel, chunk, 0);
            if (response.status == 0) {
                break;
            }
            Libsn_ReadPortBuffer(0xB1FF0000, destination, response.status);
            destination += response.status;
            total += response.status;
            remaining -= response.status;
        }
        Libsn_RestoreInterruptEnable(saved);
    }
    return total;
}
s32 Libsn_WriteHostChannel(s32 channel, u8 *source, u32 remaining) {
    ControllerRequest request;
    ControllerResponse response;
    s32 total = 0;
    s32 saved;
    u32 chunk;
    if (g_libsnHostTransportMode == 2) {
        while (remaining != 0) {
            chunk = remaining;
            if (chunk > 0x8000) chunk = 0x8000;
            request.header = (u32)source;
            request.status = chunk;
            request.reserved = 1;
            request.command = 0x80000606;
            request.argument0 = channel;
            request.argument1 = chunk;
            request.argument2 = 0;
            request.reply = &g_libsnHostReplyQueue;
            osSendMesg(&g_libsnHostRequestQueue, &request, 1);
            osRecvMesg(&g_libsnHostReplyQueue, &response.message, 1);
            if (response.status == 0) return total;
            source += response.status;
            total += response.status;
            remaining -= response.status;
        }
    } else {
        saved = Libsn_DisableInterrupts();
        while (remaining != 0) {
            chunk = remaining;
            if (chunk > 0x8000) chunk = 0x8000;
            Libsn_WritePortBuffer(0xB1FF0000, source, chunk);
            response.status = Libsn_SendHostCommand(0x606, channel, chunk, 0);
            if (response.status == 0) break;
            source += response.status;
            total += response.status;
            remaining -= response.status;
        }
        Libsn_RestoreInterruptEnable(saved);
    }
    return total;
}
s32 Libsn_SendHostTripleRequest(s32 firstArgument, u32 secondArgument, s32 thirdArgument) {
    ControllerRequest request;
    ControllerResponse response;
    s32 saved;
    if (g_libsnHostTransportMode == 2) {
        request.argument0 = firstArgument;
        request.status = 0;
        request.command = 0x80000707;
        request.argument1 = secondArgument;
        request.argument2 = thirdArgument;
        request.reply = &g_libsnHostReplyQueue;
        osSendMesg(&g_libsnHostRequestQueue, &request, 1);
        osRecvMesg(&g_libsnHostReplyQueue, &response.message, 1);
    } else {
        saved = Libsn_DisableInterrupts();
        response.status = Libsn_SendHostCommand(0x707, firstArgument, secondArgument, thirdArgument);
        Libsn_RestoreInterruptEnable(saved);
    }
    return response.status;
}
