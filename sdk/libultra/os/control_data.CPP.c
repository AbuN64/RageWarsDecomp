#include "include_asm.h"
#include "COMMON/LONE/CONTROLLER_MOTOR_STOP_DATA.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"
#include "COMMON/OBJRECAT4V6.H"
#include "COMMON/RUNTIME_DECLARATIONS.H"
#include "TYPES.H"
#include "COMMON/CONTROLLER_MOTOR_STATE.H"
#include <ultra64.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "../../include/os_pif.h"

/* control_data.CPP */
#if defined(VERSION_EU)
extern u8 g_controllerMotorStopCommands[];
u32 Control_StopMotorEu(void *motorContext) {
    Block40 saved;
    u8 *source;
    s32 i;

    source = (u8 *)&g_controllerStatusPifBuffer;
    if (g_controllerMotorInitialized[((ControllerMotorIndexView *)motorContext)->channel] == 0) {
        return 5;
    } else {
        u32 result;
        s32 count;

        __osSiGetAccess();
        g_controllerLastCommand = 3;
        __osSiRawStartDma(1, &g_controllerMotorStopCommands[((ControllerMotorIndexView *)motorContext)->channel << 6]);
        osRecvMesg(((ControllerMotorIndexView *)motorContext)->messageQueueAddress, 0, 1);
        __osSiRawStartDma(0, (u8 *)&g_controllerStatusPifBuffer);
        osRecvMesg(((ControllerMotorIndexView *)motorContext)->messageQueueAddress, 0, 1);
        count = ((ControllerMotorIndexView *)motorContext)->channel;
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

#if defined(VERSION_EU)
u32 Control_StartMotorEu(void *motorContext) {
    Block40 saved;
    u8 *source;
    s32 i;

    source = (u8 *)&g_controllerStatusPifBuffer;
    if (g_controllerMotorInitialized[((ControllerMotorIndexView *)motorContext)->channel] == 0) {
        return 5;
    } else {
        u32 result;
        s32 count;

        __osSiGetAccess();
        g_controllerLastCommand = 3;
        __osSiRawStartDma(1, &g_controllerMotorStartCommands[((ControllerMotorIndexView *)motorContext)->channel << 6]);
        osRecvMesg(((ControllerMotorIndexView *)motorContext)->messageQueueAddress, 0, 1);
        __osSiRawStartDma(0, (u8 *)&g_controllerStatusPifBuffer);
        osRecvMesg(((ControllerMotorIndexView *)motorContext)->messageQueueAddress, 0, 1);
        count = ((ControllerMotorIndexView *)motorContext)->channel;
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
        if ((result == 0) && ((__osContDataCrc(&g_controllerMotorStartData) & 0xFF) != saved.bytes[0x26])) {
            result = 4;
        }
        __osSiRelAccess();
        return result;
    }
}
#endif
