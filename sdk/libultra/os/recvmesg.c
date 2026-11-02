#include "../../include/thread_queue.h"
#include "include_asm.h"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "TYPES.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "DATA/REST_SOURCE_RECORDS.H"

/* recvmesg.c */
/* 802C0390_4.CPP */

/* recvmesg.c */
extern OSThread *__osRunningThread;
extern void __osEnqueueAndYield(void *);

s32 osRecvMesg(OSMesgQueue *queue, OSMesg *message, s32 block)
{
    u32 mask = __osDisableInt();

    while (queue->validCount == 0) {
        if (!block) {
            __osRestoreInt(mask);
            return -1;
        }
        __osRunningThread->state = 8;
        __osEnqueueAndYield(&queue->mtqueue);
    }

    if (message != 0) {
        *message = queue->msg[queue->first];
    }
    queue->first = (queue->first + 1) % queue->msgCount;
    queue->validCount--;
    if (queue->fullqueue->next != 0) {
        osStartThread(__osPopThread(&queue->fullqueue));
    }
    __osRestoreInt(mask);
    return 0;
}

#if defined(VERSION_EU_X)
/* Zero word ending osRecvMesg; no instruction reads it. */
unsigned int g_osRecvMesgZeroTail[1] = {
    0x00000000,
};

/* Stale float 879.875f; no instruction reads it. */
float g_osRecvMesgStaleFloat[1] = { 879.875f };

/* Zero word after the stale float; no instruction reads it. */
unsigned int g_osRecvMesgSecondZeroTail[1] = {
    0x00000000,
};
#endif

/* OSRECVMESG_PADDING.CPP */
#if defined(VERSION_US_REV1)
/* ROM-grounded data: zero word after osRecvMesg */
unsigned char g_osRecvMesgZeroWord[4] = { 0, 0, 0, 0 };

/* Stale float 879.875f; no instruction reads it. */
float g_osRecvMesgStaleFloat[1] = { 879.875f };
#endif
