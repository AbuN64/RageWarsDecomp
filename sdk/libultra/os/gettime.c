#include "COMMON/EXTERNS.H"
#include "COMMON/OSTHREAD_S.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "COMMON/OS_TIMER_INTERRUPT_INTERNALS.H"
#include <ultra64.h>
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
