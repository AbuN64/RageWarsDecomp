#include "COMMON/OSPIHANDLE_S.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "TYPES.H"
#include "../../include/OSINT/CREATE.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "../../include/os_pif.h"
#include "include_asm.h"
#include "../../include/OSINT/__OSPIRELACCESS.H"

/* 802BEA40.CPP */
/* Takes the access token from the message queue g_peripheralDmaAccessQueue, first creating that one-message queue
   over g_peripheralDmaAccessMessage with osCreateMesgQueue and seeding it with a null message through osSendMesg_Mutex
   when g_peripheralAccessQueueInitialized says it does not exist yet. */

static inline void create_access_queue(void) {
    g_peripheralAccessQueueInitialized[0] = 1;
    osCreateMesgQueue(&g_peripheralDmaAccessQueue, &g_peripheralDmaAccessMessage, 1);
    osSendMesg(&g_peripheralDmaAccessQueue, 0, 0);
}

void __osPiCreateAccessQueue(void) {
    g_peripheralAccessQueueInitialized[0] = 1;
    osCreateMesgQueue(&g_peripheralDmaAccessQueue, &g_peripheralDmaAccessMessage, 1);
    osSendMesg(&g_peripheralDmaAccessQueue, 0, 0);
}

void __osPiGetAccess(void) {
    OSMesg token;

    if (!g_peripheralAccessQueueInitialized[0]) {
        create_access_queue();
    }
    osRecvMesg(&g_peripheralDmaAccessQueue, &token, 1);
}

/* 802BEA40_2.CPP */
void __osPiRelAccess(void) {
    osSendMesg(&g_peripheralDmaAccessQueue, 0, 0);
}

