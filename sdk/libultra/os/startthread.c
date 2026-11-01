#include "../../include/thread_queue.h"
#include "include_asm.h"
#include "COMMON/LONE/OS_RUNNABLE_THREAD_QUEUE.H"
#include "COMMON/NODERECAT1C.H"
#include "COMMON/CTX.H"
#include "TYPES.H"
#include "COMMON/VERSION_CALLS.H"
#include "COMMON/__OSDISPATCHTHREAD.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

/* 802C0840_3.CPP */

/* startthread.c */
extern ThreadNode *__osRunningThread;

extern void __osEnqueueAndYield(ThreadNode **queue, ThreadNode *node);
void osStartThread(OSThread *thread) {
    ThreadNode *threadStorage = (ThreadNode *)thread;
    ThreadNode **sentinel;
    u32 token;
    token = __osDisableInt();
    if (threadStorage->state == 1) {
        goto state_one;
    }
    if (threadStorage->state != 8) {
        goto state_done;
    }
    threadStorage->state = 2;
    __osEnqueueThread((ThreadNode **)&__osRunQueue, threadStorage);
    goto state_done;
state_one:
    if (threadStorage->queue == 0) {
        goto insert_arg;
    }
    sentinel = (ThreadNode **)&__osRunQueue;
    if (threadStorage->queue == sentinel) {
insert_arg:
        threadStorage->state = 2;
        __osEnqueueThread((ThreadNode **)&__osRunQueue, threadStorage);
    } else {
        threadStorage->state = 8;
        __osEnqueueThread(threadStorage->queue, threadStorage);
        __osEnqueueThread(sentinel, __osPopThread(threadStorage->queue));
    }
state_done:
    if (__osRunningThread == 0) {
        __osDispatchThread();
    } else if (__osRunningThread->priority < (*(ThreadNode **)&__osRunQueue)->priority) {
        __osRunningThread->state = 2;
        __osEnqueueAndYield((ThreadNode **)&__osRunQueue, __osRunningThread);
    }
    __osRestoreInt(token);
}

