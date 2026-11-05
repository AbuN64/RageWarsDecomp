#include "types.h"
#include "Common/__osdispatchthread.h"
#include "Common/ctx.h"
#include "types.h"
#include "Common/version_calls.h"
#include "Common/os_timer_interrupt_internals.h"
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "../../include/libultra/os/thread.h"

extern OsThreadQueueNode *__osActiveQueue;
extern void *__osRunningThread;


void osDestroyThread(OSThread *thread) {
    OsThreadQueueNode *node;
    OsThreadQueueNode *cur;
    OsThreadQueueNode **head;
    s32 token;
    node = thread;
    token = __osDisableInt();
    if (node == 0) {
        node = __osRunningThread;
    } else if (node->state != 1) {
        __osDequeueThread(node->queue, node);
    }
    head = &__osActiveQueue;
    if (*head == node) {
        *head = node->next;
    } else {
        cur = *head;
        while (cur->priority != -1) {
            if (cur->next == node) {
                cur->next = node->next;
                break;
            }
            cur = cur->next;
        }
    }
    if (node == __osRunningThread) {
        __osDispatchThread();
    }
    __osRestoreInt(token);
}

#if defined(VERSION_US)
/* Zero word ending destroythread's object; no instruction reads it. */
unsigned int g_osInvalICacheZeroTail[1] = {
    0x00000000,
};
#endif
