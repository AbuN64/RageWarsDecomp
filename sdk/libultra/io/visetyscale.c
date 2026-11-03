#include "../../include/libgultra.h"
#include "COMMON/OSVISCALE.H"
#include "TYPES.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

extern __OSViContext *__osViNext;
void osViSetYScale(f32 yScale) {
    void *savedInterruptMask;
    savedInterruptMask = __osDisableInt();
    (((struct __OSViContext *) ((s8 *) __osViNext))->y.factor) = yScale;
    (((struct __OSViContext *) ((s8 *) __osViNext))->state) = (u16) ((((struct __OSViContext *) ((s8 *) __osViNext))->state) | 4);
    __osRestoreInt(savedInterruptMask);
}
