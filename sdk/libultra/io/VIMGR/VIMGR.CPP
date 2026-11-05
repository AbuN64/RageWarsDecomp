#include "../../../include/thread_queue.h"
#include "Common/osviscale.h"
#include "Common/os_timer_nodes.h"
#include "types.h"
#include "Common/boot_tv_type.h"
#include "../../../include/AUDIO/vi.H"
#include "System/vimgr.h"
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "include_asm.h"
#include "Common/boot_memory_and_thread_boundaries.h"
#include "Common/runtime_declarations.h"
#include "Common/os_timer_interrupt_internals.h"
#include "System/video_context_views.h"
#include "../../../include/AUDIO/__OSVISWAPCONTEXT.H"

/* 802BA5F0_22.CPP */
#if !(defined(VERSION_EU))
/* osCreateViManager, drafted from ultralib src/io/vimgr.c (2.0I: no __additional_scanline). */


extern OSThread g_videoManagerThread;
extern OSMesgQueue g_videoManagerEventQueue;
extern OSMesg g_videoManagerEventMessages[5];


extern s32 osGetThreadPri(OSThread *t);
extern void osSetThreadPri(OSThread *t, s32 pri);


void System_CreateVideoManager(s32 pri)
{
    u32 savedMask;
    s32 oldPri;
    s32 myPri;

    if (g_videoDeviceManager.active) {
        return;
    }
    __osTimerServicesInit();
    osCreateMesgQueue(&g_videoManagerEventQueue, g_videoManagerEventMessages, 5);
    g_videoRetraceEvent.hdr.type = 13;
    g_videoRetraceEvent.hdr.pri = 0;
    g_videoRetraceEvent.hdr.retQueue = 0;
    g_videoTimerEvent.hdr.type = 14;
    g_videoTimerEvent.hdr.pri = 0;
    g_videoTimerEvent.hdr.retQueue = 0;
    osSetEventMesg(7, &g_videoManagerEventQueue, &g_videoRetraceEvent);
    osSetEventMesg(3, &g_videoManagerEventQueue, &g_videoTimerEvent);
    oldPri = -1;
    myPri = osGetThreadPri(0);

    if (myPri < pri) {
        oldPri = myPri;
        osSetThreadPri(0, pri);
    }

    savedMask = __osDisableInt();
    g_videoDeviceManager.active = 1;
    g_videoDeviceManager.thread = &g_videoManagerThread;
    g_videoDeviceManager.cmdQueue = &g_videoManagerEventQueue;
    g_videoDeviceManager.evtQueue = &g_videoManagerEventQueue;
    g_videoDeviceManager.acsQueue = 0;
    g_videoDeviceManager.dma = 0;
    g_videoDeviceManager.edma = 0;
    osCreateThread(&g_videoManagerThread, 0, System_VideoManagerThreadEntry, &g_videoDeviceManager, g_videoManagerThreadStack + 0x1000 / sizeof(u64), pri);
    __osViInit();
    osStartThread(&g_videoManagerThread);
    __osRestoreInt(savedMask);

    if (oldPri != -1) {
        osSetThreadPri(0, oldPri);
    }
}
#endif

/* 802BA5F0_23.CPP */
#if defined(VERSION_EU)
#include "Common/resident_event_handler.h"
#include "Common/os_timer_nodes.h"
s32 osGetThreadPri(OSThread *thread);
void osSetThreadPri(OSThread *thread, s32 priority);
extern OSThread g_videoManagerThread;
extern OSMesgQueue g_videoManagerEventQueue;
extern void *g_videoManagerEventMessages[5];
extern u64 g_videoManagerThreadStack[0x200];

