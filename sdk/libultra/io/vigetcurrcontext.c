#include "include_asm.h"
#include "COMMON/OSVISCALE.H"
#include "SYSTEM/VIDEO_CONTEXT_VIEWS.H"
#include "TYPES.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

/** Returns __osViCurr. */
extern __OSViContext *__osViCurr;

__OSViContext *__osViGetCurrentContext(void) {
    return __osViCurr;
}

extern __OSViContext *__osViNext;

void osViSetEvent(OSMesgQueue *messageQueue, OSMesg retraceMessage, u32 retraceInterval) {
    u32 savedInterruptMask;
    __OSViContext *rec;

    savedInterruptMask = __osDisableInt();
    rec = __osViNext;
    rec->msgq = messageQueue;
    rec->msg = retraceMessage;
    rec->retraceCount = retraceInterval;
    __osRestoreInt(savedInterruptMask);
}

