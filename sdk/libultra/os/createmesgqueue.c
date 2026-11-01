#include "include_asm.h"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "../../include/libgultra.h"
#include "COMMON/OSTHREAD_S.H"
#include "TYPES.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "DATA/REST_SOURCE_RECORDS.H"

/* createmesgqueue.c */
/* 802BFD80_2.CPP */

/* createmesgqueue.c */
void osCreateMesgQueue(OSMesgQueue *mq, OSMesg *msg, s32 msgCount) {
    mq->mtqueue = (void **)&__osThreadTail;
    mq->fullqueue = (void **)&__osThreadTail;
    mq->validCount = 0;
    mq->first = 0;
    mq->msgCount = msgCount;
    mq->msg = msg;
}

/* OSSTARTTHREAD_DATA.CPP */
extern char g_audioDiskTransferLinkTable[];

#if !(defined(VERSION_US) || defined(VERSION_US_REV1))
#ifdef VERSION_DE
RestOsstartthreadEncodedWordsLayout422 k_OsstartthreadEncodedWords = {
    { (void *)&__osThreadTail, (void *)&__osThreadTail, 0, 0 },
    "?s33",
    16.0f,
};
#endif
#ifdef VERSION_EU_X
extern char __osThreadTail[];
void *k_OsstartthreadEncodedWords[6] = {
    __osThreadTail, __osThreadTail, 0, 0,
    0, 0,
};
#endif
#ifdef VERSION_EU
void * k_OsstartthreadEncodedWords[6] = {
    (void *)&__osThreadTail, (void *)&__osThreadTail, 0, 0, (void *)((char *)&g_audioDiskTransferLinkTable + 1748), (void *)((char *)&g_audioDiskTransferLinkTable + 24),
};
#endif
#endif
