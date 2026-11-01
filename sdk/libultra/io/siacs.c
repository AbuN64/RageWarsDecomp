#include "TYPES.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/CONTREADFORMAT.H"
#include "COMMON/OSPIHANDLE_S.H"
#include "COMMON/CONTROLLER_MOTOR_STATE.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "../../include/OS/siaccess.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "COMMON/LONE/siaccess.H"

extern OSMesgQueue g_serialInterfaceAccessQueue;
extern OSMesg g_serialInterfaceAccessMessage;

/* siaccess.CPP */
/* 802BECB0.CPP */
void __osSiCreateAccessQueue(void) {
    g_serialInterfaceAccessQueueInitialized[0] = 1;
    osCreateMesgQueue(&g_serialInterfaceAccessQueue, &g_serialInterfaceAccessMessage, 1);
    osSendMesg(&g_serialInterfaceAccessQueue, 0, 0);
}

/* 802BECB0_2.CPP */
/* Takes the access token from the message queue g_serialInterfaceAccessQueue, first creating that one-message queue
   over g_serialInterfaceAccessMessage_Siaccess with osCreateMesgQueue and seeding it with a null message through osSendMesg_Mutex
   when g_serialInterfaceAccessQueueInitialized says it does not exist yet. Adapted from __osPiGetAccess with the queue, its buffer and its flag changed. */

static inline void create_access_queue(void) {
    g_serialInterfaceAccessQueueInitialized[0] = 1;
    osCreateMesgQueue(&g_serialInterfaceAccessQueue, &g_serialInterfaceAccessMessage, 1);
    osSendMesg(&g_serialInterfaceAccessQueue, 0, 0);
}

void __osSiGetAccess(void) {
    OSMesg token;

    if (!g_serialInterfaceAccessQueueInitialized[0]) {
        create_access_queue();
    }
    osRecvMesg(&g_serialInterfaceAccessQueue, &token, 1);
}

/* siaccess.CPP */
void __osSiRelAccess(void) {
    osSendMesg(&g_serialInterfaceAccessQueue, 0, 0);
}

/* G_SERIALINTERFACEACCESSQUEUEINITIALIZED.CPP */
#if defined(VERSION_US_REV1)
s32 g_serialInterfaceAccessQueueInitialized[1] = {0};
#endif
