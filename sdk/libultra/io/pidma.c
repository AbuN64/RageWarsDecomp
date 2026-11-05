#include "Common/runtime_declarations.h"
#include "types.h"
#include "types.h"
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "../../include/libultra/io/pigetcmdq.h"

typedef struct Queue Queue;






s32 osPiStartDma(OSIoMesg *entry, s32 subtype, s32 direction, u32 deviceAddress,
                   void *dramAddress, u32 transferSize, OSMesgQueue *completionQueue) {
    s16 type;

    if (__osPiDevMgr.active == 0) {
        return -1;
    }
    type = 12;
    if (direction == 0) {
        type = 11;
    }
    entry->hdr.type = type;
    entry->hdr.pri = subtype;
    entry->hdr.retQueue = completionQueue;
    entry->dramAddr = dramAddress;
    entry->devAddr = deviceAddress;
    entry->size = transferSize;
    entry->piHandle = 0;
    if (subtype != 1) {
        return osSendMesg(osPiGetCmdQueue(), (s32)entry, 0);
    }
    return osJamMesg(osPiGetCmdQueue(), entry, 0);
}
