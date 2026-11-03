#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "COMMON/CONTREADFORMAT.H"
#include "TYPES.H"
#include "COMMON/CONTROLLER_MOTOR_STATE.H"
#include "TYPES.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "../../include/os_pif.h"
#include "../../include/libultra/os/oscontreset_data.CPP.h"




s32 osContStartQuery(OSMesgQueue *completionQueue) {
    s32 result;
    u8 *p;

    __osSiGetAccess();
    p = &g_controllerLastCommand;
    if (*p != 0) {
        __osPackRequestData(0);
        __osSiRawStartDma(1, &g_controllerQueryPifBuffer);
        osRecvMesg(completionQueue, 0, 1);
    }
    result = __osSiRawStartDma(0, &g_controllerQueryPifBuffer);
    *p = 0;
    __osSiRelAccess();
    return result;
}


void osContGetQuery(OSContStatus *controllerStatus) {
    s32 validControllerMask;
    __osContGetInitData(&validControllerMask, controllerStatus);
}
