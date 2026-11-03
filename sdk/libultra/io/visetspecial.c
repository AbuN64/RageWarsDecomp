#include "COMMON/BOOT_TV_TYPE.H"
#include <PR/abi.h>
#include "COMMON/OSVISCALE.H"
#include "TYPES.H"
#include "COMMON/OS_TIMER_INTERRUPT_INTERNALS.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

extern __OSViContext *__osViNext;

void osViSetSpecialFeatures(u32 featureCommands) {
    u32 token;

    token = __osDisableInt();
    if (featureCommands & 1) {
        __osViNext->control |= 8;
    }
    if (featureCommands & 2) {
        __osViNext->control &= ~8;
    }
    if (featureCommands & 4) {
        __osViNext->control |= 4;
    }
    if (featureCommands & 8) {
        __osViNext->control &= ~4;
    }
    if (featureCommands & 0x10) {
        __osViNext->control |= 0x10;
    }
    if (featureCommands & 0x20) {
        __osViNext->control &= ~0x10;
    }
    if (featureCommands & 0x40) {
        __osViNext->control = (__osViNext->control | 0x10000) & ~0x300;
    }
    if (featureCommands & 0x80) {
        __osViNext->control &= ~0x10000;
        __osViNext->control |= __osViNext->modep->comRegs.ctrl & 0x300;
    }
    __osViNext->state |= 8;
    __osRestoreInt(token);
}
