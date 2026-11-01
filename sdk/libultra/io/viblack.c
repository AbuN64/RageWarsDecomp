#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/OS_TIMER_INTERRUPT_INTERNALS.H"
#include <ultra64.h>
#include "COMMON/TEXTURE.H"
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

extern void *__osViNext;

void osViBlack(u8 blackEnabled) {
    u32 savedInterruptMask;
    u16 *ptr;
    u16 v;

    savedInterruptMask = __osDisableInt();
    if (blackEnabled & 0xFF) {
        ptr = (u16 *)__osViNext;
        v = *ptr | 0x20;
    } else {
        ptr = (u16 *)__osViNext;
        v = *ptr & 0xFFDF;
    }
    *ptr = v;
    __osRestoreInt(savedInterruptMask);
}

