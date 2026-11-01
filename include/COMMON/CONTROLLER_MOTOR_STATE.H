#ifndef COMMON_CONTROLLER_MOTOR_STATE_H
#define COMMON_CONTROLLER_MOTOR_STATE_H
#include "TYPES.H"
#include "COMMON/LONE/CONTROLLER_MOTOR_START_DATA.H"
#include "COMMON/BOOT_MEMORY_AND_THREAD_BOUNDARIES.H"



typedef struct {
    s32 status;
    s32 messageQueueAddress;
    s32 channel;
} ControllerMotorIndexView;

extern s32 g_controllerMotorInitialized[];

extern u8 g_controllerMotorStartCommands[];

extern void __osSiGetAccess(void);
extern u32 __osContDataCrc(void *data);
extern void __osSiRelAccess(void);
#endif
