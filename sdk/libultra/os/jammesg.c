#include "../../include/thread_queue.h"
#include "include_asm.h"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "COMMON/OS_TIMER_INTERRUPT_INTERNALS.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

/* 802C0390_2.CPP */

/* 802C0250.CPP */
extern void __osEnqueueAndYield(void *threadQueue);

extern OSThread *__osRunningThread;

s32 osJamMesg(OSMesgQueue *messageQueue, void *message, s32 waitMode) {
    u32 saved;
    s32 index;

    saved = __osDisableInt();
    while (messageQueue->validCount >= messageQueue->msgCount) {
        if (waitMode != 1) {
            __osRestoreInt(saved);
            return -1;
        }
        __osRunningThread->state = 8;
        __osEnqueueAndYield(&messageQueue->fullqueue);
    }

    index = (messageQueue->first + messageQueue->msgCount - 1) % messageQueue->msgCount;
    messageQueue->first = index;
    messageQueue->msg[index] = message;
    messageQueue->validCount++;
    if (messageQueue->mtqueue->next != 0) {
        osStartThread(__osPopThread(&messageQueue->mtqueue));
    }
    __osRestoreInt(saved);
    return 0;
}

