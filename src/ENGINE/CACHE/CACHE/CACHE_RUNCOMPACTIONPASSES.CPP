#include "ENGINE/CACHE/CACHE.H"
#include "include_asm.h"
#include "TYPES.H"
#include <ultra64.h>
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "COMMON/CONTROLLER_MOTOR_STATE.H"
#include "COMMON/OS_TIMER_INTERRUPT_INTERNALS.H"
#include "COMMON/MANAGER.H"
#include "SCENE/RESOURCE_BINDING_AND_FADE_VIEWS.H"
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>

extern OSMesgQueue g_resourceHeapLockQueue;
extern ResourceManagerState g_resourceActivityState;


void Cache_RunCompactionPasses(s32 unused) {
    s32 pendingPasses;
    s32 remainingPasses;
    u32 mask;
    u32 interruptMask;
    s32 passIndex;
    ResourceManagerState *resourceManager;
    void *queueAddress;
    OSMesgQueue *receive;
    OSMesgQueue *send;

    resourceManager = &g_resourceActivityState;
#if defined(VERSION_US)
    if (resourceManager->active != 0) {
        resourceManager->active--;
    }
    resourceManager->count++;
    mask = __osDisableInt();
    pendingPasses = g_resourceHeapLockUsers + 1;
    g_resourceHeapLockUsers = pendingPasses;
    if (pendingPasses != 1) {
        __osRestoreInt(mask);
        queueAddress = (char *)resourceManager - (((char *)&((struct ResMgr *)0)->reservedWordC1C - (char *)0) - ((char *)&((struct ResMgr *)0)->heapLockQueue - (char *)0));
        receive = queueAddress;
        osRecvMesg(receive, 0, 1);
#else
    passIndex = 1;
    resourceManager->active = passIndex;
    resourceManager->count += passIndex;
    mask = __osDisableInt();
    pendingPasses = g_resourceHeapLockUsers + passIndex;
    g_resourceHeapLockUsers = pendingPasses;
    if (pendingPasses != passIndex) {
        __osRestoreInt(mask);
        queueAddress = (char *)resourceManager - (((char *)&((struct ResMgr *)0)->reservedWordC1C - (char *)0) - ((char *)&((struct ResMgr *)0)->heapLockQueue - (char *)0));
        receive = queueAddress;
        osRecvMesg(receive, 0, passIndex);
#endif
        passIndex = 0;
    } else {
        __osRestoreInt(mask);
        passIndex = 0;
    }
    do {
        Cache_CompactResourceHeap(0, 0);
        passIndex++;
    } while (passIndex < 10);
    interruptMask = __osDisableInt();
    remainingPasses = g_resourceHeapLockUsers - 1;
    g_resourceHeapLockUsers = remainingPasses;
    if (remainingPasses != 0) {
        __osRestoreInt(interruptMask);
        queueAddress = &g_resourceHeapLockQueue;
        send = queueAddress;
        osSendMesg(send, 0, 1);
    } else {
        __osRestoreInt(interruptMask);
    }
}
