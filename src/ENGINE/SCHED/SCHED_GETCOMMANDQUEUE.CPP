#include "include_asm.h"
#include "COMMON/WORLDSORTENTRY.H"
#include "ENGINE/SCHED.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include <ultra64.h>
#include "COMMON/OSVISCALE.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "COMMON/LLDIVRESULT.H"
#include "TYPES.H"
#include "TYPES.H"
#include "COMMON/BOOT_TV_TYPE.H"
#include "../../../sdk/include/SCHED/osscremoveclient.H"
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
/** Return the address 0x78 bytes into the supplied object. */
void *Sched_GetCommandQueue(void *object) {
    SchedulerCommandQueueView *record = object;
    return &record->commandQueue;
}
