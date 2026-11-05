#include "include_asm.h"
#include "Common/worldsortentry.h"
#include "Common/vector4f.h"
#include "Common/runtime_declarations.h"
#include <platform_sdk.h>
#include "Common/osviscale.h"
#include "Common/boot_memory_and_thread_boundaries.h"
#include "Common/lldivresult.h"
#include "types.h"
#include "types.h"
#include "Common/boot_tv_type.h"
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
