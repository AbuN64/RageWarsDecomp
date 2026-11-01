#include "../../../include/thread_queue.h"
#include "include_asm.h"
#include "COMMON/LONE/OS_RUNNABLE_THREAD_QUEUE.H"
#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/CTX.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "../../../include/libultra/io/leointerrupt_resume.h"

/* leointerrupt_resume.c */
void __osLeoAbnormalResume(void) {
    DiskTransferInfo *diskTransferInfo;
    u32 status;

    status = *(volatile u32 *)0xA4600010;
    diskTransferInfo = (DiskTransferInfo *)(g_currentDiskPeripheralHandle + 0x14);
    while (status & 3) {
        status = *(volatile u32 *)0xA4600010;
    }
    *(volatile u32 *)0xA5000510 = diskTransferInfo->bmControl | 0x10000000;
    status = *(volatile u32 *)0xA4600010;
    while (status & 3) {
        status = *(volatile u32 *)0xA4600010;
    }
    *(volatile u32 *)0xA5000510 = diskTransferInfo->bmControl;
    __osLeoResume();
    {
        volatile u32 *statusAddr = (volatile u32 *)0xA4600010;
        s32 mask = 0x100401;
        s32 *flagsAddr = &__OSGlobalIntMask;
        s32 flags = *flagsAddr;

        *statusAddr = 2;
        *flagsAddr = flags | mask;
    }
}

void __osLeoResume(void) {
    OSMesgQueue *node;
    s32 validCountValue;
    s32 v1;
    s32 v0;
    s32 rem;

    node = g_piInterruptManager.cur;
    if (node != 0) {
        validCountValue = node->validCount;
        v1 = node->msgCount;
        if (validCountValue < v1) {
            v0 = node->first + validCountValue;
            rem = v0 % v1;
            node->msg[rem] = g_piInterruptManager.f4;
            node->validCount = node->validCount + 1;
            if (node->mtqueue->next != 0) {
                __osEnqueueThread(&__osRunQueue, __osPopThread(&node->mtqueue));
            }
        }
    }
}
