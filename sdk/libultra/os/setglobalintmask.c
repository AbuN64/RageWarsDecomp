#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "TYPES.H"
#include <ultra64.h>
#include <PR/os_internal_exception.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>



void __osSetGlobalIntMask(OSHWIntr interruptMask) {
    u32 mask;
    s32 *p;

    mask = __osDisableInt();
    p = &__OSGlobalIntMask;
    *p |= interruptMask;
    __osRestoreInt(mask);
}
