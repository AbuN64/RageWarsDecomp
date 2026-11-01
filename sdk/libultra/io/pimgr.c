#include "../../include/thread_queue.h"
#include "include_asm.h"
#include "../../include/OSINT/CREATE.H"
#include "../../include/libultra/os/pi_device_manager_operations.h"

/* 802BDEA0.CPP */
#if !defined(VERSION_US_REV1)
#include "TYPES.H"
#include "COMMON/OSVISCALE.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "../../include/os_pif.h"
extern OSDevMgr __osPiDevMgr;
extern s32 osGetThreadPri(struct OSThread_s *);
extern void osSetThreadPri(struct OSThread_s *, s32);
extern void osCreateThread(struct OSThread_s *, s32, void (*)(void *), void *, void *, s32);

void osCreatePiManager(s32 pri, OSMesgQueue *cmdQ, void **cmdBuf, s32 cmdMsgCnt)
{
    u32 savedMask;
    s32 oldPri;
    s32 myPri;

    if (__osPiDevMgr.active) {
        return;
    }
    osCreateMesgQueue(cmdQ, cmdBuf, cmdMsgCnt);
    osCreateMesgQueue(&g_peripheralManagerAccessQueue, g_peripheralAccessMessages, 1);

    if (!g_peripheralAccessQueueInitialized[0]) {
        __osPiCreateAccessQueue();
    }

    osSetEventMesg(8, &g_peripheralManagerAccessQueue, 0x22222222);
    oldPri = -1;
    myPri = osGetThreadPri(0);

    if (myPri < pri) {
        oldPri = myPri;
        osSetThreadPri(0, pri);
    }

    savedMask = __osDisableInt();
    __osPiDevMgr.active = 1;
    __osPiDevMgr.acsQueue = &g_peripheralDmaAccessQueue;
    __osPiDevMgr.dma = System_PeripheralRawDmaEntry;
    __osPiDevMgr.edma = System_PeripheralExtendedDmaEntry;
    __osPiDevMgr.evtQueue = &g_peripheralManagerAccessQueue;
    __osPiDevMgr.thread = &g_peripheralManagerThread;
    __osPiDevMgr.cmdQueue = cmdQ;
    osCreateThread(&g_peripheralManagerThread, 0, System_PeripheralManagerThreadEntry, &__osPiDevMgr, g_peripheralManagerThreadStack + sizeof(g_peripheralManagerThreadStack), pri);
    osStartThread(&g_peripheralManagerThread);
    __osRestoreInt(savedMask);

    if (oldPri != -1) {
        osSetThreadPri(0, oldPri);
    }
}
#endif


/* 802BDEC0.CPP */
#if defined(VERSION_US_REV1)
#include "TYPES.H"
#include "COMMON/OSVISCALE.H"
#include "../../include/os_pif.h"
extern OSDevMgr __osPiDevMgr;

extern s32 osGetThreadPri(struct OSThread_s *);
extern void osSetThreadPri(struct OSThread_s *, s32);
extern void osCreateThread(struct OSThread_s *, s32, void (*)(void *), void *, void *, s32);

void osCreatePiManager(s32 pri, OSMesgQueue *cmdQ, void **cmdBuf, s32 cmdMsgCnt)
{
    u32 savedMask;
    s32 oldPri;
    s32 myPri;

    if (__osPiDevMgr.active) {
        return;
    }
    osCreateMesgQueue(cmdQ, cmdBuf, cmdMsgCnt);
    osCreateMesgQueue(&g_peripheralManagerAccessQueue, g_peripheralAccessMessages, 1);

    if (!g_peripheralAccessQueueInitialized[0]) {
        __osPiCreateAccessQueue();
    }

    osSetEventMesg(8, &g_peripheralManagerAccessQueue, 0x22222222);
    oldPri = -1;
    myPri = osGetThreadPri(0);

    if (myPri < pri) {
        oldPri = myPri;
        osSetThreadPri(0, pri);
    }

    savedMask = __osDisableInt();
    __osPiDevMgr.active = 1;
    __osPiDevMgr.acsQueue = &g_peripheralDmaAccessQueue;
    __osPiDevMgr.dma = System_PeripheralRawDmaEntry;
    __osPiDevMgr.edma = System_PeripheralExtendedDmaEntry;
    __osPiDevMgr.evtQueue = &g_peripheralManagerAccessQueue;
    __osPiDevMgr.thread = &g_peripheralManagerThread;
    __osPiDevMgr.cmdQueue = cmdQ;
    osCreateThread(&g_peripheralManagerThread, 0, System_PeripheralManagerThreadEntry, &__osPiDevMgr, g_peripheralManagerThreadStack + sizeof(g_peripheralManagerThreadStack), pri);
    osStartThread(&g_peripheralManagerThread);
    __osRestoreInt(savedMask);

    if (oldPri != -1) {
        osSetThreadPri(0, oldPri);
    }
}
#endif
