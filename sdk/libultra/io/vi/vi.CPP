#include "include_asm.h"
#include "Common/boot_tv_type.h"
#include <platform_sdk.h>
#include "Common/osviscale.h"
#include "types.h"
#include "../../../include/AUDIO/vi.H"
#include "../../../include/AUDIO/__OSVISWAPCONTEXT.H"
#include "Ui/X_files/x_plus.h"
#include "../../../include/libultra/audio/vi.h"

extern __OSViContext *__osViCurr;
extern __OSViContext *__osViNext;

void __osViInit(void)
{
    __OSViContext *contexts = g_videoInterfaceContexts;
    s32 tv_type;

    XPlus_FillMemory(contexts, 0, sizeof(g_videoInterfaceContexts));
    tv_type = g_consoleTvType;
    __osViCurr = &contexts[0];
    __osViNext = &contexts[1];
    contexts[1].retraceCount = 1;
    contexts[0].retraceCount = 1;
    contexts[1].framep = (void *)0x80000000U;
    contexts[0].framep = (void *)0x80000000U;
    if (tv_type == 0) {
        contexts[1].modep = &g_videoInterfaceModeDefault;
    } else if (tv_type == 2) {
        contexts[1].modep = &g_videoInterfaceModeAlternate;
    } else {
        contexts[1].modep = osViModeTable;
    }
    __osViNext->state = 0x20;
    __osViNext->control = __osViNext->modep->comRegs.ctrl;
    while (IO_READ(0xA4400010U) > 10) {
    }
    IO_WRITE(0xA4400000U, 0);
    __osViSwapContext();
}
