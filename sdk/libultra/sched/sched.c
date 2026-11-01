#include "include_asm.h"
#include "COMMON/WORLDSORTENTRY.H"
#include "COMMON/VECTOR4F.H"
#include "COMMON/ITEMRECAT20V1.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include <ultra64.h>
#include "COMMON/OSVISCALE.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "COMMON/LLDIVRESULT.H"
#include "TYPES.H"
#include "TYPES.H"
#include "COMMON/BOOT_TV_TYPE.H"
#include "../../include/SCHED/osscremoveclient.H"
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>


void osScAddClient(OSSched *scheduler, OSScClient *client, OSMesgQueue *messageQueue) {
    s32 savedInterruptMask;
    savedInterruptMask = osSetIntMask(1);
    client->msgQ = messageQueue;
    client->next = scheduler->clientList;
    scheduler->clientList = client;
    osSetIntMask(savedInterruptMask);
}

void osScRemoveClient(OSSched *scheduler, OSScClient *client) {
    s32 saved;
    OSScClientWork *cur;
    OSScClientWork *prev;

    prev = 0;
    cur = scheduler->clientList;
    saved = osSetIntMask(1);
    while (cur != 0) {
        if (cur == client) {
            if (prev != 0) {
                prev->next = cur->next;
            } else {
                scheduler->clientList = cur->next;
            }
            break;
        }
        prev = cur;
        cur = cur->next;
    }
    osSetIntMask(saved);
}
