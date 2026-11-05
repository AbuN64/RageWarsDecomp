#include "include_asm.h"
#include "Common/osviscale.h"
#include "System/video_context_views.h"
#include "types.h"
#include <platform_sdk.h>
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

