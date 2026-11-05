#include "Common/externs.h"
#include "Common/osthread_s.h"
#include "types.h"
#include "Common/runtime_declarations.h"
#include "Common/os_timer_interrupt_internals.h"
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>



u64 osGetTime(void) {
    u32 saved;
    u32 count;
    u32 elapsed;
    u64 time;

    saved = __osDisableInt();
    count = osGetCount();
    elapsed = count - __osBaseCounter;
    time = __osCurrentTime;
    __osRestoreInt(saved);
    return time + elapsed;
}
