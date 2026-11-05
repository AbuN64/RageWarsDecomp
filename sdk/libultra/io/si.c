#include "types.h"
#include "Common/controller_motor_state.h"
#include "../../include/libultra/io/si.h"

/** Report whether either low bit of the VI current register is set. */
int __osSiDeviceBusy(void) {
    return (*(volatile unsigned int *)0xA4800018 & 3) != 0;
}
