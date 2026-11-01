#include "TYPES.H"
#include "COMMON/LONE/CONTROLLER_MOTOR_STOP_DATA.H"
#include "COMMON/SHAREDPLAYER.H"
#include "TYPES.H"
#include "COMMON/CONTROLLER_MOTOR_STATE.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "../../include/os_pif.h"

#if defined(VERSION_DE)

extern u8 g_controllerLastCommand;

extern u8 g_controllerMotorStopCommands[];






u32 Control_StopMotorDe(Triple *motorContext) {
    Block40 saved;
    u8 *source;
    s32 i;

    source = (u8 *)&g_controllerStatusPifBuffer;
    if (g_controllerMotorInitialized[motorContext->z] == 0) {
        return 5;
    } else {
        u32 result;
        s32 count;

        __osSiGetAccess();
        g_controllerLastCommand = 3;
        __osSiRawStartDma(1, &g_controllerMotorStopCommands[motorContext->z << 6]);
        osRecvMesg(motorContext->y, 0, 1);
        __osSiRawStartDma(0, (u8 *)&g_controllerStatusPifBuffer);
        osRecvMesg(motorContext->y, 0, 1);
        count = motorContext->z;
        if (count != 0) {
            i = 0;
            if (count > 0) {
                do {
                    i++;
                    source++;
                } while (i < count);
            }
        }
        saved = *(Block40 *)source;
        result = (saved.bytes[2] & 0xC0) >> 4;
        if ((result == 0) && ((__osContDataCrc(&g_controllerMotorStopData) & 0xFF) != saved.bytes[0x26])) {
            result = 4;
        }
        __osSiRelAccess();
        return result;
    }
}
#endif
