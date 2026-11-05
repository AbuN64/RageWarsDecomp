#include "../../include/thread_queue.h"
#include "Common/boot_memory_and_thread_boundaries.h"
#include "Common/osviscale.h"
#include "Common/runtime_declarations.h"
#include "Ui/Tsmos/Screens/pakinterfacescreen.h"
#include "types.h"
#include <platform_sdk.h>
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
