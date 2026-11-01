#include "../../include/libgultra.h"
#include "COMMON/OSVISCALE.H"
#include "TYPES.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

extern void *__osViNext;
void osViSetYScale(f32 yScale) {
    void *savedInterruptMask;
    savedInterruptMask = __osDisableInt();
    (((struct ViVerticalScaleView *) ((s8 *) __osViNext))->yScaleFactor) = yScale;
    (((struct ViVerticalScaleView *) ((s8 *) __osViNext))->state) = (u16) ((((struct ViVerticalScaleView *) ((s8 *) __osViNext))->state) | 4);
    __osRestoreInt(savedInterruptMask);
}