void System_CreateVideoManagerEu(s32 managerPriority) {
    s32 currentPriority;
    s32 restorePriority;
    u32 savedInterruptMask;

    if (g_videoDeviceManager.active == 0) {
        restorePriority = -1;
        __osTimerServicesInit();
        osCreateMesgQueue(&g_videoManagerEventQueue, g_videoManagerEventMessages, 5);
        g_videoRetraceEvent.hdr.type = 0xD;
        g_videoRetraceEvent.hdr.pri = 0;
        g_videoRetraceEvent.hdr.retQueue = 0;
        g_videoTimerEvent.hdr.type = 0xE;
        g_videoTimerEvent.hdr.pri = 0;
        g_videoTimerEvent.hdr.retQueue = 0;
        osSetEventMesg(7, &g_videoManagerEventQueue, &g_videoRetraceEvent);
        osSetEventMesg(3, &g_videoManagerEventQueue, &g_videoTimerEvent);
        currentPriority = osGetThreadPri(0);
        if (currentPriority < managerPriority) {
            restorePriority = currentPriority;
            osSetThreadPri(0, managerPriority);
        }
        savedInterruptMask = __osDisableInt();
        g_videoDeviceManager.active = 1;
        g_videoDeviceManager.cmdQueue = &g_videoManagerEventQueue;
        g_videoDeviceManager.evtQueue = &g_videoManagerEventQueue;
        g_videoDeviceManager.thread = &g_videoManagerThread;
        g_videoDeviceManager.acsQueue = 0;
        g_videoDeviceManager.dma = 0;
        g_videoDeviceManager.edma = 0;
        osCreateThread(&g_videoManagerThread, 0, System_VideoManagerThreadEntry, &g_videoDeviceManager, g_videoManagerThreadStack + sizeof(g_videoManagerThreadStack) / sizeof(g_videoManagerThreadStack[0]), managerPriority);
        __osViInit();
        osStartThread(&g_videoManagerThread);
        __osRestoreInt(savedInterruptMask);
        if (restorePriority != -1) {
            osSetThreadPri(0, restorePriority);
        }
    }
}
#endif

/* viMgrMain, drafted from ultralib src/io/vimgr.c: the VI manager thread swaps the video context on
   each retrace, posts the client's retrace message every retraceCount retraces, advances the
   64-bit OS time, and runs timer interrupts. retrace is its static u16. */

extern u16 g_videoManagerRetraceCountdown;

extern __OSViContext *__osViGetCurrentContext(void);

extern void __osTimerInterrupt(void);

static inline u16 *viRetrace(void)
{
    return &g_videoManagerRetraceCountdown;
}

void System_RunVideoManager(OSDevMgr *arg)
{
    __OSViContext *vc;
    OSDevMgr *dm;
    OSIoMesg *mb;
    s32 first;
    u32 count;

    u16 *retraceInit;
    u32 *intrCount;
    u32 *baseCounter;
    u64 *currentTime;

    mb = 0;
    first = 0;
    vc = __osViGetCurrentContext();
    retraceInit = &g_videoManagerRetraceCountdown;
    *retraceInit = vc->retraceCount;
    if (*retraceInit == 0) {
        *retraceInit = 1;
    }
    dm = arg;

    while (1) {
        osRecvMesg(dm->evtQueue, (OSMesg *)&mb, 1);
        switch (mb->hdr.type) {
            case 13:
                __osViSwapContext();
                if (--*viRetrace() == 0) {
                    vc = __osViGetCurrentContext();
                    if (vc->msgq != 0) {
                        osSendMesg(vc->msgq, vc->msg, 0);
                    }
                    *viRetrace() = vc->retraceCount;
                }

                intrCount = &g_timerServiceCounter;
                (*intrCount)++;

                if (first) {
                    count = osGetCount();
                    __osCurrentTime = count;
                    first = 0;
                }

                baseCounter = &__osBaseCounter;
                count = *baseCounter;
                *baseCounter = osGetCount();
                count = *baseCounter - count;
                currentTime = &__osCurrentTime;
                *currentTime = *currentTime + count;
                break;
            case 14:
                __osTimerInterrupt();
                break;
            default:
                break;
        }
    }
}
