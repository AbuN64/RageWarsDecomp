#include "types.h"
#include "Engine/Cache/decmprsr.h"
#include "include_asm.h"
#include "Common/Lone/resource_request_queue.h"
#include "Common/worldsortentry.h"
#include "Common/vector4f.h"
#include "Common/runtime_declarations.h"
#include <platform_sdk.h>
#include "Common/osviscale.h"
#include "Common/boot_memory_and_thread_boundaries.h"
#include "Common/lldivresult.h"
#include "types.h"
#include "types.h"
#include "Common/boot_tv_type.h"
#include "../../include/SCHED/osscremoveclient.H"
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "Sched/sched_handletaskcommands.h"

extern s32 g_resourceLoadPriorityBoost;

void __scYield(void *scheduler) {
    OSScTask *currentRspTask;
    currentRspTask = ((OSSched *)scheduler)->curRSPTask;
    if (currentRspTask->list.t.type == 1) {
        currentRspTask->state = (s32) (currentRspTask->state | 0x10);
        osSpTaskYield();
    }
}

void Sched_HandleTaskCommands(void *scheduler) {
    OSScTask *node = 0;
    s32 value1 = 0;
    s32 value2 = 0;
    s32 flags;

    while (osRecvMesg(&((OSSched *)scheduler)->cmdQ, &node, 0) != -1) {
        if (node->list.t.type == 1 && (node->flags & 0x20) && g_resourceLoadPriorityBoost == 0) {
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
