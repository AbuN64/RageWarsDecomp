#include "types.h"
#include "Common/osthread_s.h"
#include "Common/boot_memory_and_thread_boundaries.h"
#include "Common/os_timer_interrupt_internals.h"
#include <platform_sdk.h>
#include <PR/os_internal_exception.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

/* 802C0390_6.CPP */

/* 802C04C0.CPP */
void __osResetGlobalIntMask(OSHWIntr interruptMask) {
    u32 savedInterruptMask;
    s32 *p;

    savedInterruptMask = __osDisableInt();
    p = &__OSGlobalIntMask;
    *p &= ~interruptMask | 0x401;
    __osRestoreInt(savedInterruptMask);
}
