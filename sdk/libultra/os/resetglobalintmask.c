#include "TYPES.H"
#include "COMMON/OSTHREAD_S.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "COMMON/OS_TIMER_INTERRUPT_INTERNALS.H"
#include <ultra64.h>
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
