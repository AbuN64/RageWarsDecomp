#include "TYPES.H"
#include "COMMON/CONTROLLER_MOTOR_STATE.H"
#include "../../include/libultra/io/si.h"

/** Report whether either low bit of the VI current register is set. */
int __osSiDeviceBusy(void) {
    return (*(volatile unsigned int *)0xA4800018 & 3) != 0;
}
