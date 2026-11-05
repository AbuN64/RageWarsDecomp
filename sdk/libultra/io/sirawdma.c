#include "include_asm.h"
#include "types.h"
#include "Common/controller_motor_state.h"
#include "Common/runtime_declarations.h"
#include <platform_sdk.h>
#include "../../include/libgultra.h"
#include "../../include/libultra/io/si.h"
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "../../include/libultra/debug/assert.h"
#include "Data/rest_source_records.h"
#include "Data/Ovl1_c/navigation_callback_address.h"

extern void osWritebackDCache(void *addr, s32 size);

extern void osInvalDCache(void *addr, s32 size);

/* G_CONSTANTSENCODEDWORDSBLOCK19.CPP */
/* g_ConstantsEncodedHalfwords.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: rodata/unresolved/800CCBF2 */
unsigned short g_ConstantsEncodedHalfwords[1] = {
    0xED50,
};
#endif

/* NAVIGATION_CALLBACK_ADDRESS.CPP */
#if defined(VERSION_US_REV1)
void * g_navGoalRouteTargetingCallbackAddresses[3] = {
    (void *)&addrLow_Nav_RebuildRequestedGoalRoute, (void *)&addrLow_Nav_CollectEnemyTargets, (void *)&addrLow_Target_UpdateTargetSelection,
};
#endif

/* sirawdma.c */
#if defined(VERSION_US)
char s_SirawdmaSMHUDEXPANDText[14] =
    "\000\015SMHUD_EXPAND";
#endif

#if defined(VERSION_US)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_EU_X)
unsigned short k_SirawdmaEncodedHalfwords[7] = {
    0xED70, 0x0020, 0xEB00, 0x0021, 0x0250, 0x0020, 0xF6E0,
};
#endif

#if defined(VERSION_EU_X)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_EU)
char s_SirawdmaTextsText[14] =
    " Texts\000\000\000\000\077\200\000\000";
#endif

#if defined(VERSION_EU)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_DE)
char s_SirawdmaIoSprawdmaText[14] =
    "\000\000io/sprawdma.";
#endif

/* libultradata.c */
/* ROM-grounded data: src/k_exText.c */
const unsigned char k_exText[3] = {
    0x45, 0x58, 0x00,
};

/* sirawdma.c */
#if !(defined(VERSION_US_REV1))
const char g_sirawdmaText[14] =
    "io/sirawdma.c\000";
#endif

#if defined(VERSION_DE)
/* bytes live in the preceding array */
#endif

#if defined(VERSION_US_REV1)
/* ROM-grounded data: src/SirawdmaTextSource.c */
const char s_sirawdmaText[14] = "io/sirawdma.c";
#endif

/* sirawdma.c */
s32 __osSiRawStartDma(s32 direction, void *dramAddr) {
    if ((u32)dramAddr & 3) {
        __assert(&g_serialDmaAssertText, s_sirawdmaText, 0x37);
    }
    if (__osSiDeviceBusy() != 0) {
        return -1;
    }
    if (direction == 1) {
        osWritebackDCache(dramAddr, 0x40);
    }
    IO_WRITE(0xA4800000U, osVirtualToPhysical(dramAddr));
    if (direction == 0) {
        IO_WRITE(0xA4800004U, 0x1FC007C0U);
    } else {
        IO_WRITE(0xA4800010U, 0x1FC007C0U);
    }
    if (direction == 0) {
        osInvalDCache(dramAddr, 0x40);
    }
    return 0;
}
