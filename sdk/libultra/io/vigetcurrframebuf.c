#include "Common/boot_tv_type.h"
#include "Common/osviscale.h"
#include "types.h"
#include "Common/os_timer_interrupt_internals.h"
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

extern __OSViContext *__osViCurr;

void *osViGetCurrentFramebuffer(void) {
    void *saveMask = __osDisableInt();
    void *framep = __osViCurr->framep;
    __osRestoreInt(saveMask);
    return framep;
}
