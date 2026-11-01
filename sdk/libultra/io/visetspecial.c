#include "COMMON/BOOT_TV_TYPE.H"
#include <PR/abi.h>
#include "COMMON/OSVISCALE.H"
#include "TYPES.H"
#include "COMMON/OS_TIMER_INTERRUPT_INTERNALS.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

extern StateosViSetSpecialFeatures *__osViNext;

void osViSetSpecialFeatures(u32 featureCommands) {
    u32 token;

    token = __osDisableInt();
    if (featureCommands & 1) {
        __osViNext->flags |= 8;
    }
    if (featureCommands & 2) {
        __osViNext->flags &= ~8;
    }
    if (featureCommands & 4) {
        __osViNext->flags |= 4;
    }
    if (featureCommands & 8) {
        __osViNext->flags &= ~4;
    }
    if (featureCommands & 0x10) {
        __osViNext->flags |= 0x10;
    }
    if (featureCommands & 0x20) {
        __osViNext->flags &= ~0x10;
    }
    if (featureCommands & 0x40) {
        __osViNext->flags = (__osViNext->flags | 0x10000) & ~0x300;
    }
    if (featureCommands & 0x80) {
        __osViNext->flags &= ~0x10000;
        __osViNext->flags |= __osViNext->inner->w1 & 0x300;
    }
    __osViNext->status |= 8;
    __osRestoreInt(token);
}
