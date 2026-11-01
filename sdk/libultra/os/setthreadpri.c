#include "../../include/thread_queue.h"
#include "include_asm.h"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "TYPES.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

/* osSetThreadPri, drafted from ultralib src/os/setthreadpri.c (2.0I-L, non-debug). */



extern OSThread *__osRunQueue;
extern OSThread *__osRunningThread;
extern void __osDequeueThread(OSThread **queue, OSThread *t);
extern void __osEnqueueAndYield(OSThread **queue);

void osSetThreadPri(OSThread *t, s32 pri)
{
    register u32 saveMask;
    OSThread **runQueue;

    saveMask = __osDisableInt();

    if (t == 0) {
        t = __osRunningThread;
    }

    if (t->priority != pri) {
        t->priority = pri;

        if (t != __osRunningThread && t->state != 1) {
            __osDequeueThread(t->queue, t);
            __osEnqueueThread(t->queue, t);
        }

        runQueue = &__osRunQueue;
        if (__osRunningThread->priority < (*runQueue)->priority) {
            __osRunningThread->state = 2;
            __osEnqueueAndYield(runQueue);
        }
    }

    __osRestoreInt(saveMask);
}

