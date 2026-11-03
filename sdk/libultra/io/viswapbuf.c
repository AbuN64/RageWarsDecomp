#include "include_asm.h"
#include "../../include/libgultra.h"
#include "COMMON/OSVISCALE.H"
#include "TYPES.H"
#include <ultra64.h>
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

