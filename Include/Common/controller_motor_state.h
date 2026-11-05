#ifndef COMMON_CONTROLLER_MOTOR_STATE_H
#define COMMON_CONTROLLER_MOTOR_STATE_H
#include "types.h"
#include "Common/Lone/controller_motor_start_data.h"
#include "Common/boot_memory_and_thread_boundaries.h"
#include "../../sdk/include/libultra/io/crc.h"



typedef struct {
    s32 status;
    s32 messageQueueAddress;
    s32 channel;
} ControllerMotorIndexView;

extern s32 g_controllerMotorInitialized[];

extern u8 g_controllerMotorStartCommands[];

extern void __osSiGetAccess(void);

extern void __osSiRelAccess(void);
#endif
