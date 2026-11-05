#include "include_asm.h"
#include "../../include/libgultra.h"
#include "Common/osviscale.h"
#include "types.h"
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

extern __OSViContext *__osViNext;

void osViSwapBuffer(void *framebuffer) {
    u32 savedMask;

    savedMask = __osDisableInt();
    __osViNext->framep = framebuffer;
    __osViNext->state |= 0x10;
    __osRestoreInt(savedMask);
}

