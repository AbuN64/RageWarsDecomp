#include "include_asm.h"
#include "types.h"
#include "Common/os_timer_interrupt_internals.h"
#include <platform_sdk.h>
#include "Common/texture.h"
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

