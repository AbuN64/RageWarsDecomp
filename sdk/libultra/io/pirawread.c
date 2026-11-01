#include "include_asm.h"
#include "COMMON/OSPIHANDLE_S.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"
#include "COMMON/ALFXPARAM.H"
#include "../../include/libultra/io/pirawread.H"
#include "../../include/libultra/debug/assert.h"

/* pirawread.c */
s32 osPiRawReadIo(s32 deviceOffset, s32 *outputWord) {
    u32 status;

    if (outputWord == 0) {
        __assert(&g_peripheralReadAssertText, s_pirawreadText, 0x3D);
    }
    status = *(volatile u32 *)0xA4600010;
    while (status & 3) {
        status = *(volatile u32 *)0xA4600010;
    }
    *outputWord = *(s32 *)(g_cartridgeRomBaseAddress | deviceOffset | 0xA0000000);
    return 0;
}

/* OSPIRAWREADIO_DATA.CPP */
/* ROM-grounded data: src/k_osPiRawReadIoTextBytes.c */
const unsigned char k_osPiRawReadIoTextBytes[3] = {
    0x45, 0x58, 0x00,
};

/* PIRAWREAD.CPP */
#if !(defined(VERSION_US_REV1))
const char g_pirawreadText[15] =
    "io/pirawread.c\000";
#endif

#if defined(VERSION_US)
unsigned char k_PirawreadEncodedBytes[13] = {
    0x0F, 0x00, 0x0A, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, 0x2E, 0x31, 0x37, 0x35,
};
#endif

#if defined(VERSION_US)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_EU_X)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_EU)
unsigned char k_PirawreadEncodedBytesBlock1[13] = {
    0x00, 0x4F, 0x00, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00,
};
#endif

#if defined(VERSION_EU)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_DE)
char s_PirawreadIoSirawdmaText[13] =
    "\000io/sirawdma.";
#endif

#if defined(VERSION_DE)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/s_pirawreadText_Pirawread.c */
const char s_pirawreadText[15] =
    "io/pirawread.c";
#endif
