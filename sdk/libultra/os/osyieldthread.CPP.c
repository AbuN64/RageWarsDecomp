#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "COMMON/LONE/OS_RUNNABLE_THREAD_QUEUE.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/NODERECAT1C.H"
#include "TYPES.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

/* osyieldthread.CPP */
extern s32 __osProbeTLB(void);

u32 osVirtualToPhysical(void *virtualAddress) {
    if ((s32)virtualAddress < 0 && (u32)virtualAddress <= 0x9FFFFFFFU) {
        return (u32)virtualAddress & 0x1FFFFFFF;
    }
    if ((u32)(virtualAddress + 0x60000000) > 0x1FFFFFFFU) {
        return __osProbeTLB();
    }
    return (u32)virtualAddress & 0x1FFFFFFF;
}

s32 __osEnqueueAndYield(s32 *, s32);
extern void *__osRunningThread;

void osYieldThread(void)
{
  void *savedInterruptMask;
  s32 *runnableQueue;
  s8 *runningThreadBytes;
  int runnableState;
  savedInterruptMask = __osDisableInt();
  ((OSThread *)(runningThreadBytes = (s8 *) __osRunningThread))->state = (runnableState = 2);
  runnableQueue = &__osRunQueue;
  __osEnqueueAndYield(runnableQueue, runnableState);
  __osRestoreInt(savedInterruptMask);
}
