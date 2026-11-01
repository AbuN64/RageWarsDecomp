#include "../../include/thread_queue.h"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "TYPES.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

extern OSThread *__osRunningThread;

extern void __osEnqueueAndYield(void *queue_data);



s32 osSendMesg(OSMesgQueue *queue, OSMesg entry, s32 mode) {
    s32 saved;

    saved = __osDisableInt();
    while (queue->validCount >= queue->msgCount) {
        if (mode != 1) {
            __osRestoreInt(saved);
            return -1;
        }
        __osRunningThread->state = 8;
        __osEnqueueAndYield(&queue->fullqueue);
    }
    queue->msg[(queue->first + queue->validCount) % queue->msgCount] = entry;
    queue->validCount++;
    if (queue->mtqueue->next != 0) {
        osStartThread(__osPopThread(&queue->mtqueue));
    }
    __osRestoreInt(saved);
    return 0;
}
