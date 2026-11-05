#include "types.h"
#include "Common/Lone/controller_motor_stop_data.h"
#include "Common/sharedplayer.h"
#include "types.h"
#include "Common/controller_motor_state.h"
#include "Common/boot_memory_and_thread_boundaries.h"
#include <platform_sdk.h>
#include <PR/os_internal_reg.h>
#include <PR/os_internal_si.h>
#include "../../include/os_pif.h"
#include "../../include/libultra/io/crc.h"

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
