#include "include_asm.h"
#include "COMMON/OSVISCALE.H"
#include "SYSTEM/VIDEO_CONTEXT_VIEWS.H"
#include "TYPES.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

/** Returns __osViCurr. */
extern void *__osViCurr;

void *__osViGetCurrentContext(void) {
    return __osViCurr;
}

extern void *__osViNext;

void osViSetEvent(OSMesgQueue *messageQueue, OSMesg retraceMessage, u32 retraceInterval) {
    u32 savedInterruptMask;
    VideoContextEventView *rec;

    savedInterruptMask = __osDisableInt();
    rec = __osViNext;
    rec->f10 = messageQueue;
    rec->f14 = retraceMessage;
    rec->f2 = retraceInterval;
    __osRestoreInt(savedInterruptMask);
}

