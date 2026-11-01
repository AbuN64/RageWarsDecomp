#include "COMMON/RUNTIME_DECLARATIONS.H"
#include <ultra64.h>
#include "COMMON/ALFXPARAM.H"
#include "TYPES.H"
#include <PR/os_internal_rsp.h>
#include "../../../include/libgultra/sp.h"
#include "../../../include/libultra/debug/assert.h"
#include "include_asm.h"

/* sprawdma_text.c */
#if defined(VERSION_US)
char s_expandHudLabelFragment[14] =
    "MHUD_EXPANDHR\000";
#endif

#if defined(VERSION_US)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_EU_X)
unsigned short k_GSprawdmatextEncodedHalfwordsBlock1[7] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};
#endif

#if defined(VERSION_EU_X)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_EU)
unsigned short k_GSprawdmatextEncodedHalfwordsBlock1[7] = {
    0x0000, 0x41F0, 0x0000, 0x4180, 0x0000, 0x41F0, 0x0000,
};
#endif

#if defined(VERSION_EU)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_DE)
unsigned short k_GSprawdmatextEncodedHalfwords[7] = {
    0x0000, 0x0000, 0x0000, 0x4F00, 0x0000, 0x8E02, 0x0024,
};
#endif

/* sprawdma_bytes.c */
/* ROM-grounded data: src/k_sprawdmaTextBytes_Sprawdma.c */
const unsigned char k_sprawdmaTextBytes[3] = {
    0x45, 0x58, 0x00,
};

/* sprawdma_text.c */
#if !(defined(VERSION_US_REV1))
const char g_sprawdmaText[14] =
    "io/sprawdma.c\000";
#endif

#if defined(VERSION_DE)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/s_sprawdmaText_GSprawdmatext.c */
const char s_sprawdmaText[14] = "io/sprawdma.c";
#endif

/* sprawdma.c */
s32 __osSpRawStartDma(s32 direction, u32 deviceAddress, void *dramAddress, u32 size) {
    if (deviceAddress & 7) {
        __assert(&g_signalProcessorDmaAssertText, s_sprawdmaText, 0x3A);
    }
    if ((u32)dramAddress & 7) {
        __assert(&g_signalProcessorDmaAssertText, s_sprawdmaText, 0x3B);
    }
    if (size & 7) {
        __assert(&g_signalProcessorDmaAssertText, s_sprawdmaText, 0x3C);
    }
    if (__osSpDeviceBusy() != 0) {
        return -1;
    }
    IO_WRITE(0xA4040000U, deviceAddress);
    IO_WRITE(0xA4040004U, osVirtualToPhysical(dramAddress));
    if (direction == 0) {
        IO_WRITE(0xA404000CU, size - 1);
    } else {
        IO_WRITE(0xA4040008U, size - 1);
    }
    return 0;
}
