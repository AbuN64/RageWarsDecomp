#include "include_asm.h"
#include "COMMON/LONE/RESOURCE_REQUEST_QUEUE.H"
#include "COMMON/WORLDSORTENTRY.H"
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
#include "../../include/SCHED/osscremoveclient.H"
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

extern s32 g_resourceLoadPriorityBoost;

void __scYield(void *scheduler) {
    void *currentRspTask;
    currentRspTask = (((struct SchedulerCurrentRspTaskView *) ((s8 *) scheduler))->currentRspTask);
    if ((((struct SchedulerTaskFlagsView *) ((s8 *) currentRspTask))->taskType) == 1) {
        (((struct SchedulerTaskFlagsView *) ((s8 *) currentRspTask))->state) = (s32) ((((struct SchedulerTaskFlagsView *) ((s8 *) currentRspTask))->state) | 0x10);
        osSpTaskYield();
    }
}

void Sched_HandleTaskCommands(void *scheduler) {
    NodeSchedHandleTaskCommands *node = 0;
    s32 value1 = 0;
    s32 value2 = 0;
    s32 flags;

    while (osRecvMesg(&((OSSched *)scheduler)->cmdQ, &node, 0) != -1) {
        if (node->type == 1 && (node->flags & 0x20) && g_resourceLoadPriorityBoost == 0) {
            g_resourceLoadPriorityBoost = 2;
            osSetThreadPri(&g_resourceCacheWorker, g_resourceLoadBusyPriority);
        }
        __scAppendList(scheduler, node);
    }

    if (((OSSched *)scheduler)->doAudio != 0 &&
        ((OSSched *)scheduler)->curRSPTask != 0) {
        __scYield(scheduler);
        return;
    }

    flags = (((OSSched *)scheduler)->curRSPTask == 0) * 2 |
            (((OSSched *)scheduler)->curRDPTask == 0);
    if (((s32 (*)(void *, s32 *, s32 *, s32))Sched_SelectRunnableTasks)(scheduler, &value1, &value2, flags) != flags) {
        ((void (*)(void *, s32, s32))Sched_StartSelectedTasks)(scheduler, value1, value2);
    }
}

int Sched_GetInterruptQueueAddress(int scheduler) {
    return scheduler + 0x40;
}
