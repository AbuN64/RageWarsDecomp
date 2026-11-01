#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/OSTHREAD_S.H"
#include "COMMON/GUMTXL2F.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "../../include/libgultra/ai.h"
#include <ultra64.h>

/* aisetnextbuf.c */
/* Queues an audio buffer for the AI DMA, backing the address up 0x2000 bytes after a buffer that ended on an 8 KiB boundary, returning -1 when __osAiDeviceBusy reports the interface busy and zero after writing the physical address from osVirtualToPhysical and the length to the AI registers (libultra osAiSetNextBuffer). Adapted from __osSiRawReadIo with the argument checks replaced by the boundary flag byte g_audioDmaBoundaryWorkaroundFlag read through its array declaration, the busy test by __osAiDeviceBusy, and the uncached read by two AI register writes. */

s32 osAiSetNextBuffer(void *bufPtr, u32 size) {
    char *bptr = bufPtr;

    if (g_audioDmaBoundaryWorkaroundFlag[0] != 0) {
        bptr -= 0x2000;
    }
    if ((((u32)bufPtr + size) & 0x1FFF) == 0) {
        g_audioDmaBoundaryWorkaroundFlag[0] = 1;
    } else {
        g_audioDmaBoundaryWorkaroundFlag[0] = 0;
    }
    if (__osAiDeviceBusy() != 0) {
        return -1;
    }
    *(volatile u32 *)0xA4500000 = osVirtualToPhysical(bptr);
    *(volatile u32 *)0xA4500004 = size;
    return 0;
}

/* OSAISETNEXTBUFFER_DATA.CPP */
#if defined(VERSION_US_REV1)
unsigned int g_osaisetnextbufferDataConstantWords[8] = {
    0x00000010, 0x00000010, 0x00000020, 0x00000000, 0xC1200000, 0x00000000, 0x00000000, 0x00000000,
};

/* ROM-grounded data: src/ragewars_ai_boundary_flag_us_rev1.c */
#if defined(VERSION_US_REV1)
u8 g_osaisetnextbufferDataTextBytes = 0;
#endif
#endif
