#include "Common/ospihandle_s.h"
#include <platform_sdk.h>
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Gamecore/externs.h"
#include "../../include/libultra/io/epirawread.H"
#include "../../include/libultra/debug/assert.h"
#include "include_asm.h"
#include "Common/alfxparam.h"

/* epirawread.c */
extern OSPiHandle *g_peripheralDomainHandles[];

s32 osEPiRawReadIo(struct OSPiHandle_s *piHandle, u32 deviceOffset, u32 *outputWord) {
    OSPiHandle *previous;
    s32 index;

    if (outputWord == 0) {
        __assert(&g_extendedPeripheralReadAssertText, s_epirawreadText, 0x2B);
    }
    while (IO_READ(PI_STATUS_REG) & 3) {
    }
    index = piHandle->domain;
    previous = g_peripheralDomainHandles[index];
    if (previous != piHandle) {
        if (index == 0) {
            if (previous->latency != piHandle->latency) {
                IO_WRITE(0xA4600014U, piHandle->latency);
            }
            if (previous->pageSize != piHandle->pageSize) {
                IO_WRITE(0xA460001CU, piHandle->pageSize);
            }
            if (previous->relDuration != piHandle->relDuration) {
                IO_WRITE(0xA4600020U, piHandle->relDuration);
            }
            if (previous->pulse != piHandle->pulse) {
                IO_WRITE(0xA4600018U, piHandle->pulse);
            }
        } else {
            if (previous->latency != piHandle->latency) {
                IO_WRITE(0xA4600024U, piHandle->latency);
            }
            if (previous->pageSize != piHandle->pageSize) {
                IO_WRITE(0xA460002CU, piHandle->pageSize);
            }
            if (previous->relDuration != piHandle->relDuration) {
                IO_WRITE(0xA4600030U, piHandle->relDuration);
            }
            if (previous->pulse != piHandle->pulse) {
                IO_WRITE(0xA4600028U, piHandle->pulse);
            }
        }
        g_peripheralDomainHandles[index] = piHandle;
    }
    *outputWord = IO_READ(piHandle->baseAddress | deviceOffset | 0xA0000000U);
    return 0;
}

/* EPIRAWREAD.CPP */
/* 800CC694_36.CPP */

/* 800CC694_37.CPP */
/* ROM-grounded data: src/ragewars_resident_strings_CD7A4_us_rev1.c */
#if defined(VERSION_US)
unsigned int k_EpirawreadEncodedWords[3] = {
    0x66000000, 0x04000000, 0x0000082E,
};
#endif

/* 802BE040_13.CPP */
/* 802BE040_13.CPP */

/* 802C0390_16.CPP */

/* 802BE040_9.CPP */

/* EPIRAWREAD_STRINGS.CPP */
#if defined(VERSION_EU)
const unsigned int k_systemRunPiManagerJumpTableTrailingWord = 0x41800000U;
#endif

const unsigned char s_epirawreadExText[3] = {
    0x45, 0x58, 0x00,
};
const char s_epirawreadText[16] = "io/epirawread.c";

/* PI_RAW_READ_SOURCE_NAME.CPP */
#if defined(VERSION_DE)
char g_piRawReadSourceName[12] = "io/pirawread";
#endif
