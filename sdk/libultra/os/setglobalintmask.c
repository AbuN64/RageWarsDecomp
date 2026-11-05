#include "Common/runtime_declarations.h"
#include "Common/boot_memory_and_thread_boundaries.h"
#include "types.h"
#include <platform_sdk.h>
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
