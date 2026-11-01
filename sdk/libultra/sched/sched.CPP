#include "include_asm.h"
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
extern s32 g_schedulerPendingFramebuffer;
extern s32 g_displayedFramebufferAndRefreshRate;
void __scAppendList(OSSched *scheduler, void *task) {
    void *previousTail;

    if ((((struct OSScTask_s *)task)->list.t.type) == 2) {
        previousTail = scheduler->audioListTail;
        if (previousTail != 0) {
            ((struct OSScTask_s *)previousTail)->next = task;
        } else {
            scheduler->audioListHead = task;
        }
        scheduler->audioListTail = task;
        scheduler->doAudio = 1;
    } else {
        previousTail = scheduler->gfxListTail;
        if (previousTail != 0) {
            ((struct OSScTask_s *)previousTail)->next = task;
        } else {
            scheduler->gfxListHead = task;
        }
        scheduler->gfxListTail = task;
    }
    ((struct OSScTask_s *)task)->next = 0;
    ((struct OSScTask_s *)task)->state = (((struct OSScTask_s *)task)->flags) & 3;
}

void *Sched_GetTaskWithAvailableFramebuffer(struct OSScTask_s *scheduler) {
    s32 f1a;
    s32 f1b;
    void *v2;

    if (scheduler == 0) {
        return 0;
    }
    f1a = (s32)scheduler->framebuffer;
    if (f1a == g_displayedFramebufferAndRefreshRate) {
        return 0;
    }
    v2 = osViGetCurrentFramebuffer();
    f1b = (s32)scheduler->framebuffer;
    if (f1b == (s32)v2) {
        return 0;
    }
    if (f1b != g_schedulerPendingFramebuffer) {
        return scheduler;
    }
    return 0;
}

s32 Sched_CompleteTaskAndSwapBuffer(void *scheduler, void *task) {
    if ((((s32)((struct OSScTask_s *)task)->state)) & 3) {
        return 0;
    }
    if ((((struct OSScTask_s *)task)->list.t.type) != 1) {
        return 1;
    }
    if (((((s32)((struct OSScTask_s *)task)->flags)) & 0x60) != 0x60) {
        return 1;
    }
    osViSwapBuffer(((s32)((struct OSScTask_s *)task)->framebuffer));
    return 1;
}


#if defined(VERSION_US)
unsigned int k_SchedEncodedWords[3] = {
    0x63616C65, 0x52000088, 0x00000008,
};
#endif

#if defined(VERSION_EU_X)
char s_SchedLILLYJIMText[12] =
    "LILLY\000\000\000JIM ";
#endif

#if defined(VERSION_DE)
float k_SchedEncodedWordsBlock1[3] = {
    10.24f, 1.0f, 81.92f,
};
#endif
